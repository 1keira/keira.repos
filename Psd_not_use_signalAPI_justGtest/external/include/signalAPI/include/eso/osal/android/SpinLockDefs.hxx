#ifndef OSAL_ANDROID_SPINLOCKDEFS_HXX
#define OSAL_ANDROID_SPINLOCKDEFS_HXX

// Android does not provide POSIX spinlocks
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

#endif // OSAL_ANDROID_SPINLOCKDEFS_HXX
