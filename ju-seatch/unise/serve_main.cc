#include <gflags/gflags.h>
#include <comlogplugin.h>
#include <boost/scoped_ptr.hpp>
#include "breakpad/client/linux/handler/exception_handler.h"
// #include <google/profiler.h>
#include "unise/singleton.h"
#include "util/file_monitor.h"
#include "unise/state_monitor.h"
#include "unise/asl_wordseg.h"
#include "serve/serve_impl.h"
#include "unise/base.h"
#include "util/global_init.h"
#include "unise/global_handler.h"
#include "serve/search_engine.h"
#include "serve/frontend/unise_frontend.h"
#include "unise/delay_callback.h"
#include "unise/util.h"
#include "baidu/rpc/server.h"

namespace bhp = baidu::rpc;

DEFINE_string(dump_path, "./bin", ".dmp文件存放路径");
DEFINE_bool(enable_minidump, false, "启用minidump的开关");
DEFINE_int32(idle_timeout_s, -1, "Connection will be closed if there is no \
            read/write operations during the last 'idle_timeout_s'");
DEFINE_int32(logoff_ms, 2000, "Maximum duration of server's LOGOFF state (waiting \
        for client to close connection before server stops)");
DEFINE_string(server_address, "", "rpc server conf, format as, acceptable_ip:port,\
            if not set, use the ServerAddress in configure file of unise_serve");
DECLARE_string(conf_fpath);
DECLARE_string(conf_fname);

using namespace unise;

static bool g_signal_quit = false;

void on_exit(int signum)
{
    UWARNING("Program exiting on signal %s(%d).", strsignal(signum), signum);
    RAISE_EVENT(on_exit);
    g_signal_quit = true; 
}

static bool dump_callback(const google_breakpad::MinidumpDescriptor& descriptor,
        void* context,
        bool succeeded)
{
    UNOTICE("Dump path: %s", descriptor.path());
    return true;
}

int main(int argc, char *argv[]) {
    int ret = -1;
    // 最先应解析 gflags 文件和命令行参数，命令行参数覆盖 gflags 文件设置
    GlobalInit::global_init(argc, argv);
    // 初始化 BreakPad 接口
    boost::scoped_ptr<google_breakpad::MinidumpDescriptor> descriptor;
    boost::scoped_ptr<google_breakpad::ExceptionHandler> eh;
    if (FLAGS_enable_minidump) {
        if (-1 == access(FLAGS_dump_path.c_str(), F_OK)) {
            mkdir(FLAGS_dump_path.c_str(), S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
        }
        if (-1 == access(FLAGS_dump_path.c_str(), F_OK)) {
            FLAGS_dump_path = "./";
        }
        descriptor.reset(new google_breakpad::MinidumpDescriptor(FLAGS_dump_path));
        eh.reset(new google_breakpad::ExceptionHandler(*(descriptor.get()), NULL, dump_callback, NULL, true, -1));
    }
    // 根据 gflags 解析对应的配置文件，这里不使用约束文件，因为很多情形下RD
    // 会忘记更新约束文件，带来的麻烦可能比好处还大。
    comcfg::Configure conf;
    if (conf.load(FLAGS_conf_fpath.c_str(), FLAGS_conf_fname.c_str()) != 0) {
        UFATAL("Failed to load conf file: %s/%s.", FLAGS_conf_fpath.c_str(),
               FLAGS_conf_fname.c_str());
        return ret;
    }
    // 使用 public/comlog-plugin 封装的 comlog 接口初始化 comlog
    if (comlog_init(conf["Log"])) {
        UFATAL("Failed to initialize log module, please check [Log] in file: %s/%s",
               FLAGS_conf_fpath.c_str(), FLAGS_conf_fname.c_str());
        return ret;
    }

    // 初始化unise资源类
    if (false == Singleton<AslWordseg>::get()->init()) {
        UFATAL("Failed to init AslWordseg");
        return ret;
    }

    // 初始化FileMonitor
    Singleton<FileMonitor>::get()->start();

    // 初始化StateMonitor
    Singleton<StateMonitor>::get()->start();
    Singleton<StateMonitor>::get()->add_text_state_message("start_date", get_date(get_timestamp()));
    
    // 初始化延迟回调线程
    DelayCallbackThread delay_callback_thread;
    delay_callback_thread.start();

    // 初始化 pbrpc Server
    bhp::Server pbrpcserv;
    bhp::ServerOptions srv_opt;
    // 调用global handler的init函数
    std::string global_handler_name;
    boost::scoped_ptr<GlobalHandler> global_handler;

    try {
        global_handler_name.assign(conf["GlobalHandler"]["plugin"].to_cstr());
    } catch (comcfg::ConfigException & e) {
        global_handler_name.assign("");
        UWARNING("illegal Configure for GlobalHandler:%s, skip it", e.what());
    }

    do {
        if (global_handler_name != "") {
            global_handler.reset(GlobalHandlerFactory::get_instance(global_handler_name));
            if (global_handler.get() == NULL) {
                UFATAL("get global_handler[%s] failed", global_handler_name.c_str());
                break;
            } else if (!global_handler->init_basic(conf["GlobalHandler"])) {
                UFATAL("init global_handler[%s] failed", global_handler_name.c_str());
                break;
            }
        }

        // construct SearchEngine and Init
        // 需要保证SearchEngine在延迟回调执行完毕后才析构
        unise::SearchEngine * search_engine = Singleton<SearchEngine>::get();
        if (false == search_engine->init(conf["SearchEngine"])) {
            UFATAL("Init SearchEngine failed");
            break;
        }

        // init the frontend
        unise::UniseFrontend* frontend = Singleton<UniseFrontend>::get();
        frontend->Init();

        // 初始化 SE 服务
        ServeImpl se_service(search_engine);

        // 初始化 rpc Server
        if (pbrpcserv.AddService(&se_service, 
                    baidu::rpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
            UFATAL("Failed to register service");
            break;
        }

        try {
            srv_opt.idle_timeout_sec = FLAGS_idle_timeout_s;
            std::string server_address = FLAGS_server_address;
            if (server_address == "") {
                server_address = conf["RpcServer"]["ServerAddress"].to_cstr();
                UNOTICE("rpc_server use server_address(from conf) is:%s", server_address.c_str());
            } else {
                UNOTICE("rpc_server use server_address(from gflags) is:%s", server_address.c_str());
            }
            ret = pbrpcserv.Start(server_address.c_str(), &srv_opt);
            if (0 != ret) {
                UFATAL("Failed to start rpc server");
                break;
            }
        } catch (comcfg::ConfigException & e) {
            UFATAL("illegal Configure for rpc-server:%s", e.what());
            break;
        }

        signal(SIGTERM, on_exit);
        signal(SIGINT,  on_exit);

        GetMemInfo mem_info; 
        mem_info.get_proc_mem_info();
        UNOTICE("After Program started, proc_virt=%llu kb proc_res=%llu kb",mem_info._proc_virt, mem_info._proc_res);
        mem_info.get_sys_mem_info();
        UNOTICE("After Program started, sys_total=%llu kb sys_free=%llu kb",mem_info._sys_total, mem_info._sys_free);
        std::cout << "Program started, waiting for signal..." << std::endl;
        UNOTICE("Program started, waiting for signal...");

        // 等待中断信号
        while (!g_signal_quit) {
            sleep(1);
        }
        ret = 0;
    } while (0);

    pbrpcserv.Stop(FLAGS_logoff_ms);
    pbrpcserv.Join();
    UNOTICE("now try to stop the threads");
    // 服务关闭后，已经没有查询了，可以执行所有的回调
    // note: 有可能会stop两次(在析构的时候也执行一次)
    //       为了保证delay_callback_thread的所有回调执行
    //       在search_engine析构之前，这里显示调用一次
    delay_callback_thread.stop();
    delay_callback_thread.join();
    Singleton<StateMonitor>::get()->stop();
    Singleton<StateMonitor>::get()->join();
    Singleton<FileMonitor>::get()->stop();
    Singleton<FileMonitor>::get()->join();
    // 这里可能会进行SearchEngine的析构
    UNOTICE("Program stoped safely");
    return ret;
}
