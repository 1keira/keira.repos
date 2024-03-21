/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <common/Macros.hxx>
#include <osal/SysError.hxx>

/*  Note for Win CE:
 *  ===============
 * Relative path names are not supported in Windows CE. 
 *
 * All path names are relative to the root directory. Hence all
 * occurrences of relative path names in the applications should be
 * changed with the full path. In other words there is no concept of
 * current directory under Windows CE, hence any references to any
 * resource without specifying the full path always refers with respect
 * to the root directory.  Say we are currently in the directory
 * \\windows and we refer to a file by name readme.txt under this
 * directory.  If we refer to it by just its name without giving the
 * full path it will lead to nowhere since it will search for it in the
 * root directory. Hence the full path needs to be specified. */

/*
 *    mage2618:
 *
 *    we're going to emulate the CWD at a later stage. From that point
 *    on we should be able to handle paths as usual.
 *
 *    Entry point on CE is '\\'
 */


namespace osal {

    /*
        XXX

        NOTE: there are still network paths on Win32 that
        start with two backslashes: \\someshare\something

        Currently not supported
    */

#ifdef OSAL_EXPORT_CONTEXT

    inline Path Path::findEntryPoint() const
    {
#if defined(IPL_OS_WINCE)
        const char TERM_SEP[2] = { SEPARATOR, '\0' };
        return TERM_SEP;
#else
        Path ret = this->getEntryPoint();

        if( ret.empty() )
        {
            // try to resolve to an absolute path and return that
            // entry point
            ret = this->getAbsolute().substr(0, 3);
        }
        return ret;
#endif
    }

    inline WidePath WidePath::findEntryPoint() const
    {
#if defined(IPL_OS_WINCE)
        const wchar_t TERM_SEP[2] = { SEPARATOR, L'\0' };
        return TERM_SEP;
#else
        WidePath ret = this->getEntryPoint();

        if( ret.empty() )
        {
            // try to resolve to an absolute path and return that
            // entry point
            ret = this->getAbsolute().substr(0, 3);
        }

        return ret;
#endif
    }

    template <typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>
    BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>
    BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::getEntryPoint() const
    {
// pedu2501: WinCE does not deal with drive names! Thus we have no entry
// point!
#if defined(IPL_OS_WINCE)
        const CHAR_TYPE TERM_SEP[2] = { SEPARATOR,
            CHAR_TRAITS::to_char_type(0) };

        return this->isAbsolute() ? TERM_SEP : BasicPath();
#else
        if( this->isAbsolute() )
            return this->substr(0, 3);
        // relative path on windows still can have an entry point
        else if( this->size() > 1 &&
            ((*this)[1] == CHAR_TRAITS::to_char_type(':')) )
        {
            return this->substr(0, 2);
        }

        return BasicPath();
#endif
    }

    template <typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>
    bool
    BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::isAbsolute() const
    {
#if defined(IPL_OS_WINCE)
        return (!this->empty()) && ((*this)[0] == SEPARATOR);
#else
        /*
        *    Note: The path is only absolute if colon and backslash
        *    are present. Without the backslash it happens to be a
        *    path relative to the current working directory for the
        *    specified drive.
        */
        return (this->size() > 2) &&
            ((*this)[1] == CHAR_TRAITS::to_char_type(':')) &&
            ((*this)[2] == SEPARATOR);
#endif
    }

#endif // OSAL_EXPORT_CONTEXT

} // end namespace
