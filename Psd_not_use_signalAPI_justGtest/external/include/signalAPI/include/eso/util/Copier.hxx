/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <ipl_config.h>

#include <util/FileSys.hxx>

#include <iplbase/exceptions.hxx>
#include <common/CommonError.hxx>
#include <common/error/ErrorHelper.hxx>
#include <osal/SysError.hxx>
#include <osal/FileSys.hxx>
#include <osal/FileInfo.hxx>
#include <osal/TreeWalker.hxx>
#include <osal/Path.hxx>
#include <osal/OpenError.hxx>

#include <string.h>

namespace util {

    //! \brief
    //! helper class for implementation of util::FileSys's recursive copy
    //! operations
    template <typename STRING>
    class Copier :
        public osal::TreeWalkerBase<STRING>::IEntryProcessor
    {
    public: // types
        typedef typename osal::PathTraits<STRING> Traits;
        typedef typename Traits::StringPointer StringPointer;
        typedef typename Traits::ConstStringPointer ConstStringPointer;
        typedef typename Traits::StringObj StringObj;
        typedef typename Traits::Character Character;
        typedef typename Traits::PathObj PathObj;
        typedef typename Traits::ApiObj ApiObj;
    public: // types
        typedef typename util::FileSysBase<STRING>::ICopyHandler
            ICopyHandler;

        typedef typename ICopyHandler::CopyStatus CopyStatus;

        typedef typename ICopyHandler::CopyReturn CopyReturn;

        typedef typename osal::TreeWalkerBase<STRING> TreeWalker;

        typedef typename TreeWalker::WalkReturn WalkReturn;

        typedef typename TreeWalker::IEntryProcessor IEntryProcessor;

        typedef typename IEntryProcessor::WalkStatus WalkStatus;
    public:
        Copier(
            ConstStringPointer s,
            ConstStringPointer d,
            ICopyHandler *ch) IPL_NOEXCEPT;

        ~Copier() IPL_NOEXCEPT
        {
            delete[] m_copy_buf;
        }

        virtual WalkReturn processEntry(
            ConstStringPointer relpath,
            const osal::FileInfo &info,
            const WalkStatus &ws) IPL_NOEXCEPT;

        virtual WalkReturn processError(
            ConstStringPointer relpath,
            const osal::FileInfo &info,
            const WalkStatus &ws) IPL_NOEXCEPT;

        CopyReturn getResult() const IPL_NOEXCEPT
        { return m_cr; }

        bool isValid() const IPL_NOEXCEPT
        {
            return m_is_valid;
        }
    private:
        PathObj m_src;
        PathObj m_dst;
        ICopyHandler *m_ch;
        uint_fast16_t m_cur_path_depth;
        bool m_dst_is_dir;
        CopyReturn m_cr;
        bool m_root_is_file;
        uint8_t *m_copy_buf;
        uint_fast32_t m_copy_buf_size;
        bool m_is_valid;
    };

    template <typename STRING>
    Copier<STRING>::Copier(
        ConstStringPointer s,
        ConstStringPointer d,
        ICopyHandler *ch) IPL_NOEXCEPT :
            m_src(s), m_dst(d), m_ch(ch),
            m_cur_path_depth(0), m_dst_is_dir(false),
            m_root_is_file(false), m_copy_buf(NULL),
            m_copy_buf_size(0), m_is_valid(true)
    {
        osal::FileInfo dst_info( static_cast<ApiObj>(m_dst) );

        if( !dst_info.isValid() )
        {
            // okay, seems the caller specified a different basename
            // to use
            ipl_error.ack();

            // we need to get IO buffer size for the target.  if
            // this still doesn't work then something is wrong in
            // general and algorithm will abort accordingly.
            dst_info = osal::FileInfo( osal::UnicodeString(m_dst.getDirname()) );

            if( ! dst_info.isValid() )
            {
                ipl_error.ack();
                // value from c-library. not particularly well
                // suited but anyway ...  at least something.
                m_copy_buf_size = BUFSIZ;
            }
        }
        else if( dst_info.getType() == osal::FileInfo::DIRECTORY )
        {
            // m_dst_basename_offset = m_dst.size();

            // seems the caller wants to keep the basename of m_src
            // and put it into the directory m_dst.
            //
            // add the basename to dst
            m_dst.addComponent( m_src.getBasename() );
        }

        if( dst_info.isValid() )
        {
            m_copy_buf_size = dst_info.IOBlockSize();
        }

        m_copy_buf = new(ipl::raise_error) uint8_t[m_copy_buf_size];

        if ( ! m_copy_buf ) // BRANCH_COVERAGE_UNTESTABLE
        {
            m_is_valid = false;
            return;
        }

        osal::FileInfo src_info( static_cast<ApiObj>(m_src) );

        if( ! src_info.isValid() ) // BRANCH_COVERAGE_UNTESTABLE
            ipl_error.ack();
        else if( src_info.getType() != osal::FileInfo::DIRECTORY )
            m_root_is_file = true;

        // note: if still anything is wrong like src not being a
        // dir, dst not being a valid path and stuff then walk()
        // will fail accordingly.
    }

    template <typename STRING>
    typename Copier<STRING>::WalkReturn
    Copier<STRING>::processEntry(
        ConstStringPointer relpath,
        const osal::FileInfo &info,
        const WalkStatus &ws) IPL_NOEXCEPT
    {
        m_cr.reset();
        CopyStatus cs(ws);

        // we left some directory. need to adjust m_dst
        while( m_cur_path_depth &&
            m_cur_path_depth >= ws.getPathDepth() )
        {
            m_dst.removeComponent();
            m_cur_path_depth--;
        }

        if( !ws.isDir() && !m_root_is_file )
            // temporarily add current basename to copy to
            m_dst.addComponent( ws.getBasename() );
        else if( ws.isDir() && ws.getPathDepth() )
        {
            // if this is the root of the tree then we don't need to
            // add the current directory as the root is added at
            // construction time already, if necessary
            m_dst.addComponent( ws.getBasename() );
            m_cur_path_depth++;
        }

        if( m_ch )
        {
            IPLBASE_ABORT_ON_EXCEPTION(
                m_cr = m_ch->checkCopy( relpath,
                    m_dst.c_str(), info, cs );
            )

            if( m_cr.walkError() )
            {
                return m_cr;
            }
            else if( m_cr.skipCopy() )
            {
                m_cr.reset();

                // additionally tell tree walker to skip the
                // current directory if it is one
                m_cr.setSkipDirectory();

                return m_cr;
            }
        }

        bool keep_trying = true;

        while ( keep_trying )
        {
            keep_trying = false;

            bool have_error = false;

            // in this case we simply need to create our
            // directory
            if( ws.isDir() )
            {
                have_error = osal::FileSys::createDir(
                    static_cast<ApiObj>(m_dst) );
            }
            else if( osal::FileSys::copy(
                static_cast<ApiObj>(static_cast<StringObj>(relpath)),
                static_cast<ApiObj>(m_dst),
                m_copy_buf_size,
                m_copy_buf ) )
            {
                have_error = true;
            }

            if( have_error )
            {
                if( ipl_error.isA( osal::SysError ) )
                {
                    switch( ipl_error.id() )  // BRANCH_COVERAGE_UNTESTABLE
                    {
                    case osal::FILE_EXISTS:
                        cs.setDstExists();
                        break;
                    case osal::PERMISSION_DENIED:
                        cs.setCannotWriteDst();
                        break;
                    default:
                        cs.setOtherCopyError();
                        break;
                    }
                }
                else
                {
                    cs.setOtherCopyError();
                }

                if( m_ch )
                {
                    m_cr = m_ch->copyError( relpath,
                        m_dst.c_str(), info, cs );
                    ipl_error.ack();

                    if( m_cr.retryCopy() )
                    {
                        keep_trying = true;
                        m_cr.reset();
                    }
                }
                else
                {
                    // keep error active in this case such
                    // that client can check the error
                    m_cr.setError();
                }
            }
        } // end while keep_trying

        if( !ws.isDir() && !m_root_is_file )
            // remove basename again
            m_dst.removeComponent();

        return m_cr;
    }

    template <typename STRING>
    typename Copier<STRING>::WalkReturn
    Copier<STRING>::processError(
        ConstStringPointer relpath,
        const osal::FileInfo &info,
        const WalkStatus &ws) IPL_NOEXCEPT
    {
        CopyStatus cs(ws);

        if( m_ch )
        {
            m_dst.addComponent( ws.getBasename() );
            cs.setCannotReadSrc();
            m_cr = m_ch->copyError( relpath,
                m_dst.c_str(), info, cs );
            m_dst.removeComponent();
        }
        else
        {
            m_cr.setError();
            ipl_raise( osal::SysError,
                osal::PERMISSION_DENIED, relpath );
        }

        return m_cr;
    }

}  // end of namespace util
