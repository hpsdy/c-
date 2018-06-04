/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file doc_base_builder.cc
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/26 15:50:14
 * @version $Revision$
 * @brief Doc基量构建的基类的实现
 *
 **/

#include "doc_base_builder.h"

namespace unise
{

DocBaseBuilder::DocBaseBuilder(const std::string &name,
        const DocFileInfo &doc_file_info) :
    Thread(name),
    _doc_file_info(doc_file_info),
    _fin(doc_file_info.file_name.c_str(), std::ios::in),
    _status(true)
{
    _fin.seekg(doc_file_info.offset);
    _end_offset = doc_file_info.offset + doc_file_info.len;
}

DocBaseBuilder::~DocBaseBuilder()
{
    _fin.close();
}

};

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
