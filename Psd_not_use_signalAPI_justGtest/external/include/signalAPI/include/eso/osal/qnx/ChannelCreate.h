/*****************************************************************************/
/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
    $Id$
*/
/*****************************************************************************/
#ifndef OSAL_QNX_CHANNELCREATE_H
#define OSAL_QNX_CHANNELCREATE_H
/*****************************************************************************/

#ifndef OSAL_CHANNELCREATE_HUSH
#warning OsalChannelCreate and friends are not needed anymore. Please change to normal QNX ChannelCreate(_r) etc.
#endif

#include <osal/osal_dso.h>

#include <sys/neutrino.h>

/*****************************************************************************/
/*!
    \page OsalChannelCreate_page The QNX system pulse multiplexing channels subsystem

    \b Note: This QNX limitation is fixed, the mechanism is not needed anymore.

    The QNX function ChannelCreate has a serious limitation.
    The _NTO_CHF_COID_DISCONNECT and _NTO_CHF_THREAD_DEATH flags must only be
    set on one single channel per process,
    i.e. only one channel can receive _PULSE_CODE_COIDDEATH or
    _PULSE_CODE_THREADDEATH pulses.
    Obviously, if you combine several independent software parts into one
    program and more than one of those needs to track dying threads or channels
    (i.e. needs to set those flags/receive those pulses),
    the limitation cannot be complied with.

    OSAL contains drop-in replacements for the QNX functions
    ChannelCreate(), ChannelCreate_r(), ChannelDestroy() and ChannelDestroy_r()
    that do not have this limitation and \b must be used instead, namely
    OsalChannelCreate(), OsalChannelCreate_r(), OsalChannelDestroy() and
    OsalChannelDestroy_r().

    The replacement functions work by maintaining an internal channel/thread
    that acts as the one single receiver of _PULSE_CODE_COIDDEATH and
    _PULSE_CODE_THREADDEATH pulses.
    The replacement functions intercept and remove the two flags
    and register the created channels with the single receiver.
    When one of the pulses comes in it gets resent to all registered channels.
    Therefore the only interface change is to prefix
    channel creation/destruction with "Osal".

    Now as OSAL uses a channel with _NTO_CHF_COID_DISCONNECT and
    _NTO_CHF_THREAD_DEATH set, <strong>nobody else must set them, ever</strong>.
    Unfortunately this includes channels created from within QNX code.
    So you must never call anything in QNX that internally creates a channel
    with one of these flags set, including ressource managers.
    Instead you must create the channel yourself (via the OSAL functions)
    and inject it into whatever you're trying to use.
    For ressource managers for example this means using
    dispatch_create_channel() instead of dispatch_create().

    As OSAL uses a thread to do the dispatching, the mechanism does only work
    when OSAL (including the thread) is initialized.
    This is done by adding
    \code
    osal::Osal osal;
    \endcode
    to the beginnig of your main() function.

    So to safely receive _PULSE_CODE_COIDDEATH and/or _PULSE_CODE_THREADDEATH
    pulses in your code
    - Replace \#include <sys/neutrino.h> with \#include <osal/qnx/ChannelCreate.h>
    - Replace ChannelCreate() with OsalChannelCreate(),
      ChannelCreate_r() with OsalChannelCreate_r(),
      ChannelDestroy() with OsalChannelDestroy() and
      ChannelDestroy_r() with OsalChannelDestroy_r()
    - Make sure that OSAL gets initialized before you expect the pulses
    - Make sure you don't call the four QNX functions, not even indirectly
      (I apologize for this inconvenience, but I cannot help it.
      We're trying to do the OS'es job on application level here.)

    If, on the other hand, the problem is triggered by the sheer existence
    of the workaround (i.e. you had a single channel before but now cannot
    create it any more), the whole mechanism can be switched of by defining
    DISABLE_QNX_PULSEHANDLING at osal compile time.
    OsalCreateChannel() et al. just call the original QNX functions in this
    case.
*/
/*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*!
    \brief Drop-in replacement for ChannelCreate

    This is identical to QNX' ChannelCreate except that the
    _NTO_CHF_COID_DISCONNECT and _NTO_CHF_THREAD_DEATH flags may be used
    on as many channels as you like.

    If DISABLE_QNX_PULSEHANDLING is defined, this just calls ChannelCreate.

    \see \ref OsalChannelCreate_page
*/
OSAL_EXPORT int OsalChannelCreate(unsigned flags);

/*!
    \brief Drop-in replacement for ChannelCreate_r

    This is identical to QNX' ChannelCreate_r except that the
    _NTO_CHF_COID_DISCONNECT and _NTO_CHF_THREAD_DEATH flags may be used
    on as many channels as you like.

    If DISABLE_QNX_PULSEHANDLING is defined, this just calls ChannelCreate_r.

    \see \ref OsalChannelCreate_page
*/
OSAL_EXPORT int OsalChannelCreate_r(unsigned flags);

/*!
    \brief Drop-in replacement for ChannelDestroy

    This is identical to QNX' ChannelDestroy except that
    you must use it for all channels created with
    OsalCreateChannel or OsalCreateChannel_r.

    If DISABLE_QNX_PULSEHANDLING is defined, this just calls ChannelDestroy.

    \see \ref OsalChannelCreate_page
*/
OSAL_EXPORT int OsalChannelDestroy(int chid);

/*!
    \brief Drop-in replacement for ChannelDestroy_r

    This is identical to QNX' ChannelDestroy_r except that
    you must use it for all channels created with
    OsalCreateChannel or OsalCreateChannel_r.

    If DISABLE_QNX_PULSEHANDLING is defined, this just calls ChannelDestroy_r.

    \see \ref OsalChannelCreate_page
*/
OSAL_EXPORT int OsalChannelDestroy_r(int chid);

/*****************************************************************************/

#ifdef __cplusplus
}  // end of extern "C"
#endif

/*****************************************************************************/
#endif
