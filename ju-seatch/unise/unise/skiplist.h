#ifndef  UTIL_SKIPLIST_H_
#define  UTIL_SKIPLIST_H_

#include <iterator>
// 为了避免与 boost 库产生编译问题，likely/unlikely 采用 boost 实现而非
// linux/compiler.h 实现
//#include <linux/compiler.h>
#include <boost/lockfree/detail/branch_hints.hpp>

#include "unise/singleton.h"
#include "unise/delay_callback.h"
#include "unise/callback.h"

namespace unise
{
using boost::lockfree::detail::likely;
using boost::lockfree::detail::unlikely;

template<typename _Tp> class _SkipListConstIterator;

#pragma pack(push, 1)   // 减小 Skip list 的内存占用，可能会影响性能，细抠性能时可以比较一下
/// @brief Skip lists 节点，这里把 list 的 key 和 value 合并到一起，不做区分。
/// @note 使用 POD 类型和分配器，才能为此类型多分配一部分尾部空间用来存储 forward 数组
template<typename _Tp>
struct _SkipListNode {
    _Tp                 data;       ///< 不区分 key, value，_Tp 需重载 < 运算符
    _SkipListNode<_Tp> *forward[1]; ///< 前向指针数组，指向对应层级下一个节点
};

/// @brief Skip list 实现
/// @note *无锁 Skip list 的实现*
/// 1. UniSE 的整个设计都希望尽量追求无锁实现，但完全线程安全的无锁实现要考虑
/// 很多方面，实现困难而且容易存在BUG。为了使无锁实现更为简单也更易被理解，
/// UniSE 采取了一写多读的模型，即在任何时刻永远只会有一个线程在写数据。
/// 无锁 Skip list 也采纳了这种模型，所以在使用时要注意这一点，永远不要在
/// 多于一个线程中对同一个 SkipList 对象进行写操作。
/// 2. 为了性能，基础类型模块尽量不打日志，通过单测保证正确性，可以抛异常到上层
template<typename _Tp>
class SkipList
{
public:
    typedef uint32_t                    size_type;      ///< 尽量减少空间占用
    typedef int8_t                      level_type;     ///< 需要是有符号整型，好 handle i-- 的情况
    typedef _Tp                         key_type;
    typedef _Tp                         value_type;
    typedef _SkipListConstIterator<_Tp> const_iterator;
    typedef _SkipListNode<_Tp>          node_type;

protected:
    // SkipList 的层级与 lg(n)/lg(1/PROB) 有一定相关性，实验发现 13~15 足以覆盖一千万数据
    // 这个值会对 head 节点大小有一定影响，当短链较多时，不宜设置过大
    const static level_type             MAXLEVEL = 16;  ///< Skip list 最大层级
    // Redis 使用 1/4，经测试十万数据时较链表大约有 7 bytes 的 overhead，性能与 std::set 相当
    // 1/2 情况下性能会略差，overhead 也增大到 13 bytes 左右
    const static double                 PROB = 0.25;    ///< 下层元素出现在上层概率
    node_type                          *_head;          ///< Skip list 的链表头
    volatile size_type                  _size;          ///< 当前 Skip list 的长度
    level_type                          _level;         ///< 当前 Skip list 的层级数

public:
    /// @brief 头节点为空
    /// @note 是否能让头节点非空？
    SkipList()
        : _size(0),
          _level(1) {
        _head = _create_node(MAXLEVEL);
        for (level_type i = 0; i < MAXLEVEL; i++) {
            _head->forward[i] = NULL;
        }
    }

    /// @brief 从头节点开始删除，保证删除过程中头节点处于正常位置
    /// @note 目前来看，clear 和析构不用延时删除节点，因为上层会做延时
    ~SkipList() {
        this->clear();
        ::free(_head);
        _head = NULL;
    }

    /// @brief 链表开始迭代器，即第0层第一个节点
    const_iterator begin() const {
        return _head->forward[0];
    }

    /// @brief 链表结束迭代器，即NULL指针
    const_iterator end() const {
        return NULL;
    }

    /// @brief 当前 skiplist 大小
    /// @return
    size_type size() const {
        return _size;
    }

    void clear() {
        node_type *x = _head->forward[0];
        for (level_type i = 0; i < MAXLEVEL; i++) {
            _head->forward[i] = NULL;
        }
        while (NULL != x) {
            node_type *y = x;
            x = x->forward[0];
            ::free(y);
        }
        _size = 0;
        _level = 0;
    }

    /// @brief 按键值查找元素，找到后返回迭代器
    /// @param[in] t 元素的值
    /// @return 找到返回 iterator；找不到返回 end()
    const_iterator find(const _Tp &t) const {
        const_iterator lower = this->lower_bound(t);
        if (lower != this->end() && (*lower) == t) {
            return lower;
        } else {
            return this->end();
        }
    }

    /// @brief 以键值为下界查找元素，找到第一个不小于t的节点后，返回其迭代器
    /// @param[in] t 元素的值
    /// @return 找到返回 iterator；找不到返回 end()
    const_iterator lower_bound(const _Tp &t) const {
        node_type * x = _head;
        for (level_type i = _level - 1; i >= 0; i--) {
            // 通过一个临时变量，避免写线程修改指针的影响
            node_type * cp = x->forward[i];
            while (cp && cp->data < t) {
                x = cp;
                cp = cp->forward[i];
            }
        }
        return x->forward[0];
    }

    /// @brief 根据值插入一个元素，重复的元素不会被更新。
    /// @param[in] t 要插入的元素
    /// @return end() 插入失败；非 end() 存在或插入成功；
    const_iterator insert(const _Tp &t) {
        node_type * update[MAXLEVEL];
        // 找到要插入的位置
        node_type *next = _find_prev(t, update);
        // 不接受元素重复的情况。
        if (unlikely(next != NULL && next->data == t)) {
            return next;
        }
        // 确定节点层级
        level_type level = _random_level();
        if (unlikely(level > _level)) {
            for (level_type i = _level; i < level; i++) {
                update[i] = _head;
            }
            _level = level;
        }
        // 创建节点
        node_type *x = _create_node(level);
        if (unlikely(NULL == x)) {
            // TODO 是 return 还是 throw？
            return this->end();
        }
        x->data = t;
        // 完善其后续节点
        for (level_type i = 0; i < level; i++) {
            x->forward[i] = update[i]->forward[i];
        }
        // 从底向上切换各层前序节点的指针（一写多读，不需要使用 CAS）
        for (level_type i = 0; i < level; i++) {
            update[i]->forward[i] = x;
        }
        ++_size;
        return x;
    }

    /// @brief 根据值删除一个元素。
    /// @param[in] t 要删除的元素
    /// @return erase 的节点数
    size_type erase(const _Tp & t) {
        node_type * update[MAXLEVEL];
        node_type * x = _head;
        level_type i = 0;
        // 找到要删除元素的位置
        x = _find_prev(t, update);
        if (x != NULL && x->data == t) {
            // 从底向上切换各层前序节点的指针（一写多读，不需要使用 CAS）
            for (i = 0; i < _level; i++) {
                if (update[i]->forward[i] == x) {
                    update[i]->forward[i] = x->forward[i];
                }
            }
            _delayed_free(x);
            --_size;
            for (i = _level - 1; i >= 0 && NULL == _head->forward[i]; i--) {
                // DO NOTHING
            }
            _level = i + 1;
            return 1;
        } else {
            return 0;
        }
    }

protected:
    /// @brief 节点最多出现在第几层的随机数产生器
    /// @return 该节点属于几层链表
    /// @note 实现来自 redis
    inline level_type _random_level() const {
        level_type level = 1;
        // global_init 时需要初始化随机数种子
        while ((random() & 0xFFFF) < (PROB * 0xFFFF)) {
            level += 1;
        }
        return (level < MAXLEVEL) ? level : MAXLEVEL;
    }

    /// @brief 找到要插入的位置，即各个层级的前序节点
    /// @param[in] t 要查找的元素
    /// @param[out] update 各个层级的前序节点
    /// @return 第一个 key 不小于查找元素的节点
    inline node_type * _find_prev(const _Tp &t, node_type **update) const {
        node_type * x = _head;
        for (level_type i = _level - 1; i >= 0; i--) {
            node_type * cp = x->forward[i];
            while (cp && cp->data < t) {
                x = cp;
                cp = cp->forward[i];
            }
            update[i] = x;
        }
        return x->forward[0];   // 一写多读，这里不考虑 forward 指针被改写的情况。
    }

    /// @brief 创建节点
    /// @param[in] level 动态的层级数组
    /// @return 创建好的节点
    inline node_type * _create_node(level_type level) {
        // FIXME 内存分配失败 log? exception?
        node_type * node = (node_type*) malloc(sizeof(node_type) + (level - 1) * sizeof(node_type*));
        return node;
    }
    /// @note 遍历时，iterator 是暴露出来的。在多线程情况下，如果不能做延迟删除，
    /// 就需要对节点进行引用计数或至少打标记，这样做内存代价较高，我们不愿意采纳。
    void _delayed_free(node_type * node) {
        if (!Singleton<DelayedEnv>::get()->add_callback(
                NewCallback(free, static_cast<void *>(node)))) {
            // FIXME log? exception?
        }
    }
};
#pragma pack(pop)

/// @brief Skip list 的迭代器
template<typename _Tp>
struct _SkipListConstIterator {
    typedef _SkipListConstIterator<_Tp>  _Self;
    typedef _SkipListNode<_Tp>          _Node;

    typedef ptrdiff_t                   difference_type;
    typedef std::forward_iterator_tag   iterator_category;
    typedef _Tp                         value_type;
    typedef const _Tp*                  pointer;
    typedef const _Tp&                  reference;

    _SkipListConstIterator(): _node() { }

    _SkipListConstIterator(const _Node* __x): _node(__x) { }

    /// @brief dereference 运算符
    reference operator*() const {
        return _node->data;
    }

    /// @brief 指针运算符
    pointer operator->() const {
        return &_node->data;
    }

    /// @brief 前置++
    _Self& operator++() {
        _node = _node->forward[0];
        return *this;
    }

    /// @brief 后置++
    _Self operator++(int) {
        _Self __tmp = *this;
        _node = _node->forward[0];
        return __tmp;
    }

    /// @brief 相等比较运算符
    bool operator==(const _Self& __x) const {
        return _node == __x._node;
    }

    /// @brief 不等比较运算符
    bool operator!=(const _Self& __x) const {
        return _node != __x._node;
    }

    const _Node* _node;     ///< 存储当前节点信息
};

}
#endif  // SKIP_LIST_H_
