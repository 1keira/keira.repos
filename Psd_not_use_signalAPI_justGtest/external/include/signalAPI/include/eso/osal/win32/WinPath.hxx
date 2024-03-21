/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
*/

#ifndef OSAL_WIN32_WINPATH_HXX
#define OSAL_WIN32_WINPATH_HXX

#include <iplbase/win32.h>

#include <common/Macros.hxx>
#include <common/error/ErrorHelper.hxx>

#include <osal/Path.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    /**
    * \brief
    *     Smart object for handling ascii<->unicode conversions and win32
    *     path peculiarities

    *     This object can take any of the typical string types roaming
    *     around like:
    *
    *     * c character array containing ASCII
    *     * STL string container containing ASCII
    *     * c wide character array containing UTF16
    *     * OSAL UnicodeString container containing raw UTF16
    *
    *     The object will copy/convert the obtained data into itself in
    *     UTF16 wide character encoding.
    *
    *     The getAscii() function allows to convert the string back into
    *     ASCII, replacing non-fitting characters with questionmarks -
    *     this is e.g. useful to print unicode paths in error strings that
    *     expect %s.
    *
    *     The getPath() function additionall allows to add win32 path
    *     length checks. If the path length is greater than around 250
    *     characters then the special "don't interpret path mark" is
    *     prepended. This handling is not yet complete, though. In case
    *     the path is relative then in the case of too long paths OSAL
    *     needs to resolve the path to an absolute path itself.
    *
    *     Apart from all that this object inherits the STL
    *     container-semantics from osal::WidePath and any path operations
    *     provided there, too.
    **/
    class OSAL_EXPORT WinPath :
        public osal::WidePath
    {
    public:
        WinPath()
        { }

        WinPath(const char *s, const size_t chars = 0) :
            WidePath(s, chars)
        { }

        WinPath(const ipl::string &s) :
            WidePath(s.c_str(), s.size())
        { }

        WinPath(const wchar_t *s, const size_t chars = 0) :
            WidePath(s)
        { }

        WinPath(const osal::UnicodeString &ucs) :
            WidePath( ucs.nativeData() )
        { }

        /**
        * \brief
        *     Returns a ptr. to the current path, suitable for turning
        *     into a system call

        *     if \c add_path_mark_if_needed is set to \c true then the
        *     function call will transparently add a "don't interpret
        *     path mark" to the path that is returned. This will not
        *     modify the current contents of the string object.
        **/
        const ipl::wstring& getPath(
            const bool add_path_mark_if_needed = true) const;

        /**
        * \brief
        *     get the stored unicode path as an ASCII string

        *     Any characters that can't be represented in ASCII will
        *     be replaced by questionmarks
        **/
        ipl::string getAscii();

        //! transparently become an osal::UnicodeString
        operator osal::UnicodeString() const
        {
            osal::UnicodeString ret(
                (const char*)(this->getPath(false)).c_str(),
                (this->size() + 1) * sizeof(native_utf),
                osal::UnicodeString::SHARED );

            return ret;
        }

    protected: // functions
        //! checks whether \c str starts with a path mark already
        static bool hasPathMark(const wchar_t *str);

    protected: // data
        //! \brief
        //! if necessary this contains the string data of the current
        //! object prepended with a path mark
        mutable ipl::wstring m_string_with_path_mark;

        //! \brief
        //!    this should be the same as MAX_PATH but MSDN doesn't say
        //!    that precisely enough thus we make sure by defining our own
        //!    constant.
        static const size_t S_WIN32_MAX_API_PATH = 248;

        /*
        *    This is a strange prefix-mark that can be used with
        *    certain Win32 file APIs to allow longer paths and
        *    disable interpretation of paths and stuff. It is
        *    uncertain to me what that means to us. It might be
        *    possible that not even relative path names are
        *    "interpreted" by the system any more then.
        *
        *    It seems that \\?\ is in ASCII i.e. we have to convert
        *    it into UTF16 to use it. As it can *only* be used with
        *    the unicode APIs, not the ASCII ones.
        *
        *    XXX after testing it turned out true that when using
        *    this path mark the system doesn't do *anything* with the
        *    path any more. Not even resolving relative paths. Thus
        *    this class needs to add some implicit magic to resolve
        *    relative paths if the S_WIN32_MAX_API_PATH is exceeded.
        *    This is not yet the case.
        */
        static const wchar_t S_DONTINTERPRET_PATH_MARK_UTF16[];
        //! length of S_DONTINTERPRET_PATH_MARK_UTF16 in characters (not
        //! bytes!), not including null terminator.
        static const size_t S_DONTINTERPRET_PATH_MARK_UTF16_LENGTH;
    };

}  // end of namespace osal

#endif
