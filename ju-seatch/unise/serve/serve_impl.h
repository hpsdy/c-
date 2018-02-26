#ifndef SERVE_SERVE_IMPL_H_
#define SERVE_SERVE_IMPL_H_

#include "unise/general_servlet.pb.h"
#include "serve/search_engine.h"
#include "unise/base.h"
#include "baidu/rpc/channel.h"

class ServeImpl : public unise::UniseService
{
public:
    ServeImpl(unise::SearchEngine * search_engine)
        : search_engine_(search_engine) {}

    virtual ~ServeImpl() {}
    virtual void Search(::google::protobuf::RpcController* controller,
            const ::unise::GeneralSearchRequest* request,
            ::unise::GeneralSearchResponse* response,
            ::google::protobuf::Closure* done) {
#ifndef NDEBUG
        try {
#endif
            search_engine_->search(request, response);
#ifndef NDEBUG
        } catch (bsl::ParseErrorException &e) {
            UWARNING("[\tlvl=MONITOR\treq_id=%lu\tfile=%s\tline=%u\tbsl::exception=%s\t]",
                     request->request_id(), e.file(), e.line(), e.what());
            response->set_status_code(unise::kStatusError);
            response->set_status_msg("Invalid request.\n");
        } catch (bsl::Exception &e) {
            UWARNING("[\tlvl=FOLLOW\treq_id=%lu\tfile=%s\tline=%u\tbsl::exception=%s\t]",
                     request->request_id(), e.file(), e.line(), e.what());
            response->set_status_code(unise::kStatusError);
            response->set_status_msg("Internal server error.");
        } catch (std::exception& e) {
            UWARNING("[\tlvl=FOLLOW\treq_id=%lu\tstd::exception=%s\t]",
                     request->request_id(), e.what());
            response->set_status_code(unise::kStatusError);
            response->set_status_msg("Internal server error.");
        } catch (...) {
            UWARNING("[\tlvl=FOLLOW\treq_id=%lu\tunknown::exception\t]",
                     request->request_id());
            response->set_status_code(unise::kStatusError);
            response->set_status_msg("Internal server error.");
        }
#endif
        if (done) {
            done->Run();
            UDEBUG("ServeImpl: search done");
        }
    }
private:
    unise::SearchEngine * search_engine_;
};

#endif
