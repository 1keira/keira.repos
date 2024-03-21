/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef IPL_ALIGN_HXX
#define IPL_ALIGN_HXX
/*****************************************************************************/

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <stddef.h>

#ifdef HAVE_STD_ALIGN
#include <memory>
#include "Macros.hxx"
#include <iplbase/type_traits.hxx>
#endif

/*****************************************************************************/

namespace IPL_NAMESPACE {

/*****************************************************************************/

    /*!
        \brief Align integer to a multiple of \a alignment

        If \a alignment is not specified,
        some alignment appropriate for all types is used.
    */
    inline size_t align(size_t address, size_t alignment=IPL_MAX_ALIGNMENT) IPL_NOEXCEPT
    {
        address+=alignment-1;
        address-=address%alignment;
        return address;
    }

/*****************************************************************************/

    /*!
        \brief Align pointer to a multiple of \a alignment

        If \a alignment is not specified,
        some alignment appropriate for all types is used.
    */
    template <typename T>
    inline T *align(T *p, size_t alignment=IPL_MAX_ALIGNMENT) IPL_NOEXCEPT
    {
        return reinterpret_cast<T *>(align(reinterpret_cast<size_t>(p),
                                           alignment));
    }

/*****************************************************************************/

    /*!
        \brief Cast pointer suppressing gcc5 alignment warnings

        With \a T being a \b pointer \b type this is roughly equivalent to
        <code>reinterpret_cast<T>(pointer)</code>,
        except gcc5 accepts it without warnings.

        Use as in
        <code>
            unsigned char *p;
            long *l=ipl::cast_without_warning<long *>(p);  // changes alignment requirements
        </code>

        Depending on the version of language and library, proper alingment
        is possibly asserted.
    */
    template<typename T, typename U>
    inline T cast_without_warning(U *pointer)
    {
#ifdef HAVE_STD_ALIGN
        // avoiding (false positive) alignment warnings
        void *p=(void *)pointer;
        size_t b=sizeof(typename iplbase::remove_pointer<T>::type);
        T result=(T)std::align(
            1, // assume that it is already suitably aligned anyway...
            b, p, b
        );
        IPL_ASSERT((void *)result==p);
        return result;
#else
        return (T)(void *)pointer;
#endif
    }

/*****************************************************************************/

}  // end of namespace IPL_NAMESPACE

/*****************************************************************************/
#endif
