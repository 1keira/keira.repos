/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_ATOMICBOOL_HXX
#define COMM_ATOMICBOOL_HXX

#include <ipl_config.h>
#ifdef HAVE_STD_ATOMIC_BOOL
#include <atomic>
#else
#include <osal/AtomicCounter.hxx>
#endif

/**
 * Implements a bool that can be tested and set safely from different threads
 */
namespace comm {
#ifdef HAVE_STD_ATOMIC_BOOL
    class AtomicBool {
        public:
            explicit AtomicBool(bool initial=false)
            : m_flag(initial)
            {
            }

            ~AtomicBool() {}

            bool set() {
                return m_flag.exchange(true);
            }

            bool reset() {
                return m_flag.exchange(false);
            };

            bool isSet() const {
                return m_flag.load();
            }

        private:
            std::atomic<bool>   m_flag;
    };
#else
    class AtomicBool {
        public:
            AtomicBool(bool initial=false)
            : m_flag(initial?1:0)
            {
            }

            ~AtomicBool() {}

            bool set() {
                return m_flag.exchange(1);
            }

            bool reset() {
                return m_flag.exchange(0);
            };

            bool isSet() const {
                return m_flag.getCurrentCount() != 0;
            }

        private:
            osal::AtomicCounter m_flag;
    };
#endif
}



#endif // COMM_ATOMICBOOL_HXX

