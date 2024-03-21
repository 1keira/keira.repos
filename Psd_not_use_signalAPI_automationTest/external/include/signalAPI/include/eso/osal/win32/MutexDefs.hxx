#ifndef OSAL_WIN32_MUTEXDEFS_HXX
#define OSAL_WIN32_MUTEXDEFS_HXX

#include <iplbase/win32.h>
#include <osal/AtomicCounter.hxx>

namespace osal
{

//! datatype definition for thread internal mutex references
struct OSAL_EXPORT MutexHandle
{
    CRITICAL_SECTION handle;
    // AtomicCounter to detect problems regarding non-recursive mutexes
    AtomicCounter counter;

    int type;

    static MutexHandle s_invalid_handle;

    MutexHandle(const bool invalidate = false)
    {
        if(invalidate)
        {
            this->invalidate();
        }
    }

    bool isValid() const
    {
        /*
         * to save a field for validity we invalidate the
         * critical section via writing stuff all over it
         */
        return ::memcmp( &handle, &s_invalid_handle.handle,
            sizeof(CRITICAL_SECTION) ) != 0;
    }
    
    void invalidate()
    {
        ::memset( &handle, 0xFF, sizeof(CRITICAL_SECTION) );
        counter = AtomicCounter(0);
    }
};

} // end ns osal

#endif // inc. guard
