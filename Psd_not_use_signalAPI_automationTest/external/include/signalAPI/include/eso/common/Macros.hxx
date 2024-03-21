/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_MACROS_HXX
#define IPL_MACROS_HXX

// Collection of unspecific but still useful C macros

#include <stdio.h>
#include <stdlib.h>

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#ifndef IPL_NO_PRINTF_LIKE_FUNCTION_CHECK
#    ifdef __GNUC__
        /**
         * \brief
         *    Attribute for printf-like functions in gcc

         *     GCC allows compile time checks of functions that
         *     behave like the printf family of functions i.e.
         *     that take a format string plus varargs and the
         *     format string works just like the C printf API.
         *
         *     This feature is only available for gcc
         *     compilers. You need to put this macro after the
         *     function of concern. The parameter \c
         *     stringIndex denotes the number of the parameter
         *     that contains the format string. The parameter
         *     \c firstToCheck denotes the number of the first
         *     vararg parameter of the function.
         *
         *     For both parameters the following rules apply:
         *     Counting starts at one. For non-static member
         *     functions of C++ classes you need to add one for
         *     the "this" pointer of the class instance.
         **/
#        define IPL_PRINTF_LIKE_FUNCTION(stringIndex, firstToCheck)\
             __attribute__((format(printf, stringIndex, firstToCheck)))
#    else
#        define IPL_PRINTF_LIKE_FUNCTION(stringIndex, firstToCheck) /* empty */
#    endif
#endif

/**
 * \brief
 *     Aborts program execution

 *     Calls ipl::GlobalErrorHandler::doAbort(), providing the current
 *     source code location and the given text message to it.
 **/
#define IPL_ABORT(...) \
    ipl::GlobalErrorHandler::doAbort(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

// we've decided not to disable asserts ever
#if 1 //#ifndef NDEBUG
    /**
    * \brief
    *     Abort program execution if the given condition evaluates to zero

    *     If \c COND evaluates to zero then
    *     ipl::GlobalErrorHandle::doAssert() will be called, providing the
    *     current source code location and the given text message to it
    **/
    #define IPL_ASSERT_VERBOSE(COND, ...) \
        do { \
            if(! (COND)) {\
                ipl::GlobalErrorHandler::doAssert(\
                    false,\
                    #COND,\
                    __FILE__,\
                    __LINE__,\
                    __FUNCTION__,\
                    __VA_ARGS__);\
            } \
        } while(0)

    /**
    * \brief
    *     Abort program execution if the given condition evaluates to zero

    *     Does the same as IPL_ASSERT_VERBOSE but without specifying and
    *     additional text message.
    **/
    #define IPL_ASSERT(COND) \
        do { \
            if(! (COND)) {\
                ipl::GlobalErrorHandler::doAssert(\
                    false,\
                    #COND,\
                    __FILE__,\
                    __LINE__,\
                    __FUNCTION__);\
            } \
        } while(0)

#else

    // for the NDEBUG case we expand to (void)(COND) to avoid unused
    // variable warnings if -Wall is set on GCC.
    // ...and with sizeof we even avoid evaluating COND
    // (http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert)
    #define IPL_ASSERT(COND) (void)(sizeof(COND))
    #define IPL_ASSERT_VERBOSE(COND, ...) (void)(sizeof(COND))

#endif  // NDEBUG

/**
 * \brief
 *     Emit a warning containing the given text message

 *     Calls ipl::GlobalErrorHandler::doWarning() providing it with the
 *     current source code loaction and the given text message.
 **/
#define IPL_WARN(...) \
    ipl::GlobalErrorHandler::doWarning(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

/**
 * \brief
 *     Engage out of memory handling

 *     If a heap memory allocation failed you should call this macro.
 *     It call ipl::GlobalErrorHandler::doOutOfMem() providing it with
 *     the current source code location and the given text message.
 *
 *     If this macro returns then you should retry the memory
 *     allocation to see whether it can now succeed.
 **/
#define IPL_OOM(...) \
    ipl::GlobalErrorHandler::doOutOfMem(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

/**
 * \brief
 *     Try to allocate data via NEWCALL assigning it to PTR

 *     NEWCALL is supposed to be an arbitrary call to "new". The memory
 *     returned from new is assigned to PTR. If no memory could be
 *     obtained then IPL_OOM is called with MSG and if that returns the
 *     allocation is attempted again
 **/
#define IPL_NEW(PTR, NEWCALL, MSG) \
     do {\
        PTR=NULL;\
        while( !PTR )\
        {\
            PTR = NEWCALL;\
            if( !PTR )\
            {\
                IPL_OOM(MSG);\
            }\
        }\
    } while(0)


/**
 * \brief
 *     returns the minimum of two values X and Y.
 * \warning
 *     Don't use dangerous constructs like:
 *
 *     int i, j;
 *     // ...
 *     int min = MIN(i++, j++)
 *
 *     As here your variables i and j would be incremented twice, not
 *     once. This is an unavoidable sideeffect when using macros.
 **/
#define IPL_MIN(X,Y) ( (X) < (Y) ? (X) : (Y) )

/**
 * \brief
 *     returns the maximum of two values X and Y.
 * \warning
 *     Don't use dangerous constructs like:
 *
 *     int i, j;
 *     // ...
 *     int max = MAX(i++, j++)
 *
 *     As here your variables i and j would be incremented twice, not
 *     once. This is an unavoidable sideeffect when using macros.
 **/
#define IPL_MAX(X,Y) ( (X) > (Y) ? (X) : (Y) )

/* Note IPL_NO_DEPRECATION can be used to turn off warnings in a single cpp/cxx compilation unit. */
/* For header files, see IPL_DISABLE_WARNING_* below */

//@{
/**
 * \brief
 *     Marking functions/types as deprecated
 *
 *     Put this around a function or type declaration, end BEFORE the terminating semicolon:
 *
 *     IPL_DEPRECATED( "use my_new_func() instead.", void myfunc() ) ;
 *
 *     IPL_DEPRECATED( "use a_new_t instead.", typedef struct {int a;} a_t ) ;
 *
 *     to get compile warnings when using the function/type.
 *
 *     For classes, structs, unions, namespaces, enums, templates, start the makro AFTER the keyword:
 *
 *     union IPL_DEPRECATED( "use std::variant instead.", myunion{} ) ;
 *
 *     class IPL_DEPRECATED( "use ANew instead.", AOld {int a;} ) ;
 *
 *     Do not combine &lt;module&gt;_EXPORT declarations with IPL_DEPRECATED
 *     because some compiler/options cannot handle
 *
 *     struct __attribute__((visibility)) [[deprecated]] &lt;structname&gt;
 *
 *     combinations,
 *     use two separate declarations instead, &lt;module&gt;_EXPORT as forward declaration.
 *
 *     To disable deprecation warnings,
 *     define IPL_NO_DEPRECATION in your .cpp/.cxx file before any include.
 *
 *     If there is too much code in the __VA_ARGS__ argument, some compilers (especially MSC)
 *     prefer the usage of 2 local start and end macros instead of a single enclosing one:
 *
 *     union IPL_DEPRECATED_PRE( "use std::variant instead." ) myunion{} IPL_DEPRECATED_POST( "use std::variant instead." ) ;
 *
 *     If you combine function/method declaration and implementation (e.g. inline
 *     methods in header files) you also have to use the start/end macros so that
 *     IPL_DEPRECATED_POST appears between the function's signature and body:
 *
 *     IPL_DEPRECATED_PRE("...") void my_func(int my_param) IPL_DEPRECATED_POST("...")
 *     { do_something(my_param); };
 **/
#ifndef IPL_NO_DEPRECATION
#ifndef NDEBUG
#if defined(IPL_OS_ANDROID)
    //   to compile for android, __attribute__ does not work --> cpp14
    #define IPL_DEPRECATED(HELP_MESSAGE,...) [[deprecated(HELP_MESSAGE)]] __VA_ARGS__
    #define IPL_DEPRECATED_PRE(HELP_MESSAGE) [[deprecated(HELP_MESSAGE)]]
    #define IPL_DEPRECATED_POST(HELP_MESSAGE)
#elif (defined(__GNUC__) || defined(__clang__))&&(!defined(IPL_OS_ANDROID))
    #define IPL_DEPRECATED(HELP_MESSAGE,...) __VA_ARGS__ __attribute__((deprecated(HELP_MESSAGE)))
    #define IPL_DEPRECATED_PRE(HELP_MESSAGE)
    #define IPL_DEPRECATED_POST(HELP_MESSAGE) __attribute__((deprecated(HELP_MESSAGE)))
#elif defined(_MSC_VER)
    #define IPL_DEPRECATED(HELP_MESSAGE,...) __declspec(deprecated(HELP_MESSAGE)) __VA_ARGS__
    #define IPL_DEPRECATED_PRE(HELP_MESSAGE) __declspec(deprecated(HELP_MESSAGE))
    #define IPL_DEPRECATED_POST(HELP_MESSAGE)
#elif __cplusplus >= 201402L
    #define IPL_DEPRECATED(HELP_MESSAGE,...) [[deprecated(HELP_MESSAGE)]] __VA_ARGS__
    #define IPL_DEPRECATED_PRE(HELP_MESSAGE) [[deprecated(HELP_MESSAGE)]]
    #define IPL_DEPRECATED_POST(HELP_MESSAGE)
#else
    #define IPL_DEPRECATED(HELP_MESSAGE,...) __VA_ARGS__
    #define IPL_DEPRECATED_PRE(HELP_MESSAGE)
    #define IPL_DEPRECATED_POST(HELP_MESSAGE)
#endif
#else  //  NDEBUG
    //  no deprecated warnigns for release versions:
    #define IPL_DEPRECATED(HELP_MESSAGE,...) __VA_ARGS__
    #define IPL_DEPRECATED_PRE(HELP_MESSAGE)
    #define IPL_DEPRECATED_POST(HELP_MESSAGE)
#endif  //  NDEBUG
#else  //  IPL_NO_DEPRECATION
    //  no deprecated warnigns if explicitly turned off:
    #define IPL_DEPRECATED(HELP_MESSAGE,...) __VA_ARGS__
    #define IPL_DEPRECATED_PRE(HELP_MESSAGE)
    #define IPL_DEPRECATED_POST(HELP_MESSAGE)
#endif  //  IPL_NO_DEPRECATION
//@}

//@{
/**
 * \brief
 *     Macros to temporarily disable deprecation warnings:
 *
 *  For disabling deprecation warnings, there is no RATIONALE needed because "shall be fixed as soon as priorities allow" is assumed.
 */
#if defined(_MSC_VER)
    #define IPL_DISABLE_WARNING_PUSH               __pragma(warning( push ))
    #define IPL_DISABLE_WARNING_POP                __pragma(warning( pop ))
    #define IPL_private_DISABLE_WARNING(WARN_NUM)  __pragma(warning( disable : WARN_NUM ))
    #define IPL_DISABLE_WARNING_DEPRECATION        IPL_private_DISABLE_WARNING(4996)
#elif defined(__GNUC__) || defined(__clang__)
    #define IPL_private_CALL_PRAGMA(X)             _Pragma(#X)
    #define IPL_DISABLE_WARNING_PUSH               IPL_private_CALL_PRAGMA(GCC diagnostic push)
    #define IPL_DISABLE_WARNING_POP                IPL_private_CALL_PRAGMA(GCC diagnostic pop)
    #define IPL_private_DISABLE_WARNING(WARN_NAME) IPL_private_CALL_PRAGMA(GCC diagnostic ignored #WARN_NAME)
    #define IPL_DISABLE_WARNING_DEPRECATION        IPL_private_DISABLE_WARNING(-Wdeprecated-declarations)
#else
    #define IPL_DISABLE_WARNING_PUSH
    #define IPL_DISABLE_WARNING_POP
    #define IPL_DISABLE_WARNING_DEPRECATION
#endif
//@}

//@{
/**
 * \brief
 *     Macros to temporarily disable warnings, e.g. implicit typecast warnings
 *
 *  Note: Warnings of different compilers cannot be mapped 1:1 to each other.
 *  Therefore, we need an abstraction from a warning of a concrete compiler
 *  to the IPL_DISABLE_WARNING_XY macro.
 *  E.g. MSC has warnings 4995 and 4996 which both refer to usage of deprecated functions, gcc just has one warning-type.
 *
 *  Note: Most warnings can be mitigated (alternatively to disabling) by other solution,
 *  Here some examples.
 *
 *  The unused variable warning can be avoided by doing a typecast to void:
 *  (void) my_unused_var;
 *  There are also other means like __maybe_unused for linux, __attribute__((unused)) for gcc
 *
 *  The ellipsis typecast warning can be avoided by using the right type:
 *  %d %ld %lld
 *  PRId8    PRId16  PRId32  PRId64
 *  PRIdFAST8   PRIdFAST16  PRIdFAST32  PRIdFAST64
 *  PRIdPTR
 *  PRIu8   PRIu16  PRIu32  PRIu64
 *  PRIuFAST8   PRIuFAST16  PRIuFAST32  PRIuFAST64
 *  PRIuPTR
 *  PRIx8   PRIx16  PRIx32  PRIx64
 *  PRIxFAST8   PRIxFAST16  PRIxFAST32  PRIxFAST64
 *  PRIxPTR
 *  etc.
 */
/*
 *  To achieve a similar abstration level of all disable warning macros, align newly added macros with following examples:
 *
 *  IPL_DISABLE_WARNING_IMPLICIT_TYPE_CAST(RATIONALE)  // for printf-ellipsis typecasts and precision loss and bool-compare and others
 *  IPL_DISABLE_WARNING_NARROWING_TYPE_CAST(RATIONALE)  // for casts that may drop significant bits
 *  IPL_DISABLE_WARNING_OVERLENGTH_LITERAL(RATIONALE)  // for overlength-strings etc
 *  IPL_DISABLE_WARNING_UNUSED_VARIABLE(RATIONALE)  // to disable warnings on unused variables
 *  IPL_DISABLE_WARNING_COMPILER_OPTIMIZATION(RATIONALE)  // to disable warnings from compiler optimizations that do not fully reflect the source
 *  IPL_DISABLE_WARNING_UNINITIALIZED_VARIABLE(RATIONALE)
 */
#if defined(_MSC_VER)
    /* see https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c4000-c5999 */
    #define IPL_DISABLE_WARNING_IMPLICIT_TYPE_CAST(RATIONALE)          IPL_private_DISABLE_WARNING(4800)  /* typecasts to bool */\
                                                                       IPL_private_DISABLE_WARNING(4477)  /* typecasts in printf */
    #define IPL_DISABLE_WARNING_CAST_INCREASES_ALIGNMENT(RATIONALE)    IPL_private_DISABLE_WARNING(4367)
    #define IPL_DISABLE_WARNING_SELF_ASSIGN(RATIONALE)
    #define IPL_DISABLE_WARNING_FOR_LOOP_ANALYSIS(RATIONALE)
    #define IPL_DISABLE_WARNING_SHIFT_OVERFLOW(RATIONALE)              IPL_private_DISABLE_WARNING(4333)
    #define IPL_DISABLE_WARNING_MAYBE_UNINITIALIZED(RATIONALE)         IPL_private_DISABLE_WARNING(4701)
    #define IPL_DISABLE_WARNING_UNUSED_RESULT(RATIONALE)
    #define IPL_DISABLE_WARNING_STRICT_ALIASING(RATIONALE)
    #define IPL_DISABLE_WARNING_MISSING_OVERRIDE(RATIONALE)            IPL_private_DISABLE_WARNING(4492)
    #define IPL_DISABLE_WARNING_FORMAT_STRING_NONLITERAL(RATIONALE)    IPL_private_DISABLE_WARNING(4774)
    #define IPL_DISABLE_WARNING_SIGN_PROMO(RATIONALE)
#elif defined(__GNUC__) && !defined(__clang__)
    #define IPL_DISABLE_WARNING_IMPLICIT_TYPE_CAST(RATIONALE)          IPL_private_DISABLE_WARNING(-Wbool-compare) /* typecasts to bool */\
                                                                       IPL_private_DISABLE_WARNING(-Wformat) /* typecasts in printf */
    #define IPL_DISABLE_WARNING_CAST_INCREASES_ALIGNMENT(RATIONALE)    IPL_private_DISABLE_WARNING(-Wcast-align)
    #define IPL_DISABLE_WARNING_SELF_ASSIGN(RATIONALE)
    #define IPL_DISABLE_WARNING_FOR_LOOP_ANALYSIS(RATIONALE)
    #define IPL_DISABLE_WARNING_SHIFT_OVERFLOW(RATIONALE)              IPL_private_DISABLE_WARNING(-Wshift-count-overflow)
    #define IPL_DISABLE_WARNING_MAYBE_UNINITIALIZED(RATIONALE)         IPL_private_DISABLE_WARNING(-Wmaybe-uninitialized)
    #define IPL_DISABLE_WARNING_UNUSED_RESULT(RATIONALE)               IPL_private_DISABLE_WARNING(-Wunused-result)
    #define IPL_DISABLE_WARNING_STRICT_ALIASING(RATIONALE)             IPL_private_DISABLE_WARNING(-Wstrict-aliasing)
    #define IPL_DISABLE_WARNING_MISSING_OVERRIDE(RATIONALE)
    #define IPL_DISABLE_WARNING_FORMAT_STRING_NONLITERAL(RATIONALE)    IPL_private_DISABLE_WARNING(-Wformat-nonliteral)
    #define IPL_DISABLE_WARNING_SIGN_PROMO(RATIONALE)                  IPL_private_DISABLE_WARNING(-Wsign-promo)
#elif defined(__clang__)
    #define IPL_DISABLE_WARNING_IMPLICIT_TYPE_CAST(RATIONALE)          IPL_private_DISABLE_WARNING(-Wbool-compare) /* typecasts to bool */\
                                                                       IPL_private_DISABLE_WARNING(-Wformat) /* typecasts in printf */
    #define IPL_DISABLE_WARNING_CAST_INCREASES_ALIGNMENT(RATIONALE)    IPL_private_DISABLE_WARNING(-Wcast-align)
    #define IPL_DISABLE_WARNING_SELF_ASSIGN(RATIONALE)                 IPL_private_DISABLE_WARNING(-Wself-assign-overloaded)
    #define IPL_DISABLE_WARNING_FOR_LOOP_ANALYSIS(RATIONALE)           IPL_private_DISABLE_WARNING(-Wfor-loop-analysis)
    #define IPL_DISABLE_WARNING_SHIFT_OVERFLOW(RATIONALE)              IPL_private_DISABLE_WARNING(-Wshift-count-overflow)
    #define IPL_DISABLE_WARNING_MAYBE_UNINITIALIZED(RATIONALE)         IPL_private_DISABLE_WARNING(-Wconditional-uninitialized)
    #define IPL_DISABLE_WARNING_UNUSED_RESULT(RATIONALE)               IPL_private_DISABLE_WARNING(-Wunused-result)
    #define IPL_DISABLE_WARNING_STRICT_ALIASING(RATIONALE)             IPL_private_DISABLE_WARNING(-Wstrict-aliasing)
    #define IPL_DISABLE_WARNING_MISSING_OVERRIDE(RATIONALE)            IPL_private_DISABLE_WARNING(-Winconsistent-missing-override)
    #define IPL_DISABLE_WARNING_FORMAT_STRING_NONLITERAL(RATIONALE)    IPL_private_DISABLE_WARNING(-Wformat-nonliteral)
    #define IPL_DISABLE_WARNING_SIGN_PROMO(RATIONALE)                  IPL_private_DISABLE_WARNING(-Wsign-promo)
#else
    #define IPL_DISABLE_WARNING_IMPLICIT_TYPE_CAST(RATIONALE)
    #define IPL_DISABLE_WARNING_CAST_INCREASES_ALIGNMENT(RATIONALE)
    #define IPL_DISABLE_WARNING_SELF_ASSIGN(RATIONALE)
    #define IPL_DISABLE_WARNING_FOR_LOOP_ANALYSIS(RATIONALE)
    #define IPL_DISABLE_WARNING_SHIFT_OVERFLOW(RATIONALE)
    #define IPL_DISABLE_WARNING_MAYBE_UNINITIALIZED(RATIONALE)
    #define IPL_DISABLE_WARNING_UNUSED_RESULT(RATIONALE)
    #define IPL_DISABLE_WARNING_STRICT_ALIASING(RATIONALE)
    #define IPL_DISABLE_WARNING_MISSING_OVERRIDE(RATIONALE)
    #define IPL_DISABLE_WARNING_FORMAT_STRING_NONLITERAL(RATIONALE)
    #define IPL_DISABLE_WARNING_SIGN_PROMO(RATIONALE)
#endif
//@}

/**
 * \brief
 *     Determines whether a type is plain old data (pod)

 *     According to C++ a type is POD (with no guarantess, if in doubt
 *     please look into the spec.) if:
 *
 *     * it is a primitive type i.e. no class/struct type
 *     * an enum
 *     * a union
 *     * a complex struct/class type that
 *       - has got no protected or private members
 *       - has got no virtual functions
 *       - is not derived from another type
 *       - has got no user defined operators
 *       - has got no user defined constructors or destructors
 *
 *     Determining whether a type is POD is something that in the end
 *     only the compiler itself can do. That is what is macro is for.
 *     It asks the compiler whether a given type is POD or not.
 *
 *     The macro is used like a function with the type to be checked as
 *     its single parameter. The macro returns a boolean value of \c
 *     false if the type is not POD and \c true if the type is
 *     considered POD.
 *
 *     Usage:
 *     \code
 *     if( IPL_IS_POD(int) )
 *     {
 *        // hooray!
 *     }
 *     \endcode
 **/
// __is_pod is a comipler intrinsic of recent gcc versions and MSVC++
// 2005 and newer (maybe also older). If any other compiler comes into
// play we'll have to see. Part of the logic can be done via template
// magic but not all of it. In the worst case IPL_IS_POD simply always
// returns false.
#define IPL_IS_POD __is_pod

/**
 * \brief
 *     Determines for an arbitrary integer value whether its highest
 *     bit is set or not.
 * \return
 *     \c true if highest bit it set, \c false if highest bit is unset
 **/
#define IPL_HIGHEST_BIT_SET(X) \
    ((X >> ((sizeof(X) * 8) - 1)) != 0)

/**
 * \brief
 *     Determines the size of a c array.
 * \return array size
 **/
#define IPL_ARRAY_SIZE(a) \
    (sizeof(a)/sizeof(a[0]))

// include this only here, it's not needed for the macro definitions
// using it, but clients should be able to use them
#include <common/GlobalErrorHandler.hxx>

#endif
