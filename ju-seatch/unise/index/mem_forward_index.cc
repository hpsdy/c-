/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file mem_forward_index.cc
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/05 16:52:26
 * @version $Revision$
 * @brief 内存FactDoc正排信息
 *
 **/


#include "util/util.h"
#include "mem_forward_index.h"
#include <boost/scoped_array.hpp>

using google::protobuf::io::CodedInputStream;
using google::protobuf::io::CodedOutputStream;

namespace unise
{

bool MemForwardIndex::build(const std::vector<TokenHit> &token_hits)
{/*{{{*/
    if (0 == token_hits.size()) {
        return true;
    }
    TokenId last_token_id = 0;
    SecAnnoInfo sec_anno_info;
    std::vector<SecAnnoInfo> token_hit_info;
    for (size_t i = 0; i < token_hits.size(); ++i) {
        if (token_hits[i].get_token_id() != last_token_id || 0 == i) {
            //新的TokenId
            if (0 != i) {
                token_hit_info.push_back(sec_anno_info);
                add_one_token_to_map(last_token_id, token_hit_info);
                token_hit_info.clear();
            }
            last_token_id = token_hits[i].get_token_id();
            sec_anno_info.section_id = token_hits[i].get_section_id();
            sec_anno_info.annotation_id = token_hits[i].get_annotation_id();
            sec_anno_info.pos.clear();
            sec_anno_info.pos.push_back(token_hits[i].get_pos());;
        } else if (token_hits[i].get_section_id() != sec_anno_info.section_id ||
                   token_hits[i].get_annotation_id() != sec_anno_info.annotation_id) {
            //相同的TokenId，另一个SectionID&AnnotationID
            token_hit_info.push_back(sec_anno_info);
            sec_anno_info.section_id = token_hits[i].get_section_id();
            sec_anno_info.annotation_id = token_hits[i].get_annotation_id();
            sec_anno_info.pos.clear();
            sec_anno_info.pos.push_back(token_hits[i].get_pos());;
        } else {
            //相同的TokenId，相同的SectionID&AnnotationID
            sec_anno_info.pos.push_back(token_hits[i].get_pos());;
        }
    }
    token_hit_info.push_back(sec_anno_info);
    add_one_token_to_map(last_token_id, token_hit_info);
    return true;
}/*}}}*/

size_t MemForwardIndex::get_token_num() const
{/*{{{*/
    return _token_map.size();
}/*}}}*/

bool MemForwardIndex::get_token_id_list(std::vector<TokenId> *token_id_list) const
{/*{{{*/
    for (std::map<TokenId, TokenInfo>::const_iterator iter = _token_map.begin();
            iter != _token_map.end();
            ++iter) {
        token_id_list->push_back(iter->first);
    }
    return true;
}/*}}}*/

size_t MemForwardIndex::get_doc_token_hit_list_size(TokenId token_id) const
{/*{{{*/
    std::map<TokenId, TokenInfo>::const_iterator iter = _token_map.find(token_id);
    if (iter != _token_map.end()) {
        return (iter->second).hit_list_size;
    }
    return 0;
}/*}}}*/

bool MemForwardIndex::get_doc_token_hit_list(TokenId token_id,
        const std::vector<doc_token_hit_t*> &doc_token_hit_list) const
{/*{{{*/
    std::map<TokenId, TokenInfo>::const_iterator iter = _token_map.find(token_id);
    if (iter == _token_map.end()) {
        return false;
    }
    CodedInputStream input((iter->second).data.get(), (iter->second).data_len);
    size_t i = 0;
    const void* data_ptr = NULL;
    int left_len = 0;
    do {
        SectionId secid = 0;
        AnnotationId annoid = 0;
        uint32_t temp_secid;
        uint32_t temp_annoid;
        //读取section id和annotation id
        if (!input.ReadVarint32(&temp_secid) || !input.ReadVarint32(&temp_annoid)) {
            return false;
        }
        secid = static_cast<SectionId>(temp_secid);
        annoid = static_cast<SectionId>(temp_annoid);
        //读取pos
        int32_t pos = 0;
        while (true) {
            uint32_t inc = 0;
            if (!input.ReadVarint32(&inc)) {
                return false;
            }
            if (0 == inc) {
                break;
            }
            doc_token_hit_list[i]->section_id = secid;
            doc_token_hit_list[i]->annotation_id = annoid;
            pos += inc;
            doc_token_hit_list[i]->pos = pos;
            i++;
        }
        input.GetDirectBufferPointerInline(&data_ptr, &left_len);
    } while (left_len > 0);
    return true;
}/*}}}*/

void MemForwardIndex::add_one_token_to_map(TokenId token_id,
        const std::vector<SecAnnoInfo> &token_hit_info)
{/*{{{*/
    const uint32_t MaxVarint32Bytes = 5;
    uint32_t count = 0;
    for (size_t i = 0; i < token_hit_info.size(); ++i) {
        count += 2 + token_hit_info[i].pos.size() + 1;
    }
    uint32_t max_data_len = MaxVarint32Bytes * count;
    uint32_t hit_list_size = 0;
    boost::scoped_array<uint8> data_ptr(new uint8 [max_data_len]);
    uint8 *data = data_ptr.get();
    for (size_t i = 0; i < token_hit_info.size(); ++i) {
        //填写section id
        data = CodedOutputStream::WriteVarint32ToArray(token_hit_info[i].section_id, data);
        //填写annoation id
        data = CodedOutputStream::WriteVarint32ToArray(
                    static_cast<uint32_t>(token_hit_info[i].annotation_id), data);
        //填写pos
        for (size_t j = 0; j < token_hit_info[i].pos.size(); ++j) {
            int32_t pos = 0 == j ? token_hit_info[i].pos[0] :
                          token_hit_info[i].pos[j] - token_hit_info[i].pos[j - 1];
            data = CodedOutputStream::WriteVarint32ToArray(pos, data);
        }
        data = CodedOutputStream::WriteVarint32ToArray(0x0, data);
        hit_list_size += token_hit_info[i].pos.size();
    }
    TokenInfo token_info;
    token_info.data_len = data - data_ptr.get();
    token_info.data.reset(new uint8 [token_info.data_len]);
    memcpy(token_info.data.get(), data_ptr.get(), token_info.data_len);
    token_info.hit_list_size = hit_list_size;
    _token_map[token_id] = token_info;
}/*}}}*/

}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
