// 由于百度基础库的不规范做法，导致个别宏命名与 boost 库的部分头文件中
// 变量名冲突，这里统一做一个 wrap，避免出现编译问题。
// NOTE!!! 不要将没有冲突问题的头文件放到这里

#ifndef UNISE_BOOST_WRAP_H
#define UNISE_BOOST_WRAP_H

// boost/chrono/duration.hpp 中使用了一个变量叫做 CR，与 ul_def.h 中的 CR 宏定义冲突
// 所以这里包含 boost 头文件时，要处理一下。gcc 4.3 以后才支持
// #pragma push_macro/pop_macro，所以我们只能做重定义的处理。
#ifdef CR
#define CR_CONFLICTED
#undef CR
#endif  // CR

#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/lock_types.hpp>
#include <boost/thread/condition_variable.hpp>

#ifdef CR_CONFLICTED
#define CR (char)10 // '\n'
#undef CR_CONFLICTED
#endif // CR_CONFLICTED

#endif  // UNISE_BOOST_WRAP_H
