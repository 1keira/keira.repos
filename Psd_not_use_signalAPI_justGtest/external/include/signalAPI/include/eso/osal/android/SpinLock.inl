/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

// Android does not provide POSIX spinlocks.
// All calls fail with CommonError: NOT_SUPPORTED

#include <common/CommonError.hxx>

namespace osal
{

// the SpinLock is never valid because m_handle.isValid always returns false
// (see SpinLockDefs.hxx)
inline SpinLock::SpinLock() {}

inline SpinLock::~SpinLock() {}

inline bool SpinLock::lock() const
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "SpinLocks are not supported." );
    return true;
}

inline bool SpinLock::unlock() const
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "SpinLocks are not supported." );
    return true;
}

inline int_fast8_t SpinLock::tryLock() const
{
    ipl_raise( ipl::CommonError, ipl::NOT_SUPPORTED, "SpinLocks are not supported." );
    return true;
}

}
