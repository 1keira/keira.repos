/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef IPL_FSTREAM_HXX
#define IPL_FSTREAM_HXX

// note: we need filebuf_base for OSAL file API in any case std or ipl
// STL

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <fstream>

#include <stdio.h>

// #include <common/streams/streamtypes.hxx>
#include <common/streams/ios.hxx>

#include <common/streams/streambuf.hxx>
#include <common/streams/istream.hxx>
#include <common/streams/ostream.hxx>

#include <common/types/string.hxx>
#include <common/iplcommon_dso.h>
#include <common/Macros.hxx>


namespace IPL_NAMESPACE {

    using std::basic_filebuf;
    using std::basic_ifstream;
    using std::basic_ofstream;
    using std::basic_fstream;

    using std::filebuf;
    using std::wfilebuf;
    using std::ifstream;
    using std::wifstream;
    using std::ofstream;
    using std::wofstream;
    using std::fstream;
    using std::wfstream;
    using std::swap;
}


namespace IPL_NAMESPACE
{

/**
 * \brief
 *     A streambuf that can read/write from/to files

 *     A filebuf is associated with a physical file in the system. It
 *     operates as defined in the streambuf base class, with the
 *     particularity that a joint position pointer is maintained for
 *     both, the input and output sequence.
 *
 *     As the case with C stdio API the user can mix input and output
 *     operations on the buffer. But between switches from input to
 *     output and vice versa the user needs to perform a seek operation
 *     on the buffer (a null-operation like seekg(0, cur) or seekp(0,
 *     cur) suffices). Otherwise errors or undefined results occur.
 *
 *     This is a slightly more abstract variant of filebuf. It keeps
 *     the actual I/O operations still virtual but it maintains the
 *     joint file pointer positions, read/write mode and all the
 *     semantics. This is because we need to immplement two variants of
 *     this buffer. One that sits on top of C fstreams and one that
 *     sits on top of OSAL.
 **/
class IPLCOMMON_EXPORT filebuf_base :
    // we implement the streambuf interface
    public streambuf
{
protected: // types and constants
    //! \brief
    //! special value used in applyWindows(): reset windows to
    //! contain no elements
    static const streamsize RESET_WINDOWS = -1;
    //! special value used in applyWindows(): provide empty window
    static const streamsize EMPTY_WINDOWS = 0;

    //! \brief
    //!    some arbitrary character that does _not_ equal EOF (for
    //!    return value of overflow and similar)
    static const char NOT_EOF = '0';
public: // methods
    //! initializes internal variables and calls streambuf()
    inline filebuf_base(ios_base::openmode om) IPL_NOEXCEPT :
        streambuf(),
        m_buf(NULL),
        m_buf_size(0),
        m_file_mode(om),
        m_external_buf(false),
        m_read_mode(false),
        m_write_mode(false)
    {
        applyWindows(RESET_WINDOWS);
    }
    
protected: // inherited and overriden virtual methods

    /**
     * \brief
     *     Get new data from real input source on empty buffer
     **/
    int underflow();

    /**
     * \brief
     *     Transfer characters to the real output destination when
     *     the buffer is full.
     **/
    int overflow(int c = EOF);

    /**
     * \brief
     *     set the internal position pointer to a new relative
     *     position
     * \note
     *     As filebuf maintains a single position pointer for input
     *     and output the which parameter is to be ignored.
     *
     *     Seeking implies syncing if there is unwritten data
     *     present.
     *
     *     After a successful seek operation the input/output mode
     *     of the buffer may be changed by the client.
     * \return
     *     new position or -1 on error.
     **/
    inline streampos seekoff(streamoff off, ios_base::seekdir way,
        ios_base::openmode which = ios_base::in | ios_base::out);

    /**
     * \brief
     *     Set the internal position pointer to a new absolute
     *     position
     * \note
     *     As filebuf maintains a single position pointer for input
     *     and output the which parameter is to be ignored.
     *
     *     Seeking implies syncing if there is unwritten data
     *     present.
     *
     *     After a successful seek operation the input/output mode
     *     of the buffer may be changed by the client.
     * \return
     *     new position or -1 on error.
     **/
    inline streampos seekpos(streampos sp,
        ios_base::openmode which =
            ios_base::in | ios_base::out);

    /**
     * \brief
     *     Synchronizes internal character sequence with file content
     * \return
     *     zero on success, -1 on error
     **/
    int sync();

    // unimplemented functions -> deviation from the standard

    /*
     * left out because putback stuff seems to be a pain in the ass
     * with questionable value
     */
    //int pbackfail(int c = EOF);

    /*
     * we don't do locale stuff
     */
    //void imbue(const locale &loc);
protected: // member functions
    /**
     * \brief
     *     Applies new buffer windows by setting new put and get
     *     areas
     * \param[in]
     *     p_offset Offset to apply to the buffer window, or
     *     special values EMPTY_WINDOWS and RESET_WINDOWS.
     *
     *     If RESET_WINDOWS is passed then the get and put windows
     *     will be zero sized and thus any subsequent i/o operation
     *     will result in overflow or underflow.
     *
     *    If EMPTY_WINDOWS is passed then the get window will be
     *    zero sized and the put window will cover the complete
     *    buffer (i.e. the complete buffer can be used for caching
     *    output characters).
     *
     *     If a value > 0 is passed then the get area will contain
     *     p_offset many characters starting at the beginning of
     *     the buffer area. The put area will be zero sized in this
     *     case.
     * \note
     *     Here we have some special semantics: As the user of the
     *     buffer may only switch from input to output and vice
     *     versa after a seek operation we can always occupy the
     *     complete buffer for one mode of operation until a switch
     *     of operation occurs.
     *
     *     The current mode of operation is given via m_read_mode
     *     and m_write_mode. If both are false then there the
     *     current mode is undetermined and may become either one
     *     upon an input or output operation on the buffer. The
     *     setting of the mode is usually done in the overflow or
     *     underflow implementations.
     *
     *     If m_read_mode is true then the buffer is currently
     *     performing input. No output is allowed in this mode.
     *     During input mode the buffer windows are set in a way
     *     that the put window will be zero sized. The get window
     *     will have the size that covers any buffered input
     *     characters or being zero sized if buffering is turned
     *     off. To disable the read mode setting a seek operation
     *     needs to be performed on the buffer.
     *
     *     If m_write_mode is true then the buffer is currently
     *     performing output. No input is allowed in this mode.
     *     During output mode the buffer windows are set in a way
     *     that the put window will cover the complete buffer range
     *     and be able to buffer output characters until the buffer
     *     is full or synced. The get window will be zero sized. To
     *     disable the write mode setting a seek operation needs to
     *     be performed on the buffer.
     **/
    inline void applyWindows(streamsize p_offset) IPL_NOEXCEPT;

    //! \brief
    //! resets buffer pointer and size, deletes buffer if internal,
    //! resets buffer windows
    void destroyBuffer() IPL_NOEXCEPT;

    //! creates a suitable buffer acc. to m_buf_size
    void createBuffer() IPL_NOEXCEPT;

    /**
     * \brief
     *    Actually read up to \c max characters into memory
     *    starting at \c to

     *    returns how many characters have been read in \c read
     * \return
     *    false on success, true on EOF/error.
     **/
    virtual bool actuallyRead(char *to, const size_t max, size_t &read) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Actually write \c count characters from \c from to the
     *     file returning the number of written characters in \c
     *     written
     * \return
     *     true on error, false otherwise
     **/
    virtual bool actuallyWrite(const char *from,
        const size_t count, size_t &written) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Do an actual seek operation relative to way, off characters far

     *     new position is returned in \c now
     * \return
     *     true on error, false on success
     **/
    virtual bool actuallySeek(const streamoff to,
        const ios_base::seekdir way, streampos &now) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Actually perform a flush operation on the file
     **/
    virtual bool actuallyFlush() IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Return true if the file is currently open, false otherwise
     **/
    virtual bool isOpen() IPL_NOEXCEPT = 0;

protected: // members
    //! Pointer to client provided buffer or internally allocated buffer
    char *m_buf;

    //! Size of m_buf in bytes
    size_t m_buf_size;

    //! the mode with which filebuf was opened.
    ios_base::openmode m_file_mode;

    //! \brief
    //!    Wheter m_buf points to a user provided buffer (true) or
    //!    is an internally allocated buffer (false)
    bool m_external_buf;

    //! If buffer is currently in read mode
    bool m_read_mode;

    //! If buffer is currently in write mode
    bool m_write_mode;

    //! \brief
    //! Default buffer size in bytes to apply for internally
    //! allocated buffers
    static const size_t S_DEF_BUF_SIZE = 2048;
};

void filebuf_base::applyWindows(streamsize p_offset) IPL_NOEXCEPT
{
    IPL_ASSERT( p_offset >= RESET_WINDOWS );

    // libstdc++ does check for in and out mode. But what is on sole
    // append? No buffering then?

    const bool IS_IN = (m_file_mode & ios_base::in) != 0;
    const bool IS_OUT = (m_file_mode & ios_base::out) != 0;

    // set new get area to 0 .. p_offset
    if( IS_IN && p_offset > 0 )
        this->setg(m_buf, m_buf, m_buf + p_offset);
    // in both other cases (RESET_WINDOWS, EMPTY_WINDOWS) we have
    // zero sized get area
    else
        // set all ptrs. equal thereby disabling buffering for
        // input
        this->setg(m_buf, m_buf, m_buf);

    // occupy the complete buffer for the put area (but only if at
    // least two bytes are there - one is hidden from base class and
    // is reserved for special overflow char semantics upon
    // overflow(int).
    if( IS_OUT && p_offset == EMPTY_WINDOWS && m_buf_size > 1)
        this->setp(m_buf, m_buf + m_buf_size - 1);
    // in both other cases (RESET_WINDOWS or offset >= 1 or buffer
    // size <= 1 we have no put area
    else
        this->setp(NULL, NULL);
}


streampos filebuf_base::seekoff(streamoff off,
    ios_base::seekdir way, ios_base::openmode which)
{
    streamoff real_off = off;

    // for the current position we need to take into account the
    // current position in the get window. But not for the put
    // window as in put case we flush the stream beforehand anyway
    //
    if( m_read_mode && way == ios_base::cur )
        real_off -= (egptr() - gptr());

    streampos ret;
    if( ! actuallySeek(real_off, way, ret ) )
    {
        // on success we can reset read/write mode and reset
        // buffer windows which effectively allows clients to
        // change from input to output or vice versa.
        m_read_mode = false;
        m_write_mode = false;
        applyWindows(RESET_WINDOWS);

        return ret;
    }

    return -1;
}



streampos filebuf_base::seekpos(streampos sp, ios_base::openmode which)
{
    streampos ret;

    if( ! actuallySeek(sp, ios_base::beg, ret) )
    {
        // on success we can reset read/write mode and reset
        // buffer windows which effectively allows clients to
        // change from input to output or vice versa.
        m_read_mode = false;
        m_write_mode = false;
        applyWindows(RESET_WINDOWS);

        return ret;
    }

    return -1;
}



} // end IPL_NAMESPACE

#endif
