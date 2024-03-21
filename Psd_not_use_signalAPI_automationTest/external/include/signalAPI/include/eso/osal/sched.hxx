/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SCHED_HXX
#define OSAL_SCHED_HXX

#include <ipl_config.h>
#include <osal/osal_dso.h>
#include <common/inttypes.h>
#include <common/streams/iostream.hxx>

#if defined (IPL_OS_WINPC) || defined (IPL_OS_WIN32)
#include <iplbase/win32.h>    // thread priority-, priority class constants
#endif

namespace osal {
    class Thread;


    namespace sched {

        /**
         *\brief
         *    An enum to express the scheduling policy or priority class.
         *\details
         * The scheduling policy is some classification of the scheduling algorithm.
         * <br>A specific scheduling policy may have one or more parameters configuring the algorithm.
         * Some policies have no parameters though and some OSes don't make the scheduling policy
         * subject to change vi API or don't have more than one (e.g. Integrity).
         * <br>Windows uses the concept of priority class for processes and priority for threads.
         *\note The priority class on Windows is a property of the process, not the thread.
         **/
        enum Policy_E {
            OSAL_SCHED_NOOP                    /// Don't apply scheduling policy and parameters.
            ,OSAL_SCHED_POLICY_KEEP            /** When creating a thread/process: inherit policy from caller,
                                             * when setting parameters: keep policy, apply parameters.
                                             */
            ,OSAL_SCHED_POLICY_RR            /// POSIX/Linux/QNX: round robin realtime policy
            ,OSAL_SCHED_POLICY_FIFO            /// POSIX/Linux/Qnx: fifo reatltime policy
            ,OSAL_SCHED_POLICY_NORMAL        /** Linux: default time sharing scheduler (CFS),
                                             *  QNX: the round robin policy.
                                             */
            ,OSAL_SCHED_POLICY_OTHER        /** To keep with the POSIX-like naming OTHER is
                                             *  the same as NORMAL
                                             */
                                    = OSAL_SCHED_POLICY_NORMAL
            // windows prio class values start with 0x20 so their values fit in here
#if defined (IPL_OS_WINPC) || defined (IPL_OS_WIN32)
            /// Windows: idle priority class
            ,OSAL_SCHED_CLASS_IDLE          = IDLE_PRIORITY_CLASS
            /// Windows: below normal priority class
            ,OSAL_SCHED_CLASS_BELOW_NORMAL    = BELOW_NORMAL_PRIORITY_CLASS
            /// Windows: normal priority class
            ,OSAL_SCHED_CLASS_NORMAL        = NORMAL_PRIORITY_CLASS
            /// Windows: above normal priority class
            ,OSAL_SCHED_CLASS_ABOVE_NORMAL    = ABOVE_NORMAL_PRIORITY_CLASS
            /// Windows: high priority class
            ,OSAL_SCHED_CLASS_HIGH            = HIGH_PRIORITY_CLASS
            /// Windows: realtime priority class
            ,OSAL_SCHED_CLASS_REALTIME        = REALTIME_PRIORITY_CLASS
#else
            ,OSAL_SCHED_CLASS_IDLE            /// Windows: idle priority class
            ,OSAL_SCHED_CLASS_BELOW_NORMAL    /// Windows: below normal priority class
            ,OSAL_SCHED_CLASS_NORMAL        /// Windows: normal priority class
            ,OSAL_SCHED_CLASS_ABOVE_NORMAL    /// Windows: above normal priority class
            ,OSAL_SCHED_CLASS_HIGH            /// Windows: high priority class
            ,OSAL_SCHED_CLASS_REALTIME        /// Windows: realtime priority class
#endif
        };

        /// Operator to insert an osal::sched::Policy_E value into an ostream.
        OSAL_EXPORT ipl::ostream& operator<<(ipl::ostream& stream, osal::sched::Policy_E p);

        /**
         *\brief
         *    Wraps Policy_E in a struct.
         *\details
         * Default constructs with OSAL_SCHED_NOOP.
         **/
        struct Policy {
            Policy() : value(OSAL_SCHED_NOOP) {}
            Policy(Policy_E policy) : value(policy) {}

            operator Policy_E() const { return value; }

            bool operator==(osal::sched::Policy rhs) const {
                return value == rhs.value;
            }

            bool  operator!=(osal::sched::Policy rhs) const {
                return !operator==(rhs);
            }

            bool operator==(osal::sched::Policy_E rhs) const {
                return value == rhs;
            }

            bool  operator!=(osal::sched::Policy_E rhs) const {
                return !operator==(rhs);
            }

            Policy& operator=(osal::sched::Policy_E rhs) {
                value=rhs;
                return *this;
            }

            bool undefined() const  { return value == OSAL_SCHED_NOOP; }
            bool keep() const       { return value == OSAL_SCHED_POLICY_KEEP; }
            Policy_E value;
        };


        inline ipl::ostream& operator<<(ipl::ostream& stream, osal::sched::Policy p) {
            stream<<p.value;
            return stream;
        }

        /**
         *\brief
         *    An enum to express the windows thread priority.
         *\note refer to Windows documentation for the meaning of these values.
         **/
        // Windows Thread Priorities: enumerable not integral
#if defined (IPL_OS_WINPC) || defined (IPL_OS_WIN32)
        enum WinThreadPrio {
            OSAL_WIN_THREAD_PRIO_IDLE           = THREAD_PRIORITY_IDLE
            ,OSAL_WIN_THREAD_PRIO_LOWEST        = THREAD_PRIORITY_LOWEST
            ,OSAL_WIN_THREAD_PRIO_BELOW_NORMAL  = THREAD_PRIORITY_BELOW_NORMAL
            ,OSAL_WIN_THREAD_PRIO_NORMAL        = THREAD_PRIORITY_NORMAL
            ,OSAL_WIN_THREAD_PRIO_ABOVE_NORMAL  = THREAD_PRIORITY_ABOVE_NORMAL
            ,OSAL_WIN_THREAD_PRIO_HIGHEST       = THREAD_PRIORITY_HIGHEST
            ,OSAL_WIN_THREAD_PRIO_TIME_CRITICAL = THREAD_PRIORITY_TIME_CRITICAL
        };
#else
        enum WinThreadPrio {
            OSAL_WIN_THREAD_PRIO_IDLE           /// idle thread priority
            ,OSAL_WIN_THREAD_PRIO_LOWEST        /// lowest thread priority
            ,OSAL_WIN_THREAD_PRIO_BELOW_NORMAL  /// below normal thread priority
            ,OSAL_WIN_THREAD_PRIO_NORMAL        /// normal thread priority
            ,OSAL_WIN_THREAD_PRIO_ABOVE_NORMAL  /// above normal thread priority
            ,OSAL_WIN_THREAD_PRIO_HIGHEST       /// highest normal thread priority
            ,OSAL_WIN_THREAD_PRIO_TIME_CRITICAL /// time critical normal thread priority
        };
#endif

        /// Operator to insert an osal::sched::WinThreadPrio value into an ostream.
        OSAL_EXPORT ipl::ostream& operator<<(ipl::ostream& stream, osal::sched::WinThreadPrio p);

        /* Osal access to scheduling parameters.
         * This usually involves some classification of the scheduling algorithm -
         * the scheduling policy and a set of parameters configuring the algorithm.
         * Some policies have no parameters, some OSes don't make the scheduling policy
         * subject to cahnge vi API (e.g. Integrity)
         * Windows uses the concept of priority class for processes and priority for threads.
         */


        // Types for all kinds of scheduling parameters

        /**
         *\brief
         *    Holds a nice value e.g. for the osal::sched::OSAL_SCHED_POLICY_NORMAL scheduling policy on Linux.
         *\details
         * The default value is 0.
         **/
        struct OSAL_EXPORT Nice {
            Nice():value() {}
            Nice(int v): value(v) {}
            int value;

            operator int() const {
                return value;
            }
        };


        /**
         *\brief
         *    Holds a priority value.
         *\details
         * On POSIX and Integrity the value type is an unsigned integer.
         * <br>On Windows the value type is the enum WinThreadPrio.
         * <br>The scheduling policies osal::sched::OSAL_SCHED_POLICY_RR and osal::sched::OSAL_SCHED_POLICY_FIFO
         * use this on POSIX/Linux/QNX.
         * <br>On QNX the scheduling policy osal::sched::OSAL_SCHED_POLICY_NORMAL also uses this.
         * <br>Integrity uses this.
         * <br>Windows uses this for a thread's priority.
         * <br>On POSIX and Integrity The default value is 0.
         * <br>On Windows the default value is osal::sched::OSAL_WIN_THREAD_PRIO_NORMAL.
         **/
        /**
         *\brief
         *    Holds a thread priority used on Windows.
         *\details
         * The default value is soal::OSAL_WIN_THREAD_PRIO_NORMAL.
         **/
        struct OSAL_EXPORT Prio {
#if defined (IPL_OS_WINPC) || defined (IPL_OS_WIN32)
            typedef WinThreadPrio value_type;   ///< value type
#else
            typedef unsigned value_type;        ///< value type
#endif
            Prio()
#if defined (IPL_OS_WINPC) || defined (IPL_OS_WIN32)
            : value(OSAL_WIN_THREAD_PRIO_NORMAL)
#else
            : value(0)
#endif
            {}

            Prio(WinThreadPrio v)
#if defined (IPL_OS_WINPC) || defined (IPL_OS_WIN32)
            : value(v)
#else
            // on non-windows initializing with a Windows-specific value, results in
            // the safe default
            : value(0)
#endif
            {}

            Prio(unsigned v)
#if defined (IPL_OS_WINPC) || defined (IPL_OS_WIN32)
            // on windows initializing with a non Windows-specific value, results in
            // the safe default
            : value(OSAL_WIN_THREAD_PRIO_NORMAL)
#else
            : value(v)
#endif
            {}

            value_type value;

            operator value_type() const {
                return value;
            }
        };

        /**
         *\brief
         *    Holds an integral weight value used together with an integral priority value on Integrity.
         *\details
         * The default value is 0.
         **/
        struct OSAL_EXPORT Weight {
            Weight():value() {}
            Weight(unsigned v): value(v) {}
            unsigned value;

            operator unsigned() const {
                return value;
            }
        };


        /**
         *\brief
         *    Holds generic scheduling parameters.
         **/
        struct OSAL_EXPORT Param {
                Param() = default;
                Param(Prio p)              : priority(p) {}
                Param(Nice n)              : nice(n) {}
                Param(Weight w, Prio p)    : priority(p), weight(w) {}
                Param(WinThreadPrio wp)    : priority(wp) {}
                /**
                 * \brief Constructor from policy and an integer value (e.g. from configuration).
                 * \details
                 *  The integer value is interpreted based on policy.
                 *  <br>For most policies it is not ambiguous what a single integer parameter
                 *  means, but e.g. on Linux it might be a priority or a nice value. The policy is
                 *  used to initialize the correct member.
                 */
                Param(Policy p, int value);

                // once the extension-member ext and version get used these need to be updated.
                Param(const Param&) = default;
                Param& operator=(const Param&) = default;
                Param(Param&&) = default;
                Param& operator=(Param&&) = default;

            private:
                friend class Thread;
            public:
                uint8_t     version{0u};        // for future extensions
                intptr_t    ext{0};             // for future extensions
                Prio        priority;           ///< priority, applies to windows, to FIFO, RR on POSIX, Integrity
                Nice        nice;               ///< nice value, applies to linux NORMAL
                Weight      weight;             ///< weight, applies to Integrity (with priority)

                bool operator==(const osal::sched::Param& rhs) const {
                    return (
                            (priority.value == rhs.priority.value)
                            && (nice.value == rhs.nice.value)
                            && (weight.value == rhs.weight.value)
                           );
                }

                bool operator!=(const osal::sched::Param& rhs) const {
                    return !operator==(rhs);
                }

        };

        /// Operator to insert an osal::sched::Param value into an ostream.
        OSAL_EXPORT ipl::ostream& operator<<(ipl::ostream& stream, const osal::sched::Param& p);


        /// \brief Scheduling attributes. They consist of policy and its parameters.
        struct Attr {
            Attr()
            {
            }

            Attr(Policy_E policy, const Param& param)
            : policy(policy)
            , param(param)
            {
            }

            Attr(Policy policy, const Param& param)
            : policy(policy)
            , param(param)
            {
            }

            Attr(Policy policy, int value)
            : policy(policy)
            , param(policy, value)
            {
            }

            bool operator==(const osal::sched::Attr& rhs) const {
                return (policy == rhs.policy) && (param == rhs.param);
            }

            bool operator!=(const osal::sched::Attr& rhs) const {
                return !operator==(rhs);
            }

            Policy  policy;
            Param   param;
        };


        inline ipl::ostream& operator<<(ipl::ostream& stream, const osal::sched::Attr& a) {
            stream << a.policy<<", "<<a.param;
            return stream;
        }
    }

}
#endif // OSAL_SCHED_HXX
