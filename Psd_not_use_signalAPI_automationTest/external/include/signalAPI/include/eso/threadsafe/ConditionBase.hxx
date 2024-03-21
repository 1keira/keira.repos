/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_CONDITIONBASE_HXX
#define THREADSAFE_CONDITIONBASE_HXX
/*****************************************************************************/

#include "threadsafe_dso.h"
#include <iplbase/NonCopyable.hxx>

#ifndef DISABLE_THREADSAFE_UNDEFS_I_ACCEPT_THE_CONSEQUENCES

#ifdef TIMEOUT
#ifdef _MSC_VER
#pragma message(__FILE__)
#pragma message("#undef-ing TIMEOUT to avoid name collision")
#else
#warning #undef-ing TIMEOUT to avoid name collision
#endif
#undef TIMEOUT
#endif

#ifdef ERROR
#ifdef _MSC_VER
#pragma message(__FILE__)
#pragma message("#undef-ing ERROR to avoid name collision")
#else
#warning #undef-ing ERROR to avoid name collision
#endif
#undef ERROR
#endif

#ifdef ERROR_INCONSISTENCY
#ifdef _MSC_VER
#pragma message(__FILE__)
#pragma message("#undef-ing ERROR_INCONSISTENCY to avoid name collision")
#else
#warning #undef-ing ERROR_INCONSISTENCY to avoid name collision
#endif
#undef ERROR_INCONCISTENCY
#endif

#endif

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \brief Common stuff for all Condition/ConditionImpl variants
    */
    class THREADSAFE_EXPORT ConditionBase: public iplbase::NonCopyable {

    public:
        //! \name Error constants
        //! \anchor ipl_ConditionBase_error_constants
        //! \{
        //! \brief Indication for "wait timed out"
        static const char *const TIMEOUT;
        //! \brief Indication for "something went wrong, no details"
        static const char *const ERROR;
        //! \brief Indication for "the condition was used in a way it shouldn't"
        static const char *const ERROR_INCONSISTENCY;
        //! \}

    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
