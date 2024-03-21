#ifndef OSAL_ANDROID_SHMSPINLOCKDEFS_HXX
#define OSAL_ANDROID_SHMSPINLOCKDEFS_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

// there are no POSIX spinlocks on Android 

namespace osal
{

//! OS handle to reference a shared memory spinlock
struct OSAL_EXPORT ShmSpinLockHandle
{
    struct Data
    {
    };

    ShmSpinLockHandle()  { }

    bool isValid() const
    {
        return false;
    }

};

}

#endif // OSAL_ANDROID_SHMSPINLOCKDEFS_HXX
