#ifndef OSAL_WIN32_SHMSPINLOCKDEFS_HXX
#define OSAL_WIN32_SHMSPINLOCKDEFS_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <osal/ShmMutex.hxx>

namespace osal
{

/*
 * we simply re-use the ShmMutex for now.
 *
 * We could introduce some spinning at a later time by putting an atomic
 * counter into the SHM and do the spinning ourselves.
 */
struct ShmSpinLockHandle
{
    typedef osal::ShmMutex::Data Data;
    osal::ShmMutex mutex;

    bool isValid()
    {
        return mutex.isValid();
    }

    ShmSpinLockHandle() :
        mutex()
    { }

    bool setup(volatile void *addr,
        const bool init,
        const bool auto_dest)
    {
        return mutex.attach((void*)addr,
            init,
            auto_dest,
            osal::ShmMutex::BINARY,
            false);
    }
};

} // end ns osal

#endif
