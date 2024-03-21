/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_FILESYS_HXX
#define UTIL_FILESYS_HXX

#include <ipl_config.h>

// to prevent annoying warnings on WIN32
#include <iplcompiler.h>

#include <iplbase/exceptions.hxx>
#include <common/types/vector.hxx>
#include <common/types/set.hxx>
#include <common/CommonError.hxx>
#include <osal/FileSys.hxx>
#include <osal/TreeWalker.hxx>
#include <osal/SysError.hxx>
#include <osal/FileInfo.hxx>
#include <osal/Path.hxx>
#include <osal/OpenError.hxx>
#include <util/util_dso.h>

#include <string.h>

namespace util {

    /**
    * \brief
    *     Enhanced File System Functionality

    *     Based on primitive OS functionality allow more comfortable file
    *     system operations.
    *
    *     A number of operations in osal::FileSys are only possible in a
    *     non-recursive way or if performed on the same file system in
    *     case of move.
    *
    *     The functions in this class overcome these limitations.
    **/
    template <typename STRING>
    class FileSysBase
    {
    public: // types
        typedef typename osal::PathTraits<STRING> Traits;
        typedef typename Traits::StringPointer StringPointer;
        typedef typename Traits::ConstStringPointer ConstStringPointer;
        typedef typename Traits::StringObj StringObj;
        typedef typename Traits::Character Character;
        typedef typename Traits::PathObj PathObj;
        typedef typename Traits::ApiObj ApiObj;
        typedef typename osal::TreeWalkerBase<STRING> TreeWalker;
        typedef typename TreeWalker::IEntryProcessor IEntryProcessor;
        typedef typename IEntryProcessor::WalkStatus WalkStatus;
        typedef typename TreeWalker::WalkReturn WalkReturn;

        /**
        * \brief
        *     Callback interface for recursive removal

        *     This interface is very similar to
        *     osal::TreeWalker::IEntryProcessor but specialized for
        *     the needs of recursive removal of file system trees.
        **/
        class IRemoveHandler
        {
        public: // types

            //! \brief
            //! Derived WalkStatus that adds remove specific error
            //! states
            class RemoveStatus :
                public WalkStatus
            {
            public: // functions
                //! status object without any state set
                RemoveStatus() IPL_NOEXCEPT { reset(); }

                //! \brief
                //! copy status from \c ws and initialise rm
                //! state to nothing
                RemoveStatus(const WalkStatus &ws) IPL_NOEXCEPT : WalkStatus(ws)
                { m_rm_status = 0; }

                //! reset all state flags
                void reset() IPL_NOEXCEPT
                { m_rm_status = 0; WalkStatus::reset(); }

                //! \brief
                //! indicates that removal failed due to lack of
                //! permission
                bool rmNoPerm() const IPL_NOEXCEPT
                { return (m_rm_status & RM_NO_PERM) != 0; }

                //! \brief
                //! indicates that removal failed, because the
                //! dir was not empty
                bool dirNotEmpty() const IPL_NOEXCEPT
                { return (m_rm_status & DIR_NOT_EMPTY) != 0; }

                //! \brief
                //! indicates that some other remove error
                //! occured
                bool otherRmError() const IPL_NOEXCEPT
                { return (m_rm_status & OTHER_RM_ERROR) != 0; }

                //! \brief
                //! indicates that the OS refused removal as the
                //! file is in use by others
                bool objectBusy() const IPL_NOEXCEPT
                { return (m_rm_status & OBJECT_BUSY) != 0; }

                void setRmNoPerm() IPL_NOEXCEPT
                { m_rm_status |= RM_NO_PERM; }

                void setDirNotEmpty() IPL_NOEXCEPT
                { m_rm_status |= DIR_NOT_EMPTY; }

                void setOtherRmError() IPL_NOEXCEPT
                { m_rm_status |= OTHER_RM_ERROR; }

                void setObjectBusy() IPL_NOEXCEPT
                { m_rm_status |= OBJECT_BUSY; }
            private: // members
                static const uint_fast32_t RM_NO_PERM = 1;
                static const uint_fast32_t DIR_NOT_EMPTY = 2;
                static const uint_fast32_t OTHER_RM_ERROR = 4;
                static const uint_fast32_t OBJECT_BUSY = 8;

                uint_fast32_t m_rm_status;
            };

            //! \brief
            //! Derived WalkReturn that adds possiblity to skip
            //! deletion of individual files
            class RemoveReturn :
                public WalkReturn
            {
            public:
                RemoveReturn() IPL_NOEXCEPT { reset(); }

                RemoveReturn(const WalkReturn &wr) IPL_NOEXCEPT :
                    WalkReturn(wr)
                { m_skip_delete = false; }

                //! resets all indications
                void reset() IPL_NOEXCEPT
                { m_skip_delete = false; WalkReturn::reset(); }

                bool skipDelete() const IPL_NOEXCEPT
                { return m_skip_delete; }

                //! \brief
                //! tells the remove algorithm not to delete the
                //! current file entry
                RemoveReturn setSkipDelete() IPL_NOEXCEPT
                { m_skip_delete = true; return *this; }

            private:
                bool m_skip_delete;
            };
        public: // functions

            virtual ~IRemoveHandler() {}

            /**
            * \brief
            *     Callback that is called before removal of
            *     individual files

            *     This callback matches the
            *     osal::TreeWalker::IEntryProcessor::processEntry().
            *     It is always called before the given \c relpath
            *     is going to be deleted.
            **/
            virtual RemoveReturn checkRemove(ConstStringPointer relpath,
                const osal::FileInfo &info,
                const RemoveStatus &rs) = 0;

            /**
            * \brief
            *     Callback thats is called after removal of an
            *     individual file failed

            *     By default the implementation of removeError
            *     calls checkRemove(), just like
            *     osal::TreeWalker::IEntryProcessor::processError()
            *     does.
            *
            *     This callback is also called if \c relpath could
            *     not be successfully iterated by the TreeWalker.
            **/
            virtual RemoveReturn removeError(ConstStringPointer relpath,
                const osal::FileInfo &info,
                const RemoveStatus &rs)
            {
                IPLBASE_ABORT_ON_EXCEPTION(
                    return checkRemove(relpath, info, rs);
                )
                return RemoveReturn();  // to keep the compiler happy
            }
        };

        /**
        * \brief
        *     Callback interface for recursive copy

        *     This interface is very similar to
        *     osal::TreeWalker::IEntryProcessor but specialized for
        *     the needs of recursive copying of file system trees.
        **/
        class ICopyHandler
        {
        public: // types

            //! \brief
            //! Derived WalkStatus that adds copy specific error
            //! states
            class CopyStatus :
                public WalkStatus
            {
            public: // functions
                //! \brief
                //! copies the state from \c ws and unset any
                //! copy specific state
                CopyStatus(const WalkStatus &ws) IPL_NOEXCEPT : WalkStatus(ws)
                { m_copy_status = 0; }

                //! creates an object without any state set
                CopyStatus() IPL_NOEXCEPT { reset(); }

                //! resets all state
                void reset() IPL_NOEXCEPT
                { m_copy_status = 0; WalkStatus::reset(); }

                //! \brief
                //! indicates that the source file could not be
                //! read
                bool cannotReadSrc() const IPL_NOEXCEPT
                { return (m_copy_status & CANNOT_READ_SRC) != 0; }

                //! \brief
                //! indicates that the destination file already
                //! exists
                bool dstExists() const IPL_NOEXCEPT
                { return (m_copy_status & DST_EXISTS) != 0; }

                //! \brief
                //! indicates the the destination file could not
                //! be written
                bool cannotWriteDst() const IPL_NOEXCEPT
                { return (m_copy_status & CANNOT_WRITE_DST) != 0; }

                //! indicates that some other copy error occured
                bool otherCopyError() const IPL_NOEXCEPT
                { return (m_copy_status & OTHER_COPY_ERROR) != 0; }

                void setCannotReadSrc() IPL_NOEXCEPT
                { m_copy_status |= CANNOT_READ_SRC; }

                void setDstExists() IPL_NOEXCEPT
                { m_copy_status |= DST_EXISTS; }

                void setCannotWriteDst() IPL_NOEXCEPT
                { m_copy_status |= CANNOT_WRITE_DST; }

                void setOtherCopyError() IPL_NOEXCEPT
                { m_copy_status |= OTHER_COPY_ERROR; }
            private: // members
                static const uint_fast32_t CANNOT_READ_SRC = 1;
                static const uint_fast32_t DST_EXISTS = 2;
                static const uint_fast32_t CANNOT_WRITE_DST = 4;
                static const uint_fast32_t OTHER_COPY_ERROR = 8;

                uint_fast32_t m_copy_status;
            };

            //! \brief
            //! Derived WalkReturn that adds possiblity to skip or
            //! retry copying of individual files
            class CopyReturn :
                public WalkReturn
            {
            public:
                CopyReturn() IPL_NOEXCEPT { reset(); }

                CopyReturn(const WalkReturn &wr) IPL_NOEXCEPT :
                    WalkReturn(wr)
                { m_skip_copy = m_retry_copy = false; }

                void reset() IPL_NOEXCEPT
                {
                    m_skip_copy = false;
                    m_retry_copy = false;
                    WalkReturn::reset();
                }

                bool skipCopy() const IPL_NOEXCEPT
                { return m_skip_copy; }

                bool retryCopy() const IPL_NOEXCEPT
                { return m_retry_copy; }

                //! \brief
                //!    if set then the copy algorithm does not
                //!    perform the copy operation for the
                //!    given pair of {source, dst}
                CopyReturn setSkipCopy() IPL_NOEXCEPT
                { m_skip_copy = true; return *this; }

                //! \brief
                //!    if set then the copy algorithm retries a
                //!    failed copy operation. Only recognized in a
                //!    copyError() context.
                CopyReturn setRetryCopy() IPL_NOEXCEPT
                { m_retry_copy = true; return *this; }

            private:
                bool m_skip_copy;
                bool m_retry_copy;
            };
        public: // functions

            virtual ~ICopyHandler() {}

            /**
            * \brief
            *     Callback that is called before individual copy
            *     operations

            *     This callback matches the
            *     osal::TreeWalker::IEntryProcessor::processEntry().
            *     It is always called before the given \c
            *     relpath_src is going to be copied to \c
            *     relpath_dst.
            **/
            virtual CopyReturn checkCopy(
                ConstStringPointer relpath_src,
                ConstStringPointer relpath_dst,
                const osal::FileInfo &info,
                const CopyStatus &rs) = 0;

            /**
            * \brief
            *     Callback thats is called after copying of an
            *     individual file failed

            *     By default the implementation of copyError calls
            *     checkCopy(), just like
            *     osal::TreeWalker::IEntryProcessor::processError()
            *     does.
            *
            *     This callback is also called in case \c
            *     relpath_src could not be successfully iterated
            *     by the TreeWalker.
            **/
            virtual CopyReturn copyError(
                ConstStringPointer relpath_src,
                ConstStringPointer relpath_dst,
                const osal::FileInfo &info,
                const CopyStatus &rs)
            {
                return checkCopy(relpath_src,
                    relpath_dst, info, rs);
            }
        };

        /**
        * \brief
        *     Complex return type for move operations

        *     As an inter-file-system move consists of two logical
        *     operations (copy of src to dst, then removal of src),
        *     the return type consists of two logical return types.
        *     One for the copy operation and one for the remove
        *     operation.
        **/
        typedef ipl::pair<
            typename ICopyHandler::CopyReturn,
            typename IRemoveHandler::RemoveReturn > MoveReturn;

    public: // functions

        /**
        * \brief
        *     Copies the file system tree starting at path \c source
        *     to the location denoted by path \c dest

        *     The path \c source must point to an existing file or
        *     directory.
        *
        *     The path \c dest can point to an existing directory. In
        *     this case the basename of path \c source will be used to
        *     copy \c source into the directory denoted by \c dest.
        *
        *     If both paths point to a existing non-directory objects
        *     then the file at \c dest will be overwritten by \c
        *     source.
        *
        *     If \c source points to a directory and \c dest doesn't
        *     then an error occurs.
        *
        *     Also the last component of path \c dest may point to a
        *     non-existing file system object while the next to last
        *     component denotes an existing directory. In this case
        *     the basename of \c source will be changed to the
        *     basename of \c dest for the copy.
        *
        *     The path \c source and all its contents need to be
        *     readable and accessible by the caller. The path \c dest
        *     must be writeable by the caller.
        *
        *     If \c h is given then before each copy operation and each
        *     error situation will be reported to the callback.
        *     Otherwise all files will be copied and upon the first
        *     error condition the operation will be aborted.
        * \warning
        *     Error handling is not yet very precise
        **/
        static typename ICopyHandler::CopyReturn copyRecursive(
            ConstStringPointer source,
            ConstStringPointer dest,
            ICopyHandler *ch = NULL) IPL_NOEXCEPT;

        //! \brief
        //! version of copyRecursive(const char*, const char*,
        //! ICopyHandler*) that takes STL string objects
        static typename ICopyHandler::CopyReturn copyRecursive(
            const StringObj &source,
            const StringObj &dest,
            ICopyHandler *ch = NULL) IPL_NOEXCEPT
        {
            return copyRecursive(source.c_str(), dest.c_str(), ch);
        }

        /**
        * \brief
        *     Remove the directory tree starting at \c path from the
        *     file system

        *     \c path will be removed from the file system, deleting
        *     contained objects recursively, if needed. \c path must
        *     point to an existing file or directory.
        *
        *     Appropriate write and list/enter permissions for all
        *     objects within \c path are required for this operation
        *     to succeed.
        *
        *     If an object within \c path cannot be removed for
        *     whatever reason then the operation will abort, leaving
        *     whatever remains of the file system objects in \c path.
        *
        *     If \c rh is specified then before each file system
        *     object is deleted \c rh will be called back for
        *     inspection by the caller. Also errors will be reported
        *     to \c rh.
        *
        *     If \c rh is not specified then all files will be
        *     deleted. When an error occurs the operation will then be
        *     aborted unconditionally.
        *  \warning
        *     Error handling is not yet very precise
        **/
        static typename IRemoveHandler::RemoveReturn
            removeRecursive(
                ConstStringPointer path,
                IRemoveHandler *rh = NULL) IPL_NOEXCEPT;

        //! \brief
        //! STL string variant of removeRecursive(ConstStringPointer,
        //! osal::TreeWalker::IEntryProcessor*)
        static typename IRemoveHandler::RemoveReturn
            removeRecursive(
                const StringObj &path,
                IRemoveHandler *rh = NULL) IPL_NOEXCEPT
        {
            return removeRecursive(path.c_str(), rh);
        }

        /**
        * \brief
        *     Move the content of path \c source to \c dest

        *     For \c source, \c dest and \c ch the same rules apply as
        *     at copyRecursive(const char*, const char*,
        *     ICopyHandler*).
        *
        *     For \c rh the same rules apply as to
        *     removeRecursive(const char*, IRemoveHandler*).
        *
        *     This function first attempts to perform a single move of
        *     \c source to \c dest via osal::FileSys::rename(). If
        *     that succeeds then the callbacks for \c ch and \c rh
        *     will never be called and the operation returns
        *     successfully.
        * \warning
        *     Error handling is not yet very precise
        * \return
        *     If the copy operation failed then MoveReturn.first will
        *     indicate an error and MoveReturn.second is undefined. If
        *     MoveReturn.first indicates success then
        *     MoveReturn.second indicates error during removal.
        **/
        static MoveReturn moveCrossFS(
            ConstStringPointer source,
            ConstStringPointer dest,
            ICopyHandler *ch = NULL,
            IRemoveHandler *rh = NULL) IPL_NOEXCEPT;

        //! \brief
        //!    A version of \c moveCrossFS(const char*, const char*,
        //!    ICopyHandler*, IRemoveHandler*) that uses STL string
        //!    objects
        static MoveReturn moveCrossFS(
            const StringObj &source,
            const StringObj &dest,
            ICopyHandler *ch = NULL,
            IRemoveHandler *rh = NULL) IPL_NOEXCEPT
        {
            return moveCrossFS(source.c_str(),
                dest.c_str(), ch, rh);
        }

        /**
        * \brief
        *     Create directories for \c path

        *     This function creates all directories necessary to
        *     construct \c path. \c path can be a relative or an
        *     absolute path specification. Part or all of \c path is
        *     allowed to already exist or even completely exist.
        *
        *     The call will fail if any component of \c path already
        *     exists and is not a directory, however.
        * \return
        *     \c true on error, \c false on success
        **/
        static bool createDirRecursive(ConstStringPointer path) IPL_NOEXCEPT;

        //! STL string variant of createDirRecrusive(ConstStringPointer)
        static bool createDirRecursive(const StringObj &path) IPL_NOEXCEPT
        {
            return createDirRecursive(path.c_str());
        }
    };

    typedef FileSysBase< char* > FileSys;
    typedef FileSysBase< wchar_t* > FileSysWide;

    #ifndef UTIL_EXPORT_CONTEXT

    /*
    * this is for certain gcc versions (namely gcc 4.4.2 for qnx x86) that
    * complain about the respective constant being explicitly instantiated
    * but not defined.
    *
    * these out of class declarations seem to help that compilers to get
    * over it.
    **/

    template <typename STRING>
    const uint_fast32_t FileSysBase<STRING>::ICopyHandler::CopyStatus::CANNOT_READ_SRC;
    template <typename STRING>
    const uint_fast32_t FileSysBase<STRING>::ICopyHandler::CopyStatus::DST_EXISTS;
    template <typename STRING>
    const uint_fast32_t FileSysBase<STRING>::ICopyHandler::CopyStatus::CANNOT_WRITE_DST;
    template <typename STRING>
    const uint_fast32_t FileSysBase<STRING>::ICopyHandler::CopyStatus::OTHER_COPY_ERROR;
    #endif

    }

    #include <util/Copier.hxx>
    #include <util/Deleter.hxx>

    namespace util {

    template <typename STRING>
    typename FileSysBase<STRING>::ICopyHandler::CopyReturn
    FileSysBase<STRING>::copyRecursive(
        ConstStringPointer source,
        ConstStringPointer dest,
        ICopyHandler *ch) IPL_NOEXCEPT
    {
        Copier<STRING> cp(source, dest, ch);

        if( ! cp.isValid() ) // BRANCH_COVERAGE_UNTESTABLE (only false if allocation fails in cp's ctor)
        {
            return typename Copier<STRING>::CopyReturn().setError();
        }

        osal::TreeWalkerBase<STRING> tw( cp );

        tw.setPath( source );

        if( tw.walk().walkError() )
        {
            if( ! cp.getResult().walkError() )
            {
                return tw.getWalkRes();
            }
        }

        return cp.getResult();
    }

    template <typename STRING>
    typename util::FileSysBase<STRING>::IRemoveHandler::RemoveReturn
    FileSysBase<STRING>::removeRecursive(
        ConstStringPointer p,
        typename util::FileSysBase<STRING>::IRemoveHandler *rh) IPL_NOEXCEPT
    {
        Deleter<STRING> d(p, rh);

        osal::TreeWalkerBase<STRING> tw(d);

        tw.postOrderCB(true);
        tw.preOrderCB(false);
        tw.setPath(p);

        if( tw.walk().walkError() )
        {
            if( ! d.getResult().walkError() )
                return tw.getWalkRes();
        }

        return d.getResult();
    }


    template <typename STRING>
    typename FileSysBase<STRING>::MoveReturn
    FileSysBase<STRING>::moveCrossFS(
        ConstStringPointer source,
        ConstStringPointer dest,
        typename FileSysBase<STRING>::ICopyHandler *ch,
        typename FileSysBase<STRING>::IRemoveHandler *rh) IPL_NOEXCEPT
    {
        MoveReturn ret;

        if( ! osal::FileSys::move(
            osal::UnicodeString(StringObj(source)),
            osal::UnicodeString(StringObj(dest) )) )
        {
            // already done!
            return ret;
        }

        // ignore the error and try copy, then remove
        ipl_error.ack();

        ret.first = copyRecursive(source, dest, ch);

        if( ret.first.walkError() )
            return ret;

        ret.second = removeRecursive(source, rh);

        return ret;
    }


    template <typename STRING>
    bool FileSysBase<STRING>::createDirRecursive(ConstStringPointer path) IPL_NOEXCEPT
    {
        /*
        * The simplest strategy seems to be to start from the beginning
        * of the path and try to get a FileInfo for it. If it is
        * already there and a directory, no trouble. If a file then
        * bail out with error. If not there then create it.
        *
        * We could also start from the end of the path and go backwards
        * until the first directory is there . Then go forward again.
        * But the worst case situation is worse then in the first
        * approach (needing to go from the end completely to the
        * beginning, trying to get FileInfo, then going forward
        * creating directories for each one again.
        *
        * We could also use mkdirat() like semantics. That would
        * require osal::Directory to provide a createDir() function
        * that is optimized on POSIX 2008 systems. I hope creating
        * directories won't be a very frequent operation thus I stick
        * to the primmitive approach.
        *
        * Copying the path is necessary as we need to select sub-paths
        * from it. In theory it would be possible to use the callers
        * string in case it isn't used by other threads.  But that
        * could get complicated.
        */
        PathObj p(path);

        osal::Path::size_type sep_pos = 0;
        osal::FileInfo f;

        // this flag is true as long as we're still seeing existing path
        // components
        bool still_existing = true;

        do
        {
            sep_pos = p.find(p.SEPARATOR, sep_pos + 1 );

            // temporary path for the test
            PathObj tmp (p.substr(0, sep_pos));

            if( still_existing )
            {
                f = osal::FileInfo( static_cast<ApiObj>(tmp) );

                // exists and is no directory. this is an error
                // condition
                if( f.isValid() &&
                    f.getType() != osal::FileInfo::DIRECTORY )
                {
                    ipl_raise( osal::SysError,
                        osal::NO_DIRECTORY, tmp.c_str() );
                    return true;
                }
                else if( !f.isValid() )
                {
                    // okay, file doesn't exit, probably
                    if( ipl_error.isA(osal::OpenError)
                        && ipl_error.id() == osal::BAD_PATH )
                    {
                        ipl_error.ack();
                        still_existing = false;
                    }
                    // some error other then non-existence
                    // occured.
                    else
                    {
                        return true;
                    }
                }
            }

            // careful, flag can change inside if block above
            if( ! still_existing )
            {
                if( osal::FileSys::createDir(
                    static_cast<ApiObj>(tmp)) )
                {
                    // permission denied or something,
                    // anyway it failed
                    return true;
                }
            }
        }
        while( sep_pos != p.npos &&
            /* covers trailing slashes */
            (sep_pos != p.length() - 1)
            );

        return false;
    }

}  // end of namespace util

#endif
