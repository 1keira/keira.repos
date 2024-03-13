/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_POSIX_PROCESSTNGDEFS_HXX
#define OSAL_POSIX_PROCESSTNGDEFS_HXX

// #include "../posix/BinFileDefs.hxx"
// 
// #include <common/types/string.hxx>
// #include <common/types/vector.hxx>
// #include <common/types/utility.hxx>

namespace osal {

    //! OS handle to reference a certain process
    struct ProcessHandle
    {
//         pid_t id;
//         // this is kept to have a process ID around even after a process
//         // exited but wasn't collected by the application yet
//         pid_t last_id;
//         // path to executable be it in ASCII or unicode
//         ipl::string executable;
//         // arguments in ASCII or unicode
//         ipl::vector<ipl::string> args;
//         //! currently set environment in ASCII or unicode
//         ipl::vector< ipl::pair<ipl::string,
//             ipl::string> > env;
//         
//         //! Redirection path for stdout, if any, in ASCII or unicode
//         ipl::string stdout_redir;
// 
//         //! Redirection path for stderr, if any, in ASCII or unicode
//         ipl::string stderr_redir;
// 
//         //! Redirection path for stdin, if any, in ASCII or unicode
//         ipl::string stdin_redir;
// 
//         FileHandle stdout_fd;
//         FileHandle stdin_fd;
//         FileHandle stderr_fd;
// 
//         //! Whether this child is a process leader for a new process
//         //group
//         bool process_leader;
// 
//         ProcessHandle() :
//             id(-1),
//             last_id(-1),
//             executable(),
//             stdout_fd(OSAL_INVALID_FILE_HANDLE),
//             stdin_fd(OSAL_INVALID_FILE_HANDLE),
//             stderr_fd(OSAL_INVALID_FILE_HANDLE),
//             process_leader(false)
//         { }

        bool operator==(const ProcessHandle &h)
        {
            return 0;
//             return id == h.id;
        }

        bool operator!=(const ProcessHandle &h)
        {
            return 0;
//             return !(*this == h);
        }

        bool isValid()
        {
            return 0;
//             return id != -1;
        }

        void reset()
        {
//             // remember the current ID as last_id for getProcessId()
//             last_id = id;
//             // invalid ID
//             id = -1;
//             // don't reset the rest, the process might be re-started
        }

        void resetLastId()
        {
//             last_id = -1;
        }
    };

    //! Identifier for a process, Note! this is left seperate 
    //! from Processhandle on purpose (differs on other OSs)!
    typedef /*pid_t*/int ProcessId;

    //! Exit code values from child processes
    typedef int ProcessExitCode;

}  // end of namespace osal

#endif
