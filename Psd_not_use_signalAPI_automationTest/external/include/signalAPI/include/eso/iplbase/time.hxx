/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef IPLBASE_TIME_HXX
#define IPLBASE_TIME_HXX
/*****************************************************************************/
/*!
    \file
    \brief Types needed for specifying timeouts
*/
/*****************************************************************************/

#include <ipl_config.h>

#include "type_traits.hxx"
#include "iplbase_dso.h"

#include <limits>

/*****************************************************************************/

namespace iplbase {

/*****************************************************************************/

#define IPLBASE_TIME_TPS 1000

/*****************************************************************************/

    /*!
        \internal
        \brief Some kind of time, expressed as a number of ticks of some size

    */
    template <typename T, T TPS>
    class /* IPLBASE_EXPORT nope, inline-only */  NumberOfTicks {

    public:

        typedef T Ticks;

        NumberOfTicks(Ticks ticks, Ticks ticks_per_second) IPL_NOEXCEPT:
            m_ticks(convert_ticks(ticks, ticks_per_second, TICKS_PER_SECOND)) {}

        //! \brief Set duration in \e your tick size
        void set(Ticks ticks, Ticks ticks_per_second) IPL_NOEXCEPT {
            m_ticks=convert_ticks(ticks, ticks_per_second, TICKS_PER_SECOND);
        }
        //! \brief Convenience: Set duration in milliseconds
        void set_ms(Ticks ms) IPL_NOEXCEPT { set(ms, 1000); }

        //! \brief Express duration in \e your tick size
        Ticks ticks(Ticks ticks_per_second) const IPL_NOEXCEPT {
            return convert_ticks(m_ticks, TICKS_PER_SECOND, ticks_per_second);
        }
        //! \brief Convenience: Express duration in milliseconds
        Ticks ms() const IPL_NOEXCEPT { return ticks(1000); }

        //! \brief Convenience: Express duration in microseconds
        Ticks us() const IPL_NOEXCEPT { return ticks(1000000); }

        //! \brief Convenience: Express duration in nanoseconds
        Ticks ns() const IPL_NOEXCEPT { return ticks(1000000000); }

        bool operator == (const NumberOfTicks<T, TPS> &other) const IPL_NOEXCEPT {
            return m_ticks==other.m_ticks;
        }
        bool operator != (const NumberOfTicks<T, TPS> &other) const IPL_NOEXCEPT {
            return m_ticks!=other.m_ticks;
        }
        bool operator < (const NumberOfTicks<T, TPS> &other) const IPL_NOEXCEPT {
            return m_ticks<other.m_ticks;
        }
        bool operator > (const NumberOfTicks<T, TPS> &other) const IPL_NOEXCEPT {
            return m_ticks>other.m_ticks;
        }
        bool operator <= (const NumberOfTicks<T, TPS> &other) const IPL_NOEXCEPT {
            return m_ticks<=other.m_ticks;
        }
        bool operator >= (const NumberOfTicks<T, TPS> &other) const IPL_NOEXCEPT {
            return m_ticks>=other.m_ticks;
        }

    private:

        //! \internal
        struct ConvertSigned {
            static Ticks convert_ticks(Ticks ticks, Ticks from, Ticks to) IPL_NOEXCEPT
            {
                Ticks t=ticks*to;
                Ticks q=t/from;
                Ticks r=t%from;
                if(r*2>from)
                    q++;
                else if(r*2<-from)  // r's sign is implementation defined if t<0
                    q--;
                return q;
            }
        };

        //! \internal
        struct ConvertUnsigned {
            static Ticks convert_ticks(Ticks ticks, Ticks from, Ticks to) IPL_NOEXCEPT
            {
                Ticks t=ticks*to;
                Ticks q=t/from;
                Ticks r=t%from;
                if(r*2>from)
                    q++;
                return q;
            }
        };

    protected:
        //! Convert a time expressed as number of ticks
        //! to a different tick size
        static Ticks convert_ticks(Ticks ticks, Ticks from, Ticks to) IPL_NOEXCEPT {
            return conditional<is_signed<Ticks>::value,
                               ConvertSigned, ConvertUnsigned
                              >::type::convert_ticks(ticks, from, to);
        }

        static const Ticks TICKS_PER_SECOND=TPS;

        Ticks m_ticks;
    };

/*****************************************************************************/

    /*!
        \brief An amount of time, represented in an opaque way

        Internally this is some integer number of ticks.
        You can read/write it in terms of your own ticks,
        but internal calculation might be inaccurate to the internal ticks.

        Note: stdint.h is not available below layer "common",
        therefore we use longlong types.

    */
    class IPLBASE_EXPORT Duration:
        public NumberOfTicks<long long, IPLBASE_TIME_TPS /* must be the same
                                                         as TimePoint's */ > {

        typedef NumberOfTicks<long long, IPLBASE_TIME_TPS> Parent;

    public:
        //! \brief A duration of zero
        Duration() IPL_NOEXCEPT: Parent(0, 1) {}
        //! \brief An explicit duration, \a ticks_per_second defaults to 1000
        explicit Duration(Ticks ticks, Ticks ticks_per_second=1000) IPL_NOEXCEPT:
            Parent(ticks, ticks_per_second) {}

        using Parent::ms;
        //! \brief Create a duration of \a milliseconds milliseconds
        static Duration ms(Ticks milliseconds) IPL_NOEXCEPT {
            return Duration(milliseconds, 1000);
        }

        friend class TimePoint;  // for optimized access

        Duration operator + (const Duration &other) const IPL_NOEXCEPT {
            return Duration(m_ticks+other.m_ticks, TICKS_PER_SECOND);
        }
        Duration operator - (const Duration &other) const IPL_NOEXCEPT {
            return Duration((Duration::Ticks)m_ticks-(Duration::Ticks)other.m_ticks,
                            TICKS_PER_SECOND);
        }
        Duration operator - () const IPL_NOEXCEPT {
            return Duration(-m_ticks, TICKS_PER_SECOND);
        }

        //! \brief Maximum Duration possible
        static const Duration MAX;
    };

/*****************************************************************************/

    /*!
        \brief A point in time, represented in an opaque way

        Internally this is some integer number of ticks since some epoch.
        You can create it in terms of your own ticks,
        but calculation might be inaccurate to the internal ticks.

        Note: stdint.h is not available below layer "common",
        therefore we use longlong types.

    */
    class IPLBASE_EXPORT TimePoint:
        public NumberOfTicks<unsigned long long, IPLBASE_TIME_TPS /* must be the same
                                                                  as Duration's */ > {

        typedef NumberOfTicks<unsigned long long, IPLBASE_TIME_TPS> Parent;
        //! \internal
        //! \brief Tag for special constructor
        struct SetTicks {};
        //! \internal
        //! \brief Tag for special constructor
        static const SetTicks SET_TICKS;

    public:
        //! \brief The time point right now
        TimePoint() IPL_NOEXCEPT: Parent(now(), IPLBASE_TIME_TPS) {}
        //! \brief The time point \a plus in the future
        explicit TimePoint(const Duration &plus) IPL_NOEXCEPT:
            Parent(now(), IPLBASE_TIME_TPS) {
            operator += (plus);
        }
        //! \brief The time point \a plus_ticks in the future,
        //! \a ticks_per_second defaults to 1000
        explicit TimePoint(Duration::Ticks plus_ticks,
                           Ticks ticks_per_second=1000) IPL_NOEXCEPT:
            Parent(now(), IPLBASE_TIME_TPS) {
            m_ticks+=(Ticks)convert_ticks(plus_ticks, ticks_per_second, TICKS_PER_SECOND);
        }
        //! \internal
        //! \brief The time point represented by \a ticks
        TimePoint(const SetTicks &, Ticks ticks) IPL_NOEXCEPT:
            Parent(ticks, IPLBASE_TIME_TPS) {}

        TimePoint &operator += (const Duration &duration) IPL_NOEXCEPT {
            m_ticks+=(Ticks)duration.m_ticks;
            return *this;
        }
        TimePoint &operator -= (const Duration &duration) IPL_NOEXCEPT {
            m_ticks-=(Ticks)duration.m_ticks;
            return *this;
        }

        TimePoint operator + (const Duration &duration) const IPL_NOEXCEPT {
            return TimePoint(SET_TICKS, m_ticks+(Ticks)duration.m_ticks);
        }
        TimePoint operator - (const Duration &duration) const IPL_NOEXCEPT {
            return TimePoint(SET_TICKS, m_ticks-(Ticks)duration.m_ticks);
        }
        Duration operator - (const TimePoint &other) const IPL_NOEXCEPT {
            return Duration((Duration::Ticks)m_ticks-(Duration::Ticks)other.m_ticks,
                            TICKS_PER_SECOND);
        }

        //! \brief Latest TimePoint possible
        static const TimePoint MAX;

    protected:
        static Ticks now() IPL_NOEXCEPT;
    };

/*****************************************************************************/

}  // end of namespace iplbase

/*****************************************************************************/
#endif
