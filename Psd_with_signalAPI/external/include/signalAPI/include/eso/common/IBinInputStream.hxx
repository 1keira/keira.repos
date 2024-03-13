/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_IBININPUTSTREAM_HXX
#define IPL_IBININPUTSTREAM_HXX

#include <ipl_config.h>
#include <common/Macros.hxx>
#include <common/ipl_namespace.hxx>
#include <common/IBinStreamBase.hxx>
#include <common/stdint.h>
#include <common/iplcommon_dso.h>

#include <stdlib.h>

namespace IPL_NAMESPACE
{

/**
 * \brief
 *    Binary input stream abstraction
 * \see
 *    IBinStreamBase

 *    Based on the description in IBinStreamBase this class realises
 *    the generic parts of a binary input stream.
 *
 *    It defines the abstract interface for implementations of binary
 *    input streams:
 *
 *    performRead()
 *    checkReadBufferConsistency() [optional]
 *
 *    And it defines the user visible interface to access the stream:
 *
 *    read()
 *
 *    The implementation offers an optional buffering scheme that
 *    allows to read ahead data from the underlying stream
 *    implementation, if possible. This makes sense if e.g. per-byte
 *    parsing of the input stream is performed by clients which would
 *    be pretty costly if for each byte a system call would have to be
 *    performed.
 *
 *    If you have a buffer of 1024 bytes defined at construction time
 *    and read a single byte via read() then the implementation
 *    attempts to read up to 1024 bytes into an internal buffer and
 *    then feeds the smaller data chunks to the client in turn.
**/
class IPLCOMMON_EXPORT IBinInputStream :
    virtual public IBinStreamBase
{
public: // functions
    /**
     * \brief
     *    Construct an input stream according to supplied parameters
     * \param[in]
     *    p_blocking Determines wheter read operations on this
     *    input stream are to be blocking or non-blocking. If
     *    blocking is \c true then when a system call is performed
     *    the call will block until at least some amount of data
     *    was actually read. Otherwise the call may return
     *    immediately without any data read.
     *
     *    This also influences how the handling of the optional
     *    internal buffer is done.
     * \param[in]
     *    p_buffersize If non-zero then a read buffer will be
     *    used. Read calls then try to read ahead as much data as
     *    fits in the buffer such that subsequent read calls might
     *    be able to be served from the local buffer.
     * \errorindicator
     *    via isValid()
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - OUT_OF_MEMORY
     **/
    IBinInputStream(const bool p_blocking, const size_t p_buffersize=0) IPL_NOEXCEPT;

    /**
     * \brief
     *    virtual destructor ensures that derived class destructor
     *    is always called.
     * \errors
     *    none
    **/
    virtual ~IBinInputStream() IPL_NOEXCEPT;
    
    IBinInputStream(const IBinInputStream &)=delete;
    IBinInputStream &operator = (const IBinInputStream &)=delete;

    /**
     * \brief
     *    Read in data from the input stream.

     *    Read in at max \c p_max_bytes bytes from the input
     *    stream into the given data buffer \c p_read_buffer. The
     *    actual number of read bytes are returned in \c
     *    p_bytes_read. If this is a non-blocking input stream
     *    then zero bytes may be read without an error being
     *    occured i.e. 0 is returned.
     *
     *    If \c p_max_bytes is zero of \c p_read_buffer is NULL
     *    then the function call will return 0 without performing
     *    any actions.
     *
     *    The following applies if an internal buffer has been
     *    requested at consturction time:
     *
     *    If there is any cached data available from the internal
     *    buffer:
     *
     *    Data from the internal buffer will be put into \c
     *    p_read_buffer. The underlying stream implementation will
     *    not be called to read more data.
     *
     *    If there is no data in the internal buffer:
     *
     *    If \c p_max_bytes is greater or equal than the size of
     *    the internal buffer then the underlying stream
     *    implementation will be requested to read directly into
     *    \c p_read_buffer instead of the internal buffer.
     *
     *    If \c p_max_bytes is less than the internal buffer then
     *    the underlying stream implementation will be requested
     *    to read into the internal buffer and whatever amount of
     *    data has been read into it will then be copied into \c
     *    p_read_buffer up to \c p_max_bytes.
     * \param[out]
     *    p_read_buffer client data buffer where to put the read
     *    data. Needs to be able to hold at least \c p_max_bytes
     *    bytes.
     * \param[in]
     *    p_max_bytes maximum number of bytes that may be read and
     *    put into \c p_read_buffer
     * \param[out]
     *    p_bytes_read the actual number of bytes that have been
     *    read and put into \c p_read_buffer will be put here if >
     *    0 is returned.
     * \return
     *    The function returns > 0 if \c p_read_buffer could be
     *    filled with data (i.e.  at least one byte of data), zero
     *    if no data could be read without blocking (in
     *    non-blocking mode) and < 0 in case of error.
     *
     *    Note that similar to the streams library the
     *    end-of-stream condition is signaled via an
     *    error/exception return. A StreamError with flag
     *    END_OF_STREAM is raised in that case.
     * \errors
     *    The generic stream classes don't raise errors
     *    themselves. Errors are indicated by negative return
     *    codes. If the InputStream implementation raises an error
     *    during calls to performRead then these errors will be
     *    forwarded to callers of read(). The state of the
     *    InputStream will remain stable in case of error as long
     *    the implementation of performRead is stable in this
     *    case.
     *
     *    By contract implementations are required to raise a
     *    StreamError in case of error return that may have
     *    attached more detailed error information.
     *
     *    For more detailed information see the documentation of
     *    performRead() of the stream implementation.
     * \errorindicator
     *    via return code.
     **/
    int_fast8_t read(
        void* const p_read_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_read) IPL_NOEXCEPT;

    /**
     * \brief
     *    Easier detection of end of stream condition

     *    In case read() returned < 0 and you want to easily check
     *    for the end-of-stream condition you can use this
     *    function.
     *
     *    It will check whether the current error indicate end of
     *    stream. If so then the error will be acknowledged and \c
     *    true is returned. Otherwise the error is kept active and
     *    \c false is returned.
     *
     * \warning
     *    Do not use this without having read() return < 0, as it
     *    may incorrectly indicate end of stream when
     *    there is still data to read
     **/
    bool endOfStream() const IPL_NOEXCEPT
    {
        if( ipl_error.isA( StreamError ) &&
            ipl_error.id() == END_OF_STREAM )
        {
            ipl_error.ack();
            return true;
        }

        return false;
    }

    /**
     * \brief
     *    returns whether this input stream performs buffering
     * \return
     *    true if the input stream is buffered, false otherwise.
     **/
    bool isInputBuffered() const IPL_NOEXCEPT
    {
        return m_read_buffer_size != 0;
    }

    /**
     * \brief
     *    returns the size of the buffer used for reading from the
     *    input stream
     **/
    size_t readBufferSize() const IPL_NOEXCEPT
    {
        return m_read_buffer_size;
    }

    /**
     * \brief
     *    return whether the local read buffer is currently empty
     *    or not
     * \return
     *    true if the local read buffer is empty, false otherwise.
     **/
    bool readBufferEmpty() const IPL_NOEXCEPT
    {
        return m_read_buffer_data_start ==
            m_read_buffer_data_end;
    }

    /**
     * \brief
     *    returns the number of bytes of user data currently
     *    present in the local buffer
     * \note
     *    It can happen that even though this function returns
     *    that data is present in the local buffer that a call to
     *    read() cannot provide that data, because the stream
     *    implementation needed to invalidate the local read
     *    buffer.
     **/
    size_t readBufferDataAmount() const IPL_NOEXCEPT
    {
        return m_read_buffer_data_end -
            m_read_buffer_data_start;
    }

    //! returns true if construction was successful, false otherwise
    virtual bool isValid() const IPL_NOEXCEPT
    { return !m_read_buffer_size || m_read_buffer != NULL; }

protected: // functions

    /**
     * \brief
     *    Optional hook for implementation to verify validity of
     *    internally buffered data

     *    On some stream implementations events that aren't
     *    visible to the generic stream code can cause internally
     *    cached data to become invalid. In such cases the
     *    implementation can override this virtual function to
     *    check the consistency of internally buffered data before
     *    a the logic of a read() operation is performed.
     *
     *    This is currently the case for streams that are seekable
     *    that allow combined read/write operaitons. The generic
     *    stream code doesn't have a notion of seeking a stream or
     *    switching read/write modes. But doing that invalidates
     *    buffered data. This is exactly a use case for this
     *    function.
     **/
    virtual bool checkReadBufferConsistency() IPL_NOEXCEPT
    { return false; };

    /**
     * \brief
     *    Actually read data from the stream

     *    This pure virtual method is called internally on behalf
     *    of the client in case the internal buffer is empty and
     *    the actual read operation has to be performed / or if
     *    there is no internal buffer.
     * \return
     *    true on error, false on success.
     * \errors
     *    A StreamError possibly attached with more detailed
     *    error(s)
     * \see
     *    read()
     **/
    virtual bool performRead(
        void* const p_read_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_read) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *    Reset the local read buffer indices to zero

     *    ... and thus remove any previously stored data from the
     *    buffer (logically) and set the buffer in a defined,
     *    clean state.
     *
     *    XXX
     *    This function is kept protected to allow implementations
     *    to invalidate any buffered data in case of external
     *    events invisible to the generic stream handling code
     *    (e.g. a seek or re-open operation has been performed on
     *    the stream).
     **/
    void resetReadBuffer() IPL_NOEXCEPT
    {
        m_read_buffer_data_start = m_read_buffer_data_end = 0;
    }

private: // data
    //! this gives the start byte for user data stored in the buffer
    size_t m_read_buffer_data_start;
    //! this gives the end byte for user data stored in the buffer
    size_t m_read_buffer_data_end;
    //! determines the buffer size (if zero then no buffering is performed).
    const size_t m_read_buffer_size;
    //! the memory area (on the heap) that is used for buffering.
    uint8_t* const m_read_buffer;
}; // end class

} // end namespace ipl

#endif /* IPL_IBININPUTSTREAM_HXX */
