// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#ifndef  UNISE_DEMO_DOC_H
#define  UNISE_DEMO_DOC_H

#include <string>
#include "json/json.h"
#include "unise/fact_doc.h"
#include "unise/util.h"

#include <boost/shared_ptr.hpp>

namespace unise {
#pragma pack(push, 1)

class ArticleDoc : public FactDoc {
public:
    ArticleDoc():_reader(new Json::Reader(Json::Features::strictMode())) {}
    bool init(const std::string& line) {
        std::vector<std::string> article_infos;
        string_split(line, "\t", &article_infos);
        if (article_infos.size() != 2) {
            UWARNING("invalid data format");
            return false;
        }
        if (_reader->parse(article_infos.at(1), _json_value, false) == false) {
            UWARNING("parse json failed");
            return false;
        }
        StringToUint64(article_infos.at(0), &this->_resource_id);
        StringToInt64(_json_value["area_id"].asString(), &this->_area_id);
        StringToInt64(_json_value["city_id"].asString(), &this->_city_id);
        this->_title = _json_value["title"].asString();
        this->_source = _json_value["source"].asString();
        this->_image_url = _json_value["image_url"].asString();
        this->_content = _json_value["content"].asString();
        this->_na_redirect_url = _json_value["na_redirect_url"].asString();
        this->_wap_redirect_url = _json_value["wap_redirect_url"].asString();
        StringToInt(_json_value["score"].asString(), &this->_score);
        StringToUint(_json_value["publish_time"].asString(), &this->_publish_time);

        this->_category_id = _json_value["category_id"].asString();
        StringToInt64(_json_value["column_id"].asString(), &this->_column_id);
        this->_tags = _json_value["tags"].asString();

        return true;
    }

    virtual ~ArticleDoc() {}
    virtual DocId get_doc_id() const { return _resource_id; }
    std::string get_title() const {return _title;}
    std::string get_content() const {return _content;}
    virtual int32_t get_score() const { return _score; }
    uint32_t get_publish_time() const {return _publish_time;}
    int64_t get_city_id() const {return _city_id;}
    virtual std::string get_dimension_name() const { return "ArticleDoc"; }

public:
    uint64_t _resource_id;
    int64_t _area_id;
    int64_t _city_id;
    std::string _title;
    std::string _source;
    std::string _image_url;
    std::string _content;
    std::string _na_redirect_url;
    std::string _wap_redirect_url;
    int32_t _score;
    uint32_t _publish_time;

    std::string _category_id;
    int64_t _column_id;
    std::string _tags;

private:
    friend class boost::serialization::access;

    template <typename Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<FactDoc>(*this);
            ar & _resource_id;
            ar & _area_id;
            ar & _city_id;
            ar & _title;
            ar & _source;
            ar & _image_url;
            ar & _content;
            ar & _na_redirect_url;
            ar & _wap_redirect_url;
            ar & _score;
            ar & _publish_time;

            ar & _category_id;
            ar & _column_id;
            ar & _tags;
        }

private:
    boost::shared_ptr<Json::Reader> _reader;
    Json::Value _json_value;

};
#pragma pack(pop)
}

#endif  // UNISE_DEMO_DOC_H

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
