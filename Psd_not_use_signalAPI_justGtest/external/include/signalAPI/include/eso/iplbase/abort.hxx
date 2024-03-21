/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef IPLBASE_ABORT_HXX
#define IPLBASE_ABORT_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include "iplbase_dso.h"

#if defined(IPL_OS_QNX)
#include "abort-qnx.hxx"
#elif defined(IPL_OS_POSIX) || defined (IPL_OS_INTEGRITY)
#include "abort-posix.hxx"
#elif defined(IPL_OS_WIN32)
#include "abort-win32.hxx"
#else
#error Unsupported OS
#endif

/*****************************************************************************/

namespace iplbase {

/*****************************************************************************/

    //! \brief Output a code position and a complaint and
    //! (try to) abort execution
    IPLBASE_EXPORT void abort(const char *file, int line, const char *function,
                              const char *fmt, ...);

/*****************************************************************************/

}  // end of namespace iplbase

/*****************************************************************************/
#endif
