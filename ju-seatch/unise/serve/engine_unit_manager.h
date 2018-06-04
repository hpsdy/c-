// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  ENGINE_UNIT_MANAGER_H_
#define  ENGINE_UNIT_MANAGER_H_

#include <map>
#include <string>
#include "unise/engine_unit.h"
#include "Configure.h"

namespace unise
{

// TODO (wangguangyuan): make the EngineUnitManager tobe a Global Singleton
class EngineUnitManager
{
public:
    EngineUnitManager();
    ~EngineUnitManager();
    bool init(const comcfg::ConfigUnit&);
    EngineUnit * get_engine_unit(const std::string & name);

private:
    std::map<std::string, EngineUnit*> engine_unit_map_;
};
}

#endif  // ENGINE_UNIT_MANAGER_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
