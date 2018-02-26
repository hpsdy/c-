# 1 "factory.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "factory.h"
# 38 "factory.h"
# 1 "/usr/local/include/c++/4.9.0/map" 1 3
# 58 "/usr/local/include/c++/4.9.0/map" 3
       
# 59 "/usr/local/include/c++/4.9.0/map" 3

# 1 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 1 3
# 61 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
# 1 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 1 3
# 59 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
# 1 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++config.h" 1 3
# 186 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++config.h" 3
namespace std
{
  typedef long unsigned int size_t;
  typedef long int ptrdiff_t;




}
# 430 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++config.h" 3
# 1 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/os_defines.h" 1 3
# 39 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/os_defines.h" 3
# 1 "/usr/include/features.h" 1 3 4
# 361 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 373 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 374 "/usr/include/sys/cdefs.h" 2 3 4
# 362 "/usr/include/features.h" 2 3 4
# 385 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4



# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/gnu/stubs.h" 2 3 4




# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 2 3 4
# 386 "/usr/include/features.h" 2 3 4
# 40 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/os_defines.h" 2 3
# 431 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++config.h" 2 3


# 1 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/cpu_defines.h" 1 3
# 434 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++config.h" 2 3
# 60 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/functexcept.h" 1 3
# 40 "/usr/local/include/c++/4.9.0/bits/functexcept.h" 3
# 1 "/usr/local/include/c++/4.9.0/bits/exception_defines.h" 1 3
# 41 "/usr/local/include/c++/4.9.0/bits/functexcept.h" 2 3

namespace std __attribute__ ((__visibility__ ("default")))
{



  void
  __throw_bad_exception(void) __attribute__((__noreturn__));


  void
  __throw_bad_alloc(void) __attribute__((__noreturn__));


  void
  __throw_bad_cast(void) __attribute__((__noreturn__));

  void
  __throw_bad_typeid(void) __attribute__((__noreturn__));


  void
  __throw_logic_error(const char*) __attribute__((__noreturn__));

  void
  __throw_domain_error(const char*) __attribute__((__noreturn__));

  void
  __throw_invalid_argument(const char*) __attribute__((__noreturn__));

  void
  __throw_length_error(const char*) __attribute__((__noreturn__));

  void
  __throw_out_of_range(const char*) __attribute__((__noreturn__));

  void
  __throw_out_of_range_fmt(const char*, ...) __attribute__((__noreturn__))
    __attribute__((__format__(__printf__, 1, 2)));

  void
  __throw_runtime_error(const char*) __attribute__((__noreturn__));

  void
  __throw_range_error(const char*) __attribute__((__noreturn__));

  void
  __throw_overflow_error(const char*) __attribute__((__noreturn__));

  void
  __throw_underflow_error(const char*) __attribute__((__noreturn__));


  void
  __throw_ios_failure(const char*) __attribute__((__noreturn__));

  void
  __throw_system_error(int) __attribute__((__noreturn__));

  void
  __throw_future_error(int) __attribute__((__noreturn__));


  void
  __throw_bad_function_call() __attribute__((__noreturn__));


}
# 61 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/cpp_type_traits.h" 1 3
# 35 "/usr/local/include/c++/4.9.0/bits/cpp_type_traits.h" 3
       
# 36 "/usr/local/include/c++/4.9.0/bits/cpp_type_traits.h" 3
# 68 "/usr/local/include/c++/4.9.0/bits/cpp_type_traits.h" 3
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  template<typename _Iterator, typename _Container>
    class __normal_iterator;


}

namespace std __attribute__ ((__visibility__ ("default")))
{


  struct __true_type { };
  struct __false_type { };

  template<bool>
    struct __truth_type
    { typedef __false_type __type; };

  template<>
    struct __truth_type<true>
    { typedef __true_type __type; };



  template<class _Sp, class _Tp>
    struct __traitor
    {
      enum { __value = bool(_Sp::__value) || bool(_Tp::__value) };
      typedef typename __truth_type<__value>::__type __type;
    };


  template<typename, typename>
    struct __are_same
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Tp>
    struct __are_same<_Tp, _Tp>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<typename _Tp>
    struct __is_void
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_void<void>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_integer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };




  template<>
    struct __is_integer<bool>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<>
    struct __is_integer<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
# 198 "/usr/local/include/c++/4.9.0/bits/cpp_type_traits.h" 3
  template<>
    struct __is_integer<short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_integer<unsigned long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_floating
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };


  template<>
    struct __is_floating<float>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_floating<double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_floating<long double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_pointer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Tp>
    struct __is_pointer<_Tp*>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_normal_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<typename _Iterator, typename _Container>
    struct __is_normal_iterator< __gnu_cxx::__normal_iterator<_Iterator,
             _Container> >
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_arithmetic
    : public __traitor<__is_integer<_Tp>, __is_floating<_Tp> >
    { };




  template<typename _Tp>
    struct __is_scalar
    : public __traitor<__is_arithmetic<_Tp>, __is_pointer<_Tp> >
    { };




  template<typename _Tp>
    struct __is_char
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_char<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<>
    struct __is_char<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };


  template<typename _Tp>
    struct __is_byte
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

  template<>
    struct __is_byte<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_byte<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

  template<>
    struct __is_byte<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };




  template<typename _Tp>
    struct __is_move_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
# 413 "/usr/local/include/c++/4.9.0/bits/cpp_type_traits.h" 3

}
# 62 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/ext/type_traits.h" 1 3
# 32 "/usr/local/include/c++/4.9.0/ext/type_traits.h" 3
       
# 33 "/usr/local/include/c++/4.9.0/ext/type_traits.h" 3




namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{



  template<bool, typename>
    struct __enable_if
    { };

  template<typename _Tp>
    struct __enable_if<true, _Tp>
    { typedef _Tp __type; };



  template<bool _Cond, typename _Iftrue, typename _Iffalse>
    struct __conditional_type
    { typedef _Iftrue __type; };

  template<typename _Iftrue, typename _Iffalse>
    struct __conditional_type<false, _Iftrue, _Iffalse>
    { typedef _Iffalse __type; };



  template<typename _Tp>
    struct __add_unsigned
    {
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;

    public:
      typedef typename __if_type::__type __type;
    };

  template<>
    struct __add_unsigned<char>
    { typedef unsigned char __type; };

  template<>
    struct __add_unsigned<signed char>
    { typedef unsigned char __type; };

  template<>
    struct __add_unsigned<short>
    { typedef unsigned short __type; };

  template<>
    struct __add_unsigned<int>
    { typedef unsigned int __type; };

  template<>
    struct __add_unsigned<long>
    { typedef unsigned long __type; };

  template<>
    struct __add_unsigned<long long>
    { typedef unsigned long long __type; };


  template<>
    struct __add_unsigned<bool>;

  template<>
    struct __add_unsigned<wchar_t>;



  template<typename _Tp>
    struct __remove_unsigned
    {
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;

    public:
      typedef typename __if_type::__type __type;
    };

  template<>
    struct __remove_unsigned<char>
    { typedef signed char __type; };

  template<>
    struct __remove_unsigned<unsigned char>
    { typedef signed char __type; };

  template<>
    struct __remove_unsigned<unsigned short>
    { typedef short __type; };

  template<>
    struct __remove_unsigned<unsigned int>
    { typedef int __type; };

  template<>
    struct __remove_unsigned<unsigned long>
    { typedef long __type; };

  template<>
    struct __remove_unsigned<unsigned long long>
    { typedef long long __type; };


  template<>
    struct __remove_unsigned<bool>;

  template<>
    struct __remove_unsigned<wchar_t>;



  template<typename _Type>
    inline bool
    __is_null_pointer(_Type* __ptr)
    { return __ptr == 0; }

  template<typename _Type>
    inline bool
    __is_null_pointer(_Type)
    { return false; }
# 165 "/usr/local/include/c++/4.9.0/ext/type_traits.h" 3
  template<typename _Tp, bool = std::__is_integer<_Tp>::__value>
    struct __promote
    { typedef double __type; };




  template<typename _Tp>
    struct __promote<_Tp, false>
    { };

  template<>
    struct __promote<long double>
    { typedef long double __type; };

  template<>
    struct __promote<double>
    { typedef double __type; };

  template<>
    struct __promote<float>
    { typedef float __type; };

  template<typename _Tp, typename _Up,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type>
    struct __promote_2
    {
      typedef __typeof__(_Tp2() + _Up2()) __type;
    };

  template<typename _Tp, typename _Up, typename _Vp,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type,
           typename _Vp2 = typename __promote<_Vp>::__type>
    struct __promote_3
    {
      typedef __typeof__(_Tp2() + _Up2() + _Vp2()) __type;
    };

  template<typename _Tp, typename _Up, typename _Vp, typename _Wp,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type,
           typename _Vp2 = typename __promote<_Vp>::__type,
           typename _Wp2 = typename __promote<_Wp>::__type>
    struct __promote_4
    {
      typedef __typeof__(_Tp2() + _Up2() + _Vp2() + _Wp2()) __type;
    };


}
# 63 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/ext/numeric_traits.h" 1 3
# 32 "/usr/local/include/c++/4.9.0/ext/numeric_traits.h" 3
       
# 33 "/usr/local/include/c++/4.9.0/ext/numeric_traits.h" 3




namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

# 54 "/usr/local/include/c++/4.9.0/ext/numeric_traits.h" 3
  template<typename _Value>
    struct __numeric_traits_integer
    {

      static const _Value __min = (((_Value)(-1) < 0) ? (_Value)1 << (sizeof(_Value) * 8 - ((_Value)(-1) < 0)) : (_Value)0);
      static const _Value __max = (((_Value)(-1) < 0) ? (((((_Value)1 << ((sizeof(_Value) * 8 - ((_Value)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(_Value)0);



      static const bool __is_signed = ((_Value)(-1) < 0);
      static const int __digits = (sizeof(_Value) * 8 - ((_Value)(-1) < 0));
    };

  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__min;

  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__max;

  template<typename _Value>
    const bool __numeric_traits_integer<_Value>::__is_signed;

  template<typename _Value>
    const int __numeric_traits_integer<_Value>::__digits;
# 99 "/usr/local/include/c++/4.9.0/ext/numeric_traits.h" 3
  template<typename _Value>
    struct __numeric_traits_floating
    {

      static const int __max_digits10 = (2 + (std::__are_same<_Value, float>::__value ? 24 : std::__are_same<_Value, double>::__value ? 53 : 64) * 643L / 2136);


      static const bool __is_signed = true;
      static const int __digits10 = (std::__are_same<_Value, float>::__value ? 6 : std::__are_same<_Value, double>::__value ? 15 : 18);
      static const int __max_exponent10 = (std::__are_same<_Value, float>::__value ? 38 : std::__are_same<_Value, double>::__value ? 308 : 4932);
    };

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_digits10;

  template<typename _Value>
    const bool __numeric_traits_floating<_Value>::__is_signed;

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__digits10;

  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_exponent10;

  template<typename _Value>
    struct __numeric_traits
    : public __conditional_type<std::__is_integer<_Value>::__value,
    __numeric_traits_integer<_Value>,
    __numeric_traits_floating<_Value> >::__type
    { };


}
# 64 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/stl_pair.h" 1 3
# 59 "/usr/local/include/c++/4.9.0/bits/stl_pair.h" 3
# 1 "/usr/local/include/c++/4.9.0/bits/move.h" 1 3
# 34 "/usr/local/include/c++/4.9.0/bits/move.h" 3
# 1 "/usr/local/include/c++/4.9.0/bits/concept_check.h" 1 3
# 33 "/usr/local/include/c++/4.9.0/bits/concept_check.h" 3
       
# 34 "/usr/local/include/c++/4.9.0/bits/concept_check.h" 3
# 35 "/usr/local/include/c++/4.9.0/bits/move.h" 2 3

namespace std __attribute__ ((__visibility__ ("default")))
{







  template<typename _Tp>
    inline _Tp*
    __addressof(_Tp& __r)
    {
      return reinterpret_cast<_Tp*>
 (&const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
    }


}
# 149 "/usr/local/include/c++/4.9.0/bits/move.h" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

# 164 "/usr/local/include/c++/4.9.0/bits/move.h" 3
  template<typename _Tp>
    inline void
    swap(_Tp& __a, _Tp& __b)




    {

     

      _Tp __tmp = (__a);
      __a = (__b);
      __b = (__tmp);
    }




  template<typename _Tp, size_t _Nm>
    inline void
    swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm])



    {
      for (size_t __n = 0; __n < _Nm; ++__n)
 swap(__a[__n], __b[__n]);
    }



}
# 60 "/usr/local/include/c++/4.9.0/bits/stl_pair.h" 2 3





namespace std __attribute__ ((__visibility__ ("default")))
{

# 95 "/usr/local/include/c++/4.9.0/bits/stl_pair.h" 3
  template<class _T1, class _T2>
    struct pair
    {
      typedef _T1 first_type;
      typedef _T2 second_type;

      _T1 first;
      _T2 second;





      pair()
      : first(), second() { }


      pair(const _T1& __a, const _T2& __b)
      : first(__a), second(__b) { }



      template<class _U1, class _U2>
 pair(const pair<_U1, _U2>& __p)
 : first(__p.first), second(__p.second) { }
# 209 "/usr/local/include/c++/4.9.0/bits/stl_pair.h" 3
    };


  template<class _T1, class _T2>
    inline bool
    operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first == __y.first && __x.second == __y.second; }


  template<class _T1, class _T2>
    inline bool
    operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first < __y.first
      || (!(__y.first < __x.first) && __x.second < __y.second); }


  template<class _T1, class _T2>
    inline bool
    operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x == __y); }


  template<class _T1, class _T2>
    inline bool
    operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __y < __x; }


  template<class _T1, class _T2>
    inline bool
    operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__y < __x); }


  template<class _T1, class _T2>
    inline bool
    operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x < __y); }
# 284 "/usr/local/include/c++/4.9.0/bits/stl_pair.h" 3
  template<class _T1, class _T2>
    inline pair<_T1, _T2>
    make_pair(_T1 __x, _T2 __y)
    { return pair<_T1, _T2>(__x, __y); }





}
# 65 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_types.h" 1 3
# 62 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_types.h" 3
       
# 63 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_types.h" 3







namespace std __attribute__ ((__visibility__ ("default")))
{

# 89 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_types.h" 3
  struct input_iterator_tag { };


  struct output_iterator_tag { };


  struct forward_iterator_tag : public input_iterator_tag { };



  struct bidirectional_iterator_tag : public forward_iterator_tag { };



  struct random_access_iterator_tag : public bidirectional_iterator_tag { };
# 116 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_types.h" 3
  template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
           typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {

      typedef _Category iterator_category;

      typedef _Tp value_type;

      typedef _Distance difference_type;

      typedef _Pointer pointer;

      typedef _Reference reference;
    };
# 162 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_types.h" 3
  template<typename _Iterator>
    struct iterator_traits
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type value_type;
      typedef typename _Iterator::difference_type difference_type;
      typedef typename _Iterator::pointer pointer;
      typedef typename _Iterator::reference reference;
    };



  template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef _Tp& reference;
    };


  template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef ptrdiff_t difference_type;
      typedef const _Tp* pointer;
      typedef const _Tp& reference;
    };





  template<typename _Iter>
    inline typename iterator_traits<_Iter>::iterator_category
    __iterator_category(const _Iter&)
    { return typename iterator_traits<_Iter>::iterator_category(); }





  template<typename _Iterator, bool _HasBase>
    struct _Iter_base
    {
      typedef _Iterator iterator_type;
      static iterator_type _S_base(_Iterator __it)
      { return __it; }
    };

  template<typename _Iterator>
    struct _Iter_base<_Iterator, true>
    {
      typedef typename _Iterator::iterator_type iterator_type;
      static iterator_type _S_base(_Iterator __it)
      { return __it.base(); }
    };
# 232 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_types.h" 3

}
# 66 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_funcs.h" 1 3
# 62 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_funcs.h" 3
       
# 63 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_funcs.h" 3


# 1 "/usr/local/include/c++/4.9.0/debug/debug.h" 1 3
# 46 "/usr/local/include/c++/4.9.0/debug/debug.h" 3
namespace std
{
  namespace __debug { }
}




namespace __gnu_debug
{
  using namespace std::__debug;
}
# 66 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_funcs.h" 2 3

namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last,
               input_iterator_tag)
    {

     

      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      while (__first != __last)
 {
   ++__first;
   ++__n;
 }
      return __n;
    }

  template<typename _RandomAccessIterator>
    inline typename iterator_traits<_RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
               random_access_iterator_tag)
    {

     

      return __last - __first;
    }
# 112 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_funcs.h" 3
  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    {

      return std::__distance(__first, __last,
        std::__iterator_category(__first));
    }

  template<typename _InputIterator, typename _Distance>
    inline void
    __advance(_InputIterator& __i, _Distance __n, input_iterator_tag)
    {

     
      ;
      while (__n--)
 ++__i;
    }

  template<typename _BidirectionalIterator, typename _Distance>
    inline void
    __advance(_BidirectionalIterator& __i, _Distance __n,
       bidirectional_iterator_tag)
    {

     

      if (__n > 0)
        while (__n--)
   ++__i;
      else
        while (__n++)
   --__i;
    }

  template<typename _RandomAccessIterator, typename _Distance>
    inline void
    __advance(_RandomAccessIterator& __i, _Distance __n,
              random_access_iterator_tag)
    {

     

      __i += __n;
    }
# 171 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_funcs.h" 3
  template<typename _InputIterator, typename _Distance>
    inline void
    advance(_InputIterator& __i, _Distance __n)
    {

      typename iterator_traits<_InputIterator>::difference_type __d = __n;
      std::__advance(__i, __d, std::__iterator_category(__i));
    }
# 202 "/usr/local/include/c++/4.9.0/bits/stl_iterator_base_funcs.h" 3

}
# 67 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 1 3
# 66 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
# 1 "/usr/local/include/c++/4.9.0/bits/ptr_traits.h" 1 3
# 67 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 2 3

namespace std __attribute__ ((__visibility__ ("default")))
{

# 96 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _Iterator>
    class reverse_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
        typename iterator_traits<_Iterator>::value_type,
        typename iterator_traits<_Iterator>::difference_type,
        typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator current;

      typedef iterator_traits<_Iterator> __traits_type;

    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef typename __traits_type::pointer pointer;
      typedef typename __traits_type::reference reference;







      reverse_iterator() : current() { }




      explicit
      reverse_iterator(iterator_type __x) : current(__x) { }




      reverse_iterator(const reverse_iterator& __x)
      : current(__x.current) { }





      template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x)
 : current(__x.base()) { }




      iterator_type
      base() const
      { return current; }
# 160 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
      reference
      operator*() const
      {
 _Iterator __tmp = current;
 return *--__tmp;
      }






      pointer
      operator->() const
      { return &(operator*()); }






      reverse_iterator&
      operator++()
      {
 --current;
 return *this;
      }






      reverse_iterator
      operator++(int)
      {
 reverse_iterator __tmp = *this;
 --current;
 return __tmp;
      }






      reverse_iterator&
      operator--()
      {
 ++current;
 return *this;
      }






      reverse_iterator
      operator--(int)
      {
 reverse_iterator __tmp = *this;
 ++current;
 return __tmp;
      }






      reverse_iterator
      operator+(difference_type __n) const
      { return reverse_iterator(current - __n); }







      reverse_iterator&
      operator+=(difference_type __n)
      {
 current -= __n;
 return *this;
      }






      reverse_iterator
      operator-(difference_type __n) const
      { return reverse_iterator(current + __n); }







      reverse_iterator&
      operator-=(difference_type __n)
      {
 current += __n;
 return *this;
      }






      reference
      operator[](difference_type __n) const
      { return *(*this + __n); }
    };
# 290 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _Iterator>
    inline bool
    operator==(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return __x.base() == __y.base(); }

  template<typename _Iterator>
    inline bool
    operator<(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y.base() < __x.base(); }

  template<typename _Iterator>
    inline bool
    operator!=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__x == __y); }

  template<typename _Iterator>
    inline bool
    operator>(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y < __x; }

  template<typename _Iterator>
    inline bool
    operator<=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__y < __x); }

  template<typename _Iterator>
    inline bool
    operator>=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__x < __y); }

  template<typename _Iterator>
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y.base() - __x.base(); }

  template<typename _Iterator>
    inline reverse_iterator<_Iterator>
    operator+(typename reverse_iterator<_Iterator>::difference_type __n,
       const reverse_iterator<_Iterator>& __x)
    { return reverse_iterator<_Iterator>(__x.base() - __n); }



  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator==(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return __x.base() == __y.base(); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y.base() < __x.base(); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator!=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__x == __y); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y < __x; }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__y < __x); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__x < __y); }

  template<typename _IteratorL, typename _IteratorR>







    inline typename reverse_iterator<_IteratorL>::difference_type
    operator-(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)

    { return __y.base() - __x.base(); }
# 402 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _Container>
    class back_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;

    public:

      typedef _Container container_type;


      explicit
      back_insert_iterator(_Container& __x) : container(&__x) { }
# 429 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
      back_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 container->push_back(__value);
 return *this;
      }
# 452 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
      back_insert_iterator&
      operator*()
      { return *this; }


      back_insert_iterator&
      operator++()
      { return *this; }


      back_insert_iterator
      operator++(int)
      { return *this; }
    };
# 478 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _Container>
    inline back_insert_iterator<_Container>
    back_inserter(_Container& __x)
    { return back_insert_iterator<_Container>(__x); }
# 493 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _Container>
    class front_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;

    public:

      typedef _Container container_type;


      explicit front_insert_iterator(_Container& __x) : container(&__x) { }
# 519 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
      front_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 container->push_front(__value);
 return *this;
      }
# 542 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
      front_insert_iterator&
      operator*()
      { return *this; }


      front_insert_iterator&
      operator++()
      { return *this; }


      front_insert_iterator
      operator++(int)
      { return *this; }
    };
# 568 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _Container>
    inline front_insert_iterator<_Container>
    front_inserter(_Container& __x)
    { return front_insert_iterator<_Container>(__x); }
# 587 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _Container>
    class insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
      typename _Container::iterator iter;

    public:

      typedef _Container container_type;





      insert_iterator(_Container& __x, typename _Container::iterator __i)
      : container(&__x), iter(__i) {}
# 630 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
      insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 iter = container->insert(iter, __value);
 ++iter;
 return *this;
      }
# 656 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
      insert_iterator&
      operator*()
      { return *this; }


      insert_iterator&
      operator++()
      { return *this; }


      insert_iterator&
      operator++(int)
      { return *this; }
    };
# 682 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _Container, typename _Iterator>
    inline insert_iterator<_Container>
    inserter(_Container& __x, _Iterator __i)
    {
      return insert_iterator<_Container>(__x,
      typename _Container::iterator(__i));
    }




}

namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

# 706 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  using std::iterator_traits;
  using std::iterator;
  template<typename _Iterator, typename _Container>
    class __normal_iterator
    {
    protected:
      _Iterator _M_current;

      typedef iterator_traits<_Iterator> __traits_type;

    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::iterator_category iterator_category;
      typedef typename __traits_type::value_type value_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef typename __traits_type::reference reference;
      typedef typename __traits_type::pointer pointer;

      __normal_iterator()
      : _M_current(_Iterator()) { }

      explicit
      __normal_iterator(const _Iterator& __i)
      : _M_current(__i) { }


      template<typename _Iter>
        __normal_iterator(const __normal_iterator<_Iter,
     typename __enable_if<
              (std::__are_same<_Iter, typename _Container::pointer>::__value),
        _Container>::__type>& __i)
        : _M_current(__i.base()) { }
# 749 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
      __normal_iterator
      _M_const_cast() const
      { return *this; }



      reference
      operator*() const
      { return *_M_current; }

      pointer
      operator->() const
      { return _M_current; }

      __normal_iterator&
      operator++()
      {
 ++_M_current;
 return *this;
      }

      __normal_iterator
      operator++(int)
      { return __normal_iterator(_M_current++); }


      __normal_iterator&
      operator--()
      {
 --_M_current;
 return *this;
      }

      __normal_iterator
      operator--(int)
      { return __normal_iterator(_M_current--); }


      reference
      operator[](difference_type __n) const
      { return _M_current[__n]; }

      __normal_iterator&
      operator+=(difference_type __n)
      { _M_current += __n; return *this; }

      __normal_iterator
      operator+(difference_type __n) const
      { return __normal_iterator(_M_current + __n); }

      __normal_iterator&
      operator-=(difference_type __n)
      { _M_current -= __n; return *this; }

      __normal_iterator
      operator-(difference_type __n) const
      { return __normal_iterator(_M_current - __n); }

      const _Iterator&
      base() const
      { return _M_current; }
    };
# 821 "/usr/local/include/c++/4.9.0/bits/stl_iterator.h" 3
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() == __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() == __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() != __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() != __rhs.base(); }


  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() < __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() < __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() > __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() > __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() <= __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() <= __rhs.base(); }

  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
   
    { return __lhs.base() >= __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() >= __rhs.base(); }





  template<typename _IteratorL, typename _IteratorR, typename _Container>







    inline typename __normal_iterator<_IteratorL, _Container>::difference_type
    operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)

    { return __lhs.base() - __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline typename __normal_iterator<_Iterator, _Container>::difference_type
    operator-(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
   
    { return __lhs.base() - __rhs.base(); }

  template<typename _Iterator, typename _Container>
    inline __normal_iterator<_Iterator, _Container>
    operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
       __n, const __normal_iterator<_Iterator, _Container>& __i)
   
    { return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }


}
# 68 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3



# 1 "/usr/local/include/c++/4.9.0/bits/predefined_ops.h" 1 3
# 33 "/usr/local/include/c++/4.9.0/bits/predefined_ops.h" 3
namespace __gnu_cxx
{
namespace __ops
{
  struct _Iter_less_iter
  {
    template<typename _Iterator1, typename _Iterator2>
      bool
      operator()(_Iterator1 __it1, _Iterator2 __it2) const
      { return *__it1 < *__it2; }
  };

  inline _Iter_less_iter
  __iter_less_iter()
  { return _Iter_less_iter(); }

  struct _Iter_less_val
  {
    template<typename _Iterator, typename _Value>
      bool
      operator()(_Iterator __it, _Value& __val) const
      { return *__it < __val; }
    };

  inline _Iter_less_val
  __iter_less_val()
  { return _Iter_less_val(); }

  inline _Iter_less_val
  __iter_comp_val(_Iter_less_iter)
  { return _Iter_less_val(); }

  struct _Val_less_iter
  {
    template<typename _Value, typename _Iterator>
      bool
      operator()(_Value& __val, _Iterator __it) const
      { return __val < *__it; }
    };

  inline _Val_less_iter
  __val_less_iter()
  { return _Val_less_iter(); }

  inline _Val_less_iter
  __val_comp_iter(_Iter_less_iter)
  { return _Val_less_iter(); }

  struct _Iter_equal_to_iter
  {
    template<typename _Iterator1, typename _Iterator2>
      bool
      operator()(_Iterator1 __it1, _Iterator2 __it2) const
      { return *__it1 == *__it2; }
    };

  inline _Iter_equal_to_iter
  __iter_equal_to_iter()
  { return _Iter_equal_to_iter(); }

  struct _Iter_equal_to_val
  {
    template<typename _Iterator, typename _Value>
      bool
      operator()(_Iterator __it, _Value& __val) const
      { return *__it == __val; }
    };

  inline _Iter_equal_to_val
  __iter_equal_to_val()
  { return _Iter_equal_to_val(); }

  inline _Iter_equal_to_val
  __iter_comp_val(_Iter_equal_to_iter)
  { return _Iter_equal_to_val(); }

  template<typename _Compare>
    struct _Iter_comp_iter
    {
      _Compare _M_comp;

      _Iter_comp_iter(_Compare __comp)
 : _M_comp(__comp)
      { }

      template<typename _Iterator1, typename _Iterator2>
        bool
        operator()(_Iterator1 __it1, _Iterator2 __it2)
        { return bool(_M_comp(*__it1, *__it2)); }
    };

  template<typename _Compare>
    inline _Iter_comp_iter<_Compare>
    __iter_comp_iter(_Compare __comp)
    { return _Iter_comp_iter<_Compare>(__comp); }

  template<typename _Compare>
    struct _Iter_comp_val
    {
      _Compare _M_comp;

      _Iter_comp_val(_Compare __comp)
 : _M_comp(__comp)
      { }

      template<typename _Iterator, typename _Value>
 bool
 operator()(_Iterator __it, _Value& __val)
 { return bool(_M_comp(*__it, __val)); }
    };

  template<typename _Compare>
   inline _Iter_comp_val<_Compare>
    __iter_comp_val(_Compare __comp)
    { return _Iter_comp_val<_Compare>(__comp); }

  template<typename _Compare>
    inline _Iter_comp_val<_Compare>
    __iter_comp_val(_Iter_comp_iter<_Compare> __comp)
    { return _Iter_comp_val<_Compare>(__comp._M_comp); }

  template<typename _Compare>
    struct _Val_comp_iter
    {
      _Compare _M_comp;

      _Val_comp_iter(_Compare __comp)
 : _M_comp(__comp)
      { }

      template<typename _Value, typename _Iterator>
 bool
 operator()(_Value& __val, _Iterator __it)
 { return bool(_M_comp(__val, *__it)); }
    };

  template<typename _Compare>
    inline _Val_comp_iter<_Compare>
    __val_comp_iter(_Compare __comp)
    { return _Val_comp_iter<_Compare>(__comp); }

  template<typename _Compare>
    inline _Val_comp_iter<_Compare>
    __val_comp_iter(_Iter_comp_iter<_Compare> __comp)
    { return _Val_comp_iter<_Compare>(__comp._M_comp); }

  template<typename _Value>
    struct _Iter_equals_val
    {
      _Value& _M_value;

      _Iter_equals_val(_Value& __value)
 : _M_value(__value)
      { }

      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return *__it == _M_value; }
    };

  template<typename _Value>
    inline _Iter_equals_val<_Value>
    __iter_equals_val(_Value& __val)
    { return _Iter_equals_val<_Value>(__val); }

  template<typename _Iterator1>
    struct _Iter_equals_iter
    {
      typename std::iterator_traits<_Iterator1>::reference _M_ref;

      _Iter_equals_iter(_Iterator1 __it1)
 : _M_ref(*__it1)
      { }

      template<typename _Iterator2>
 bool
 operator()(_Iterator2 __it2)
 { return *__it2 == _M_ref; }
    };

  template<typename _Iterator>
    inline _Iter_equals_iter<_Iterator>
    __iter_comp_iter(_Iter_equal_to_iter, _Iterator __it)
    { return _Iter_equals_iter<_Iterator>(__it); }

  template<typename _Predicate>
    struct _Iter_pred
    {
      _Predicate _M_pred;

      _Iter_pred(_Predicate __pred)
 : _M_pred(__pred)
      { }

      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return bool(_M_pred(*__it)); }
    };

  template<typename _Predicate>
    inline _Iter_pred<_Predicate>
    __pred_iter(_Predicate __pred)
    { return _Iter_pred<_Predicate>(__pred); }

  template<typename _Compare, typename _Value>
    struct _Iter_comp_to_val
    {
      _Compare _M_comp;
      _Value& _M_value;

      _Iter_comp_to_val(_Compare __comp, _Value& __value)
 : _M_comp(__comp), _M_value(__value)
      { }

      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return bool(_M_comp(*__it, _M_value)); }
    };

  template<typename _Compare, typename _Value>
    _Iter_comp_to_val<_Compare, _Value>
    __iter_comp_val(_Compare __comp, _Value &__val)
    { return _Iter_comp_to_val<_Compare, _Value>(__comp, __val); }

  template<typename _Compare, typename _Iterator1>
    struct _Iter_comp_to_iter
    {
      _Compare _M_comp;
      typename std::iterator_traits<_Iterator1>::reference _M_ref;

      _Iter_comp_to_iter(_Compare __comp, _Iterator1 __it1)
 : _M_comp(__comp), _M_ref(*__it1)
      { }

      template<typename _Iterator2>
 bool
 operator()(_Iterator2 __it2)
 { return bool(_M_comp(*__it2, _M_ref)); }
    };

  template<typename _Compare, typename _Iterator>
    inline _Iter_comp_to_iter<_Compare, _Iterator>
    __iter_comp_iter(_Iter_comp_iter<_Compare> __comp, _Iterator __it)
    { return _Iter_comp_to_iter<_Compare, _Iterator>(__comp._M_comp, __it); }

  template<typename _Predicate>
    struct _Iter_negate
    {
      _Predicate _M_pred;

      _Iter_negate(_Predicate __pred)
 : _M_pred(__pred)
      { }

      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return !bool(_M_pred(*__it)); }
    };

  template<typename _Predicate>
    inline _Iter_negate<_Predicate>
    __negate(_Iter_pred<_Predicate> __pred)
    { return _Iter_negate<_Predicate>(__pred._M_pred); }

}
}
# 72 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 2 3

namespace std __attribute__ ((__visibility__ ("default")))
{






  template<bool _BoolType>
    struct __iter_swap
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void
        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
          typedef typename iterator_traits<_ForwardIterator1>::value_type
            _ValueType1;
          _ValueType1 __tmp = (*__a);
          *__a = (*__b);
          *__b = (__tmp);
 }
    };

  template<>
    struct __iter_swap<true>
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void
        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
          swap(*__a, *__b);
        }
    };
# 118 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline void
    iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
    {

     

     



      typedef typename iterator_traits<_ForwardIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_ForwardIterator2>::value_type
 _ValueType2;

     

     


      typedef typename iterator_traits<_ForwardIterator1>::reference
 _ReferenceType1;
      typedef typename iterator_traits<_ForwardIterator2>::reference
 _ReferenceType2;
      std::__iter_swap<__are_same<_ValueType1, _ValueType2>::__value
 && __are_same<_ValueType1&, _ReferenceType1>::__value
 && __are_same<_ValueType2&, _ReferenceType2>::__value>::
 iter_swap(__a, __b);



    }
# 164 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator2
    swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
  _ForwardIterator2 __first2)
    {

     

     

      ;

      for (; __first1 != __last1; ++__first1, ++__first2)
 std::iter_swap(__first1, __first2);
      return __first2;
    }
# 192 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _Tp>
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b)
    {

     

      if (__b < __a)
 return __b;
      return __a;
    }
# 215 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _Tp>
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b)
    {

     

      if (__a < __b)
 return __b;
      return __a;
    }
# 238 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _Tp, typename _Compare>
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {

      if (__comp(__b, __a))
 return __b;
      return __a;
    }
# 259 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _Tp, typename _Compare>
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {

      if (__comp(__a, __b))
 return __b;
      return __a;
    }



  template<typename _Iterator>
    struct _Niter_base
    : _Iter_base<_Iterator, __is_normal_iterator<_Iterator>::__value>
    { };

  template<typename _Iterator>
    inline typename _Niter_base<_Iterator>::iterator_type
    __niter_base(_Iterator __it)
    { return std::_Niter_base<_Iterator>::_S_base(__it); }


  template<typename _Iterator>
    struct _Miter_base
    : _Iter_base<_Iterator, __is_move_iterator<_Iterator>::__value>
    { };

  template<typename _Iterator>
    inline typename _Miter_base<_Iterator>::iterator_type
    __miter_base(_Iterator __it)
    { return std::_Miter_base<_Iterator>::_S_base(__it); }







  template<bool, bool, typename>
    struct __copy_move
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   for (; __first != __last; ++__result, ++__first)
     *__result = *__first;
   return __result;
 }
    };
# 326 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<>
    struct __copy_move<false, false, random_access_iterator_tag>
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   typedef typename iterator_traits<_II>::difference_type _Distance;
   for(_Distance __n = __last - __first; __n > 0; --__n)
     {
       *__result = *__first;
       ++__first;
       ++__result;
     }
   return __result;
 }
    };
# 364 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<bool _IsMove>
    struct __copy_move<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_m(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {





   const ptrdiff_t _Num = __last - __first;
   if (_Num)
     __builtin_memmove(__result, __first, sizeof(_Tp) * _Num);
   return __result + _Num;
 }
    };

  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a(_II __first, _II __last, _OI __result)
    {
      typedef typename iterator_traits<_II>::value_type _ValueTypeI;
      typedef typename iterator_traits<_OI>::value_type _ValueTypeO;
      typedef typename iterator_traits<_II>::iterator_category _Category;
      const bool __simple = (__is_trivial(_ValueTypeI)
                      && __is_pointer<_II>::__value
                      && __is_pointer<_OI>::__value
        && __are_same<_ValueTypeI, _ValueTypeO>::__value);

      return std::__copy_move<_IsMove, __simple,
                       _Category>::__copy_m(__first, __last, __result);
    }



  template<typename _CharT>
    struct char_traits;

  template<typename _CharT, typename _Traits>
    class istreambuf_iterator;

  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator;

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
      ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(_CharT*, _CharT*,
     ostreambuf_iterator<_CharT, char_traits<_CharT> >);

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
      ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(const _CharT*, const _CharT*,
     ostreambuf_iterator<_CharT, char_traits<_CharT> >);

  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
        _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT, char_traits<_CharT> >,
     istreambuf_iterator<_CharT, char_traits<_CharT> >, _CharT*);

  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a2(_II __first, _II __last, _OI __result)
    {
      return _OI(std::__copy_move_a<_IsMove>(std::__niter_base(__first),
          std::__niter_base(__last),
          std::__niter_base(__result)));
    }
# 454 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _II, typename _OI>
    inline _OI
    copy(_II __first, _II __last, _OI __result)
    {

     
     

      ;

      return (std::__copy_move_a2<__is_move_iterator<_II>::__value>
       (std::__miter_base(__first), std::__miter_base(__last),
        __result));
    }
# 506 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<bool, bool, typename>
    struct __copy_move_backward
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   while (__first != __last)
     *--__result = *--__last;
   return __result;
 }
    };
# 534 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<>
    struct __copy_move_backward<false, false, random_access_iterator_tag>
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   typename iterator_traits<_BI1>::difference_type __n;
   for (__n = __last - __first; __n > 0; --__n)
     *--__result = *--__last;
   return __result;
 }
    };
# 564 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<bool _IsMove>
    struct __copy_move_backward<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_move_b(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {





   const ptrdiff_t _Num = __last - __first;
   if (_Num)
     __builtin_memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
   return __result - _Num;
 }
    };

  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      typedef typename iterator_traits<_BI1>::value_type _ValueType1;
      typedef typename iterator_traits<_BI2>::value_type _ValueType2;
      typedef typename iterator_traits<_BI1>::iterator_category _Category;
      const bool __simple = (__is_trivial(_ValueType1)
                      && __is_pointer<_BI1>::__value
                      && __is_pointer<_BI2>::__value
        && __are_same<_ValueType1, _ValueType2>::__value);

      return std::__copy_move_backward<_IsMove, __simple,
                                _Category>::__copy_move_b(__first,
         __last,
         __result);
    }

  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a2(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      return _BI2(std::__copy_move_backward_a<_IsMove>
    (std::__niter_base(__first), std::__niter_base(__last),
     std::__niter_base(__result)));
    }
# 628 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _BI1, typename _BI2>
    inline _BI2
    copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
    {

     
     
     


      ;

      return (std::__copy_move_backward_a2<__is_move_iterator<_BI1>::__value>
       (std::__miter_base(__first), std::__miter_base(__last),
        __result));
    }
# 686 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
       const _Tp& __value)
    {
      for (; __first != __last; ++__first)
 *__first = __value;
    }

  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (; __first != __last; ++__first)
 *__first = __tmp;
    }


  template<typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, void>::__type
    __fill_a(_Tp* __first, _Tp* __last, const _Tp& __c)
    {
      const _Tp __tmp = __c;
      __builtin_memset(__first, static_cast<unsigned char>(__tmp),
         __last - __first);
    }
# 730 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline void
    fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
    {

     

      ;

      std::__fill_a(std::__niter_base(__first), std::__niter_base(__last),
      __value);
    }

  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      for (__decltype(__n + 0) __niter = __n;
    __niter > 0; --__niter, ++__first)
 *__first = __value;
      return __first;
    }

  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (__decltype(__n + 0) __niter = __n;
    __niter > 0; --__niter, ++__first)
 *__first = __tmp;
      return __first;
    }

  template<typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, _Tp*>::__type
    __fill_n_a(_Tp* __first, _Size __n, const _Tp& __c)
    {
      std::__fill_a(__first, __first + __n, __c);
      return __first + __n;
    }
# 790 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _OI, typename _Size, typename _Tp>
    inline _OI
    fill_n(_OI __first, _Size __n, const _Tp& __value)
    {

     

      return _OI(std::__fill_n_a(std::__niter_base(__first), __n, __value));
    }

  template<bool _BoolType>
    struct __equal
    {
      template<typename _II1, typename _II2>
        static bool
        equal(_II1 __first1, _II1 __last1, _II2 __first2)
        {
   for (; __first1 != __last1; ++__first1, ++__first2)
     if (!(*__first1 == *__first2))
       return false;
   return true;
 }
    };

  template<>
    struct __equal<true>
    {
      template<typename _Tp>
        static bool
        equal(const _Tp* __first1, const _Tp* __last1, const _Tp* __first2)
        {
   return !__builtin_memcmp(__first1, __first2, sizeof(_Tp)
       * (__last1 - __first1));
 }
    };

  template<typename _II1, typename _II2>
    inline bool
    __equal_aux(_II1 __first1, _II1 __last1, _II2 __first2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple = ((__is_integer<_ValueType1>::__value
         || __is_pointer<_ValueType1>::__value)
                      && __is_pointer<_II1>::__value
                      && __is_pointer<_II2>::__value
        && __are_same<_ValueType1, _ValueType2>::__value);

      return std::__equal<__simple>::equal(__first1, __last1, __first2);
    }

  template<typename, typename>
    struct __lc_rai
    {
      template<typename _II1, typename _II2>
        static _II1
        __newlast1(_II1, _II1 __last1, _II2, _II2)
        { return __last1; }

      template<typename _II>
        static bool
        __cnd2(_II __first, _II __last)
        { return __first != __last; }
    };

  template<>
    struct __lc_rai<random_access_iterator_tag, random_access_iterator_tag>
    {
      template<typename _RAI1, typename _RAI2>
        static _RAI1
        __newlast1(_RAI1 __first1, _RAI1 __last1,
     _RAI2 __first2, _RAI2 __last2)
        {
   const typename iterator_traits<_RAI1>::difference_type
     __diff1 = __last1 - __first1;
   const typename iterator_traits<_RAI2>::difference_type
     __diff2 = __last2 - __first2;
   return __diff2 < __diff1 ? __first1 + __diff2 : __last1;
 }

      template<typename _RAI>
        static bool
        __cnd2(_RAI, _RAI)
        { return true; }
    };

  template<typename _II1, typename _II2, typename _Compare>
    bool
    __lexicographical_compare_impl(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2,
       _Compare __comp)
    {
      typedef typename iterator_traits<_II1>::iterator_category _Category1;
      typedef typename iterator_traits<_II2>::iterator_category _Category2;
      typedef std::__lc_rai<_Category1, _Category2> __rai_type;

      __last1 = __rai_type::__newlast1(__first1, __last1, __first2, __last2);
      for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
    ++__first1, ++__first2)
 {
   if (__comp(__first1, __first2))
     return true;
   if (__comp(__first2, __first1))
     return false;
 }
      return __first1 == __last1 && __first2 != __last2;
    }

  template<bool _BoolType>
    struct __lexicographical_compare
    {
      template<typename _II1, typename _II2>
        static bool __lc(_II1, _II1, _II2, _II2);
    };

  template<bool _BoolType>
    template<typename _II1, typename _II2>
      bool
      __lexicographical_compare<_BoolType>::
      __lc(_II1 __first1, _II1 __last1, _II2 __first2, _II2 __last2)
      {
 return std::__lexicographical_compare_impl(__first1, __last1,
         __first2, __last2,
     __gnu_cxx::__ops::__iter_less_iter());
      }

  template<>
    struct __lexicographical_compare<true>
    {
      template<typename _Tp, typename _Up>
        static bool
        __lc(const _Tp* __first1, const _Tp* __last1,
      const _Up* __first2, const _Up* __last2)
 {
   const size_t __len1 = __last1 - __first1;
   const size_t __len2 = __last2 - __first2;
   const int __result = __builtin_memcmp(__first1, __first2,
      std::min(__len1, __len2));
   return __result != 0 ? __result < 0 : __len1 < __len2;
 }
    };

  template<typename _II1, typename _II2>
    inline bool
    __lexicographical_compare_aux(_II1 __first1, _II1 __last1,
      _II2 __first2, _II2 __last2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple =
 (__is_byte<_ValueType1>::__value && __is_byte<_ValueType2>::__value
  && !__gnu_cxx::__numeric_traits<_ValueType1>::__is_signed
  && !__gnu_cxx::__numeric_traits<_ValueType2>::__is_signed
  && __is_pointer<_II1>::__value
  && __is_pointer<_II2>::__value);

      return std::__lexicographical_compare<__simple>::__lc(__first1, __last1,
           __first2, __last2);
    }

  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    __lower_bound(_ForwardIterator __first, _ForwardIterator __last,
    const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
 {
   _DistanceType __half = __len >> 1;
   _ForwardIterator __middle = __first;
   std::advance(__middle, __half);
   if (__comp(__middle, __val))
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
   else
     __len = __half;
 }
      return __first;
    }
# 988 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val)
    {

     
     

      ;

      return std::__lower_bound(__first, __last, __val,
    __gnu_cxx::__ops::__iter_less_val());
    }



  inline int
  __lg(int __n)
  { return sizeof(int) * 8 - 1 - __builtin_clz(__n); }

  inline unsigned
  __lg(unsigned __n)
  { return sizeof(int) * 8 - 1 - __builtin_clz(__n); }

  inline long
  __lg(long __n)
  { return sizeof(long) * 8 - 1 - __builtin_clzl(__n); }

  inline unsigned long
  __lg(unsigned long __n)
  { return sizeof(long) * 8 - 1 - __builtin_clzl(__n); }

  inline long long
  __lg(long long __n)
  { return sizeof(long long) * 8 - 1 - __builtin_clzll(__n); }

  inline unsigned long long
  __lg(unsigned long long __n)
  { return sizeof(long long) * 8 - 1 - __builtin_clzll(__n); }




# 1045 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _II1, typename _II2>
    inline bool
    equal(_II1 __first1, _II1 __last1, _II2 __first2)
    {

     
     
     


      ;

      return std::__equal_aux(std::__niter_base(__first1),
         std::__niter_base(__last1),
         std::__niter_base(__first2));
    }
# 1077 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    inline bool
    equal(_IIter1 __first1, _IIter1 __last1,
   _IIter2 __first2, _BinaryPredicate __binary_pred)
    {

     
     
      ;

      for (; __first1 != __last1; ++__first1, ++__first2)
 if (!bool(__binary_pred(*__first1, *__first2)))
   return false;
      return true;
    }
# 1202 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _II1, typename _II2>
    inline bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2)
    {





     
     
     
     
      ;
      ;

      return std::__lexicographical_compare_aux(std::__niter_base(__first1),
      std::__niter_base(__last1),
      std::__niter_base(__first2),
      std::__niter_base(__last2));
    }
# 1238 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _II1, typename _II2, typename _Compare>
    inline bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2, _Compare __comp)
    {

     
     
      ;
      ;

      return std::__lexicographical_compare_impl
 (__first1, __last1, __first2, __last2,
  __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }

  template<typename _InputIterator1, typename _InputIterator2,
    typename _BinaryPredicate>
    pair<_InputIterator1, _InputIterator2>
    __mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
        _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {
      while (__first1 != __last1 && __binary_pred(__first1, __first2))
        {
   ++__first1;
   ++__first2;
        }
      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
    }
# 1281 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _InputIterator1, typename _InputIterator2>
    inline pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2)
    {

     
     
     


      ;

      return std::__mismatch(__first1, __last1, __first2,
        __gnu_cxx::__ops::__iter_equal_to_iter());
    }
# 1314 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3
  template<typename _InputIterator1, typename _InputIterator2,
    typename _BinaryPredicate>
    inline pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {

     
     
      ;

      return std::__mismatch(__first1, __last1, __first2,
 __gnu_cxx::__ops::__iter_comp_iter(__binary_pred));
    }
# 1414 "/usr/local/include/c++/4.9.0/bits/stl_algobase.h" 3

}
# 62 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/allocator.h" 1 3
# 46 "/usr/local/include/c++/4.9.0/bits/allocator.h" 3
# 1 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++allocator.h" 1 3
# 33 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++allocator.h" 3
# 1 "/usr/local/include/c++/4.9.0/ext/new_allocator.h" 1 3
# 33 "/usr/local/include/c++/4.9.0/ext/new_allocator.h" 3
# 1 "/usr/local/include/c++/4.9.0/new" 1 3
# 37 "/usr/local/include/c++/4.9.0/new" 3
       
# 38 "/usr/local/include/c++/4.9.0/new" 3


# 1 "/usr/local/include/c++/4.9.0/exception" 1 3
# 33 "/usr/local/include/c++/4.9.0/exception" 3
       
# 34 "/usr/local/include/c++/4.9.0/exception" 3

#pragma GCC visibility push(default)


# 1 "/usr/local/include/c++/4.9.0/bits/atomic_lockfree_defines.h" 1 3
# 33 "/usr/local/include/c++/4.9.0/bits/atomic_lockfree_defines.h" 3
       
# 34 "/usr/local/include/c++/4.9.0/bits/atomic_lockfree_defines.h" 3
# 39 "/usr/local/include/c++/4.9.0/exception" 2 3

extern "C++" {

namespace std
{
# 60 "/usr/local/include/c++/4.9.0/exception" 3
  class exception
  {
  public:
    exception() throw() { }
    virtual ~exception() throw();



    virtual const char* what() const throw();
  };



  class bad_exception : public exception
  {
  public:
    bad_exception() throw() { }



    virtual ~bad_exception() throw();


    virtual const char* what() const throw();
  };


  typedef void (*terminate_handler) ();


  typedef void (*unexpected_handler) ();


  terminate_handler set_terminate(terminate_handler) throw();
# 102 "/usr/local/include/c++/4.9.0/exception" 3
  void terminate() throw() __attribute__ ((__noreturn__));


  unexpected_handler set_unexpected(unexpected_handler) throw();
# 114 "/usr/local/include/c++/4.9.0/exception" 3
  void unexpected() __attribute__ ((__noreturn__));
# 127 "/usr/local/include/c++/4.9.0/exception" 3
  bool uncaught_exception() throw() __attribute__ ((__pure__));


}

namespace __gnu_cxx
{

# 152 "/usr/local/include/c++/4.9.0/exception" 3
  void __verbose_terminate_handler();


}

}

#pragma GCC visibility pop
# 41 "/usr/local/include/c++/4.9.0/new" 2 3

#pragma GCC visibility push(default)

extern "C++" {

namespace std
{






  class bad_alloc : public exception
  {
  public:
    bad_alloc() throw() { }



    virtual ~bad_alloc() throw();


    virtual const char* what() const throw();
  };
# 85 "/usr/local/include/c++/4.9.0/new" 3
  class bad_array_length : public bad_alloc
  {
  public:
    bad_array_length() throw() { };



    virtual ~bad_array_length() throw();


    virtual const char* what() const throw();
  };


  struct nothrow_t { };

  extern const nothrow_t nothrow;



  typedef void (*new_handler)();



  new_handler set_new_handler(new_handler) throw();





}
# 128 "/usr/local/include/c++/4.9.0/new" 3
void* operator new(std::size_t) throw(std::bad_alloc)
  __attribute__((__externally_visible__));
void* operator new[](std::size_t) throw(std::bad_alloc)
  __attribute__((__externally_visible__));
void operator delete(void*) throw()
  __attribute__((__externally_visible__));
void operator delete[](void*) throw()
  __attribute__((__externally_visible__));
void* operator new(std::size_t, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void* operator new[](std::size_t, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void operator delete(void*, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void operator delete[](void*, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));


inline void* operator new(std::size_t, void* __p) throw()
{ return __p; }
inline void* operator new[](std::size_t, void* __p) throw()
{ return __p; }


inline void operator delete (void*, void*) throw() { }
inline void operator delete[](void*, void*) throw() { }

}

#pragma GCC visibility pop
# 34 "/usr/local/include/c++/4.9.0/ext/new_allocator.h" 2 3






namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  using std::size_t;
  using std::ptrdiff_t;
# 57 "/usr/local/include/c++/4.9.0/ext/new_allocator.h" 3
  template<typename _Tp>
    class new_allocator
    {
    public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp& reference;
      typedef const _Tp& const_reference;
      typedef _Tp value_type;

      template<typename _Tp1>
        struct rebind
        { typedef new_allocator<_Tp1> other; };







      new_allocator() throw() { }

      new_allocator(const new_allocator&) throw() { }

      template<typename _Tp1>
        new_allocator(const new_allocator<_Tp1>&) throw() { }

      ~new_allocator() throw() { }

      pointer
      address(reference __x) const
      { return std::__addressof(__x); }

      const_pointer
      address(const_reference __x) const
      { return std::__addressof(__x); }



      pointer
      allocate(size_type __n, const void* = 0)
      {
 if (__n > this->max_size())
   std::__throw_bad_alloc();

 return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }


      void
      deallocate(pointer __p, size_type)
      { ::operator delete(__p); }

      size_type
      max_size() const throw()
      { return size_t(-1) / sizeof(_Tp); }
# 128 "/usr/local/include/c++/4.9.0/ext/new_allocator.h" 3
      void
      construct(pointer __p, const _Tp& __val)
      { ::new((void *)__p) _Tp(__val); }

      void
      destroy(pointer __p) { __p->~_Tp(); }

    };

  template<typename _Tp>
    inline bool
    operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return true; }

  template<typename _Tp>
    inline bool
    operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return false; }


}
# 34 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++allocator.h" 2 3
# 47 "/usr/local/include/c++/4.9.0/bits/allocator.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/memoryfwd.h" 1 3
# 46 "/usr/local/include/c++/4.9.0/bits/memoryfwd.h" 3
       
# 47 "/usr/local/include/c++/4.9.0/bits/memoryfwd.h" 3



namespace std __attribute__ ((__visibility__ ("default")))
{

# 63 "/usr/local/include/c++/4.9.0/bits/memoryfwd.h" 3
  template<typename>
    class allocator;

  template<>
    class allocator<void>;


  template<typename, typename>
    struct uses_allocator;




}
# 48 "/usr/local/include/c++/4.9.0/bits/allocator.h" 2 3




namespace std __attribute__ ((__visibility__ ("default")))
{








  template<>
    class allocator<void>
    {
    public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef void* pointer;
      typedef const void* const_pointer;
      typedef void value_type;

      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };






    };
# 91 "/usr/local/include/c++/4.9.0/bits/allocator.h" 3
  template<typename _Tp>
    class allocator: public __gnu_cxx::new_allocator<_Tp>
    {
   public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp& reference;
      typedef const _Tp& const_reference;
      typedef _Tp value_type;

      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };







      allocator() throw() { }

      allocator(const allocator& __a) throw()
      : __gnu_cxx::new_allocator<_Tp>(__a) { }

      template<typename _Tp1>
        allocator(const allocator<_Tp1>&) throw() { }

      ~allocator() throw() { }


    };

  template<typename _T1, typename _T2>
    inline bool
    operator==(const allocator<_T1>&, const allocator<_T2>&)
    { return true; }

  template<typename _Tp>
    inline bool
    operator==(const allocator<_Tp>&, const allocator<_Tp>&)
    { return true; }

  template<typename _T1, typename _T2>
    inline bool
    operator!=(const allocator<_T1>&, const allocator<_T2>&)
    { return false; }

  template<typename _Tp>
    inline bool
    operator!=(const allocator<_Tp>&, const allocator<_Tp>&)
    { return false; }






  extern template class allocator<char>;
  extern template class allocator<wchar_t>;






  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_swap
    { static void _S_do_it(_Alloc&, _Alloc&) { } };

  template<typename _Alloc>
    struct __alloc_swap<_Alloc, false>
    {
      static void
      _S_do_it(_Alloc& __one, _Alloc& __two)
      {

 if (__one != __two)
   swap(__one, __two);
      }
    };


  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_neq
    {
      static bool
      _S_do_it(const _Alloc&, const _Alloc&)
      { return false; }
    };

  template<typename _Alloc>
    struct __alloc_neq<_Alloc, false>
    {
      static bool
      _S_do_it(const _Alloc& __one, const _Alloc& __two)
      { return __one != __two; }
    };
# 218 "/usr/local/include/c++/4.9.0/bits/allocator.h" 3

}
# 63 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 1 3
# 63 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

# 104 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
  template<typename _Arg, typename _Result>
    struct unary_function
    {

      typedef _Arg argument_type;


      typedef _Result result_type;
    };




  template<typename _Arg1, typename _Arg2, typename _Result>
    struct binary_function
    {

      typedef _Arg1 first_argument_type;


      typedef _Arg2 second_argument_type;


      typedef _Result result_type;
    };
# 166 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
  template<typename _Tp>
    struct plus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x + __y; }
    };


  template<typename _Tp>
    struct minus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x - __y; }
    };


  template<typename _Tp>
    struct multiplies : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x * __y; }
    };


  template<typename _Tp>
    struct divides : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x / __y; }
    };


  template<typename _Tp>
    struct modulus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x % __y; }
    };


  template<typename _Tp>
    struct negate : public unary_function<_Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x) const
      { return -__x; }
    };
# 335 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
  template<typename _Tp>
    struct equal_to : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x == __y; }
    };


  template<typename _Tp>
    struct not_equal_to : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x != __y; }
    };


  template<typename _Tp>
    struct greater : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x > __y; }
    };


  template<typename _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x < __y; }
    };


  template<typename _Tp>
    struct greater_equal : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x >= __y; }
    };


  template<typename _Tp>
    struct less_equal : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x <= __y; }
    };
# 496 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
  template<typename _Tp>
    struct logical_and : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x && __y; }
    };


  template<typename _Tp>
    struct logical_or : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x || __y; }
    };


  template<typename _Tp>
    struct logical_not : public unary_function<_Tp, bool>
    {
      bool
      operator()(const _Tp& __x) const
      { return !__x; }
    };
# 583 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
  template<typename _Tp>
    struct bit_and : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x & __y; }
    };

  template<typename _Tp>
    struct bit_or : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x | __y; }
    };

  template<typename _Tp>
    struct bit_xor : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x ^ __y; }
    };

  template<typename _Tp>
    struct bit_not : public unary_function<_Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x) const
      { return ~__x; }
    };
# 699 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
  template<typename _Predicate>
    class unary_negate
    : public unary_function<typename _Predicate::argument_type, bool>
    {
    protected:
      _Predicate _M_pred;

    public:
      explicit
      unary_negate(const _Predicate& __x) : _M_pred(__x) { }

      bool
      operator()(const typename _Predicate::argument_type& __x) const
      { return !_M_pred(__x); }
    };


  template<typename _Predicate>
    inline unary_negate<_Predicate>
    not1(const _Predicate& __pred)
    { return unary_negate<_Predicate>(__pred); }


  template<typename _Predicate>
    class binary_negate
    : public binary_function<typename _Predicate::first_argument_type,
        typename _Predicate::second_argument_type, bool>
    {
    protected:
      _Predicate _M_pred;

    public:
      explicit
      binary_negate(const _Predicate& __x) : _M_pred(__x) { }

      bool
      operator()(const typename _Predicate::first_argument_type& __x,
   const typename _Predicate::second_argument_type& __y) const
      { return !_M_pred(__x, __y); }
    };


  template<typename _Predicate>
    inline binary_negate<_Predicate>
    not2(const _Predicate& __pred)
    { return binary_negate<_Predicate>(__pred); }
# 770 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
  template<typename _Arg, typename _Result>
    class pointer_to_unary_function : public unary_function<_Arg, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg);

    public:
      pointer_to_unary_function() { }

      explicit
      pointer_to_unary_function(_Result (*__x)(_Arg))
      : _M_ptr(__x) { }

      _Result
      operator()(_Arg __x) const
      { return _M_ptr(__x); }
    };


  template<typename _Arg, typename _Result>
    inline pointer_to_unary_function<_Arg, _Result>
    ptr_fun(_Result (*__x)(_Arg))
    { return pointer_to_unary_function<_Arg, _Result>(__x); }


  template<typename _Arg1, typename _Arg2, typename _Result>
    class pointer_to_binary_function
    : public binary_function<_Arg1, _Arg2, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg1, _Arg2);

    public:
      pointer_to_binary_function() { }

      explicit
      pointer_to_binary_function(_Result (*__x)(_Arg1, _Arg2))
      : _M_ptr(__x) { }

      _Result
      operator()(_Arg1 __x, _Arg2 __y) const
      { return _M_ptr(__x, __y); }
    };


  template<typename _Arg1, typename _Arg2, typename _Result>
    inline pointer_to_binary_function<_Arg1, _Arg2, _Result>
    ptr_fun(_Result (*__x)(_Arg1, _Arg2))
    { return pointer_to_binary_function<_Arg1, _Arg2, _Result>(__x); }


  template<typename _Tp>
    struct _Identity
    : public unary_function<_Tp,_Tp>
    {
      _Tp&
      operator()(_Tp& __x) const
      { return __x; }

      const _Tp&
      operator()(const _Tp& __x) const
      { return __x; }
    };

  template<typename _Pair>
    struct _Select1st
    : public unary_function<_Pair, typename _Pair::first_type>
    {
      typename _Pair::first_type&
      operator()(_Pair& __x) const
      { return __x.first; }

      const typename _Pair::first_type&
      operator()(const _Pair& __x) const
      { return __x.first; }
# 857 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
    };

  template<typename _Pair>
    struct _Select2nd
    : public unary_function<_Pair, typename _Pair::second_type>
    {
      typename _Pair::second_type&
      operator()(_Pair& __x) const
      { return __x.second; }

      const typename _Pair::second_type&
      operator()(const _Pair& __x) const
      { return __x.second; }
    };
# 890 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 3
  template<typename _Ret, typename _Tp>
    class mem_fun_t : public unary_function<_Tp*, _Ret>
    {
    public:
      explicit
      mem_fun_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp* __p) const
      { return (__p->*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)();
    };



  template<typename _Ret, typename _Tp>
    class const_mem_fun_t : public unary_function<const _Tp*, _Ret>
    {
    public:
      explicit
      const_mem_fun_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp* __p) const
      { return (__p->*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)() const;
    };



  template<typename _Ret, typename _Tp>
    class mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      mem_fun_ref_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp& __r) const
      { return (__r.*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)();
  };



  template<typename _Ret, typename _Tp>
    class const_mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      const_mem_fun_ref_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp& __r) const
      { return (__r.*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)() const;
    };



  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_t : public binary_function<_Tp*, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };



  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_t : public binary_function<const _Tp*, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };



  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };



  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }

      _Ret
      operator()(const _Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }

    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };



  template<typename _Ret, typename _Tp>
    inline mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)())
    { return mem_fun_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline const_mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)())
    { return mem_fun_ref_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp>
    inline const_mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_ref_t<_Ret, _Tp>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }

  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }




}


# 1 "/usr/local/include/c++/4.9.0/backward/binders.h" 1 3
# 59 "/usr/local/include/c++/4.9.0/backward/binders.h" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

# 103 "/usr/local/include/c++/4.9.0/backward/binders.h" 3
  template<typename _Operation>
    class binder1st
    : public unary_function<typename _Operation::second_argument_type,
       typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::first_argument_type value;

    public:
      binder1st(const _Operation& __x,
  const typename _Operation::first_argument_type& __y)
      : op(__x), value(__y) { }

      typename _Operation::result_type
      operator()(const typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }



      typename _Operation::result_type
      operator()(typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }
    } ;


  template<typename _Operation, typename _Tp>
    inline binder1st<_Operation>
    bind1st(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::first_argument_type _Arg1_type;
      return binder1st<_Operation>(__fn, _Arg1_type(__x));
    }


  template<typename _Operation>
    class binder2nd
    : public unary_function<typename _Operation::first_argument_type,
       typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::second_argument_type value;

    public:
      binder2nd(const _Operation& __x,
  const typename _Operation::second_argument_type& __y)
      : op(__x), value(__y) { }

      typename _Operation::result_type
      operator()(const typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }



      typename _Operation::result_type
      operator()(typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }
    } ;


  template<typename _Operation, typename _Tp>
    inline binder2nd<_Operation>
    bind2nd(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::second_argument_type _Arg2_type;
      return binder2nd<_Operation>(__fn, _Arg2_type(__x));
    }



}
# 1081 "/usr/local/include/c++/4.9.0/bits/stl_function.h" 2 3
# 64 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 2 3

# 1 "/usr/local/include/c++/4.9.0/ext/alloc_traits.h" 1 3
# 32 "/usr/local/include/c++/4.9.0/ext/alloc_traits.h" 3
       
# 33 "/usr/local/include/c++/4.9.0/ext/alloc_traits.h" 3
# 41 "/usr/local/include/c++/4.9.0/ext/alloc_traits.h" 3
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

# 94 "/usr/local/include/c++/4.9.0/ext/alloc_traits.h" 3
template<typename _Alloc>
  struct __alloc_traits



  {
    typedef _Alloc allocator_type;
# 172 "/usr/local/include/c++/4.9.0/ext/alloc_traits.h" 3
    typedef typename _Alloc::pointer pointer;
    typedef typename _Alloc::const_pointer const_pointer;
    typedef typename _Alloc::value_type value_type;
    typedef typename _Alloc::reference reference;
    typedef typename _Alloc::const_reference const_reference;
    typedef typename _Alloc::size_type size_type;
    typedef typename _Alloc::difference_type difference_type;

    static pointer
    allocate(_Alloc& __a, size_type __n)
    { return __a.allocate(__n); }

    static void deallocate(_Alloc& __a, pointer __p, size_type __n)
    { __a.deallocate(__p, __n); }

    template<typename _Tp>
      static void construct(_Alloc& __a, pointer __p, const _Tp& __arg)
      { __a.construct(__p, __arg); }

    static void destroy(_Alloc& __a, pointer __p)
    { __a.destroy(__p); }

    static size_type max_size(const _Alloc& __a)
    { return __a.max_size(); }

    static const _Alloc& _S_select_on_copy(const _Alloc& __a) { return __a; }

    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
    {


      std::__alloc_swap<_Alloc>::_S_do_it(__a, __b);
    }

    template<typename _Tp>
      struct rebind
      { typedef typename _Alloc::template rebind<_Tp>::other other; };

  };


}
# 66 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 2 3




namespace std __attribute__ ((__visibility__ ("default")))
{

# 90 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
  enum _Rb_tree_color { _S_red = false, _S_black = true };

  struct _Rb_tree_node_base
  {
    typedef _Rb_tree_node_base* _Base_ptr;
    typedef const _Rb_tree_node_base* _Const_Base_ptr;

    _Rb_tree_color _M_color;
    _Base_ptr _M_parent;
    _Base_ptr _M_left;
    _Base_ptr _M_right;

    static _Base_ptr
    _S_minimum(_Base_ptr __x)
    {
      while (__x->_M_left != 0) __x = __x->_M_left;
      return __x;
    }

    static _Const_Base_ptr
    _S_minimum(_Const_Base_ptr __x)
    {
      while (__x->_M_left != 0) __x = __x->_M_left;
      return __x;
    }

    static _Base_ptr
    _S_maximum(_Base_ptr __x)
    {
      while (__x->_M_right != 0) __x = __x->_M_right;
      return __x;
    }

    static _Const_Base_ptr
    _S_maximum(_Const_Base_ptr __x)
    {
      while (__x->_M_right != 0) __x = __x->_M_right;
      return __x;
    }
  };

  template<typename _Val>
    struct _Rb_tree_node : public _Rb_tree_node_base
    {
      typedef _Rb_tree_node<_Val>* _Link_type;


      _Val _M_value_field;

      _Val*
      _M_valptr()
      { return std::__addressof(_M_value_field); }

      const _Val*
      _M_valptr() const
      { return std::__addressof(_M_value_field); }
# 157 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
    };

  __attribute__ ((__pure__)) _Rb_tree_node_base*
  _Rb_tree_increment(_Rb_tree_node_base* __x) throw ();

  __attribute__ ((__pure__)) const _Rb_tree_node_base*
  _Rb_tree_increment(const _Rb_tree_node_base* __x) throw ();

  __attribute__ ((__pure__)) _Rb_tree_node_base*
  _Rb_tree_decrement(_Rb_tree_node_base* __x) throw ();

  __attribute__ ((__pure__)) const _Rb_tree_node_base*
  _Rb_tree_decrement(const _Rb_tree_node_base* __x) throw ();

  template<typename _Tp>
    struct _Rb_tree_iterator
    {
      typedef _Tp value_type;
      typedef _Tp& reference;
      typedef _Tp* pointer;

      typedef bidirectional_iterator_tag iterator_category;
      typedef ptrdiff_t difference_type;

      typedef _Rb_tree_iterator<_Tp> _Self;
      typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
      typedef _Rb_tree_node<_Tp>* _Link_type;

      _Rb_tree_iterator()
      : _M_node() { }

      explicit
      _Rb_tree_iterator(_Link_type __x)
      : _M_node(__x) { }

      reference
      operator*() const
      { return *static_cast<_Link_type>(_M_node)->_M_valptr(); }

      pointer
      operator->() const
      { return static_cast<_Link_type> (_M_node)->_M_valptr(); }

      _Self&
      operator++()
      {
 _M_node = _Rb_tree_increment(_M_node);
 return *this;
      }

      _Self
      operator++(int)
      {
 _Self __tmp = *this;
 _M_node = _Rb_tree_increment(_M_node);
 return __tmp;
      }

      _Self&
      operator--()
      {
 _M_node = _Rb_tree_decrement(_M_node);
 return *this;
      }

      _Self
      operator--(int)
      {
 _Self __tmp = *this;
 _M_node = _Rb_tree_decrement(_M_node);
 return __tmp;
      }

      bool
      operator==(const _Self& __x) const
      { return _M_node == __x._M_node; }

      bool
      operator!=(const _Self& __x) const
      { return _M_node != __x._M_node; }

      _Base_ptr _M_node;
  };

  template<typename _Tp>
    struct _Rb_tree_const_iterator
    {
      typedef _Tp value_type;
      typedef const _Tp& reference;
      typedef const _Tp* pointer;

      typedef _Rb_tree_iterator<_Tp> iterator;

      typedef bidirectional_iterator_tag iterator_category;
      typedef ptrdiff_t difference_type;

      typedef _Rb_tree_const_iterator<_Tp> _Self;
      typedef _Rb_tree_node_base::_Const_Base_ptr _Base_ptr;
      typedef const _Rb_tree_node<_Tp>* _Link_type;

      _Rb_tree_const_iterator()
      : _M_node() { }

      explicit
      _Rb_tree_const_iterator(_Link_type __x)
      : _M_node(__x) { }

      _Rb_tree_const_iterator(const iterator& __it)
      : _M_node(__it._M_node) { }

      iterator
      _M_const_cast() const
      { return iterator(static_cast<typename iterator::_Link_type>
   (const_cast<typename iterator::_Base_ptr>(_M_node))); }

      reference
      operator*() const
      { return *static_cast<_Link_type>(_M_node)->_M_valptr(); }

      pointer
      operator->() const
      { return static_cast<_Link_type>(_M_node)->_M_valptr(); }

      _Self&
      operator++()
      {
 _M_node = _Rb_tree_increment(_M_node);
 return *this;
      }

      _Self
      operator++(int)
      {
 _Self __tmp = *this;
 _M_node = _Rb_tree_increment(_M_node);
 return __tmp;
      }

      _Self&
      operator--()
      {
 _M_node = _Rb_tree_decrement(_M_node);
 return *this;
      }

      _Self
      operator--(int)
      {
 _Self __tmp = *this;
 _M_node = _Rb_tree_decrement(_M_node);
 return __tmp;
      }

      bool
      operator==(const _Self& __x) const
      { return _M_node == __x._M_node; }

      bool
      operator!=(const _Self& __x) const
      { return _M_node != __x._M_node; }

      _Base_ptr _M_node;
    };

  template<typename _Val>
    inline bool
    operator==(const _Rb_tree_iterator<_Val>& __x,
               const _Rb_tree_const_iterator<_Val>& __y)
    { return __x._M_node == __y._M_node; }

  template<typename _Val>
    inline bool
    operator!=(const _Rb_tree_iterator<_Val>& __x,
               const _Rb_tree_const_iterator<_Val>& __y)
    { return __x._M_node != __y._M_node; }

  void
  _Rb_tree_insert_and_rebalance(const bool __insert_left,
                                _Rb_tree_node_base* __x,
                                _Rb_tree_node_base* __p,
                                _Rb_tree_node_base& __header) throw ();

  _Rb_tree_node_base*
  _Rb_tree_rebalance_for_erase(_Rb_tree_node_base* const __z,
          _Rb_tree_node_base& __header) throw ();


  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc = allocator<_Val> >
    class _Rb_tree
    {
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
        rebind<_Rb_tree_node<_Val> >::other _Node_allocator;

      typedef __gnu_cxx::__alloc_traits<_Node_allocator> _Alloc_traits;

    protected:
      typedef _Rb_tree_node_base* _Base_ptr;
      typedef const _Rb_tree_node_base* _Const_Base_ptr;

    public:
      typedef _Key key_type;
      typedef _Val value_type;
      typedef value_type* pointer;
      typedef const value_type* const_pointer;
      typedef value_type& reference;
      typedef const value_type& const_reference;
      typedef _Rb_tree_node<_Val>* _Link_type;
      typedef const _Rb_tree_node<_Val>* _Const_Link_type;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Alloc allocator_type;

      _Node_allocator&
      _M_get_Node_allocator()
      { return *static_cast<_Node_allocator*>(&this->_M_impl); }

      const _Node_allocator&
      _M_get_Node_allocator() const
      { return *static_cast<const _Node_allocator*>(&this->_M_impl); }

      allocator_type
      get_allocator() const
      { return allocator_type(_M_get_Node_allocator()); }

    protected:
      _Link_type
      _M_get_node()
      { return _Alloc_traits::allocate(_M_get_Node_allocator(), 1); }

      void
      _M_put_node(_Link_type __p)
      { _Alloc_traits::deallocate(_M_get_Node_allocator(), __p, 1); }


      _Link_type
      _M_create_node(const value_type& __x)
      {
 _Link_type __tmp = _M_get_node();
 try
   { get_allocator().construct(__tmp->_M_valptr(), __x); }
 catch(...)
   {
     _M_put_node(__tmp);
     throw;
   }
 return __tmp;
      }

      void
      _M_destroy_node(_Link_type __p)
      {
 get_allocator().destroy(__p->_M_valptr());
 _M_put_node(__p);
      }
# 442 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
      _Link_type
      _M_clone_node(_Const_Link_type __x)
      {
 _Link_type __tmp = _M_create_node(*__x->_M_valptr());
 __tmp->_M_color = __x->_M_color;
 __tmp->_M_left = 0;
 __tmp->_M_right = 0;
 return __tmp;
      }

    protected:
      template<typename _Key_compare,
        bool _Is_pod_comparator = __is_pod(_Key_compare)>
        struct _Rb_tree_impl : public _Node_allocator
        {
   _Key_compare _M_key_compare;
   _Rb_tree_node_base _M_header;
   size_type _M_node_count;

   _Rb_tree_impl()
   : _Node_allocator(), _M_key_compare(), _M_header(),
     _M_node_count(0)
   { _M_initialize(); }

   _Rb_tree_impl(const _Key_compare& __comp, const _Node_allocator& __a)
   : _Node_allocator(__a), _M_key_compare(__comp), _M_header(),
     _M_node_count(0)
   { _M_initialize(); }
# 478 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
 private:
   void
   _M_initialize()
   {
     this->_M_header._M_color = _S_red;
     this->_M_header._M_parent = 0;
     this->_M_header._M_left = &this->_M_header;
     this->_M_header._M_right = &this->_M_header;
   }
 };

      _Rb_tree_impl<_Compare> _M_impl;

    protected:
      _Base_ptr&
      _M_root()
      { return this->_M_impl._M_header._M_parent; }

      _Const_Base_ptr
      _M_root() const
      { return this->_M_impl._M_header._M_parent; }

      _Base_ptr&
      _M_leftmost()
      { return this->_M_impl._M_header._M_left; }

      _Const_Base_ptr
      _M_leftmost() const
      { return this->_M_impl._M_header._M_left; }

      _Base_ptr&
      _M_rightmost()
      { return this->_M_impl._M_header._M_right; }

      _Const_Base_ptr
      _M_rightmost() const
      { return this->_M_impl._M_header._M_right; }

      _Link_type
      _M_begin()
      { return static_cast<_Link_type>(this->_M_impl._M_header._M_parent); }

      _Const_Link_type
      _M_begin() const
      {
 return static_cast<_Const_Link_type>
   (this->_M_impl._M_header._M_parent);
      }

      _Link_type
      _M_end()
      { return static_cast<_Link_type>(&this->_M_impl._M_header); }

      _Const_Link_type
      _M_end() const
      { return static_cast<_Const_Link_type>(&this->_M_impl._M_header); }

      static const_reference
      _S_value(_Const_Link_type __x)
      { return *__x->_M_valptr(); }

      static const _Key&
      _S_key(_Const_Link_type __x)
      { return _KeyOfValue()(_S_value(__x)); }

      static _Link_type
      _S_left(_Base_ptr __x)
      { return static_cast<_Link_type>(__x->_M_left); }

      static _Const_Link_type
      _S_left(_Const_Base_ptr __x)
      { return static_cast<_Const_Link_type>(__x->_M_left); }

      static _Link_type
      _S_right(_Base_ptr __x)
      { return static_cast<_Link_type>(__x->_M_right); }

      static _Const_Link_type
      _S_right(_Const_Base_ptr __x)
      { return static_cast<_Const_Link_type>(__x->_M_right); }

      static const_reference
      _S_value(_Const_Base_ptr __x)
      { return *static_cast<_Const_Link_type>(__x)->_M_valptr(); }

      static const _Key&
      _S_key(_Const_Base_ptr __x)
      { return _KeyOfValue()(_S_value(__x)); }

      static _Base_ptr
      _S_minimum(_Base_ptr __x)
      { return _Rb_tree_node_base::_S_minimum(__x); }

      static _Const_Base_ptr
      _S_minimum(_Const_Base_ptr __x)
      { return _Rb_tree_node_base::_S_minimum(__x); }

      static _Base_ptr
      _S_maximum(_Base_ptr __x)
      { return _Rb_tree_node_base::_S_maximum(__x); }

      static _Const_Base_ptr
      _S_maximum(_Const_Base_ptr __x)
      { return _Rb_tree_node_base::_S_maximum(__x); }

    public:
      typedef _Rb_tree_iterator<value_type> iterator;
      typedef _Rb_tree_const_iterator<value_type> const_iterator;

      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
      pair<_Base_ptr, _Base_ptr>
      _M_get_insert_unique_pos(const key_type& __k);

      pair<_Base_ptr, _Base_ptr>
      _M_get_insert_equal_pos(const key_type& __k);

      pair<_Base_ptr, _Base_ptr>
      _M_get_insert_hint_unique_pos(const_iterator __pos,
        const key_type& __k);

      pair<_Base_ptr, _Base_ptr>
      _M_get_insert_hint_equal_pos(const_iterator __pos,
       const key_type& __k);
# 627 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
      iterator
      _M_insert_(_Base_ptr __x, _Base_ptr __y,
   const value_type& __v);



      iterator
      _M_insert_lower(_Base_ptr __y, const value_type& __v);

      iterator
      _M_insert_equal_lower(const value_type& __x);


      _Link_type
      _M_copy(_Const_Link_type __x, _Link_type __p);

      void
      _M_erase(_Link_type __x);

      iterator
      _M_lower_bound(_Link_type __x, _Link_type __y,
       const _Key& __k);

      const_iterator
      _M_lower_bound(_Const_Link_type __x, _Const_Link_type __y,
       const _Key& __k) const;

      iterator
      _M_upper_bound(_Link_type __x, _Link_type __y,
       const _Key& __k);

      const_iterator
      _M_upper_bound(_Const_Link_type __x, _Const_Link_type __y,
       const _Key& __k) const;

    public:

      _Rb_tree() { }

      _Rb_tree(const _Compare& __comp,
        const allocator_type& __a = allocator_type())
      : _M_impl(__comp, _Node_allocator(__a)) { }

      _Rb_tree(const _Rb_tree& __x)
      : _M_impl(__x._M_impl._M_key_compare,
         _Alloc_traits::_S_select_on_copy(__x._M_get_Node_allocator()))
      {
 if (__x._M_root() != 0)
   {
     _M_root() = _M_copy(__x._M_begin(), _M_end());
     _M_leftmost() = _S_minimum(_M_root());
     _M_rightmost() = _S_maximum(_M_root());
     _M_impl._M_node_count = __x._M_impl._M_node_count;
   }
      }
# 714 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
      ~_Rb_tree()
      { _M_erase(_M_begin()); }

      _Rb_tree&
      operator=(const _Rb_tree& __x);


      _Compare
      key_comp() const
      { return _M_impl._M_key_compare; }

      iterator
      begin()
      {
 return iterator(static_cast<_Link_type>
   (this->_M_impl._M_header._M_left));
      }

      const_iterator
      begin() const
      {
 return const_iterator(static_cast<_Const_Link_type>
         (this->_M_impl._M_header._M_left));
      }

      iterator
      end()
      { return iterator(static_cast<_Link_type>(&this->_M_impl._M_header)); }

      const_iterator
      end() const
      {
 return const_iterator(static_cast<_Const_Link_type>
         (&this->_M_impl._M_header));
      }

      reverse_iterator
      rbegin()
      { return reverse_iterator(end()); }

      const_reverse_iterator
      rbegin() const
      { return const_reverse_iterator(end()); }

      reverse_iterator
      rend()
      { return reverse_iterator(begin()); }

      const_reverse_iterator
      rend() const
      { return const_reverse_iterator(begin()); }

      bool
      empty() const
      { return _M_impl._M_node_count == 0; }

      size_type
      size() const
      { return _M_impl._M_node_count; }

      size_type
      max_size() const
      { return _Alloc_traits::max_size(_M_get_Node_allocator()); }

      void



      swap(_Rb_tree& __t);
# 819 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
      pair<iterator, bool>
      _M_insert_unique(const value_type& __x);

      iterator
      _M_insert_equal(const value_type& __x);

      iterator
      _M_insert_unique_(const_iterator __position, const value_type& __x);

      iterator
      _M_insert_equal_(const_iterator __position, const value_type& __x);


      template<typename _InputIterator>
        void
        _M_insert_unique(_InputIterator __first, _InputIterator __last);

      template<typename _InputIterator>
        void
        _M_insert_equal(_InputIterator __first, _InputIterator __last);

    private:
      void
      _M_erase_aux(const_iterator __position);

      void
      _M_erase_aux(const_iterator __first, const_iterator __last);

    public:
# 872 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
      void
      erase(iterator __position)
      { _M_erase_aux(__position); }

      void
      erase(const_iterator __position)
      { _M_erase_aux(__position); }

      size_type
      erase(const key_type& __x);
# 894 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
      void
      erase(iterator __first, iterator __last)
      { _M_erase_aux(__first, __last); }

      void
      erase(const_iterator __first, const_iterator __last)
      { _M_erase_aux(__first, __last); }

      void
      erase(const key_type* __first, const key_type* __last);

      void
      clear()
      {
        _M_erase(_M_begin());
        _M_leftmost() = _M_end();
        _M_root() = 0;
        _M_rightmost() = _M_end();
        _M_impl._M_node_count = 0;
      }


      iterator
      find(const key_type& __k);

      const_iterator
      find(const key_type& __k) const;

      size_type
      count(const key_type& __k) const;

      iterator
      lower_bound(const key_type& __k)
      { return _M_lower_bound(_M_begin(), _M_end(), __k); }

      const_iterator
      lower_bound(const key_type& __k) const
      { return _M_lower_bound(_M_begin(), _M_end(), __k); }

      iterator
      upper_bound(const key_type& __k)
      { return _M_upper_bound(_M_begin(), _M_end(), __k); }

      const_iterator
      upper_bound(const key_type& __k) const
      { return _M_upper_bound(_M_begin(), _M_end(), __k); }

      pair<iterator, iterator>
      equal_range(const key_type& __k);

      pair<const_iterator, const_iterator>
      equal_range(const key_type& __k) const;


      bool
      __rb_verify() const;
# 965 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
    };

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    inline bool
    operator==(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
        const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    {
      return __x.size() == __y.size()
      && std::equal(__x.begin(), __x.end(), __y.begin());
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    inline bool
    operator<(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
       const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    {
      return std::lexicographical_compare(__x.begin(), __x.end(),
       __y.begin(), __y.end());
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    inline bool
    operator!=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
        const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { return !(__x == __y); }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    inline bool
    operator>(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
       const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { return __y < __x; }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    inline bool
    operator<=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
        const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { return !(__y < __x); }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    inline bool
    operator>=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
        const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { return !(__x < __y); }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    inline void
    swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
  _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
    { __x.swap(__y); }
# 1091 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>&
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    operator=(const _Rb_tree& __x)
    {
      if (this != &__x)
 {

   clear();
# 1113 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
   _M_impl._M_key_compare = __x._M_impl._M_key_compare;
   if (__x._M_root() != 0)
     {
       _M_root() = _M_copy(__x._M_begin(), _M_end());
       _M_leftmost() = _S_minimum(_M_root());
       _M_rightmost() = _S_maximum(_M_root());
       _M_impl._M_node_count = __x._M_impl._M_node_count;
     }
 }
      return *this;
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>



    typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::



    _M_insert_(_Base_ptr __x, _Base_ptr __p, const _Val& __v)

    {
      bool __insert_left = (__x != 0 || __p == _M_end()
       || _M_impl._M_key_compare(_KeyOfValue()(__v),
            _S_key(__p)));

      _Link_type __z = _M_create_node((__v));

      _Rb_tree_insert_and_rebalance(__insert_left, __z, __p,
        this->_M_impl._M_header);
      ++_M_impl._M_node_count;
      return iterator(__z);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>



    typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::



    _M_insert_lower(_Base_ptr __p, const _Val& __v)

    {
      bool __insert_left = (__p == _M_end()
       || !_M_impl._M_key_compare(_S_key(__p),
             _KeyOfValue()(__v)));

      _Link_type __z = _M_create_node((__v));

      _Rb_tree_insert_and_rebalance(__insert_left, __z, __p,
        this->_M_impl._M_header);
      ++_M_impl._M_node_count;
      return iterator(__z);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>



    typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::



    _M_insert_equal_lower(const _Val& __v)

    {
      _Link_type __x = _M_begin();
      _Link_type __y = _M_end();
      while (__x != 0)
 {
   __y = __x;
   __x = !_M_impl._M_key_compare(_S_key(__x), _KeyOfValue()(__v)) ?
         _S_left(__x) : _S_right(__x);
 }
      return _M_insert_lower(__y, (__v));
    }

  template<typename _Key, typename _Val, typename _KoV,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_Link_type
    _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::
    _M_copy(_Const_Link_type __x, _Link_type __p)
    {

      _Link_type __top = _M_clone_node(__x);
      __top->_M_parent = __p;

      try
 {
   if (__x->_M_right)
     __top->_M_right = _M_copy(_S_right(__x), __top);
   __p = __top;
   __x = _S_left(__x);

   while (__x != 0)
     {
       _Link_type __y = _M_clone_node(__x);
       __p->_M_left = __y;
       __y->_M_parent = __p;
       if (__x->_M_right)
  __y->_M_right = _M_copy(_S_right(__x), __y);
       __p = __y;
       __x = _S_left(__x);
     }
 }
      catch(...)
 {
   _M_erase(__top);
   throw;
 }
      return __top;
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    void
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_erase(_Link_type __x)
    {

      while (__x != 0)
 {
   _M_erase(_S_right(__x));
   _Link_type __y = _S_left(__x);
   _M_destroy_node(__x);
   __x = __y;
 }
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KeyOfValue,
        _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_lower_bound(_Link_type __x, _Link_type __y,
     const _Key& __k)
    {
      while (__x != 0)
 if (!_M_impl._M_key_compare(_S_key(__x), __k))
   __y = __x, __x = _S_left(__x);
 else
   __x = _S_right(__x);
      return iterator(__y);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KeyOfValue,
        _Compare, _Alloc>::const_iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_lower_bound(_Const_Link_type __x, _Const_Link_type __y,
     const _Key& __k) const
    {
      while (__x != 0)
 if (!_M_impl._M_key_compare(_S_key(__x), __k))
   __y = __x, __x = _S_left(__x);
 else
   __x = _S_right(__x);
      return const_iterator(__y);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KeyOfValue,
        _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_upper_bound(_Link_type __x, _Link_type __y,
     const _Key& __k)
    {
      while (__x != 0)
 if (_M_impl._M_key_compare(__k, _S_key(__x)))
   __y = __x, __x = _S_left(__x);
 else
   __x = _S_right(__x);
      return iterator(__y);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KeyOfValue,
        _Compare, _Alloc>::const_iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_upper_bound(_Const_Link_type __x, _Const_Link_type __y,
     const _Key& __k) const
    {
      while (__x != 0)
 if (_M_impl._M_key_compare(__k, _S_key(__x)))
   __y = __x, __x = _S_left(__x);
 else
   __x = _S_right(__x);
      return const_iterator(__y);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::iterator,
  typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::iterator>
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    equal_range(const _Key& __k)
    {
      _Link_type __x = _M_begin();
      _Link_type __y = _M_end();
      while (__x != 0)
 {
   if (_M_impl._M_key_compare(_S_key(__x), __k))
     __x = _S_right(__x);
   else if (_M_impl._M_key_compare(__k, _S_key(__x)))
     __y = __x, __x = _S_left(__x);
   else
     {
       _Link_type __xu(__x), __yu(__y);
       __y = __x, __x = _S_left(__x);
       __xu = _S_right(__xu);
       return pair<iterator,
            iterator>(_M_lower_bound(__x, __y, __k),
        _M_upper_bound(__xu, __yu, __k));
     }
 }
      return pair<iterator, iterator>(iterator(__y),
          iterator(__y));
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::const_iterator,
  typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::const_iterator>
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    equal_range(const _Key& __k) const
    {
      _Const_Link_type __x = _M_begin();
      _Const_Link_type __y = _M_end();
      while (__x != 0)
 {
   if (_M_impl._M_key_compare(_S_key(__x), __k))
     __x = _S_right(__x);
   else if (_M_impl._M_key_compare(__k, _S_key(__x)))
     __y = __x, __x = _S_left(__x);
   else
     {
       _Const_Link_type __xu(__x), __yu(__y);
       __y = __x, __x = _S_left(__x);
       __xu = _S_right(__xu);
       return pair<const_iterator,
            const_iterator>(_M_lower_bound(__x, __y, __k),
       _M_upper_bound(__xu, __yu, __k));
     }
 }
      return pair<const_iterator, const_iterator>(const_iterator(__y),
        const_iterator(__y));
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    void
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __t)



    {
      if (_M_root() == 0)
 {
   if (__t._M_root() != 0)
     {
       _M_root() = __t._M_root();
       _M_leftmost() = __t._M_leftmost();
       _M_rightmost() = __t._M_rightmost();
       _M_root()->_M_parent = _M_end();

       __t._M_root() = 0;
       __t._M_leftmost() = __t._M_end();
       __t._M_rightmost() = __t._M_end();
     }
 }
      else if (__t._M_root() == 0)
 {
   __t._M_root() = _M_root();
   __t._M_leftmost() = _M_leftmost();
   __t._M_rightmost() = _M_rightmost();
   __t._M_root()->_M_parent = __t._M_end();

   _M_root() = 0;
   _M_leftmost() = _M_end();
   _M_rightmost() = _M_end();
 }
      else
 {
   std::swap(_M_root(),__t._M_root());
   std::swap(_M_leftmost(),__t._M_leftmost());
   std::swap(_M_rightmost(),__t._M_rightmost());

   _M_root()->_M_parent = _M_end();
   __t._M_root()->_M_parent = __t._M_end();
 }

      std::swap(this->_M_impl._M_node_count, __t._M_impl._M_node_count);
      std::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);

      _Alloc_traits::_S_on_swap(_M_get_Node_allocator(),
    __t._M_get_Node_allocator());
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::_Base_ptr,
  typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::_Base_ptr>
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_unique_pos(const key_type& __k)
    {
      typedef pair<_Base_ptr, _Base_ptr> _Res;
      _Link_type __x = _M_begin();
      _Link_type __y = _M_end();
      bool __comp = true;
      while (__x != 0)
 {
   __y = __x;
   __comp = _M_impl._M_key_compare(__k, _S_key(__x));
   __x = __comp ? _S_left(__x) : _S_right(__x);
 }
      iterator __j = iterator(__y);
      if (__comp)
 {
   if (__j == begin())
     return _Res(__x, __y);
   else
     --__j;
 }
      if (_M_impl._M_key_compare(_S_key(__j._M_node), __k))
 return _Res(__x, __y);
      return _Res(__j._M_node, 0);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::_Base_ptr,
  typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::_Base_ptr>
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_equal_pos(const key_type& __k)
    {
      typedef pair<_Base_ptr, _Base_ptr> _Res;
      _Link_type __x = _M_begin();
      _Link_type __y = _M_end();
      while (__x != 0)
 {
   __y = __x;
   __x = _M_impl._M_key_compare(__k, _S_key(__x)) ?
         _S_left(__x) : _S_right(__x);
 }
      return _Res(__x, __y);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>



    pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::iterator, bool>
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::



    _M_insert_unique(const _Val& __v)

    {
      typedef pair<iterator, bool> _Res;
      pair<_Base_ptr, _Base_ptr> __res
 = _M_get_insert_unique_pos(_KeyOfValue()(__v));

      if (__res.second)
 return _Res(_M_insert_(__res.first, __res.second,
          (__v)),
      true);

      return _Res(iterator(static_cast<_Link_type>(__res.first)), false);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>



    typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::



    _M_insert_equal(const _Val& __v)

    {
      pair<_Base_ptr, _Base_ptr> __res
 = _M_get_insert_equal_pos(_KeyOfValue()(__v));
      return _M_insert_(__res.first, __res.second, (__v));
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::_Base_ptr,
         typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::_Base_ptr>
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_hint_unique_pos(const_iterator __position,
      const key_type& __k)
    {
      iterator __pos = __position._M_const_cast();
      typedef pair<_Base_ptr, _Base_ptr> _Res;


      if (__pos._M_node == _M_end())
 {
   if (size() > 0
       && _M_impl._M_key_compare(_S_key(_M_rightmost()), __k))
     return _Res(0, _M_rightmost());
   else
     return _M_get_insert_unique_pos(__k);
 }
      else if (_M_impl._M_key_compare(__k, _S_key(__pos._M_node)))
 {

   iterator __before = __pos;
   if (__pos._M_node == _M_leftmost())
     return _Res(_M_leftmost(), _M_leftmost());
   else if (_M_impl._M_key_compare(_S_key((--__before)._M_node), __k))
     {
       if (_S_right(__before._M_node) == 0)
  return _Res(0, __before._M_node);
       else
  return _Res(__pos._M_node, __pos._M_node);
     }
   else
     return _M_get_insert_unique_pos(__k);
 }
      else if (_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
 {

   iterator __after = __pos;
   if (__pos._M_node == _M_rightmost())
     return _Res(0, _M_rightmost());
   else if (_M_impl._M_key_compare(__k, _S_key((++__after)._M_node)))
     {
       if (_S_right(__pos._M_node) == 0)
  return _Res(0, __pos._M_node);
       else
  return _Res(__after._M_node, __after._M_node);
     }
   else
     return _M_get_insert_unique_pos(__k);
 }
      else

 return _Res(__pos._M_node, 0);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>



    typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::



    _M_insert_unique_(const_iterator __position, const _Val& __v)

    {
      pair<_Base_ptr, _Base_ptr> __res
 = _M_get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));

      if (__res.second)
 return _M_insert_(__res.first, __res.second,
     (__v));
      return iterator(static_cast<_Link_type>(__res.first));
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    pair<typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::_Base_ptr,
         typename _Rb_tree<_Key, _Val, _KeyOfValue,
      _Compare, _Alloc>::_Base_ptr>
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_get_insert_hint_equal_pos(const_iterator __position, const key_type& __k)
    {
      iterator __pos = __position._M_const_cast();
      typedef pair<_Base_ptr, _Base_ptr> _Res;


      if (__pos._M_node == _M_end())
 {
   if (size() > 0
       && !_M_impl._M_key_compare(__k, _S_key(_M_rightmost())))
     return _Res(0, _M_rightmost());
   else
     return _M_get_insert_equal_pos(__k);
 }
      else if (!_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
 {

   iterator __before = __pos;
   if (__pos._M_node == _M_leftmost())
     return _Res(_M_leftmost(), _M_leftmost());
   else if (!_M_impl._M_key_compare(__k, _S_key((--__before)._M_node)))
     {
       if (_S_right(__before._M_node) == 0)
  return _Res(0, __before._M_node);
       else
  return _Res(__pos._M_node, __pos._M_node);
     }
   else
     return _M_get_insert_equal_pos(__k);
 }
      else
 {

   iterator __after = __pos;
   if (__pos._M_node == _M_rightmost())
     return _Res(0, _M_rightmost());
   else if (!_M_impl._M_key_compare(_S_key((++__after)._M_node), __k))
     {
       if (_S_right(__pos._M_node) == 0)
  return _Res(0, __pos._M_node);
       else
  return _Res(__after._M_node, __after._M_node);
     }
   else
     return _Res(0, 0);
 }
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>



    typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::



    _M_insert_equal_(const_iterator __position, const _Val& __v)

    {
      pair<_Base_ptr, _Base_ptr> __res
 = _M_get_insert_hint_equal_pos(__position, _KeyOfValue()(__v));

      if (__res.second)
 return _M_insert_(__res.first, __res.second,
     (__v));

      return _M_insert_equal_lower((__v));
    }
# 1834 "/usr/local/include/c++/4.9.0/bits/stl_tree.h" 3
  template<typename _Key, typename _Val, typename _KoV,
           typename _Cmp, typename _Alloc>
    template<class _II>
      void
      _Rb_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::
      _M_insert_unique(_II __first, _II __last)
      {
 for (; __first != __last; ++__first)
   _M_insert_unique_(end(), *__first);
      }

  template<typename _Key, typename _Val, typename _KoV,
           typename _Cmp, typename _Alloc>
    template<class _II>
      void
      _Rb_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::
      _M_insert_equal(_II __first, _II __last)
      {
 for (; __first != __last; ++__first)
   _M_insert_equal_(end(), *__first);
      }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    void
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_erase_aux(const_iterator __position)
    {
      _Link_type __y =
 static_cast<_Link_type>(_Rb_tree_rebalance_for_erase
    (const_cast<_Base_ptr>(__position._M_node),
     this->_M_impl._M_header));
      _M_destroy_node(__y);
      --_M_impl._M_node_count;
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    void
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    _M_erase_aux(const_iterator __first, const_iterator __last)
    {
      if (__first == begin() && __last == end())
 clear();
      else
 while (__first != __last)
   erase(__first++);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    erase(const _Key& __x)
    {
      pair<iterator, iterator> __p = equal_range(__x);
      const size_type __old_size = size();
      erase(__p.first, __p.second);
      return __old_size - size();
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    void
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    erase(const _Key* __first, const _Key* __last)
    {
      while (__first != __last)
 erase(*__first++);
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KeyOfValue,
        _Compare, _Alloc>::iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    find(const _Key& __k)
    {
      iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
      return (__j == end()
       || _M_impl._M_key_compare(__k,
     _S_key(__j._M_node))) ? end() : __j;
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KeyOfValue,
        _Compare, _Alloc>::const_iterator
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    find(const _Key& __k) const
    {
      const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
      return (__j == end()
       || _M_impl._M_key_compare(__k,
     _S_key(__j._M_node))) ? end() : __j;
    }

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
    count(const _Key& __k) const
    {
      pair<const_iterator, const_iterator> __p = equal_range(__k);
      const size_type __n = std::distance(__p.first, __p.second);
      return __n;
    }

  __attribute__ ((__pure__)) unsigned int
  _Rb_tree_black_count(const _Rb_tree_node_base* __node,
                       const _Rb_tree_node_base* __root) throw ();

  template<typename _Key, typename _Val, typename _KeyOfValue,
           typename _Compare, typename _Alloc>
    bool
    _Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::__rb_verify() const
    {
      if (_M_impl._M_node_count == 0 || begin() == end())
 return _M_impl._M_node_count == 0 && begin() == end()
        && this->_M_impl._M_header._M_left == _M_end()
        && this->_M_impl._M_header._M_right == _M_end();

      unsigned int __len = _Rb_tree_black_count(_M_leftmost(), _M_root());
      for (const_iterator __it = begin(); __it != end(); ++__it)
 {
   _Const_Link_type __x = static_cast<_Const_Link_type>(__it._M_node);
   _Const_Link_type __L = _S_left(__x);
   _Const_Link_type __R = _S_right(__x);

   if (__x->_M_color == _S_red)
     if ((__L && __L->_M_color == _S_red)
  || (__R && __R->_M_color == _S_red))
       return false;

   if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L)))
     return false;
   if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__x)))
     return false;

   if (!__L && !__R && _Rb_tree_black_count(__x, _M_root()) != __len)
     return false;
 }

      if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
 return false;
      if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
 return false;
      return true;
    }


}
# 61 "/usr/local/include/c++/4.9.0/map" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 1 3
# 66 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

# 94 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
  template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
            typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
    class map
    {
    public:
      typedef _Key key_type;
      typedef _Tp mapped_type;
      typedef std::pair<const _Key, _Tp> value_type;
      typedef _Compare key_compare;
      typedef _Alloc allocator_type;

    private:

      typedef typename _Alloc::value_type _Alloc_value_type;
     
     

     

    public:
      class value_compare
      : public std::binary_function<value_type, value_type, bool>
      {
 friend class map<_Key, _Tp, _Compare, _Alloc>;
      protected:
 _Compare comp;

 value_compare(_Compare __c)
 : comp(__c) { }

      public:
 bool operator()(const value_type& __x, const value_type& __y) const
 { return comp(__x.first, __y.first); }
      };

    private:

      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
 rebind<value_type>::other _Pair_alloc_type;

      typedef _Rb_tree<key_type, value_type, _Select1st<value_type>,
         key_compare, _Pair_alloc_type> _Rep_type;


      _Rep_type _M_t;

      typedef __gnu_cxx::__alloc_traits<_Pair_alloc_type> _Alloc_traits;

    public:


      typedef typename _Alloc_traits::pointer pointer;
      typedef typename _Alloc_traits::const_pointer const_pointer;
      typedef typename _Alloc_traits::reference reference;
      typedef typename _Alloc_traits::const_reference const_reference;
      typedef typename _Rep_type::iterator iterator;
      typedef typename _Rep_type::const_iterator const_iterator;
      typedef typename _Rep_type::size_type size_type;
      typedef typename _Rep_type::difference_type difference_type;
      typedef typename _Rep_type::reverse_iterator reverse_iterator;
      typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;







      map()
      : _M_t() { }






      explicit
      map(const _Compare& __comp,
   const allocator_type& __a = allocator_type())
      : _M_t(__comp, _Pair_alloc_type(__a)) { }
# 182 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      map(const map& __x)
      : _M_t(__x._M_t) { }
# 252 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      template<typename _InputIterator>
        map(_InputIterator __first, _InputIterator __last)
 : _M_t()
        { _M_t._M_insert_unique(__first, __last); }
# 269 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      template<typename _InputIterator>
        map(_InputIterator __first, _InputIterator __last,
     const _Compare& __comp,
     const allocator_type& __a = allocator_type())
 : _M_t(__comp, _Pair_alloc_type(__a))
        { _M_t._M_insert_unique(__first, __last); }
# 292 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      map&
      operator=(const map& __x)
      {
 _M_t = __x._M_t;
 return *this;
      }
# 344 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      allocator_type
      get_allocator() const
      { return allocator_type(_M_t.get_allocator()); }







      iterator
      begin()
      { return _M_t.begin(); }






      const_iterator
      begin() const
      { return _M_t.begin(); }






      iterator
      end()
      { return _M_t.end(); }






      const_iterator
      end() const
      { return _M_t.end(); }






      reverse_iterator
      rbegin()
      { return _M_t.rbegin(); }






      const_reverse_iterator
      rbegin() const
      { return _M_t.rbegin(); }






      reverse_iterator
      rend()
      { return _M_t.rend(); }






      const_reverse_iterator
      rend() const
      { return _M_t.rend(); }
# 463 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      bool
      empty() const
      { return _M_t.empty(); }


      size_type
      size() const
      { return _M_t.size(); }


      size_type
      max_size() const
      { return _M_t.max_size(); }
# 490 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      mapped_type&
      operator[](const key_type& __k)
      {



 iterator __i = lower_bound(__k);

 if (__i == end() || key_comp()(__k, (*__i).first))





          __i = insert(__i, value_type(__k, mapped_type()));

 return (*__i).second;
      }
# 535 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      mapped_type&
      at(const key_type& __k)
      {
 iterator __i = lower_bound(__k);
 if (__i == end() || key_comp()(__k, (*__i).first))
   __throw_out_of_range(("map::at"));
 return (*__i).second;
      }

      const mapped_type&
      at(const key_type& __k) const
      {
 const_iterator __i = lower_bound(__k);
 if (__i == end() || key_comp()(__k, (*__i).first))
   __throw_out_of_range(("map::at"));
 return (*__i).second;
      }
# 628 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      std::pair<iterator, bool>
      insert(const value_type& __x)
      { return _M_t._M_insert_unique(__x); }
# 677 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      iterator



      insert(iterator __position, const value_type& __x)

      { return _M_t._M_insert_unique_(__position, __x); }
# 703 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      template<typename _InputIterator>
        void
        insert(_InputIterator __first, _InputIterator __last)
        { _M_t._M_insert_unique(__first, __last); }
# 744 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      void
      erase(iterator __position)
      { _M_t.erase(__position); }
# 760 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      size_type
      erase(const key_type& __x)
      { return _M_t.erase(__x); }
# 796 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      void
      erase(iterator __first, iterator __last)
      { _M_t.erase(__first, __last); }
# 812 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      void
      swap(map& __x)



      { _M_t.swap(__x._M_t); }







      void
      clear()
      { _M_t.clear(); }






      key_compare
      key_comp() const
      { return _M_t.key_comp(); }





      value_compare
      value_comp() const
      { return value_compare(_M_t.key_comp()); }
# 858 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      iterator
      find(const key_type& __x)
      { return _M_t.find(__x); }
# 873 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      const_iterator
      find(const key_type& __x) const
      { return _M_t.find(__x); }
# 885 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      size_type
      count(const key_type& __x) const
      { return _M_t.find(__x) == _M_t.end() ? 0 : 1; }
# 900 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      iterator
      lower_bound(const key_type& __x)
      { return _M_t.lower_bound(__x); }
# 915 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      const_iterator
      lower_bound(const key_type& __x) const
      { return _M_t.lower_bound(__x); }







      iterator
      upper_bound(const key_type& __x)
      { return _M_t.upper_bound(__x); }







      const_iterator
      upper_bound(const key_type& __x) const
      { return _M_t.upper_bound(__x); }
# 954 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      std::pair<iterator, iterator>
      equal_range(const key_type& __x)
      { return _M_t.equal_range(__x); }
# 973 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
      std::pair<const_iterator, const_iterator>
      equal_range(const key_type& __x) const
      { return _M_t.equal_range(__x); }

      template<typename _K1, typename _T1, typename _C1, typename _A1>
        friend bool
        operator==(const map<_K1, _T1, _C1, _A1>&,
     const map<_K1, _T1, _C1, _A1>&);

      template<typename _K1, typename _T1, typename _C1, typename _A1>
        friend bool
        operator<(const map<_K1, _T1, _C1, _A1>&,
    const map<_K1, _T1, _C1, _A1>&);
    };
# 998 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator==(const map<_Key, _Tp, _Compare, _Alloc>& __x,
               const map<_Key, _Tp, _Compare, _Alloc>& __y)
    { return __x._M_t == __y._M_t; }
# 1015 "/usr/local/include/c++/4.9.0/bits/stl_map.h" 3
  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator<(const map<_Key, _Tp, _Compare, _Alloc>& __x,
              const map<_Key, _Tp, _Compare, _Alloc>& __y)
    { return __x._M_t < __y._M_t; }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator!=(const map<_Key, _Tp, _Compare, _Alloc>& __x,
               const map<_Key, _Tp, _Compare, _Alloc>& __y)
    { return !(__x == __y); }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator>(const map<_Key, _Tp, _Compare, _Alloc>& __x,
              const map<_Key, _Tp, _Compare, _Alloc>& __y)
    { return __y < __x; }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator<=(const map<_Key, _Tp, _Compare, _Alloc>& __x,
               const map<_Key, _Tp, _Compare, _Alloc>& __y)
    { return !(__y < __x); }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator>=(const map<_Key, _Tp, _Compare, _Alloc>& __x,
               const map<_Key, _Tp, _Compare, _Alloc>& __y)
    { return !(__x < __y); }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline void
    swap(map<_Key, _Tp, _Compare, _Alloc>& __x,
  map<_Key, _Tp, _Compare, _Alloc>& __y)
    { __x.swap(__y); }


}
# 62 "/usr/local/include/c++/4.9.0/map" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 1 3
# 64 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

# 92 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
  template <typename _Key, typename _Tp,
     typename _Compare = std::less<_Key>,
     typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
    class multimap
    {
    public:
      typedef _Key key_type;
      typedef _Tp mapped_type;
      typedef std::pair<const _Key, _Tp> value_type;
      typedef _Compare key_compare;
      typedef _Alloc allocator_type;

    private:

      typedef typename _Alloc::value_type _Alloc_value_type;
     
     

     

    public:
      class value_compare
      : public std::binary_function<value_type, value_type, bool>
      {
 friend class multimap<_Key, _Tp, _Compare, _Alloc>;
      protected:
 _Compare comp;

 value_compare(_Compare __c)
 : comp(__c) { }

      public:
 bool operator()(const value_type& __x, const value_type& __y) const
 { return comp(__x.first, __y.first); }
      };

    private:

      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
 rebind<value_type>::other _Pair_alloc_type;

      typedef _Rb_tree<key_type, value_type, _Select1st<value_type>,
         key_compare, _Pair_alloc_type> _Rep_type;

      _Rep_type _M_t;

      typedef __gnu_cxx::__alloc_traits<_Pair_alloc_type> _Alloc_traits;

    public:


      typedef typename _Alloc_traits::pointer pointer;
      typedef typename _Alloc_traits::const_pointer const_pointer;
      typedef typename _Alloc_traits::reference reference;
      typedef typename _Alloc_traits::const_reference const_reference;
      typedef typename _Rep_type::iterator iterator;
      typedef typename _Rep_type::const_iterator const_iterator;
      typedef typename _Rep_type::size_type size_type;
      typedef typename _Rep_type::difference_type difference_type;
      typedef typename _Rep_type::reverse_iterator reverse_iterator;
      typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;







      multimap()
      : _M_t() { }






      explicit
      multimap(const _Compare& __comp,
        const allocator_type& __a = allocator_type())
      : _M_t(__comp, _Pair_alloc_type(__a)) { }
# 180 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      multimap(const multimap& __x)
      : _M_t(__x._M_t) { }
# 248 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      template<typename _InputIterator>
        multimap(_InputIterator __first, _InputIterator __last)
 : _M_t()
        { _M_t._M_insert_equal(__first, __last); }
# 264 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      template<typename _InputIterator>
        multimap(_InputIterator __first, _InputIterator __last,
   const _Compare& __comp,
   const allocator_type& __a = allocator_type())
 : _M_t(__comp, _Pair_alloc_type(__a))
        { _M_t._M_insert_equal(__first, __last); }
# 287 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      multimap&
      operator=(const multimap& __x)
      {
 _M_t = __x._M_t;
 return *this;
      }
# 339 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      allocator_type
      get_allocator() const
      { return allocator_type(_M_t.get_allocator()); }







      iterator
      begin()
      { return _M_t.begin(); }






      const_iterator
      begin() const
      { return _M_t.begin(); }






      iterator
      end()
      { return _M_t.end(); }






      const_iterator
      end() const
      { return _M_t.end(); }






      reverse_iterator
      rbegin()
      { return _M_t.rbegin(); }






      const_reverse_iterator
      rbegin() const
      { return _M_t.rbegin(); }






      reverse_iterator
      rend()
      { return _M_t.rend(); }






      const_reverse_iterator
      rend() const
      { return _M_t.rend(); }
# 456 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      bool
      empty() const
      { return _M_t.empty(); }


      size_type
      size() const
      { return _M_t.size(); }


      size_type
      max_size() const
      { return _M_t.max_size(); }
# 536 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      iterator
      insert(const value_type& __x)
      { return _M_t._M_insert_equal(__x); }
# 569 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      iterator



      insert(iterator __position, const value_type& __x)

      { return _M_t._M_insert_equal_(__position, __x); }
# 596 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      template<typename _InputIterator>
        void
        insert(_InputIterator __first, _InputIterator __last)
        { _M_t._M_insert_equal(__first, __last); }
# 650 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      void
      erase(iterator __position)
      { _M_t.erase(__position); }
# 666 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      size_type
      erase(const key_type& __x)
      { return _M_t.erase(__x); }
# 706 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      void
      erase(iterator __first, iterator __last)
      { _M_t.erase(__first, __last); }
# 722 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      void
      swap(multimap& __x)



      { _M_t.swap(__x._M_t); }







      void
      clear()
      { _M_t.clear(); }






      key_compare
      key_comp() const
      { return _M_t.key_comp(); }





      value_compare
      value_comp() const
      { return value_compare(_M_t.key_comp()); }
# 768 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      iterator
      find(const key_type& __x)
      { return _M_t.find(__x); }
# 783 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      const_iterator
      find(const key_type& __x) const
      { return _M_t.find(__x); }






      size_type
      count(const key_type& __x) const
      { return _M_t.count(__x); }
# 807 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      iterator
      lower_bound(const key_type& __x)
      { return _M_t.lower_bound(__x); }
# 822 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      const_iterator
      lower_bound(const key_type& __x) const
      { return _M_t.lower_bound(__x); }







      iterator
      upper_bound(const key_type& __x)
      { return _M_t.upper_bound(__x); }







      const_iterator
      upper_bound(const key_type& __x) const
      { return _M_t.upper_bound(__x); }
# 859 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      std::pair<iterator, iterator>
      equal_range(const key_type& __x)
      { return _M_t.equal_range(__x); }
# 876 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
      std::pair<const_iterator, const_iterator>
      equal_range(const key_type& __x) const
      { return _M_t.equal_range(__x); }

      template<typename _K1, typename _T1, typename _C1, typename _A1>
        friend bool
        operator==(const multimap<_K1, _T1, _C1, _A1>&,
     const multimap<_K1, _T1, _C1, _A1>&);

      template<typename _K1, typename _T1, typename _C1, typename _A1>
        friend bool
        operator<(const multimap<_K1, _T1, _C1, _A1>&,
    const multimap<_K1, _T1, _C1, _A1>&);
  };
# 901 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator==(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,
               const multimap<_Key, _Tp, _Compare, _Alloc>& __y)
    { return __x._M_t == __y._M_t; }
# 918 "/usr/local/include/c++/4.9.0/bits/stl_multimap.h" 3
  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator<(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,
              const multimap<_Key, _Tp, _Compare, _Alloc>& __y)
    { return __x._M_t < __y._M_t; }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator!=(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,
               const multimap<_Key, _Tp, _Compare, _Alloc>& __y)
    { return !(__x == __y); }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator>(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,
              const multimap<_Key, _Tp, _Compare, _Alloc>& __y)
    { return __y < __x; }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator<=(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,
               const multimap<_Key, _Tp, _Compare, _Alloc>& __y)
    { return !(__y < __x); }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool
    operator>=(const multimap<_Key, _Tp, _Compare, _Alloc>& __x,
               const multimap<_Key, _Tp, _Compare, _Alloc>& __y)
    { return !(__x < __y); }


  template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline void
    swap(multimap<_Key, _Tp, _Compare, _Alloc>& __x,
         multimap<_Key, _Tp, _Compare, _Alloc>& __y)
    { __x.swap(__y); }


}
# 63 "/usr/local/include/c++/4.9.0/map" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/range_access.h" 1 3
# 33 "/usr/local/include/c++/4.9.0/bits/range_access.h" 3
       
# 34 "/usr/local/include/c++/4.9.0/bits/range_access.h" 3
# 64 "/usr/local/include/c++/4.9.0/map" 2 3
# 39 "factory.h" 2
# 1 "/usr/local/include/c++/4.9.0/string" 1 3
# 36 "/usr/local/include/c++/4.9.0/string" 3
       
# 37 "/usr/local/include/c++/4.9.0/string" 3


# 1 "/usr/local/include/c++/4.9.0/bits/stringfwd.h" 1 3
# 37 "/usr/local/include/c++/4.9.0/bits/stringfwd.h" 3
       
# 38 "/usr/local/include/c++/4.9.0/bits/stringfwd.h" 3




namespace std __attribute__ ((__visibility__ ("default")))
{








  template<class _CharT>
    struct char_traits;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
           typename _Alloc = allocator<_CharT> >
    class basic_string;

  template<> struct char_traits<char>;


  typedef basic_string<char> string;


  template<> struct char_traits<wchar_t>;


  typedef basic_string<wchar_t> wstring;
# 86 "/usr/local/include/c++/4.9.0/bits/stringfwd.h" 3

}
# 40 "/usr/local/include/c++/4.9.0/string" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/char_traits.h" 1 3
# 37 "/usr/local/include/c++/4.9.0/bits/char_traits.h" 3
       
# 38 "/usr/local/include/c++/4.9.0/bits/char_traits.h" 3


# 1 "/usr/local/include/c++/4.9.0/bits/postypes.h" 1 3
# 38 "/usr/local/include/c++/4.9.0/bits/postypes.h" 3
       
# 39 "/usr/local/include/c++/4.9.0/bits/postypes.h" 3

# 1 "/usr/local/include/c++/4.9.0/cwchar" 1 3
# 39 "/usr/local/include/c++/4.9.0/cwchar" 3
       
# 40 "/usr/local/include/c++/4.9.0/cwchar" 3




# 1 "/usr/include/wchar.h" 1 3 4
# 37 "/usr/include/wchar.h" 3 4
# 1 "/usr/include/stdio.h" 1 3 4
# 45 "/usr/include/stdio.h" 3 4
struct _IO_FILE;



typedef struct _IO_FILE FILE;





# 65 "/usr/include/stdio.h" 3 4
typedef struct _IO_FILE __FILE;
# 38 "/usr/include/wchar.h" 2 3 4


# 1 "/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.9.0/include/stdarg.h" 1 3 4
# 40 "/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.9.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 41 "/usr/include/wchar.h" 2 3 4

# 1 "/usr/include/bits/wchar.h" 1 3 4
# 43 "/usr/include/wchar.h" 2 3 4
# 52 "/usr/include/wchar.h" 3 4
# 1 "/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.9.0/include/stddef.h" 1 3 4
# 212 "/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.9.0/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 353 "/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.9.0/include/stddef.h" 3 4
typedef unsigned int wint_t;
# 53 "/usr/include/wchar.h" 2 3 4
# 83 "/usr/include/wchar.h" 3 4
typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
# 104 "/usr/include/wchar.h" 3 4


typedef __mbstate_t mbstate_t;



# 129 "/usr/include/wchar.h" 3 4
extern "C" {




struct tm;









extern wchar_t *wcscpy (wchar_t *__restrict __dest,
   __const wchar_t *__restrict __src) throw ();

extern wchar_t *wcsncpy (wchar_t *__restrict __dest,
    __const wchar_t *__restrict __src, size_t __n)
     throw ();


extern wchar_t *wcscat (wchar_t *__restrict __dest,
   __const wchar_t *__restrict __src) throw ();

extern wchar_t *wcsncat (wchar_t *__restrict __dest,
    __const wchar_t *__restrict __src, size_t __n)
     throw ();


extern int wcscmp (__const wchar_t *__s1, __const wchar_t *__s2)
     throw () __attribute__ ((__pure__));

extern int wcsncmp (__const wchar_t *__s1, __const wchar_t *__s2, size_t __n)
     throw () __attribute__ ((__pure__));




extern int wcscasecmp (__const wchar_t *__s1, __const wchar_t *__s2) throw ();


extern int wcsncasecmp (__const wchar_t *__s1, __const wchar_t *__s2,
   size_t __n) throw ();



# 1 "/usr/include/xlocale.h" 1 3 4
# 28 "/usr/include/xlocale.h" 3 4
typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;
# 178 "/usr/include/wchar.h" 2 3 4

extern int wcscasecmp_l (__const wchar_t *__s1, __const wchar_t *__s2,
    __locale_t __loc) throw ();

extern int wcsncasecmp_l (__const wchar_t *__s1, __const wchar_t *__s2,
     size_t __n, __locale_t __loc) throw ();





extern int wcscoll (__const wchar_t *__s1, __const wchar_t *__s2) throw ();



extern size_t wcsxfrm (wchar_t *__restrict __s1,
         __const wchar_t *__restrict __s2, size_t __n) throw ();








extern int wcscoll_l (__const wchar_t *__s1, __const wchar_t *__s2,
        __locale_t __loc) throw ();




extern size_t wcsxfrm_l (wchar_t *__s1, __const wchar_t *__s2,
    size_t __n, __locale_t __loc) throw ();


extern wchar_t *wcsdup (__const wchar_t *__s) throw () __attribute__ ((__malloc__));





extern "C++" wchar_t *wcschr (wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcschr") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcschr (__const wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcschr") __attribute__ ((__pure__));






extern "C++" wchar_t *wcsrchr (wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcsrchr") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcsrchr (__const wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcsrchr") __attribute__ ((__pure__));









extern wchar_t *wcschrnul (__const wchar_t *__s, wchar_t __wc)
     throw () __attribute__ ((__pure__));





extern size_t wcscspn (__const wchar_t *__wcs, __const wchar_t *__reject)
     throw () __attribute__ ((__pure__));


extern size_t wcsspn (__const wchar_t *__wcs, __const wchar_t *__accept)
     throw () __attribute__ ((__pure__));


extern "C++" wchar_t *wcspbrk (wchar_t *__wcs, __const wchar_t *__accept)
     throw () __asm ("wcspbrk") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcspbrk (__const wchar_t *__wcs,
           __const wchar_t *__accept)
     throw () __asm ("wcspbrk") __attribute__ ((__pure__));






extern "C++" wchar_t *wcsstr (wchar_t *__haystack, __const wchar_t *__needle)
     throw () __asm ("wcsstr") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcsstr (__const wchar_t *__haystack,
          __const wchar_t *__needle)
     throw () __asm ("wcsstr") __attribute__ ((__pure__));






extern wchar_t *wcstok (wchar_t *__restrict __s,
   __const wchar_t *__restrict __delim,
   wchar_t **__restrict __ptr) throw ();


extern size_t wcslen (__const wchar_t *__s) throw () __attribute__ ((__pure__));





extern "C++" wchar_t *wcswcs (wchar_t *__haystack, __const wchar_t *__needle)
     throw () __asm ("wcswcs") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wcswcs (__const wchar_t *__haystack,
          __const wchar_t *__needle)
     throw () __asm ("wcswcs") __attribute__ ((__pure__));
# 303 "/usr/include/wchar.h" 3 4
extern size_t wcsnlen (__const wchar_t *__s, size_t __maxlen)
     throw () __attribute__ ((__pure__));






extern "C++" wchar_t *wmemchr (wchar_t *__s, wchar_t __c, size_t __n)
     throw () __asm ("wmemchr") __attribute__ ((__pure__));
extern "C++" __const wchar_t *wmemchr (__const wchar_t *__s, wchar_t __c,
           size_t __n)
     throw () __asm ("wmemchr") __attribute__ ((__pure__));






extern int wmemcmp (__const wchar_t *__restrict __s1,
      __const wchar_t *__restrict __s2, size_t __n)
     throw () __attribute__ ((__pure__));


extern wchar_t *wmemcpy (wchar_t *__restrict __s1,
    __const wchar_t *__restrict __s2, size_t __n) throw ();



extern wchar_t *wmemmove (wchar_t *__s1, __const wchar_t *__s2, size_t __n)
     throw ();


extern wchar_t *wmemset (wchar_t *__s, wchar_t __c, size_t __n) throw ();





extern wchar_t *wmempcpy (wchar_t *__restrict __s1,
     __const wchar_t *__restrict __s2, size_t __n)
     throw ();






extern wint_t btowc (int __c) throw ();



extern int wctob (wint_t __c) throw ();



extern int mbsinit (__const mbstate_t *__ps) throw () __attribute__ ((__pure__));



extern size_t mbrtowc (wchar_t *__restrict __pwc,
         __const char *__restrict __s, size_t __n,
         mbstate_t *__p) throw ();


extern size_t wcrtomb (char *__restrict __s, wchar_t __wc,
         mbstate_t *__restrict __ps) throw ();


extern size_t __mbrlen (__const char *__restrict __s, size_t __n,
   mbstate_t *__restrict __ps) throw ();
extern size_t mbrlen (__const char *__restrict __s, size_t __n,
        mbstate_t *__restrict __ps) throw ();

# 403 "/usr/include/wchar.h" 3 4



extern size_t mbsrtowcs (wchar_t *__restrict __dst,
    __const char **__restrict __src, size_t __len,
    mbstate_t *__restrict __ps) throw ();



extern size_t wcsrtombs (char *__restrict __dst,
    __const wchar_t **__restrict __src, size_t __len,
    mbstate_t *__restrict __ps) throw ();






extern size_t mbsnrtowcs (wchar_t *__restrict __dst,
     __const char **__restrict __src, size_t __nmc,
     size_t __len, mbstate_t *__restrict __ps) throw ();



extern size_t wcsnrtombs (char *__restrict __dst,
     __const wchar_t **__restrict __src,
     size_t __nwc, size_t __len,
     mbstate_t *__restrict __ps) throw ();






extern int wcwidth (wchar_t __c) throw ();



extern int wcswidth (__const wchar_t *__s, size_t __n) throw ();






extern double wcstod (__const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr) throw ();





extern float wcstof (__const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) throw ();
extern long double wcstold (__const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) throw ();







extern long int wcstol (__const wchar_t *__restrict __nptr,
   wchar_t **__restrict __endptr, int __base) throw ();



extern unsigned long int wcstoul (__const wchar_t *__restrict __nptr,
      wchar_t **__restrict __endptr, int __base)
     throw ();






__extension__
extern long long int wcstoll (__const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr, int __base)
     throw ();



__extension__
extern unsigned long long int wcstoull (__const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr,
     int __base) throw ();






__extension__
extern long long int wcstoq (__const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr, int __base)
     throw ();



__extension__
extern unsigned long long int wcstouq (__const wchar_t *__restrict __nptr,
           wchar_t **__restrict __endptr,
           int __base) throw ();
# 528 "/usr/include/wchar.h" 3 4
extern long int wcstol_l (__const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr, int __base,
     __locale_t __loc) throw ();

extern unsigned long int wcstoul_l (__const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr,
        int __base, __locale_t __loc) throw ();

__extension__
extern long long int wcstoll_l (__const wchar_t *__restrict __nptr,
    wchar_t **__restrict __endptr,
    int __base, __locale_t __loc) throw ();

__extension__
extern unsigned long long int wcstoull_l (__const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr,
       int __base, __locale_t __loc)
     throw ();

extern double wcstod_l (__const wchar_t *__restrict __nptr,
   wchar_t **__restrict __endptr, __locale_t __loc)
     throw ();

extern float wcstof_l (__const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr, __locale_t __loc)
     throw ();

extern long double wcstold_l (__const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr,
         __locale_t __loc) throw ();




extern wchar_t *wcpcpy (wchar_t *__restrict __dest,
   __const wchar_t *__restrict __src) throw ();



extern wchar_t *wcpncpy (wchar_t *__restrict __dest,
    __const wchar_t *__restrict __src, size_t __n)
     throw ();
# 578 "/usr/include/wchar.h" 3 4
extern __FILE *open_wmemstream (wchar_t **__bufloc, size_t *__sizeloc) throw ();






extern int fwide (__FILE *__fp, int __mode) throw ();






extern int fwprintf (__FILE *__restrict __stream,
       __const wchar_t *__restrict __format, ...)
                                                           ;




extern int wprintf (__const wchar_t *__restrict __format, ...)
                                                           ;

extern int swprintf (wchar_t *__restrict __s, size_t __n,
       __const wchar_t *__restrict __format, ...)
     throw () ;





extern int vfwprintf (__FILE *__restrict __s,
        __const wchar_t *__restrict __format,
        __gnuc_va_list __arg)
                                                           ;




extern int vwprintf (__const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
                                                           ;


extern int vswprintf (wchar_t *__restrict __s, size_t __n,
        __const wchar_t *__restrict __format,
        __gnuc_va_list __arg)
     throw () ;






extern int fwscanf (__FILE *__restrict __stream,
      __const wchar_t *__restrict __format, ...)
                                                          ;




extern int wscanf (__const wchar_t *__restrict __format, ...)
                                                          ;

extern int swscanf (__const wchar_t *__restrict __s,
      __const wchar_t *__restrict __format, ...)
     throw () ;
# 678 "/usr/include/wchar.h" 3 4









extern int vfwscanf (__FILE *__restrict __s,
       __const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
                                                          ;




extern int vwscanf (__const wchar_t *__restrict __format,
      __gnuc_va_list __arg)
                                                          ;

extern int vswscanf (__const wchar_t *__restrict __s,
       __const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
     throw () ;
# 734 "/usr/include/wchar.h" 3 4









extern wint_t fgetwc (__FILE *__stream);
extern wint_t getwc (__FILE *__stream);





extern wint_t getwchar (void);






extern wint_t fputwc (wchar_t __wc, __FILE *__stream);
extern wint_t putwc (wchar_t __wc, __FILE *__stream);





extern wint_t putwchar (wchar_t __wc);







extern wchar_t *fgetws (wchar_t *__restrict __ws, int __n,
   __FILE *__restrict __stream);





extern int fputws (__const wchar_t *__restrict __ws,
     __FILE *__restrict __stream);






extern wint_t ungetwc (wint_t __wc, __FILE *__stream);

# 799 "/usr/include/wchar.h" 3 4
extern wint_t getwc_unlocked (__FILE *__stream);
extern wint_t getwchar_unlocked (void);







extern wint_t fgetwc_unlocked (__FILE *__stream);







extern wint_t fputwc_unlocked (wchar_t __wc, __FILE *__stream);
# 825 "/usr/include/wchar.h" 3 4
extern wint_t putwc_unlocked (wchar_t __wc, __FILE *__stream);
extern wint_t putwchar_unlocked (wchar_t __wc);
# 835 "/usr/include/wchar.h" 3 4
extern wchar_t *fgetws_unlocked (wchar_t *__restrict __ws, int __n,
     __FILE *__restrict __stream);







extern int fputws_unlocked (__const wchar_t *__restrict __ws,
       __FILE *__restrict __stream);







extern size_t wcsftime (wchar_t *__restrict __s, size_t __maxsize,
   __const wchar_t *__restrict __format,
   __const struct tm *__restrict __tp) throw ();







extern size_t wcsftime_l (wchar_t *__restrict __s, size_t __maxsize,
     __const wchar_t *__restrict __format,
     __const struct tm *__restrict __tp,
     __locale_t __loc) throw ();
# 889 "/usr/include/wchar.h" 3 4
}
# 45 "/usr/local/include/c++/4.9.0/cwchar" 2 3
# 62 "/usr/local/include/c++/4.9.0/cwchar" 3
namespace std
{
  using ::mbstate_t;
}
# 135 "/usr/local/include/c++/4.9.0/cwchar" 3
namespace std __attribute__ ((__visibility__ ("default")))
{


  using ::wint_t;

  using ::btowc;
  using ::fgetwc;
  using ::fgetws;
  using ::fputwc;
  using ::fputws;
  using ::fwide;
  using ::fwprintf;
  using ::fwscanf;
  using ::getwc;
  using ::getwchar;
  using ::mbrlen;
  using ::mbrtowc;
  using ::mbsinit;
  using ::mbsrtowcs;
  using ::putwc;
  using ::putwchar;

  using ::swprintf;

  using ::swscanf;
  using ::ungetwc;
  using ::vfwprintf;

  using ::vfwscanf;


  using ::vswprintf;


  using ::vswscanf;

  using ::vwprintf;

  using ::vwscanf;

  using ::wcrtomb;
  using ::wcscat;
  using ::wcscmp;
  using ::wcscoll;
  using ::wcscpy;
  using ::wcscspn;
  using ::wcsftime;
  using ::wcslen;
  using ::wcsncat;
  using ::wcsncmp;
  using ::wcsncpy;
  using ::wcsrtombs;
  using ::wcsspn;
  using ::wcstod;

  using ::wcstof;

  using ::wcstok;
  using ::wcstol;
  using ::wcstoul;
  using ::wcsxfrm;
  using ::wctob;
  using ::wmemcmp;
  using ::wmemcpy;
  using ::wmemmove;
  using ::wmemset;
  using ::wprintf;
  using ::wscanf;
  using ::wcschr;
  using ::wcspbrk;
  using ::wcsrchr;
  using ::wcsstr;
  using ::wmemchr;
# 232 "/usr/local/include/c++/4.9.0/cwchar" 3

}







namespace __gnu_cxx
{





  using ::wcstold;
# 257 "/usr/local/include/c++/4.9.0/cwchar" 3
  using ::wcstoll;
  using ::wcstoull;

}

namespace std
{
  using ::__gnu_cxx::wcstold;
  using ::__gnu_cxx::wcstoll;
  using ::__gnu_cxx::wcstoull;
}
# 41 "/usr/local/include/c++/4.9.0/bits/postypes.h" 2 3
# 68 "/usr/local/include/c++/4.9.0/bits/postypes.h" 3
namespace std __attribute__ ((__visibility__ ("default")))
{

# 88 "/usr/local/include/c++/4.9.0/bits/postypes.h" 3
  typedef long streamoff;
# 98 "/usr/local/include/c++/4.9.0/bits/postypes.h" 3
  typedef ptrdiff_t streamsize;
# 111 "/usr/local/include/c++/4.9.0/bits/postypes.h" 3
  template<typename _StateT>
    class fpos
    {
    private:
      streamoff _M_off;
      _StateT _M_state;

    public:




      fpos()
      : _M_off(0), _M_state() { }
# 133 "/usr/local/include/c++/4.9.0/bits/postypes.h" 3
      fpos(streamoff __off)
      : _M_off(__off), _M_state() { }


      operator streamoff() const { return _M_off; }


      void
      state(_StateT __st)
      { _M_state = __st; }


      _StateT
      state() const
      { return _M_state; }





      fpos&
      operator+=(streamoff __off)
      {
 _M_off += __off;
 return *this;
      }





      fpos&
      operator-=(streamoff __off)
      {
 _M_off -= __off;
 return *this;
      }







      fpos
      operator+(streamoff __off) const
      {
 fpos __pos(*this);
 __pos += __off;
 return __pos;
      }







      fpos
      operator-(streamoff __off) const
      {
 fpos __pos(*this);
 __pos -= __off;
 return __pos;
      }






      streamoff
      operator-(const fpos& __other) const
      { return _M_off - __other._M_off; }
    };






  template<typename _StateT>
    inline bool
    operator==(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) == streamoff(__rhs); }

  template<typename _StateT>
    inline bool
    operator!=(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) != streamoff(__rhs); }





  typedef fpos<mbstate_t> streampos;

  typedef fpos<mbstate_t> wstreampos;
# 239 "/usr/local/include/c++/4.9.0/bits/postypes.h" 3

}
# 41 "/usr/local/include/c++/4.9.0/bits/char_traits.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/cwchar" 1 3
# 39 "/usr/local/include/c++/4.9.0/cwchar" 3
       
# 40 "/usr/local/include/c++/4.9.0/cwchar" 3




# 1 "/usr/include/wchar.h" 1 3 4
# 45 "/usr/local/include/c++/4.9.0/cwchar" 2 3
# 42 "/usr/local/include/c++/4.9.0/bits/char_traits.h" 2 3

namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

# 57 "/usr/local/include/c++/4.9.0/bits/char_traits.h" 3
  template<typename _CharT>
    struct _Char_types
    {
      typedef unsigned long int_type;
      typedef std::streampos pos_type;
      typedef std::streamoff off_type;
      typedef std::mbstate_t state_type;
    };
# 82 "/usr/local/include/c++/4.9.0/bits/char_traits.h" 3
  template<typename _CharT>
    struct char_traits
    {
      typedef _CharT char_type;
      typedef typename _Char_types<_CharT>::int_type int_type;
      typedef typename _Char_types<_CharT>::pos_type pos_type;
      typedef typename _Char_types<_CharT>::off_type off_type;
      typedef typename _Char_types<_CharT>::state_type state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }

      static int
      compare(const char_type* __s1, const char_type* __s2, std::size_t __n);

      static std::size_t
      length(const char_type* __s);

      static const char_type*
      find(const char_type* __s, std::size_t __n, const char_type& __a);

      static char_type*
      move(char_type* __s1, const char_type* __s2, std::size_t __n);

      static char_type*
      copy(char_type* __s1, const char_type* __s2, std::size_t __n);

      static char_type*
      assign(char_type* __s, std::size_t __n, char_type __a);

      static char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }

      static int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(__c); }

      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static int_type
      eof()
      { return static_cast<int_type>(-1); }

      static int_type
      not_eof(const int_type& __c)
      { return !eq_int_type(__c, eof()) ? __c : to_int_type(char_type()); }
    };

  template<typename _CharT>
    int
    char_traits<_CharT>::
    compare(const char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
 if (lt(__s1[__i], __s2[__i]))
   return -1;
 else if (lt(__s2[__i], __s1[__i]))
   return 1;
      return 0;
    }

  template<typename _CharT>
    std::size_t
    char_traits<_CharT>::
    length(const char_type* __p)
    {
      std::size_t __i = 0;
      while (!eq(__p[__i], char_type()))
        ++__i;
      return __i;
    }

  template<typename _CharT>
    const typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    find(const char_type* __s, std::size_t __n, const char_type& __a)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
        if (eq(__s[__i], __a))
          return __s + __i;
      return 0;
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    move(char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      return static_cast<_CharT*>(__builtin_memmove(__s1, __s2,
          __n * sizeof(char_type)));
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    copy(char_type* __s1, const char_type* __s2, std::size_t __n)
    {

      std::copy(__s2, __s2 + __n, __s1);
      return __s1;
    }

  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    assign(char_type* __s, std::size_t __n, char_type __a)
    {

      std::fill_n(__s, __n, __a);
      return __s;
    }


}

namespace std __attribute__ ((__visibility__ ("default")))
{

# 226 "/usr/local/include/c++/4.9.0/bits/char_traits.h" 3
  template<class _CharT>
    struct char_traits : public __gnu_cxx::char_traits<_CharT>
    { };



  template<>
    struct char_traits<char>
    {
      typedef char char_type;
      typedef int int_type;
      typedef streampos pos_type;
      typedef streamoff off_type;
      typedef mbstate_t state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static bool
      lt(const char_type& __c1, const char_type& __c2)
      {

 return (static_cast<unsigned char>(__c1)
  < static_cast<unsigned char>(__c2));
      }

      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return __builtin_memcmp(__s1, __s2, __n); }

      static size_t
      length(const char_type* __s)
      { return __builtin_strlen(__s); }

      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return static_cast<const char_type*>(__builtin_memchr(__s, __a, __n)); }

      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      { return static_cast<char_type*>(__builtin_memmove(__s1, __s2, __n)); }

      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return static_cast<char_type*>(__builtin_memcpy(__s1, __s2, __n)); }

      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      { return static_cast<char_type*>(__builtin_memset(__s, __a, __n)); }

      static char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }



      static int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(static_cast<unsigned char>(__c)); }

      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static int_type
      eof()
      { return static_cast<int_type>(-1); }

      static int_type
      not_eof(const int_type& __c)
      { return (__c == eof()) ? 0 : __c; }
  };




  template<>
    struct char_traits<wchar_t>
    {
      typedef wchar_t char_type;
      typedef wint_t int_type;
      typedef streamoff off_type;
      typedef wstreampos pos_type;
      typedef mbstate_t state_type;

      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }

      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }

      static bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }

      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcmp(__s1, __s2, __n); }

      static size_t
      length(const char_type* __s)
      { return wcslen(__s); }

      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return wmemchr(__s, __a, __n); }

      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemmove(__s1, __s2, __n); }

      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcpy(__s1, __s2, __n); }

      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      { return wmemset(__s, __a, __n); }

      static char_type
      to_char_type(const int_type& __c)
      { return char_type(__c); }

      static int_type
      to_int_type(const char_type& __c)
      { return int_type(__c); }

      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }

      static int_type
      eof()
      { return static_cast<int_type>((0xffffffffu)); }

      static int_type
      not_eof(const int_type& __c)
      { return eq_int_type(__c, eof()) ? 0 : __c; }
  };



}
# 41 "/usr/local/include/c++/4.9.0/string" 2 3


# 1 "/usr/local/include/c++/4.9.0/bits/localefwd.h" 1 3
# 37 "/usr/local/include/c++/4.9.0/bits/localefwd.h" 3
       
# 38 "/usr/local/include/c++/4.9.0/bits/localefwd.h" 3


# 1 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++locale.h" 1 3
# 39 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++locale.h" 3
       
# 40 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++locale.h" 3

# 1 "/usr/local/include/c++/4.9.0/clocale" 1 3
# 39 "/usr/local/include/c++/4.9.0/clocale" 3
       
# 40 "/usr/local/include/c++/4.9.0/clocale" 3


# 1 "/usr/include/locale.h" 1 3 4
# 29 "/usr/include/locale.h" 3 4
# 1 "/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.9.0/include/stddef.h" 1 3 4
# 30 "/usr/include/locale.h" 2 3 4
# 1 "/usr/include/bits/locale.h" 1 3 4
# 27 "/usr/include/bits/locale.h" 3 4
enum
{
  __LC_CTYPE = 0,
  __LC_NUMERIC = 1,
  __LC_TIME = 2,
  __LC_COLLATE = 3,
  __LC_MONETARY = 4,
  __LC_MESSAGES = 5,
  __LC_ALL = 6,
  __LC_PAPER = 7,
  __LC_NAME = 8,
  __LC_ADDRESS = 9,
  __LC_TELEPHONE = 10,
  __LC_MEASUREMENT = 11,
  __LC_IDENTIFICATION = 12
};
# 31 "/usr/include/locale.h" 2 3 4

extern "C" {
# 51 "/usr/include/locale.h" 3 4



struct lconv
{


  char *decimal_point;
  char *thousands_sep;





  char *grouping;





  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;

  char p_cs_precedes;

  char p_sep_by_space;

  char n_cs_precedes;

  char n_sep_by_space;






  char p_sign_posn;
  char n_sign_posn;


  char int_p_cs_precedes;

  char int_p_sep_by_space;

  char int_n_cs_precedes;

  char int_n_sep_by_space;






  char int_p_sign_posn;
  char int_n_sign_posn;
# 121 "/usr/include/locale.h" 3 4
};



extern char *setlocale (int __category, __const char *__locale) throw ();


extern struct lconv *localeconv (void) throw ();


# 152 "/usr/include/locale.h" 3 4
extern __locale_t newlocale (int __category_mask, __const char *__locale,
        __locale_t __base) throw ();
# 187 "/usr/include/locale.h" 3 4
extern __locale_t duplocale (__locale_t __dataset) throw ();



extern void freelocale (__locale_t __dataset) throw ();






extern __locale_t uselocale (__locale_t __dataset) throw ();







}
# 43 "/usr/local/include/c++/4.9.0/clocale" 2 3
# 51 "/usr/local/include/c++/4.9.0/clocale" 3
namespace std
{
  using ::lconv;
  using ::setlocale;
  using ::localeconv;
}
# 42 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++locale.h" 2 3






namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{


  extern "C" __typeof(uselocale) __uselocale;


}


namespace std __attribute__ ((__visibility__ ("default")))
{


  typedef __locale_t __c_locale;





  inline int
  __convert_from_v(const __c_locale& __cloc __attribute__ ((__unused__)),
     char* __out,
     const int __size __attribute__ ((__unused__)),
     const char* __fmt, ...)
  {

    __c_locale __old = __gnu_cxx::__uselocale(__cloc);
# 88 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/c++locale.h" 3
    __builtin_va_list __args;
    __builtin_va_start(__args, __fmt);


    const int __ret = __builtin_vsnprintf(__out, __size, __fmt, __args);




    __builtin_va_end(__args);


    __gnu_cxx::__uselocale(__old);







    return __ret;
  }


}
# 41 "/usr/local/include/c++/4.9.0/bits/localefwd.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/iosfwd" 1 3
# 36 "/usr/local/include/c++/4.9.0/iosfwd" 3
       
# 37 "/usr/local/include/c++/4.9.0/iosfwd" 3





namespace std __attribute__ ((__visibility__ ("default")))
{

# 74 "/usr/local/include/c++/4.9.0/iosfwd" 3
  class ios_base;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ios;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_streambuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_istream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ostream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_iostream;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
     typename _Alloc = allocator<_CharT> >
    class basic_stringbuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_istringstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_ostringstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_stringstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_filebuf;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ifstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ofstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_fstream;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class istreambuf_iterator;

  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class ostreambuf_iterator;



  typedef basic_ios<char> ios;


  typedef basic_streambuf<char> streambuf;


  typedef basic_istream<char> istream;


  typedef basic_ostream<char> ostream;


  typedef basic_iostream<char> iostream;


  typedef basic_stringbuf<char> stringbuf;


  typedef basic_istringstream<char> istringstream;


  typedef basic_ostringstream<char> ostringstream;


  typedef basic_stringstream<char> stringstream;


  typedef basic_filebuf<char> filebuf;


  typedef basic_ifstream<char> ifstream;


  typedef basic_ofstream<char> ofstream;


  typedef basic_fstream<char> fstream;



  typedef basic_ios<wchar_t> wios;


  typedef basic_streambuf<wchar_t> wstreambuf;


  typedef basic_istream<wchar_t> wistream;


  typedef basic_ostream<wchar_t> wostream;


  typedef basic_iostream<wchar_t> wiostream;


  typedef basic_stringbuf<wchar_t> wstringbuf;


  typedef basic_istringstream<wchar_t> wistringstream;


  typedef basic_ostringstream<wchar_t> wostringstream;


  typedef basic_stringstream<wchar_t> wstringstream;


  typedef basic_filebuf<wchar_t> wfilebuf;


  typedef basic_ifstream<wchar_t> wifstream;


  typedef basic_ofstream<wchar_t> wofstream;


  typedef basic_fstream<wchar_t> wfstream;




}
# 42 "/usr/local/include/c++/4.9.0/bits/localefwd.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/cctype" 1 3
# 39 "/usr/local/include/c++/4.9.0/cctype" 3
       
# 40 "/usr/local/include/c++/4.9.0/cctype" 3


# 1 "/usr/include/ctype.h" 1 3 4
# 28 "/usr/include/ctype.h" 3 4
# 1 "/usr/include/bits/types.h" 1 3 4
# 28 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
# 131 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 132 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef long int __swblk_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

typedef long int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;
# 29 "/usr/include/ctype.h" 2 3 4

extern "C" {
# 41 "/usr/include/ctype.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 38 "/usr/include/endian.h" 2 3 4
# 61 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 28 "/usr/include/bits/byteswap.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/byteswap.h" 2 3 4
# 62 "/usr/include/endian.h" 2 3 4
# 42 "/usr/include/ctype.h" 2 3 4






enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
# 81 "/usr/include/ctype.h" 3 4
extern __const unsigned short int **__ctype_b_loc (void)
     throw () __attribute__ ((__const));
extern __const __int32_t **__ctype_tolower_loc (void)
     throw () __attribute__ ((__const));
extern __const __int32_t **__ctype_toupper_loc (void)
     throw () __attribute__ ((__const));
# 96 "/usr/include/ctype.h" 3 4






extern int isalnum (int) throw ();
extern int isalpha (int) throw ();
extern int iscntrl (int) throw ();
extern int isdigit (int) throw ();
extern int islower (int) throw ();
extern int isgraph (int) throw ();
extern int isprint (int) throw ();
extern int ispunct (int) throw ();
extern int isspace (int) throw ();
extern int isupper (int) throw ();
extern int isxdigit (int) throw ();



extern int tolower (int __c) throw ();


extern int toupper (int __c) throw ();








extern int isblank (int) throw ();






extern int isctype (int __c, int __mask) throw ();






extern int isascii (int __c) throw ();



extern int toascii (int __c) throw ();



extern int _toupper (int) throw ();
extern int _tolower (int) throw ();
# 247 "/usr/include/ctype.h" 3 4
extern int isalnum_l (int, __locale_t) throw ();
extern int isalpha_l (int, __locale_t) throw ();
extern int iscntrl_l (int, __locale_t) throw ();
extern int isdigit_l (int, __locale_t) throw ();
extern int islower_l (int, __locale_t) throw ();
extern int isgraph_l (int, __locale_t) throw ();
extern int isprint_l (int, __locale_t) throw ();
extern int ispunct_l (int, __locale_t) throw ();
extern int isspace_l (int, __locale_t) throw ();
extern int isupper_l (int, __locale_t) throw ();
extern int isxdigit_l (int, __locale_t) throw ();

extern int isblank_l (int, __locale_t) throw ();



extern int __tolower_l (int __c, __locale_t __l) throw ();
extern int tolower_l (int __c, __locale_t __l) throw ();


extern int __toupper_l (int __c, __locale_t __l) throw ();
extern int toupper_l (int __c, __locale_t __l) throw ();
# 323 "/usr/include/ctype.h" 3 4
}
# 43 "/usr/local/include/c++/4.9.0/cctype" 2 3
# 62 "/usr/local/include/c++/4.9.0/cctype" 3
namespace std
{
  using ::isalnum;
  using ::isalpha;
  using ::iscntrl;
  using ::isdigit;
  using ::isgraph;
  using ::islower;
  using ::isprint;
  using ::ispunct;
  using ::isspace;
  using ::isupper;
  using ::isxdigit;
  using ::tolower;
  using ::toupper;
}
# 43 "/usr/local/include/c++/4.9.0/bits/localefwd.h" 2 3

namespace std __attribute__ ((__visibility__ ("default")))
{

# 55 "/usr/local/include/c++/4.9.0/bits/localefwd.h" 3
  class locale;

  template<typename _Facet>
    bool
    has_facet(const locale&) throw();

  template<typename _Facet>
    const _Facet&
    use_facet(const locale&);


  template<typename _CharT>
    bool
    isspace(_CharT, const locale&);

  template<typename _CharT>
    bool
    isprint(_CharT, const locale&);

  template<typename _CharT>
    bool
    iscntrl(_CharT, const locale&);

  template<typename _CharT>
    bool
    isupper(_CharT, const locale&);

  template<typename _CharT>
    bool
    islower(_CharT, const locale&);

  template<typename _CharT>
    bool
    isalpha(_CharT, const locale&);

  template<typename _CharT>
    bool
    isdigit(_CharT, const locale&);

  template<typename _CharT>
    bool
    ispunct(_CharT, const locale&);

  template<typename _CharT>
    bool
    isxdigit(_CharT, const locale&);

  template<typename _CharT>
    bool
    isalnum(_CharT, const locale&);

  template<typename _CharT>
    bool
    isgraph(_CharT, const locale&);

  template<typename _CharT>
    _CharT
    toupper(_CharT, const locale&);

  template<typename _CharT>
    _CharT
    tolower(_CharT, const locale&);


  class ctype_base;
  template<typename _CharT>
    class ctype;
  template<> class ctype<char>;

  template<> class ctype<wchar_t>;

  template<typename _CharT>
    class ctype_byname;


  class codecvt_base;
  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt;
  template<> class codecvt<char, char, mbstate_t>;

  template<> class codecvt<wchar_t, char, mbstate_t>;

  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt_byname;



  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class num_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class num_put;

  template<typename _CharT> class numpunct;
  template<typename _CharT> class numpunct_byname;


  template<typename _CharT>
    class collate;
  template<typename _CharT> class
    collate_byname;


  class time_base;
  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class time_get;
  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class time_get_byname;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put_byname;


  class money_base;

  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class money_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class money_put;

  template<typename _CharT, bool _Intl = false>
    class moneypunct;
  template<typename _CharT, bool _Intl = false>
    class moneypunct_byname;


  class messages_base;
  template<typename _CharT>
    class messages;
  template<typename _CharT>
    class messages_byname;


}
# 44 "/usr/local/include/c++/4.9.0/string" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/ostream_insert.h" 1 3
# 33 "/usr/local/include/c++/4.9.0/bits/ostream_insert.h" 3
       
# 34 "/usr/local/include/c++/4.9.0/bits/ostream_insert.h" 3


# 1 "/usr/local/include/c++/4.9.0/bits/cxxabi_forced.h" 1 3
# 34 "/usr/local/include/c++/4.9.0/bits/cxxabi_forced.h" 3
       
# 35 "/usr/local/include/c++/4.9.0/bits/cxxabi_forced.h" 3

#pragma GCC visibility push(default)


namespace __cxxabiv1
{







  class __forced_unwind
  {
    virtual ~__forced_unwind() throw();


    virtual void __pure_dummy() = 0;
  };
}


#pragma GCC visibility pop
# 37 "/usr/local/include/c++/4.9.0/bits/ostream_insert.h" 2 3

namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits>
    inline void
    __ostream_write(basic_ostream<_CharT, _Traits>& __out,
      const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;

      const streamsize __put = __out.rdbuf()->sputn(__s, __n);
      if (__put != __n)
 __out.setstate(__ios_base::badbit);
    }

  template<typename _CharT, typename _Traits>
    inline void
    __ostream_fill(basic_ostream<_CharT, _Traits>& __out, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;

      const _CharT __c = __out.fill();
      for (; __n > 0; --__n)
 {
   const typename _Traits::int_type __put = __out.rdbuf()->sputc(__c);
   if (_Traits::eq_int_type(__put, _Traits::eof()))
     {
       __out.setstate(__ios_base::badbit);
       break;
     }
 }
    }

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    __ostream_insert(basic_ostream<_CharT, _Traits>& __out,
       const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;

      typename __ostream_type::sentry __cerb(__out);
      if (__cerb)
 {
   try
     {
       const streamsize __w = __out.width();
       if (__w > __n)
  {
    const bool __left = ((__out.flags()
     & __ios_base::adjustfield)
           == __ios_base::left);
    if (!__left)
      __ostream_fill(__out, __w - __n);
    if (__out.good())
      __ostream_write(__out, __s, __n);
    if (__left && __out.good())
      __ostream_fill(__out, __w - __n);
  }
       else
  __ostream_write(__out, __s, __n);
       __out.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __out._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     { __out._M_setstate(__ios_base::badbit); }
 }
      return __out;
    }




  extern template ostream& __ostream_insert(ostream&, const char*, streamsize);


  extern template wostream& __ostream_insert(wostream&, const wchar_t*,
          streamsize);




}
# 45 "/usr/local/include/c++/4.9.0/string" 2 3







# 1 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 1 3
# 37 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
       
# 38 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3

# 1 "/usr/local/include/c++/4.9.0/ext/atomicity.h" 1 3
# 32 "/usr/local/include/c++/4.9.0/ext/atomicity.h" 3
       
# 33 "/usr/local/include/c++/4.9.0/ext/atomicity.h" 3


# 1 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr.h" 1 3
# 30 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr.h" 3
#pragma GCC visibility push(default)
# 148 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr.h" 3
# 1 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 1 3
# 35 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 3
# 1 "/usr/include/pthread.h" 1 3 4
# 25 "/usr/include/pthread.h" 3 4
# 1 "/usr/include/sched.h" 1 3 4
# 30 "/usr/include/sched.h" 3 4
# 1 "/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.9.0/include/stddef.h" 1 3 4
# 31 "/usr/include/sched.h" 2 3 4



# 1 "/usr/include/time.h" 1 3 4
# 74 "/usr/include/time.h" 3 4


typedef __time_t time_t;



# 120 "/usr/include/time.h" 3 4
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
# 35 "/usr/include/sched.h" 2 3 4


typedef __pid_t pid_t;





# 1 "/usr/include/bits/sched.h" 1 3 4
# 74 "/usr/include/bits/sched.h" 3 4
struct sched_param
  {
    int __sched_priority;
  };

extern "C" {



extern int clone (int (*__fn) (void *__arg), void *__child_stack,
    int __flags, void *__arg, ...) throw ();


extern int unshare (int __flags) throw ();


extern int sched_getcpu (void) throw ();


}







struct __sched_param
  {
    int __sched_priority;
  };
# 116 "/usr/include/bits/sched.h" 3 4
typedef unsigned long int __cpu_mask;






typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;
# 199 "/usr/include/bits/sched.h" 3 4
extern "C" {

extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
  throw ();
extern cpu_set_t *__sched_cpualloc (size_t __count) throw () ;
extern void __sched_cpufree (cpu_set_t *__set) throw ();

}
# 44 "/usr/include/sched.h" 2 3 4




extern "C" {


extern int sched_setparam (__pid_t __pid, __const struct sched_param *__param)
     throw ();


extern int sched_getparam (__pid_t __pid, struct sched_param *__param) throw ();


extern int sched_setscheduler (__pid_t __pid, int __policy,
          __const struct sched_param *__param) throw ();


extern int sched_getscheduler (__pid_t __pid) throw ();


extern int sched_yield (void) throw ();


extern int sched_get_priority_max (int __algorithm) throw ();


extern int sched_get_priority_min (int __algorithm) throw ();


extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) throw ();
# 118 "/usr/include/sched.h" 3 4
extern int sched_setaffinity (__pid_t __pid, size_t __cpusetsize,
         __const cpu_set_t *__cpuset) throw ();


extern int sched_getaffinity (__pid_t __pid, size_t __cpusetsize,
         cpu_set_t *__cpuset) throw ();


}
# 26 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/time.h" 1 3 4
# 30 "/usr/include/time.h" 3 4
extern "C" {







# 1 "/usr/local/lib/gcc/x86_64-unknown-linux-gnu/4.9.0/include/stddef.h" 1 3 4
# 39 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/bits/time.h" 1 3 4
# 43 "/usr/include/time.h" 2 3 4
# 58 "/usr/include/time.h" 3 4


typedef __clock_t clock_t;



# 92 "/usr/include/time.h" 3 4
typedef __clockid_t clockid_t;
# 104 "/usr/include/time.h" 3 4
typedef __timer_t timer_t;
# 131 "/usr/include/time.h" 3 4


struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  __const char *tm_zone;




};








struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };


struct sigevent;
# 180 "/usr/include/time.h" 3 4



extern clock_t clock (void) throw ();


extern time_t time (time_t *__timer) throw ();


extern double difftime (time_t __time1, time_t __time0)
     throw () __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) throw ();





extern size_t strftime (char *__restrict __s, size_t __maxsize,
   __const char *__restrict __format,
   __const struct tm *__restrict __tp) throw ();





extern char *strptime (__const char *__restrict __s,
         __const char *__restrict __fmt, struct tm *__tp)
     throw ();







extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     __const char *__restrict __format,
     __const struct tm *__restrict __tp,
     __locale_t __loc) throw ();



extern char *strptime_l (__const char *__restrict __s,
    __const char *__restrict __fmt, struct tm *__tp,
    __locale_t __loc) throw ();






extern struct tm *gmtime (__const time_t *__timer) throw ();



extern struct tm *localtime (__const time_t *__timer) throw ();





extern struct tm *gmtime_r (__const time_t *__restrict __timer,
       struct tm *__restrict __tp) throw ();



extern struct tm *localtime_r (__const time_t *__restrict __timer,
          struct tm *__restrict __tp) throw ();





extern char *asctime (__const struct tm *__tp) throw ();


extern char *ctime (__const time_t *__timer) throw ();







extern char *asctime_r (__const struct tm *__restrict __tp,
   char *__restrict __buf) throw ();


extern char *ctime_r (__const time_t *__restrict __timer,
        char *__restrict __buf) throw ();




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) throw ();



extern int daylight;
extern long int timezone;





extern int stime (__const time_t *__when) throw ();
# 313 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) throw ();


extern time_t timelocal (struct tm *__tp) throw ();


extern int dysize (int __year) throw () __attribute__ ((__const__));
# 328 "/usr/include/time.h" 3 4
extern int nanosleep (__const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) throw ();


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) throw ();


extern int clock_settime (clockid_t __clock_id, __const struct timespec *__tp)
     throw ();






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       __const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) throw ();




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) throw ();


extern int timer_delete (timer_t __timerid) throw ();


extern int timer_settime (timer_t __timerid, int __flags,
     __const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) throw ();


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     throw ();


extern int timer_getoverrun (timer_t __timerid) throw ();
# 390 "/usr/include/time.h" 3 4
extern int getdate_err;
# 399 "/usr/include/time.h" 3 4
extern struct tm *getdate (__const char *__string);
# 413 "/usr/include/time.h" 3 4
extern int getdate_r (__const char *__restrict __string,
        struct tm *__restrict __resbufp);


}
# 27 "/usr/include/pthread.h" 2 3 4

# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 24 "/usr/include/bits/pthreadtypes.h" 2 3 4
# 50 "/usr/include/bits/pthreadtypes.h" 3 4
typedef unsigned long int pthread_t;


typedef union
{
  char __size[56];
  long int __align;
} pthread_attr_t;



typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
# 76 "/usr/include/bits/pthreadtypes.h" 3 4
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;

    unsigned int __nusers;



    int __kind;

    int __spins;
    __pthread_list_t __list;
# 101 "/usr/include/bits/pthreadtypes.h" 3 4
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{

  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;


    unsigned int __flags;
  } __data;
# 187 "/usr/include/bits/pthreadtypes.h" 3 4
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 29 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/bits/setjmp.h" 1 3 4
# 27 "/usr/include/bits/setjmp.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/setjmp.h" 2 3 4




typedef long int __jmp_buf[8];
# 30 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 31 "/usr/include/pthread.h" 2 3 4



enum
{
  PTHREAD_CREATE_JOINABLE,

  PTHREAD_CREATE_DETACHED

};



enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP

  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL



  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP

};




enum
{
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};





enum
{
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT
};
# 115 "/usr/include/pthread.h" 3 4
enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
# 147 "/usr/include/pthread.h" 3 4
enum
{
  PTHREAD_INHERIT_SCHED,

  PTHREAD_EXPLICIT_SCHED

};



enum
{
  PTHREAD_SCOPE_SYSTEM,

  PTHREAD_SCOPE_PROCESS

};



enum
{
  PTHREAD_PROCESS_PRIVATE,

  PTHREAD_PROCESS_SHARED

};
# 182 "/usr/include/pthread.h" 3 4
struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
};


enum
{
  PTHREAD_CANCEL_ENABLE,

  PTHREAD_CANCEL_DISABLE

};
enum
{
  PTHREAD_CANCEL_DEFERRED,

  PTHREAD_CANCEL_ASYNCHRONOUS

};
# 220 "/usr/include/pthread.h" 3 4
extern "C" {




extern int pthread_create (pthread_t *__restrict __newthread,
      __const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) throw () __attribute__ ((__nonnull__ (1, 3)));





extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));







extern int pthread_join (pthread_t __th, void **__thread_return);




extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) throw ();







extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
     __const struct timespec *__abstime);






extern int pthread_detach (pthread_t __th) throw ();



extern pthread_t pthread_self (void) throw () __attribute__ ((__const__));


extern int pthread_equal (pthread_t __thread1, pthread_t __thread2) throw ();







extern int pthread_attr_init (pthread_attr_t *__attr) throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_destroy (pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getdetachstate (__const pthread_attr_t *__attr,
     int *__detachstate)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
     int __detachstate)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getguardsize (__const pthread_attr_t *__attr,
          size_t *__guardsize)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
          size_t __guardsize)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getschedparam (__const pthread_attr_t *__restrict
           __attr,
           struct sched_param *__restrict __param)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedparam (pthread_attr_t *__restrict __attr,
           __const struct sched_param *__restrict
           __param) throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_getschedpolicy (__const pthread_attr_t *__restrict
     __attr, int *__restrict __policy)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getinheritsched (__const pthread_attr_t *__restrict
      __attr, int *__restrict __inherit)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
      int __inherit)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getscope (__const pthread_attr_t *__restrict __attr,
      int *__restrict __scope)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getstackaddr (__const pthread_attr_t *__restrict
          __attr, void **__restrict __stackaddr)
     throw () __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__deprecated__));





extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
          void *__stackaddr)
     throw () __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__));


extern int pthread_attr_getstacksize (__const pthread_attr_t *__restrict
          __attr, size_t *__restrict __stacksize)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
          size_t __stacksize)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getstack (__const pthread_attr_t *__restrict __attr,
      void **__restrict __stackaddr,
      size_t *__restrict __stacksize)
     throw () __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
      size_t __stacksize) throw () __attribute__ ((__nonnull__ (1)));





extern int pthread_attr_setaffinity_np (pthread_attr_t *__attr,
     size_t __cpusetsize,
     __const cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (1, 3)));



extern int pthread_attr_getaffinity_np (__const pthread_attr_t *__attr,
     size_t __cpusetsize,
     cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (1, 3)));





extern int pthread_getattr_np (pthread_t __th, pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (2)));







extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
      __const struct sched_param *__param)
     throw () __attribute__ ((__nonnull__ (3)));


extern int pthread_getschedparam (pthread_t __target_thread,
      int *__restrict __policy,
      struct sched_param *__restrict __param)
     throw () __attribute__ ((__nonnull__ (2, 3)));


extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     throw ();




extern int pthread_getname_np (pthread_t __target_thread, char *__buf,
          size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2)));


extern int pthread_setname_np (pthread_t __target_thread, __const char *__name)
     throw () __attribute__ ((__nonnull__ (2)));





extern int pthread_getconcurrency (void) throw ();


extern int pthread_setconcurrency (int __level) throw ();







extern int pthread_yield (void) throw ();




extern int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize,
       __const cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (3)));


extern int pthread_getaffinity_np (pthread_t __th, size_t __cpusetsize,
       cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (3)));
# 478 "/usr/include/pthread.h" 3 4
extern int pthread_once (pthread_once_t *__once_control,
    void (*__init_routine) (void)) __attribute__ ((__nonnull__ (1, 2)));
# 490 "/usr/include/pthread.h" 3 4
extern int pthread_setcancelstate (int __state, int *__oldstate);



extern int pthread_setcanceltype (int __type, int *__oldtype);


extern int pthread_cancel (pthread_t __th);




extern void pthread_testcancel (void);




typedef struct
{
  struct
  {
    __jmp_buf __cancel_jmp_buf;
    int __mask_was_saved;
  } __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t __attribute__ ((__aligned__));
# 524 "/usr/include/pthread.h" 3 4
struct __pthread_cleanup_frame
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};




class __pthread_cleanup_class
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;

 public:
  __pthread_cleanup_class (void (*__fct) (void *), void *__arg)
    : __cancel_routine (__fct), __cancel_arg (__arg), __do_it (1) { }
  ~__pthread_cleanup_class () { if (__do_it) __cancel_routine (__cancel_arg); }
  void __setdoit (int __newval) { __do_it = __newval; }
  void __defer () { pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED,
        &__cancel_type); }
  void __restore () const { pthread_setcanceltype (__cancel_type, 0); }
};
# 726 "/usr/include/pthread.h" 3 4
struct __jmp_buf_tag;
extern int __sigsetjmp (struct __jmp_buf_tag *__env, int __savemask) throw ();





extern int pthread_mutex_init (pthread_mutex_t *__mutex,
          __const pthread_mutexattr_t *__mutexattr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
        __const struct timespec *__restrict
        __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_getprioceiling (__const pthread_mutex_t *
      __restrict __mutex,
      int *__restrict __prioceiling)
     throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
      int __prioceiling,
      int *__restrict __old_ceiling)
     throw () __attribute__ ((__nonnull__ (1, 3)));




extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));

extern int pthread_mutex_consistent_np (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
# 790 "/usr/include/pthread.h" 3 4
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getpshared (__const pthread_mutexattr_t *
      __restrict __attr,
      int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
      int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_gettype (__const pthread_mutexattr_t *__restrict
          __attr, int *__restrict __kind)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getprotocol (__const pthread_mutexattr_t *
       __restrict __attr,
       int *__restrict __protocol)
     throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
       int __protocol)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getprioceiling (__const pthread_mutexattr_t *
          __restrict __attr,
          int *__restrict __prioceiling)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
          int __prioceiling)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getrobust (__const pthread_mutexattr_t *__attr,
     int *__robustness)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern int pthread_mutexattr_getrobust_np (__const pthread_mutexattr_t *__attr,
        int *__robustness)
     throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
     int __robustness)
     throw () __attribute__ ((__nonnull__ (1)));

extern int pthread_mutexattr_setrobust_np (pthread_mutexattr_t *__attr,
        int __robustness)
     throw () __attribute__ ((__nonnull__ (1)));
# 872 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock,
    __const pthread_rwlockattr_t *__restrict
    __attr) throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict __rwlock,
           __const struct timespec *__restrict
           __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict __rwlock,
           __const struct timespec *__restrict
           __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));





extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getpshared (__const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
       int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getkind_np (__const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pref)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
       int __pref) throw () __attribute__ ((__nonnull__ (1)));







extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
         __const pthread_condattr_t *__restrict
         __cond_attr) throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_destroy (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_signal (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));






extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
         pthread_mutex_t *__restrict __mutex)
     __attribute__ ((__nonnull__ (1, 2)));
# 984 "/usr/include/pthread.h" 3 4
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
       pthread_mutex_t *__restrict __mutex,
       __const struct timespec *__restrict
       __abstime) __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_condattr_init (pthread_condattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_getpshared (__const pthread_condattr_t *
     __restrict __attr,
     int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
     int __pshared) throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_condattr_getclock (__const pthread_condattr_t *
          __restrict __attr,
          __clockid_t *__restrict __clock_id)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
          __clockid_t __clock_id)
     throw () __attribute__ ((__nonnull__ (1)));
# 1028 "/usr/include/pthread.h" 3 4
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));






extern int pthread_barrier_init (pthread_barrier_t *__restrict __barrier,
     __const pthread_barrierattr_t *__restrict
     __attr, unsigned int __count)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     throw () __attribute__ ((__nonnull__ (1)));



extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_getpshared (__const pthread_barrierattr_t *
        __restrict __attr,
        int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
        int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));
# 1095 "/usr/include/pthread.h" 3 4
extern int pthread_key_create (pthread_key_t *__key,
          void (*__destr_function) (void *))
     throw () __attribute__ ((__nonnull__ (1)));


extern int pthread_key_delete (pthread_key_t __key) throw ();


extern void *pthread_getspecific (pthread_key_t __key) throw ();


extern int pthread_setspecific (pthread_key_t __key,
    __const void *__pointer) throw () ;




extern int pthread_getcpuclockid (pthread_t __thread_id,
      __clockid_t *__clock_id)
     throw () __attribute__ ((__nonnull__ (2)));
# 1129 "/usr/include/pthread.h" 3 4
extern int pthread_atfork (void (*__prepare) (void),
      void (*__parent) (void),
      void (*__child) (void)) throw ();
# 1143 "/usr/include/pthread.h" 3 4
}
# 36 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 2 3
# 47 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 3
typedef pthread_t __gthread_t;
typedef pthread_key_t __gthread_key_t;
typedef pthread_once_t __gthread_once_t;
typedef pthread_mutex_t __gthread_mutex_t;
typedef pthread_mutex_t __gthread_recursive_mutex_t;
typedef pthread_cond_t __gthread_cond_t;
typedef struct timespec __gthread_time_t;
# 101 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 3
static __typeof(pthread_once) __gthrw_pthread_once __attribute__ ((__weakref__("pthread_once")));
static __typeof(pthread_getspecific) __gthrw_pthread_getspecific __attribute__ ((__weakref__("pthread_getspecific")));
static __typeof(pthread_setspecific) __gthrw_pthread_setspecific __attribute__ ((__weakref__("pthread_setspecific")));

static __typeof(pthread_create) __gthrw_pthread_create __attribute__ ((__weakref__("pthread_create")));
static __typeof(pthread_join) __gthrw_pthread_join __attribute__ ((__weakref__("pthread_join")));
static __typeof(pthread_equal) __gthrw_pthread_equal __attribute__ ((__weakref__("pthread_equal")));
static __typeof(pthread_self) __gthrw_pthread_self __attribute__ ((__weakref__("pthread_self")));
static __typeof(pthread_detach) __gthrw_pthread_detach __attribute__ ((__weakref__("pthread_detach")));

static __typeof(pthread_cancel) __gthrw_pthread_cancel __attribute__ ((__weakref__("pthread_cancel")));

static __typeof(sched_yield) __gthrw_sched_yield __attribute__ ((__weakref__("sched_yield")));

static __typeof(pthread_mutex_lock) __gthrw_pthread_mutex_lock __attribute__ ((__weakref__("pthread_mutex_lock")));
static __typeof(pthread_mutex_trylock) __gthrw_pthread_mutex_trylock __attribute__ ((__weakref__("pthread_mutex_trylock")));

static __typeof(pthread_mutex_timedlock) __gthrw_pthread_mutex_timedlock __attribute__ ((__weakref__("pthread_mutex_timedlock")));

static __typeof(pthread_mutex_unlock) __gthrw_pthread_mutex_unlock __attribute__ ((__weakref__("pthread_mutex_unlock")));
static __typeof(pthread_mutex_init) __gthrw_pthread_mutex_init __attribute__ ((__weakref__("pthread_mutex_init")));
static __typeof(pthread_mutex_destroy) __gthrw_pthread_mutex_destroy __attribute__ ((__weakref__("pthread_mutex_destroy")));

static __typeof(pthread_cond_init) __gthrw_pthread_cond_init __attribute__ ((__weakref__("pthread_cond_init")));
static __typeof(pthread_cond_broadcast) __gthrw_pthread_cond_broadcast __attribute__ ((__weakref__("pthread_cond_broadcast")));
static __typeof(pthread_cond_signal) __gthrw_pthread_cond_signal __attribute__ ((__weakref__("pthread_cond_signal")));
static __typeof(pthread_cond_wait) __gthrw_pthread_cond_wait __attribute__ ((__weakref__("pthread_cond_wait")));
static __typeof(pthread_cond_timedwait) __gthrw_pthread_cond_timedwait __attribute__ ((__weakref__("pthread_cond_timedwait")));
static __typeof(pthread_cond_destroy) __gthrw_pthread_cond_destroy __attribute__ ((__weakref__("pthread_cond_destroy")));

static __typeof(pthread_key_create) __gthrw_pthread_key_create __attribute__ ((__weakref__("pthread_key_create")));
static __typeof(pthread_key_delete) __gthrw_pthread_key_delete __attribute__ ((__weakref__("pthread_key_delete")));
static __typeof(pthread_mutexattr_init) __gthrw_pthread_mutexattr_init __attribute__ ((__weakref__("pthread_mutexattr_init")));
static __typeof(pthread_mutexattr_settype) __gthrw_pthread_mutexattr_settype __attribute__ ((__weakref__("pthread_mutexattr_settype")));
static __typeof(pthread_mutexattr_destroy) __gthrw_pthread_mutexattr_destroy __attribute__ ((__weakref__("pthread_mutexattr_destroy")));
# 236 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 3
static __typeof(pthread_key_create) __gthrw___pthread_key_create __attribute__ ((__weakref__("__pthread_key_create")));
# 246 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 3
static inline int
__gthread_active_p (void)
{
  static void *const __gthread_active_ptr
    = __extension__ (void *) &__gthrw___pthread_key_create;
  return __gthread_active_ptr != 0;
}
# 658 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 3
static inline int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void*),
    void *__args)
{
  return __gthrw_pthread_create (__threadid, __null, __func, __args);
}

static inline int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
  return __gthrw_pthread_join (__threadid, __value_ptr);
}

static inline int
__gthread_detach (__gthread_t __threadid)
{
  return __gthrw_pthread_detach (__threadid);
}

static inline int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
  return __gthrw_pthread_equal (__t1, __t2);
}

static inline __gthread_t
__gthread_self (void)
{
  return __gthrw_pthread_self ();
}

static inline int
__gthread_yield (void)
{
  return __gthrw_sched_yield ();
}

static inline int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
  if (__gthread_active_p ())
    return __gthrw_pthread_once (__once, __func);
  else
    return -1;
}

static inline int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
  return __gthrw_pthread_key_create (__key, __dtor);
}

static inline int
__gthread_key_delete (__gthread_key_t __key)
{
  return __gthrw_pthread_key_delete (__key);
}

static inline void *
__gthread_getspecific (__gthread_key_t __key)
{
  return __gthrw_pthread_getspecific (__key);
}

static inline int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
  return __gthrw_pthread_setspecific (__key, __ptr);
}

static inline void
__gthread_mutex_init_function (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    __gthrw_pthread_mutex_init (__mutex, __null);
}

static inline int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_destroy (__mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_lock (__mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_trylock (__mutex);
  else
    return 0;
}


static inline int
__gthread_mutex_timedlock (__gthread_mutex_t *__mutex,
      const __gthread_time_t *__abs_timeout)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_timedlock (__mutex, __abs_timeout);
  else
    return 0;
}


static inline int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_unlock (__mutex);
  else
    return 0;
}
# 807 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 3
static inline int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_lock (__mutex);
}

static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_trylock (__mutex);
}


static inline int
__gthread_recursive_mutex_timedlock (__gthread_recursive_mutex_t *__mutex,
         const __gthread_time_t *__abs_timeout)
{
  return __gthread_mutex_timedlock (__mutex, __abs_timeout);
}


static inline int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_unlock (__mutex);
}

static inline int
__gthread_recursive_mutex_destroy (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_destroy (__mutex);
}
# 849 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr-default.h" 3
static inline int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
  return __gthrw_pthread_cond_broadcast (__cond);
}

static inline int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
  return __gthrw_pthread_cond_signal (__cond);
}

static inline int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
  return __gthrw_pthread_cond_wait (__cond, __mutex);
}

static inline int
__gthread_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex,
     const __gthread_time_t *__abs_timeout)
{
  return __gthrw_pthread_cond_timedwait (__cond, __mutex, __abs_timeout);
}

static inline int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
          __gthread_recursive_mutex_t *__mutex)
{
  return __gthread_cond_wait (__cond, __mutex);
}

static inline int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
  return __gthrw_pthread_cond_destroy (__cond);
}
# 149 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/gthr.h" 2 3


#pragma GCC visibility pop
# 36 "/usr/local/include/c++/4.9.0/ext/atomicity.h" 2 3
# 1 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/atomic_word.h" 1 3
# 32 "/usr/local/include/c++/4.9.0/x86_64-unknown-linux-gnu/bits/atomic_word.h" 3
typedef int _Atomic_word;
# 37 "/usr/local/include/c++/4.9.0/ext/atomicity.h" 2 3

namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{







  static inline _Atomic_word
  __exchange_and_add(volatile _Atomic_word* __mem, int __val)
  { return __atomic_fetch_add(__mem, __val, 4); }

  static inline void
  __atomic_add(volatile _Atomic_word* __mem, int __val)
  { __atomic_fetch_add(__mem, __val, 4); }
# 64 "/usr/local/include/c++/4.9.0/ext/atomicity.h" 3
  static inline _Atomic_word
  __exchange_and_add_single(_Atomic_word* __mem, int __val)
  {
    _Atomic_word __result = *__mem;
    *__mem += __val;
    return __result;
  }

  static inline void
  __atomic_add_single(_Atomic_word* __mem, int __val)
  { *__mem += __val; }

  static inline _Atomic_word
  __attribute__ ((__unused__))
  __exchange_and_add_dispatch(_Atomic_word* __mem, int __val)
  {

    if (__gthread_active_p())
      return __exchange_and_add(__mem, __val);
    else
      return __exchange_and_add_single(__mem, __val);



  }

  static inline void
  __attribute__ ((__unused__))
  __atomic_add_dispatch(_Atomic_word* __mem, int __val)
  {

    if (__gthread_active_p())
      __atomic_add(__mem, __val);
    else
      __atomic_add_single(__mem, __val);



  }


}
# 40 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 2 3





namespace std __attribute__ ((__visibility__ ("default")))
{

# 111 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    class basic_string
    {
      typedef typename _Alloc::template rebind<_CharT>::other _CharT_alloc_type;


    public:
      typedef _Traits traits_type;
      typedef typename _Traits::char_type value_type;
      typedef _Alloc allocator_type;
      typedef typename _CharT_alloc_type::size_type size_type;
      typedef typename _CharT_alloc_type::difference_type difference_type;
      typedef typename _CharT_alloc_type::reference reference;
      typedef typename _CharT_alloc_type::const_reference const_reference;
      typedef typename _CharT_alloc_type::pointer pointer;
      typedef typename _CharT_alloc_type::const_pointer const_pointer;
      typedef __gnu_cxx::__normal_iterator<pointer, basic_string> iterator;
      typedef __gnu_cxx::__normal_iterator<const_pointer, basic_string>
                                                            const_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;

    private:
# 148 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      struct _Rep_base
      {
 size_type _M_length;
 size_type _M_capacity;
 _Atomic_word _M_refcount;
      };

      struct _Rep : _Rep_base
      {

 typedef typename _Alloc::template rebind<char>::other _Raw_bytes_alloc;
# 173 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
 static const size_type _S_max_size;
 static const _CharT _S_terminal;



        static size_type _S_empty_rep_storage[];

        static _Rep&
        _S_empty_rep()
        {



   void* __p = reinterpret_cast<void*>(&_S_empty_rep_storage);
   return *reinterpret_cast<_Rep*>(__p);
 }

        bool
 _M_is_leaked() const
        { return this->_M_refcount < 0; }

        bool
 _M_is_shared() const
        { return this->_M_refcount > 0; }

        void
 _M_set_leaked()
        { this->_M_refcount = -1; }

        void
 _M_set_sharable()
        { this->_M_refcount = 0; }

 void
 _M_set_length_and_sharable(size_type __n)
 {

   if (__builtin_expect(this != &_S_empty_rep(), false))

     {
       this->_M_set_sharable();
       this->_M_length = __n;
       traits_type::assign(this->_M_refdata()[__n], _S_terminal);


     }
 }

 _CharT*
 _M_refdata() throw()
 { return reinterpret_cast<_CharT*>(this + 1); }

 _CharT*
 _M_grab(const _Alloc& __alloc1, const _Alloc& __alloc2)
 {
   return (!_M_is_leaked() && __alloc1 == __alloc2)
           ? _M_refcopy() : _M_clone(__alloc1);
 }


 static _Rep*
 _S_create(size_type, size_type, const _Alloc&);

 void
 _M_dispose(const _Alloc& __a)
 {

   if (__builtin_expect(this != &_S_empty_rep(), false))

     {

       ;
       if (__gnu_cxx::__exchange_and_add_dispatch(&this->_M_refcount,
        -1) <= 0)
  {
    ;
    _M_destroy(__a);
  }
     }
 }

 void
 _M_destroy(const _Alloc&) throw();

 _CharT*
 _M_refcopy() throw()
 {

   if (__builtin_expect(this != &_S_empty_rep(), false))

            __gnu_cxx::__atomic_add_dispatch(&this->_M_refcount, 1);
   return _M_refdata();
 }

 _CharT*
 _M_clone(const _Alloc&, size_type __res = 0);
      };


      struct _Alloc_hider : _Alloc
      {
 _Alloc_hider(_CharT* __dat, const _Alloc& __a)
 : _Alloc(__a), _M_p(__dat) { }

 _CharT* _M_p;
      };

    public:




      static const size_type npos = static_cast<size_type>(-1);

    private:

      mutable _Alloc_hider _M_dataplus;

      _CharT*
      _M_data() const
      { return _M_dataplus._M_p; }

      _CharT*
      _M_data(_CharT* __p)
      { return (_M_dataplus._M_p = __p); }

      _Rep*
      _M_rep() const
      { return &((reinterpret_cast<_Rep*> (_M_data()))[-1]); }



      iterator
      _M_ibegin() const
      { return iterator(_M_data()); }

      iterator
      _M_iend() const
      { return iterator(_M_data() + this->size()); }

      void
      _M_leak()
      {
 if (!_M_rep()->_M_is_leaked())
   _M_leak_hard();
      }

      size_type
      _M_check(size_type __pos, const char* __s) const
      {
 if (__pos > this->size())
   __throw_out_of_range_fmt(("%s: __pos (which is %zu) > " "this->size() (which is %zu)")
                                         ,
       __s, __pos, this->size());
 return __pos;
      }

      void
      _M_check_length(size_type __n1, size_type __n2, const char* __s) const
      {
 if (this->max_size() - (this->size() - __n1) < __n2)
   __throw_length_error((__s));
      }


      size_type
      _M_limit(size_type __pos, size_type __off) const
      {
 const bool __testoff = __off < this->size() - __pos;
 return __testoff ? __off : this->size() - __pos;
      }


      bool
      _M_disjunct(const _CharT* __s) const
      {
 return (less<const _CharT*>()(__s, _M_data())
  || less<const _CharT*>()(_M_data() + this->size(), __s));
      }



      static void
      _M_copy(_CharT* __d, const _CharT* __s, size_type __n)
      {
 if (__n == 1)
   traits_type::assign(*__d, *__s);
 else
   traits_type::copy(__d, __s, __n);
      }

      static void
      _M_move(_CharT* __d, const _CharT* __s, size_type __n)
      {
 if (__n == 1)
   traits_type::assign(*__d, *__s);
 else
   traits_type::move(__d, __s, __n);
      }

      static void
      _M_assign(_CharT* __d, size_type __n, _CharT __c)
      {
 if (__n == 1)
   traits_type::assign(*__d, __c);
 else
   traits_type::assign(__d, __n, __c);
      }



      template<class _Iterator>
        static void
        _S_copy_chars(_CharT* __p, _Iterator __k1, _Iterator __k2)

        {
   for (; __k1 != __k2; ++__k1, ++__p)
     traits_type::assign(*__p, *__k1);
 }

      static void
      _S_copy_chars(_CharT* __p, iterator __k1, iterator __k2)
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }

      static void
      _S_copy_chars(_CharT* __p, const_iterator __k1, const_iterator __k2)
     
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }

      static void
      _S_copy_chars(_CharT* __p, _CharT* __k1, _CharT* __k2)
      { _M_copy(__p, __k1, __k2 - __k1); }

      static void
      _S_copy_chars(_CharT* __p, const _CharT* __k1, const _CharT* __k2)
     
      { _M_copy(__p, __k1, __k2 - __k1); }

      static int
      _S_compare(size_type __n1, size_type __n2)
      {
 const difference_type __d = difference_type(__n1 - __n2);

 if (__d > __gnu_cxx::__numeric_traits<int>::__max)
   return __gnu_cxx::__numeric_traits<int>::__max;
 else if (__d < __gnu_cxx::__numeric_traits<int>::__min)
   return __gnu_cxx::__numeric_traits<int>::__min;
 else
   return int(__d);
      }

      void
      _M_mutate(size_type __pos, size_type __len1, size_type __len2);

      void
      _M_leak_hard();

      static _Rep&
      _S_empty_rep()
      { return _Rep::_S_empty_rep(); }

    public:







      basic_string()

      : _M_dataplus(_S_empty_rep()._M_refdata(), _Alloc()) { }







      explicit
      basic_string(const _Alloc& __a);






      basic_string(const basic_string& __str);






      basic_string(const basic_string& __str, size_type __pos,
     size_type __n = npos);







      basic_string(const basic_string& __str, size_type __pos,
     size_type __n, const _Alloc& __a);
# 488 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string(const _CharT* __s, size_type __n,
     const _Alloc& __a = _Alloc());





      basic_string(const _CharT* __s, const _Alloc& __a = _Alloc());






      basic_string(size_type __n, _CharT __c, const _Alloc& __a = _Alloc());
# 539 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      template<class _InputIterator>
        basic_string(_InputIterator __beg, _InputIterator __end,
       const _Alloc& __a = _Alloc());




      ~basic_string()
      { _M_rep()->_M_dispose(this->get_allocator()); }





      basic_string&
      operator=(const basic_string& __str)
      { return this->assign(__str); }





      basic_string&
      operator=(const _CharT* __s)
      { return this->assign(__s); }
# 572 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      operator=(_CharT __c)
      {
 this->assign(1, __c);
 return *this;
      }
# 613 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      iterator
      begin()
      {
 _M_leak();
 return iterator(_M_data());
      }





      const_iterator
      begin() const
      { return const_iterator(_M_data()); }





      iterator
      end()
      {
 _M_leak();
 return iterator(_M_data() + this->size());
      }





      const_iterator
      end() const
      { return const_iterator(_M_data() + this->size()); }






      reverse_iterator
      rbegin()
      { return reverse_iterator(this->end()); }






      const_reverse_iterator
      rbegin() const
      { return const_reverse_iterator(this->end()); }






      reverse_iterator
      rend()
      { return reverse_iterator(this->begin()); }






      const_reverse_iterator
      rend() const
      { return const_reverse_iterator(this->begin()); }
# 719 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
    public:



      size_type
      size() const
      { return _M_rep()->_M_length; }



      size_type
      length() const
      { return _M_rep()->_M_length; }


      size_type
      max_size() const
      { return _Rep::_S_max_size; }
# 748 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      void
      resize(size_type __n, _CharT __c);
# 761 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      void
      resize(size_type __n)
      { this->resize(__n, _CharT()); }
# 784 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      capacity() const
      { return _M_rep()->_M_capacity; }
# 805 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      void
      reserve(size_type __res_arg = 0);





      void
      clear()
      { _M_mutate(0, this->size(), 0); }





      bool
      empty() const
      { return this->size() == 0; }
# 835 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      const_reference
      operator[] (size_type __pos) const
      {
 ;
 return _M_data()[__pos];
      }
# 852 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      reference
      operator[](size_type __pos)
      {


 ;

 ;
 _M_leak();
 return _M_data()[__pos];
      }
# 874 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      const_reference
      at(size_type __n) const
      {
 if (__n >= this->size())
   __throw_out_of_range_fmt(("basic_string::at: __n " "(which is %zu) >= this->size() " "(which is %zu)")

                            ,
       __n, this->size());
 return _M_data()[__n];
      }
# 896 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      reference
      at(size_type __n)
      {
 if (__n >= size())
   __throw_out_of_range_fmt(("basic_string::at: __n " "(which is %zu) >= this->size() " "(which is %zu)")

                            ,
       __n, this->size());
 _M_leak();
 return _M_data()[__n];
      }
# 948 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      operator+=(const basic_string& __str)
      { return this->append(__str); }






      basic_string&
      operator+=(const _CharT* __s)
      { return this->append(__s); }






      basic_string&
      operator+=(_CharT __c)
      {
 this->push_back(__c);
 return *this;
      }
# 989 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      append(const basic_string& __str);
# 1005 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      append(const basic_string& __str, size_type __pos, size_type __n);







      basic_string&
      append(const _CharT* __s, size_type __n);






      basic_string&
      append(const _CharT* __s)
      {
 ;
 return this->append(__s, traits_type::length(__s));
      }
# 1037 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      append(size_type __n, _CharT __c);
# 1059 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      template<class _InputIterator>
        basic_string&
        append(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_iend(), _M_iend(), __first, __last); }





      void
      push_back(_CharT __c)
      {
 const size_type __len = 1 + this->size();
 if (__len > this->capacity() || _M_rep()->_M_is_shared())
   this->reserve(__len);
 traits_type::assign(_M_data()[this->size()], __c);
 _M_rep()->_M_set_length_and_sharable(__len);
      }






      basic_string&
      assign(const basic_string& __str);
# 1117 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      assign(const basic_string& __str, size_type __pos, size_type __n)
      { return this->assign(__str._M_data()
       + __str._M_check(__pos, "basic_string::assign"),
       __str._M_limit(__pos, __n)); }
# 1133 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      assign(const _CharT* __s, size_type __n);
# 1145 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      assign(const _CharT* __s)
      {
 ;
 return this->assign(__s, traits_type::length(__s));
      }
# 1161 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      assign(size_type __n, _CharT __c)
      { return _M_replace_aux(size_type(0), this->size(), __n, __c); }
# 1173 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      template<class _InputIterator>
        basic_string&
        assign(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_ibegin(), _M_iend(), __first, __last); }
# 1202 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      void
      insert(iterator __p, size_type __n, _CharT __c)
      { this->replace(__p, __p, __n, __c); }
# 1218 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      template<class _InputIterator>
        void
        insert(iterator __p, _InputIterator __beg, _InputIterator __end)
        { this->replace(__p, __p, __beg, __end); }
# 1250 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos1, const basic_string& __str)
      { return this->insert(__pos1, __str, size_type(0), __str.size()); }
# 1272 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos1, const basic_string& __str,
      size_type __pos2, size_type __n)
      { return this->insert(__pos1, __str._M_data()
       + __str._M_check(__pos2, "basic_string::insert"),
       __str._M_limit(__pos2, __n)); }
# 1295 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos, const _CharT* __s, size_type __n);
# 1313 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos, const _CharT* __s)
      {
 ;
 return this->insert(__pos, __s, traits_type::length(__s));
      }
# 1336 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      insert(size_type __pos, size_type __n, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::insert"),
         size_type(0), __n, __c); }
# 1354 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      iterator
      insert(iterator __p, _CharT __c)
      {
 ;
 const size_type __pos = __p - _M_ibegin();
 _M_replace_aux(__pos, size_type(0), size_type(1), __c);
 _M_rep()->_M_set_leaked();
 return iterator(_M_data() + __pos);
      }
# 1379 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      erase(size_type __pos = 0, size_type __n = npos)
      {
 _M_mutate(_M_check(__pos, "basic_string::erase"),
    _M_limit(__pos, __n), size_type(0));
 return *this;
      }
# 1395 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      iterator
      erase(iterator __position)
      {

                               ;
 const size_type __pos = __position - _M_ibegin();
 _M_mutate(__pos, size_type(1), size_type(0));
 _M_rep()->_M_set_leaked();
 return iterator(_M_data() + __pos);
      }
# 1415 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      iterator
      erase(iterator __first, iterator __last);
# 1446 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos, size_type __n, const basic_string& __str)
      { return this->replace(__pos, __n, __str._M_data(), __str.size()); }
# 1468 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos1, size_type __n1, const basic_string& __str,
       size_type __pos2, size_type __n2)
      { return this->replace(__pos1, __n1, __str._M_data()
        + __str._M_check(__pos2, "basic_string::replace"),
        __str._M_limit(__pos2, __n2)); }
# 1493 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s,
       size_type __n2);
# 1513 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s)
      {
 ;
 return this->replace(__pos, __n1, __s, traits_type::length(__s));
      }
# 1537 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(size_type __pos, size_type __n1, size_type __n2, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::replace"),
         _M_limit(__pos, __n1), __n2, __c); }
# 1555 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(iterator __i1, iterator __i2, const basic_string& __str)
      { return this->replace(__i1, __i2, __str._M_data(), __str.size()); }
# 1574 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s, size_type __n)
      {

                          ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1, __s, __n);
      }
# 1595 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s)
      {
 ;
 return this->replace(__i1, __i2, __s, traits_type::length(__s));
      }
# 1616 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string&
      replace(iterator __i1, iterator __i2, size_type __n, _CharT __c)
      {

                          ;
 return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __c);
      }
# 1639 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      template<class _InputIterator>
        basic_string&
        replace(iterator __i1, iterator __i2,
  _InputIterator __k1, _InputIterator __k2)
        {
  
                            ;
   ;
   typedef typename std::__is_integer<_InputIterator>::__type _Integral;
   return _M_replace_dispatch(__i1, __i2, __k1, __k2, _Integral());
 }



      basic_string&
      replace(iterator __i1, iterator __i2, _CharT* __k1, _CharT* __k2)
      {

                          ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1, __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2,
       const _CharT* __k1, const _CharT* __k2)
      {

                          ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1, __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2, iterator __k1, iterator __k2)
      {

                          ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1.base(), __k2 - __k1);
      }

      basic_string&
      replace(iterator __i1, iterator __i2,
       const_iterator __k1, const_iterator __k2)
      {

                          ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1.base(), __k2 - __k1);
      }
# 1715 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
    private:
      template<class _Integer>
 basic_string&
 _M_replace_dispatch(iterator __i1, iterator __i2, _Integer __n,
       _Integer __val, __true_type)
        { return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __val); }

      template<class _InputIterator>
 basic_string&
 _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
       _InputIterator __k2, __false_type);

      basic_string&
      _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
       _CharT __c);

      basic_string&
      _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
        size_type __n2);



      template<class _InIterator>
        static _CharT*
        _S_construct_aux(_InIterator __beg, _InIterator __end,
    const _Alloc& __a, __false_type)
 {
          typedef typename iterator_traits<_InIterator>::iterator_category _Tag;
          return _S_construct(__beg, __end, __a, _Tag());
 }



      template<class _Integer>
        static _CharT*
        _S_construct_aux(_Integer __beg, _Integer __end,
    const _Alloc& __a, __true_type)
        { return _S_construct_aux_2(static_cast<size_type>(__beg),
        __end, __a); }

      static _CharT*
      _S_construct_aux_2(size_type __req, _CharT __c, const _Alloc& __a)
      { return _S_construct(__req, __c, __a); }

      template<class _InIterator>
        static _CharT*
        _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a)
 {
   typedef typename std::__is_integer<_InIterator>::__type _Integral;
   return _S_construct_aux(__beg, __end, __a, _Integral());
        }


      template<class _InIterator>
        static _CharT*
         _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
        input_iterator_tag);



      template<class _FwdIterator>
        static _CharT*
        _S_construct(_FwdIterator __beg, _FwdIterator __end, const _Alloc& __a,
       forward_iterator_tag);

      static _CharT*
      _S_construct(size_type __req, _CharT __c, const _Alloc& __a);

    public:
# 1797 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      copy(_CharT* __s, size_type __n, size_type __pos = 0) const;
# 1808 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      void
      swap(basic_string& __s);
# 1818 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      const _CharT*
      c_str() const
      { return _M_data(); }







      const _CharT*
      data() const
      { return _M_data(); }




      allocator_type
      get_allocator() const
      { return _M_dataplus; }
# 1851 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find(const _CharT* __s, size_type __pos, size_type __n) const;
# 1864 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find(const basic_string& __str, size_type __pos = 0) const

      { return this->find(__str.data(), __pos, __str.size()); }
# 1879 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find(__s, __pos, traits_type::length(__s));
      }
# 1896 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find(_CharT __c, size_type __pos = 0) const ;
# 1909 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      rfind(const basic_string& __str, size_type __pos = npos) const

      { return this->rfind(__str.data(), __pos, __str.size()); }
# 1926 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      rfind(const _CharT* __s, size_type __pos, size_type __n) const;
# 1939 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      rfind(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->rfind(__s, __pos, traits_type::length(__s));
      }
# 1956 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      rfind(_CharT __c, size_type __pos = npos) const ;
# 1970 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_first_of(const basic_string& __str, size_type __pos = 0) const

      { return this->find_first_of(__str.data(), __pos, __str.size()); }
# 1987 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_first_of(const _CharT* __s, size_type __pos, size_type __n) const;
# 2000 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_first_of(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find_first_of(__s, __pos, traits_type::length(__s));
      }
# 2019 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_first_of(_CharT __c, size_type __pos = 0) const
      { return this->find(__c, __pos); }
# 2034 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_last_of(const basic_string& __str, size_type __pos = npos) const

      { return this->find_last_of(__str.data(), __pos, __str.size()); }
# 2051 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_last_of(const _CharT* __s, size_type __pos, size_type __n) const;
# 2064 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_last_of(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->find_last_of(__s, __pos, traits_type::length(__s));
      }
# 2083 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_last_of(_CharT __c, size_type __pos = npos) const
      { return this->rfind(__c, __pos); }
# 2097 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_first_not_of(const basic_string& __str, size_type __pos = 0) const

      { return this->find_first_not_of(__str.data(), __pos, __str.size()); }
# 2114 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos,
   size_type __n) const;
# 2128 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find_first_not_of(__s, __pos, traits_type::length(__s));
      }
# 2145 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_first_not_of(_CharT __c, size_type __pos = 0) const
 ;
# 2160 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_last_not_of(const basic_string& __str, size_type __pos = npos) const

      { return this->find_last_not_of(__str.data(), __pos, __str.size()); }
# 2177 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos,
         size_type __n) const;
# 2191 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->find_last_not_of(__s, __pos, traits_type::length(__s));
      }
# 2208 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      size_type
      find_last_not_of(_CharT __c, size_type __pos = npos) const
 ;
# 2224 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      basic_string
      substr(size_type __pos = 0, size_type __n = npos) const
      { return basic_string(*this,
       _M_check(__pos, "basic_string::substr"), __n); }
# 2243 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      int
      compare(const basic_string& __str) const
      {
 const size_type __size = this->size();
 const size_type __osize = __str.size();
 const size_type __len = std::min(__size, __osize);

 int __r = traits_type::compare(_M_data(), __str.data(), __len);
 if (!__r)
   __r = _S_compare(__size, __osize);
 return __r;
      }
# 2275 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      int
      compare(size_type __pos, size_type __n, const basic_string& __str) const;
# 2301 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      int
      compare(size_type __pos1, size_type __n1, const basic_string& __str,
       size_type __pos2, size_type __n2) const;
# 2319 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      int
      compare(const _CharT* __s) const;
# 2343 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s) const;
# 2370 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s,
       size_type __n2) const;
  };
# 2382 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }







  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(const _CharT* __lhs,
       const basic_string<_CharT,_Traits,_Alloc>& __rhs);







  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT,_Traits,_Alloc>& __rhs);







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
      const _CharT* __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs, _CharT __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      __string_type __str(__lhs);
      __str.append(__size_type(1), __rhs);
      return __str;
    }
# 2503 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) == 0; }

  template<typename _CharT>
    inline
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, bool>::__type
    operator==(const basic_string<_CharT>& __lhs,
        const basic_string<_CharT>& __rhs)
    { return (__lhs.size() == __rhs.size()
       && !std::char_traits<_CharT>::compare(__lhs.data(), __rhs.data(),
          __lhs.size())); }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) == 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) == 0; }
# 2549 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return !(__lhs == __rhs); }
# 2586 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) < 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    { return __lhs.compare(__rhs) < 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) > 0; }
# 2623 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) > 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    { return __lhs.compare(__rhs) > 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) < 0; }
# 2660 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) <= 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) <= 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) >= 0; }
# 2697 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) >= 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) >= 0; }







  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const _CharT* __lhs,
      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) <= 0; }
# 2734 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline void
    swap(basic_string<_CharT, _Traits, _Alloc>& __lhs,
  basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { __lhs.swap(__rhs); }
# 2752 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT, _Traits, _Alloc>& __str);

  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __is, basic_string<char>& __str);
# 2770 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
        const basic_string<_CharT, _Traits, _Alloc>& __str)
    {


      return __ostream_insert(__os, __str.data(), __str.size());
    }
# 2793 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim);
# 2810 "/usr/local/include/c++/4.9.0/bits/basic_string.h" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str)
    { return getline(__is, __str, __is.widen('\n')); }

  template<>
    basic_istream<char>&
    getline(basic_istream<char>& __in, basic_string<char>& __str,
     char __delim);


  template<>
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>& __in, basic_string<wchar_t>& __str,
     wchar_t __delim);



}
# 53 "/usr/local/include/c++/4.9.0/string" 2 3
# 1 "/usr/local/include/c++/4.9.0/bits/basic_string.tcc" 1 3
# 40 "/usr/local/include/c++/4.9.0/bits/basic_string.tcc" 3
       
# 41 "/usr/local/include/c++/4.9.0/bits/basic_string.tcc" 3



namespace std __attribute__ ((__visibility__ ("default")))
{


  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_max_size = (((npos - sizeof(_Rep_base))/sizeof(_CharT)) - 1) / 4;

  template<typename _CharT, typename _Traits, typename _Alloc>
    const _CharT
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_terminal = _CharT();

  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::npos;



  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::_Rep::_S_empty_rep_storage[
    (sizeof(_Rep_base) + sizeof(_CharT) + sizeof(size_type) - 1) /
      sizeof(size_type)];





  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
     input_iterator_tag)
      {

 if (__beg == __end && __a == _Alloc())
   return _S_empty_rep()._M_refdata();


 _CharT __buf[128];
 size_type __len = 0;
 while (__beg != __end && __len < sizeof(__buf) / sizeof(_CharT))
   {
     __buf[__len++] = *__beg;
     ++__beg;
   }
 _Rep* __r = _Rep::_S_create(__len, size_type(0), __a);
 _M_copy(__r->_M_refdata(), __buf, __len);
 try
   {
     while (__beg != __end)
       {
  if (__len == __r->_M_capacity)
    {

      _Rep* __another = _Rep::_S_create(__len + 1, __len, __a);
      _M_copy(__another->_M_refdata(), __r->_M_refdata(), __len);
      __r->_M_destroy(__a);
      __r = __another;
    }
  __r->_M_refdata()[__len++] = *__beg;
  ++__beg;
       }
   }
 catch(...)
   {
     __r->_M_destroy(__a);
     throw;
   }
 __r->_M_set_length_and_sharable(__len);
 return __r->_M_refdata();
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    template <typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
     forward_iterator_tag)
      {

 if (__beg == __end && __a == _Alloc())
   return _S_empty_rep()._M_refdata();


 if (__gnu_cxx::__is_null_pointer(__beg) && __beg != __end)
   __throw_logic_error(("basic_string::_S_construct null not valid"));

 const size_type __dnew = static_cast<size_type>(std::distance(__beg,
              __end));

 _Rep* __r = _Rep::_S_create(__dnew, size_type(0), __a);
 try
   { _S_copy_chars(__r->_M_refdata(), __beg, __end); }
 catch(...)
   {
     __r->_M_destroy(__a);
     throw;
   }
 __r->_M_set_length_and_sharable(__dnew);
 return __r->_M_refdata();
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::
    _S_construct(size_type __n, _CharT __c, const _Alloc& __a)
    {

      if (__n == 0 && __a == _Alloc())
 return _S_empty_rep()._M_refdata();


      _Rep* __r = _Rep::_S_create(__n, size_type(0), __a);
      if (__n)
 _M_assign(__r->_M_refdata(), __n, __c);

      __r->_M_set_length_and_sharable(__n);
      return __r->_M_refdata();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str)
    : _M_dataplus(__str._M_rep()->_M_grab(_Alloc(__str.get_allocator()),
       __str.get_allocator()),
    __str.get_allocator())
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _Alloc& __a)
    : _M_dataplus(_S_construct(size_type(), _CharT(), __a), __a)
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos, size_type __n)
    : _M_dataplus(_S_construct(__str._M_data()
          + __str._M_check(__pos,
      "basic_string::basic_string"),
          __str._M_data() + __str._M_limit(__pos, __n)
          + __pos, _Alloc()), _Alloc())
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos,
   size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__str._M_data()
          + __str._M_check(__pos,
      "basic_string::basic_string"),
          __str._M_data() + __str._M_limit(__pos, __n)
          + __pos, __a), __a)
    { }


  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s + __n, __a), __a)
    { }


  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s ? __s + traits_type::length(__s) :
          __s + npos, __a), __a)
    { }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(size_type __n, _CharT __c, const _Alloc& __a)
    : _M_dataplus(_S_construct(__n, __c, __a), __a)
    { }


  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(_InputIterator __beg, _InputIterator __end, const _Alloc& __a)
    : _M_dataplus(_S_construct(__beg, __end, __a), __a)
    { }
# 240 "/usr/local/include/c++/4.9.0/bits/basic_string.tcc" 3
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const basic_string& __str)
    {
      if (_M_rep() != __str._M_rep())
 {

   const allocator_type __a = this->get_allocator();
   _CharT* __tmp = __str._M_rep()->_M_grab(__a, __str.get_allocator());
   _M_rep()->_M_dispose(__a);
   _M_data(__tmp);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const _CharT* __s, size_type __n)
    {
      ;
      _M_check_length(this->size(), __n, "basic_string::assign");
      if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
 return _M_replace_safe(size_type(0), this->size(), __s, __n);
      else
 {

   const size_type __pos = __s - _M_data();
   if (__pos >= __n)
     _M_copy(_M_data(), __s, __n);
   else if (__pos)
     _M_move(_M_data(), __s, __n);
   _M_rep()->_M_set_length_and_sharable(__n);
   return *this;
 }
     }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(size_type __n, _CharT __c)
    {
      if (__n)
 {
   _M_check_length(size_type(0), __n, "basic_string::append");
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_assign(_M_data() + this->size(), __n, __c);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const _CharT* __s, size_type __n)
    {
      ;
      if (__n)
 {
   _M_check_length(size_type(0), __n, "basic_string::append");
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     {
       if (_M_disjunct(__s))
  this->reserve(__len);
       else
  {
    const size_type __off = __s - _M_data();
    this->reserve(__len);
    __s = _M_data() + __off;
  }
     }
   _M_copy(_M_data() + this->size(), __s, __n);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str)
    {
      const size_type __size = __str.size();
      if (__size)
 {
   const size_type __len = __size + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_copy(_M_data() + this->size(), __str._M_data(), __size);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str, size_type __pos, size_type __n)
    {
      __str._M_check(__pos, "basic_string::append");
      __n = __str._M_limit(__pos, __n);
      if (__n)
 {
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_copy(_M_data() + this->size(), __str._M_data() + __pos, __n);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }

   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     insert(size_type __pos, const _CharT* __s, size_type __n)
     {
       ;
       _M_check(__pos, "basic_string::insert");
       _M_check_length(size_type(0), __n, "basic_string::insert");
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, size_type(0), __s, __n);
       else
         {

           const size_type __off = __s - _M_data();
           _M_mutate(__pos, 0, __n);
           __s = _M_data() + __off;
           _CharT* __p = _M_data() + __pos;
           if (__s + __n <= __p)
             _M_copy(__p, __s, __n);
           else if (__s >= __p)
             _M_copy(__p, __s + __n, __n);
           else
             {
        const size_type __nleft = __p - __s;
               _M_copy(__p, __s, __nleft);
               _M_copy(__p + __nleft, __p + __n, __n - __nleft);
             }
           return *this;
         }
     }

   template<typename _CharT, typename _Traits, typename _Alloc>
     typename basic_string<_CharT, _Traits, _Alloc>::iterator
     basic_string<_CharT, _Traits, _Alloc>::
     erase(iterator __first, iterator __last)
     {
      
                           ;




       const size_type __size = __last - __first;
       if (__size)
  {
    const size_type __pos = __first - _M_ibegin();
    _M_mutate(__pos, __size, size_type(0));
    _M_rep()->_M_set_leaked();
    return iterator(_M_data() + __pos);
  }
       else
  return __first;
     }

   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     replace(size_type __pos, size_type __n1, const _CharT* __s,
      size_type __n2)
     {
       ;
       _M_check(__pos, "basic_string::replace");
       __n1 = _M_limit(__pos, __n1);
       _M_check_length(__n1, __n2, "basic_string::replace");
       bool __left;
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, __n1, __s, __n2);
       else if ((__left = __s + __n2 <= _M_data() + __pos)
  || _M_data() + __pos + __n1 <= __s)
  {

    size_type __off = __s - _M_data();
    __left ? __off : (__off += __n2 - __n1);
    _M_mutate(__pos, __n1, __n2);
    _M_copy(_M_data() + __pos, _M_data() + __off, __n2);
    return *this;
  }
       else
  {

    const basic_string __tmp(__s, __n2);
    return _M_replace_safe(__pos, __n1, __tmp._M_data(), __n2);
  }
     }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_destroy(const _Alloc& __a) throw ()
    {
      const size_type __size = sizeof(_Rep_base) +
                        (this->_M_capacity + 1) * sizeof(_CharT);
      _Raw_bytes_alloc(__a).deallocate(reinterpret_cast<char*>(this), __size);
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_leak_hard()
    {

      if (_M_rep() == &_S_empty_rep())
 return;

      if (_M_rep()->_M_is_shared())
 _M_mutate(0, 0, 0);
      _M_rep()->_M_set_leaked();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_mutate(size_type __pos, size_type __len1, size_type __len2)
    {
      const size_type __old_size = this->size();
      const size_type __new_size = __old_size + __len2 - __len1;
      const size_type __how_much = __old_size - __pos - __len1;

      if (__new_size > this->capacity() || _M_rep()->_M_is_shared())
 {

   const allocator_type __a = get_allocator();
   _Rep* __r = _Rep::_S_create(__new_size, this->capacity(), __a);

   if (__pos)
     _M_copy(__r->_M_refdata(), _M_data(), __pos);
   if (__how_much)
     _M_copy(__r->_M_refdata() + __pos + __len2,
      _M_data() + __pos + __len1, __how_much);

   _M_rep()->_M_dispose(__a);
   _M_data(__r->_M_refdata());
 }
      else if (__how_much && __len1 != __len2)
 {

   _M_move(_M_data() + __pos + __len2,
    _M_data() + __pos + __len1, __how_much);
 }
      _M_rep()->_M_set_length_and_sharable(__new_size);
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    reserve(size_type __res)
    {
      if (__res != this->capacity() || _M_rep()->_M_is_shared())
        {

   if (__res < this->size())
     __res = this->size();
   const allocator_type __a = get_allocator();
   _CharT* __tmp = _M_rep()->_M_clone(__a, __res - this->size());
   _M_rep()->_M_dispose(__a);
   _M_data(__tmp);
        }
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    swap(basic_string& __s)
    {
      if (_M_rep()->_M_is_leaked())
 _M_rep()->_M_set_sharable();
      if (__s._M_rep()->_M_is_leaked())
 __s._M_rep()->_M_set_sharable();
      if (this->get_allocator() == __s.get_allocator())
 {
   _CharT* __tmp = _M_data();
   _M_data(__s._M_data());
   __s._M_data(__tmp);
 }

      else
 {
   const basic_string __tmp1(_M_ibegin(), _M_iend(),
        __s.get_allocator());
   const basic_string __tmp2(__s._M_ibegin(), __s._M_iend(),
        this->get_allocator());
   *this = __tmp2;
   __s = __tmp1;
 }
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::_Rep*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _S_create(size_type __capacity, size_type __old_capacity,
       const _Alloc& __alloc)
    {


      if (__capacity > _S_max_size)
 __throw_length_error(("basic_string::_S_create"));
# 577 "/usr/local/include/c++/4.9.0/bits/basic_string.tcc" 3
      const size_type __pagesize = 4096;
      const size_type __malloc_header_size = 4 * sizeof(void*);







      if (__capacity > __old_capacity && __capacity < 2 * __old_capacity)
 __capacity = 2 * __old_capacity;




      size_type __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);

      const size_type __adj_size = __size + __malloc_header_size;
      if (__adj_size > __pagesize && __capacity > __old_capacity)
 {
   const size_type __extra = __pagesize - __adj_size % __pagesize;
   __capacity += __extra / sizeof(_CharT);

   if (__capacity > _S_max_size)
     __capacity = _S_max_size;
   __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);
 }



      void* __place = _Raw_bytes_alloc(__alloc).allocate(__size);
      _Rep *__p = new (__place) _Rep;
      __p->_M_capacity = __capacity;







      __p->_M_set_sharable();
      return __p;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_clone(const _Alloc& __alloc, size_type __res)
    {

      const size_type __requested_cap = this->_M_length + __res;
      _Rep* __r = _Rep::_S_create(__requested_cap, this->_M_capacity,
      __alloc);
      if (this->_M_length)
 _M_copy(__r->_M_refdata(), _M_refdata(), this->_M_length);

      __r->_M_set_length_and_sharable(this->_M_length);
      return __r->_M_refdata();
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    resize(size_type __n, _CharT __c)
    {
      const size_type __size = this->size();
      _M_check_length(__size, __n, "basic_string::resize");
      if (__size < __n)
 this->append(__n - __size, __c);
      else if (__n < __size)
 this->erase(__n);

    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
      basic_string<_CharT, _Traits, _Alloc>&
      basic_string<_CharT, _Traits, _Alloc>::
      _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
     _InputIterator __k2, __false_type)
      {
 const basic_string __s(__k1, __k2);
 const size_type __n1 = __i2 - __i1;
 _M_check_length(__n1, __s.size(), "basic_string::_M_replace_dispatch");
 return _M_replace_safe(__i1 - _M_ibegin(), __n1, __s._M_data(),
          __s.size());
      }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
     _CharT __c)
    {
      _M_check_length(__n1, __n2, "basic_string::_M_replace_aux");
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
 _M_assign(_M_data() + __pos1, __n2, __c);
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
      size_type __n2)
    {
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
 _M_copy(_M_data() + __pos1, __s, __n2);
      return *this;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      ;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      const __size_type __len = _Traits::length(__lhs);
      __string_type __str;
      __str.reserve(__len + __rhs.size());
      __str.append(__lhs, __len);
      __str.append(__rhs);
      return __str;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      __string_type __str;
      const __size_type __len = __rhs.size();
      __str.reserve(__len + 1);
      __str.append(__size_type(1), __lhs);
      __str.append(__rhs);
      return __str;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    copy(_CharT* __s, size_type __n, size_type __pos) const
    {
      _M_check(__pos, "basic_string::copy");
      __n = _M_limit(__pos, __n);
      ;
      if (__n)
 _M_copy(__s, _M_data() + __pos, __n);

      return __n;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      const _CharT* __data = _M_data();

      if (__n == 0)
 return __pos <= __size ? __pos : npos;

      if (__n <= __size)
 {
   for (; __pos <= __size - __n; ++__pos)
     if (traits_type::eq(__data[__pos], __s[0])
  && traits_type::compare(__data + __pos + 1,
     __s + 1, __n - 1) == 0)
       return __pos;
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(_CharT __c, size_type __pos) const
    {
      size_type __ret = npos;
      const size_type __size = this->size();
      if (__pos < __size)
 {
   const _CharT* __data = _M_data();
   const size_type __n = __size - __pos;
   const _CharT* __p = traits_type::find(__data + __pos, __n, __c);
   if (__p)
     __ret = __p - __data;
 }
      return __ret;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      if (__n <= __size)
 {
   __pos = std::min(size_type(__size - __n), __pos);
   const _CharT* __data = _M_data();
   do
     {
       if (traits_type::compare(__data + __pos, __s, __n) == 0)
  return __pos;
     }
   while (__pos-- > 0);
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(_CharT __c, size_type __pos) const
    {
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   for (++__size; __size-- > 0; )
     if (traits_type::eq(_M_data()[__size], __c))
       return __size;
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __n && __pos < this->size(); ++__pos)
 {
   const _CharT* __p = traits_type::find(__s, __n, _M_data()[__pos]);
   if (__p)
     return __pos;
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size && __n)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (traits_type::find(__s, __n, _M_data()[__size]))
  return __size;
     }
   while (__size-- != 0);
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __pos < this->size(); ++__pos)
 if (!traits_type::find(__s, __n, _M_data()[__pos]))
   return __pos;
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(_CharT __c, size_type __pos) const
    {
      for (; __pos < this->size(); ++__pos)
 if (!traits_type::eq(_M_data()[__pos], __c))
   return __pos;
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (!traits_type::find(__s, __n, _M_data()[__size]))
  return __size;
     }
   while (__size--);
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(_CharT __c, size_type __pos) const
    {
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (!traits_type::eq(_M_data()[__size], __c))
  return __size;
     }
   while (__size--);
 }
      return npos;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n, const basic_string& __str) const
    {
      _M_check(__pos, "basic_string::compare");
      __n = _M_limit(__pos, __n);
      const size_type __osize = __str.size();
      const size_type __len = std::min(__n, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __str.data(), __len);
      if (!__r)
 __r = _S_compare(__n, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos1, size_type __n1, const basic_string& __str,
     size_type __pos2, size_type __n2) const
    {
      _M_check(__pos1, "basic_string::compare");
      __str._M_check(__pos2, "basic_string::compare");
      __n1 = _M_limit(__pos1, __n1);
      __n2 = __str._M_limit(__pos2, __n2);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos1,
         __str.data() + __pos2, __len);
      if (!__r)
 __r = _S_compare(__n1, __n2);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(const _CharT* __s) const
    {
      ;
      const size_type __size = this->size();
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__size, __osize);
      int __r = traits_type::compare(_M_data(), __s, __len);
      if (!__r)
 __r = _S_compare(__size, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__n1, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
 __r = _S_compare(__n1, __osize);
      return __r;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s,
     size_type __n2) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
 __r = _S_compare(__n1, __n2);
      return __r;
    }


  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in,
        basic_string<_CharT, _Traits, _Alloc>& __str)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __istream_type::ios_base __ios_base;
      typedef typename __istream_type::int_type __int_type;
      typedef typename __string_type::size_type __size_type;
      typedef ctype<_CharT> __ctype_type;
      typedef typename __ctype_type::ctype_base __ctype_base;

      __size_type __extracted = 0;
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   try
     {

       __str.erase();
       _CharT __buf[128];
       __size_type __len = 0;
       const streamsize __w = __in.width();
       const __size_type __n = __w > 0 ? static_cast<__size_type>(__w)
                                : __str.max_size();
       const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
       const __int_type __eof = _Traits::eof();
       __int_type __c = __in.rdbuf()->sgetc();

       while (__extracted < __n
       && !_Traits::eq_int_type(__c, __eof)
       && !__ct.is(__ctype_base::space,
     _Traits::to_char_type(__c)))
  {
    if (__len == sizeof(__buf) / sizeof(_CharT))
      {
        __str.append(__buf, sizeof(__buf) / sizeof(_CharT));
        __len = 0;
      }
    __buf[__len++] = _Traits::to_char_type(__c);
    ++__extracted;
    __c = __in.rdbuf()->snextc();
  }
       __str.append(__buf, __len);

       if (_Traits::eq_int_type(__c, __eof))
  __err |= __ios_base::eofbit;
       __in.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     {



       __in._M_setstate(__ios_base::badbit);
     }
 }

      if (!__extracted)
 __err |= __ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }

  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __in,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __istream_type::ios_base __ios_base;
      typedef typename __istream_type::int_type __int_type;
      typedef typename __string_type::size_type __size_type;

      __size_type __extracted = 0;
      const __size_type __n = __str.max_size();
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, true);
      if (__cerb)
 {
   try
     {
       __str.erase();
       const __int_type __idelim = _Traits::to_int_type(__delim);
       const __int_type __eof = _Traits::eof();
       __int_type __c = __in.rdbuf()->sgetc();

       while (__extracted < __n
       && !_Traits::eq_int_type(__c, __eof)
       && !_Traits::eq_int_type(__c, __idelim))
  {
    __str += _Traits::to_char_type(__c);
    ++__extracted;
    __c = __in.rdbuf()->snextc();
  }

       if (_Traits::eq_int_type(__c, __eof))
  __err |= __ios_base::eofbit;
       else if (_Traits::eq_int_type(__c, __idelim))
  {
    ++__extracted;
    __in.rdbuf()->sbumpc();
  }
       else
  __err |= __ios_base::failbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     {



       __in._M_setstate(__ios_base::badbit);
     }
 }
      if (!__extracted)
 __err |= __ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }




  extern template class basic_string<char>;
  extern template
    basic_istream<char>&
    operator>>(basic_istream<char>&, string&);
  extern template
    basic_ostream<char>&
    operator<<(basic_ostream<char>&, const string&);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&, char);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&);


  extern template class basic_string<wchar_t>;
  extern template
    basic_istream<wchar_t>&
    operator>>(basic_istream<wchar_t>&, wstring&);
  extern template
    basic_ostream<wchar_t>&
    operator<<(basic_ostream<wchar_t>&, const wstring&);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&, wchar_t);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&);




}
# 54 "/usr/local/include/c++/4.9.0/string" 2 3
# 40 "factory.h" 2


namespace unise
{


class Any
{
public:
    Any() : _var_ptr(__null) {}

    template<typename T>
    Any(const T &value) : _var_ptr(new Type<T>(value)) {}

    Any(const Any &other) : _var_ptr(other._var_ptr ? other._var_ptr->clone() : __null) {}

    ~Any() {
        delete _var_ptr;
    }

    template<typename T>
    T *any_cast() {
        return _var_ptr ? &static_cast<Type<T> *>(_var_ptr)->_var : __null;
    }

private:

    class Typeless
    {
    public:
        virtual ~Typeless() {}
        virtual Typeless *clone() const = 0;
    };


    template<typename T>
    class Type : public Typeless
    {
    public:
        explicit Type(const T &value) : _var(value) {}
        virtual Typeless *clone() const {
            return new Type(_var);
        }
        T _var;
    };
    Typeless *_var_ptr;
};


struct ConcreteFactory {
    typedef Any(*FactoryIntf)();
    FactoryIntf get_instance;
    FactoryIntf get_singleton;
};



typedef std::map<std::string, ConcreteFactory> FactoryMap;
typedef std::map<std::string, FactoryMap> BaseClassMap;



BaseClassMap& g_factory_map();
}
