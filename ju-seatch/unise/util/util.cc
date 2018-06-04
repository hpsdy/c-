// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)

#include "unise/util.h"

#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <wchar.h>
#include <wctype.h>
#include <endian.h>
#include <uln_sign_murmur.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <iostream>
#include <sstream>
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/split.hpp"
#include "json/json.h"

DEFINE_string(thirdparty_path, "../thirdparty", "the thirdparty relative path to unise");

using std::string;
using std::vector;
using std::pair;

namespace unise {

void string_trim(string * str, const string & garbage) {
    if (str == NULL || str->size() == 0) {
        return;
    }
    size_t start = str->find_first_not_of(garbage);
    size_t end = str->find_last_not_of(garbage);
    if (start != string::npos && end != string::npos) {
        str->assign(str->substr(start, end + 1 - start));
    } else {
        str->assign("");
    }
}

void string_split(const string & str,
                  const string & sep,
                  vector<string> * strs,
                  bool ignore_empty) {
    if (strs == NULL) {
        return;
    }
    size_t start = 0;
    size_t found = str.find_first_of(sep, start);
    while (string::npos != found) {
        string tmp = str.substr(start, found - start);
        if (!ignore_empty || tmp != "") {
            strs->push_back(tmp);
        }
        start = found + 1;
        found = str.find_first_of(sep, start);
    }
    string tmp = str.substr(start, str.size() - start);
    if (!ignore_empty || tmp != "") {
        strs->push_back(tmp);
    }
}

void string_split(const string & str, const string & sep, vector<string> * strs) {
    string_split(str, sep, strs, true);
}

class StringToIntTraits
{
public:
    typedef std::string string_type;
    typedef int value_type;
    static const int kBase = 10;
    static inline value_type convert_func(const string_type::value_type* str,
            string_type::value_type** endptr) {
        return strtoimax(str, endptr, kBase);
    }
    static inline bool valid_func(const string_type& str) {
        return !str.empty() && !isspace(str[0]);
    }
};

class StringToUintTraits
{
public:
    typedef std::string string_type;
    typedef uint32_t value_type;
    static const int kBase = 10;
    static inline value_type convert_func(const string_type::value_type* str,
            string_type::value_type** endptr) {
        return strtoumax(str, endptr, kBase);
    }
    static inline bool valid_func(const string_type& str) {
        return !str.empty() && !isspace(str[0]);
    }
};

class StringToUint64Traits
{
public:
    typedef std::string string_type;
    typedef uint64_t value_type;
    static const int kBase = 10;
    static inline value_type convert_func(const string_type::value_type* str,
            string_type::value_type** endptr) {
        return strtoull(str, endptr, kBase);
    }
    static inline bool valid_func(const string_type& str) {
        return !str.empty() && !isspace(str[0]);
    }
};

class StringToInt64Traits
{
public:
    typedef std::string string_type;
    typedef int64_t value_type;
    static const int kBase = 10;
    static inline value_type convert_func(const string_type::value_type* str,
            string_type::value_type** endptr) {
        return strtoll(str, endptr, kBase);
    }
    static inline bool valid_func(const string_type& str) {
        return !str.empty() && !isspace(str[0]);
    }
};

// For the HexString variants, use the unsigned variants like strtoul for
// convert_func so that input like "0x80000000" doesn't result in an overflow.

class HexStringToIntTraits
{
public:
    typedef std::string string_type;
    typedef int value_type;
    static const int kBase = 16;
    static inline value_type convert_func(const string_type::value_type* str,
            string_type::value_type** endptr) {
        return strtoumax(str, endptr, kBase);
    }
    static inline bool valid_func(const string_type& str) {
        return !str.empty() && !isspace(str[0]);
    }
};

class HexStringToInt64Traits
{
public:
    typedef std::string string_type;
    typedef int64_t value_type;
    static const int kBase = 16;
    static inline value_type convert_func(const string_type::value_type* str,
            string_type::value_type** endptr) {
        return strtoul(str, endptr, kBase);
    }
    static inline bool valid_func(const string_type& str) {
        return !str.empty() && !isspace(str[0]);
    }
};

bool StringToBool(const std::string& input, bool* output)
{
    const char* kTrue[] = { "1", "t", "true", "y", "yes" };
    const char* kFalse[] = { "0", "f", "false", "n", "no" };
    for (size_t i = 0; i < sizeof(kTrue) / sizeof(*kTrue); ++i) {
        if (strcasecmp(input.c_str(), kTrue[i]) == 0) {
            *output = true;
            return true;
        } else if (strcasecmp(input.c_str(), kFalse[i]) == 0) {
            *output = false;
            return true;
        }
    }
    return false;   // didn't match a legal input
}

bool StringToInt(const std::string& input, int* output)
{
    return StringToNumber<StringToIntTraits>(input, output);
}

bool StringToUint(const std::string& input, uint32_t* output)
{
    return StringToNumber<StringToUintTraits>(input, output);
}

bool StringToUint64(const std::string& input, uint64_t* output)
{
    return StringToNumber<StringToUint64Traits>(input, output);
}

bool StringToInt64(const std::string& input, int64_t* output)
{
    return StringToNumber<StringToInt64Traits>(input, output);
}

bool HexStringToInt(const std::string& input, int* output)
{
    return StringToNumber<HexStringToIntTraits>(input, output);
}

bool SizeStringToUint64(const std::string& input_string, uint64_t* output)
{
    std::string memory_size = input_string;
    int len = memory_size.size();
    char last_char = memory_size[len - 1];
    uint64_t times = 0;
    uint64_t msize = 0;
    switch (last_char) {
        case 'g':
        case 'G':
            times = 1024 * 1024 * 1024;
            memory_size.erase(memory_size.end() - 1);
            break;
        case 'm':
        case 'M':
            times = 1024 * 1024;
            memory_size.erase(memory_size.end() - 1);
            break;
        case 'k':
        case 'K':
            times = 1024;
            memory_size.erase(memory_size.end() - 1);
            break;
        default:
            break;
    }
    bool ret = StringToUint64(memory_size, &msize);
    if (!ret) { return false; }
    msize = msize * times;
    *output = msize;
    return true;
}

bool HexStringToInt64(const std::string& input, int64_t* output)
{
    return StringToNumber<HexStringToInt64Traits>(input, output);
}

bool TrimString(const std::wstring& input,
        const wchar_t trim_chars[],
        std::wstring* output)
{
    return TrimStringT(input, trim_chars, TRIM_ALL, output) != TRIM_NONE;
}

bool TrimString(const std::string& input,
    const char trim_chars[],
    std::string* output)
{
    return TrimStringT(input, trim_chars, TRIM_ALL, output) != TRIM_NONE;
}

bool IntToString(int64_t number, string * str)
{
    char buf[1024];
    sprintf(buf, "%ld", number);
    buf[1023] = '\0';
    str->assign(buf);
    return true;
}

std::string BoolToString(bool value)
{
    return value ? "true" : "false";
}

std::string IntToString(int value)
{
    return IntToStringT<std::string, int, unsigned int, true>::
           IntToString(value);
}
std::wstring IntToWString(int value)
{
    return IntToStringT<std::wstring, int, unsigned int, true>::
           IntToString(value);
}
std::string UintToString(unsigned int value)
{
    return IntToStringT<std::string, unsigned int, unsigned int, false>::
           IntToString(value);
}
std::wstring UintToWString(unsigned int value)
{
    return IntToStringT<std::wstring, unsigned int, unsigned int, false>::
           IntToString(value);
}
std::string Int64ToString(int64_t value)
{
    return IntToStringT<std::string, int64_t, uint64_t, true>::
           IntToString(value);
}
std::wstring Int64ToWString(int64_t value)
{
    return IntToStringT<std::wstring, int64_t, uint64_t, true>::
           IntToString(value);
}
std::string Uint64ToString(uint64_t value)
{
    return IntToStringT<std::string, uint64_t, uint64_t, false>::
           IntToString(value);
}
std::wstring Uint64ToWString(uint64_t value)
{
    return IntToStringT<std::wstring, uint64_t, uint64_t, false>::
           IntToString(value);
}

void StringAppendV(std::string* dst, const char* format, va_list ap)
{
    StringAppendVT(dst, format, ap);
}

void StringAppendV(std::wstring* dst, const wchar_t* format, va_list ap)
{
    StringAppendVT(dst, format, ap);
}

const std::string StringPrintf(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    std::string result;
    StringAppendV(&result, format, ap);
    va_end(ap);
    return result;
}

const std::wstring StringPrintf(const wchar_t* format, ...)
{
    va_list ap;
    va_start(ap, format);
    std::wstring result;
    StringAppendV(&result, format, ap);
    va_end(ap);
    return result;
}

void StringAppendF(std::string* dst, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    StringAppendVT(dst, format, ap);
    va_end(ap);
}

void StringAppendF(std::wstring* dst, const wchar_t* format, ...)
{
    va_list ap;
    va_start(ap, format);
    StringAppendVT(dst, format, ap);
    va_end(ap);
}

bool get_bool_experiment_value(const GeneralSearchRequest & request,
        const std::string & key,
        bool * value)
{
    if (request.has_search_params()) {
        for (int i = 0; i < request.search_params().experiments_size(); ++i) {
            const Experiment & e = request.search_params().experiments(i);
            if (e.key() == key) {
                if (e.has_value() == false || e.value() == "false") {
                    *value = false;
                    return true;
                } else {
                    *value = true;
                    return true;
                }
            }
        }
    }
    return false;
}

bool get_int_experiment_value(const GeneralSearchRequest & request,
        const std::string & key,
        int32_t * value)
{
    if (request.has_search_params()) {
        for (int i = 0; i < request.search_params().experiments_size(); ++i) {
            const Experiment & e = request.search_params().experiments(i);
            if (e.key() == key && e.has_value()) {
                int32_t tmp;
                if (StringToInt(e.value(), &tmp)) {
                    *value = tmp;
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

bool get_string_experiment_value(const GeneralSearchRequest & request,
        const std::string & key,
        std::string * value)
{
    if (request.has_search_params()) {
        for (int i = 0; i < request.search_params().experiments_size(); ++i) {
            const Experiment & e = request.search_params().experiments(i);
            if (e.key() == key && e.has_value()) {
                *value = e.value();
                return true;
            }
        }
    }
    return false;
}

bool get_host_name(std::string &hostname)
{/*{{{*/
    char host[128];
    if (0 != gethostname(host, sizeof(host))) {
        return false;
    }
    hostname.assign(host);
    return true;
}/*}}}*/

bool get_host_loc_from_baidu_domain(const std::string &hostname, 
    std::string &location)
{/*{{{*/
    std::vector<std::string> tokens;
    boost::split(tokens, hostname, boost::is_any_of("."), 
        boost::token_compress_on);
    if (tokens.size() <= 0) {
        return false;
    }
    size_t token_num = tokens.size();
    if (token_num > 2 && ((tokens[token_num - 2] == "baidu") &&
            (tokens[token_num - 1]) == "com")) {
        location.assign(tokens[token_num - 3]);
    } else {
        location.assign(tokens[tokens.size() - 1]);
    }
    return true;
}/*}}}*/

std::string get_file_path(const std::string& relative_to_thirdparty)
{
    if (FLAGS_thirdparty_path.at(FLAGS_thirdparty_path.length() - 1) != '/') {
      return FLAGS_thirdparty_path + "/" + relative_to_thirdparty;
    } else {
      return FLAGS_thirdparty_path + relative_to_thirdparty;
    }
}


TokenId get_token_id_from_query_node_value(const QueryNodeValue& value)
{
    TokenId token_id = ILLEGAL_TOKEN_ID;
    // check value first only realize text type
    if (false == value.has_text_value() || value.text_value() == "") {
        UNOTICE("not set text_value");
        return ILLEGAL_TOKEN_ID;
    }
    string token_string;
    if (value.has_annotation_name() && value.annotation_name() != "") {
        token_string.assign("ANNO" + TOKEN_SEP + value.annotation_name() + TOKEN_SEP +
                    value.text_value() + TOKEN_SEP);
    } else if (value.has_section_name() && value.section_name() != "") {
        token_string.assign("SECT" + TOKEN_SEP + value.section_name() + TOKEN_SEP +
                    value.text_value() + TOKEN_SEP);
    } else {
        UNOTICE("annotation_name and section_name both not set");
        return ILLEGAL_TOKEN_ID;
    }
    // murmur 只有参数为 NULL 时才出错，所以这里不处理返回值
    uln_sign_murmur2_64(token_string.data(), token_string.size(),
                reinterpret_cast<long long unsigned*>(&token_id));
    UDEBUG("get token value:%s token_id:%llu", token_string.c_str(), token_id);
    return token_id;
}

bool generate_annotations_from_field(const std::string& value,
                                          AnnotationId id,
                                          AnnotationType type,
                                          std::vector<Annotation> * annotations)
{
    Annotation anno;
    anno.id = id;
    if (type == TEXT) {
        anno.text_value.assign(value);
        annotations->push_back(anno);
        return true;
    } else if (type == NUMBER) {
        if (false == StringToInt64(value, &anno.number_value)) {
            UNOTICE("annotation id [%u] has illegal number_value:%s",
                     static_cast<uint32_t>(id), value.c_str());
            return false;
        }
        annotations->push_back(anno);
        return true;
    } else {
        UNOTICE("not support annotation type [%u]", type);
        return false;
    }
}

// @note 暂时只支持text类型的value
bool get_json_values_by_key(const Json::Value& root_value,
                         const std::string& pattern,
                         std::vector<string> * value)
{
    UDEBUG("get value from pattern:%s", pattern.c_str());
    size_t cur = 0;
    if (root_value.empty()) {
        UDEBUG("root_value empty");
        return false;
    }
    if (pattern.length() == 0) {
        if (root_value.isString()) {
            value->push_back(root_value.asString());
            UDEBUG("find value:%s", root_value.asString().c_str());
            return true;
        } else {
            UDEBUG("not find string value");
            return false;
        }
    }
    if (pattern.at(cur) == '.') {
        size_t start = ++cur;
        // find member value start
        while (cur < pattern.length() &&
                    pattern.at(cur) != '.' &&
                    pattern.at(cur) != '@') {
            ++cur;
        }
        std::string name(pattern.substr(start, cur - start));
        UDEBUG("find object name:%s", name.c_str());
        if (root_value.isMember(name)) {
            Json::Value default_value;
            return get_json_values_by_key(root_value.get(name, default_value),
                        pattern.substr(cur),
                        value);
        } else {
            return false;
        }
    } else if (pattern.at(cur) == '@') {
        size_t start = ++cur;
        // find array start
        while (cur < pattern.length() &&
                    pattern.at(cur) != '.' &&
                    pattern.at(cur) != '@') {
            ++cur;
        }
        std::string name(pattern.substr(start, cur - start));
        UDEBUG("find array name:%s", name.c_str());
        if (root_value.isMember(name)) {
            uint32_t i = 0;
            Json::Value default_value;
            Json::Value array_value = root_value.get(name, default_value);
            if (array_value.empty()) {
                return false;
            }
            while (array_value.isValidIndex(i)) {
                get_json_values_by_key(array_value.get(i, default_value),
                                       pattern.substr(cur),
                                       value);
                ++i;
            }
            return true;
        } else {
            return false;
        }
    }
    return true;
}

bool generate_annotations_from_field(const std::string& field,
                                    const IndexFieldFormat& format,
                                    std::vector<Annotation> * annotations)
{
    if (format.type() == KV && format.has_key_value_format()) {
        return generate_annotations_from_field(field,
                                           format.key_value_format().annotation_id(),
                                           format.key_value_format().annotation_type(),
                                           annotations);
    } else if (format.type() == JSON && format.json_formats_size() != 0) {
        Json::Reader reader;
        Json::Value json_value;
        if (false == reader.parse(field, json_value, false)) {
            UTRACE("parse json failed");
            return false;
        }
        for (int i = 0; i < format.json_formats_size(); ++i) {
            std::vector<std::string> values;
            if (false == get_json_values_by_key(json_value,
                                                format.json_formats(i).key_pattern(),
                                                &values)) {
                UTRACE("not find pattern:%s", format.json_formats(i).key_pattern().c_str());
                // 没有发现该value，忽略
                continue;
            }
            // 使用逗号，把数组类型的json value拼起来
            std::string text_value;
            for (size_t j = 0; j < values.size(); ++j) {
                if (j != 0) {
                    text_value.append(",");
                }
                text_value.append(values.at(j));
            }
            // 发现value，但是建索引失败，那么需要放弃这个doc
            if (false == generate_annotations_from_field(
                            text_value,
                            format.json_formats(i).annotation_id(),
                            format.json_formats(i).annotation_type(),
                            annotations)) {
                UTRACE("generate anno id [%u] failed",
                            format.json_formats(i).annotation_id());
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

/// @brief 获取增量记录的eventid
uint64_t get_event_id(const std::string &line) {/*{{{*/
    uint64_t event_id = 0;
    std::istringstream in;
    in.str(line);
    if(!(in >> event_id)) {
        UNOTICE("Invalid das inc record (has no event id), content:%s",
                line.c_str());
    }
    return event_id;
}/*}}}*/

int32_t get_timestamp() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec;
}

std::string get_date(int32_t timestamp) {
    struct tm t;
    time_t ts = timestamp;
    localtime_r(&ts, &t);
    char buf[64];
    snprintf(buf, 64, "%04d-%02d-%02d %02d:%02d:%02d",
                t.tm_year+1900,
                t.tm_mon+1,
                t.tm_mday,
                t.tm_hour,
                t.tm_min,
                t.tm_sec);
    std::string date(buf);
    return date;
}

int base64_encode(const uint8_t * in, int len, uint8_t * out, int size) {
    GOOGLE_DCHECK(in);
    GOOGLE_DCHECK(out);
    int ret = 0;
    BIO * bio = NULL;
    BIO * b64 = NULL;
    BUF_MEM * bptr = NULL;

    do {
        // TODO:add check here
        b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        bio = BIO_new(BIO_s_mem());
        bio = BIO_push(b64, bio);

        ret = BIO_write(bio, in, len);
        if (ret != len) {
            break;
        }
        ret = BIO_flush(bio);
        if (ret != 1) {
            break;
        }
        BIO_get_mem_ptr(bio, &bptr);
        if (size >= bptr->length) {
            // 目标空间足够大
            memcpy(out, bptr->data, bptr->length);
            ret = bptr->length;
        } else {
            // 目标空间不够
            ret = -1;
        }
    } while (0);
    if (bio != NULL) {
        BIO_free_all(bio);
    }
    return ret;
}

int base64_decode(uint8_t * in, int len, uint8_t * out, int size) {
    GOOGLE_DCHECK(in);
    GOOGLE_DCHECK(out);
    BIO * bio = NULL;
    BIO * b64 = NULL;
    int ret = -1;
    do {
        b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        bio = BIO_new_mem_buf(in, len);
        bio = BIO_push(b64, bio);
        ret = BIO_read(bio, out, size);
    } while (0);

    if (bio != NULL) {
        BIO_free_all(bio);
    }

    if (ret >= 0 && ret <= size) {
        return ret;
    } else {
        // BIO read error OR buffer not-enough
        return -1;
    }
}
string process_escape_characters(const string& str) {
    if (str == "") {
        return str;
    }
    size_t start = 0;
    const char *ptr = str.c_str();
    string converted_str = "";
    // 没有转义字符
    size_t found = str.find_first_of("\\", start);
    if (string::npos == found) {
        return str; 
    }
    // 可能有转义字符
    while (string::npos != found) {
        // 拷贝不需要处理的子串
        string tmp = str.substr(start, found - start);
        converted_str += tmp;
        // 英文的斜杠或者其他的转义
        if (*(ptr + found + 1) < '0' || *(ptr + found + 1) > '8') {
            char tmp[3] = {0};
            tmp[0] = '\\';
            tmp[1] = *(ptr + found + 1);
            converted_str += (char*)tmp;
            start = found + 2;
            
        // 处理 utf-8 的一个字节
        } else {
            unsigned char esc[2] = {0};
            int idx = 1;
            esc[0] += ((*(ptr + found + idx)) - '0') * 64;
            ++idx;
            esc[0] += ((*(ptr + found + idx)) - '0') * 8;
            ++idx;
            esc[0] += ((*(ptr + found + idx)) - '0');
            ++idx;
            converted_str += (char*)esc;
            start = found + idx;
        }
        found = str.find_first_of("\\", start);
    }
    string tmp = str.substr(start, str.length());
    converted_str += tmp;
    return converted_str;
}

const Annotation * find_annotation_by_id(uint32_t id, const DimensionDoc& doc) {
    size_t left = 0;
    size_t right = doc.annotations.size();
    while (left < right) {
        size_t mid = left + ((right - left) >> 1); 
        const Annotation* ret = &(doc.annotations[mid]);
        if (ret->id == id) {
            return ret;
        } else if (ret->id < id) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return NULL;
}

} // namespace unise

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
