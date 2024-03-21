#ifndef OSAL_GHSCONNECTIONBASE_HXX
#define OSAL_GHSCONNECTIONBASE_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Joerg Kupietz
*/

#include <ipl_config.h>

#include <common/CommonError.hxx>
#include <osal/Path.hxx>

#include <osal/posix/UnixSocketDefs.hxx>

#include <common/NonCopyable.hxx>

#include <common/IBinInOutStream.hxx>

namespace osal
{

class OSAL_EXPORT GHSConnectionBase :
    // copying a connection doesn't make sense
    public ipl::NonCopyable,
    // as a connection provides I/O we want to be an input and output
    // stream for binary data
    public ipl::IBinInOutStream
{
public: // types
    enum ConnState
    {
       //! The connection is not active currently
       INACTIVE,
       //! \brief
       //! The connection is configured, opened and ready for
       //! communication
       OPEN,
       //! \brief
       //! The connection was OPEN but was disconnected or some
       //! network event occured that broke the connection (e.g.
       //! disconnection on connection oriented connection)
       DEAD
    };

    enum ConnErrors
    {
        //! an invalid connection was encountered
        CONN_INVALID = 0,
        //! A connection option is unknown to the system
        UNKNOWN_OPTION,
        //! The value provided for a connection option was invalid
        INVALID_OPTION,
        //! Connection creation failed for some system spec. reason
        CREATE_FAILED,
        //! The cnnection endpoint used is already busy
        ADDRESS_IN_USE,
        //! The connection endpoint used is invalid
        ADDRESS_INVALID,
        //! Connection has been reset by peer
        CONNRESET,
        //! peer is not reachable
        NO_PEER,
        //! used network is down/unreachable
        NO_NETWORK,
        //! address resolve operation failed
        RESOLVE_FAILED,
        //! \brief
        //! actual data transfer failed (but probably worked
        //! before)
        COMMUNICATION_FAILED,
        //! connection to peer was normally closed
        CONNECTION_CLOSED,
        //! \brief
        //! a send/receive operation could not be completely
        //! finished as the amount of data was too high
        MSG_TOO_BIG
    };

    //! specific error type
    static ipl::ErrorType Error;

public: // functions
    virtual ~GHSConnectionBase();

    bool close();

    const ipl::string& getPeerName() const
    {
        return m_conn_resource;
    }

    ConnState getState() const
    {
       return m_conn_state;
    }

    size_t getNextMsgSize ();

    virtual bool isValid() const
    { return IBinInOutStream::isValid() && m_is_valid
        && this->getState() != DEAD; }

protected: // functions
    GHSConnectionBase(
        const size_t       p_input_buffer,
        const size_t       p_output_buffer,
        const ipl::string& p_conn_resource);

    void setState(const ConnState p_new_state)
    {
        m_conn_state = p_new_state;
    }

    bool closeGHSConnection (::Connection& conn, bool reraise_error = false);

    void checkRxTxError (::Error res, StreamErrors* stream_err = NULL);

    virtual bool performRead(
        void* const  p_read_buffer,
        const size_t p_max_bytes,
        size_t&      p_bytes_read);

    virtual bool performWrite(
        const void* const p_write_buffer,
        const size_t      p_max_bytes,
        size_t&           p_bytes_written);

private: // functions

protected: // members
    ipl::string   m_conn_resource;
    ::Connection  m_local_endpoint;
    ::Connection  m_peer_endpoint;
    //! whether construction succeeded
    bool          m_is_valid;

private: // members
    ConnState m_conn_state;
};

} // end namespace osal

#endif /* OSAL_GHSCONNECTIONBASE_HXX */
