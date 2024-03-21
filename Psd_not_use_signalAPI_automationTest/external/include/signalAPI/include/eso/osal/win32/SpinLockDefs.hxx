#ifndef OSAL_WIN32_SPINLOCKDEFS_HXX
#define OSAL_WIN32_SPINLOCKDEFS_HXX

#include <iplbase/win32.h>

namespace osal
{

//! datatype definition for thread internal mutex references
struct OSAL_EXPORT SpinLockHandle
{
    CRITICAL_SECTION handle;

    static SpinLockHandle s_invalid_handle;

    SpinLockHandle(const bool invalidate = false)
    {
        if( invalidate )
        {
            this->invalidate();
        }
    }

    bool isValid() const
    {
        /*
         * to save a field for validity we invalidate the
         * critical section via writing zeroes all over it
         */

        return ::memcmp( &handle, &s_invalid_handle.handle,
            sizeof(CRITICAL_SECTION) ) != 0;
    }
    
    void invalidate()
    {
        ::memset( &handle, 0xFF, sizeof(CRITICAL_SECTION) );
    }
};

} // end ns osal

#endif
