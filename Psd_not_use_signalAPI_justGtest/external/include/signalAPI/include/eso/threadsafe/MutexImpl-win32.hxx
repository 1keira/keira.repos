/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_MUTEXIMPL_WIN32_HXX
#define THREADSAFE_MUTEXIMPL_WIN32_HXX

#ifndef IPL_OS_WIN32
#error Only valid on Win32
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"
#include <iplbase/time.hxx>
#include <iplbase/win32.h>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Win32 implementation of Mutex functionality
    */
    class THREADSAFE_EXPORT MutexImpl {

    public:
        MutexImpl(bool recursive) IPL_NOEXCEPT;
        ~MutexImpl() IPL_NOEXCEPT;

        const char *lock() IPL_NOEXCEPT;
        const char *unlock() IPL_NOEXCEPT;
        const char *try_lock() IPL_NOEXCEPT;
        const char *try_lock(const iplbase::Duration &timeout) IPL_NOEXCEPT;

        //! \see http://blogs.msdn.com/b/oldnewthing/archive/2004/02/23/78395.aspx
        static const DWORD NO_THREAD=0;

    protected:
        bool recursive;
        CRITICAL_SECTION handle;
        unsigned count;
        DWORD owner;
        friend class ConditionImpl;  // may access handle & owner
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
