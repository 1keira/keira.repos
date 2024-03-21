/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_TYPE_TRAITS_HXX
#define IPL_TYPE_TRAITS_HXX

/*
 * this header contains some assorted template magic mostly needed in
 * the area of STL, type traits and similar
 */

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#if defined(HAVE_TYPE_TRAITS)
#include <type_traits>

namespace IPL_NAMESPACE {

    using std::integral_constant;
    using std::true_type;
    using std::false_type;
    using std::is_integral;
    using std::integral_constant;
    using std::is_pod;
}
#else

#include <common/Macros.hxx> // IPL_IS_POD

#ifdef USE_THREADSAFE_IN_OSAL
#include <iplbase/type_traits.hxx>
#endif

namespace IPL_NAMESPACE
{

#ifdef USE_THREADSAFE_IN_OSAL

using iplbase::integral_constant;
using iplbase::true_type;
using iplbase::false_type;
using iplbase::is_integral;

#else

/**
 * \brief
 *     A type that contains a scalar (integral) constant

 *     This type contains a static constant of type T that has got the
 *     value \c the_value.
 *
 *     It is most commonly used with T = bool to provide true/false
 *     semantics tied to a complete type under certain circumstances
 *     like the implementation of \c is_pod.
 **/
template <class T, T the_value>
struct integral_constant
{
    typedef T value_type;
    typedef integral_constant<T, the_value> type;
    static const value_type value = the_value;
};

//! this can be used as a base class to tie the true constant to a type
typedef integral_constant<bool, true> true_type;
//! this can be used as a base class to tie the false constant to a type
typedef integral_constant<bool, false> false_type;

/**
 * \brief
 *     A type that allows to determine whether the type T is an
 *     integral data type

 *     An integral type is a primitive type that represents a whole
 *     number.
 *
 *     This type inherits from \c true_type if T is an integral type
 *     and from \c false_type is T is not an integral type. Thus the
 *     condition can be checked by looking at is_integral<T>::value.
 **/
template <class T>
struct is_integral :
    public integral_constant<bool, false>
{};

#define IPL_MAKE_INTEGRAL_DEFINITION(TYPE) \
template<> \
struct is_integral<TYPE> : \
    public integral_constant<bool, true> \
{}

IPL_MAKE_INTEGRAL_DEFINITION(bool);
IPL_MAKE_INTEGRAL_DEFINITION(char);
IPL_MAKE_INTEGRAL_DEFINITION(unsigned char);
IPL_MAKE_INTEGRAL_DEFINITION(signed char);
IPL_MAKE_INTEGRAL_DEFINITION(int);
IPL_MAKE_INTEGRAL_DEFINITION(unsigned int);
IPL_MAKE_INTEGRAL_DEFINITION(short);
IPL_MAKE_INTEGRAL_DEFINITION(unsigned short);
IPL_MAKE_INTEGRAL_DEFINITION(long long);
IPL_MAKE_INTEGRAL_DEFINITION(long);
IPL_MAKE_INTEGRAL_DEFINITION(unsigned long);
IPL_MAKE_INTEGRAL_DEFINITION(unsigned long long);

#endif

/**
 * \brief
 *     A type that allows to determine whether the type T is plain old
 *     data

 *     This type inherits from \c true_type if T is plain old data and
 *     from \c false_type is T is not plain old data. Thus the
 *     condition can be checked by looking at is_pod<T>::value.
 *
 *     An explanation of when a type is POD and when not can be found
 *     at \c IPL_IS_POD. It can be of interest whether a type is POD or
 *     not when you need to deal with generic templates and want to
 *     optimize your template as good as possible. PODs can be used
 *     with efficient C functions like memcpy, memcmp or memmove while
 *     non-PODs cannot and need to be dealt with calling individual
 *     operators, invoking the usual C++ logic.
 **/
template <class T>
struct is_pod :
    // mage2618: because MSVC doesn't count integral types as PODs
    // we need to add that check here
    public integral_constant<bool, IPL_IS_POD(T) || is_integral<T>::value >
{};

} // end ns ipl

#endif // HAVE_TYPE_TRAITS
#endif
