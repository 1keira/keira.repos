/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SYSTEMINFO_HXX
#define OSAL_SYSTEMINFO_HXX

#include <ipl_config.h>
#include <common/error/Error.hxx>
#include <common/types/vector.hxx>

#if defined IPL_OS_POSIX
#    include "posix/ProcessTNGDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/ProcessTNGDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/ProcessTNGDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/Time.hxx>
#include <osal/osal_dso.h>

namespace osal
{

/**
 *    \brief
 *        A wrapping class for collecting process-relevant status information.
 *
 *        There is only so much you can collect in a more or less consistent way
 *        across different operating systems. This class tries to provide a subset
 *        of this information which currently comprises the following process
 *        attributes:
 *
 *        - process name
 *        - system and user times spent by the process
 *        - number of threads running in the process' context
 *        - dynamic memory allocations requested by the process
 *
 *        See the description of the class methods for various implications and
 *        shortcomings of gathered values.
 **/
class OSAL_EXPORT ProcessInfo
{
public:
    enum ProcessInfoValidFlags
    {
        IPL_NAME_VALID = 0,
        IPL_SYSTIME_VALID = 1,
        IPL_USRTIME_VALID = 2,
        IPL_THREADCNT_VALID = 3,
        IPL_HEAPUSG_VALID = 4,
        IPL_STACKUSG_VALID = 5,
        IPL_LAST_VALID = 6
    };

    ProcessInfo() :
        m_valid(false),
        m_valid_flags(IPL_LAST_VALID, false),
        m_pid(0),
        m_system_time(0),
        m_user_time(0),
        m_sample_time(0),
        m_thread_count(0),
        m_heap_usage(0),
        m_stack_usage(0)
    {
    }

    /**
     *    \brief
     *        Creates an object holding various status information of a process.
     *
     *    \param[in]
     *        pid The unique identifier of the process whose status information
     *        is to be collected.
     *
     *    \errorindicator
     *        via isValid()
     *
     *    \errors
     *        SysError with ID QUERY_FAILED if an error occurred during collecting
     *        status information.
     **/
    ProcessInfo(osal::ProcessId pid) :
        m_valid(false),
        m_valid_flags(IPL_LAST_VALID, false),
        m_pid(pid),
        m_system_time(0),
        m_user_time(0),
        m_sample_time(0),
        m_thread_count(0),
        m_heap_usage(0),
        m_stack_usage(0)
    {
        init();
    }

    /**
     *    \brief
     *        Validity indicator for ProcessInfo objects.

     *        Use this method for checking if construction of a ProcessInfo
     *        object was successful. This is usually not the case if the PID
     *        supplied in the constructor does not refer to an existing process.
     *        Additionally you should call isValid(ProcessInfoValidFlags) before
     *        querying and using any of the process attributes stored in this
     *        class. On QNX and Linux platforms you may expect all attributes are
     *        valid if this method returns true, but on Windows platforms not all
     *        information may be gathered for some processes due to user
     *        restrictions or mixed 32/64-bit runtime environments.
     *    \return
     *        true if construction succeeded, false otherwise.
     **/
    bool isValid() const
    {
        return m_valid;
    }

    /**
     *    \brief
     *        Validity indicator for collected process information.
     *    \param[in]
     *        flag one of ProcessInfoValidFlags.
     *    \return
     *        true if the process attribute is valid, false otherwise.
     **/
    bool isValid(ProcessInfoValidFlags flag) const
    {
        return (flag < IPL_LAST_VALID) ? m_valid_flags[flag] : false;
    }

    /**
     *    \brief
     *        Get the name of the process identified by pid.
     *    \return
     *        A string containing the process name or an empty string if the name
     *        could not be determined.
     **/
    const ipl::string & getProcessName() const
    {
        return m_process_name;
    }

    /**
     *    \brief
     *        Get the time the process spent executing in kernel mode.
     *    \return
     *        Time in milliseconds spent in kernel mode.
     *    \note
     *        You should check isValid(IPL_SYSTIME_VALID) before using this
     *        value. On Linux and QNX you can expect this to be always valid,
     *        on Windows systems this may be unaccessible due to user access
     *        restrictions. In this case 0 is returned.
     **/
    osal::TimeT getSystemTime() const
    {
        return m_system_time;
    }

    /**
     *    \brief
     *        Get the time the process spent executing in user mode.
     *    \return
     *        Time in milliseconds spent in user mode.
     *    \note
     *        You should check isValid(IPL_USRTIME_VALID) before using this
     *        value. On Linux and QNX you can expect this to be always valid,
     *        on Windows systems this may be unaccessible due to user access
     *        restrictions. In this case 0 is returned.
     **/
    osal::TimeT getUserTime() const
    {
        return m_user_time;
    }

    /**
     *    \brief
     *        Get the number of threads currently active in the process.
     *    \return
     *        Number of active threads.
     *    \note
     *        You should check isValid(IPL_THREADCNT_VALID) before using this
     *        value. On Linux and QNX you can expect this to be always valid,
     *        on Windows systems this may be unaccessible due to user access
     *        restrictions. In this case 0 is returned.
     **/
    size_t getThreadCount() const
    {
        return m_thread_count;
    }

    /**
     *    \brief
     *        Get dynamic memory allocated by the process.
     *    \return
     *        Memory allocated in bytes.
     *    \note
     *        You should check isValid(IPL_HEAPUSG_VALID) before using this
     *        value. On Linux and QNX you can expect this to be always valid,
     *        on Windows systems this may be unaccessible due to user access
     *        restrictions. In this case 0 is returned.
     *        Furthermore, this value may be inaccessible on Windows 64-bit
     *        systems because the process doing the query is running as 32-bit
     *        process in which case no information can be gathered about 64-bit
     *        processes.
     *        In addition you should not rely too much on these values but
     *        merely use it as a hint that needs further investigation if you
     *        suspect excess memory usage in a process.
     *
     *        How this value is gathered:
     *        - On Windows a system snapshot is created with
     *          CreateToolhelp32Snapshot which contains lists of heap blocks
     *          reserved by a process which is then accumulated and returned.
     *        - On QNX the memory regions mapped for the specified process are
     *          analyzed and their size is accumulated. The value should be
     *          exactly the same as reported by the QNX 'showmem' tool.
     *        - On Linux this simply returns the 6th entry in /proc/\<pid>/statm
     *          multiplied by the system's page size.
     *
     *        Comparing this value across different OS's is not very useful. In
     *        fact even different libc implementations will probably yield
     *        different results.
     **/
    size_t getHeapUsage() const
    {
        return m_heap_usage;
    }

    /**
     *    \brief
     *        Get memory allocated for stack usage by the process.
     *    \return
     *        Memory allocated in bytes.
     *    \note
     *        You should check isValid(IPL_STACKUSG_VALID) before using this
     *        value. In general, the same rules apply as for getHeapUsage().
     *
     *        Furthermore, this function returns the total stack memory for
     *        all threads of a process, not the stack usage of individual
     *        threads.
     **/
    size_t getStackUsage() const
    {
        return m_stack_usage;
    }

    /**
     *    \brief
     *        Get the unique process identifier associated with this object.
     *
     *    \return
     *        The PID as supplied in the constructor when this object was created.
     **/
    osal::ProcessId getPID() const
    {
        return m_pid;
    }

    /**
     *    \brief
     *        Calculate the CPU load caused by this process.
     *
     *        This function returns the CPU load between two arbitrary points
     *        in time caused by this process, sampled by creating two instances
     *        of this class. A typical usage could look like this (error-checking
     *        omitted):
     *
     *    \code
     *        // Determine how much CPU the process with PID 42 uses during
     *        // the next five seconds.
     *        ProcessInfo start(42);
     *        Time::sleep(5000);
     *        ProcessInfo end(42);
     *        ipl::cout << ProcessInfo::getCpuLoad(start, end) << ipl::endl;
     *    \endcode
     *
     *    \param[in]
     *        start The sample taken at the beginning of the measured interval.
     *
     *    \param[in]
     *        end The sample taken at the end of the measured interval.
     *
     *    \return
     *        A value in the range of [0,100] expressing the CPU load as
     *        percentage. On error, -1.0 is returned.
     *
     *    \errors
     *        SysError with ID INVALID_ARGUMENT if start and end do not
     *        contain info of the same process
     *        SysError with ID INVALID_ARGUMENT if either of \a start or \a end
     *        time-measurement relevant entries are invalid.
     *
     *    \warning
     *        This function can not reliably distinguish between incorrectly
     *        ordered parameters and external modifications to the system clock.
     *        So in case the sampling time of start is greater than the time
     *        stored in end, 0 is returned and no further error is raised.
     **/
    static double getCpuLoad(const ProcessInfo & start, const ProcessInfo & end);

    /**
     *    \brief
     *        Get a list of currently running process's identifiers.
     *
     *    \param[out]
     *        pids A vector that will be filled in with process identifiers of
     *        all currently existing processes in the system.
     *
     *    \return
     *        false on success, true if an error occurred.
     *
     *    \errorindicator
     *        via return code
     *
     *    \errors
     *        SysError with ID QUERY_FAILED.
     **/
    static bool getPIDs(ipl::vector<osal::ProcessId> & pids);

private:
    bool m_valid;
    //! Bit field indicating valid attributes of this class.
    ipl::vector<bool> m_valid_flags;
    //! The process name as known by the OS.
    ipl::string m_process_name;
    //! The unique process identifier.
    osal::ProcessId m_pid;
    //! System time consumed by the process.
    osal::TimeT m_system_time;
    //! User time consumed by the process.
    osal::TimeT m_user_time;
    //! Timestamp this information was collected.
    osal::TimeT m_sample_time;
    //! Number of threads of the process.
    size_t m_thread_count;
    //! Kind-of dynamic memory used by the process.
    size_t m_heap_usage;
    //! Memory allocated by the process for stack usage (sum of all thread stack sizes).
    size_t m_stack_usage;

    //! Initializes the members above by querying OS functions.
    void init();
};

/**
 *    \brief
 *        Utility class providing CPU system load calculation.
 *
 *        Calculating the system load is in general performed by measuring the
 *        amount of time the OS kernel has spent in idle mode and the time that
 *        has passed so far. Note that the concept of "system load" in this
 *        context always requires some amount of reference time frame. E.g. one
 *        can express the load of the system over the last n seconds but there
 *        is no real way of determining the current (as in "right now") CPU
 *        usage.
 *        This class should therefore be used by creating a pair of instances
 *        like this (error-handling omitted):
 *
 *    \code
 *
 *        // Simple measurement of cpu load during last 5 seconds.
 *        SystemLoad a;
 *        Time::sleep(5000);
 *        SystemLoad b;
 *        ipl::cout << SystemLoad::getCpuLoad(a, b) << ipl::endl;
 *
 *    \endcode
 **/
class OSAL_EXPORT SystemLoad
{
public:
    /**
     *    \brief
     *        Constructor which will take a sample of time spent in idle thread.
     *
     *    \errorindicator
     *        via isValid()
     *
     *    \errors
     *        SysError with ID QUERY_FAILED if
     *        - Acquiring the number of idle seconds failed.
     *        - Taking a timestamp failed (unlikely).
     **/
    SystemLoad() :
        m_is_valid(false),
        m_sample_time(0),
        m_idle_millis(0.0)
    {
        (void) sample();
    }

    /**
     *    \brief
     *        Take a new sample of time spent in idle thread.
     *
     *    \return
     *        true on error, false on success.
     *
     *    \errorindicator
     *        If true is returned an error occured.
     *
     *    \errors
     *        SysError with ID QUERY_FAILED if
     *        - Acquiring the number of idle seconds failed.
     *        - Taking a timestamp failed (unlikely).
     **/
    bool sample();

    //! returns true if acquiring idle time succeeded, false otherwise.
    bool isValid() const
    {
        return m_is_valid;
    }

    /**
     *    \brief
     *        Calculate the CPU load.
     *
     *        This function returns the CPU load between two arbitrary points
     *        in time, sampled by creating two instances of SystemLoad class.
     *
     *    \param[in]
     *        start The sample taken at the beginning of the measured interval.
     *
     *    \param[in]
     *        end The sample taken at the end of the measured interval.
     *
     *    \return
     *        A value in the range of [0,100] expressing the CPU load as
     *        percentage. On error, -1.0 is returned.
     *
     *    \errors
     *        SysError with ID INVALID_ARGUMENT if either of start or end are
     *        invalid.
     *
     *    \warning
     *        This function can not reliably distinguish between incorrectly
     *        ordered parameters and external modifications to the system clock.
     *        So in case the sampling time of start is greater than the time
     *        stored in end, 0 is returned and no further error is raised.
     **/
    static double getCpuLoad(const SystemLoad & start, const SystemLoad & end);

private:
    //! Valid flag, true means sampling succeeded.
    bool m_is_valid;
    //! The time the sample was taken.
    osal::TimeT m_sample_time;
    //! The number of milliseconds spent in system idle thread.
    double m_idle_millis;
};

} // end of namespace osal

#endif /* OSAL_SYSTEMINFO_HXX */
