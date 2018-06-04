// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  INDEX_GENERAL_FACT_DOC_H_
#define  INDEX_GENERAL_FACT_DOC_H_

#include <map>
#include <string>
#include <vector>
#include "unise/fact_doc.h"

namespace unise
{
#pragma pack(push, 1)
class GeneralFactDoc : public FactDoc
{
public:
    GeneralFactDoc() {}
    virtual ~GeneralFactDoc() {}
    virtual int32_t get_score() const {
        return score;
    }
    virtual DocId get_doc_id() const {
        return docid;
    }
    virtual std::string get_dimension_name() const {
        return "GeneralFactDoc";
    }

public:
    DocId docid;
    int32_t score;
};
#pragma pack(pop)
}

#endif  // INDEX_GENERAL_FACT_DOC_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
