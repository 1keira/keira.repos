/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_DIRECTORY_HXX
#define UTIL_DIRECTORY_HXX

#include <ipl_config.h>

#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <osal/Directory.hxx>
#include <osal/FileSys.hxx>
#include <osal/Path.hxx>
#include <util/util_dso.h>
#include <util/UnicodeString.hxx>

namespace util {

    /**
    * \brief
    *    Enhance Directory access with directory tree handling
    *    functionality.
    *    This class adds some comfort features to osal::Directory.
    *
    *    It allows for browsing the directory tree, entering and leaving
    *    directories, scanning directories according to primitive regular
    *    expressions, get ready to use directory listing containers etc.
    **/
    class UTIL_EXPORT Directory :
        public osal::Directory
    {
    public:
        /**
        * \brief
        *     Create an Empty, Invalid Directory
        **/
        Directory() IPL_NOEXCEPT : m_first_entry(false), m_has_error(false)
        { };

        /**
        * \brief
        *    Calls osal::Directory constructor for \c path

        *    If \c path is a relativ path specification then the
        *    constructor makes the path absolute for easier
        *    processing logic later on. Thus the current working
        *    directory will be evaluated.
        * \see
        *    osal::Directory
        * \errorindicator
        *    via osal::Directory::isValid()
        **/
        inline Directory(const ipl::string &path) IPL_NOEXCEPT;

        //! unicode variant of Directory(const ipl::string&)
        inline Directory(const osal::UnicodeString &path) IPL_NOEXCEPT;

        /**
        * \brief
        *    Selects the next entry of the current directory opened
        * \errorindicator
        *     Additionally via hasError()
        * \see
        *    osal::Directory::next()
        **/
        int_fast8_t next() IPL_NOEXCEPT
        {
            if (! this->isValid() )
            {
                m_has_error = true;
                return -1;
            }
            m_first_entry = false;
            const int_fast8_t ret = ::osal::Directory::next();
            m_has_error = ret < 0;
            return ret;
        }

        /**
        * \brief
        *    Returns true if the currently selected entry is a
        *    directory, false otherwise
        * \note
        *    On error false is returned, no error is raised. (error
        *    would be if no FileInfo can be constructed).
        **/
        inline bool isDir() const IPL_NOEXCEPT;

        /**
        * \brief
        *    Returns a vector containing all directory entries of the
        *    current directory

        *    Calls rewind(), puts every curEntry() into an
        *    ipl::vector until next() returns false().
        *
        *    After return of the function the current entry will be
        *    the last entry of the directory (i.e. next() returns
        *    false). Use rewind() if you want to get to the first
        *    position again.
        * \errorindicator
        *     If reading the directory contents fails at some point
        *     then whatever contents could be read will be returned in
        *     the vector and hasError() returns \c true.
        * \errors
        *     The errors described at osal::Directory::next() can
        *     occur.
        **/
        ipl::vector<ipl::string> getListing() IPL_NOEXCEPT;

        /**
        * \brief
        *    Returns a listing like getListing() but sorted in
        *    alphabetical order
        * \see
        *     getListing()
        **/
        ipl::vector<ipl::string> getSortedListing() IPL_NOEXCEPT;

        /**
        * \brief
        *    Returns entries in the current directory that match \c
        *    pattern and \c type

        *    Calls getListing() to perform the search i.e. after
        *    return of the function the last entry of the directory
        *    will be selected.
        * \param[in] pattern
        *    pattern the searched entries need to match. May contain
        *    a _single_ wildcard (i.e.  asterisk, '*').
        * \param[in] type
        *    Types of directory entries to return. If set to
        *    ENTRY_TYPE_END then all types will be returned.
        * \param[in] sort
        *    Whether to return matching entries alphabetically sorted
        *    or not.
        * \errorindicator
        *     If reading the directory contents fails at some point
        *     then whatever matching entries could be read will be
        *     returned in the vector and hasError() returns \c true.
        * \errors
        *     The errors described at osal::Directory::next() can
        *     occur.
        **/
        ipl::vector<ipl::string> search(const ipl::string &pattern,
            const osal::FileInfo::EntryType type =
                osal::FileInfo::ENTRY_TYPE_END,
            const bool sort = false) IPL_NOEXCEPT;

        /**
        * \brief
        *    Returns true in case the current directory is the root
        *    directory of the filesystem

        *    This information helps to identify whether another
        *    climb() call is possible or not.
        **/
        bool isRoot() const IPL_NOEXCEPT;

        /**
        * \brief
        *    Return a new Directory object representing the currently
        *    selected directory entry

        *    This is only possible if the current directory entry is
        *    of type DIRECTORY.
        * \errorindicator
        *    on error the returned object is not valid i.e. isValid()
        *    returns false.
        * \errors
        *    the errors defined at osal::Directory() can occur.
        **/
        util::Directory subdir() const IPL_NOEXCEPT;

        /**
        * \brief
        *    Return a new Directory object representing the parent
        *    directory of the current directory.

        *    This is only possible if the current directory is not
        *    the root directory.
        * \errorindicator
        *    on error the returned object is not valid i.e. isValid()
        *    returns false.
        * \errors
        *    ipl::CommonError with IDs:
        *
        *    - PAR_OUT_OF_RANGE if the current directory is the root
        *    directory
        *
        *    the errors defined at osal::Directory() can also occur.
        **/
        util::Directory pardir() const IPL_NOEXCEPT;

        /**
        * \brief
        *    Position to the first entry of the current directory
        *    again
        * \errorindicator
        *    on error the object is not valid i.e. isValid() returns
        *    false.
        * \errors
        *    the errors defined at osal::Directory() can occur.
        **/
        void rewind() IPL_NOEXCEPT;

        //! Returns the path of the current directory opened
        const ipl::string dirname() const IPL_NOEXCEPT
        {
            return static_cast<ipl::string>(
                osal::UnicodeString(m_cur_dir) );
        }

        //! Returns the path of the current directory opened, in unicode
        void dirname(util::UnicodeString &name) const IPL_NOEXCEPT
        { name = util::UnicodeString(osal::UnicodeString(m_cur_dir)); }

        //! \brief
        //! Returns the path of the current directory opened, as a wide
        //! string
        void dirname(ipl::wstring &name) const IPL_NOEXCEPT
        { name = osal::UnicodeString(m_cur_dir); }

        //! \brief
        //! Returns whether the last call tosearch(), getListing() or
        //! getStortedListing() failed
        bool hasError() const IPL_NOEXCEPT
        { return m_has_error; }
    private:
        //! current directory opened
        osal::WidePath m_cur_dir;

        //! \brief
        //! set to true if the first entry of the m_dir is still
        //! selected (for perf. optimizations)
        bool m_first_entry;

        //! error flag for hasError()
        bool m_has_error;
    };

    bool Directory::isDir() const IPL_NOEXCEPT
    {
        const osal::FileInfo fi = this->curInfo();

        if( ! fi.isValid() )
        {
            ipl_error.ack();
            return false;
        }

        return fi.getType() == osal::FileInfo::DIRECTORY;
    }

    Directory::Directory(const ipl::string &path) IPL_NOEXCEPT :
        osal::Directory(path, true),
        m_cur_dir(osal::UnicodeString(path)),
        m_first_entry(true),
        m_has_error(false)
    { m_cur_dir = m_cur_dir.getAbsolute(); }

    Directory::Directory(const osal::UnicodeString &path) IPL_NOEXCEPT :
        osal::Directory(path, true),
        m_cur_dir(path),
        m_first_entry(true),
        m_has_error(false)
    { m_cur_dir = m_cur_dir.getAbsolute(); }

}  // end of namespace osal

#endif
