/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_PATH_HXX
#define OSAL_PATH_HXX

#include <ipl_config.h>

#ifdef IPL_OS_POSIX
#    include "posix/PathDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/PathDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/PathDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal_dso.h>
#include <osal/UnicodeString.hxx>
#include <osal/Environment.hxx>
#include <osal/FileInfo.hxx>

#include <common/types/string.hxx>
#include <common/types/list.hxx>
#include <common/types/set.hxx>
#include <common/types/utility.hxx>
#include <common/types/memory.hxx> // ipl::allocator

namespace osal {

    template<typename CHAR_TYPE>
    const CHAR_TYPE* getPathLiteral() {
        return NULL;  // ???
    }

    // specialisations of getPathLiteral for char and wchar_t, implementation is in Path.cxx
    template<>
    OSAL_EXPORT
    const char* getPathLiteral<char>();

    template<>
    OSAL_EXPORT
    const wchar_t* getPathLiteral<wchar_t>();

    template<typename STRING_TYPE>
    STRING_TYPE getExecutableSuffix()
    {}

    // specialisations of getExecutableSuffix
    template<>
    OSAL_EXPORT
    ipl::string getExecutableSuffix<ipl::string>();

    template<>
    OSAL_EXPORT
    ipl::wstring getExecutableSuffix<ipl::wstring>();


    /**
    * \brief
    *    Specialization of a String Container for File System Paths

    *    This class allows typical operations on paths like making
    *    relative paths absolute, canonicalizing or normalizing a path
    *    etc.
    *
    *    Note that this class merely operates on the string data and
    *    doesn't care about actual file system content i.e. it doesn't
    *    very if the path points to a valid file system object or to a
    *    file or a directory etc.
    *
    *    Also note that this class is independent of the string encoding
    *    (char/wchar_t). For this functionality in OSAL we chose to use
    *    the wstring object for working with unicode. This is because
    *    working with the raw unicode data in e.g. UTF8 would make the
    *    raw path operations very complex as OSAL doesn't have a "smart"
    *    unicode handling class.
    *
    *    To overcome this problem we use the wide character variant of
    *    the STL string. For WIN32 based operating systems the wide
    *    character string is in UTF16, just like what osal::UnicodeString
    *    contains. For POSIX based operating systems, however, the wide
    *    character string is encoded in UTF32 and conversions from/to
    *    osal::UnicodeString need to be done.
    *
    *    This performance penalty is considered to be okay as working
    *    with Paths usually shouldn't pose a critical operation
    *    repetitively performed in applications. The details of unicode
    *    handling and ASCII handling are handled in derivations of this
    *    class Path and WidePath.
    **/
    template<typename CHAR_TYPE, typename CHAR_TRAITS = ipl::char_traits<CHAR_TYPE>,
        typename ALLOCATOR = ipl::allocator<CHAR_TYPE> >
    class BasicPath :
        public ipl::basic_string<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>
    {
    public: // constants
        //! \brief
        //! The path separator used for the platform you're
        //! currently running on. Plain ASCII character.
        static const CHAR_TYPE SEPARATOR =
            path_traits<CHAR_TYPE>::SEPARATOR;

        /**
        * \brief
        *     Maximum Length of any path in bytes

        *     This is the maximum length of a file system path in
        *     respect to the OSAL and native operating system APIs.
        *     This size already considers a terminating null
        *     character.
        *
        *     Please take note that is is the length of a path in
        *     *bytes*, not in characters. It is not possible to
        *     determine a generic maximum length in characters in
        *     encodings like UTF8. You could choose a pessimistic
        *     approach for UTF8 and consider MAX_PATH_LENGTH / 4 as
        *     the maximum number of characters.
        *
        *     It is probably best to compare the size of a unicode
        *     path in bytes against this constant.
        * \note
        *     On Win32 you can have longer paths than this
        *     contants suggest but it requires a bare-metal apporach
        *     using a special path prefix that causes the system to
        *     cease interpreting the path which results in e.g.
        *     relative paths not being resolved any more and similar
        *     things.
        *
        *     OSAL might choose to transparently do this handling for
        *     the user in case a path is longer than this constant. It
        *     will introduce overheader, however. Also it might
        *     introduce side effects as OSAL then needs needs to
        *     evaluate the current working directory so resolve
        *     relative paths itself.
        **/
        static const size_t MAX_PATH_LEN =
            path_traits<CHAR_TYPE>::MAX_PATH_LEN;

        /**
        * \brief
        *     Maximum Length of a Path Component in bytes

        *     The same rules as for \c MAX_PATH_LEN account here, too.
        *     Use osal::FileSys::maxComponentLength() for individual
        *     file system limits. This size already considers a
        *     terminating null character.
        **/
        static const size_t MAX_COMPONENT_LEN =
            path_traits<CHAR_TYPE>::MAX_COMPONENT_LEN;
    protected: // types
        typedef ipl::basic_string<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>
            parent_string;
    public: // types
        typedef CHAR_TRAITS traits_type;
        typedef typename traits_type::char_type value_type;
        typedef typename parent_string::size_type size_type;

    public: // member functions

        //! Construct an empty path object
        BasicPath() :
            parent_string() { }

        /**
        * \brief
        *    Construct a Path Object from Plain c-string \c s
        **/
        BasicPath(const value_type *s) :
            parent_string(s) { }

        /**
        * \brief
        *    Construct a Path Object from string Object \c s
        **/
        BasicPath(const parent_string &s) :
            parent_string(s) { }

        /**
        * \brief
        *    Return the File Extension this Object Points to

        *    The file extension is usually a short postfix of files
        *    to indicate the nature of its contents (e.g. ".txt" for
        *    text files). The separator for this is the dot character
        *    '.'.
        *
        *    While on Win32 systems it is pretty standard to have
        *    extension of exactly three characters for nearly all
        *    files on Unix-like systems we have many files without
        *    any extensions at all. Also when extensions are used
        *    there be used multiple parts (e.g. ".tar.gz").
        *
        *    The parameter \c only_last determines wheter only the
        *    last part of the extension is given (in the case of
        *    ".tar.gz" you would get "gz") or whether the complete
        *    extension starting at the first separator is given
        *    ("tar.gz" in the example).
        *
        *    Note that it may also happen that files have dots in the
        *    filenames themselves. Also on Unix-like systems it is
        *    common to have files and directories starting with a dot
        *    to be considered hidden.
        *
        *    This function will simply lookup the postfix according
        *    to the \c only_last setting from the basename of the
        *    current path as returned by getBasename().
        * \return
        *    A string containing the file extension according to the
        *    \c only_last setting. The extension will not contain a
        *    leading dot. If the current path is empty or the current
        *    path basename doesn't contain an extension or if there
        *    is a single extension separator at the end of the
        *    filename the an empty string will be returned.
        **/
        parent_string getExtension(
                const bool only_last = false
                ) const
        {
            parent_string base = this->getBasename();

            size_type separator;

            if( only_last )
                separator = base.find_last_of( EXT_SEPARATOR );
            else
                separator = base.find_first_of( EXT_SEPARATOR );

            if( separator != this->npos && separator != base.size() - 1)
                return base.substr( separator + 1 );

            return parent_string();
        }

        /**
        * \brief
        *    Returns the Filename Component of the Current Path

        *    The filename component is considered the last component
        *    of the current path.  Note that even if the current path
        *    has a trailing Path::SEPARATOR character (which usually
        *    means that a directory is denoted instead of a regular
        *    file) the last component will be returned, the trailing
        *    SEPARATOR being removed.
        *
        *    If the current path consists only of one component then
        *    that is returned regardless of any leading or trailing
        *    SEPARATOR characters or whether this is an absolute or
        *    relative path.
        *
        *    If the current path is empty then an empty string is
        *    returned. This function does *not* check whether the
        *    returned basename actually is an existing file at that
        *    file system location.
        * \param[in] cut_extension
        *    If set to true then cut a possible existing file name
        *    extension from the basename before it is returned.
        *    currently not implemented
        **/
        parent_string getBasename(
            const bool cut_extension = false) const
        {
            return this->split().second;
        }

        /**
        * \brief
        *    Returns the Directory Component(s) of the Current Path

        *    The directory components of a Path are considered to be
        *    all but the last path component.
        *
        *    If the current Path is the root Path or a file system
        *    entry point then that is returned unmodified.
        *
        *    If the current Path is relative and consists of only one
        *    path component (i.e. it is simply a filename without any
        *    directory specifications) then "." for the current
        *    working directory is returned.
        *
        *    Any trailing SEPARATOR characters will be stripped, any
        *    remaining multiple SEPARATOR characters will be ignored.
        **/
        BasicPath getDirname() const
        {
            return this->split().first;
        }

        /**
        * \brief
        *    Return the Individual Path Components in a List

        *    The returned list will contain the name of each path
        *    component (i.e. each directory and filename without
        *    separators.
        *
        *    If there is an entry point present in the current Path
        *    then first component in the returned list will denote it
        *    i.e. "/" on Unix-like systems and the drive letter
        *    prefix on WinPC.
        *
        *    The other returned components are in the order of the
        *    path components as they appear in the current path.
        **/
        ipl::list<parent_string> getComponents() const
        {

            ipl::list<parent_string> comps;

            if( this->empty() )
                return comps;

            const BasicPath entry = this->getEntryPoint();

            // if there are no separators at all then add the single component
            if( this->find_first_of(SEPARATOR) ==
                    ipl::string::npos &&
                    this->size() > entry.size() )
            {
                comps.push_front(
                        this->substr( entry.size() ) );
            }

            // indices to the individual path components
            //
            // to the end of the current component, skip trailing
            // separators
            size_type comp_end =
                this->find_last_not_of(SEPARATOR);
            // to the last separator in the leftover path
            size_type comp_start =
                this->find_last_of(SEPARATOR, comp_end - 1);

            if( comp_start != ipl::string::npos )
                comp_start++;

            // as long as we don't touch the entry point part...
            while( comp_start != ipl::string::npos &&
                    comp_start >= entry.size() &&
                    comp_end != ipl::string::npos )
            {
                // skip empty parts (redundant separators)
                if( (comp_end >= comp_start) )
                    comps.push_front( this->substr(
                                comp_start,
                                comp_end - comp_start + 1) );

                // skip one component forward
                comp_end = this->find_last_not_of(
                        SEPARATOR,
                        comp_start - 2);

                if( comp_start > 1 && comp_start > entry.size() )
                {
                    if( comp_end )
                        comp_start = this->find_last_of(
                                SEPARATOR,
                                comp_end - 1)
                            + 1;
                    else
                        comp_start = comp_end;
                }
                else
                {
                    comp_start = ipl::string::npos;
                }
            }

            // first comes a possible entry point
            if( ! entry.empty() )
                comps.push_front( this->getEntryPoint() );

            return comps;
        }

        /**
        * \brief
        *    Remove the last Path Component

        *    Truncates the current Path by one component. If only one
        *    component is left then an empty path remains.
        *
        *    Trailing SEPARATORs will be stripped.
        **/
        BasicPath& removeComponent()
        {
            if( this->empty() )
                return *this;

            const size_type entry_len =
                this->getEntryPoint().size();

            if( this->size() == entry_len )
            {
                // entry point is the last component, let's
                // clean up
                this->clear();
                return *this;
            }

            // first remove any trailing slashes
            while( this->size() > entry_len
                    && *(this->end() - 1) == SEPARATOR )
            {
                this->erase( this->size() - 1 );
            }

            // index to last separator
            ipl::string::size_type comp_sep =
                this->find_last_of(SEPARATOR);

            // no more separator before last component, i.e. either
            // relative path that consisted of only one component or
            // absolute path that consisted of the root alone
            if( comp_sep == ipl::string::npos )
            {
    #ifdef IPL_OS_WINPC
                // on WinPC we have relative paths with a drive
                // letter specification i.e. an entry spec. is
                // there but it is no absolute path. In that
                // case there is no separator present at the
                // start of the path: "C:somedir"
                //
                // we want to keep the entry point in that case
                // thus check against that condition
                if( entry_len )
                    this->erase(entry_len);
                else
    #endif
                    this->clear();
            }
            else
            {
                // first iterate backwards over all
                // trailing separators; note that comp_sep always
                // points to a character that is SEPARATOR
                while(comp_sep > 0 && this->at(comp_sep - 1) == SEPARATOR)
                    --comp_sep;

                // check if we're about to remove all or
                // part of the root in that case safe the
                // trailing separator
                if( comp_sep == entry_len - 1 )
                    ++comp_sep;

                // strip of that last component, including
                // trailing separator (if not part of the root)
                this->erase( comp_sep );
            }

            return *this;
        }

        /**
        * \brief
        *    Adds the given String as the new last Component

        *    The given string \c s will simply be appended to the
        *    current path. If \c s is not empty and has no trailing
        *    SEPARATOR character then a SEPARATOR character will be
        *    inserted between the current path and the to be appended
        *    \c s.
        *
        *    \c s is allowed to contain more than one path component
        *    but should not be an absolute path. If you want to
        *    assign a new absolute path use operator=(const
        *    ipl::string&).
        *
        *    This function will not remove any redundant SEPARATOR
        *    characters already present in the current path or \c s.
        **/
        BasicPath& addComponent(const parent_string &s)
        {
            return addComponent(s.c_str());
        }

        /**
        * \brief
        *    Adds the given Strings as the new last Component
        * \see
        *    addComponent(const ipl::string&)
        **/
        BasicPath& addComponent(const value_type *s)
        {
            const size_type
                entry_len = this->getEntryPoint().size();

            if( this->size() > entry_len &&
                *(this->end() - 1) != SEPARATOR )
            {
                this->push_back(SEPARATOR);
            }

            this->append(s);

            return *this;
        }

        /**
        * \brief
        *    Get a Syntactically Correct Path

        *    Removes any detectable syntax errors in the current
        *    path. Currently this covers any duplicate seperator
        *    characters and trailing separator characters.
        **/
        BasicPath getSane() const
        {
            BasicPath ret;

            if( this->empty() )
                return ret;

            // positions of the current separator character and the
            // last separator character

            ipl::string::size_type cur = this->find_first_of(SEPARATOR);
            ipl::string::size_type last = cur;

            if( cur != ipl::string::npos )
            {
                // append the first part of the string until the
                // first separator is hit
                ret.append( this->substr(0, cur + 1) );
            }
            else
            {
                // no separators at all there, return as is
                ret = *this;
                return ret;
            }

            for( cur = this->find_first_of(SEPARATOR, last + 1);
                    cur != ipl::string::npos;
                    last = cur, cur = this->find_first_of(
                        SEPARATOR,
                        cur + 1) )
            {
                // if more than one character between
                // separators, append that part
                if( cur != last + 1 )
                {
                    ret.append( this->substr(
                                last + 1,
                                cur - last) );
                }
            }

            if( last < this->length() - 1 )
            {
                ret.append( this->substr(
                            last + 1,
                            ipl::string::npos ) );
            }

            // remove possibly trailing separator character, only if
            // not part of entry point
            if( *(ret.end() - 1) == SEPARATOR &&
                    ret.size() > ret.getEntryPoint().size() )
            {
                ret.erase( ret.size() - 1 );
            }

            return ret;
        }

        /**
        * \brief
        *     Get a Safe Path, Complex Variant

        *     A safe path is a path that doesn't contain certain
        *     characters that are considered potentially dangerous
        *     when automatically or interactively processing the path.
        *
        *    Potential dangers include the following:
        *
        *    * when uncarefully processing the path side-effects can
        *    occur that cause a different path to be worked on than
        *    intended. E.g. the application may be tricked into
        *    modifying system files or into escaping a given
        *    application root directory.
        *    * when a user works with the path then he may be
        *    confused (e.g. a line break is contained in the path
        *    making it look like two separate paths)
        *    * when the file is transferred onto another machine or
        *    file system then the filename can't be displayed there
        *    correctly any more. This may result in being unable to
        *    transfer the file to the target machine or even worse,
        *    the file is transferred but cannot be accessed there or
        *    corrupts the system etc.
        *
        *    This is a more generic variant of the getSafe()
        *    function. It allows you to remove a custom set of
        *    characters from the current path.
        * \param[in]
        *     chars_to_replace A set of characters that are to be
        *     replaced or removed from the path
        * \param[in]
        *     replace_char A character that is to take the place of
        *     any characters that match \c chars_to_replace or one of
        *     the default characters that are considered harmful. If
        *     this is zero then characters won't be replaced but
        *     removed from the current path.
        * \param[in]
        *     replace_defaults If set to \c true then additionally to
        *     the characters defined by \c chars_to_replace a default
        *     set of characters will be replaced/removed that are
        *     considered harmful by the implementation. Currently this
        *     set is compiled of any characters from the traditional
        *     ASCII set that are not one of the following: [0-9],
        *     [A-Z], [a-z], '.', '_'. This avoids any special
        *     characters that influence path interpretation, that may
        *     be interpreted by shells/programming languages or
        *     confusing whitespace.
        * \return
        *     A new path object that fulfills the given criteria for a
        *     safe path.
        **/
        BasicPath getSafe(
            const ipl::set<CHAR_TYPE> chars_to_replace,
            const CHAR_TYPE replace_char = CHAR_TRAITS::to_char_type(0),
            const bool replace_defaults = true) const
        {
            BasicPath ret;
            ret.reserve( this->size() );

            ret.append( getEntryPoint() );

            const bool erase_chars =
                replace_char == CHAR_TRAITS::to_char_type(0);

            for(size_type i = getEntryPoint().size(); i < this->size(); ++i)
            {
                const CHAR_TYPE c = this->operator[](i);
                bool replace = chars_to_replace.find(c) != chars_to_replace.end();

                if( !replace && replace_defaults &&
                        // withing ASCII range
                        CHAR_TRAITS::to_int_type( c ) < 0x7F )
                {
                    if( (! CHAR_TRAITS::lt( c, CHAR_TYPE('a'))) &&
                            CHAR_TRAITS::lt( c, CHAR_TYPE('z' + 1)) )
                    {
                        // good char, do not replace
                    }
                    else if( (! CHAR_TRAITS::lt( c,CHAR_TYPE('A'))) &&
                            CHAR_TRAITS::lt( c, CHAR_TYPE('Z' + 1)) )
                    {
                        // good char, do not replace
                    }
                    else if( (! CHAR_TRAITS::lt( c, CHAR_TYPE('0'))) &&
                            CHAR_TRAITS::lt( c, CHAR_TYPE('9' + 1)) )
                    {
                        // good char, do not replace
                    }
                    else if( CHAR_TRAITS::eq( c, CHAR_TYPE('.'))
                            || CHAR_TRAITS::eq( c, CHAR_TYPE('_'))
                            || CHAR_TRAITS::eq( c, SEPARATOR )
                        )
                    {
                        // good char, do not replace
                    }
                    else
                    {
                        replace = true;
                    }
                }

                if( replace )
                {
                    if( !erase_chars )
                    {
                        ret.append( 1, replace_char );
                    }
                }
                else
                {
                    ret.append( 1, c );
                }
            }

            return ret;
        }

        /**
        * \brief
        *     Get a Safe Path, Simple Variant

        *     Replace any characters considered harmful by the
        *     implementation with \c replace_char and return the
        *     resulting path. If \c replace_char is zero then matching
        *     characters won't be replaced but removed.
        * \see
        *     getSafe(const ipl::set<CHAR_TYPE>, const CHAR_TYPE,
        *     const bool)
        * \return
        *     A new path object that fulfills the criteria for a safe
        *     path.
        **/
        BasicPath getSafe(
            const CHAR_TYPE replace_char =
                CHAR_TRAITS::to_char_type(0))
        {
            return this->getSafe(
                ipl::set<CHAR_TYPE>(),
                replace_char,
                true);
        }

        /**
        * \brief
        *    Get a Normalized Version of the Current Path

        *    A normalized path contains a well-known separator
        *    character independent of the actual operating system.
        *    This is the '/' character.
        *
        *    Thus this function converts all SEPARATOR characters to
        *    this well-known separator. Note that this does not cover
        *    the entry point component for absolute paths. I.e. it's
        *    no way to get completely platform-independent, absolute
        *    paths.
        *
        *    Note that the returned path can't be fed to other member
        *    functions any more as they expect the platform-specific
        *    SEPARATOR character.
        **/
        parent_string getNormalized() const
        {
            // nothing to do if we already have the right separator
            if( SEPARATOR == traits_type::to_char_type('/') ) // BRANCH_COVERAGE_UNTESTABLE
            {
                return *this;
            }
            else
            {
               // On Win32 we don't want to replace the backslash of
               // the drive spec.
               parent_string ret = *this;

               for(
                  ipl::string::size_type sep = ret.find_first_of(
                      SEPARATOR,
                      this->getEntryPoint().length() );
                  sep != ipl::string::npos; // BRANCH_COVERAGE_UNTESTABLE
                  sep = ret.find_first_of(SEPARATOR, sep + 1) )
               {
                  ret[sep] = traits_type::to_char_type('/');
               }

               return ret;
            }
        }

        /**
        * \brief
        *    Get a Native Version of the given normalized path

        *    This function converts any occurences of the well-known
        *    separator in \c normalized_path with the
        *    platform-specific SEPARATOR character. I.e. this
        *    function performs the inverse operation of
        *    getNormalized().
        **/
        static BasicPath fromNormalized(
            const parent_string &normalized_path
            )
        {
            const CHAR_TYPE NORMALIZED_SEPARATOR =
                traits_type::to_char_type('/');

            // nothing to do if we already have the right separator
            if( SEPARATOR == NORMALIZED_SEPARATOR )
            {
                return normalized_path;
            }
            else
            {
               BasicPath ret = normalized_path;

               for(
                  ipl::string::size_type sep =
                      ret.find_first_of(NORMALIZED_SEPARATOR);
                  sep != ipl::string::npos;
                  sep = ret.find_first_of(NORMALIZED_SEPARATOR,
                      sep + 1) )
               {
                  ret[sep] = SEPARATOR;
               }

               return ret;
            }
        }

        /**
        * \brief
        *     Looks into the PATH environment variable for the first
        *     executable matching \c name

        *     On most systems there exists a PATH environment variable
        *     that contains a list of directories in the system where
        *     applications can look into in case a user doesn't
        *     provide the full path to program.
        *
        *     This functions cares for dealing with the different
        *     structures of the PATH environment variable on different
        *     systems. It looks into the list of directories front to
        *     back for entries matching \c name. \c name is also
        *     extended with osal::ProcessTNG::ExecutableSuffix, if
        *     required. On POSIX systems only entries that have an
        *     executable bit set will be considered. The first
        *     matching entry will be returned.
        *
        *     If \c name should happen to be an absolute path
        *     specification than only \c name is considered and the
        *     PATH environment variable is not used.
        * \return
        *     The first executable matching \c name or an empty string
        *     in case no such executable could be determined
        **/
        static BasicPath lookupExecutable(
            const BasicPath &name)
        {
            // first determine whether a executable suffix is required and
            // present
            parent_string suffix = getExecutableSuffix<parent_string>();
            bool have_suffix = suffix.length() != 0;

            osal::FileInfo fi;

            // first check if name is an absolute or relative path
            // specification instead of a pure basename
            //
            // if so, then if it is existing in this form already and
            // executable return that
            const bool is_composite = name.find_first_of( SEPARATOR ) !=
                name.npos;

            for( int i = 0; i < 2; i++ )
            {
                BasicPath p(name);

                // if the file did not exist without suffix,
                // try again with suffix
                if( i == 1 )
                {
                    if( ! have_suffix )
                        continue;

                    p.append(suffix);
                }

                fi = osal::FileInfo(UnicodeString(p));

                if( fi.isValid() &&
                        fi.getAccess().canExecute() )
                {
                    return p;
                }

                ipl_error.ack();
            }

            // if it contains separators then it's no basename,
            // we're not searching the environment variable
            if( is_composite )
                return BasicPath();

            // only if basename isn't a composite check the PATH variable

    #ifdef IPL_OS_WIN32
            const CHAR_TYPE entry_sep = traits_type::to_char_type(';');
    #else
            const CHAR_TYPE entry_sep = traits_type::to_char_type(':');
    #endif

            BasicPath path = osal::Environment::getVariable(
                    getPathLiteral<CHAR_TYPE>() );
            typename BasicPath::size_type prev_pos = 0, sep_pos = 0;

            do
            {
                prev_pos = sep_pos;
                sep_pos = path.find_first_of( entry_sep, sep_pos );

                BasicPath dir = path.substr(prev_pos, sep_pos - prev_pos );

                if( dir.empty() )
                    continue;

                for( int i = 0; i < 2; i++ )
                {
                    dir.addComponent(name);

                    // if the file did not exist without suffix,
                    // try again with suffix
                    if( i == 1 )
                    {
                        if( ! have_suffix )
                            continue;

                        dir.append(suffix);
                    }

                    fi = osal::FileInfo(UnicodeString(dir));

                    //::printf("considering \"%s\"\n", dir.c_str());

                    if( fi.isValid() && fi.getAccess().canExecute() )
                    {
                        return dir;
                    }

                    ipl_error.ack();
                    dir.removeComponent();
                }
            }
            while( sep_pos != path.npos && ++sep_pos );

            return BasicPath();
        }

        /**
        * \brief
        *    Returns the File System Entry Point as Specified in the
        *    Current Path

        *    If the current path specification contains an entry
        *    point specification then that entry point is returned.
        *    If there is no such specification than an empty string
        *    is returned.
        *
        *    In contrast to findEntryPoint() this function does not
        *    attempt to retrieve the entry point by resolving the
        *    current path. Also this function does not canonicalize
        *    the entry point. It simply returns exactly that part of
        *    the entry point that is present at the start of the
        *    current path.
        **/
        inline BasicPath getEntryPoint() const;

        /**
        * \brief
        *    Returns whether the Current Path is an Absolute Path

        *    A path is considered absolute if it starts with a file
        *    system entry point.  Otherwise the path is considered to
        *    be relative to the current working directory of the
        *    process.
        *
        *    If the current path is empty, false is returned.
        * \return
        *    \c true if the current path is an absolute path
        *    specification, \c false otherwise
        **/
        inline bool isAbsolute() const;

        /**
        * \brief
        *    Returns whether the Current Path is a Relative Path

        *    A path is considered relative if it doesn't start with a
        *    file system entry point.
        *
        *    If the current path is empty, true is returned. The
        *    empty path is considered to denote the current working
        *    directory of the process.
        *
        *    Note that this function returning true might also happen
        *    if the current path is malformed.
        * \return
        *    \c true if the current path is a path specification
        *    relative to the current working directory, \c false
        *    otherwise
        **/
        bool isRelative() const
        { return !this->isAbsolute(); }
    protected: // functions

        /**
        * \brief
        *    Split up the Current Path in Dirname and Basename
        *    Components
        * \return
        *    A pair containing the dirname of the current path as
        *    first element and the basename of the current path as
        *    second element.
        **/
        ipl::pair<parent_string, parent_string> split() const
        {
            ipl::pair<parent_string, parent_string> ret;

            if( this->empty() )
                return ret;

            ret.first = *this;

            // possibly existing entry point, empty if none there
            const parent_string ep = this->getEntryPoint();

            // cut off possibly trailing separators, but don't touch
            // entry point spec., if there
            while( ret.first.size() > ep.size() &&
                    *(ret.first.end() - 1) == SEPARATOR )
            {
                ret.first.erase( ret.first.size() - 1 );
            }

            // in this case we only have the entry point around,
            // return the entry point as first and second
            if( ep.size() == ret.first.size() )
            {
                ret.first = ep;
                ret.second = ret.first;
                return ret;
            }

            size_type last_sep =
                ret.first.find_last_of(SEPARATOR);

            // no more separators, return the thing as it is
            if( last_sep == parent_string::npos && ep.empty() )
            {
                ret.second = ret.first;
                ret.first = CHAR_TRAITS::to_char_type('.');
                return ret;
            }
            else if( last_sep == ipl::string::npos )
            {
                // we have an entry point, no more separators
                // but something more than the entry point
                // (relative path spec. on win32 like this:
                // c:somedir)
                last_sep = ep.size() - 1;
            }

            // return the string from the last separator to the end
            // of the string
            ret.second = ret.first.substr( last_sep + 1 );
            // strip off base from path
            ret.first.erase( last_sep + 1 );

            // cut off possibly trailing separators, but don't touch
            // entry point spec., if there
            while( ret.first.size() > ep.size() &&
                    *(ret.first.end() - 1) == SEPARATOR )
            {
                ret.first.erase( ret.first.size() - 1 );
            }

            if( ret.first.empty() )
                ret.first = this->getEntryPoint();

            return ret;
        }

    public: // static functions

    private:
        // file extension separator
        static const CHAR_TYPE EXT_SEPARATOR;
    }; // end class

    /**
    * \brief
    *     Specialization of BasicPath for ASCII paths

    *     This class adds ASCII specific operations to the BasicPath
    *     class. The additional member functions provided also might need
    *     to evaluate the current working directory, in contrast to what
    *     BasicPath's member functions do.
    *
    *    E.g. getAbsolute() needs to access the cwd information to do its
    *    job. This means that if the cwd changes in unexpectedly (e.g. by
    *    means of other threads calling osal::FileSys::changeWD()) then
    *    you may get unexpected results accordingly.
    **/
    class OSAL_EXPORT Path :
        public BasicPath<char>
    {
    public:
        //! see BasicPath()
        Path() :
            BasicPath<char>() { }


        //! \see BasicPath(const value_type *)
        Path(const char *s) :
            BasicPath<char>(s) { }

        //! \see BasicPath(const parent_string &)
        Path(const parent_string &s) :
            BasicPath<char>(s) { }

        Path& operator=(const ipl::string &other)
        {
            BasicPath<char>::parent_string::operator=(other);

            return *this;
        }

        Path& operator=(const char *s)
        {
            BasicPath<char>::parent_string::operator=(s);

            return *this;
        }

        Path& operator=(const char c)
        {
            BasicPath<char>::parent_string::operator=(c);

            return *this;
        }

        /**
        * \brief
        *    Get an Absolute Path for the Current Path

        *    If the current Path is a relative Path then this
        *    function returns an absolute Path for the same file
        *    system object. Otherwise the current Path is returned
        *    unmodified.
        *
        *    Thus function will not resolve any symbolic links
        *    present in the current path. Also any syntax errors,
        *    redundant path components, relative path components like
        *    ".." or "." won't be touched. It will simply be returned
        *    a path that is independent of the current working
        *    directory.
        *
        *    If an error should occur while trying to determine the
        *    current working directory for the current path then an
        *    empty path is returned. No error is raised in this case.
        * \note
        *    To perform thus functionality the current working
        *    directory needs to be queried from the system (via
        *    osal::FileSys::currentWD()). As this is a process wide
        *    datum it is subject to parallel modification by other
        *    threads (e.g. via osal::FileSys::changeWD()).
        **/
        Path getAbsolute(
            ) const;

        /**
        * \brief
        *    Get a Canonicalized Version of the Current Path

        *    The canonicalized path has the following properties:
        *
        *    - it is an absolute path
        *    - it contains no symlinks on UNIX-like systems
        *    - it contains no redundant relative components like "."
        *    or ".."
        *    - it is syntactically correct (i.e. non-fatal errors
        *    like duplicate or redundant seperators are removed)
        *
        *    This operation only succeeds if the current path points
        *    to an actual file system object. Otherwise an empty
        *    string is returned. This is because the function needs
        *    to resolve an relative or symbolic path components which
        *    only can be done if the path actually exists in the
        *    system.
        * \note
        *    This functionality might require invocation of system
        *    calls and interpret the current working directory. As
        *    such it is subject to parallel modification of the
        *    process's working directory by other threads.
        *
        *    Also it might happen that the operation fails. In this
        *    case an empty path is returned. No error is raised in
        *    that case.
        **/
        Path getCanonicalized() const;

        /**
        * \brief
        *    Determine the File System Entry Point for the Current
        *    Path

        *    The entry point is the root path component for the
        *    current path.
        *
        *    On UNIX-like systems there is a single entry point for
        *    all file system locations ('/'). Absolute paths always
        *    have an entry point specified and relative paths never
        *    have entry points.
        *
        *    On WinPC systems the entry point may differ between
        *    paths (drive letters) and may also be present on
        *    relative paths (in the form "X:somedir", which means the
        *    directory "somedir" in the current working directory on
        *    drive X).
        *
        *    For UNIX-like systems this function always returns '/'.
        *
        *    For WinPC systems this function needs to scan the
        *    current path contents. In case of a drive letter being
        *    present at the start of the path that drive letter is
        *    returned. If no drive letter is specified an attempt
        *    will be made to retrieve the absolute path of the
        *    current path via getAbsolute() and the entry point for
        *    that path will be returned. If getAbsolute() returns an
        *    empty string than this function as well returns an empty
        *    string.
        *
        *    The WinPC entry point, if found, will be in the form
        *    "X:\", where X is a varying drive letter.
        * \see
        *    FileSys::getEntryPoints()
        **/
        inline Path findEntryPoint() const;
    };

    /**
    * \brief
    *     Specialization of BasicPath for unicode paths

    *     see Path for basic explanation of this specializatoin.
    *
    *     This class also adds a constructor that takes an
    *     osal::UnicodeString and a conversion operator into an
    *     osal::UnicodeString for being able to transparently integrate
    *     the unicode path handling with the rest of the unicode APIs
    *     within OSAL.
    **/
    class OSAL_EXPORT WidePath :
        public BasicPath<wchar_t>
    {
    public:
        //! see BasicPath()
        WidePath() :
            BasicPath<wchar_t>(),
            m_valid(true) { }


        //! \see BasicPath(const value_type *)
        WidePath(const wchar_t *s) :
            BasicPath<wchar_t>(s),
            m_valid(true) { }

        //! \see BasicPath(const parent_string &)
        WidePath(const parent_string &s) :
            BasicPath<wchar_t>(s),
            m_valid(true) { }

        /**
        * \brief
        *     Create a WidePath object from an ASCII string

        *     This constructor converts the ASCII-only string into a
        *     WidePath object.
        * \param[in] chars
        *     Number of characters (not including null terminator) in
        *     \c s. If this is zero then the length of \c s will be
        *     calculated.
        **/
        explicit WidePath(const char *s, const size_t chars = 0);

        /**
        * \brief
        *     Create a WidePath object from the given UnicodeString
        *     object

        *     The given string \c ucs will be converted, if necessary,
        *     into a wide-character representation. This will be the
        *     initial path for the new WidePath object.
        *
        *     As the conversion of \c ucs into a wide character string
        *     may fail the isValid() function informs you about any
        *     errors. Also on error the resulting object will be
        *     empty.
        **/
        WidePath(const osal::UnicodeString &ucs);

        bool isValid() const
        { return m_valid; }

        WidePath& operator=(const WidePath &other)=default;
        
        WidePath& operator=(const ipl::wstring &other)
        {
            BasicPath<wchar_t>::parent_string::operator=(other);
            m_valid=true;

            return *this;
        }

        WidePath& operator=(const wchar_t *s)
        {
            BasicPath<wchar_t>::parent_string::operator=(s);
            m_valid=true;

            return *this;
        }

        WidePath& operator=(const wchar_t c)
        {
            BasicPath<wchar_t>::parent_string::operator=(c);
            m_valid=true;

            return *this;
        }

        //! \see Path::getAbsolute() const
        WidePath getAbsolute(
            ) const;

        //! \see Path::getCanonicalized()
        WidePath getCanonicalized() const;

        /**
        * \brief
        *    Determine the File System Entry Point for the Current
        *    Path
        * \see
        *     Path::findEntryPoint()
        **/
        inline WidePath findEntryPoint() const;

        //! get an osal::UnicodeString for this WidePath object
        operator osal::UnicodeString() const
        {
            return osal::UnicodeString(*(const parent_string *)this);
        }

        operator ipl::string() const
        {
            return osal::UnicodeString(*(const parent_string *)this);
        }
    protected:
        bool m_valid;
    };

    /*
    *    the following three are required for some gcc version (starting
    *    from maybe 4.0 ranging to somewhen around 4.3.3) to avoid
    *    getting complaints about these constant being explicitly
    *    instantiated but no definitions being available
    */

    template<typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>
    const CHAR_TYPE
    BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::SEPARATOR;

    template<typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>
    const size_t
    BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::MAX_PATH_LEN;

    template<typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>
    const size_t
    BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::MAX_COMPONENT_LEN;

    template<typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>
    const CHAR_TYPE
    BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::EXT_SEPARATOR =
        traits_type::to_char_type('.');

}  // end of namespace osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/Path.inl"
#elif defined IPL_OS_WINPC
#    include "win32/Path.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
