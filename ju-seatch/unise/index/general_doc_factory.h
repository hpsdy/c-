// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_GENERAL_DOC_FACTORY_H_
#define  INDEX_GENERAL_DOC_FACTORY_H_

#include <string>
#include <Configure.h>
#include "unise/doc_factory.h"
#include "unise/base.h"
#include "unise/general_plugin.pb.h"

namespace unise
{
class DimensionDoc;

class GeneralDocFactory : public DocFactory
{
public:
    GeneralDocFactory() {}
    virtual ~GeneralDocFactory() {}
    virtual bool init(const comcfg::ConfigUnit& conf);
    virtual std::string get_name() const {
        return "GeneralDocFactory";
    }
    virtual DimensionDoc * produce(const std::string & record);
    virtual void destroy(DimensionDoc * doc);
    virtual void on_delete_event(DimensionDoc * doc);
private:
    FormatConfig _format_config;

    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(GeneralDocFactory);
};

}
#endif  // INDEX_GENERAL_DOC_FACTORY_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
