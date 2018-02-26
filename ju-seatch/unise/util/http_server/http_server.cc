#include "util/http_server/http_server.h"

#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include <vector>
#include <algorithm>
#include <sstream>

#include <ul_net.h>

#include "gflags/gflags.h"
#include "unise/base.h"
#include "util/util.h"

namespace
{
const int kMaxEpollSize = 10000;
}

using std::string;
using std::map;
using std::vector;
using std::pair;

namespace unise
{

string Request::GetBodyContent() const
{
    return body_content_;
}
string Request::GetHeaderValue(const string& head_name) const
{
    map<string, string>::const_iterator it = header_.find(head_name);
    return it != header_.end() ? it->second : "";
}

string Request::GetUrlParamValue(const string& param_name) const
{
    map<string, string>::const_iterator it = url_params_.find(param_name);
    return it != url_params_.end() ? it->second : "";
}

string Request::GetPostParamValue(const string& param_name) const
{
    map<string, string>::const_iterator it = post_params_.find(param_name);
    return it != post_params_.end() ? it->second : "";
}

bool Request::url_decode(const std::string& in, std::string& out)
{
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value && is.eof()) {
                    out += static_cast<char>(value);
                    i += 2;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (in[i] == '+') {
            out += ' ';
        } else {
            out += in[i];
        }
    }
    return true;
}

Respond::Respond()
{
    status_ = 200;
    AddHeader("Content-Type", "text/html; charset=UTF-8");
    //    AddHeader("Accept-Ranges", "byte");
    //  fixed by Shunping Ye, for detail see
    //  http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.12
    AddHeader("Accept-Ranges", "bytes");
    //  added by Shunping Ye
    AddHeader("Access-Control-Allow-Origin", "*");
}

void Respond::SetStatus(const int32_t &status)
{
    status_ = status;
}
void Respond::AddContent(const string &info)
{
    content_.append(info);
}

void Respond::AddHeader(const string &key, const string &value)
{
    header_[key] = value;
}

string Respond::FlushToString()
{
    AddHeader("Content-Length", UintToString(content_.size()));
    string result;
    result.reserve(4096);
    string http_status = "HTTP/1.1 ";
    http_status += IntToString(status_);
    if (status_ == 302) {
        http_status += " MOVED_TEMPORARILY\r\n";
    } else {
        http_status += " OK\r\n";
    }
    // result.append("HTTP/1.1 200 OK\r\n");
    result.append(http_status);
    // header
    for (map<string, string>::iterator it = header_.begin();
            it != header_.end(); ++it) {
        StringAppendF(&result, "%s: %s\r\n", it->first.c_str(), it->second.c_str());
    }
    result.append("\r\n");
    // content
    result.append(content_);
    return result;
}

HttpServer::HttpServer(
        uint32_t port,
        uint32_t interval_ms) : Thread("HTTPServer")
{
    Init(port, interval_ms);
}
void HttpServer::Init(
        uint32_t port,
        uint32_t interval_ms)
{
    dft_handler_ = NULL;
    port_ = port;
    interval_ms_ = interval_ms;
    stop_ = false;
    wait_sec_ = 0;
    recv_buf_ = new char[kRecvBufLen];
    recv_buf_[kRecvBufLen - 1] = 0;
    signal(SIGPIPE, SIG_IGN);
    epoll_instance_ = epoll_create(kMaxEpollSize);
    GOOGLE_CHECK_NE(epoll_instance_, -1);
}

HttpServer::~HttpServer()
{
    close(epoll_instance_);
    delete [] recv_buf_;
    delete dft_handler_;
    for (StrToCallback::iterator it = handlers_.begin(); it != handlers_.end();
            it++) {
        delete it->second;
    }
}

void HttpServer::TimingStart(int wait_sec)
{
    wait_sec_ = wait_sec;
    this->start();
}

int HttpServer::run()
{
    sleep(wait_sec_);
    Init();
    RunWithEpoll();
    return 0;
}

void HttpServer::RunWithEpoll()
{
    int lis_fd = 0;
    int num_ready_fds = 0;
    struct epoll_event lis_fd_event;
    memset(&lis_fd_event, 0, sizeof(struct epoll_event));
    struct epoll_event ready_events[kMaxEpollSize];
    lis_fd = ul_tcplisten(port_, 5);
    if (lis_fd < 0) {
        UFATAL("TcpListen failed, maybe port:%u is wrong, minifrontend not start", port_);
        return;
    }
    if (port_ == 0) {
        struct sockaddr_in in_addr;
        socklen_t len = sizeof(in_addr);
        int rc = getsockname(
                 lis_fd,
                 (struct sockaddr*)(&in_addr),
                 &len);
        if (!rc) {
            port_ = ntohs(in_addr.sin_port);
        }
    }
    lis_fd_event.events = EPOLLIN;
    lis_fd_event.data.fd = lis_fd;
    ul_setsocktonoblock(lis_fd);
    if (epoll_ctl(epoll_instance_, EPOLL_CTL_ADD, lis_fd, &lis_fd_event) == -1) {
        UFATAL("failed to listen socket:%d error:%s", lis_fd, strerror(errno));
        return;
    }
    int work_fd = 0;
    const int kWaitTimeout = 1000;
    while (!stop_) {
        memset(ready_events, 0, sizeof(struct epoll_event) * kMaxEpollSize);
        num_ready_fds =
            epoll_wait(epoll_instance_, ready_events, kMaxEpollSize, kWaitTimeout);
        if (num_ready_fds < 0) {
            UNOTICE("epoll_wait failed:%s", strerror(errno));
            // TODO(leilu) : exit here?
            continue;
        }
        for (int i = 0; i < num_ready_fds; ++i) {
            work_fd = ready_events[i].data.fd;
            if (ready_events[i].data.fd == lis_fd) {  // a new connection
                work_fd = ul_accept(lis_fd, NULL, NULL);
                if (work_fd < 0) {
                    UFATAL("TcpAccept failed");
                    continue;
                }
                ul_setsocktonoblock(work_fd);
                struct epoll_event fd_event;
                fd_event.events = EPOLLIN;
                fd_event.data.fd = work_fd;
                if (epoll_ctl(epoll_instance_, EPOLL_CTL_ADD, work_fd, &fd_event) < 0) {
                    UFATAL("failed to add socket[%d] to listen", work_fd);
                    continue;
                }
                continue;
            }
            if (!HandleReq(work_fd)) {
                epoll_ctl(epoll_instance_, EPOLL_CTL_DEL,
                    ready_events[i].data.fd, NULL);
                close(work_fd);
            }
        }
    }
    close(lis_fd);
}

void ParseKvlist(
        const string& line,
        const string& key_value_delimiter,
        const string& key_value_pair_delimiter,
        map<string, string> *kv_pair_map,
        vector<pair<string, string> >* kv_pair_vec)
{
    vector<string> pairs;
    vector<string> kvpair;
    string_split(line, key_value_pair_delimiter, &pairs);
    for (size_t i = 0; i < pairs.size(); ++i) {
        kvpair.clear();
        string_split(pairs[i], key_value_delimiter, &kvpair);
        if (kvpair.size() != 2) {
            continue;
        }
        if (kv_pair_map) {
            kv_pair_map->insert(make_pair(kvpair[0], kvpair[1]));
        }
        if (kv_pair_vec) {
            kv_pair_vec->push_back(make_pair(kvpair[0], kvpair[1]));
        }
    }
}

bool HttpServer::ParseRequest(
        char *request, int request_len, int work_fd, Request *req_info)
{
    char *url = NULL;
    char *url_param = NULL;
    char *header = NULL;
    char *content = NULL;
    if (0 == strncmp(request, "GET ", strlen("GET "))) {
        req_info->type_ = Request::kHttpGet;
        url = request + strlen("GET ");
    } else if (0 == strncmp(request, "POST ", strlen("POST "))) {
        req_info->type_ = Request::kHttpPost;
        url = request + strlen("POST ");
    } else {
        UNOTICE("http request format error, do not have 'GET' or 'POST' info");
        return false;
    }
    GOOGLE_DCHECK_LE(url, request + request_len);
    char *pos = strstr(request + 1, " HTTP");
    if (NULL == pos) {
        UNOTICE("[\tlvl=COUNT\t] http request format error, do not have 'HTTP' info");
        UNOTICE("full content:\n%s", request);
        return false;
    }
    GOOGLE_CHECK_LE(pos, request + request_len);
    *pos = 0;
    url_param = strchr(url, '?');
    if (url_param) {
        *url_param++ = 0;
    }
    GOOGLE_CHECK_LE(url_param, request + request_len);
    pos += strlen(" HTTP");
    GOOGLE_CHECK_LE(pos, request + request_len);
    char *old_pos = pos;
    pos = strstr(pos, "\r\n\r\n");
    if (pos) {
        GOOGLE_CHECK_LE(pos, request + request_len);
        content = pos + strlen("\r\n\r\n");
        GOOGLE_CHECK_LE(content, request + request_len);
        // deal with header
        header = strstr(old_pos, "\r\n");
        if (header == pos) {
            header = NULL;
        } else {
            header += strlen("\r\n");
        }
        GOOGLE_CHECK_LT(header, request + request_len);
        *pos = 0;
    } else {
        UNOTICE("http request format error, do not have '\\r\\n\\r\\n'");
        return false;
    }
    string log = StringPrintf("url[%s], url_param[%s], header[%s], content[%s]",
                 url,
                 url_param,
                 header,
                 content);
    // Get param
    if (url_param) {
        ParseKvlist(url_param, "=", "&",
                &req_info->url_params_,
                &req_info->url_param_vec_);
    }
    if (header) {
        ParseKvlist(header, ":", "\n", &req_info->header_, NULL);
    }
    if (content) {
        ParseKvlist(content, "=", "&",
                &req_info->post_params_,
                &req_info->post_param_vec_);
        req_info->body_content_ = content;
    }
    TrimString(url, "/ ", &req_info->url_);
    return true;
}

bool HttpServer::HandleWraper(const Request &request, Respond *respond)
{
    const string &url = request.url();
    StrToCallback::iterator it = handlers_.find(url);
    if (it != handlers_.end()) {
        return it->second->Run(request, respond);
    }
    if (dft_handler_) {
        return dft_handler_->Run(request, respond);
    }
    // TODO(wangguangyuan) :
    /*
    if (root_path_ != "") {
      string full_path = StringPrintf("%s/%s",
                                      root_path_.c_str(), request.url().c_str());
      struct stat file_stat;
      int ret = stat(full_path.c_str(), &file_stat);
      if (0 == ret && S_ISREG(file_stat.st_mode)) {
        string content;
        if (file::File::ReadFileToString(full_path, &content) == false) {
          LOG(ERROR) << "fail to open file:" << full_path;
          return false;
        } else {
          respond->AddContent(content);
        }
      }
    }
    */
    return true;
}

bool HttpServer::RecvRequest(int sock)
{
    int total = 0;
    int read_num = 0;
    memset(recv_buf_, 0, kRecvBufLen);
//  int content_length = 0;
    const char* get_signature = "GET ";
    const char* post_signature = "POST ";
    char* buf_index = recv_buf_;
    while (true) {
        read_num = ul_recv(sock, buf_index, kRecvBufLen, 0);
        if (read_num < 0) {
            UNOTICE("ERROR reading request, read_num(%d), err(%m)", read_num);
            return false;
        }
        if (read_num == 0) {
            return false;
        }
        total += read_num;
        recv_buf_[total] = '\0';
        // must use this temp to prevent misleading compiling error
        int temp_kRecvBufLen = kRecvBufLen;
        GOOGLE_CHECK_LT(total, temp_kRecvBufLen);
        char* index = strstr(recv_buf_, "\r\n\r\n");
        if (index != NULL) {
            //  GET
            if (strncmp(recv_buf_, get_signature, strlen(get_signature)) == 0) {
                break;
            } else if (strncmp(recv_buf_, post_signature, strlen(post_signature)) == 0) {
                char* start = strcasestr(recv_buf_,
                            "Content-Length:") + strlen("Content-Length:");
                GOOGLE_CHECK_GE(start, recv_buf_);
                char* end = strstr(start, "\r\n");
                GOOGLE_CHECK(start != NULL);
                GOOGLE_CHECK(end != NULL);
                string len(start, end);
                int length;
                StringToInt(len, &length);
                int real_len = strlen(index + 4);
                if (length == real_len) {
                    return true;
                } else {
                    //  应该继续接收剩下的length- real_len
                    int left_len = length - real_len;
                    if (static_cast<size_t>(total + left_len) >= kRecvBufLen) {
                        return false;
                    }
                    if (ul_recv(sock, recv_buf_ + total, left_len, 0) < 0) {
                        return false;
                    } else {
                        return true;
                    }
                }
            } else {
                //  OPTIONS,HEAD等其它http方法暂时不支持
                UNOTICE("[\tlvl=COUNT\t] not support http method:%s",
                        string(recv_buf_).substr(0, 10).c_str());
                return false;
            }
        } else {
            buf_index = recv_buf_ + total;
            continue;
        }
    }
    //  return read_num;
    recv_buf_[total] = '\0';
    return true;
}

bool HttpServer::HandleReq(int work_fd)
{
    if (RecvRequest(work_fd) == false) {
        UWARNING("[\tlvl=COUNT\t] fail to recv request, see the log for detail");
        return false;
    }
    int n = strlen(recv_buf_);
    //  这里解析经常出错，原因在于TcpRecv不一定接受完毕。
    Request req_info;
    if (!ParseRequest(recv_buf_, n, work_fd, &req_info)) {
        UWARNING("[\tlvl=COUNT\t] ParseRequest failed, invalid http request");
        return false;
    }
    // TODO: respond太长时，超过缓冲区，会发送失败
    Respond respond;
    if (HandleWraper(req_info, &respond)) {
        string str_respond = respond.FlushToString();
        n = ul_swriteo_ms_ex2(work_fd, const_cast<char *>(str_respond.c_str()), str_respond.length(), 5000);
        if (n < 0) {
            UWARNING("[\tlvl=COUNT\t] TcpSend failed");
            return false;
        }
    }
    string connection = req_info.GetHeaderValue("Connection");
    string::size_type pos = connection.find("keep-alive");
    return pos != string::npos;
}

}
