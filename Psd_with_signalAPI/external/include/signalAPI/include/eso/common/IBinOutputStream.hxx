/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_IBINOUTPUTSTREAM_HXX
#define IPL_IBINOUTPUTSTREAM_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/iplcommon_dso.h>
#include <common/stdint.h>
#include <common/IBinStreamBase.hxx>

#include <stdlib.h>

namespace IPL_NAMESPACE
{

/**
 * \brief
 *     Binary output stream abstraction
 * \see
 *     IBinStreamBase

 *     Based on the description in IBinStreamBase this class realises
 *     the generic parts of a binary output stream.
 *
 *     It defines the abstract interface for implementations of binary
 *     output streams:
 *
 *     performWrite()
 *     performFlush() [optional]
 *     checkWriteBufferConsistency() [optional]
 *
 *     And it defines the user visible interface to access the stream:
 *
 *     write()
 *     flush()
 *
 *     The implementation offers an optional buffering scheme that
 *     allows to cache small portions of data written by the client to
 *     supply it too the stream implementation at a later time in one
 *     big chunk.
 *
 *     This makes sense if e.g. per-byte writes to the output stream
 *     are performed by clients which would be pretty costly if for
 *     each byte a system call would have to be performed for writing
 *     it to the stream.
 *
 *     If you have a buffer of 1024 bytes defined at construction time
 *     and write a single byte via write() then the implementation
 *     doesn't write at all to the stream implementation unless flush()
 *     is called or the internal buffer is completely filled.
**/
class IPLCOMMON_EXPORT IBinOutputStream :
    virtual public IBinStreamBase
{
public: // functions
    /**
     * \brief
     *     Construct an output stream according to parameters
     * \param[in]
     *     p_blocking Determines wheter read operations on this
     *     input stream are to be blocking or non-blocking. If
     *     blocking is \c true then when a system call is performed
     *     the call will block until at least some amount of data
     *     was actually written. Otherwise the call may return
     *     immediately without any data written.
     *
     *     This also influences how the handling of the optional
     *     internal buffer is done.
     * \param[in]
     *     p_buffersize If non-zero then a write buffer will be
     *     used. Write calls then don't immediatly write to the
     *     stream but will be put into the local buffer until
     *     flush() is called of the internal buffer is full.
     * \note
     *     Be aware that if you're using buffering then the first
     *     few writes might succeed until the first actual system
     *     call is made which can produce an error. The error is
     *     thus delayed in respect to the actions performed.
     * \errorindicator
     *     via isValid()
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - OUT_OF_MEMORY
     **/
    IBinOutputStream(
        const bool p_blocking,
        const size_t p_buffersize = 0) IPL_NOEXCEPT;

    /**
     * \brief
     *     virtual destructor ensures that derived class destructor
     *     is always called.
    **/
    virtual ~IBinOutputStream() IPL_NOEXCEPT;

    IBinOutputStream(const IBinOutputStream &)=delete;
    IBinOutputStream &operator = (const IBinOutputStream &)=delete;

    /**
     * \brief
     *     Write data to the output stream

     *     Write at max \c p_max_bytes from \c p_write_buffer to
     *     the output stream. The actual number of written bytes is
     *     returned in \c p_bytes_written.
     *
     *     if \c p_max_bytes is zero or \c p_write_buffer is NULL
     *     then no actions are performed and the function returns
     *     0.
     *
     *     The following applies if an internal buffer has been
     *     requested at construction time:
     *
     *     The local buffer is filled with data from \c
     *     p_write_buffer as far as possible. If there is not
     *     enough space in the local buffer to put all \c
     *     p_max_bytes into it then an attempt is made to write out
     *     the local buffer to the stream. If the complete local
     *     buffer could be written and the remaining data from \c
     *     p_write_buffer now fits into the local buffer then it
     *     will be copied there and the function returns.
     *
     *     If the remaining data still doesn't fit into the local
     *     buffer then an attempt is made to write data from \c
     *     p_write_buffer directly onto the stream. After that any
     *     data that still isn't written is put in the local buffer
     *     and the function returns.
     *
     *     Note that it can be the case that the function returns <
     *     0, because an error was indicated by the stream
     *     implementation but \c p_bytes_written still is non-zero,
     *     because the stream buffered data from \c p_write_buffer
     *     in the local buffer.
     * \param[in]
     *     p_write_buffer The buffer that contains the data that
     *     should be written to the output stream. It needs to
     *     contain at least \c p_max_bytes valid bytes of data.
     * \param[in]
     *     p_max_bytes The maximum number of bytes in
     *     p_write_buffer that can be used for writing to the
     *     output stream.
     * \param[out]
     *     p_bytes_written The actual number of bytes from \c
     *     p_write_buffer that could be written to the output
     *     stream. Only valid if > 0 is returned.
     * \return
     *     The function returns > 0 if at least one byte could be
     *     written to the output stream, zero if nothing could be
     *     written (non-blocking) or < 0 on error.
     * \errors
     *     The generic stream classes don't raise errors
     *     themselves. Errors are indicated by negative return
     *     codes. If the InputStream implementation raises an error
     *     during calls to performWrite then these errors will be
     *     forwarded to callers of write(). The state of the
     *     OutputStream will remain stable in case of error as long
     *     the implementation of performWrite() is stable in this
     *     case.
     *
     *     By contract implementations are required to raise a
     *     StreamError in case of error return that may have
     *     attached more detailed error information.
     * \errorindicator
     *     via return code
     **/
    int_fast8_t write(
        const void* const p_write_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_written) IPL_NOEXCEPT;

    /**
     *  \brief
     *      Flush the output stream

     *      This function performs a flush of the output stream.
     *      This writes any data left in a possibly setup local
     *      output buffer to the actual output stream. If this is a
     *      blocking stream then the generic stream code attempts to
     *      write out all buffered data. Otherwise only any data
     *      that can immediatly be written from the local buffer
     *      will be flushed (otherwise a busy loop could occur).
     *
     *      Then and if \c system_flush is set to \c true a call to
     *      the implementation of performFlush is performed. This is
     *      supposed to block (independently of the
     *      blocking/non-blocking setting of the stream) until all
     *      previously written data has really been processed by the
     *      respective target device. The use of this can
     *      significantly slow down your I/O operations. Thus it
     *      should only be used if you need to make sure for
     *      imporant reasons that output operations are really
     *      performed and successfully performed.
     *
     *      If performFlush is called and the stream doesn't support
     *      flushing then by contract the implementation is required
     *      not to raise an error but indicate success anyway.
     *  \param[in]
     *      system_flush If set to \c true then not only the buffer
     *      will be flushed but also the operating system will be
     *      asked, if possible, to write out any outstanding data to
     *      the underlying medium.
     *  \return
     *      true on error, false on success
     *  \errors
     *      By contract implementations are required to raise a
     *      StreamError in case of error return that may have
     *      attached more detailed error information.
     *  \errorindicator
     *      via return code
     **/
    bool flush(const bool system_flush = false) IPL_NOEXCEPT;

    /**
     * \brief
     *     returns wheter this output stream performs buffering
     * \return
     *     true if the output stream is buffered, false otherwise.
     **/
    bool isOutputBuffered() const IPL_NOEXCEPT
    {
        return m_write_buffer_size != 0;
    }

    /**
     * \brief
     *     returns the size of the buffer used for writing data to
     *     the output stream
     **/
    size_t writeBufferSize() const IPL_NOEXCEPT
    {
        return m_write_buffer_size;
    }

    /**
     * \brief
     *     return wheter the local write buffer is currently empty
     *     or not
     * \return
     *     true if the local write buffer is empty, false otherwise
     **/
    bool writeBufferEmpty() const IPL_NOEXCEPT
    {
        return m_write_buffer_data_start == m_write_buffer_data_end;
    }

    /**
     * \brief
     *     returns the number of bytes of user data currently
     *     cached in the local buffer
     **/
    size_t writeBufferDataAmount() const IPL_NOEXCEPT
    {
        return m_write_buffer_data_end - m_write_buffer_data_start;
    }

    //! returns true if construction was successful, false otherwise
    virtual bool isValid() const IPL_NOEXCEPT
    { return !m_write_buffer_size || m_write_buffer != NULL; }

protected: // functions
    /**
     * \brief
     *     Optional hook for implementation to verify validity of
     *     internally buffered data

     *     On some stream implementations events that aren't
     *     visible to the generic stream code can cause internally
     *     cached data to become invalid. In such cases the
     *     implementation can override this virtual function to
     *     check the consistency of internally buffered data before
     *     a the logic of a read() operation is performed.
     *
     *     This is currently the case for streams that are seekable
     *     that allow combined read/write operaitons. The generic
     *     stream code doesn't have a notion of seeking a stream or
     *     switching read/write modes. But doing that invalidates
     *     buffered data. This is exactly a use case for this
     *     function.
     **/
    virtual bool checkWriteBufferConsistency() IPL_NOEXCEPT
    { return false; };

    /**
     * \brief
     *     Actually write data to the stream

     *     This pure virtual method is called internally on behalf
     *     of a call to write() in case the internal buffer is full
     *     and an actual write operation has to be performed. This
     *     is also done if the flush() method is called.
     * \return
     *     true on error, false on success
     * \see
     *     write
     **/
    virtual bool performWrite(
        const void* const p_write_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_written) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Actually perform a flush operation on the stream

     *     This pure virtual method is called internally to cause
     *     any operating system buffers to be flushed. Might not be
     *     possible/implemented by the actual stream.
     * \return
     *     true on error, false on success
     * \note
     *     For implementors of performFlush: This call should only
     *     raise an error for real errors. If you just don't
     *     support or need a flush operation then simply do
     *     nothing.
     * \errors
     *     implementation defined.
     * \errorindicator
     *     via return code
     **/
    virtual bool performFlush() IPL_NOEXCEPT
    {
        // default implementation is to do nothing
        return false;
    }

    /**
     * \brief
     *     Reset the local write buffer indices to zero

     *     ... and thus remove any previously stored data from the
     *     buffer (logically) and set the buffer in a defined,
     *     clean state.
     *
     *     This function is kept protected to allow derived classes
     *     to invalidate the buffer. This should be done with
     *     caution, though as the data might get lost forever (on a
     *     non-seekable stream).
     **/
    void resetWriteBuffer() IPL_NOEXCEPT
    {
        m_write_buffer_data_start = m_write_buffer_data_end = 0;
    }

private: // members
    // start and end index of the buffer.
    //! this gives the start byte for user data stored in the buffer
    size_t m_write_buffer_data_start;
    //! this gives the end byte for user data stored in the buffer
    size_t m_write_buffer_data_end;
    //! \brief
    //! determines the allocated size of the m_write_buffer in bytes
    //! (if zero then no buffering is performed)
    const size_t m_write_buffer_size;
    //! a pointer to the write buffer memory area on the heap
    uint8_t* const m_write_buffer;
}; // end class

} // end namespace

#endif /* IPL_IBINOUTPUTSTREAM_HXX */
