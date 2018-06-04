// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "serve/engine_unit_manager.h"
#include "unise/base.h"
#include "unise/singleton.h"
#include "unise/delay_callback.h"

using namespace std;
namespace unise
{

EngineUnitManager::EngineUnitManager() {}
EngineUnitManager::~EngineUnitManager()
{
    // note:在析构检索引擎之前，确保所有的回调都执行完毕
    // 析构所有的EngineUnit
    for (std::map<std::string, EngineUnit*>::iterator it =
                engine_unit_map_.begin();
            it != engine_unit_map_.end();
            ++it) {
        delete it->second;
    }
}

bool EngineUnitManager::init(const comcfg::ConfigUnit& conf) {
    try {
        int num = (int)conf.size();
        UNOTICE("%d EngineUnit tobe Inited", num);
        for (int i = 0; i < num; ++i) {
            string engine_unit_name(conf[i]["EngineUnitName"].to_cstr());
            string engine_unit_type(conf[i]["EngineUnitType"].to_cstr());
            UNOTICE("The %d EngineUnit is:%s", i + 1, engine_unit_name.c_str());
            if (get_engine_unit(engine_unit_name) != NULL) {
                UFATAL("%s already Exist", engine_unit_name.c_str());
                return false;
            }
            // note: use register to generate the EngineUnit
            EngineUnit * engine_unit = EngineUnitFactory::get_instance(engine_unit_type);
            if (engine_unit == NULL) {
                UFATAL("Generate EngineUnitType:%s fail", engine_unit_type.c_str());
                return false;
            }
            if (engine_unit->init(conf[i])) {
                pair<string, EngineUnit*> v(engine_unit_name, engine_unit);
                engine_unit_map_.insert(v);
                UNOTICE("Init %s of type %s succ",
                        engine_unit->get_name().c_str(),
                        engine_unit->get_type().c_str());
            } else {
                UFATAL("Init %s fail", engine_unit_name.c_str());
                delete engine_unit;
                UFATAL("Init %s fail end", engine_unit_name.c_str());
                return false;
            }
        }
    } catch (const comcfg::ConfigException & e) {
        UFATAL("Init EngineUnitManager fail:%s", e.what());
        return false;
    }

    // 查询各个引擎是否还正在初始化
    // 只有都初始化完成后才能继续运行
    bool is_initing = true;
    do {
        is_initing = false;
        for (std::map<std::string, EngineUnit*>::iterator it =
                    engine_unit_map_.begin();
                    it != engine_unit_map_.end();
                    ++it) {
            if (it->second->is_initing()) {
                is_initing = true;
                // 有一个未初始化成功，就再等会检查吧
                // 可能在加载数据，也可能在初始化服务中
                UNOTICE("waiting for EngineUnit[%s] to be inited",
                            it->second->get_name().c_str());
                // 睡一秒
                usleep(1000000);
                break;
            }
        }
    } while (is_initing);

    // 判断是否都初始化成功
    bool all_inited = true;
    for (std::map<std::string, EngineUnit*>::iterator it =
                        engine_unit_map_.begin();
                        it != engine_unit_map_.end();
                        ++it) {
        if (!it->second->inited()) {
            all_inited = false;
            break;
        }
    }
    UNOTICE("Init EngineUnitManager %s", all_inited ? "succ" : "false");
    return all_inited;
}

EngineUnit * EngineUnitManager::get_engine_unit(const std::string & name)
{
    map<string, EngineUnit*>::iterator it = engine_unit_map_.find(name);
    if (it != engine_unit_map_.end()) {
        return it->second;
    } else {
        return NULL;
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
