// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_DOC_FACTORY_H
#define  UNISE_DOC_FACTORY_H

#include <string>
#include <fstream>
#include "unise/factory.h"
#include "unise/base.h"
#include "unise/serialization.h"

namespace comcfg {
class ConfigUnit;
}

namespace unise
{
class DimensionDoc;

/**
 * @brief 作为DimensionDoc的工厂
 *        根据一个字符串，产生一个DimensionDoc
 *        根据一个DimensionDoc的指针，销毁一个对象
 * @note 多类dimension doc可以使用一个DocFactory来构造，不过架构仍然
 *       会为每类DimensionDoc构造一个DocFactory对象
 *       请参见配置文件中DimensionDoc下面的DocFactory配置项，配置项的
 *       取值就是派生类的类名
 */
class DocFactory
{
public:
    DocFactory() {}
    virtual ~DocFactory() {}

    /**
     * @breaf 提供配置的初始化函数，配置为配置文件中,一个完整的插件配置项
     *        如：[..@DimensionDoc]
     *            [..@Scorers]
     *
     *        每个DocFactory对象构造后，会被调用初始化函数
     *        用来做一些如词表加载等工作
     *
     * @return bool
     * @retval true初始化成功；否则，服务退出
     * @see
     * @note 每种DimensionDoc只有一个Factory，单线程调用
     *
     */
    virtual bool init(const comcfg::ConfigUnit &) = 0;


    /**
     * @breaf 返回Factory的名字，框架用来打log、统计
     *
     * @param [in] : none
     * @param [out] : none
     * @return std::string
     * @retval 返回DocFactory的名字
     * @see
     * @note 一般名字跟类名相同
    **/
    virtual std::string get_name() const = 0;

    /**
     * @breaf 根据一行文本，构造出一个MyDimensionDoc的对象,MyDimensionDoc继承自
     *        DimensionDoc，外部插件使用时，通过down_cast或dynamic_cast从
     *        DimensionDoc*或DimensionDoc&转化为实际对象的指针或引用
     *
     * @param [in] : record，一行文本，以\t分割各个字段，一般第一个字段为docid
     * @param [out] : none
     * @return DimensionDoc*
     * @retval 返回构造好的DimensionDoc的指针，如果为NULL，构造失败。
     * @see
     * @note 所生成的对象由DocFactory来管理其内存空间，框架仅索引doc的指针
     *       框架内部、其他插件里面，禁止delete该指针
    **/
    virtual DimensionDoc * produce(const std::string & record) = 0;

    /**
     * @breaf 反序列化函数，获取所有的DimensionDoc *
     *
     * @param [in] : none 
     * @param [out] : 存储所有的DimensionDoc * 容器
     * @return bool 
     * @retval 返回是否反序列化成功，如果成功，返回true；否则false。
     * @note 默认返回false，用户如果需要使用序列化与反序列化，必须重载该方法
     *       为了兼容，以及简单，默认不开启该功能而已
    **/
    virtual bool deserialize(std::vector<DimensionDoc *> * dimension_docs) {
        (void)(dimension_docs);
        return false;
    }

    /**
     * @breaf 序列化函数，获取所有的DimensionDoc *
     *
     * @param [in] : 存储所有的DimensionDoc * 容器
     * @param [out] : none 
     * @return bool 
     * @retval 返回是否序列化成功，如果成功，返回true；否则false。
     * @note 默认返回false，用户如果需要使用序列化与反序列化，必须重载该方法
     *       为了兼容，以及简单，默认不开启该功能而已
    **/
    virtual bool serialize(const std::vector<const DimensionDoc *> & dimension_docs) {
        (void)(dimension_docs);
        return false;
    }

    /**
     * @breaf 根据一个指针，析构指针指向的对象
     *
     * @param [in] : doc，待删除对象的指针
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note 内部可以直接delete，析构可以正确执行
     *       内部如果需要访问MyDimensionDoc的成员函数或属性，
     *       需要首先将DimensionDoc*向下转换为具体派生类MyDimensionDoc的
     *       指针
    **/
    virtual void destroy(DimensionDoc * doc) = 0;

    /**
     * @brief 提供一个实时接口用来通知删除事件，指针doc所指对象在15s后
     *        会被执行destroy
     *
     * @param [in] : 删除事件是针对这个doc的
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note 该接口为删除事件通知，可不实现
     *       调用频率：每次update或delete时，会先调用该接口
     *       需要实现为多线程安全的，注意检索线程同步在执行
    **/
    virtual void on_delete_event(DimensionDoc * doc)
    {
        (void)(doc);
    }

    /**
     * @brief 提供一个设置doc数据类型和该数据增量信息    
     *
     * @param [in] : 增量信息
     * @param [out] : none
     * @return none
     * @retval 
     * @see
     * @note 用户请勿使用
    **/
    void set_event_info(const event_info_t& event_info) {
        _event_info = event_info;
    }

    /**
     * @brief 提供一个打印增量数据信息的接口
     *
     * @param [in] : none
     * @param [out] : none
     * @return 返回event_info结构信息
     * @retval 
     * @see
     * @note 
    **/
    const event_info_t* get_event_info() const {
        return &_event_info;
    }

private:
    event_info_t _event_info;
};

REGISTER_FACTORY(DocFactory);
#define REGISTER_DOC_FACTORY(name) REGISTER_CLASS(DocFactory, name)
}

#endif  // UNISE_DOC_FACTORY_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
