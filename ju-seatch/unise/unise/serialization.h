// Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved.
// Author: liuyongtao@baidu.com (Yongtao Liu).

#ifndef  CS_VS_CROSS_UNISE_SRC_UNISE_SERIALIZE_H
#define  CS_VS_CROSS_UNISE_SRC_UNISE_SERIALIZE_H

#include <fstream>
#include "unise/base.h"
#include "unise/dimension_doc.h"

namespace unise {

/**
 * @breaf 序列化函数，获取所有的DimensionDoc *
 *
 * @param [in] : fname 存储boost序列化数据的文件名
 * @param [out] : 存储所有的DimensionDoc * 容器
 * @return bool 
 * @retval 返回是否序列化成功，如果成功，返回true；否则false。
 * @notice 用户定义的数据类型boost库不支持序列化时，请不要调用该方法
**/
template <typename T>
bool serialize(const std::vector<const DimensionDoc *> & dimension_docs, const std::string& fname) {
    size_t doc_num = dimension_docs.size();
    if (doc_num == 0) {
        UFATAL("the number of DimensionDoc is 0.");
        return false;
    }
    std::vector<const T *> docs;
    const T * doc = NULL;
    for (size_t i = 0; i < doc_num; i++) {
        doc = dynamic_cast<const T *>(dimension_docs[i]);
        if (!doc) {
            UFATAL("Failed to get doc.");
            return false;
        }
        docs.push_back(doc);
        doc = NULL;
    }
    try {
        std::ofstream ofs(fname.c_str());
        if (!ofs.good()) {
            UFATAL("Failed to load file: %s.", fname.c_str());
            return false;
        }
        boost::archive::binary_oarchive oa(ofs);
        oa & docs;
    } catch (std::bad_alloc& e) {
        UFATAL("Failed to serialize, err_msg:%s", e.what());
        return false;
    } catch (boost::archive::archive_exception& e) {
        UFATAL("Failed to serialize, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to serialize");
        return false;
    }
    UNOTICE("Finish dump %u docs.", docs.size());
    return true;
}

/**
 * @breaf 反序列化函数，获取所有的DimensionDoc *
 *
 * @param [in] : fname 存储boost序列化数据的文件名
 * @param [out] : 存储所有的DimensionDoc * 容器
 * @return bool 
 * @retval 返回是否反序列化成功，如果成功，返回true；否则false。
 * @notice 用户定义的数据类型boost库不支持序列化时，请不要调用该方法
**/
template <typename T>
bool deserialize(std::vector<DimensionDoc *> * dimension_docs, const std::string& fname) {
    std::vector<T *> docs;
    try {
        std::ifstream ifs(fname.c_str());
        if (!ifs.good()) {
            UFATAL("Failed to load file: %s.", fname.c_str());
            return false;
        }
        boost::archive::binary_iarchive ia(ifs);
        ia & docs;
    } catch (std::bad_alloc& e) {
        UFATAL("Failed to deserialize, err_msg:%s", e.what());
        return false;
    } catch (boost::archive::archive_exception& e) {
        UFATAL("Failed to deserialize, err_msg:%s", e.what());
        return false;
    } catch (...) {
        UFATAL("Failed to deserialize");
        return false;
    }
    size_t doc_num = docs.size();
    if (doc_num == 0) {
        UFATAL("Failed to load file: %s.", fname.c_str());
        return false;
    }
    DimensionDoc * doc = NULL;
    for (size_t i = 0; i < doc_num; i++) {
        doc = dynamic_cast<DimensionDoc*>(docs[i]);
        if (!doc) {
            UFATAL("Failed to load file: %s.", fname.c_str());
            return false;
        }
        dimension_docs->push_back(doc);
        doc = NULL;
    }
    return true;
}

}

#endif  //CS_VS_CROSS_UNISE_SRC_UNISE_SERIALIZE_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
