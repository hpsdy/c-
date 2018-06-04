#ifndef UNISE_BASICTYPES_H
#define UNISE_BASICTYPES_H

#include <assert.h>
#include <limits.h>         // So we can set the bounds of our types
#include <stddef.h>         // For size_t
#include <stdint.h>         // For intptr_t.
#include <string.h>         // for memcpy
#include <google/protobuf/stubs/common.h>

namespace unise
{
using google::protobuf::internal::down_cast;
using google::protobuf::internal::implicit_cast;
}

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#ifndef DISALLOW_IMPLICIT_CONSTRUCTORS
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName();                                    \
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(TypeName)
#endif

// A macro to mark the function or variable or types to be deprecated.
// The code depends on deprecated code would cuase compile warnings.
#define UNISE_DEPRECATED __attribute__((deprecated))

// The arraysize(arr) macro returns the # of elements in an array arr.
// The expression is a compile-time constant, and therefore can be
// used in defining new arrays, for example.  If you use arraysize on
// a pointer by mistake, you will get a compile-time error.
//
// One caveat is that arraysize() doesn't accept any array of an
// anonymous type or a type defined inside a function.  In these rare
// cases, you have to use the unsafe ARRAYSIZE_UNSAFE() macro below.  This is
// due to a limitation in C++'s template system.  The limitation might
// eventually be removed, but it hasn't happened yet.

// This template function declaration is used in defining arraysize.
// Note that the function doesn't need an implementation, as we only
// use its type.
// public/common/base/macros.h中已经定义了，所以这里注释掉
// template <typename T, size_t N>
// char(&ArraySizeHelper(T(&array)[N]))[N];

// That gcc wants both of these prototypes seems mysterious. VC, for
// its part, can't decide which to use (another mystery). Matching of
// template overloads: the final frontier.
// public/common/base/macros.h中已经定义了，所以这里注释掉
// #ifndef _MSC_VER
// template <typename T, size_t N>
// char(&ArraySizeHelper(const T(&array)[N]))[N];
// #endif
// 
// #define arraysize(array) (sizeof(ArraySizeHelper(array)))


// MetatagId refers to metatag-id that we assign to
// each metatag <name, value> pair..
typedef uint32_t MetatagId;

// Argument type used in interfaces that can optionally take ownership
// of a passed in argument.  If TAKE_OWNERSHIP is passed, the called
// object takes ownership of the argument.  Otherwise it does not.
enum Ownership {
    DO_NOT_TAKE_OWNERSHIP,
    TAKE_OWNERSHIP
};

// bit_cast<Dest,Source> is a template function that implements the
// equivalent of "*reinterpret_cast<Dest*>(&source)".  We need this in
// very low-level functions like the protobuf library and fast math
// support.
//
//   float f = 3.14159265358979;
//   int i = bit_cast<int32>(f);
//   // i = 0x40490fdb
//
// The classical address-casting method is:
//
//   // WRONG
//   float f = 3.14159265358979;            // WRONG
//   int i = * reinterpret_cast<int*>(&f);  // WRONG
//
// The address-casting method actually produces undefined behavior
// according to ISO C++ specification section 3.10 -15 -.  Roughly, this
// section says: if an object in memory has one type, and a program
// accesses it with a different type, then the result is undefined
// behavior for most values of "different type".
//
// This is true for any cast syntax, either *(int*)&f or
// *reinterpret_cast<int*>(&f).  And it is particularly true for
// conversions betweeen integral lvalues and floating-point lvalues.
//
// The purpose of 3.10 -15- is to allow optimizing compilers to assume
// that expressions with different types refer to different memory.  gcc
// 4.0.1 has an optimizer that takes advantage of this.  So a
// non-conforming program quietly produces wildly incorrect output.
//
// The problem is not the use of reinterpret_cast.  The problem is type
// punning: holding an object in memory of one type and reading its bits
// back using a different type.
//
// The C++ standard is more subtle and complex than this, but that
// is the basic idea.
//
// Anyways ...
//
// bit_cast<> calls memcpy() which is blessed by the standard,
// especially by the example in section 3.9 .  Also, of course,
// bit_cast<> wraps up the nasty logic in one place.
//
// Fortunately memcpy() is very fast.  In optimized mode, with a
// constant size, gcc 2.95.3, gcc 4.0.1, and msvc 7.1 produce inline
// code with the minimal amount of data movement.  On a 32-bit system,
// memcpy(d,s,4) compiles to one load and one store, and memcpy(d,s,8)
// compiles to two loads and two stores.
//
// I tested this code with gcc 2.95.3, gcc 4.0.1, icc 8.1, and msvc 7.1.
//
// WARNING: if Dest or Source is a non-POD type, the result of the memcpy
// is likely to surprise you.

// public/common/base/macros.h中已经定义了，所以这里注释掉
// template <class Dest, class Source>
// inline Dest bit_cast(const Source& source)
// {
//     // Compile time assertion: sizeof(Dest) == sizeof(Source)
//     // A compile error here means your Dest and Source have different sizes.
//     typedef char VerifySizesAreEqual [sizeof(Dest) == sizeof(Source) ? 1 : -1];
//     Dest dest;
//     memcpy(&dest, &source, sizeof(dest));
//     return dest;
// }

// Used to explicitly mark the return value of a function as unused. If you are
// really sure you don't want to do anything with the return value of a function
// that has been marked WARN_UNUSED_RESULT, wrap it with this. Example:
//
//   scoped_ptr<MyType> my_var = ...;
//   if (TakeOwnership(my_var.get()) == SUCCESS)
//     ignore_result(my_var.release());
//
// public/common/base/macros.h中已经定义了，所以这里注释掉
// template<typename T>
// inline void ignore_result(const T& ignored)
// {
// }

#endif  // UNISE_BASICTYPES_H
