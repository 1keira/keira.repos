/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_MUTEXBASE_HXX
#define THREADSAFE_MUTEXBASE_HXX
/*****************************************************************************/

#include "threadsafe_dso.h"
#include <iplbase/NonCopyable.hxx>

/*****************************************************************************/

#ifndef DISABLE_THREADSAFE_UNDEFS_I_ACCEPT_THE_CONSEQUENCES

#ifdef ERROR
#ifdef _MSC_VER
// #pragma message(__FILE__)
// #pragma message("#undef-ing ERROR to avoid name collision")
#else
#warning #undef-ing ERROR to avoid name collision
#endif
#undef ERROR
#endif

#endif

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \brief Common stuff for all Mutex/MutexImpl variants
    */
    class THREADSAFE_EXPORT MutexBase: public iplbase::NonCopyable {

    public:
        //! \name Error constants
        //! \anchor ipl_MutexBase_error_constants
        //! \{

        //! \brief Indication for "try_lock() failed"
        static const char *const NO_LUCK;
        //! \brief Indication for "something went wrong, no details"
        static const char *const ERROR;
        //! \brief Indication for "the mutex was used in a way it shouldn't"
        static const char *const ERROR_INCONSISTENCY;
        //! \}

    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
