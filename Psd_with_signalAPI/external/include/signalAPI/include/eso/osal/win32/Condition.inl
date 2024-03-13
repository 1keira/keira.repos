/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/
#ifndef OSAL_WIN32_CONDITION_INL
#define OSAL_WIN32_CONDITION_INL

namespace osal {

    inline Condition::Condition()
    {

        if( ! m_handle.isValid() )
        {
            osal_raise( SysError, UNKNOWN_ERROR );
            ipl_reraise( Condition::Error, CREATE_FAILED );
        }
    }



    inline Condition::~Condition()
    {
        if( m_handle.isValid() && m_handle.m_event.close() )
        {
            osal_raise( SysError, UNKNOWN_ERROR );
            IPL_WARN("error closing event");
            ipl_error.ack();
        }
    }

    inline bool Condition::wait(osal::Mutex &lock)
    {
        return m_handle.wait(lock, NULL) != WAIT_SIGNALED;
    }


    inline int_fast8_t Condition::waitTimeout(osal::Mutex& lock,
        const osal::AbsTimeT &end_time)
    {
        return m_handle.wait(lock, &end_time);
    }

    inline bool Condition::signal()
    {
        return m_handle.signal(false);
    }

    inline bool Condition::signalAll()
    {
        return m_handle.signal(true);
    }

} // end ns osal

#endif
