/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_PLAINTIMER_HXX
#define UTIL_PLAINTIMER_HXX

#include <ipl_config.h>
#include <common/error/ErrorType.hxx>
#include <osal/Timer.hxx>
#include <util/util_dso.h>

/*****************************************************************************/

namespace util {

/*****************************************************************************/

    /*!
        \brief Easy to use no-frills timer

        This compensates for osal::Timer's limitation of not passing any
        useful context to its callback.
        It shares all other shortcomings of osal::Timer, such as calling all
        timers' callbacks from the same single thread, which enables one timer
        to block all the others.

        You should consider using osal::Alarm instead.
    */
    class UTIL_EXPORT PlainTimer: public osal::Timer {
    public:
        typedef void (*Callback)(void *context);

        PlainTimer(Callback callback, void *context, bool high_priority=false) IPL_NOEXCEPT:
            osal::Timer(do_it_right, high_priority),
            callback(callback), context(context) {}

    protected:
        static void do_it_right(osal::Timer *const which) IPL_NOEXCEPT;

        Callback callback;
        void *context;
    };

/*****************************************************************************/

}  // end of namespace util

/*****************************************************************************/
#endif
