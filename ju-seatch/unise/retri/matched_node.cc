// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "unise/matched_node.h"
#include "unise/base.h"
#include "util/util.h"

using std::vector;
namespace unise
{

MatchedNode::MatchedNode(TokenId token_id, vector<doc_token_hit_t*>* hits)
    : _token_id(token_id), _hits_per_doc(hits) {}

void MatchedNode::to_string(std::string* output) const
{
    GOOGLE_DCHECK(output);
    output->append("[");
    output->append(Uint64ToString(_token_id));
    output->append(",");
    for (size_t k = 0; k < _hits_per_doc->size(); ++k) {
        const doc_token_hit_t * hit = _hits_per_doc->at(k);
        output->append("[");
        output->append(UintToString(static_cast<uint32_t>(hit->section_id)));
        output->append(",");
        output->append(UintToString(static_cast<uint32_t>(hit->annotation_id)));
        output->append(",");
        output->append(IntToString(hit->pos));
        output->append("],");
    }
    output->append("],");
}

}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
