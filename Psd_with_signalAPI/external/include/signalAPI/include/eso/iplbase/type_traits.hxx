/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef IPLBASE_TYPE_TRAITS_HXX
#define IPLBASE_TYPE_TRAITS_HXX
/*****************************************************************************/
/*!
    \file
    \brief Type traits more or less conformant to C++11 [meta.*]

    Some standard traits are known missing:
    - \c is_rvalue_reference as there is no such thing in C++ before 11
    - \c is_member_function_pointer as I don't know how to implement it yet
    - \c is_enum as I don't know how to implement it yet
    - \c is_union as I don't know how to implement it yet
    - \c is_typename as I don't know how to implement it yet
    - \c is_function as I don't know how to implement it yet
    - \c is_trivial as I don't know how to implement it yet
    - \c is_trivially_copyable as I don't know how to implement it yet
    - \c is_standard_layout as I don't know how to implement it yet
    - \c is_pod as I don't know how to implement it yet
    - \c is_literal_type as I don't know how to implement it yet
    - \c is_empty as I don't know how to implement it yet
    - \c is_polymorphic as I don't know how to implement it yet
    - \c is_abstract as I don't know how to implement it yet
    - \c is_base_of as I don't know how to implement it yet
    - \c is_convertible as I don't know how to implement it yet
    - \c aligned_* as I don't know how to implement it yet
    - \c decay as I don't know how to implement it yet
    - \c *_type as I don't know how to implement it yet
    - \c result_* as I don't know how to implement it yet
    - \c is_object as it depends on \c is_function
    - \c is_scalar depends on \c is_member_function_pointer
    - \c is_member_pointer depends on \c is_member_function_pointer
    - \c is_compound depends on \c is_member_function_pointer
    - \c is_*_constructible as it requires template varargs not available before C++11
    - \c is_destructible as I have no idea how to implement it
    - ...and all their friends
    - \c alignment_of as I have no idea how to implement it
    - \c nullptr_t is not recognized
    - \c char16_t is not recognized
    - \c chat32_t is not recognized
    
*/
/*****************************************************************************/

namespace iplbase {

/*****************************************************************************/

    // [meta.help], helper class:
    template <typename T, T VALUE> struct integral_constant {
        typedef T value_type;
        static /*constexpr*/const T value=VALUE;
        typedef integral_constant<T, VALUE> type;

        /*constexpr*/ operator value_type() const { return value; }
    };
    
    typedef integral_constant<bool, true>  true_type;
    typedef integral_constant<bool, false> false_type;
    
/*****************************************************************************/

    // [meta.unary.cat], primary type categories:
    template <typename T> struct is_void: public false_type {};
    template <typename T> struct is_void<T const>: public is_void<T> {};
    template <typename T> struct is_void<T volatile>: public is_void<T> {};
    template <typename T> struct is_void<T const volatile>: public is_void<T> {};
    template <> struct is_void<void>:  public true_type {};
    
    template <typename T> struct is_integral: public false_type {};
    template <typename T> struct is_integral<T const>: public is_integral<T> {};
    template <typename T> struct is_integral<T volatile>: public is_integral<T> {};
    template <typename T> struct is_integral<T const volatile>: public is_integral<T> {};
    template <> struct is_integral<bool>: public true_type {};
    template <> struct is_integral<char>: public true_type {};
    template <> struct is_integral<wchar_t>: public true_type {};
    template <> struct is_integral<signed char>: public true_type {};
    template <> struct is_integral<unsigned char>: public true_type {};
    template <> struct is_integral<signed short>: public true_type {};
    template <> struct is_integral<unsigned short>: public true_type {};
    template <> struct is_integral<signed int>: public true_type {};
    template <> struct is_integral<unsigned int>: public true_type {};
    template <> struct is_integral<signed long>: public true_type {};
    template <> struct is_integral<unsigned long>: public true_type {};
    template <> struct is_integral<signed long long>: public true_type {};
    template <> struct is_integral<unsigned long long>: public true_type {};
    
    template <typename T> struct is_floating_point: public false_type {};
    template <typename T> struct is_floating_point<T const>: public is_floating_point<T> {};
    template <typename T> struct is_floating_point<T volatile>: public is_floating_point<T> {};
    template <typename T> struct is_floating_point<T const volatile>: public is_floating_point<T> {};
    template <> struct is_floating_point<float>: public true_type {};
    template <> struct is_floating_point<double>: public true_type {};
    template <> struct is_floating_point<long double>: public true_type {};
    
    template <typename T> struct is_array: public false_type {};
    template <typename T> struct is_array<T const>: public is_array<T> {};
    template <typename T> struct is_array<T volatile>: public is_array<T> {};
    template <typename T> struct is_array<T const volatile>: public is_array<T> {};
    template <typename T> struct is_array<T[]>: public true_type {};
    template <typename T, /*typename S, S*/int SIZE> struct is_array<T[SIZE]>: public true_type {};
    
    template <typename T> struct is_pointer: public false_type {};
    template <typename T> struct is_pointer<T const>: public is_pointer<T> {};
    template <typename T> struct is_pointer<T volatile>: public is_pointer<T> {};
    template <typename T> struct is_pointer<T const volatile>: public is_pointer<T> {};
    template <typename T> struct is_pointer<T *>: public true_type {};

    template <typename T> struct is_lvalue_reference: public false_type {};
    template <typename T> struct is_lvalue_reference<T &>: public true_type {};
    
    template <typename T> struct is_member_object_pointer: public false_type {};
    template <typename T, typename U> struct is_member_object_pointer< U T:: *>: public true_type {};
    template <typename T, typename U> struct is_member_object_pointer<U T:: *const>: public true_type {};
    template <typename T, typename U> struct is_member_object_pointer<U T:: *volatile>: public true_type {};
    template <typename T, typename U> struct is_member_object_pointer<U T:: *const volatile>: public true_type {};

    
/*****************************************************************************/

    // [meta.unary.comp], composite type categories:
    template <typename T> struct is_reference:
        public integral_constant<bool, is_lvalue_reference<T>::value /*||
                                       is_rvalue_reference<T>::value*/>
    {};
        
    template <typename T> struct is_arithmetic:
        public integral_constant<bool, is_integral<T>::value ||
                                       is_floating_point<T>::value>
    {};
    
    template <typename T> struct is_fundamental:
        public integral_constant<bool, is_arithmetic<T>::value>
    {};
    template <> struct is_fundamental<void>: true_type {};

    
/*****************************************************************************/

    // [meta.unary.prop], type properties:
    template <typename T> struct is_const: public false_type {};
    template <typename T> struct is_const<T const>: public true_type {};

    template <typename T> struct is_volatile: public false_type {};
    template <typename T> struct is_volatile<T volatile>: public true_type {};

// GCC in -Werr mode wines about the comparision always being false,
// but we need to compare, as the very definition of signed/unsigned from the
// standard is in terms of this comparision.
// Hence we suppress the warning/error, but only for the compiler we do
// nowarnings-builds with for now.
#ifdef __GNUC__
#if (__GNUC__*10000+__GNUC_MINOR__*100+__GNUC_PATCHLEVEL__)>=40600
#pragma GCC diagnostic push  // not supported before GCC 4.6
#endif
// GHS compiler does not support GCC pragmas
#ifndef __ghs__
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif
#endif

    template <typename T,
              bool internal1=is_arithmetic<T>::value,
              bool internal2=is_floating_point<T>::value> struct is_signed:
        public false_type {};
    template <typename T> struct is_signed<T, true, false>:
        public integral_constant<bool, T(-1)<T(0)> {};
    template <typename T> struct is_signed<T, true, true>:
        public true_type {};  // floats are signed but float(-1) is invalid as a constant expression

    template <typename T,
              bool internal1=is_arithmetic<T>::value,
              bool internal2=is_floating_point<T>::value> struct is_unsigned:
        public false_type {};
    template <typename T> struct is_unsigned<T, true, false>:
        public integral_constant<bool, T(0)<T(-1)> {};
    template <typename T> struct is_unsigned<T, true, true>:
        public false_type {};  // floats are signed but float(-1) is invalid as a constant expression

#ifdef __GNUC__
#if (__GNUC__*10000+__GNUC_MINOR__*100+__GNUC_PATCHLEVEL__)>=40600
#pragma GCC diagnostic pop  // not supported before GCC 4.6
#endif
#endif
    
/*****************************************************************************/

    template <typename T> struct rank: public integral_constant<unsigned, 0> {};
    template <typename T> struct rank<T[]>:
        public integral_constant<typename rank<T>::value_type, rank<T>::value+1>
    {};
    template <typename T, /*typename S, S*/int SIZE> struct rank<T[SIZE]>:
        public rank<T[]> {};
    
    template <typename T, unsigned I=0> struct extent:
        public integral_constant<int, 0> {};
    template <typename T, unsigned I> struct extent<T[], I>:
        public integral_constant<typename extent<T, I-1>::value_type, extent<T, I-1>::value>
    {};
    template <typename T> struct extent<T[], 0>:
        public integral_constant<int, 0> {};
    template <typename T, unsigned I, /*typename S, S*/int SIZE> struct extent<T[SIZE], I>:
        public integral_constant<typename extent<T, I-1>::value_type, extent<T, I-1>::value>
    {};
    template <typename T, /*typename S, S*/int SIZE> struct extent<T[SIZE], 0>:
        public integral_constant</* S */int, SIZE>
    {};
    
/*****************************************************************************/

    // [meta.rel], type relations:
    template <typename T, typename U> struct is_same: public false_type {};
    template <typename T> struct is_same<T, T>: public true_type {};
    
/*****************************************************************************/

    // [meta.trans.cv], const-volatile modifications:
    template <typename T> struct remove_const { typedef T type; };
    template <typename T> struct remove_const<T const> { typedef T type; };
    
    template <typename T> struct remove_volatile { typedef T type; };
    template <typename T> struct remove_volatile<T volatile> { typedef T type; };

    template <typename T> struct remove_cv:
        public remove_const<typename remove_volatile<T>::type>
    {};

    template <typename T> struct add_const { typedef T const type; };
    template <typename T> struct add_const<T const> { typedef T const type; };
    
    template <typename T> struct add_volatile { typedef T volatile type; };
    template <typename T> struct add_volatile<T volatile> { typedef T volatile type; };

    template <typename T> struct add_cv:
        public add_const<typename add_volatile<T>::type>
    {};
    
/*****************************************************************************/

    // [meta.trans.ref], reference modifications:
    template <typename T> struct remove_reference { typedef T type; };
    template <typename T> struct remove_reference<T &> { typedef T type; };
    
    template <typename T> struct add_lvalue_reference { typedef T &type; };
    template <typename T> struct add_lvalue_reference<T &> { typedef T &type; };
    
/*****************************************************************************/


    // [meta.trans.arr], array modifications:
    template <typename T> struct remove_extent { typedef T type; };
    template <typename T> struct remove_extent<T[]> { typedef T type; };
    template <typename T, /*typename S, S*/int SIZE> struct remove_extent<T[SIZE]> {
        typedef T type;
    };
    
    template <typename T> struct remove_all_extents { typedef T type; };
    template <typename T> struct remove_all_extents<T[]>:
        public remove_all_extents<T>
    {};
    template <typename T, /*typename S, S*/int SIZE> struct remove_all_extents<T[SIZE]>:
        public remove_all_extents<T>
    {};
    
/*****************************************************************************/

    //[meta.trans.ptr], pointer modifications:
    template <typename T> struct remove_pointer { typedef T type; };
    template <typename T> struct remove_pointer<T *> { typedef T type; };
    template <typename T> struct remove_pointer<T *const> { typedef T type; };
    template <typename T> struct remove_pointer<T *volatile> { typedef T type; };
    template <typename T> struct remove_pointer<T *const volatile> { typedef T type; };

    template <typename T> struct add_pointer {
        typedef typename remove_reference<T>::type *type;
    };
    
/*****************************************************************************/

    // [meta.trans.other], other transformations:

    template <bool, typename T=void> struct enable_if { /* no type */ };
    template <typename T> struct enable_if<true, T> { typedef T type; };
    
    template <bool, typename T, typename F> struct conditional { typedef F type; };
    template <typename T, typename F> struct conditional<true, T, F> { typedef T type; };
    

/*****************************************************************************/

}  // end of namespace iplbase

/*****************************************************************************/
#endif
