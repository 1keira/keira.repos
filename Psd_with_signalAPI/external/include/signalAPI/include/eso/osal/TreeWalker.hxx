/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_TREEWALKER_HXX
#define OSAL_TREEWALKER_HXX

#include <iplcompiler.h>

#include <common/types/string.hxx>
#include <common/types/utility.hxx>
#include <common/types/stack.hxx>
#include <common/CommonError.hxx>
#include <common/ScopeGuard.hxx>
#include <common/error/ErrorHelper.hxx>
#include <osal/Directory.hxx>
#include <osal/FileInfo.hxx>
#include <osal/Path.hxx>
#include <osal/UnicodeString.hxx>
#include <osal/FileSys.hxx>

namespace osal {

    //! \brief
    //! this type helps us write code independent of ascii / wide strings
    //! being used
    template <typename CHAR_TYPE>
    struct PathTraits
    { };

    //! specialization of PathTraits for ASCII
    template<>
    struct PathTraits<char*>
    {
        typedef osal::Path PathObj;
        typedef ipl::string StringObj;
        typedef char* StringPointer;
        typedef const char* ConstStringPointer;
        typedef char Character;
        typedef ipl::string ApiObj;
    };

    //! specialization of PathTraits for wide strings in PD unicode
    template<>
    struct PathTraits<wchar_t*>
    {
        typedef osal::WidePath PathObj;
        typedef ipl::wstring StringObj;
        typedef wchar_t* StringPointer;
        typedef const wchar_t* ConstStringPointer;
        typedef wchar_t Character;
        typedef osal::UnicodeString ApiObj;
    };

    /**
    * \brief
    *     Algorithm to iterate over a File System Tree

    *     This class implements a search algorithm that allows to
    *     efficiently search a complete directory tree. It calls a virtual
    *     C++ interface class for each file system object in the file
    *     system tree.
    *
    *     The callback also gets additional osal::FileInfo and algorithm
    *     status information.  This allows to efficiently scan directory
    *     trees and process detailed file system object information in
    *     various ways.
    * \code
    *     #include <osal/TreeWalker.hxx>
    *
    *     class TreeProcessor :
    *         public osal::TreeWalker::IEntryProcessor
    *     {
    *
    *     virtual WalkReturn processEntry(const char *relpath,
    *         const osal::FileInfo &info,
    *         const struct WalkInfo& wi)
    *     {
    *         osal::TreeWalker::WalkReturn wr;
    *
    *         // name of the file
    *         const char *basename = relpath + wi.basename_offset;
    *
    *         if( wi.is_dir )
    *         {
    *             // dir handling
    *
    *             if( not_interested )
    *             {
    *                 return wr.skipDirectory();
    *             }
    *         }
    *         else
    *         {
    *             uint_fast64_t size = info.getSize();
    *
    *             // ... some more file handling
    *
    *             if( abort_condition )
    *             {
    *                 return wr.setError();
    *             }
    *         }
    *
    *         // continue
    *         return wr;
    *     }
    *
    *     };
    *
    *     TreeProcessor tp;
    *
    *     osal::TreeWalker tw( tp );
    *
    *     tw.setPath("./mydir");
    *
    *     tw.sameFS(true);
    *     tw.preOrderCB(false);
    *     tw.postOrderCB(true);
    *
    *     tw.walk();
    * \endcode
    **/
    template <typename STRING>
    class TreeWalkerBase
    {
    public: // types
        typedef PathTraits<STRING> Traits;
        typedef typename Traits::StringPointer StringPointer;
        typedef typename Traits::ConstStringPointer
            ConstStringPointer;
        typedef typename Traits::StringObj StringObj;
        typedef typename Traits::Character Character;
        typedef typename Traits::PathObj PathObj;
        typedef typename Traits::ApiObj ApiObj;

        /**
        * \brief
        *     Datatype for Return Codes from Callback Functions

        *     This type is used for two things:
        *
        *     - signaling the overall walk result to the caller of
        *     TreeWalker::walk()
        *     - controlling the TreeWalker algorithm from within the
        *     IEntryProcessor callback invocation
        **/
        class WalkReturn
        {
        public:
            //! creates a reset() return object
            WalkReturn() { reset(); }

            //! reset the return object to signal walkOkay()
            void reset()
            { m_ret = WALK_OKAY; }

            //! set walkError() active
            WalkReturn setError()
            { m_ret = WALK_ERROR; return *this; }

            //! set skipDirectory() active
            WalkReturn setSkipDirectory()
            { m_ret = SKIP_DIRECTORY; return *this; }

            /**
            * \brief
            *     Indicates that everything is well

            *     If the object returned from the IEntryProcessor
            *     callback has this flag set then the algorithm
            *     continues as normal.
            *
            *     If an object with this flag set is returned from
            *     TreeWalker::walk() then the complete TreeWalk
            *     was successful.
            **/
            bool walkOkay() const
            { return m_ret == WALK_OKAY; }

            /**
            * \brief
            *     Indicates that an error occured

            *     If the object returned from the IEntryProcessor
            *     callback has this flag set then the algorithm is
            *     terminated and TreeWalker::walk() returns.
            *
            *     The TreeWalker may also set this error flag
            *     internally and return from TreeWalker::walk().
            *
            *     Generally if this flag is set an error should
            *     have been raised previously that describes the
            *     problem.
            **/
            bool walkError() const
            { return m_ret == WALK_ERROR; }

            /**
            * \brief
            *     Indicates that the current directory is to be
            *     skipped

            *     If an IEntryProcessor callback was called in
            *     pre-order for a directory file system object and
            *     the callback returns an object with this flag
            *     set then the TreeWalker algorithm doesn't
            *     process the directory or its contents. If the
            *     current callback was called for a non-directory
            *     file system object or not called in pre-order
            *     then this flag has no effect and behaves like
            *     walkOkay() has been set.
            **/
            bool skipDirectory() const
            { return m_ret == SKIP_DIRECTORY; }

        private:
            static const int_fast32_t WALK_OKAY = 0;
            static const int_fast32_t WALK_ERROR = -1;
            static const int_fast32_t SKIP_DIRECTORY = -2;

            int_fast32_t m_ret;
        };

        /**
        * \brief
        *     Pure virtual callback interface for the Algorithm

        *     Implement this interface to work with the TreeWalker
        *     algorithm. The interface provides a callback for normal
        *     operation processEntry() plus a second callback in case
        *     of errors occur processError(). By default the
        *     processError() implementation calls processEntry().
        *
        *     This way it is possible to process both normal entry
        *     callbacks and error callbacks in the single
        *     processEntry() callback. Errors can still be detected
        *     via the WalkStatus object passed.
        *
        *     If you instead prefer a separate callback for errors you
        *     can simply overwrite the processError() callback.
        **/
        class IEntryProcessor
        {
        public: // types
            /**
            * \brief
            *     Datatype to hold current algorithm context

            *     This type indicates special conditions to the
            *     client upon callbacks like errors or algorithmic
            *     information valuable to the client.
            **/
            class WalkStatus
            {
            public:
                //! \brief
                //! creates an empty WalkStatus without any
                //! special conditions set
                WalkStatus() : m_is_dir(false), m_basename(NULL),
                    m_path_depth(0), m_basename_offset(0)
                { reset(); }

                //! \brief
                //! resets all state but keeps basename, is_dir
                //! and path depth
                void reset() { m_status = 0; }

                /**
                * \brief
                *     The given Directory and all its Contents
                *     have been Processed

                *     This indication will only be given if
                *     postOrderCB() has been set to true. It
                *     happens upon callback for a directory
                *     file system object for which all
                *     contents have been processed already.
                *
                *     The algorithm guarantees that no more
                *     open handles to the given directory or
                *     any its contents will be kept open by
                *     the algorithm.  This means it will be
                *     possible to e.g. delete the directory
                *     without getting system errors about busy
                *     files.
                **/
                bool dirFinished() const
                { return (m_status & DIR_FINISHED) != 0; }

                /**
                * \brief
                *     The given Directory cannot be Entered

                *     This indication is given upon callback
                *     for a directory file system object that
                *     cannot be entered or searched by the
                *     calling process.
                **/
                bool dirNoAccess() const
                { return (m_status & DIR_NO_ACCESS) != 0; }

                /**
                * \brief
                *     Can't get FileInfo for the given file
                *     system object

                *     This indication means that there is an
                *     entry in the file system tree for which
                *     no FileInfo object could be acquired.
                *     This means that the algorithm can't even
                *     decide whether the file is a directory
                *     or a non-directory. Usually this means
                *     the file is either completely
                *     inaccessible or it has been moved by
                *     some other thread in the system.
                **/
                bool noInfoAvail() const
                { return (m_status & NO_INFO_AVAIL) != 0; }

                //! \brief
                //!    returns true if any of the error
                //!    indicators (dirNoAccess(), noInfoAvail())
                //!    is set
                bool errorOccured() const
                { return dirNoAccess() || noInfoAvail(); }

                //! sets the dirFinished() state
                void setDirFinished()
                { m_status |= DIR_FINISHED; }

                //! sets the dirNoAccess() state
                void setDirNoAccess()
                { m_status |= DIR_NO_ACCESS; }

                //! sets the noStatAvail() state
                void setNoStatAvail()
                { m_status |= NO_INFO_AVAIL; }

                //! \brief
                //! is set to true if the callback is performed
                //! for a directory file system object
                bool isDir() const
                { return m_is_dir; }

                void setIsDir(const bool dir)
                { m_is_dir = dir; }

                /**
                * \brief
                *    Pointer to Basename Path Component

                *    This is a pointer to the character in
                *    the \c relpath callback parameter where
                *    the basename of the path begins.
                **/
                const StringPointer getBasename() const
                { return m_basename; }

                void setBasename(StringPointer bn)
                { m_basename = bn; }

                /**
                * \brief
                *    The Directory Depth Relative to the
                *    Start Path

                *    For the start path as given to setPath()
                *    the depth will be zero. For each
                *    subsequent path component in \c relpath
                *    the callback function will be called
                *    with an incremented value.
                *
                *    Non-directory path components are also
                *    considered in this value i.e. if you
                *    start your search in "/tmp" and you're
                *    called back for a file in "/tmp/file"
                *    then path_depth will already be one.
                **/
                uint_fast16_t getPathDepth() const
                { return m_path_depth; }

                void setPathDepth(const uint_fast16_t pd)
                { m_path_depth = pd; }

                void incPathDepth()
                { m_path_depth++; }

                void decPathDepth()
                { m_path_depth--; }

                int_fast16_t getBasenameOffset() const
                { return m_basename_offset; }

                void setBasenameOffset(const uint_fast16_t bno)
                { m_basename_offset = bno;  }
            private:
                static const uint_fast32_t DIR_FINISHED = 1;
                static const uint_fast32_t DIR_NO_ACCESS = 2;
                static const uint_fast32_t NO_INFO_AVAIL = 4;

                uint_fast32_t m_status;

                bool m_is_dir;

                StringPointer m_basename;

                uint_fast16_t m_path_depth;

                uint_fast16_t m_basename_offset;
            };

        public: // functions
            virtual ~IEntryProcessor() {}
            /**
            * \brief
            *     Callback for normal entries

            *     Example: Suppose TreeWalker::setPath() was
            *     called with "./tmp" and there is a regular file
            *     in that directory called "file". Then you will
            *     get a callback for "file" with the following
            *     parameters:
            *
            *     relpath: "./tmp/file"
            *     fi: file information for "file"
            *     ws.getBasename(): "file"
            *     ws.getPathDepth(): 1
            *     ws.isDir(): false
            *     no special states set in ws otherwise
            * \param[in] relpath
            *     This gives the current path in the file system
            *     tree for which the callback occurs. The path
            *     consists of the start path as given to setPath()
            *     concatenated with the current sub-path.
            * \param[in] info
            *     The file information associated with the file
            *     system object located at \c relpath. On error
            *     conditions it is possible that this information
            *     is not accessible (in case processError() calls
            *     processEntry()) in which case fi.isValid()
            *     returns false. No error is raised, though.
            * \param[in] ws
            *     The current algorithm context
            * \return
            *     If the callback returns a WalkReturn object with
            *     walkOkay() est then the algorithm will continue
            *     normal processing of the file system tree.
            *
            *     If the callback returns a WalkReturn object with
            *     skipDirectory() set and the current entry is a
            *     directory that is about to be entered (i.e.
            *     callback occured in pre-order) then this
            *     directory will be skipped and processing
            *     continues with the next entry available. If this
            *     return code is given but the current entry isn't
            *     a directory or the current directory has already
            *     been processed (i.e. callback occured in
            *     post-order) then the behaviour will be as if
            *     state walkOkay() has been set.
            *
            *     If the callback returns a WalkReturn object with
            *     walkError() set then the algorithm will stop
            *     processing and return the same WalkReturn object
            *     from TreeWalker::walk(). In this case the
            *     callback should raise an according error to
            *     describe the problem.
            *
            *     Note that the walkError() state can also be
            *     returned from TreeWalker::walk() due to internal
            *     errors in the algorithm.
            **/
            virtual WalkReturn processEntry(ConstStringPointer relpath,
                const osal::FileInfo &info,
                const WalkStatus &ws) = 0;

            /**
            * \brief
            *    In principle the same as processEntry() but is
            *    called only on error conditions

            *    The default implementation of this function
            *    simply calls processEntry().  This way if you
            *    want to handle normal callbacks and error
            *    callbacks in the same context you only have to
            *    implement processEntry().
            *
            *    If you want to separate error handling then you
            *    can overwrite this function accordingly. If you
            *    want to ignore errors you can overwrite with an
            *    empty implementation that always returns a
            *    WalkReturn set to walkOkay().
            **/
            virtual WalkReturn processError(ConstStringPointer relpath,
                const osal::FileInfo &info,
                const WalkStatus &ws)
            {
                return processEntry(relpath, info, ws);
            }
        };

    public: // functions

        /**
        * \brief
        *     Create an Algorithm Object Bound to the given callback
        *     interface

        *     By default no start path is set and pre-order callbacks
        *     are enabled.
        **/
        TreeWalkerBase(IEntryProcessor &tw) :
            m_opts(0),
            m_walk_res(),
            m_tw(tw),
            m_root_is_dir(true),
            m_root_fs_id(INVALID_FILESYSID)
        {
            this->preOrderCB(true);
        }

        ~TreeWalkerBase()
        {
            IPL_ASSERT( m_left_dirs.empty() );
        }

        /**
        * \brief
        *     Starts the Algorithm with the Currently Applied Settings

        *     The algorithm will be started for the path set at
        *     setPath() and with any additional options set.
        *
        *     The algorithm will call the callback function specified
        *     at construction time for every encountered file system
        *     object in the file system tree starting at the given
        *     start path.
        *
        *     The algorithm will terminate on three conditions:
        *
        *     - The complete file system tree has been parsed and the
        *     callback never indicated termination. A WalkReturn with
        *     walkOkay() set will be returned in this case.
        *     - The callback function returned a WalkReturn with
        *     walkError() set. In this case the callback return value
        *     is returned here, too. If an error is raised depends on
        *     the callback implementation.
        *     - An un-recoverable error was detected by the algorithm.
        *     In this case a WalkReturn with walkError() set is
        *     returned and an error describing the problem ist raised.
        * \errorindicator
        *     WalkReturn object with walkError() set is returned on
        *     error.
        * \errors
        *    FileAccessError attached with osal::SysError on errors
        *    regarding path lookup
        *
        *     osal::SysError with IDs:
        *
        *     - OUT_OF_MEMORY if there's not enough memory left to
        *     perform the algorithm
        *     - UNKNOWN_ERROR on other conditions
        **/
        WalkReturn walk()
        {
            // this thing makes sure cleanup is called for all return paths
            typedef bool (TreeWalkerBase<STRING>::*cleanup_func)(void);
            ipl::ScopeGuard<TreeWalkerBase<STRING>, cleanup_func>
                cleanup_guard( *this, &TreeWalkerBase<STRING>::cleanup, true );

            // open the root directory to traverse, do initial setup for the
            // algorithm
            init();

            // no special status right now
            m_status.reset();

            // sane initial value is required if recursing into an empty
            // directory, or root is a file
            m_status.setIsDir(m_root_is_dir);

            // there was an error during init, obviously
            if( m_left_dirs.empty() )
            {
                return m_walk_res.setError();
            }

            // the start of the basename of the root dir
            osal::Path::size_type bn_pos =
                m_cur_path.find_last_of( m_cur_path.SEPARATOR );

            // if no separator then start at zero
            if( bn_pos == m_cur_path.npos )
                m_bn_offsets.push(0);
            else
                m_bn_offsets.push( (bn_pos < m_cur_path.size() - 1)
                        ? bn_pos + 1 : bn_pos );

            // set the current basename offset in the status
            m_status.setBasenameOffset( m_bn_offsets.top() );

            // if root is a dir and pre-order CB is set then we need to call
            // back for the initial directory first
            //
            // otherwise if root isn't a dir then we simply call for the
            // single file and finish (don't need to worry about order in
            // this case)
            if( !m_root_is_dir || this->preOrderCB() )
            {
                if( ! this->doCB(m_left_dirs.top().second) )
                {
                    if( m_walk_res.skipDirectory() )
                    {
                        // in case this is a file then we can
                        // ignore skip dir anyway
                        //
                        // if this is a dir and the root is
                        // skipped by the CB then we're
                        // finished, too.
                        m_walk_res.reset();
                    }

                    return m_walk_res;
                }

                if( !m_root_is_dir )
                {
                    delete m_left_dirs.top().first;
                    delete m_left_dirs.top().second;
                    m_left_dirs.pop();

                    return m_walk_res;
                }
            }

            // now start processing directory contents
            while ( ! m_left_dirs.empty() )
            {
                osal::Directory *cur_dir = m_left_dirs.top().first;

                // select res of osal::Directory::next()
                int_fast8_t next_res;

                // as long as we get a new entry from the current
                // directory...
                for( next_res = (cur_dir->atEnd() == true); !next_res;
                        next_res = cur_dir->next() )
                {
                    const int_fast8_t res =
                        this->enterPath( *cur_dir );

                    if( res < 0 ) // BRANCH_COVERAGE_UNTESTABLE
                    {
                        // abort algorithm
                        return m_walk_res;
                    }
                    else if( res > 0 )
                    {
                        // select next directory on current
                        // directory
                        next_res = cur_dir->next();
                        // continue with new directory
                        break;
                    }
                }

                // error scanning directory
                if( next_res < 0 ) // BRANCH_COVERAGE_UNTESTABLE
                {
                    // error from osal::Directory is kept
                    return m_walk_res.setError();
                }
                else if( cur_dir != m_left_dirs.top().first )
                {
                    // a new directory was selected
                    continue;
                }
                // check whether we need to select a new directory to
                // scan
                else if( cur_dir->atEnd() )
                {
                    // delete directory before calling back which
                    // allows the client to remove the directory if
                    // required
                    delete m_left_dirs.top().first;
                    // bittner: avoid double delete by setting the deleted pointer to zero
                    m_left_dirs.top().first = 0;

                    if( !this->leavePath(*m_left_dirs.top().second) ) // BRANCH_COVERAGE_UNTESTABLE
                        return m_walk_res;

                    delete m_left_dirs.top().second;

                    // away with the dir
                    m_left_dirs.pop();
                }
            } // end while not left_dirs empty

            if( this->changeWD() )
            {
                if( osal::FileSys::changeWD( UnicodeString(m_old_cwd) ) ) // BRANCH_COVERAGE_UNTESTABLE
                {
                    ipl_error.ack();
                }
            }

            return m_walk_res;
        }

        /**
        * \brief
        *     Returns the WalkReturn result of the last Algorithm Run

        *     The last value as returned from walk() can be queried
        *     via this function. If walk() has never been called on
        *     the object then a default constructed WalkReturn is
        *     returned here.
        **/
        WalkReturn getWalkRes() const
        { return m_walk_res; }

        /**
        * \brief
        *     Set the Change Working Directory Option

        *     If \c val is set to \c true then the algorithm will
        *     change the process's working directory to the directory
        *     or parent directory (in case of non-directory file
        *     system objects) of the currently inspected file system
        *     object for the duration of each callback.
        *
        *     Be careful with this option as the working directory is
        *     a process global datum and can influence other threads
        *     in the current process.
        *
        *     By default this option is disabled.
        **/
        void changeWD(const bool val)
        { if(val) m_opts |= OPT_CHANGE_WD; else m_opts &= (~OPT_CHANGE_WD); }

        //! \brief
        //! Returns whether Currently the Change Working Directory
        //! Option is set
        bool changeWD() const
        { return (m_opts & OPT_CHANGE_WD) != 0; }

        /**
        * \brief
        *     Set the pre-order Callback Option

        *     If \c val is set to \c true then the algorithm will call
        *     the callback function for each directory it encounters
        *     before its contents are processed.
        *
        *     This situation can be detected in the callback function
        *     if WalkStatus.isDir() returns true but
        *     WalkStatus.dirFinished() does return false.
        *
        *     The algorithm will usually have an open handle for the
        *     directory during callback execution in this context i.e.
        *     it is not necessarily possible to delete the given
        *     directory at this stage of the algorithm.
        *
        *     If you return WalkReturn with skipDirectory() set from
        *     the callback function in this context then the contents
        *     of the given directory will not be processed by the
        *     algorithm.
        *
        *     This option is enabled by default.
        **/
        void preOrderCB(const bool val)
        { if(val) m_opts |= OPT_PRE_ORDER; else m_opts &= (~OPT_PRE_ORDER); }

        //! returns \c true if the preOrderCB option is currently set
        bool preOrderCB() const
        { return (m_opts & OPT_PRE_ORDER) != 0; }

        /**
        * \brief
        *     Set the post-order Callback Option

        *     If \c val is set to \c true then the algorithm will call
        *     the callback function for each directory it encounters
        *     *after* the contents of the directory have been
        *     processed and the directory is exited.
        *
        *     This situation can be detected in the callback function
        *     if WalkStatus.isDir() returns true and
        *     WalkStatus.dirFinished() also returns true.
        *
        *     The algorithm guarantees that no more handles will be
        *     held by the TreeWalker for the directory or any of its
        *     contents in this context. This means you will be able to
        *     correctly delete a directory at this stage of the
        *     algorithm without getting busy errors from the operating
        *     system.
        *
        *     By default this option is disabled.
        * \note
        *     If you set both preOrderCB() and postOrderCB() then you
        *     get two callbacks for each directory. One upon entering
        *     it and one upon leaving it.
        *
        *     Similarly if you disable both options you don't get any
        *     callbacks for directories at all (which probably isn't
        *     what you want)
        **/
        void postOrderCB(const bool val)
        {
            if(val) m_opts |= OPT_POST_ORDER;
            else m_opts &= (~OPT_POST_ORDER);
        }

        //! returns \c true if the postOrderCB option is currently set
        bool postOrderCB() const
        { return (m_opts & OPT_POST_ORDER) != 0; }

        /**
        * \brief
        *     Set the Stay on File System Option

        *     If \c val is set to \c true then the algorithm will not
        *     cross file system boundaries while processing the file
        *     system tree. Thus if a directory file system object is
        *     not residing on the same file system as it's parent
        *     directory then it will be skipped from processing.
        *
        *     By default this option is disabled.
        **/
        void sameFS(const bool val)
        {
            if(val) m_opts |= OPT_SAME_FS;
            else m_opts &= (~OPT_SAME_FS);
        }

        //! \brief
        //! Returns whether Currently the Stay on File System Option is
        //! set
        bool sameFS() const
        { return (m_opts & OPT_SAME_FS) != 0; }

        /**
        * \brief
        *     Set the Resolve Links Options

        *     If \c val is set to \c true then the algorithm will
        *     resolve symbolic links in the file system tree and
        *     follow them. Setting this option is discouraged.  The
        *     algorithm gets much more complex as to avoid loops in
        *     the file system tree processing. Thus performance
        *     suffers considerably. Also unexpected side effects may
        *     occur.
        *
        *     By default this option is disabled.
        **/
        void resolveLinks(const bool val)
        {
            if(val) m_opts |= OPT_RESOLVE_LINKS;
            else m_opts &= (~OPT_RESOLVE_LINKS);
        }

        //! Returns whether Currently the Resolve Links Option is set
        bool resolveLinks() const
        { return (m_opts & OPT_RESOLVE_LINKS) != 0; }

        /**
        * \brief
        *     Set the File System Path to use as Root for the
        *     Algorithm

        *     The given \c path will become the root for the file
        *     system tree walk performed by the algorithm. It needs to
        *     be an existing file system object.
        *
        *     If \c path points to a directory then the directory will
        *     be recursively traversed. If it points to a
        *     non-directory then the TreeWalker will call the callback
        *     function exactly once for the given file system object.
        *
        *     By default the path is set to an empty path.
        **/
        void setPath(const StringObj &path)
        { m_start_path = path; }

        //!  Returns the Currently set Start Path
        const StringObj& getPath() const
        { return m_start_path; }

    protected: // member functions
        //! walk preparation code
        void init()
        {
            m_walk_res.reset();

            // we start at a path depth of zero
            m_status.setPathDepth(0);

            m_cur_path = m_start_path;

            // sanitize path
            m_cur_path = m_cur_path.getSane();

            // acquire FileInfo and Directory for the tree root
            //
            // push the new info as a pair on the stack

            osal::FileInfo *startinfo =
                new(ipl::raise_error) osal::FileInfo(
                        static_cast<ApiObj>(m_cur_path) );

            // in the second case error is already raised by FileInfo
            if( ! startinfo || ! startinfo->isValid() )
            {
                delete startinfo;

                return;
            }

            // remember the fs id of the tree root, in case stay on file
            // system is required
            m_root_fs_id = startinfo->getFsId();

            m_root_is_dir = ( startinfo->getType()
                    == osal::FileInfo::DIRECTORY );
            osal::Directory *startdir = NULL;

            if( m_root_is_dir )
            {
                startdir = new(ipl::raise_error)
                    osal::Directory(
                            static_cast<ApiObj>(m_cur_path),
                            true);

                // on error stop execution, in the second case error is
                // raised by Directory
                if( ! startdir || ! startdir->isValid() )
                {
                    delete startdir;
                    delete startinfo;

                    return;
                }
            }

            if( this->changeWD() )
            {
                ApiObj current_wd;

                // try to save cwd on success try to change into dir
                // containing the initial file or directory (i.e.  also
                // works if !m_root_is_dir)
                if( osal::FileSys::currentWD( current_wd ) ||
                        osal::FileSys::changeWD( UnicodeString(m_cur_path.getDirname()) ) )
                {
                    delete startinfo;
                    delete startdir;
                    return;
                }

                m_old_cwd = current_wd;
            }

            m_left_dirs.push( DirInfoPair( startdir, startinfo ) );
        }

        //! \brief
        //! cleans up any algorithm state, heap data etc. on error and
        //! success
        // the bool return is only for the ScopeGuard compatibility
        bool cleanup()
        {
            while( ! m_left_dirs.empty() )
            {
                delete m_left_dirs.top().first;
                delete m_left_dirs.top().second;
                m_left_dirs.pop();
            }

            while( ! m_bn_offsets.empty() )
                m_bn_offsets.pop();

            if( this->changeWD() && ! m_old_cwd.empty() )
            {
                if( osal::FileSys::changeWD( UnicodeString(m_old_cwd) ) ) // BRANCH_COVERAGE_UNTESTABLE
                {
                    ipl::cerr << __FUNCTION__
                        << ": WARNING: Can't change into "
                        << static_cast<ipl::string>(m_cur_path)
                        << ": "
                        << ipl_error.reason() << "\n";
                    ipl_error.ack();
                }

                m_old_cwd.clear();
            }

            return false;
        }

        //! \brief
        //!    performs a callback for the current data set in the
        //!    object and returns true if algorithm is to continue
        bool doCB(const osal::FileInfo *fi)
        {
            // set the correct basename string
            m_status.setBasename(
                &m_cur_path[m_status.getBasenameOffset()] );

            if( ! m_status.errorOccured() )
            {
                m_walk_res = m_tw.processEntry(
                    m_cur_path.c_str(), *fi, m_status);
            }
            else
            {
                m_walk_res = m_tw.processError(
                    m_cur_path.c_str(), *fi, m_status);
            }

            if( ! m_walk_res.walkOkay() )
                return false;

            return true;
        }

        /**
        * \brief
        * Leaves the current path and performs any necessary steps
        * \return
        * true if algorithm is to continue, false otherwise
        **/
        bool leavePath(const osal::FileInfo &fi,
            const bool dont_callback = false)
        {
            // NOTE: this function does *not* pop the top directory from
            // m_left_dirs

            bool ret = true;

            if( ! dont_callback )
            {
                if( m_status.isDir() )
                {
                    if( this->postOrderCB() )
                    {
                        // don't mix no access with finished. it
                        // makes no sense
                        if( ! (m_status.dirNoAccess()) )
                        {
                            // it's finished now
                            m_status.setDirFinished();
                        }

                        // for post-order option we need to do
                        // the CB upon exit from the directory
                        ret = this->doCB(&fi);
                    }
                }
                else
                {
                    // independently of pre- or post-order we need
                    // to call the CB for normal files or
                    // inaccessible file system objects
                    ret = this->doCB(&fi);
                }
            }

            if( m_status.getBasenameOffset() )
            {
                // get rid of the current basename component
                m_cur_path.erase( m_status.getBasenameOffset() - 1 );

                IPL_ASSERT( ! m_bn_offsets.empty() );
                m_status.setBasenameOffset( m_bn_offsets.top() );
                m_bn_offsets.pop();

                // not so deep any more ;)
                m_status.decPathDepth();

                if( this->changeWD() && m_status.isDir() )
                {
                    if( osal::FileSys::changeWD( // BRANCH_COVERAGE_UNTESTABLE
                                static_cast<ApiObj>(m_cur_path) ) )
                    {
                        IPL_WARN("Can't change into %s, reason: %s",
                                ((ipl::string)m_cur_path).c_str(),
                                ipl_error.getReasonList().c_str());
                        ipl_error.ack();
                    }
                }
            }

            // we're in a directory again
            m_status.setIsDir(true);

            // skip directory doesn't make sense upon leaving a directory.
            // ignore it.
            if( ! ret && m_walk_res.skipDirectory() )
            {
                ret = true;
                m_walk_res.reset();
            }

            return ret;
        }

        /**
        * \brief
        * Enters the given path and performs any necessary steps
        * \return
        * less than zero if abortion of the algorithm is requested,
        * zero if iteration of the current directory is to continue,
        * greater zero if iteration of the current directory is to be
        * suspended and the top directory is to be processed.
        **/
        int_fast8_t enterPath(const osal::Directory &d)
        {
    #ifdef OSAL_USE_PATH
            const char *p = d.curEntry();

            // skip self and parent entry (anything starting with a dot)
            if( p[0] == '.' && (p[1] == '\0'
                        || (p[1] == '.' && p[2] == '\0') ) )
            {
                return 0;
            }
    #endif
    #ifdef OSAL_USE_WIDEPATH
            osal::UnicodeString ucs;
            d.curEntry(ucs);

            const wchar_t *p = ucs.nativeData();

            // skip self and parent entry (anything starting with a dot)
            if( p[0] == L'.' && (p[1] == L'\0'
                        || (p[1] == L'.' && p[2] == L'\0') ) )
            {
                return 0;
            }
    #endif

            // remember old offset if we need to switch back
            m_bn_offsets.push(m_status.getBasenameOffset());
            // the new basename starts where we concatenate it to
            m_status.setBasenameOffset( m_cur_path.size() + 1 );
            // one component deeper
            m_status.incPathDepth();
            // no special conditions right now
            m_status.reset();
            m_cur_path.append( 1, m_cur_path.SEPARATOR );
            // our new current path
            appendEntryToPath( m_cur_path, p );

            // get the file info for the new object
            osal::FileInfo *new_info = new(ipl::raise_error)
                osal::FileInfo( d.curInfo( this->resolveLinks() ) );
            if( ! new_info )
            {
                m_walk_res.setError();
                return -1;
            }

            if( new_info->isValid() )
            {
                // store dir state
                m_status.setIsDir( new_info->getType()
                        == osal::FileInfo::DIRECTORY );

                if( this->sameFS() &&
                        new_info->getFsId() != m_root_fs_id )
                {
                    if( ! this->leavePath(*new_info, true) ) // BRANCH_COVERAGE_UNTESTABLE
                    {
                        IPL_ABORT("This is unexpected 2");
                    }

                    delete new_info;

                    // skip this entry if same file system is
                    // requested and the new object is on a
                    // different file system
                    return 0;
                }
            }
            else
            {
                //IPL_ABORT("invalid file info");
                // we're graceful in this case. Simply provide the
                // invalid info then
                ipl_error.ack();
                // we can't determine the type thus assume no dir
                m_status.setIsDir(false);
            }

            // directories need special handling
            if( m_status.isDir() )
            {
                osal::Directory *new_dir = NULL;
                new_dir = new(ipl::raise_error) osal::Directory(
                        d.curDir(true) );
                if( ! new_dir )
                {
                    delete new_info;
                    m_walk_res.setError();
                    return -1;
                }

                if( ! new_dir->isValid() )
                {
                    // we are again graceful and set an
                    // informational status
                    ipl_error.ack();
                    m_status.setDirNoAccess();

                    // don't forget to delete
                    delete new_dir;
                    new_dir = NULL;
                }

                // if pre-order is set then call the CB for this
                // directory immediatly
                if( this->preOrderCB() && !this->doCB(new_info) )
                {
                    // client might request to skip this directory
                    // ...
                    if( m_walk_res.skipDirectory() )
                    {
                        // leave the dir again, without calling
                        // back
                        if( !this->leavePath( *new_info, true ) ) // BRANCH_COVERAGE_UNTESTABLE
                        {
                            IPL_ABORT("Error leaving path");
                        }

                        // remove the stuff
                        delete new_info;
                        delete new_dir;

                        // reset return code
                        m_walk_res.reset();

                        // go on normally
                        return 0;
                    }

                    // free the current data before returning
                    delete new_info;
                    delete new_dir;

                    // callback requests something special to happen
                    return -1;
                }

                // go on with the new dir, if accessible
                if( new_dir )
                {
                    // change into the new directory now, if option is set
                    if( this->changeWD() && // BRANCH_COVERAGE_UNTESTABLE
                            osal::FileSys::changeWD(
                                static_cast<ApiObj>(m_cur_path) ) )
                    {
                        IPL_WARN("Can't change into %s, reason: %s",
                                static_cast<ipl::string>(m_cur_path).c_str(),
                                ipl_error.getReasonList().c_str());
                        ipl_error.ack();
                    }

                    // push this directory on the top to scan it next
                    m_left_dirs.push( DirInfoPair( new_dir, new_info ) );

                    return 1;
                }

                // this would be bad
                IPL_ASSERT( ! new_dir );
            }

            int_fast8_t ret = 0;

            // if this is a file or an inaccessible directory then leave the
            // current path
            if( ! this->leavePath(*new_info) )
            {
                // callback requested abortion of algorithm
                ret = -1;
            }

            delete new_info;

            return ret;
        }

    private:
        // bit-wise values for options
        static const uint_fast32_t OPT_CHANGE_WD = 1;
        static const uint_fast32_t OPT_DEPTH = 2;
        static const uint_fast32_t OPT_SAME_FS = 4;
        static const uint_fast32_t OPT_RESOLVE_LINKS = 8;
        static const uint_fast32_t OPT_PRE_ORDER = 16;
        static const uint_fast32_t OPT_POST_ORDER = 32;

        //! the root for the tree walk
        StringObj m_start_path;

        //! bitwise or'ed options
        uint_fast32_t m_opts;

        //! the current walk result value
        WalkReturn m_walk_res;

        //! c++-style callback interface
        IEntryProcessor &m_tw;

        //! whether the root of the tree walk is a directory or not
        bool m_root_is_dir;

        //! a pair of a directory plus it's associated FileInfo's
        typedef ipl::pair< osal::Directory*, osal::FileInfo* >
            DirInfoPair;
        //! a stack of DirInfoPair's
        typedef ipl::stack< DirInfoPair > DirStack;

        //! the current path we're working at
        PathObj m_cur_path;

        //! Stack of the leftover dir's that still need processing
        DirStack m_left_dirs;

        //! the current walk status
        typename IEntryProcessor::WalkStatus m_status;

        //! the basename offsets of the previous path components
        ipl::stack<int_fast16_t> m_bn_offsets;

        //! \brief
        //! The file system ID for the starting directory as returned
        //! from osal::FileInfo::getFsId()
        osal::FileSysID m_root_fs_id;

        //! \brief
        //! The working directory as it was found before the algorithm
        //! started
        StringObj m_old_cwd;
    }; // end class

    struct TreeWalker :
        public TreeWalkerBase< char* >
    {
        TreeWalker( IEntryProcessor &iep ) :
            TreeWalkerBase< char* >(iep) { };
    };

    typedef TreeWalkerBase< wchar_t* > TreeWalkerWide;

    #ifndef OSAL_EXPORT_CONTEXT

    /*
    * the following declarations are necessary for certain gcc version
    * (notably 4.3.3 for qnx x86) to make it satisfied about "explicit
    * instantiation of TreeWalkerBase<...> but not definition given.
    *
    * Somehow these gcc versions don't understand that there is very well a
    * definition given directly upon declaration.
    *
    * These statements help the compiler understand this obviously.
    */

    template <typename STRING>
    const int_fast32_t TreeWalkerBase< STRING >::WalkReturn::WALK_OKAY;
    template <typename STRING>
    const int_fast32_t TreeWalkerBase< STRING >::WalkReturn::WALK_ERROR;
    template <typename STRING>
    const int_fast32_t TreeWalkerBase< STRING >::WalkReturn::SKIP_DIRECTORY;

    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::IEntryProcessor::WalkStatus::DIR_FINISHED;
    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::IEntryProcessor::WalkStatus::DIR_NO_ACCESS;
    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::IEntryProcessor::WalkStatus::NO_INFO_AVAIL;

    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::OPT_CHANGE_WD;
    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::OPT_DEPTH;
    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::OPT_SAME_FS;
    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::OPT_RESOLVE_LINKS;
    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::OPT_PRE_ORDER;
    template <typename STRING>
    const uint_fast32_t TreeWalkerBase< STRING >::OPT_POST_ORDER;
    #endif


    #ifdef OSAL_USE_PATH
    template <typename PATH>
    inline void appendEntryToPath(PATH &p, const char*)
    {
    }

    template <>
    inline void appendEntryToPath(osal::Path &p, const char *s)
    {
        p.append( s );
    }

    template <>
    inline void appendEntryToPath(osal::WidePath &p, const char *s)
    {
        // assumming conversion to wide string doesn't need length
        osal::UnicodeString ucs(s, 0, osal::UnicodeString::SHARED);

        p.append( ucs );
    }
    #endif

    #ifdef OSAL_USE_WIDEPATH
    template <typename PATH>
    inline void appendEntryToPath(PATH &p, const wchar_t*)
    {
    }

    template <>
    inline void appendEntryToPath(osal::Path &p, const wchar_t *s)
    {
        UnicodeString ucs( (const char*)s, 0,
            osal::UnicodeString::SHARED );

        p.append( static_cast<ipl::string>(ucs) );
    }

    template <>
    inline void appendEntryToPath(osal::WidePath &p, const wchar_t *s)
    {
        p.append( s );
    }
    #endif

}  // end of namespace osal

#endif
