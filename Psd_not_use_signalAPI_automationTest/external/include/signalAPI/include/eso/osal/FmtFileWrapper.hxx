/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_FMTFILEWRAPPER_HXX
#define OSAL_FMTFILEWRAPPER_HXX

#include <common/types/string.hxx>
#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/FileBuffer.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    template <typename S>
    inline bool ClosePolicy(S &s)
    {
        s << ipl::flush;

        if( s.bad() )
        {
            return true;
        }

        return false;
    }

    template <>
    inline bool ClosePolicy<ipl::istream>(ipl::istream &s)
    { return false; }


    template <typename F, typename S, typename FL>
    /**
    * \brief
    *    Generically connects a StreamBinFile to an STL stream interface
    *    via an osal::FileBuffer object

    *    This type makes it possible to use an StreamBinFile* with an
    *    ipl::*stream compatible interface.
    *
    *    The buffering mechanism of the IBin[In,Out,InOut]Stream is never
    *    used but the FileBuffer is used for buffering instead (i.e.
    *    buffering is done the STL way)
    *
    *    By default the FileBuffer is sized to 8 kilobytes which is
    *    similar to what the ipl::fstream does.
    *
    *    The template parameter F denotes the StreamBinFile type to wrap.
    *    The parameter S denotes the STL stream interface to implement.
    *    The parameter FL denotes the [Read,Write,ReadWrite]Flags to use
    *    for constructing and opening files.
    *
    *    The StreamFmtFile F is a member of the class instead of a base
    *    of the class. This is to prevent a number of problems:
    *
    *    - both stream APIs would be exposed but the APIs are conflicting
    *    each other
    *    - both stream APIs provide read() and write() which makes
    *    trouble due to the Koenig lookup of C++
    * \example
    *    typedef FmtFileWrapper<MyBinStreamFileType,
    *        ipl::istream, BinStreamBase::ReadFlags>
    *    MyFmtStreamFileType;
    *
    *     // tada! have a formatted interface for MyBinStreamFileType
    *    MyFmtStreamFileType fmt_file;
    **/
    class /* OSAL_EXPORT win32 can't deal with export of all inline class */
        FmtFileWrapper :
        public S
    {
    public: // types
        typedef FL Flags;
        typedef osal::BinFileBase::ReadFlags ReadFlags;
        typedef osal::BinFileBase::WriteFlags WriteFlags;
    public: // functions

        /**
        * \brief
        *    Construct an invalid file, setting up a buffer of \c
        *    bufsize bytes

        *    To open a file use the open() functions provided by
        *    StreamBinFileR.
        **/
        explicit FmtFileWrapper(const size_t bufsize = 8192) :
            S(NULL),
            m_fil(),
            m_buf(&m_fil, bufsize)
        {
            this->init( &m_buf );
            checkState();
        }

        /**
        * \brief
        *    Opens the file at path \c p, sets up a buffer of \c
        *    bufsize bytes
        **/
        explicit FmtFileWrapper(const ipl::string &p,
                const FL flags = FL(),
                const size_t bufsize = 8192,
                const FileAccess &access =
                    FileAccess::owner_read|FileAccess::owner_write|
                    FileAccess::group_read|FileAccess::group_write) :
            S(NULL),
            m_fil(p, flags, access),
            m_buf(&m_fil, bufsize)
        {
            this->init( &m_buf );
            checkState();
        }

        /**
        * \brief
        *     Opens the file at unicode path \c ucs, sets up a buffer
        *     \c bufsize bytes
        **/
        explicit FmtFileWrapper(const osal::UnicodeString &ucs,
            const FL flags = FL(),
            const size_t bufsize = 8192,
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) :
            S(NULL),
            m_fil(ucs, flags, access),
            m_buf(&m_fil, bufsize)
        {
            this->init( &m_buf );
            checkState();
        }

        //! constructor variant for BinTempFileRW
        template<typename TEMPFILE>
        explicit FmtFileWrapper(TEMPFILE &o,
                const bool auto_delete,
                const size_t bufsize = 8192) :
            S(NULL),
            m_fil(o, auto_delete),
            m_buf(&m_fil, bufsize)
        {
            this->init( &m_buf );
            checkState();
        }

        //! constructor variant for Pipe
        template<typename PIPE>
        explicit FmtFileWrapper(PIPE &p,
            const size_t bufsize = 8192) :
            S(NULL),
            m_fil(p),
            m_buf(&m_fil, bufsize)
        {
            this->init( &m_buf );
            checkState();
        }

        ~FmtFileWrapper()
        {
            if( this->close() ) // BRANCH_COVERAGE_UNTESTABLE
            {
                // well we're screwed ...
                IPL_WARN("Error closing underlying file");
            }
        }

        bool close()
        {
            bool error = false;

            if( m_fil.isValid() )
            {
                error = ClosePolicy<S>(*this);
            }

            m_buf.reset();
            error |= m_fil.close();

            this->clear();

            return error;
        }

        /**
        * \brief
        *    Open a (possibly new) file

        *    Forwards the call to FL::open(const ipl::string, const
        *    FL)
        **/
        bool open(const ipl::string &p,
            const FL &flags = FL(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            return this->close() || m_fil.open(p, flags, access); // BRANCH_COVERAGE_UNTESTABLE
        }

        /**
        * \brief
        *     Open a (possibly new) file at a unicode path

        *     Forwards the call to FL::open(const
        *     osal::UnicodeString&, const FL)
        **/
        bool open(const osal::UnicodeString &ucs,
            const FL &flags = FL(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write)
        {
            return this->close() || m_fil.open(ucs, flags, access); // BRANCH_COVERAGE_UNTESTABLE
        }

        //! open variant for BinTempFileRW
        template<typename TMPFILE>
        bool open(TMPFILE &o, const bool auto_delete)
        {
            return this->close() || m_fil.open(o, auto_delete); // BRANCH_COVERAGE_UNTESTABLE
        }

        //! open variant for Pipe
        template<typename PIPE>
        bool open(PIPE &p)
        {
            return this->close() || m_fil.open(p); // BRANCH_COVERAGE_UNTESTABLE
        }

        //! returns whether the file is valid and open
        bool isValid() const
        {
            return m_fil.isValid();
        }

        //! returns whether the last operation failed
        bool hasError() const
        {
            return m_fil.hasError();
        }

        const F& getFile() const
        { return m_fil; }

        //! \brief
        //! be careful when accessing the underlying binary file. you
        //! could mess up the streams library logic.
        F& getFile()
        { return m_fil; }
    protected: // functions

        /**
        * \brief
        *     Adjust the stream state if the file state is bad
        **/
        void checkState()
        {
            if( ! m_fil.isValid() )
            {
                this->setstate(ipl::ios_base::badbit);
            }
        }

    protected: // data
        //! the contained binary file type
        F m_fil;
        //! the buffer connecting the binary stream to the formatted stream
        osal::FileBuffer m_buf;
    };

}  // end of namespace osal

#endif
