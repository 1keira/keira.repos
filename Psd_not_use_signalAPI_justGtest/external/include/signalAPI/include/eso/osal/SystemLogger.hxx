/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SYSTEMLOGGER_HXX
#define OSAL_SYSTEMLOGGER_HXX

#include <ipl_config.h>

#include <common/Singleton.hxx>

#if defined IPL_OS_ANDROID
#    include "android/SystemLoggerDefs.hxx"
#elif defined IPL_OS_LINUX
#    include "linux/SystemLoggerDefs.hxx"
#elif defined IPL_OS_QNX
#    include "qnx/SystemLoggerDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/SystemLoggerDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/SystemLoggerDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal_dso.h>

namespace osal
{

enum LogLevel
{
    LOGLEVEL_ERROR        = 0,
    LOGLEVEL_WARNING    = 1,
    LOGLEVEL_INFO        = 2
};

/**
    \brief Abstraction for the operating system's logging facility

    This class serves as a very basic abstraction for various operating systems'
    logging facilities. The following table shows which log facility is used for
    each OS:

    <table>
        <tr> <td>OS</td>         <td>Log facility</td> </tr>
        <tr> <td>Windows</td>    <td>Windows Event Log</td> </tr>
        <tr> <td>Windows CE</td> <td>CeLog</td> </tr>
        <tr> <td>Linux</td>      <td>syslog</td> </tr>
        <tr> <td>QNX</td>        <td>slog</td> </tr>
    </table>

    Because these logging services offer very different functionalities only a
    minimum of the supported features is actually usable through this class.
    E.g. there are only three different severity levels for log messages although
    Linux syslog would allow eight different levels; on the other hand Windows'
    EventLog only provides three levels, so there would be no point in allowing
    the user to choose between more than three levels.

    Note also that there is no possibility for the caller to check if a log message
    was successfully written to the OS log for quite the same reason. Some operating
    systems return a value indicating success while others don't. (Besides, what would
    you do when logging fails anyway? Try to store a log message?)

    As this class is implemented as a singleton, it is usually sufficient
    to get an instance and call its log() method, e.g.:

    \code
    SystemLogger::getInstance().log(osal::LOGLEVEL_ERROR, "critical error detected");
    \endcode

    It is normally not necessary to call openLog() and closeLog() manually, but the
    interface is provided in case someone wants to force a flush of log messages;
    note that it depends on the operating system if this makes sense at all (e.g.
    Windows CE stores its log content in memory).
 */
class OSAL_EXPORT SystemLogger
{
    IPL_DECLARE_SINGLETON(SystemLogger)
public:

    ~SystemLogger() IPL_NOEXCEPT;

    /** \brief Explicitly open the operating system's log sink

        Note that it is usually not necessary to call this function manually.
        This will already be called from the class constructor and from the
        log()-function if the OS log is closed. It merely serves as a way to
        reopen the operating system's log facility after manually closing it.
     */
    void openLog() IPL_NOEXCEPT;

    /** \brief Explicitly close the operating system's log sink

        Note that it is usually not necessary to call this function manually.
        This will be called from the class destructor in any case. It might
        be useful however, to manually close and reopen the system log if
        flushing the log messages should be forced.
     */
    void closeLog() IPL_NOEXCEPT;

    /** \brief Function for logging a message to the operating system's log facility

        \param severity A severity level that should be associated with this log
            message; see LogLevel for available levels.
        \param logmessage Pointer to null-terminated C-String. The maximum length of
            the log message might be restricted depending on the operating system.
     */
    void log(LogLevel const severity, char const * const logmessage) IPL_NOEXCEPT;

private:
    //! \brief Handle for the operating system's log facility
    osal::LogHandle m_log;
};

} // end namespace

#endif /* OSAL_SYSTEMLOGGER_HXX */
