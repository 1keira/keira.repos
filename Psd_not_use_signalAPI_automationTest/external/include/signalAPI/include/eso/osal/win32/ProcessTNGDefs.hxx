#include "BinFileDefs.hxx"

#ifndef OSAL_WIN32_PROCESSTNGDEFS_HXX
#define OSAL_WIN32_PROCESSTNGDEFS_HXX

#include <ipl_config.h>
#include "WinPath.hxx"
#include "BinFileDefs.hxx"
#include <common/types/vector.hxx>
#include <common/types/utility.hxx>

namespace osal {

    //! process reference datatype
    struct ProcessHandle
    {
        HANDLE handle;
        DWORD id;
        // executable path in unicode plus path mark, if necessary.
        WinPath executable;
#ifdef IPL_OS_WINPC
        // this is a job handle from CreateJobObject, if child is
        // supposed to run in a new process group
        HANDLE job;
#endif
        // arguments in unicode. yes I know. They're not really paths.
        ipl::vector<WinPath> args;
        // environment in unicode. yes I know. They're not really paths.
        ipl::vector< ipl::pair<WinPath, WinPath> > env;
        
        //! Redirection path for stdout, if any, in unicode
        WinPath stdout_redir;

        //! Redirection path for stderr, if any, in unicode
        WinPath stderr_redir;

        //! Redirection path for stdin, if any, in unicode
        WinPath stdin_redir;

        FileHandle stdout_fd;
        FileHandle stderr_fd;
        FileHandle stdin_fd;

        ProcessHandle() :
            handle(INVALID_HANDLE_VALUE),
            id(0),
            executable()
#ifdef IPL_OS_WINPC
            ,job(INVALID_HANDLE_VALUE),
            stdout_fd(OSAL_INVALID_FILE_HANDLE),
            stderr_fd(OSAL_INVALID_FILE_HANDLE),
            stdin_fd(OSAL_INVALID_FILE_HANDLE)
#endif
        { }

        bool operator==(const ProcessHandle &h)
        {
            return h.handle == this->handle;
        }

        bool operator!=(const ProcessHandle &h)
        {
            return !(*this == h);
        }

        bool isValid()
        {
            return handle != INVALID_HANDLE_VALUE;
        }

        void reset()
        {
            // id can be kept here in contrast to POSIX, it isn't an
            // actual handle
        
            handle = INVALID_HANDLE_VALUE;
#ifndef IPL_OS_WINCE
            job = INVALID_HANDLE_VALUE;
#endif
            // keep the rest!
        }

        void resetLastId()
        {
            id = 0;
        }
    };

    //! datatype for process IDs
    typedef DWORD ProcessId;

    //! datatype for child process exit codes
    typedef DWORD ProcessExitCode;

}  // end of namespace osal

#endif
