/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file doc_base_builder.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/26 15:38:12
 * @version $Revision$
 * @brief Doc基量构建的基类
 *
 **/

#ifndef  __DOCBASEBUILDER_H_
#define  __DOCBASEBUILDER_H_

#include "unise/thread.h"
#include <iostream>
#include <fstream>
#include <string>

namespace unise
{

struct DocFileInfo {
    std::string file_name;                /**< 文件名       */
    ssize_t offset;                       /**< 开始偏移     */
    size_t len;                           /**< 长度         */
    // 下面两个参数，只有FactDoc的builder需要使用
    std::string dump_forward_index_path;  /**< dump正排文件 */
    std::string dump_inverted_index_path; /**< dump倒排文件 */
    std::string dump_d2f_maps_path;       /**< dump级联数据 */
};

class DocBaseBuilder : public Thread
{
public:
    DocBaseBuilder(const std::string &name,
            const DocFileInfo &doc_file_info);

    virtual ~DocBaseBuilder();

    /**
    * @brief 构建Doc
    * @return ture 成功，false 失败
    */
    virtual bool build() = 0;

    /**
    * @brief 线程工作函数
    */
    virtual int run() {
        _status = build();
        return _status ? 0 : -1;
    }

    /**
     * @brief 查询是否构建成功
     */
    virtual bool status()
    {
        return _status;
    }

    /**
    * @brief 获取文件名
    */
    const std::string& get_file_name() {
        return _doc_file_info.file_name;
    }

protected:
    enum FileStatus {
        OK,
        ERROR,
        END
    };

    /**
    * @brief 获取文件中下一行
    */
    FileStatus get_next_line(std::string &line,
            char delimiter = '\n') {
        /*{{{*/
        if (_fin.fail()) {
            return ERROR;
        }
        if (getline(_fin, line, delimiter)) {
            if (_fin.tellg() > _end_offset) {
                return END;
            }
            if (_fin.fail()) {
                return ERROR;
            } else {
                return OK;
            }
        }
        return END;
    }/*}}}*/

private:
    DocFileInfo _doc_file_info;       /**< 文件相关信息  */
    std::ifstream _fin;               /**< 输入文件流    */
    ssize_t _end_offset;              /**< 结束偏移      */
    bool _status;                     ///< 是否构建成功
};

}

#endif  //__DOCBASEBUILDER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
