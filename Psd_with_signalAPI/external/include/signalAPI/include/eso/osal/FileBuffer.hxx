/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_FILEBUFFER_HXX
#define OSAL_FILEBUFFER_HXX

#include <ipl_config.h>

#include <common/streams/fstream.hxx>
#include <common/Macros.hxx>
#include <osal/osal_dso.h>
#include <osal/StreamBinFileR.hxx>
#include <osal/StreamBinFileW.hxx>
#include <osal/StreamBinFileRW.hxx>

namespace osal
{

/**
 \brief
    Adapter from osal::StreamBinFiles to ipl streams library

    This is an adapter similar to ipl::BinBuffer. Whilst
    ipl::BinBuffer is a generic adapter, this adapter only connects
    the concrete StreamBinFiles in OSAL to the STL compatible
    streams library in iplcommon.

    This is necessary as the ipl::filebuf that is used for
    ipl::ifstream and ipl::ofstream implements a special semantic
    that requires seeking to be possible which is not possible in
    general for binary input and output streams in OSAL.

    What this adapter makes possible is to use OSAL StreamBinFiles
    together with the STL compatible streams library and make them
    behave just like ipl::ifstream and ipl::ofstream.
**/
class OSAL_EXPORT FileBuffer :
    public ipl::filebuf_base
{
public:    // functions
    //! constructs an invalid file buffer
    FileBuffer() IPL_NOEXCEPT :
        filebuf_base( ipl::ios::openmode(0) ),
        m_in(NULL),
        m_out(NULL),
        m_stream(NULL)
    { }

    /**
     * \brief
     *    Create a streams library adapter for the given binary
     *    read-only file stream
     **/
    FileBuffer(StreamBinFileR *in, const size_t bufsize = 8192,
            const void *extbuf = NULL) IPL_NOEXCEPT :
        filebuf_base( ipl::ios_base::openmode( ipl::ios::in ) ),
        m_in(in),
        m_out(NULL),
        m_stream(in)
    {
        init(bufsize, extbuf);
        IPL_ASSERT( in && ! in->isInputBuffered() );
    }

    /**
     * \brief
     *    Create a streams library adapter for the given binary
     *    write-only file stream
     **/
    FileBuffer(StreamBinFileW *out, const size_t bufsize = 8192,
            const void *extbuf = NULL) IPL_NOEXCEPT :
        filebuf_base( ipl::ios_base::openmode( ipl::ios::out ) ),
        m_in(NULL),
        m_out(out),
        m_stream(out)
    {
        init(bufsize, extbuf);
        IPL_ASSERT( out && ! out->isOutputBuffered() );
    }

    /**
     * \brief
     *    Create a streams library adapter for the given binary
     *    read-write file stream
     **/
    FileBuffer(StreamBinFileRW *in_out, const size_t bufsize = 8192,
            const void *extbuf = NULL) IPL_NOEXCEPT :
        filebuf_base( ipl::ios_base::openmode( ipl::ios::out )
            | ipl::ios_base::openmode( ipl::ios::in ) ),
        m_in(in_out),
        m_out(in_out),
        m_stream(in_out)
    {
        init(bufsize, extbuf);
        IPL_ASSERT( in_out
            && ! in_out->isInputBuffered()
            && ! in_out->isOutputBuffered() );
    }

    ~FileBuffer() IPL_NOEXCEPT override
    {
        this->destroyBuffer();
    }

    void reset() IPL_NOEXCEPT
    {
        this->destroyBuffer();
        this->createBuffer();
    }
protected: // functions

    void init(const size_t bufsize, const void *extbuf) IPL_NOEXCEPT
    {
        m_buf = ( extbuf ? (char*)extbuf : NULL );
        // in the unbuffered case we still need at least one
        // byte for correct operation
        m_buf_size = (bufsize ? bufsize : 1);
        m_external_buf = extbuf != NULL;

        this->createBuffer();
    }

    //! \brief
    //! translates the streams library seek parameters to
    //! StreamBinFile seek parameters
    virtual bool actuallySeek(const ipl::streamoff off,
        const ipl::ios_base::seekdir way,
        ipl::streampos &now) IPL_NOEXCEPT;

    //! \brief
    //! translates the streams library read parameters to
    //! StreamBinFile read parameters
    virtual bool actuallyRead(char *to, const size_t max,
            size_t &read) IPL_NOEXCEPT;

    //! \brief
    //! translates the streams library write parameters to
    //! StreamBinFile write parameters
    virtual bool actuallyWrite(const char *from,
        const size_t count,
        size_t &written) IPL_NOEXCEPT;

    //! forwards the flush request to the StreamBinFile
    virtual bool actuallyFlush() IPL_NOEXCEPT;

    //! maps to isValid() of the StreamBinFiles
    bool isOpen() IPL_NOEXCEPT
    {
        return ( !m_in || m_in->isValid() )
            && ( !m_out || m_out->isValid() );
    }

protected: // data
    //! associated file input stream, NULL if none
    ipl::IBinInputStream *m_in;
    //! associated file output stream, NULL if none
    ipl::IBinOutputStream *m_out;
    //! associated with seekable stream, NULL if none
    StreamBinFileBase *m_stream;
}; // end class

} // end namespace osal

#endif
