/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_BINBUFFER_HXX
#define IPL_BINBUFFER_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <common/iplcommon_dso.h>
#include <common/stdint.h>
#include <common/Macros.hxx>
#include <common/IBinInputStream.hxx>
#include <common/IBinOutputStream.hxx>
#include <common/streams/streambuf.hxx>

#include <string.h>

namespace IPL_NAMESPACE
{

/**
 * \brief
 *    Generic adapter from IBin{Input,Output}Streams to STL compatible
 *    formatted streams

 *    This adapter allows to create an STL streams library compatible
 *    stream on top of IBin{Input,Output}Streams.
 *
 *    Where the binary streams provide only unformatted operations
 *    intended for efficient access to devices and OS facilities the
 *    STL streams provide fully fledged formatted operations and a
 *    well-known interface.
 *
 *    Some restriction apply to the adapter, however:
 *
 *    - currently seeking is not possible (this only affects regular
 *    files and device drivers, usually)
 *    - some more exotic operations like putback, showmanyc also
 *    aren't provided (they mostly can't be provided by concrete
 *    implementations anyway)
 *    - the ability to change the underlying buffer on a constructed
 *    object is also not given. instead you decide at construction
 *    time if an internal buffer is used an of what size it is. Also
 *    an external buffer may be provided this way.
 *    - the underlying binary stream is not allowed to have buffering
 *    itself as that would not make sense. Instead the special streams
 *    library buffering scheme is employed.
 *    - we don't maintain a common buffer for both input and output.
 *    i.e. this buffer does not consider seeking is possible and does
 *    once read data can be obtained again.
 *
 *    This BinBuffer can be seen in line with the streams library
 *    standard filebuf or streambuf. It's the basis to connect
 *    concrete implementations of binary streams in a generic way to
 *    the streams library interface, formatted operations and
 *    buffering scheme.
 * \warning
 *    The BinBuffer considers itself responsible for the wrapped
 *    binary streams. The binary streams API should not be handled any
 *    more from outside the streams library interface any more. Else
 *    you have to deal with the terrible consequences.
**/
class IPLCOMMON_EXPORT BinBuffer :
    public ipl::streambuf
{
public:    // functions

    /**
     * \brief
     *    Create a streams library adapter for the given binary stream(s)
     * \param[in,out] in
     *    The binary input stream this BinBuffer should care for.
     *    If NULL then all input operations on the buffer fail.
     * \param[in,out] out
     *    The binary output stream this BinBuffer should care for.
     *    If NULL then all output operations on the buffer fail.
     **/
    BinBuffer(
        IBinInputStream *in,
        IBinOutputStream *out,
        size_t inbufsize = 8192,
        size_t outbufsize = 8192,
        void *extinbuf = NULL,
        void *extoutbuf = NULL) IPL_NOEXCEPT :
            m_in(in),
            m_out(out),
            // in the unbuffered case we still need at least
            // one byte for correct operation
            m_inbuf_size(inbufsize ? inbufsize : 1),
            m_outbuf_size(outbufsize ? outbufsize : 1),
            m_inbuf( extinbuf ? (char*)extinbuf :
                new(ipl::nothrow) char[m_inbuf_size]),
            m_outbuf( extoutbuf ? (char*)extoutbuf :
                new(ipl::nothrow) char[m_outbuf_size]),
            m_internal_inbuf( !extinbuf ),
            m_internal_outbuf( !extoutbuf )
    {
        if( m_internal_inbuf && m_inbuf_size && !m_inbuf ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_ABORT("Error allocating buffer for BinBuffer");
        }
        else if( m_internal_outbuf && m_outbuf_size && !m_outbuf ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_ABORT("Error allocating buffer for BinBuffer");
        }

        IPL_ASSERT( !in || ! in->isInputBuffered() );
        IPL_ASSERT( !out || ! out->isOutputBuffered() );

        // empty put and get areas for the start
        resetBothWindows();
        // free the complete output buffer for usage
        adjustOutBuffer(0);
    }

    ~BinBuffer() IPL_NOEXCEPT
    {
        if( m_internal_inbuf )
            delete[] m_inbuf;

        if( m_internal_outbuf )
            delete[] m_outbuf;
    }
    
    BinBuffer(const BinBuffer &)=delete;
    BinBuffer &operator = (const BinBuffer &)=delete;
    
protected: // functions

    // seek is currently not supported on an abstract level (only on BinFileBase)
    //virtual streampos seekoff(streamoff off, ios_base::seekdir way,
    //    ios_base::openmode which = ios_base::in | ios_base::out );
    //
    //virtual streampos seekpos(streampos sp,
    //    ios_base::openmode which = ios_base::in | ios_base::out)

    /**
     * \brief
     *    Synchronize any yet unwritten data with underlying
     *    device

     *    In principle calls IBinOutputStream::flush()
     **/
    virtual int sync();

    /**
     * \brief
     *     Read more data from input stream

     *     In principle calls IBinInputStream::read()
     **/
    virtual int underflow();

    /**
     * \brief
     *     Write buffered data to output stream

     *     In principle calls IBinOutputStream::write()
     **/
    virtual int overflow(int c = EOF);

    void resetBothWindows() IPL_NOEXCEPT
    {
        resetGetWindow();
        resetPutWindow();
    }

    //! \brief
    //!    resets the get area such that it is zero-sized (i.e. no
    //!    data can be read from the buffer
    void resetGetWindow() IPL_NOEXCEPT
    {
        // all three are equal then
        if( m_in )
            this->setg(m_inbuf, m_inbuf, m_inbuf);
    }

    //! \brief
    //!    resets the put area such that it is zero-sized (i.e. no
    //!    data can be written to the buffer
    void resetPutWindow() IPL_NOEXCEPT
    {
        if( m_out )
            this->setp(NULL, NULL);
    }

    //! \brief
    //!    removes \c written character from the output buffer and
    //!    makes the new room available in the put window
    void adjustOutBuffer(const size_t written) IPL_NOEXCEPT
    {
        const size_t buffed_chars = pptr() - pbase();

        // only make output buffer available if more than one
        // character is there. this is for the special overflow
        // char semantics upon overflow()
        if( m_out && m_outbuf_size > 1 )
        {
            if( buffed_chars == written )
            {
                // we report only bufsize - 1 as we
                // reserve one character for the
                // overflow character in overflow()
                this->setp(m_outbuf, m_outbuf +
                    m_outbuf_size - 1);
            }
            else
            {
                const size_t left_chars = buffed_chars -
                    written;

                // only part of the out buffer was
                // written. we need to relocate
                ::memmove( m_outbuf, m_outbuf + written,
                    left_chars );

                this->setp( m_outbuf, m_outbuf +
                    left_chars );
            }
        }
    }

    //! \brief
    //!    adds \c read characters  to the input buffer and makes
    //!    the new data available in the get window
    void adjustInBuffer(const size_t read) IPL_NOEXCEPT
    {
        this->setg(m_inbuf, m_inbuf, m_inbuf + read);
    }

protected: // data
    //! associated binary input stream, NULL if none
    IBinInputStream *m_in;
    //! associated binary output stream, NULL if none
    IBinOutputStream *m_out;

    //! size of m_inbuf in bytes
    size_t m_inbuf_size;

    //! size of m_outbuf in bytes
    size_t m_outbuf_size;

    //! buffer to use for input, NULL if unbuffered
    char *m_inbuf;

    //! buffer to use for output, NULL if unbuffered
    char *m_outbuf;

    //! whether m_inbuf is a buffer allocated by BinBuffer
    bool m_internal_inbuf;

    //! whether m_outbuf is a buffer allocated by BinBuffer
    bool m_internal_outbuf;
}; // end class

} // end namespace ipl

#endif
