/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file dimension_doc_base_builder.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/26 16:18:44
 * @version $Revision$
 * @brief DimensionDoc基量构建类
 *
 **/

#ifndef  __DIMENSION_DOC_BASE_BUILDER_H_
#define  __DIMENSION_DOC_BASE_BUILDER_H_

#include <boost/shared_ptr.hpp>
#include <algorithm>
#include "unise/base.h"
#include "unise/dimension_doc.h"
#include "util/util.h"
#include "index/doc_base_builder.h"
#include "index/dimension_doc_manager.h"

namespace unise {

class DimensionDocBaseBuilder : public DocBaseBuilder {
public:
    DimensionDocBaseBuilder(const std::string &name,
            const DocFileInfo &doc_file_info,
            DimensionDocManager::dimension_t *dimension_doc,
            boost::shared_ptr<DimensionDocManager> &dimension_doc_manager);

    virtual ~DimensionDocBaseBuilder();

    /**
    * @brief 构建DimensionDoc
    * @return true 成功，false 失败
    */
    virtual bool build();

protected:
    DimensionDocManager::dimension_t *_dimension;        /**< DimensionDoc的family信息       */

    /**
    * @brief 从磁盘加载DimensionDoc
    * @return true 成功，false 失败
    */
    bool load_dimension_doc();

    /**
    * @brief 获取下一个doc
    * @return ture 成功，false 失败，has_next表示是否还有下一个doc
    * @note
    */
    bool get_next_doc(DimensionDoc **doc, bool *has_next) {
        std::string line;
        FileStatus status = get_next_line(line);
        if (OK != status) {
            *doc = NULL;
            *has_next = false;
            if (END == status) {
                return true;
            } else {
                return false;
            }
        }
        size_t pos = line.find('\t');
        if (pos != string::npos) {
            // get level id
            uint32_t level_id;
            if (!StringToUint(line.substr(0, pos), &level_id)) {
                level_id = ILLEGAL_LEVEL_ID;
                UWARNING("[\tlvl=FOLLOW\t] get level_id failed:%s", line.c_str());
            }
            // get event info
            event_info_t event_info;
            event_info.type = BASE_DATA;
            event_info.event_id = MAX_EVENT_ID;
            event_info.level_id = level_id;
            // set event info
            _dimension->factory->set_event_info(event_info);
            *doc = _dimension->factory->produce(line.substr(pos + 1));
            // 因为DimensionDocManager拿不到AnnotationManager，所以，不对DimensionDoc
            // 的annotaiton判断是否需要存储，仅仅排序
            if (*doc) {
                sort((*doc)->annotations.begin(), (*doc)->annotations.end());
            }
        } else {
            *doc = NULL;
        }
        *has_next = true;
        return true;
    }

private:
    boost::shared_ptr<DimensionDocManager> _dimension_doc_manager;        /**< DimensionDocManager       */
};

}

#endif  //__DIMENSION_DOC_BASE_BUILDER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
