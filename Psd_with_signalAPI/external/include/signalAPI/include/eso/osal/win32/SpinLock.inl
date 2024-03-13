/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_SPINLOCK_COUNT
// don't know what a good value for this is
#define OSAL_WIN32_SPINLOCK_COUNT 32
#endif

namespace osal {
    
    inline SpinLock::SpinLock()
    {
#ifndef IPL_OS_WINCE
        InitializeCriticalSectionAndSpinCount( &m_handle.handle,
            OSAL_WIN32_SPINLOCK_COUNT );
#else
        // spin count not present on CE
        InitializeCriticalSection( &m_handle.handle );
#endif
    }

    inline SpinLock::~SpinLock()
    {
        if( isValid() )
        {
            // there is no return value of any kind here. Either it
            // works or you are doomed.
            DeleteCriticalSection( &m_handle.handle );
        }
    }

    inline bool SpinLock::lock() const
    {
        EnterCriticalSection( &m_handle.handle );

        return false;
    }

    inline bool SpinLock::unlock() const
    {
        LeaveCriticalSection( &m_handle.handle );

        return false;
    }

    inline int_fast8_t SpinLock::tryLock() const
    {
        if( TryEnterCriticalSection( &m_handle.handle ) )
        {
            return TRY_LOCK_SUCCESS;
        }

        return TRY_LOCK_NOLUCK;
    }

} // end ns osal
