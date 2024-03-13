/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

namespace osal
{

inline bool ShmSpinLock::close()
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "ShmSpinLocks are not supported." );
    return true;
}

inline bool ShmSpinLock::attach(
    volatile void *shm_addr,
    const bool initialize,
    const bool auto_destroy)
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "ShmSpinLocks are not supported." );
    return true;
}

inline bool ShmSpinLock::destroy( volatile void *shm_addr )
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "ShmSpinLocks are not supported." );
    return true;
}
    
inline bool ShmSpinLock::lock() const
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "ShmSpinLocks are not supported." );
    return true;
}

inline bool ShmSpinLock::unlock() const
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "ShmSpinLocks are not supported." );
    return true;
}

inline int_fast8_t ShmSpinLock::tryLock() const
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "ShmSpinLocks are not supported." );
    return true;
}

}
