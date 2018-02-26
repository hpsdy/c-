// ===================================================================
// 以下注释来自于 google/protobuf/stubs/common.h，复制在这里便于理解
// emulates google3/base/callback.h

// Abstract interface for a callback.  When calling an RPC, you must provide
// a Closure to call when the procedure completes.  See the Service interface
// in service.h.
//
// To automatically construct a Closure which calls a particular function or
// method with a particular set of parameters, use the NewCallback() function.
// Example:
//   void FooDone(const FooResponse* response) {
//     ...
//   }
//
//   void CallFoo() {
//     ...
//     // When done, call FooDone() and pass it a pointer to the response.
//     Closure* callback = NewCallback(&FooDone, response);
//     // Make the call.
//     service->Foo(controller, request, response, callback);
//   }
//
// Example that calls a method:
//   class Handler {
//    public:
//     ...
//
//     void FooDone(const FooResponse* response) {
//       ...
//     }
//
//     void CallFoo() {
//       ...
//       // When done, call FooDone() and pass it a pointer to the response.
//       Closure* callback = NewCallback(this, &Handler::FooDone, response);
//       // Make the call.
//       service->Foo(controller, request, response, callback);
//     }
//   };
//
// Currently NewCallback() supports binding zero, one, or two arguments.
//
// Callbacks created with NewCallback() automatically delete themselves when
// executed.  They should be used when a callback is to be called exactly
// once (usually the case with RPC callbacks).  If a callback may be called
// a different number of times (including zero), create it with
// NewPermanentCallback() instead.  You are then responsible for deleting the
// callback (using the "delete" keyword as normal).
//
// Note that NewCallback() is a bit touchy regarding argument types.  Generally,
// the values you provide for the parameter bindings must exactly match the
// types accepted by the callback function.  For example:
//   void Foo(string s);
//   NewCallback(&Foo, "foo");          // WON'T WORK:  const char* != string
//   NewCallback(&Foo, string("foo"));  // WORKS
// Also note that the arguments cannot be references:
//   void Foo(const string& s);
//   string my_str;
//   NewCallback(&Foo, my_str);  // WON'T WORK:  Can't use referecnes.
// However, correctly-typed pointers will work just fine.

#ifndef UTIL_CALLBACK_H_
#define UTIL_CALLBACK_H_

#include <google/protobuf/stubs/common.h>

namespace unise
{

// 将我们用到的类型暴露到命名空间中便于使用
using google::protobuf::Closure;
using google::protobuf::NewCallback;
using google::protobuf::NewPermanentCallback;

// google/protobuf 中未实现带返回值的 Callback，这里根据需要实现了一些带返回值的
// Callback 回调类型。后续根据需要，还可以增加，比如 ResultCallback0/1/3/4/5 等
template <class R, class Arg1, class Arg2>
class ResultCallback2
{
public:
    ResultCallback2() {}
    virtual ~ResultCallback2() {}
    virtual R Run(Arg1, Arg2) = 0;
private:
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ResultCallback2);
};

// 以下为内部类型，不对外暴露
namespace internal
{

template <bool del, class R, class T, class Arg1, class Arg2>
class _MemberResultCallback_0_2 : public ResultCallback2<R, Arg1, Arg2>
{
public:
    typedef ResultCallback2<R, Arg1, Arg2> base;
    typedef R(T::*MemberSignature)(Arg1, Arg2);
    inline _MemberResultCallback_0_2(T* object, MemberSignature member)
        : object_(object), member_(member) {}

    virtual R Run(Arg1 arg1, Arg2 arg2) {
        R result = (object_->*member_)(arg1, arg2);
        if (del) {
            //  zero out the pointer to ensure segfault if used again
            member_ = NULL;
            delete this;
        }
        return result;
    }
private:
    T* object_;
    MemberSignature member_;
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(_MemberResultCallback_0_2);
};

template <bool del, class R, class T, class Arg1, class Arg2>
class _ConstMemberResultCallback_0_2 : public ResultCallback2<R, Arg1, Arg2>
{
public:
    typedef ResultCallback2<R, Arg1, Arg2> base;
    typedef R(T::*MemberSignature)(Arg1, Arg2) const;
    inline _ConstMemberResultCallback_0_2(const T* object, MemberSignature member)
        : object_(object), member_(member) {}

    virtual R Run(Arg1 arg1, Arg2 arg2) {
        R result = (object_->*member_)(arg1, arg2);
        if (del) {
            //  zero out the pointer to ensure segfault if used again
            member_ = NULL;
            delete this;
        }
        return result;
    }
private:
    const T* object_;
    MemberSignature member_;
    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(_ConstMemberResultCallback_0_2);
};

}   // namespace internal

// 获取对应带返回值 Closure 的模板函数
template <class T1, class T2, class R, class Arg1, class Arg2>
inline typename internal::_ConstMemberResultCallback_0_2<true, R, T1, Arg1, Arg2>::base*
NewCallback(const T1* obj, R(T2::*member)(Arg1, Arg2) const)
{
    return new internal::_ConstMemberResultCallback_0_2<true, R, T1, Arg1, Arg2>(obj, member);
}

template <class T1, class T2, class R, class Arg1, class Arg2>
inline typename internal::_ConstMemberResultCallback_0_2<false, R, T1, Arg1, Arg2>::base*
NewPermanentCallback(const T1* obj, R(T2::*member)(Arg1, Arg2) const)
{
    return new internal::_ConstMemberResultCallback_0_2<false, R, T1, Arg1, Arg2>(obj, member);
}

template <class T1, class T2, class R, class Arg1, class Arg2>
inline typename internal::_MemberResultCallback_0_2<true, R, T1, Arg1, Arg2>::base*
NewCallback(T1* obj, R(T2::*member)(Arg1, Arg2))
{
    return new internal::_MemberResultCallback_0_2<true, R, T1, Arg1, Arg2>(obj, member);
}

template <class T1, class T2, class R, class Arg1, class Arg2>
inline typename internal::_MemberResultCallback_0_2<false, R, T1, Arg1, Arg2>::base*
NewPermanentCallback(T1* obj, R(T2::*member)(Arg1, Arg2))
{
    return new internal::_MemberResultCallback_0_2<false, R, T1, Arg1, Arg2>(obj, member);
}

}   // namespace unise

#endif  // UTIL_CALLBACK_H_
