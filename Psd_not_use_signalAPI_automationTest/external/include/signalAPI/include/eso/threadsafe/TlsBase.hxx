/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_TLSBASE_HXX
#define THREADSAFE_TLSBASE_HXX
/*****************************************************************************/

#include "threadsafe_dso.h"
#include <iplbase/NonCopyable.hxx>

/*****************************************************************************/

#ifndef DISABLE_THREADSAFE_UNDEFS_I_ACCEPT_THE_CONSEQUENCES

#ifdef ERROR
#ifdef _MSC_VER
#pragma message(__FILE__)
#pragma message("#undef-ing ERROR to avoid name collision")
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
        \brief Common stuff for all Tls/TlsImpl variants
    */
    class THREADSAFE_EXPORT TlsBase: public iplbase::NonCopyable {

    public:
        //! \name ipl_TlsBase_error_constants "Error constants"
        //! \{
        //! \brief Indication for "something went wrong, no details"
        static const char *const ERROR;
        //! \brief Indication for "out of memory"
        static const char *const ERROR_OUT_OF_MEMORY;
        //! \}

    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
