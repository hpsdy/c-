// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "index/das_inc_builder.h"
#include <Configure.h>
#include "index/repository_manager.h"
#include "index/dimension_doc_manager.h"
#include "unise/base.h"
#include "unise/fact_doc.h"
#include "util/util.h"

DEFINE_bool(add_overwrite, false, "whether overwrite the last doc with the current doc");
DEFINE_bool(das_inc_has_from_id, true, "whether the das inc has from id");

namespace unise
{
DasIncBuilder::DasIncBuilder(RepositoryManager * repository_manager)
    : _repository_manager(repository_manager),
      _dimension_doc_manager(repository_manager->get_dimension_doc_manager())
{
}

bool DasIncBuilder::init(const comcfg::ConfigUnit & conf)
{
    _fact_doc_builder.reset(new DocBuilder(_repository_manager));
    return true;
}


void DasIncBuilder::process_one_line(const std::string & line)
{
    das_inc_record_t record;
    if (format_input(line, &record) == false) {
        // void函数，内部打印WARNING log
        UWARNING("[\tlvl=FOLLOW\t] das inc format unknown:%s", line.c_str());
        return;
    }
    return process_one_record(record);
}

bool DasIncBuilder::format_input(const std::string& line, das_inc_record_t * record)
{
    if (line == "") {
        return false;
    }
    std::string sub_str;
    size_t start = 0U;
    size_t pos = line.find(DAS_SEP, start);
    if (pos == string::npos) {
        // 有返回值的函数，内部尽量少打印WARNING
        UNOTICE("not find event id");
        return false;
    }
    sub_str = line.substr(start, pos - start);
    if (!StringToUint(sub_str, &(record->event_id))) {
        UNOTICE("event_id can't be %s", sub_str.c_str());
        return false;
    }
    start = pos + 1;
    pos = line.find(DAS_SEP, start);
    if (pos == string::npos) {
        UNOTICE("not find op_id");
        return false;
    }
    sub_str = line.substr(start, pos - start);
    if (!StringToUint(sub_str, &(record->op_id))) {
        UNOTICE("op_id can't be %s", sub_str.c_str());
        return false;
    }
    start = pos + 1;
    pos = line.find(DAS_SEP, start);
    if (pos == string::npos) {
        UNOTICE("not find level id");
        return false;
    }
    sub_str = line.substr(start, pos - start);
    if (!StringToUint(sub_str, &(record->level_id))) {
        UNOTICE("level id can't be ", sub_str.c_str());
        return false;
    }
    if (FLAGS_das_inc_has_from_id) {
        start = pos + 1;
        pos = line.find(DAS_SEP, start);
        if (pos == string::npos) {
            UNOTICE("not find from_id");
            return false;
        }
        sub_str = line.substr(start, pos - start);
        if (!StringToUint(sub_str, &(record->from_id))) {
            UNOTICE("from_id can't be %s", sub_str.c_str());
            return false;
        }
    }
    start = pos + 1;
    if (start < line.length()) {
        record->other = line.substr(start);
    }
    return true;
}

uint32_t DasIncBuilder::cascade_filt() {
    uint8_t mask = 0;
    uint8_t flag = 0;
    const SkipList<DocId> * list =
        _dimension_doc_manager->get_filt_relation_docids(&flag, &mask);
    return _fact_doc_builder->filt_relation_ship(list, flag, mask);
}

void DasIncBuilder::delete_record(const das_inc_record_t& record) {
    // get docid from the das other info
    DocId docid;
    size_t pos = record.other.find('\t');

    // note: 'other' may only contains a docid
    if (pos == string::npos) {
        pos = record.other.length();
    }
    if (false == StringToUint64(record.other.substr(0, pos), &docid)) {
        UWARNING("[\tlvl=COUNT\t] get docid fail for event_id[%u] opid:%u other:%s",
                    record.event_id,
                    record.op_id,
                    record.other.c_str());
        return;
    }
    if (record.level_id == _dimension_doc_manager->get_fact_doc_level_id()) {
        // delete inverted index and forward index first
        _fact_doc_builder->remove(docid);
    }
    _dimension_doc_manager->delete_dimension_doc(record.level_id, docid, record);

    if (record.op_id == 1U &&
        record.level_id != _dimension_doc_manager->get_fact_doc_level_id()) {
        // 只有当真正删除非fact doc时，才需要进行级联过滤
        // note: 级联过滤，没有必要在删除dimension doc之前进行
        //       无法避免检索时判断下DimensionDoc是否为空
        uint32_t num = cascade_filt();
        if (num != 0) {
            UNOTICE("[level:%u] [dimension_doc:%llu] deleted cascade [num:%u] fact_docs",
                        record.level_id, docid, num);
        }
    }
}

void DasIncBuilder::add_record(const das_inc_record_t& record) {
    // 重复插入视为覆盖操作，根据需要首先删除
    // 为了避免打印删除失败的WARNING log，这里不直接调用delete_record()
    if (FLAGS_add_overwrite) {
        // TODO(wangguangyuan) : 这段代码与删除的代码重复，需要重构
        // get docid from the das other info
        DocId docid;
        size_t pos = record.other.find('\t');
        // note: 'other' may only contains a docid
        if (pos == string::npos) {
            pos = record.other.length();
        }
        if (false == StringToUint64(record.other.substr(0, pos), &docid)) {
            // LOG中增加event_id，便于用户找到出错的event
            UWARNING("[\tlvl=FOLLOW\t] get docid fail for event_id[%u] opid:%u other:%s",
                        record.event_id,
                        record.op_id,
                        record.other.c_str());
            return;
        }
        // note：判断当前docid是否是重复插入，如果是再删除
        //       为了避免触发删除失败的log
        if (_repository_manager->get_doc_info(docid)) {
            // 当前doc为重复插入
            if (record.level_id == _dimension_doc_manager->get_fact_doc_level_id()) {
                // delete inverted index and forward index first
                _fact_doc_builder->remove(docid);
            }
            // delete the dimension doc second
            _dimension_doc_manager->delete_dimension_doc(record.level_id, docid, record);
        }
    }
    // 执行插入
    DimensionDoc * doc = _dimension_doc_manager->
        add_dimension_doc(record.level_id, record.other, record);
    if (doc == NULL) {
        UTRACE("add_dimension_doc fail for event_id[%u] opid:%u other:%s",
                    record.event_id,
                    record.op_id,
                    record.other.c_str());
        return;
    }
    // if the DimensionDoc is FactDoc, build index for the factdoc
    if (record.level_id == _dimension_doc_manager->get_fact_doc_level_id()) {
        FactDoc * fact_doc = dynamic_cast<FactDoc*>(doc);
        // build the forward index and inverted index
        _fact_doc_builder->build(fact_doc);
    } else {
        // 执行级联过滤，确保在add_dimension_doc之后调用
        uint32_t num = cascade_filt();
        if (num != 0) {
            UNOTICE("[level:%u] [dimension_doc:%llu] add/update cascade [num:%u] fact_docs",
                        record.level_id, doc->get_doc_id(), num);
        }
    }
}

void DasIncBuilder::process_one_record(const das_inc_record_t& record) {
    if (!_dimension_doc_manager->dimension_doc_exist(record.level_id)) {
        UTRACE("ignor the level_id:%u for event_id[%u]", record.level_id, record.event_id);
        return;
    }

    if (record.op_id == 2U) {
        // note: update is implemented as delete-first-and-add-second
        delete_record(record);
        add_record(record);
    } else if (record.op_id == 1U) {
        delete_record(record);
    } else if (record.op_id == 0U) {
        add_record(record);
    } else {
        UWARNING("[\tlvl=COUNT\top_id=%u\tevent_id=%u\t] unknown das op_id",
                    record.op_id, record.event_id);
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
