/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <osal/UnicodeString.hxx>

namespace osal {

    inline ProcessTNG::ProcessTNG(const ipl::string &exec_path,
                                  IProcessEvent *const cb):
#ifndef USE_SPAWN_API_IN_POSIX_PROCESSTNG
        error(false),
        error_file(NULL),
        error_line(-1),
        error_type(NULL),
        error_id(-1),
#endif
        m_cb(cb)
    {
        init();

        if( isValid() ) // BRANCH_COVERAGE_UNTESTABLE
            setExecutable(exec_path);
    }


    inline ProcessTNG::ProcessTNG(const osal::UnicodeString &ucs,
                                  IProcessEvent *const cb):
#ifndef USE_SPAWN_API_IN_POSIX_PROCESSTNG
        error(false),
        error_file(NULL),
        error_line(-1),
        error_type(NULL),
        error_id(-1),
#endif
        m_cb(cb)
    {
        init();

        if( isValid() )
            setExecutable(ucs);
    }

    inline ProcessTNG::ProcessTNG(IProcessEvent * const cb):
#ifndef USE_SPAWN_API_IN_POSIX_PROCESSTNG
        error(false),
        error_file(NULL),
        error_line(-1),
        error_type(NULL),
        error_id(-1),
#endif
        m_cb(cb)
    {
        init();
    }

    inline bool ProcessTNG::setExecutable(const osal::UnicodeString &ucs)
    {
        return setExecutable(ucs.data());
    }

    inline ProcessId ProcessTNG::getProcessId() const
    {
        return m_handle.id != INVALID_PROCESS_ID ? m_handle.id :
            m_handle.last_id;
    }

    inline void ProcessTNG::setArgs(const ipl::vector<ipl::string> &args)
    {
        m_handle.args = args;
    }

    inline void ProcessTNG::setEnv(const Vars &vars)
    {
        m_handle.env = vars;
    }

    inline void ProcessTNG::setStdout(const ipl::string &to, const bool append)
    {
        m_handle.stdout_redir = to;
        m_append_stdout = append;
        m_handle.stdout_fd = OSAL_INVALID_FILE_HANDLE;
    }

    inline void ProcessTNG::setStderr(const ipl::string &to, const bool append)
    {
        m_handle.stderr_redir = to;
        m_append_stderr = append;
        m_handle.stderr_fd = OSAL_INVALID_FILE_HANDLE;
    }

    inline void ProcessTNG::setStdin(const ipl::string &from)
    {
        m_handle.stdin_redir = from;
        m_handle.stdin_fd = OSAL_INVALID_FILE_HANDLE;
    }

    inline void ProcessTNG::setStdout(osal::Pipe &pipe)
    {
        m_handle.stdout_redir.clear();
        m_handle.stdout_fd = pipe.getWriteEnd();
    }

    inline void ProcessTNG::setStderr(osal::Pipe &pipe)
    {
        m_handle.stderr_redir.clear();
        m_handle.stderr_fd = pipe.getWriteEnd();
    }

    inline void ProcessTNG::setStdin(osal::Pipe &pipe)
    {
        m_handle.stdin_redir.clear();
        m_handle.stdin_fd = pipe.getReadEnd();
    }

}  // end of namespace osal
