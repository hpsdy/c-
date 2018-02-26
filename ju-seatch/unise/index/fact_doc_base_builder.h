/***************************************************************************
 *
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/



/**
 * @file fact_doc_base_builder.h
 * @author huiquanchao(huiquanchao@baidu.com)
 * @date 2013/12/26 16:47:59
 * @version $Revision$
 * @brief FactDoc基量构建类
 *
 **/

#ifndef  __FAC_DOC_BASE_BUILDER_H_
#define  __FAC_DOC_BASE_BUILDER_H_

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include "index/dimension_doc_base_builder.h"
#include "index/repository_manager.h"
#include "index/annotation_manager.h"
#include "index/forward_index.h"
#include "index/fix_post_list.h"
#include "index/token_list.h"
#include "unise/fact_doc.h"
#include "index/token_hit.h"
#include "unise/base.h"
#include "isegment.h"

using google::protobuf::io::CodedInputStream;
using google::protobuf::io::CodedOutputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::FileInputStream;

namespace unise
{
// CodedInputStream can't solve input file lager than 2G
// note:单个token的倒排拉链假设不超过1G
// note:单个doc的正排假设不超过1G
const int read_limit_size = 2* 1024 * 1024 * 1024 - 1;
const int token_list_limit_size = 1024 * 1024 * 1024 / 12;

class FactDocBaseBuilder : public DimensionDocBaseBuilder
{
public:
    FactDocBaseBuilder(const std::string &name,
            const DocFileInfo &doc_file_info,
            DimensionDocManager::dimension_t *dimension,
            boost::shared_ptr<DimensionDocManager> &dimension_doc_manager,
            boost::shared_ptr<RepositoryManager> &repository_manager);

    virtual ~FactDocBaseBuilder();

    /**
    * @brief 构建FactDoc，并且构建FactDoc的正排和倒排索引
    * @return ture 成功，false 失败
    */
    virtual bool build();
private:
    inline bool load_forward_index(const std::string& path)
    {
        UNOTICE("begin load forward_index:%s", path.c_str());
        int fd = open(path.c_str(), O_RDONLY);
        if (fd == -1) {
            UFATAL("open base_forward_index failed:%s", path.c_str());
            return false;
        }
        ZeroCopyInputStream * raw_input = new FileInputStream(fd);
        bool ret = load_forward_index_internal(raw_input);
        delete raw_input;
        close(fd);
        if (!ret) {
            UFATAL("load base inverted index failed");
        }
        return ret;
    }

    inline bool load_forward_index_internal(ZeroCopyInputStream * raw_input)
    {
        DocId docid;
        int32_t score;
        uint32_t length;
        uint8_t filter_flag;
        uint32_t magic_number = 0;
        int cnt = 0;

        boost::scoped_ptr<CodedInputStream>  coded_input(new CodedInputStream(raw_input));
        coded_input->SetTotalBytesLimit(read_limit_size, -1);
        if (!coded_input->ReadLittleEndian32(&magic_number) || magic_number != FORWARD_MAGIC) {
            UFATAL("start forward_magic illegal:%u", magic_number);
            return false;
        }

        if (!coded_input->ReadVarint64(&docid)) {
            UFATAL("read docid failed");
            return false;
        }

        while (docid != ILLEGAL_DOCID) {
            if (!coded_input->ReadVarint32(reinterpret_cast<uint32_t*>(&score))) {
                UFATAL("read score failed");
                return false;
            }
            if (!coded_input->ReadRaw(&filter_flag, 1)) {
                UFATAL("read filter_flag failed");
                return false;
            }
            if (!coded_input->ReadVarint32(&length)) {
                UFATAL("read length failed");
                return false;
            }
            uint8_t * buffer = new uint8_t[length];
            if (!coded_input->ReadRaw(buffer, length)) {
                UFATAL("read buffer length %u failed", length);
                delete []buffer;
                return false;
            }
            doc_info_t * doc_info = new doc_info_t();
            doc_info->docid = docid;
            doc_info->score = score;
            doc_info->filter_flag = filter_flag;
            // warning: fact_doc需要从hash中重新查找
            doc_info->fact_doc = _repository_manager->
                get_dimension_doc_manager()->get_fact_doc(docid);
            doc_info->forward_index = _repository_manager->create_forward_index();
            doc_info->forward_index->load_dump_data(buffer, length);
            _repository_manager->add_doc_info(doc_info);

            if (++cnt % 1000000 == 0) {
                UNOTICE("load %d forward_index", cnt);
            }
            coded_input.reset();
            coded_input.reset(new CodedInputStream(raw_input));
            coded_input->SetTotalBytesLimit(read_limit_size, -1);

            if (!coded_input->ReadVarint64(&docid)) {
                UFATAL("read docid failed");
                return false;
            }
        }
        if (!coded_input->ReadLittleEndian32(&magic_number) || magic_number != FORWARD_MAGIC) {
            UFATAL("end forward_magic illegal:%u", magic_number);
            return false;
        }
        UNOTICE("finish load %d forward_index", cnt);
        return true;
    }

    inline bool load_inverted_index(const std::string& path)
    {
        bool ret = false;
        UNOTICE("begin load inverted_index:%s", path.c_str());
        int fd = open(path.c_str(), O_RDONLY);
        if (fd == -1) {
            UFATAL("open base_inverted_index failed:%s", path.c_str());
            return false;
        }
        ZeroCopyInputStream * raw_input = new FileInputStream(fd);
        ret = load_inverted_index_internal(raw_input);
        delete raw_input;
        close(fd);
        if (!ret) {
            UFATAL("load base inverted index failed");
        }
        return ret;
    }

    inline bool load_inverted_index_internal(ZeroCopyInputStream * raw_input)
    {
        uint32_t magic_number;
        int cnt = 0;
        TokenId token_id;
        TokenId last_token_id = 0;
        doc_hit_t doc_hit;
        std::vector<doc_hit_t> doc_hit_list;

        boost::scoped_ptr<CodedInputStream>  coded_input(new CodedInputStream(raw_input));
        coded_input->SetTotalBytesLimit(read_limit_size, -1);

        if (!coded_input->ReadLittleEndian32(&magic_number) || magic_number != INVERTED_MAGIC) {
            UFATAL("start inverted_magic illegal:%u", magic_number);
            return false;
        }
        if (!coded_input->ReadVarint64(&token_id)) {
            UFATAL("read new tokenid failed");
            return false;
        }
        while (token_id != ILLEGAL_TOKEN_ID) {
            token_id += last_token_id;
            last_token_id = token_id;
            if (!coded_input->ReadVarint64(&doc_hit.docid)) {
                UFATAL("read docid failed");
                return false;
            }
            while (doc_hit.docid != ILLEGAL_DOCID) {
                if (!coded_input->ReadVarint32(reinterpret_cast<uint32_t*>(&doc_hit.score))) {
                    UFATAL("read score failed");
                    return false;
                }
                doc_hit_list.push_back(doc_hit);
                if (!coded_input->ReadVarint64(&doc_hit.docid)) {
                    UFATAL("read docid failed");
                    return false;
                }
            }
            TokenList *token_list = new TokenList(token_id,
                        new FixPostList(token_id, &doc_hit_list));
            // 会自动swap，不需要再进行doc_hit_list.clear()
            _repository_manager->set_token_list(token_list);
            if (++cnt % 1000000 == 0) {
                UNOTICE("load %d inverted_list", cnt);
            }

            coded_input.reset();
            coded_input.reset(new CodedInputStream(raw_input));
            coded_input->SetTotalBytesLimit(read_limit_size, -1);
            if (!coded_input->ReadVarint64(&token_id)) {
                UFATAL("read new tokenid failed");
                return false;
            }
        }
        if (!coded_input->ReadLittleEndian32(&magic_number) || magic_number != INVERTED_MAGIC) {
            UFATAL("end inverted_magic illegal:%u", magic_number);
            return false;
        }
        UNOTICE("finish load %d inverted_index", cnt);
        return true;
    }

   /**
    * @brief 获取Doc的TokenHits
    */
    void get_token_hits(FactDoc * doc, const doc_info_t& doc_info, std::vector<TokenHit> *token_hits);

    /**
    * @brief 批量构建所有Doc的倒排索引
    * @return ture 成功，false 失败
    */
    bool batch_build_inverted_index();

    /**
    * @brief 加载磁盘数据到d2f_maps结构
    * @return ture 成功，false 失败
    */
    bool load_d2f_maps();

    /**
     * @brief d2f_maps结构dump到磁盘
     * @return ture 成功，false 失败
     */
    bool dump_d2f_maps();

    bool build_dimension_doc();

private:
    boost::shared_ptr<RepositoryManager> &_repository_manager;        /**< RepositoryManager       */
    AnnotationManager * _annotation_manager;
    DimensionDocManager * _dimension_doc_manager;
    std::vector<TokenHit> _token_hit_list;         /**< 存储所有的TokenHit       */
    scw_worddict_t * _dict;
    scw_out_t * _handler;

    std::string _forward_index_path;              ///< dump正排索引数据的位置
    std::string _inverted_index_path;             ///< dump倒排索引数据的位置
    std::string _d2f_maps_path;                   ///< dump级联数据的位置
};

}

#endif  //__FAC_DOC_BASE_BUILDER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 expandtab: */
