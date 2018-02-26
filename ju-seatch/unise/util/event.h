//
// 使用 boost singals2 库，实现一个事件注册、调用系统，用于资源的延迟释放等场合。
//
// Usage:
//      class Foo {
//      private:
//          // 在类声明中定义此类要处理哪些事件，事件名必须是在本头文件中使用
//          // DEFINE_EVENT 已定义的
//          HANDLE_EVENT(on_exit);
//          HANDLE_EVENT(on_gc);
//      public:
//          Foo() {
//              // 在对象的初始化过程中，将事件的处理句柄注册到环境中。最好在所有
//              // 初始化工作完成之后再注册事件句柄，确保函数是可正确执行的。
//              REGISTER_HANDLER(on_gc, Foo, gc);
//              REGISTER_HANDLER(on_exit, Foo, exit);
//          }
//
//          // 目前只支持参数、返回值为空的事件句柄，大部分情况下也足够了
//          void gc() {
//              DO_SOMETHING...
//          }
//
//          void exit() {
//              CLEANING...
//          }
//      };
//      // 然后在任意函数内都可以 RAISE_EVENT
//      void fun() {
//          Foo a;
//          RAISE_EVENT(on_gc);
//      }
// 已注册的句柄会随着对象生存期的结束自动解注册，无需手动更改。
// 具体执行案例可参考 test_event.cc 单测文件

#ifndef UTIL_EVENT_H_
#define UTIL_EVENT_H_

#include <boost/signals2/signal.hpp>
#include "unise/singleton.h"

namespace unise
{

#define DEFINE_EVENT(EVENT_NAME) \
    Event ev_##EVENT_NAME

/// @brief 存储所有 Event 的环境。由于我们希望在全局使用这个环境，为简便起见，默认的 Event
/// handler 不支持参数和返回值。
struct EventEnv {
    typedef boost::signals2::signal<void ()>    Event;

    // 以下为所有事件的定义，增加一个事件，就需要在下面添加一行
    DEFINE_EVENT(on_exit);
    DEFINE_EVENT(on_gc);
};

} // namespace unise

#define HANDLE_EVENT(EVENT_NAME) \
    boost::signals2::scoped_connection _sc_##EVENT_NAME

#define REGISTER_HANDLER(EVENT_NAME, CLASS_NAME, EVENT_HANDLER) \
    _sc_##EVENT_NAME = \
    ::unise::Singleton< ::unise::EventEnv>::get()->ev_##EVENT_NAME.connect(boost::bind(&CLASS_NAME::EVENT_HANDLER, this))

#define RAISE_EVENT(EVENT_NAME) \
    ::unise::Singleton< ::unise::EventEnv>::get()->ev_##EVENT_NAME()

#endif
