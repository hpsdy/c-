#include "util/util.h"
#include "compact_forward_index.h"
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::CodedOutputStream;

namespace unise
{

bool CompactForwardIndex::build(const std::vector<TokenHit> & token_hits)
{
    // 每个doc不能build多次
    GOOGLE_DCHECK_EQ(NULL, _head);
    size_t token_hits_size = token_hits.size();
    if (0 == token_hits_size) {
        // 没有token，所以什么也不构建，不修改_head
        // 应该返回true，毕竟，虽然没有token，但是可能被NOT逻辑检索出来
        // 其他函数应该检查_head是否为NULL，做相应判断
        return true;
    }

    // 申请临时buffer，并估算一个肯定足够的大小
    size_t buffer_length = token_hits_size *
                             (sizeof (head_item_t) +
                              sizeof (AnnotationId) +
                              sizeof (SectionId) +
                              sizeof (int32_t) + 1);
    uint8_t * buffer = new uint8_t[buffer_length];

    // 首先构造head信息
    head_item_t * head_p = reinterpret_cast<head_item_t*>(buffer);
    head_item_t * cur_head_item = NULL;

    TokenId last_token_id = ILLEGAL_TOKEN_ID;
    for (size_t i = 0; i < token_hits_size; ++i) {
        if(token_hits.at(i).get_token_id() != last_token_id) {
            // 新的token开始了
            head_p->token_id = token_hits.at(i).get_token_id();
            head_p->num = 1U;
            last_token_id = token_hits.at(i).get_token_id();
            cur_head_item = head_p;
            ++head_p;
        } else {
            // 跟上个token相同，token个数自增
            ++cur_head_item->num;
        }
    }

    // 然后接着head构造body信息，存储实际的hit
    // 填充head中的offset信息
    uint8_t * body_p = reinterpret_cast<uint8_t*>(head_p);
    head_p = reinterpret_cast<head_item_t*>(buffer);
    last_token_id = ILLEGAL_TOKEN_ID;
    for (size_t i = 0; i < token_hits_size; ++i) {
        const TokenHit & hit = token_hits.at(i);
        if (hit.get_token_id() != last_token_id) {
            // 这是一个新的token
            // offset使用字节数
            head_p->offset = body_p - buffer;
            // 写section，使用该方法可兼容修改SectionId的类型
            SectionId sid = hit.get_section_id();
            body_p = CodedOutputStream::WriteRawToArray(&sid,
                                                        sizeof (SectionId),
                                                        body_p);
            // 写annotation id
            AnnotationId aid = hit.get_annotation_id();
            body_p = CodedOutputStream::WriteRawToArray(&aid,
                                                        sizeof (AnnotationId),
                                                        body_p);
            // 写pos
            body_p = CodedOutputStream::WriteVarint32ToArray(hit.get_pos(), body_p);
            last_token_id = hit.get_token_id();
            // 头部指针指向下一个token
            ++head_p;
        } else {
            // 这是token跟上一个token相同
            // 写section，使用该方法可兼容修改SectionId的类型
            SectionId sid = hit.get_section_id();
            body_p = CodedOutputStream::WriteRawToArray(&sid,
                                                        sizeof (SectionId),
                                                        body_p);
            // 写annotation id
            AnnotationId aid = hit.get_annotation_id();
            body_p = CodedOutputStream::WriteRawToArray(&aid,
                                                        sizeof (AnnotationId),
                                                        body_p);
            // 写pos
            body_p = CodedOutputStream::WriteVarint32ToArray(hit.get_pos(), body_p);
        }
    }
    // 构建正排成功，申请内存,修改_head
    size_t real_size = body_p - buffer;
    _head = new uint8_t[real_size];
    _end = _head + real_size;
    memcpy(_head, buffer, real_size);
    // 删除临时内存
    delete []buffer;
    
    return true;
}

bool CompactForwardIndex::get_token_id_list(std::vector<TokenId> *token_id_list) const
{
    if (unlikely(_head == NULL)) {
        return true;
    }
    head_item_t * head_item = reinterpret_cast<head_item_t*>(_head);
    size_t token_num = get_token_num();
    for (size_t i = 0; i < token_num; ++i, ++head_item) {
        token_id_list->push_back(head_item->token_id);
    }
    return true;
}

size_t CompactForwardIndex::get_doc_token_hit_list_size(TokenId token_id) const
{
    if (unlikely(_head == NULL)) {
        return 0U;
    }
    const head_item_t * head_item = find(token_id);
    if (unlikely(head_item == NULL)) {
        return 0U;
    } else {
        return head_item->num;
    }
}

bool CompactForwardIndex::get_doc_token_hit_list(TokenId token_id,
        const std::vector<doc_token_hit_t*> &doc_token_hit_list) const
{
    if (unlikely(_head == NULL)) {
        return 0U;
    }
    const head_item_t * head_item = find(token_id);
    if (unlikely(head_item == NULL)) {
        return false;
    }
    size_t wanna_size = doc_token_hit_list.size();
    size_t real_size = head_item->num;
    GOOGLE_DCHECK_EQ(wanna_size, real_size);

    uint8_t * input_start = _head+ head_item->offset;
    // TODO(wangguangyuan) : 使用更精确的size
    CodedInputStream input(input_start, _end - input_start);
    uint32_t value;
    for (size_t i = 0; i < real_size; ++i) {
        if (!input.ReadRaw(&(doc_token_hit_list.at(i)->section_id), sizeof (SectionId)) ||
            !input.ReadRaw(&(doc_token_hit_list.at(i)->annotation_id), sizeof (AnnotationId)) ||
            !input.ReadVarint32(&value)) {
            return false;
        }
        doc_token_hit_list.at(i)->pos = static_cast<uint32_t>(value);
    }
    return true;
}

}

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
