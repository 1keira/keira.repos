#ifndef PERFDAT_TIME_BITS_HXX
#define PERFDAT_TIME_BITS_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

#include <ipl_config.h>
#include <common/stdint.h>
#include <time.h>

#if defined IPL_OS_INTEGRITY
#include <INTEGRITY.h>
#ifdef MAX  // yeah, Integrity OS sucks just like Windows
#undef MAX
#endif
#endif

namespace perfdat {

#if defined IPL_OS_LINUX
    // internal time stamp is a struct timespec

    static inline uint64_t timestamp2ns(const struct timespec& ts) {
        return ((uint64_t)1000000000*ts.tv_sec+(uint64_t)ts.tv_nsec);
    }

    struct Timestamp_value : public timespec {
        Timestamp_value() {
            tv_sec = 0;
            tv_nsec = 0;
        }

        int64_t operator - (const Timestamp_value& other) const {
            return timestamp2ns(*this) - timestamp2ns(other);
        }
    };
#elif defined IPL_OS_QNX

    // internal time stamp is a unit64_t (as returned by ClockCucles)

    struct Timestamp_value {
        uint64_t    cycles;
        Timestamp_value() : cycles(0) {}

        int64_t operator - (const Timestamp_value& other) const {
            return cycles - other.cycles;
        }
    };

#elif defined IPL_OS_INTEGRITY

        class Timestamp_value: public Time {
            
        public:
            Timestamp_value() {
                Seconds=0;
                Fraction=0;
            }
            
            int64_t operator - (const Timestamp_value& other) const {
                return (((int64_t)Seconds)<<32)+(int64_t)Fraction-
                       (((int64_t)other.Seconds)<<32)-(int64_t)other.Fraction;
            }
        };
#else 
    // TODO
    struct Timestamp_value {
        int64_t operator - (const Timestamp_value& other) const {
            return 0;
        }
    };
#endif

}

#endif // PERFDAT_TIME_BITS_HXX
