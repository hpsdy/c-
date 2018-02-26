// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
#ifndef  UNISE_UTIL_H_
#define  UNISE_UTIL_H_

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "gflags/gflags.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"
#include "base/macros.h"
#include "unise/general_servlet.pb.h"
#include "unise/annotation_schema.pb.h"
#include "unise/general_plugin.pb.h"
#include "unise/basictypes.h"
#include "unise/base.h"
#include "unise/fact_doc.h"

namespace unise {
using std::string;
using std::vector;
using std::pair;

/**
 * @brief 对str的首尾进行清理，删除garbage包含的字符
 */
void string_trim(string * str, const string & garbage);

/**
 * @brief 按照sep中包含的字符，切分str，结果存储到strs里面
 * @note 如果切分后遇到""，这样子的子串被抛弃
 */
void string_split(const string & str, const string & sep, vector<string> * strs);

/**
 * @brief 按照sep中包含的字符，切分str，结果存储到strs里面
 * @note ignore_empty为true时，如果切分后遇到""，这样子的子串被抛弃
 *       ignore_empty为false时，不扔空子串
 */
void string_split(const string & str,
                  const string & sep,
                  vector<string> * strs,
                  bool ignore_empty);

// Specialized string-conversion functions.
bool IntToString(int64_t number, string * str);
std::string BoolToString(bool value);
std::string IntToString(int value);
std::wstring IntToWString(int value);
std::string UintToString(unsigned int value);
std::wstring UintToWString(unsigned int value);
std::string Int64ToString(int64_t value);
std::wstring Int64ToWString(int64_t value);
std::string Uint64ToString(uint64_t value);
std::wstring Uint64ToWString(uint64_t value);

template <typename STR, typename INT, typename UINT, bool NEG>
struct IntToStringT {
    // This is to avoid a compiler warning about unary minus on unsigned type.
    // For example, say you had the following code:
    //   template <typename INT>
    //   INT abs(INT value) { return value < 0 ? -value : value; }
    // Even though if INT is unsigned, it's impossible for value < 0, so the
    // unary minus will never be taken, the compiler will still generate a
    // warning.  We do a little specialization dance...
    template <typename INT2, typename UINT2, bool NEG2>
    struct ToUnsignedT { };

    template <typename INT2, typename UINT2>
    struct ToUnsignedT<INT2, UINT2, false> {
        static UINT2 ToUnsigned(INT2 value) {
            return static_cast<UINT2>(value);
        }
    };

    template <typename INT2, typename UINT2>
    struct ToUnsignedT<INT2, UINT2, true> {
        static UINT2 ToUnsigned(INT2 value) {
            return static_cast<UINT2>(value < 0 ? -value : value);
        }
    };

    // This set of templates is very similar to the above templates, but
    // for testing whether an integer is negative.
    template <typename INT2, bool NEG2>
    struct TestNegT { };
    template <typename INT2>
    struct TestNegT<INT2, false> {
        static bool TestNeg(INT2 value) {
            // value is unsigned, and can never be negative.
            return false;
        }
    };
    template <typename INT2>
    struct TestNegT<INT2, true> {
        static bool TestNeg(INT2 value) {
            return value < 0;
        }
    };

    static STR IntToString(INT value) {
        // log10(2) ~= 0.3 bytes needed per bit or per byte log10(2**8) ~= 2.4.
        // So round up to allocate 3 output characters per byte, plus 1 for '-'.
        const int kOutputBufSize = 3 * sizeof(INT) + 1;
        // Allocate the whole string right away, we will right back to front, and
        // then return the substr of what we ended up using.
        STR outbuf(kOutputBufSize, 0);
        bool is_neg = TestNegT<INT, NEG>::TestNeg(value);
        // Even though is_neg will never be true when INT is parameterized as
        // unsigned, even the presence of the unary operation causes a warning.
        UINT res = ToUnsignedT<INT, UINT, NEG>::ToUnsigned(value);
        for (typename STR::iterator it = outbuf.end();;) {
            --it;
            GOOGLE_DCHECK(it != outbuf.begin());
            *it = static_cast<typename STR::value_type>((res % 10) + '0');
            res /= 10;
            // We're done..
            if (res == 0) {
                if (is_neg) {
                    --it;
                    GOOGLE_DCHECK(it != outbuf.begin());
                    *it = static_cast<typename STR::value_type>('-');
                }
                return STR(it, outbuf.end());
            }
        }
        // can not reach here
        GOOGLE_DCHECK(false);
        return STR();
    }
};

// Perform a best-effort conversion of the input string to a numeric type,
// setting |*output| to the result of the conversion.  Returns true for
// "perfect" conversions; returns false in the following cases:
//  - Overflow/underflow.  |*output| will be set to the maximum value supported
//    by the data type.
//  - Trailing characters in the string after parsing the number.  |*output|
//    will be set to the value of the number that was parsed.
//  - No characters parseable as a number at the beginning of the string.
//    |*output| will be set to 0.
//  - Empty string.  |*output| will be set to 0.
bool StringToBool(const std::string& intput, bool* output);
bool StringToInt(const std::string& input, int* output);
bool StringToUint(const std::string& input, uint32_t* output);
bool StringToInt64(const std::string& input, int64_t* output);
bool StringToUint64(const std::string& input, uint64_t* output);
bool SizeStringToUint64(const std::string& input_string, uint64_t* output);
bool HexStringToInt(const std::string& input, int* output);
bool HexStringToInt64(const std::string& input, int64_t* output);

template<typename StringToNumberTraits>
bool StringToNumber(const typename StringToNumberTraits::string_type& input,
        typename StringToNumberTraits::value_type* output)
{
    typedef StringToNumberTraits traits;
    errno = 0;  // Thread-safe?  It is on at least Mac, Linux, and Windows.
    typename traits::string_type::value_type* endptr = NULL;
    typename traits::value_type value = traits::convert_func(input.c_str(),
                                        &endptr);
    *output = value;
    // Cases to return false:
    //  - If errno is ERANGE, there was an overflow or underflow.
    //  - If the input string is empty, there was nothing to parse.
    //  - If endptr does not point to the end of the string, there are either
    //    characters remaining in the string after a parsed number, or the string
    //    does not begin with a parseable number.  endptr is compared to the
    //    expected end given the string's stated length to correctly catch cases
    //    where the string contains embedded NUL characters.
    //  - valid_func determines that the input is not in preferred form.
    return errno == 0 &&
           !input.empty() &&
           input.c_str() + input.length() == endptr &&
           traits::valid_func(input);
}

// Removes characters in trim_chars from the beginning and end of input.
// NOTE: Safe to use the same variable for both input and output.
bool TrimString(const std::wstring& input,
        const wchar_t trim_chars[],
        std::wstring* output);
bool TrimString(const std::string& input,
    const char trim_chars[],
    std::string* output);

enum TrimPositions {
    TRIM_NONE     = 0,
    TRIM_LEADING  = 1 << 0,
    TRIM_TRAILING = 1 << 1,
    TRIM_ALL      = TRIM_LEADING | TRIM_TRAILING,
};

template<typename STR>
TrimPositions TrimStringT(const STR& input,
        const typename STR::value_type trim_chars[],
        TrimPositions positions,
        STR* output)
{
    // Find the edges of leading/trailing whitespace as desired.
    const typename STR::size_type last_char = input.length() - 1;
    const typename STR::size_type first_good_char = (positions & TRIM_LEADING) ?
            input.find_first_not_of(trim_chars) : 0;
    const typename STR::size_type last_good_char = (positions & TRIM_TRAILING) ?
            input.find_last_not_of(trim_chars) : last_char;
    // When the string was all whitespace, report that we stripped off whitespace
    // from whichever position the caller was interested in.  For empty input, we
    // stripped no whitespace, but we still need to clear |output|.
    if (input.empty() ||
            (first_good_char == STR::npos) || (last_good_char == STR::npos)) {
        bool input_was_empty = input.empty();  // in case output == &input
        output->clear();
        return input_was_empty ? TRIM_NONE : positions;
    }
    // Trim the whitespace.
    *output =
        input.substr(first_good_char, last_good_char - first_good_char + 1);
    // Return where we trimmed from.
    return static_cast<TrimPositions>(
            ((first_good_char == 0) ? TRIM_NONE : TRIM_LEADING) |
            ((last_good_char == last_char) ? TRIM_NONE : TRIM_TRAILING));
}

/// @brief 显示内存信息
class GetMemInfo {

public:
    /// @brief 获取页大小和进程的id
    GetMemInfo() : _proc_virt(0llu), _proc_res(0llu),  _sys_total(0llu), _sys_free(0llu), 
    _statm_fd(-1), _meminfo_fd(-1), _proc_buf(NULL), _sys_buf(NULL) {}

    virtual ~GetMemInfo() {
        if (_statm_fd != -1) {
            close(_statm_fd);
        }
        if (_meminfo_fd != -1) {
            close(_meminfo_fd);
        }
        if (_proc_buf) {
            delete [] _proc_buf;
        }
        if (_sys_buf) {
            delete [] _sys_buf;
        }
    }

    void get_proc_mem_info() {
        bool succ = false;
        if (_statm_fd == -1) {
            char full_path[28];
            _page_size = getpagesize();
            _my_pid = getpid();
            // 当字符串长度大于等于28时，会拷贝27个字节，最后一个字节补0 
            snprintf(full_path, 28, "/proc/%d/statm", _my_pid);
            _statm_fd = open(full_path, O_RDONLY, 0);
            _proc_buf = new (std::nothrow) char[128];
        }
        if (_statm_fd != -1 && _proc_buf) {
            lseek(_statm_fd, 0L, SEEK_SET);
            ssize_t num_read = read(_statm_fd, _proc_buf, 127);
            if (num_read > 0) {
                _proc_buf[num_read] = 0;
                sscanf(_proc_buf, "%llu %llu", &_proc_virt, &_proc_res);
                _proc_virt *= _page_size;
                _proc_res *= _page_size;
                _proc_virt >>= 10;
                _proc_res >>= 10;
                succ = true;
            }
        }
        if (!succ) {
            _proc_virt = _proc_res = 0llu;
        }
    }

    void get_sys_mem_info() {
        unsigned long long sys_buffers = 0;
        unsigned long long sys_cached = 0;
        bool succ = false;
        if (_meminfo_fd == -1) {
            _meminfo_fd = open("/proc/meminfo", O_RDONLY, 0);
            _sys_buf = new (std::nothrow) char[2048];
        }
        if (_meminfo_fd != -1 && _sys_buf) {
            lseek(_meminfo_fd, 0L, SEEK_SET);
            ssize_t num_read = read(_meminfo_fd, _sys_buf, 2047);
            if (num_read > 0) {
                _sys_buf[num_read] = 0;
                char *head = NULL;
                char *tail = NULL;
                do {
                    head = strstr(_sys_buf, "Buffers:");
                    if (!head) {
                        break;
                    }
                    head += strlen("Buffers:"); 
                    sys_buffers = strtoull(head, &tail, 10);

                    head = strstr(_sys_buf, "MemFree:");
                    if (!head) {
                        break;
                    }
                    head += strlen("MemFree:"); 
                    _sys_free = strtoull(head, &tail, 10);

                    head = strstr(_sys_buf, "Cached:");
                    if (!head) {
                        break;
                    }
                    head += strlen("Cached:"); 
                    sys_cached = strtoull(head, &tail, 10);

                    head = strstr(_sys_buf, "MemTotal:");
                    if (!head) {
                        break;
                    }
                    head += strlen("MemTotal:"); 
                    _sys_total = strtoull(head, &tail, 10);
                    _sys_free += sys_buffers + sys_cached;
                    succ = true;
                } while (0);
            }
        }
        if (!succ) {
            _sys_free = _sys_total = 0llu;
        }
    }
public:
    unsigned long long _proc_virt;
    unsigned long long _proc_res;
    unsigned long long _sys_total;
    unsigned long long _sys_free;
    int _my_pid;
private:
    unsigned _page_size;
    int _statm_fd;
    int _meminfo_fd;
    char *_proc_buf;
    char *_sys_buf;
};

/// @brief 秒表
class StopWatch {
public:
    /// @brief 初始化秒表
    /// @param base : 计时返回值的精度，base 为 1 代表微秒，1000 代表毫秒，依此类推
    StopWatch(uint32_t base = 1000) {
        _base = base ? base : 1.0;
        reset();
    }

    /// @brief 重置秒表
    void reset() {
        _split_time.clear();
        gettimeofday(&_start, NULL);
    }

    /// @brief 读表，当前距离 _start 度过了多长时间
    inline double read() {
        struct timeval now;
        gettimeofday(&now, NULL);
        return ((now.tv_sec - _start.tv_sec) * 1000000 + now.tv_usec - _start.tv_usec) / _base;
    }

    /// @brief 计时，记录当前距离 _start 度过了多长时间
    /// @return _start 到这次计时的时间，精度以 _base 为准
    double split() {
        double split_time = read();
        _split_time.push_back(split_time);
        return split_time;
    }

    /// @brief 获取到现在为止共 split 了多少次
    inline size_t get_split_num() {
        return _split_time.size();
    }

    /// @brief 获取第i次 split 距离 start 的时间
    /// @note 调用者需要处理越界异常
    inline double get_split_time(size_t i) {
        return _split_time[i];
    }

    /// @brief 获取第i次 split 距离上一次 split 的时间
    /// @note 调用者需要处理越界异常
    inline double get_split_lag(size_t i) {
        return i ? (_split_time[i] - _split_time[i-1]) : _split_time[0];
    }

private:
    struct timeval          _start;         ///< 计时器开始时间
    double                  _base;          ///< 时间精度
      std::vector<double>     _split_time;    ///< 每次计时距离开始时间的时长
};

const std::string StringPrintf(const char* format, ...);
const std::wstring StringPrintf(const wchar_t* format, ...);

void StringAppendF(std::string* dst, const char* format, ...);
void StringAppendF(std::wstring* dst, const wchar_t* format, ...);

void StringAppendV(std::string* dst, const char* format, va_list ap);
void StringAppendV(std::wstring* dst, const wchar_t* format, va_list ap);

inline int vsnprintfT(char* buffer,
        size_t buf_size,
        const char* format,
        va_list argptr)
{
    return ::vsnprintf(buffer, buf_size, format, argptr);
}

inline int vsnprintfT(wchar_t* buffer,
        size_t buf_size,
        const wchar_t* format,
        va_list argptr)
{
    return ::vswprintf(buffer, buf_size, format, argptr);
}

// Templatized backend for StringPrintF/StringAppendF. This does not finalize
// the va_list, the caller is expected to do that.
template <class StringType>
static void StringAppendVT(StringType* dst,
        const typename StringType::value_type* format,
        va_list ap)
{
    // First try with a small fixed size buffer.
    // This buffer size should be kept in sync with StringUtilTest.GrowBoundary
    // and StringUtilTest.StringPrintfBounds.
    typename StringType::value_type stack_buf[1024];
    va_list ap_copy;
    va_copy(ap_copy, ap);
    errno = 0;
    int result = vsnprintfT(stack_buf, arraysize(stack_buf), format, ap_copy);
    va_end(ap_copy);
    if (result >= 0 && result < static_cast<int>(arraysize(stack_buf))) {
        // It fit.
        dst->append(stack_buf, result);
        return;
    }
    // Repeatedly increase buffer size until it fits.
    int mem_length = arraysize(stack_buf);
    while (true) {
        if (result < 0) {
            // On Windows, vsnprintfT always returns the number of characters in a
            // fully-formatted string, so if we reach this point, something else is
            // wrong and no amount of buffer-doubling is going to fix it.
            if (errno != 0 && errno != EOVERFLOW) {
                // If an error other than overflow occurred, it's never going to work.
                UWARNING("[\tlvl=SERIOUS\t] Unable to printf the requested string due to error.");
                return;
            }
            // Try doubling the buffer size.
            mem_length *= 2;
        } else {
            // We need exactly "result + 1" characters.
            mem_length = result + 1;
        }
        if (mem_length > 32 * 1024 * 1024) {
            // That should be plenty, don't try anything larger.  This protects
            // against huge allocations when using vsnprintfT implementations that
            // return -1 for reasons other than overflow without setting errno.
            UWARNING("[\tlvl=SERIOUS\t] Unable to printf the requested string due to size.");
            return;
        }
        std::vector<typename StringType::value_type> mem_buf(mem_length);
        // NOTE: You can only use a va_list once.  Since we're in a while loop, we
        // need to make a new copy each time so we don't use up the original.
        va_copy(ap_copy, ap);
        result = vsnprintfT(&mem_buf[0], mem_length, format, ap_copy);
        va_end(ap_copy);
        if ((result >= 0) && (result < mem_length)) {
            // It fit.
            dst->append(&mem_buf[0], result);
            return;
        }
    }
}

// return true if find the key
// note:in EngineUnit, use SearchContext.get_experiment_value
//      in SearchEngine, just use this method
bool get_bool_experiment_value(const GeneralSearchRequest & request,
        const std::string & key, bool * value);

// return true if find the key
// note:in EngineUnit, use SearchContext.get_experiment_value
//      in SearchEngine, just use this method
bool get_int_experiment_value(const GeneralSearchRequest & request,
        const std::string & key, int32_t * value);

// return true if find the key
// note:in EngineUnit, use SearchContext.get_experiment_value
//      in SearchEngine, just use this method
bool get_string_experiment_value(const GeneralSearchRequest & request,
        const std::string & key, std::string * value);

/**
* @brief 获取主机名
*/
bool get_host_name(std::string &hostname);

/**
* @brief 获取主机所在机房
* @note hostname应为百度的主机名即以".baidu.com"结尾
*/
bool get_host_loc_from_baidu_domain(const std::string &hostname, 
    std::string &location);

/// @brief 根据相对thirdparty的位置，获取文件针对binary的相对路径
/// @note 依赖了FLAGS_thirdparty_path的配置,FLAGS_thirdparty_path最好为绝对路径
std::string get_file_path(const std::string& relative_to_thirdparty);

/**
 * @breaf 根据查询节点，获取该查询节点对应的tokenid
 *        主要在检索端调用，如scorer中
 *
 * @param [in] : query_node, VALUE类型的查询节点
 * @param [out] : none
 * @return int64_t
 * @retval query_node对应的倒排拉链的token的token id
 *         ILLEGAL_TOKEN_ID，获取失败
 * @see
 * @note 该函数是能支持TEXT value类型的query node
 *       未来支持NUMBER value类型的query node时，需要提供新的方法
**/
TokenId get_token_id_from_query_node_value(const QueryNodeValue& value);

/**
 * @brief 根据das的一个field字段，以及配置的类型，生成Annotation
 * @note 需要保证的前提的AnnotationSchema已经配置好了
 */
bool generate_annotations_from_field(const std::string& field,
                                     const IndexFieldFormat& format,
                                     std::vector<Annotation> * annotations);

uint64_t get_event_id(const std::string &line);

/**
 * @brief 获取当前的系统时间，单位ms
 */
int32_t get_timestamp();

/**
 * @brief 根据距1970-1-1 00:00:00的秒数，获取本地时间
 *        返回string格式：YYYY-MM-DD HH:mm:ss
 */
std::string get_date(int32_t timestamp);

/**
 * @brief 对一个字节数组，进行base64编码
 * @param[in] in，被编码字节数组的起始地址
 * @param[in] len, 数组长度
 * @param[out] out, 编码结果缓冲区的起始地址
 * @param[out] size, 编码结果缓冲区大小
 * @retval 返回编码结果的长度，单位字节
 * @return -1 失败
 *         >=0 成功
 * @warning 采用int，是因为底层实现使用OPENSSL的BIO
 */
int base64_encode(const uint8_t * in, int len, uint8_t * out, int size);

/**
 * @brief 对 PrintToString 函数输出的 string 结果中的八进制转义码序列进行处理
 * @param[in] str，从 PrintToString 函数得到的结果
 * @retval 返回处理后的结果，如汉字等可以明文显示
 * @notice 如果处理失败将返回原始结果
 *
 */
string process_escape_characters(const string& str);

/**
 * @brief 对base64编码的字符串解码
 * @param[in] in，解码数组的起始地址
 * @param[in] len, 解码数组长度
 * @param[out] out, 结果缓冲区的起始地址
 * @param[out] size, 结果缓冲区大小
 * @retval 返回解码结果的长度，单位字节
 * @return -1 失败
 *         >=0 成功
 */
int base64_decode(uint8_t * in, int len, uint8_t * out, int size);

// 读取序列化protobuf的配置文件内容
template <class T>
bool load_protobuf_conf(const std::string &file_name, T *obj) {
    const int fd = open(file_name.c_str(), O_RDONLY);
    if (fd == -1) {
        UFATAL("failed to open '%s' file", file_name.c_str());
        return false;
    }
    google::protobuf::io::FileInputStream ins(fd);
    bool init_succ = google::protobuf::TextFormat::Parse(&ins, obj);
    if (!init_succ) {
        UFATAL("failed to read '%s' illegal conf", file_name.c_str());
    }
    ins.Close();
    close(fd);
    return init_succ;
}

const Annotation * find_annotation_by_id(uint32_t id, const DimensionDoc& doc);

} // namespace unise

#endif  // UNISE_UTIL_H_

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
