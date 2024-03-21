/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SYSTEMERROR_HXX
#define OSAL_SYSTEMERROR_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>

//#if defined (IPL_OS_ANDROID) || defined (IPL_OS_LINUX) || defined (IPL_OS_QNX)
#if (defined IPL_OS_POSIX) || (defined IPL_OS_INTEGRITY)
#    include "posix/SystemErrorDefs.hxx"
#elif defined (IPL_OS_WINPC)
#    include "win32/SystemErrorDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal_dso.h>

namespace osal
{

/**
 \brief
    a class that allows access to system specific error codes
**/
class OSAL_EXPORT SystemError
{
public:
    /**
     * \brief
     *    Retrieves the currently set system error produces by the
     *    last system call and stores it in m_error.
    **/
    SystemError();

    /**
     * \brief
     *     Uses the given parameter \c err as error code
     **/
    SystemError(SystemErrorType err)
    {
        m_error = err;
    }

    /**
     *     \brief
     *         print the system error in a formated way
    **/
    ipl::string getString() const;
protected:
    SystemErrorType m_error; ///< system specific error code
};

} // end namespace

#endif // OSAL_SYSTEMERROR_HXX
