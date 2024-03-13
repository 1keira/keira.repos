/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef COMMON_PSEUDOBOOL_HXX
#define COMMON_PSEUDOBOOL_HXX
/*****************************************************************************/

#include <common/ipl_namespace.hxx>
#include <common/iplcommon_dso.h>

/*****************************************************************************/

namespace IPL_NAMESPACE {

/*****************************************************************************/

    /*!
        \brief Type to use for cast-to-bool operator methods instead of \c bool

        If you want to be able to put some object into \c if() as if it was a
        \c bool, you would normally just add an \c operator \c bool to its class.
        Unfortunately that doesn't do what you want, though, due to implicit
        type coercion rules.

        The standard way around this is to add a cast operator to some random
        function pointer type instead (which implicitly coerces to bool) and
        use any function matching the type as \c true and \c NULL as \c false.
        While this works well it also tends to be very non-obvious, and if you
        don't want unnecessary dependencies you must pick a function that is
        already used by the class. Which is not always possible.

        In order to relieve you from picking a suitable albeit random function
        while making your intent clearer, we provide an explicit PseudoBool type
        here together with constants of PSEUDO_TRUE ans PSEUDO_FALSE.
        Instead of putting an \c operator \c bool returning \c true or \c false
        into your class, you put in an \c operator \c ipl::PseudoBool and
        have it return \c ipl::PSEUDO_TRUE or \c ipl::PSEUDO_FALSE.
        That's all.
    */
    typedef void (*PseudoBool)();
    //! \brief PseudoBool constant that evaluates \c false in a bool context
    IPLCOMMON_EXPORT extern const PseudoBool PSEUDO_FALSE;
    //! \brief PseudoBool constant that evaluates \c true in a bool context
    //!
    //! Ignore that this is really a function, that's but a technical aspect.
    IPLCOMMON_EXPORT void PSEUDO_TRUE();

/*****************************************************************************/

}  // end of namespace IPL_NAMESPACE

/*****************************************************************************/
#endif
