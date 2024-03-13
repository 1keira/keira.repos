/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_GLOBALERRORHANDLER_HXX
#define IPL_GLOBALERRORHANDLER_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <stdlib.h>

#include <common/iplcommon_dso.h>
#include <common/Macros.hxx>

#ifdef USE_THREADSAFE_IN_TINYOSAL
#include <threadsafe/AtomicCounter.hxx>
#endif

namespace IPL_NAMESPACE
{

/**
 * \brief
 *     Facilities for global handling of critical errors

 *     This class provides facilities that can be used in the following
 *     cases:
 *
 *     - an irrecoverable program state has been reached in a thread
 *     and program execution cannot continue. In this case doAbort()
 *     can be used.
 *
 *     - checking a certain program state for sanity and cease program
 *     execution in case sanity cannot be verified. For this doAssert()
 *     is provided.
 *
 *     - emitting a warning message in case a suspicious program state
 *     has been detected that allows program execution to continue but
 *     the problem should be reported to the developer. doWarning()
 *     is the function to use in that situation.
 *
 *     - if a heap memory allocation failed that makes further program
 *     execution impossible. doOutOfMem() helps in this case.
 *
 *     For each of these facilities a number of handlers can be
 *     registered in an atexit()-like manner. This means that the
 *     handlers can only be registered but cannot be unregistered any
 *     more. The handlers will be executed in the reverse order of
 *     registration. For each facility a default handler is installed
 *     by this class that does the following:
 *
 *     - it prints all available information onto stderr
 *     - for all facilities except doWarning() it calls abort() to
 *     terminate program execution, if abort() calls have not been
 *     disabled via a call to disableAbort(true).
 *
 *    The doOutOfMem() facility allows registered handlers to indicate
 *    that a retry to get heap memory should be made by the caller. In
 *    that case no abort() will be called.
 * \note
 *     This class is accompanied by a number of preprocessor macros
 *     that ease the handling for developers. These macros can be found
 *     in the common/Macros.hxx header:
 *
 *     - IPL_ABORT
 *     - IPL_ASSERT
 *     - IPL_ASSERT_VERBOSE
 *     - IPL_WARN
 *     - IPL_OOM
 **/
class IPLCOMMON_EXPORT GlobalErrorHandler
{
public: // types
#ifdef USE_THREADSAFE_IN_TINYOSAL
        typedef threadsafe::AtomicCounter Atomic;
#else
        typedef volatile int Atomic;
#endif

    /**
     * \brief
     *     Signature for the callback function for abort handlers

     *     Provided parameters are
     *
     *     - a string describing the source code location where the
     *     error occured
     *     - a string describing the reason for the abort
     **/
    typedef void (*AbortHandler)(const char *location, const char *problem);
    /**
     * \brief
     *     Signature for the callback function for assert handlers

     *     Provided parameters are
     *
     *     - a string describing the condition that failed
     *     - a string describing the source code location where the
     *     error occured
     *     - a string describing the reason for the abort
     *     (optional)
     **/
    typedef void (*AssertHandler)(const char *cond, const char *location, const char *problem);
    /**
     * \brief
     *     Signature for the callback function for warning handlers

     *     Provided parameters are:
     *
     *     - a string describing the source code location where the
     *     warning occured
     *     - a string describing the reason for the warning
     **/
    typedef void (*WarningHandler)(const char *location, const char *problem);

    /**
     * \brief
     *     Signature for the callback function for out of memory
     *     handlers

     *     Provided parameters are:
     *
     *     - a string describing the source code location where the
     *     lack of memory occured
     *     - a human-readable string describing the lack of memory
     *     (e.g. what kind of data structure couldn't be
     *     allocated, optional)
     * \return
     *     If \c true is returned then no more out of memory
     *     handlers will be called but execution is returned to the
     *     caller of outOfMem() to allow it to retry the memory
     *     allocation.
     *
     *     If \c false is returned then the next out of memory
     *     handlers will be called or abort() will be called if no
     *     more handlers are available.
     **/
    typedef bool (*OutOfMemHandler)(const char *location, const char *problem);

public: // static functions

    /**
     * \brief
     *     Allows to switch actual abort() calls on/off

     *     If \c val is set to \c true then the GlobalErrorHandler
     *     will never perform a call to native abort() or assert()
     *     but instead continue execution of the program by
     *     returning from the doAbort() or doAssert() or
     *     doOutOfMem() functions.
     *
     *     Everything else will remain the same i.e. all handlers
     *     will be called and logging/printouts occur.
     *
     *     If one of the called handlers calls abort() or assert()
     *     on its own then this setting here will, of course, have
     *     no effect.
     *
     *     By default the call to abort() is *not* disabled.
     *     Disabling the actual calls to abort() is discouraged as
     *     the code will not be prepared to handle the situation
     *     and most probably will run into other devastating
     *     problems of an undefined nature.
     **/
    static void disableAbort(const bool val) IPL_NOEXCEPT
    {
         /* this is not particularly thread safe
         * but should suffice for the moment. Usually this will
         * only be called once from the main thread and from
         * there only reads occur */
        s_disable_abort = val;
    }

    //! Returns whether currently calls to abort() are disabled
    static bool isAbortDisabled() IPL_NOEXCEPT
    { return s_disable_abort; }

    /**
     * \brief
     *     Register a new abort handler
     * \return
     *     \c false if registration succeeded, \c true if no more
     *     handlers can be registered
     **/
    static bool atAbort( AbortHandler ah ) IPL_NOEXCEPT;

    /**
     * \brief
     *     Register a new assert handler
     * \return
     *     \c false if registration succeeded, \c true if no more
     *     handlers can be registered
     **/
    static bool atAssert( AssertHandler ah ) IPL_NOEXCEPT;

    /**
     * \brief
     *     Register a new warning handler
     * \return
     *     \c false if registration succeeded, \c true if no more
     *     handlers can be registered
     **/
    static bool atWarning( WarningHandler wh ) IPL_NOEXCEPT;

    /**
     * \brief
     *     Register a new out of memory handler
     * \return
     *     \c false if registration succeeded, \c true if no more
     *     handlers can be registered
     **/
    static bool atOutOfMem( OutOfMemHandler oh ) IPL_NOEXCEPT;

    /**
     * \brief
     *     Perform an abort

     *     All currently registered abort handlers will be called
     *     in reverse order of registration. The default abort
     *     handler will always be called last.
     *
     *     None of the custom abort handlers shall abort program
     *     execution on their own. Instead the default handler
     *     calls abort() in case isAbortDisabled() returns \c false.
     *     Otherwise the function returns and execution continues
     *     in an undefined manner.
     * \param[in]
     *     file The source file where the problem occured
     * \param[in]
     *     line The line in \c file where the problem occured
     * \param[in]
     *     function The function where the problem occured
     * \param[in]
     *     fmt An optional printf()-compatible format string
     *     followed by optional vararg arguments that make up an
     *     informational message why the abort occured.
     **/
    static void doAbort(const char *file, const int line,
        const char *function,
        const char *fmt = NULL, ...) IPL_NOEXCEPT
        IPL_PRINTF_LIKE_FUNCTION(4, 5);

    /**
     * \brief
     *     Perform an assertion

     *     If \c cnd is \c true then the function returns without
     *     doing anything.
     *
     *     If \c cnd is \c false then all assert handlers will be
     *     called in reverse order of registration. The default
     *     assert handler will always be called last.
     *
     *     None of the custom handlers shall abort program
     *     execution on their own. Instead the default handler
     *     calls abort() in case isAbortDisabled() returns \c false.
     *     Otherwise the function returns and execution continues
     *     in an undefined manner.
     * \param[in] cnd
     *     The condition to check
     * \param[in] cnd_label
     *     A string representing the condition that has been
     *     checked
     * \param[in]
     *     file The source file where the problem occured
     * \param[in]
     *     line The line in \c file where the problem occured
     * \param[in]
     *     function The function where the problem occured
     * \param[in]
     *     fmt An optional printf()-compatible format string
     *     followed by optional vararg arguments that make up an
     *     informational message why the assert occured.
     **/
    static void doAssert(const bool cnd, const char *cnd_label,
        const char *file, const int line, const char *function,
        const char *fmt = NULL, ...) IPL_NOEXCEPT
        IPL_PRINTF_LIKE_FUNCTION(6, 7);

    /**
     * \brief
     *     Emit a developer warning

     *     All warning handlers will be called in reverse order of
     *     registration. The default warning handler will always be
     *     called last.
     * \param[in]
     *     file The source file where the problem occured
     * \param[in]
     *     line The line in \c file where the problem occured
     * \param[in]
     *     function The function where the problem occured
     * \param[in]
     *     fmt An optional printf()-compatible format string
     *     followed by optional vararg arguments that make up an
     *     informational message why the warning occured.
     **/
    static void doWarning(const char *file, const int line,
        const char *function, const char *fmt = NULL, ...) IPL_NOEXCEPT
        IPL_PRINTF_LIKE_FUNCTION(4, 5);

    /**
     * \brief
     *     Start out of memory handling

     *     All out of memory handlers will be called in reverse
     *     order of registration. The default out of mem handler
     *     will always be called last.
     *
     *     The first handler that returns \c true from its callback
     *     function no remaining handlers will be called but the
     *     function returns to the caller to allow it to retry the
     *     memory allocation. If memory allocation still fails then
     *     this function should be called again.
     *
     *     If none of the handlers returns \c true then abort() is
     *     called to end program execution in case
     *     isAbortDisabled() returns \c false.
     * \param[in]
     *     file The source file where the problem occured
     * \param[in]
     *     line The line in \c file where the problem occured
     * \param[in]
     *     function The function where the problem occured
     * \param[in]
     *     fmt An optional printf()-compatible format string
     *     followed by optional vararg arguments that make up an
     *     informational message containing additional information
     *     about the failed memory allocation.
     **/
    static void doOutOfMem(const char *file, const int line,
        const char *function, const char *fmt = NULL, ...) IPL_NOEXCEPT
        IPL_PRINTF_LIKE_FUNCTION(4, 5);

protected: // static functions

    /**
     * \brief
     *     Default abort handler callback

     *     This handler is always present and will always be called
     *     last in case of a call to doAbort().
     *
     *     It writes \c location and \c problem onto stderr. Also
     *     it writes a currently set error onto stderr, if one is
     *     present.
     **/
    static void defaultAbortHandler(const char *location,
        const char *problem) IPL_NOEXCEPT;

    /**
     * \brief
     *     Default assert handler callback

     *     This handler is always present and will always be called
     *     last in case of a call to doAssert().
     *
     *     It writes \c location, \c cond and \c problem onto
     *     stderr. Also it writes a currently set error onto
     *     stderr, if one is present.
     **/
    static void defaultAssertHandler(const char *cond,
                                     const char *location,
                                     const char *problem) IPL_NOEXCEPT;

    /**
     * \brief
     *     Default warning handler callback

     *     This handler is always present and will always be called
     *     last in case of a call to doWarning().
     *
     *     It writes \c location and \c problem onto stderr. Also
     *     it writes a currently set error onto stderr, if one is
     *     present.
     **/
    static void defaultWarningHandler(const char *location,
        const char *problem) IPL_NOEXCEPT;

    /**
     * \brief
     *     Default out of memory handler callback

     *     This handler is always present and will always be called
     *     last in case of a call to doOutOfMem().
     *
     *     It writes \c location and \c problem onto stderr. Also
     *     it writes a currently set error onto stderr, if one is
     *     present.
     *
     *     It always returns \c false.
     **/
    static bool defaultOutOfMemHandler(const char *location,
        const char *problem) IPL_NOEXCEPT;

protected: // static data
    //! \brief
    //! maximum number of handlers for each facility that can be
    //! registered. This does not count against default handlers.
    static const int MAX_HANDLERS=8;
    //! \brief
    //! maximum length of vararg-generated messages in characters
    static const int MAX_MSG_LEN=1024;

    static Atomic s_num_abort_handlers;
    static Atomic s_num_assert_handlers;
    static Atomic s_num_warning_handlers;
    static Atomic s_num_outofmem_handlers;

    static AbortHandler s_abort_handlers[MAX_HANDLERS];
    static AssertHandler s_assert_handlers[MAX_HANDLERS];
    static WarningHandler s_warning_handlers[MAX_HANDLERS];
    static OutOfMemHandler s_outofmem_handlers[MAX_HANDLERS];

    static volatile bool s_disable_abort;
};

} // end ns

#endif // include guard
