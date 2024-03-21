/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef IPLBASE_EXIT_HXX
#define IPLBASE_EXIT_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <stdlib.h>

#if defined (IPL_OS_ANDROID)
// _exit on android r12b-arm-api19-libc++ toolchain
#include <unistd.h>
#endif
/*****************************************************************************/

namespace iplbase {

/*****************************************************************************/

    //! \brief End process without any cleanup – the preferred way to end a framework process
    //!
    // Note: This should remain all-inline, so it can be used without linking
    // against libiplbase (CxxTest needs this, for example).
    inline void exit(int result)
    {
#if defined HAVE_QUICK_EXIT
        quick_exit(result);
#elif defined IPL_OS_ANDROID || defined IPL_OS_WINPC
        _exit(result);
#elif defined HAVE_STD__EXIT
        std::_Exit(result);
#else
        _Exit(result);
#endif
    }
    
/*****************************************************************************/

}  // end of namespace iplbase

/*****************************************************************************/
#endif
