#ifndef UTIL_FILE_MONITOR_H_
#define UTIL_FILE_MONITOR_H_

#include "unise/callback.h"
#include "unise/thread.h"
#include "unise/boost_wrap.h"
#include "util/inotify.h"
#include "util/event.h"

namespace unise
{

/// @brief 文件更新监控类，独立线程
/// @usage 这个类是独立的线程，推荐使用单例的方式应用，以下是建议用法：
/// main.cc:
///     // 启动文件监控线程
///     Singleton<FileMonitor>::get()->start();
/// module.cc:
///     // 注册文件更新时要触发的回调函数
///     Singleton<FileMonitor>::get()->register_fcb("data/filename", NewPermanentCallback(...));
/// 为了使线程功能跟内聚，建议 NewPermanentCallback 中的回调只做文件更新的通知，
/// 通知其本职线程加载文件，而不是在回调中直接加载文件。
/// 当然，如果监控的文件数较少，而且加载复杂度不高，也可以直接在回调中完成文件加载。
class FileMonitor : public Thread
{
public:
    /// @brief 便于以单例方式使用，须支持默认构造函数
    FileMonitor();
    ~FileMonitor();

    /// @brief 注册文件、目录路径，以及处理文件更新事件的回调函数
    /// @param[in] path : 文件或目录路径
    /// @param[in] callback : 处理文件或者目录更新的回调函数
    /// @return 注册是否成功
    /// @note 能观察到的事件：
    /// 1. 文件被修改、删除、替换；
    /// 2. 目录中文件被增加、删除；目录被删除、替换；
    /// @note
    /// 1. 无法观察到目录中文件的移动；
    /// 2. 为简化设计，FileMonitor 不会告诉回调变动的具体信息，需要回调方自己记录
    /// 历史状态以便与当前状态比对。
    /// 3. 注册时路径必须存在；但注册后路径的删除不会使回调删除，FileMonitor 仍然
    /// 会继续尝试监控该路径是否有新文件被生成。
    bool register_fcb(const std::string& path, Closure* callback);

    /// @brief 移除已经添加的路径，该路径下所有的回调函数都被删除
    /// @param path
    void remove_fcb(const std::string &path);

    /// @brief 线程主函数入口
    int run();

    /**
     * @brief 停止监控线程
     * @note  请用户不要调用
     */
    void stop() { _sig_exit = true; }

protected:
    /// @brief 文件更新管理的内部类型
    struct fm_info_t {
        int                                         wd;         ///< watch 句柄
        std::vector<boost::shared_ptr<Closure> >    callbacks;  ///< 该路径上注册的回调列表
    };
    typedef std::map<int, std::string>          wd_map_t;
    typedef std::map<std::string, fm_info_t>    path_map_t;

    // 要 watch 的 inotify 事件
    static const uint32_t WATCH_IN_EVENTS = IN_CLOSE_WRITE | IN_DELETE | IN_CREATE
                                            | IN_DELETE_SELF | IN_MOVE | IN_MODIFY
                                            | IN_IGNORED;
    // static const uint32_t HANDLE_IN_EVENTS = IN_CLOSE_WRITE | IN_DELETE | IN_CREATE
    //                                        | IN_IGNORED | IN_MODIFY;
    static const uint32_t HANDLE_IN_EVENTS = IN_CLOSE_WRITE;
    // 可能需要随着监控文件数调整？
    static const size_t READ_BUFLEN = 4096;

private:
    /// @brief 处理文件或者目录更新的 inotify 事件
    /// @param wd
    /// @param mask
    void _handle_event(int wd, uint32_t mask);

    /// @brief 处理正在监控的 inode 被删除或移动的情况
    /// @note 监控文件的 inode 一旦被删除或者移动，路径就改变了，我们必须尝试监控到新的文件
    void _handle_fail();

    HANDLE_EVENT(on_exit);
    void _on_exit() {
        _sig_exit = true;
    }

    int32_t                     _timeout_ms;    ///< 每次 select 的超时时间
    int32_t                     _watch_fd;      ///< inotify 的 watch 句柄
    boost::shared_mutex         _mutex;         ///< 更新锁
    wd_map_t                    _wd_map;        ///< 从 wd 到路径名
    path_map_t                  _path_map;      ///< 从路径名到回调
    std::vector<std::string>    _fail_paths;    ///< inode失效的路径列表
    bool                        _sig_exit;      ///< 让线程退出的信号
};  // FileMonitor

}   // namespace unise

#endif  // UTIL_FILE_MONITOR_H_
