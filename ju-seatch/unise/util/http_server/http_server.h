#ifndef UTIL_HTTP_SERVER_HTTP_SERVER_H_
#define UTIL_HTTP_SERVER_HTTP_SERVER_H_

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <string>

#include "unise/thread.h"
#include "unise/callback.h"
#include "util/hash_tables.h"

namespace unise
{

class Request
{
public:
    enum Type {
        kHttpGet,
        kHttpPost,
    };

    std::string GetBodyContent() const;
    std::string GetHeaderValue(const std::string& head_name) const;
    std::string GetUrlParamValue(const std::string& param_name) const;
    std::string GetPostParamValue(const std::string& param_name) const;

    Type type() const { return type_; }
    std::string url() const { return url_; }

    const std::map<std::string, std::string> &header() const { return header_; }
    const std::map<std::string, std::string> &url_params() const {
        return url_params_;
    }
    const std::map<std::string, std::string> &post_params() const {
        return post_params_;
    }

    const std::vector<std::pair<std::string, std::string> >&
    url_param_vec() const {
        return url_param_vec_;
    }
    const std::vector<std::pair<std::string, std::string> >&
    post_param_vec() const {
        return post_param_vec_;
    }

    /// @brief 来自 boost 的 url_decode 实现
    /// http://www.boost.org/doc/libs/1_53_0/doc/html/boost_asio/example/http/ServerPort/
    /// request_handler.cpp
    /// @note 为减轻测试代价，接口和实现与 boost example 保持完全一致
    /// Perform URL-decoding on a string. Returns false if the encoding was
    /// invalid.
    static bool url_decode(const std::string& in, std::string& out);

private:
    Type type_;
    std::string url_;
    friend class HttpServer;
    std::map<std::string, std::string> header_;
    std::map<std::string, std::string> url_params_;
    std::vector<std::pair<std::string, std::string> > url_param_vec_;
    std::map<std::string, std::string> post_params_;
    std::vector<std::pair<std::string, std::string> > post_param_vec_;
    std::string body_content_;
};

class Respond
{
public:
    explicit Respond();
    void SetStatus(const int32_t &status);
    void AddContent(const std::string &info);
    void AddHeader(const std::string &key, const std::string &value);

private:
    std::string FlushToString();

    friend class HttpServer;
    std::string content_;
    std::map<std::string, std::string> header_;
    int32_t status_;
};

enum HandleStatus {
    kKeepAlive,
    kCloseSock,
    kHandleError
};

class HttpServer : public unise::Thread
{
public:

    explicit HttpServer(
            uint32_t port,
            uint32_t interval_ms = 100);
    ~HttpServer();

    void TryStop() {
        stop_ = true;
    }

    void Stop() {
        stop_ = true;
        join();
    }

    void TimingStart(int wait_sec = 0);

    template <class Type>
    void AddHandler(
            const std::string& name,
            Type* obj,
            bool (Type::*member)(const Request&, Respond*)) {
        handlers_[name] = unise::NewPermanentCallback(obj, member);
    }
#if 0
    void AddHandler(const std::string& name,
            bool (*fun)(const Request&, Respond*)) {
        handlers_[name] = unise::NewPermanentCallback(fun);
    }
    void AddHandler(const std::string& name,
            unise::ResultCallback2<bool, const Request&, Respond*>* callback) {
        handlers_[name] = callback;
    }
#endif

    template <class Type>
    void SetDftHandler(Type* obj,
            bool (Type::*member)(const Request&, Respond*)) {
        dft_handler_ = unise::NewPermanentCallback(obj, member);
    }
#if 0
    void SetDftHandler(bool (*fun)(const Request&, Respond*)) {
        dft_handler_ = unise::NewPermanentCallback(fun);
    }
    void SetDftHandler(
            unise::ResultCallback2<bool, const Request&, Respond*>* callback) {
        dft_handler_ = callback;
    }
#endif

    void SetRootPath(std::string root_path) {
        root_path_ = root_path;
    }

    uint16_t ServerPort() const { return port_; }

    virtual void Init() {}

private:
    void Init(uint32_t port, uint32_t interval_ms);

    typedef __gnu_cxx::hash_map<std::string, unise::ResultCallback2<bool, const Request&, Respond*>*> StrToCallback;
    virtual int run();

    bool HandleWraper(const Request &request, Respond *respond);
    bool RecvRequest(int sock);
    bool HandleReq(int work_fd);
    bool ParseRequest(
            char *request, int request_len, int work_fd, Request *req_info);
    void RunWithEpoll();

    StrToCallback handlers_;
    unise::ResultCallback2<bool, const Request &, Respond*>* dft_handler_;
    std::string root_path_;

    static const uint32_t kRecvTimeout = 1000 * 10;
    static const uint32_t kRecvBufLen = 1024 * 1024 * 10;
    uint32_t port_;
    uint32_t interval_ms_;
    char *recv_buf_;
    bool stop_;
    int wait_sec_;
    // epoll instance
    int epoll_instance_;
    std::vector<std::pair<std::string, std::string> > user_passes_;
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(HttpServer);
};
void ParseKvlist(
        const std::string& line,
        const std::string& key_value_delimiter,
        char key_value_pair_delimiter,
        std::map<std::string, std::string> *kv_pair_map,
        std::vector<std::pair<std::string, std::string> >* kv_pair_vec);
}

#endif  // UTIL_HTTP_SERVER_HTTP_SERVER_H_
