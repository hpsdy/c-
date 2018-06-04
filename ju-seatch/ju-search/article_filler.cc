// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#include "article_filler.h"
#include "unise/factory.h"

namespace unise {
void ArticleFiller::fill_search_result(MatchedDoc * result,
        SearchResult* search_result) const {
    const ArticleDoc* doc = dynamic_cast<const ArticleDoc*>(get_dimension_doc(
                            "ArticleDoc",
                            result->get_doc_id()));

    if (doc == NULL) {
        return;
    } else {
        Snippet * snippet = search_result->add_snippets();
        snippet->set_key("id");
        snippet->set_value(Uint64ToString(doc->_resource_id));

        snippet = search_result->add_snippets();
        snippet->set_key("source");
        snippet->set_value(doc->_source);

        snippet = search_result->add_snippets();
        snippet->set_key("image_url");
        snippet->set_value(doc->_image_url);

        snippet = search_result->add_snippets();
        snippet->set_key("na_redirect_url");
        snippet->set_value(doc->_na_redirect_url);

        snippet = search_result->add_snippets();
        snippet->set_key("wap_redirect_url");
        snippet->set_value(doc->_wap_redirect_url);

        snippet = search_result->add_snippets();
        snippet->set_key("publish_time");
        snippet->set_value(UintToString(doc->_publish_time));

        snippet = search_result->add_snippets();
        snippet->set_key("category_id");
        snippet->set_value(doc->_category_id);

        snippet = search_result->add_snippets();
        snippet->set_key("column_id");
        snippet->set_value(Int64ToString(doc->_column_id));

        const FactDoc & fact_doc = result->get_fact_doc();
        for (size_t k = 0; k < fact_doc.annotations.size(); k++) {
            AnnotationId id = fact_doc.annotations.at(k).id;
            if (id == 3 || id == 6) {
                std::string doc_id_annotation_id = StringPrintf("%u_%u",
                       result->get_doc_id(),
                       id);
                std::string pos_lens_str;
                bool need_hilight = get_string_experiment_value(*_request,
                        doc_id_annotation_id, &pos_lens_str);

                string annotation_value = fact_doc.annotations.at(k).text_value;
                size_t hilight_first_begin = 0;
                size_t hilight_first_end = 0;
                size_t hilight_second_begin = 0;
                size_t hilight_second_end = 0;
                std::vector<std::string> pos_lens_vec;

                char* raw_query_hilight = NULL;
                uint32_t pos = 0;
                uint32_t len = 0;
                if (need_hilight) {
                    const char* raw_query = _request->raw_query().c_str();
                    raw_query_hilight = strstr(annotation_value.c_str(), raw_query);

                    if (raw_query_hilight != NULL) {
                        pos = raw_query_hilight - annotation_value.c_str();
                        len = _request->raw_query().size();
                        annotation_value.insert(pos + len, "</em>");
                        annotation_value.insert(pos, "<em>");
                    } else {
                        string_split(pos_lens_str, ";", &pos_lens_vec);
                        for (size_t i = 0; i < pos_lens_vec.size(); i++) {
                            std::string pos_len_str = pos_lens_vec.at(i);
                            std::vector<std::string> pos_len_vec;
                            string_split(pos_len_str, ":", &pos_len_vec);
                            if (pos_len_vec.size() == 2) {
                                StringToUint(pos_len_vec.at(0), &pos);
                                StringToUint(pos_len_vec.at(1), &len);
                                annotation_value.insert(pos + len, "</em>");
                                annotation_value.insert(pos, "<em>");
                                if (i == 0) {
                                    hilight_second_begin = pos;
                                    hilight_second_end = pos + len + 9;
                                } else {
                                    hilight_first_begin = pos;
                                    hilight_first_end = pos + len + 9;
                                    hilight_second_begin += 9;
                                    hilight_second_end += 9;
                                }
                            }
                        }
                    }
                }
                if (id == 3) {
                    snippet = search_result->add_snippets();
                    snippet->set_key("title");
                    snippet->set_value(annotation_value);

                } else {
                    const char* annotation_value_str = annotation_value.c_str();
                    const char* hilight_begin_str = NULL;
                    const char* hilight_end_str = NULL;

                    if (pos == 0) {
                        hilight_begin_str = annotation_value_str;
                        hilight_end_str = uln_utf8_next_n(annotation_value_str, 10);
                    } else if (raw_query_hilight != NULL) {
                        hilight_begin_str = annotation_value_str + pos;
                        hilight_end_str = hilight_begin_str + len + 9;
                    } else if (pos_lens_vec.size() == 1) {
                        hilight_begin_str = annotation_value_str + hilight_second_begin;
                        hilight_end_str = annotation_value_str + hilight_second_end;
                    } else {
                        hilight_begin_str = annotation_value_str + hilight_first_begin;
                        if (hilight_second_begin - hilight_first_end > 90) {
                            hilight_end_str = annotation_value_str + hilight_first_end;
                        } else {
                            hilight_end_str = annotation_value_str + hilight_second_end;
                        }
                    }
                    hilight_end_str = uln_utf8_next_n(hilight_end_str, 30);
                    if (annotation_value.size() - hilight_second_end < 30) {
                        hilight_begin_str = uln_utf8_prev_n(hilight_begin_str, 15, annotation_value_str);
                    } else {
                        hilight_begin_str = uln_utf8_prev_n(hilight_begin_str, 10, annotation_value_str);
                    }
                    size_t hilight_begin_pos = hilight_begin_str - annotation_value_str;
                    size_t hilight_end_pos = hilight_end_str - annotation_value_str;
                    snippet = search_result->add_snippets();
                    snippet->set_key("content");
                    if (hilight_begin_pos >= 0 && hilight_end_pos != std::string::npos) {
                        annotation_value = annotation_value.substr(hilight_begin_pos, hilight_end_pos - hilight_begin_pos);
                        string_trim(&annotation_value, ".;,?");
                        snippet->set_value(annotation_value);
                    } else {
                        snippet->set_value("");
                    }
                }
            }
        }
    }
    // get the extension
    // just to show the usage of extension-of-protobuf
    // UNOTICE("filler by article test_id[%d] docid[%llu]",
           // search_result->GetExtension(unise::test_id),
           // result->get_doc_id());
}

void ArticleFiller::end_for_search(PluginResponse * plugin_response) {
    // just to show the usage of extension-of-protobuf
    plugin_response->set_name(get_name());
    plugin_response->set_enable(true);
    plugin_response->set_information("plugin time " + get_date(get_timestamp()));
    // plugin_response->SetExtension(unise::timestamp, get_timestamp());
}

REGISTER_RESULT_FILLER(ArticleFiller);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
