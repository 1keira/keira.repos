#ifndef OSAL_INTEGRITY_SPINLOCKDEFS_HXX
#define OSAL_INTEGRITY_SPINLOCKDEFS_HXX

// Integrity does not provide POSIX spinlocks
// TODO could be emulated?

namespace osal
{

//! provide a handle to the public header
struct OSAL_EXPORT SpinLockHandle
{
    SpinLockHandle() { }

    bool isValid() const
    {
        return false;
    }
};

}

#endif // OSAL_Integrity_SPINLOCKDEFS_HXX
