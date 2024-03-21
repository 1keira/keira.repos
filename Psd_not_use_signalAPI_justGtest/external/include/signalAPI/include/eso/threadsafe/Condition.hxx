/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_CONDITION_HXX
#define THREADSAFE_CONDITION_HXX
/*****************************************************************************/

#include <ipl_config.h>

// #include "threadsafe_dso.h"

#if defined(IPL_OS_POSIX)
#include "ConditionImpl-posix.hxx"
#elif defined(IPL_OS_WIN32)
#include "ConditionImpl-win32.hxx"
#elif defined(IPL_OS_INTEGRITY)
#include "ConditionImpl-integrity.hxx"
#else
#error Unsupported OS
#endif

#include "ConditionBase.hxx"
#include "Mutex.hxx"

#include <iplbase/time.hxx>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \brief Condition variable

        All the methods return NULL on success or a string describing
        the failure.
        You can compare the pointer you get against the
        \ref ipl_ConditionBase_error_constants "error constants" to assess
        the problem
        or just output the string to the user.

        The mutex supplied in the constructor must be locked before the call
        to wait/wait_timeout. It will be atomically released in the waiting time,
        and atomically aquired again before the return from wait.
        A possible usage example looks like follows:  

            bool ready = false;
            threadsafe::Mutex mutex;
            threadsafe::Condition condition(mutex);
 
            void waiting_thread() {
              threadsafe::Mutex::Guard guard(mutex);
              while(!ready) condition.wait();
            }
            
            int main() {
              std::thread worker(waiting_thread);
              {
                threadsafe::Mutex::Guard guard(mutex);
                ready = true;
              }

              condition.signal_one();
              worker.join();
            }
            

        \link2req{satisfies,req~FW_THREADSAFE_CONDITION~1}
    */
    class /* THREADSAFE_EXPORT not allowed, inline-only */ Condition: public ConditionBase {

    public:

        Condition(Mutex &mutex) IPL_NOEXCEPT: mutex(mutex), impl(mutex.impl) {}

        const char *wait() IPL_NOEXCEPT         { return impl.wait();         }
        const char *wait_timeout(const iplbase::TimePoint &end_time) IPL_NOEXCEPT {
            return impl.wait_timeout(end_time);
        }
        const char *signal_one() IPL_NOEXCEPT   { return impl.signal_one();   }
        const char *signal_all() IPL_NOEXCEPT   { return impl.signal_all();   }

        Mutex &mutex;  //!< \brief public so you can be nasty with it

    protected:
        ConditionImpl impl;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
