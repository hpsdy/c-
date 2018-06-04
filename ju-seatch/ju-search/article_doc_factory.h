// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_DEMO_DOC_FACTORY_H
#define  UNISE_DEMO_DOC_FACTORY_H

#include <string>
#include "Configure.h"
#include "unise/doc_factory.h"

namespace unise {
class DimensionDoc;

class ArticleDocFactory : public DocFactory {
public:
    ArticleDocFactory() : _produce_num(0LLU) {}
    virtual ~ArticleDocFactory() {}
    virtual bool init(const comcfg::ConfigUnit& conf) {
        (void)(conf);
        _dump_path = "./data/" + get_name() + ".dump";
        return true;
    }

    virtual std::string get_name() const {
        return "ArticleDocFactory";
    }

    virtual DimensionDoc * produce(const std::string & record);
    virtual bool serialize(const std::vector<const DimensionDoc *> & dimension_docs);
    virtual bool deserialize(std::vector<DimensionDoc *> * dimension_docs);
    virtual void destroy(DimensionDoc * doc);
    virtual void on_delete_event(DimensionDoc * doc);

private:
    uint64_t _produce_num; 
    std::string _dump_path;
};

}
#endif  // UNISE_DEMO_DOC_FACTORY_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
