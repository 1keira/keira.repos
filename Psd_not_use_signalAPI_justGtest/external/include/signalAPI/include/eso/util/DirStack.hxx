/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_DIRSTACK_HXX
#define UTIL_DIRSTACK_HXX

#include <ipl_config.h>

#include <common/types/stack.hxx>
#include <common/types/string.hxx>
#include <common/CommonError.hxx>
#include <osal/FileSys.hxx>
#include <osal/UnicodeString.hxx>
#include <util/util_dso.h>

namespace util {

    /**
    * \brief
    *     pushd/popd like directory stack functionality

    *     \b WARNING! \b WARNING! \b WARNING!
    *
    *     This is fundamentally broken! Do not use!
    *
    *     As known from UNIX shells (bash) this class implements a
    *     pushd/popd like directory stack functionality.
    *
    *     Note, however, that as the current working directory of a
    *     process is a shared datum between all threads this class also is
    *     shared between threads and parallel, unsychronized usage of it
    *     will result in big trouble.
    * \deprecated since 2020-01-31: please implement your own directory stack if needed
    **/
    class UTIL_EXPORT
    IPL_DEPRECATED( "Do not use, see doxygen comment",
    DirStack
    {
    public:
        /**
        * \brief
        *     Push the current working directory on the stack and
        *     enter \c path
        * \errorindicator
        *     via return code of true
        * \note
        *     In case of error the directory stack will remain
        *     unmodified
        **/
        static bool pushd(const osal::UnicodeString &path) IPL_NOEXCEPT
        {
            m_dir_stack.push( osal::UnicodeString() );

            if( osal::FileSys::currentWD(m_dir_stack.top()) )
            {
                m_dir_stack.pop();
                return true;
            }

            if( osal::FileSys::changeWD(path) )
            {
                m_dir_stack.pop();
                return true;
            }

            return false;
        }

        //! version of pushd(const osal::UnicodeString) for ipl::string
        static bool pushd(const ipl::string &path) IPL_NOEXCEPT
        { return pushd( osal::UnicodeString(path) ); }

        //! version of pushd(const osal::UnicodeString) for const char*
        static bool pushd(const char * const path) IPL_NOEXCEPT
        { return pushd( ipl::string(path) ); }

        /**
        * \brief
        *     Enter the directory currently on the top of the stack
        *     and remove it from the stack
        * \errorindicator
        *     via return code of true
        * \note
        *     In case of error the top directory entry will still be
        *     removed from the stack. This is to prevent e.g.
        *     directories to stay forever on top of the stack that
        *     don't exist any more.
        **/
        static bool popd() IPL_NOEXCEPT
        {
            if( m_dir_stack.empty() )
            {
                ipl_raise( ipl::CommonError,
                    ipl::INVALID_USAGE,
                    "Attempt to pop directory from empty stack" );
                return true;
            }

            const bool ret = osal::FileSys::changeWD( m_dir_stack.top() );

            m_dir_stack.pop();

            return ret;
        }

    private:
        static ipl::stack<osal::UnicodeString> m_dir_stack;
    }
    )  /* end IPL_DEPRECATED */
    ;

}  // end of namespace osal

#endif
