/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_PIPE_HXX
#define OSAL_PIPE_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>
#include <osal/osal_dso.h>
#include <osal/osal.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/PipeDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/PipeDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal
{

/**
 * \brief
 *     Creates an anonymous pipe for unidirectional communication with
 *     other processes

 *     A pipe is a unidirectional communications channel. It consists
 *     of two FileHandles, one being the read end of the channel and
 *     one being the write end.
 *
 *    These handles can be inherited as a transparent replacement for
 *    stdout, stderr or stdin to child processes via
 *    osal::ProcessTNG::setStdout(osal::Pipe&),
 *    osal::ProcessTNG::setStderr(osal::Pipe&) and
 *    osal::ProcessTNG::setStdin(osal::Pipe&).
 *
 *    If required, an end of the Pipe can be closed.  For example, if
 *    you inherit the write end of the Pipe as the stdout of a child
 *    process then you will want to close the write end in the parent
 *    after it has been inherited to the child process. Otherwise
 *    reading from the read end in the parent will never return with
 *    an end of file condition. That is, because the pipe will never
 *    end as long as a process with an open handle to the write side
 *    exists in the system.
 *
 *    It is also possible to inherit the same read or write end of a
 *    Pipe to multiple child processes. The atomicWriteSize() function
 *    returns the maximum number of bytes that can be written
 *    atomically to the write end of a pipe, without causing the write
 *    content being interleaved with writes of other clients of the
 *    same pipe's write end.
 *
 *    To actually get a means to read or write from a Pipe end you can
 *    pass the Pipe object to a StreamBinFileR, StreamBinFileW or
 *    StreamFmtFileR, StreamFmtFileW accordingly. The constructors of
 *    those classes taking a Pipe object will take over ownership of
 *    the read or write end of the Pipe respectively. Handles that are
 *    taken over will be invalidated in the Pipe object.
 *
 *     Passing the Pipe to osal::ProcessTNG does not count as
 *     consumption as the child will get its own copy of the pipe end.
 * \note
 *     This mechanism is currently not supported on WinCE due to
 *     missing APIs on that OS. On WinCE Pipe objects will always
 *     be invalid, the constructor raising an error. OSAL may implement
 *     a suitable emulation layer on WinCE at a later time to fill this
 *     gap.
 **/
class OSAL_EXPORT Pipe :
    ipl::NonCopyable
{
public: // functions
    /**
     * \brief
     *     Create a new anonymous Pipe

     *     This is the only constructor and creates a new pipe with
     *     its read and write ends.
     * \errorindicator
     *    via isValid()
     * \errors
     *     osal::SysError with IDs:
     *
     *     - SYSTEM_RESSOURCES_EXHAUSTED if the maximum number of
     *     file descriptors in the process or system has been
     *     reached
     *     - OUT_OF_MEMORY if the buffer required for the pipe
     *     could not be allocated by the system
     *     - NOT_IMPLEMENTED can occur on QNX if the pipe manager
     *     is not running; will always occur on WinCE due to
     *     missing OS support
     *     - UNKNOWN_ERROR on severe or unexpected errors
     **/
    explicit Pipe();

    /**
     * \brief
     *     Close unused pipe ends, if needed

     *     If any end of the pipe wasn't consumed by another class
     *     then that end will be closed by the destructor.
     *
     *     On close errors IPL_WARN is called and the handles are
     *     invalidated nonetheless.
     **/
    ~Pipe();

    //! \brief
    //! returns whether construction succeeded and both pipe ends
    //! are valid
    bool isValid() const
    { return readEndValid() && writeEndValid(); }

    //! returns whether a yet unused read end is there
    bool readEndValid() const
    {
        return m_read_end != OSAL_INVALID_FILE_HANDLE;
    }

    //! returns whether a yet unused write end is there
    bool writeEndValid() const
    {
        return m_write_end != OSAL_INVALID_FILE_HANDLE;
    }

    /**
     * \brief
     *     Closes the write end of the pipe, if still valid
     * \note
     *     If the write end is currently invalid then \c false is
     *     returned and nothing is done.
     * \return
     *     \c false on success, \c true on error
     **/
    bool closeWriteEnd();

    /**
     * \brief
     *     Closes the read end of the pipe, if still valid
     * \note
     *     If the read end is currently invalid then \c false is
     *     returned and nothing is done.
     * \return
     *     \c false on success, \c true on error
     **/
    bool closeReadEnd();

    /**
     * \brief
     *     Closes both ends of the pipe
     **/
    bool close()
    {
        bool ret = closeReadEnd();
        ret |= closeWriteEnd();

        return ret;
    }

    /**
     * \brief
     *     Get the number of bytes that can be atomically written
     *     to a pipe

     *     This value is of interest if you intend to inherit the
     *     write end of a pipe to multiple child processes at the
     *     same time.
     *
     *     In that situation the question arises what happens if
     *     multiple processes write to the pipe simultaneously. If
     *     the data written would be interleaved arbitrarily than
     *     the pipe reader couldn't make any sense of the data
     *     read. That is what this size is for.
     *
     *     The system guarantees that a write to the pipe that is
     *     less or equal to the atomicWriteSize() will always
     *     appear as a piece on the read end of the pipe even if
     *     parallel writes occur on the pipe.
     *
     *     This size typically in in the order of four kilobytes.
     *     If you need precise information over this you need to
     *     query this function.
     **/
    inline static size_t atomicWriteSize();

protected:
    friend class BinFileBase;
    friend class ProcessTNG;

    /**
     *  \brief
     *      invalidates the read end pipe

     *    Allows another class that uses this object to actually
     *    use the pipe to invalidate the local handle such that
     *    it's marked as "used" and ownership is moved to the
     *    caller.
     **/
    void invalidateReadEnd()
    { m_read_end = OSAL_INVALID_FILE_HANDLE; }

    /**
     * \brief
     *     invalidates the write end pipe
     * \see
     *     invalidateReadEnd()
     **/
    void invalidateWriteEnd()
    { m_write_end = OSAL_INVALID_FILE_HANDLE; }

    /**
     * \brief
     *     Retrieve the handle of the read end of the pipe
     **/
    FileHandle getReadEnd() const
    { return m_read_end; }

    /**
     * \brief
     *     Retrieve the handle of the write end of the pipe
     **/
    FileHandle getWriteEnd() const
    { return m_write_end; }
private:
    osal::FileHandle m_read_end;
    osal::FileHandle m_write_end;
}; // end class

} // end osal

#if defined IPL_OS_POSIX
#    include "posix/Pipe.inl"
#elif defined IPL_OS_WINPC || defined IPL_OS_INTEGRITY
#    include "win32/Pipe.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif // OSAL_PIPE_HXX
