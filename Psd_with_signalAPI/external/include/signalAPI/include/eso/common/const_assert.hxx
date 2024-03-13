/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_CONST_ASSERT_HXX
#define IPL_CONST_ASSERT_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#if __cplusplus>=201103L  // C++11
    #define IPL_CONST_ASSERT(COND) static_assert( COND, #COND )
    #define IPL_CONST_ASSERT_LABEL(LABEL, COND) static_assert( COND, #LABEL )
#elif defined __clang__
    #define IPL_CONST_ASSERT(COND) _Static_assert( COND, #COND )
    #define IPL_CONST_ASSERT_LABEL(LABEL, COND) _Static_assert( COND, #LABEL )
#else
    #define IPL_CONST_ASSERT(COND) ipl::const_assert< COND >::testme()
    #define IPL_CONST_ASSERT_LABEL(LABEL, COND)\
        typedef ipl::const_assert< COND > LABEL; LABEL::testme()

    namespace IPL_NAMESPACE
    {

        /**
        * \brief
        *     Compile time assert helper

        *     This templated class provides a standard way of aborting the
        *     compilation process in case some condition turns out to be
        *     false.
        *
        *     The condition need to be evaluable during compile time i.e. it
        *     needs to consist of compile-time constants.
        *
        *     This can only be used within function bodies, not at global
        *     scope or in class declarations.
        *
        *     The error message that results from an invalid condition depends
        *     on the compiler used. Usually you will get something like
        *     "const_assert\<false> not defined / incomplete".

        *     please don't directly instantiate const_assert, compile time assertion
        *     support is compiler dependent, the template based implementation isn't always
        *     usable

        *     please use the variant with a label that explains the assertion.
        *     IPL_CONST_ASSERT_LABEL( please_correct_your_code, 10 < 50 );
        *     The condition only variant is here for backwards compatibility only
        *     IPL_CONST_ASSERT( 10 < 5 );
        * \note
        *     The C+11 standard has static_assert for this.
        **/
        template <bool condition>
        struct const_assert
        {
            const_assert() IPL_NOEXCEPT
            {
        // we use _Static_assert for clang, this shouldn't get instantiated with clang
        #ifndef __clang__
                const_assert<condition>::testme();
        #endif
            }

        };

        //! Specialization of const_assert for the positive case
        template<>
        struct const_assert<true>
        {
            static void testme() IPL_NOEXCEPT
            { }
        };

    } // end ns ipl

#endif

#endif
