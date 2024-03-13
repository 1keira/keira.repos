/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal {

    inline Mutex::~Mutex()
    {
        if( isValid() )
        {
            // there is no return value of any kind here. Either it
            // works or you are doomed.
            DeleteCriticalSection( &m_handle.handle );
        }
    }

    inline Mutex::Mutex(const MutexType p_mutex_type, bool p_prio_inherit)
    {
        (void)p_prio_inherit;
        m_handle.type = p_mutex_type;
#ifdef OSAL_USE_WIN32_EXCEPTIONS
        // can't use that: cannot use _try in functions requiring object
        // unwinding.
        __try
        {
#endif
            m_handle.counter = AtomicCounter(0);

            // may raise STATUS_NO_MEMORY
            // (according to MSDN more recent versions of at least
            // WinXP and successors it is guaranteed that no
            // additional memory is needed here)
            InitializeCriticalSection( &m_handle.handle );
#ifdef OSAL_USE_WIN32_EXCEPTIONS
        }
        __except(STATUS_NO_MEMORY == GetExceptionCode())
        {
            osal_raise( SysError, OUT_OF_MEMORY );
            return;
        }
#endif
    }

    inline bool Mutex::lock() const
    {
        // don't do anything here, this might cause a race condition may
        // throw
        EnterCriticalSection( &m_handle.handle );

        // this is thrown after a global timeout configured by means of
        // a registry key in Windows (doesn_t compile. ask Bill).
        // --> EXCEPTION_POSSIBLE_DEADLOCK
        // it seems MSDN wants us not to handle that exception but
        // instead let the application crash. Well it desktop software
        // after all...

        // we now own the mutex one more time

        // now that we got the mutex we may check if we (this thread)
        // got the mutex more than once already
        if( (m_handle.counter++ != 0) && m_handle.type == BINARY)
        {
            // undo the unwanted locking procedure above (this is
            // always an incremental lock so we can do that). This
            // ensures some error consistency. Not very beautiful
            // though but what can we do...
            this->unlock();

            osal_try_reraise( Mutex::Error, INCONSISTENCY );

            return true;
        }

        return false;
    }

    inline bool Mutex::unlock() const
    {
        // some debugging support
        if( m_handle.counter-- < 1 )
        {
            // if this thread wants to unlock this mutex then there
            // MUST have been a count higher than zero no matter
            // what.
            m_handle.counter++;

            ipl_raise( Mutex::Error, INCONSISTENCY,
                "mutex is not owned by this thread");
            return true;
        }

        // do the job
        LeaveCriticalSection( &m_handle.handle );

        return false;
    }


    inline int_fast8_t Mutex::tryLock() const
    {
        // tryEnter doesn't seem to throw the exception that Enter does.
        // Maybe this is reflected by a negative return value in this
        // case. MSDN doesn't say much about this.
        //
        // attention: don't just set the new owner! might be we didn't
        // get the mutex!
        if( TryEnterCriticalSection( &m_handle.handle ) )
        {
            // now that we got the mutex we may check if we (this
            // thread) got the mutex more than once already
            if((m_handle.counter++ != 0) && m_handle.type == BINARY)
            {
                // undo the unwanted locking procedure above
                // (this is always an incremental lock so we can
                // do that). This ensures some exception safety.
                // Not very beautiful though but what can be
                // do...
                if ( unlock() ) {
                    // return error if undoig the lock failed 
                    return TRY_LOCK_ERROR;
                }
                // we tried to re-lock a binary mutex: return NOLUCK
                return TRY_LOCK_NOLUCK;

            }
            return TRY_LOCK_SUCCESS;
        }
        return TRY_LOCK_NOLUCK;
    }

} // end ns osal
