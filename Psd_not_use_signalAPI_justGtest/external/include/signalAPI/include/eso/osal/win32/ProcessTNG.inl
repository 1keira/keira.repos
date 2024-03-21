/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include "WinPath.hxx"

namespace osal {

    inline ProcessTNG::ProcessTNG(const osal::UnicodeString &exec_path,
                                  IProcessEvent *const cb):
        m_cb(cb)
    {
        init();

        if( isValid() )
            setExecutable(exec_path);
    }

    inline ProcessTNG::ProcessTNG(const ipl::string &path,
                                  IProcessEvent *const cb):
        m_cb(cb)
    {
        init();

        if( isValid() )
            setExecutable(path);
    }

    inline ProcessTNG::ProcessTNG(IProcessEvent *const cb):
        m_cb(cb)
    {
        init();
    }

    inline bool ProcessTNG::setExecutable(const ipl::string &path)
    {
        return setExecutable(
            static_cast<osal::UnicodeString>(path) );
    }

    inline ProcessId ProcessTNG::getProcessId() const
    {
        return m_handle.id;
    }

    inline void ProcessTNG::setArgs(const ipl::vector<ipl::string> &args)
    {
        m_handle.args.clear();

        for( ipl::vector<ipl::string>::const_iterator it = args.begin();
            it != args.end();
            it++)
        {
            WinPath arg( *it );

            m_handle.args.push_back( arg );
        }
    }

    inline void ProcessTNG::setEnv(const Vars &vars
    )
    {
        m_handle.env.clear();

        for(Vars::const_iterator it=vars.begin(); it!=vars.end(); it++) {
            ipl::pair<WinPath, WinPath> var_pair;

            var_pair.first = WinPath( it->first );
            var_pair.second = WinPath( it->second );

            m_handle.env.push_back( var_pair );
        }
    }

    inline void ProcessTNG::setStdout(const ipl::string &to, const bool append)
    {
        m_handle.stdout_redir = WinPath(to);
        m_append_stdout = append;
        m_handle.stdout_fd = OSAL_INVALID_FILE_HANDLE;
    }

    inline void ProcessTNG::setStderr(const ipl::string &to,
        const bool append)
    {
        m_handle.stderr_redir = WinPath(to);
        m_append_stderr = append;
        m_handle.stdout_fd = OSAL_INVALID_FILE_HANDLE;
    }

    inline void ProcessTNG::setStdin(const ipl::string &from)
    {
        m_handle.stdin_redir = WinPath(from);
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
