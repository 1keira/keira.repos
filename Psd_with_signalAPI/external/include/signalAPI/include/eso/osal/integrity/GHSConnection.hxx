#ifndef OSAL_GHSCONNECTION_HXX
#define OSAL_GHSCONNECTION_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Joerg Kupietz
*/

#include <ipl_config.h>
#include <osal/integrity/GHSConnectionBase.hxx>

namespace osal
{

class OSAL_EXPORT GHSConnection :
    public GHSConnectionBase
{
    friend class GHSServerConnection;

public: // types
    class Description;

public: // functions

    GHSConnection(
            const uint_fast32_t p_input_buffer,
            const uint_fast32_t p_output_buffer,
            const ipl::string&  p_conn_resource);

    GHSConnection(
            const uint_fast32_t p_input_buffer,
            const uint_fast32_t p_output_buffer,
            const Description&  p_desc);

    virtual ~GHSConnection();

    bool connect();
};

class GHSConnection::Description
{
public: // functions

    //! \brief Creates an invalid description!
    Description():
        valid          (false),
        local_endpoint (NULLConnection),
        peer_endpoint  (NULLConnection) {}

    //! \brief
    //!     This allows for if( desc ) queries to check for validity
    //! \see
    //!     isValid()
    operator bool() const
    { return isValid(); }

    //! \brief
    //!     Returns true in case the description refers to a valid, unused socket
    bool isValid() const
    { return valid; }

    //! \brief
    //!     Returns the name of the GHS connection
    const ipl::string& getLocalAddress() const
    { return local_address; }

    //! \brief
    //!     If the object is destroyed while still being valid then the
    //!     associated OS-level socket will be closed.
    ~Description();

protected: // functions

    Description(
       const ::Connection& local_endpoint,
       const ::Connection& peer_endpoint,
       const ipl::string&  local_address) :
        valid(true),
        local_endpoint(local_endpoint), peer_endpoint(peer_endpoint),
        local_address(local_address) {}

public:
    Description(const Description &other) :
        valid          (other.valid),
        local_endpoint (other.local_endpoint),
        peer_endpoint  (other.peer_endpoint),
        local_address  (other.local_address)
    {
        other.valid = false;
    }

protected: // members
    //! true if the object is still valid, false otherwise
    mutable bool valid;
    //! the OS handle associated with the connection
    const ::Connection local_endpoint;
    //! the addresses associated with local and peer node
    const ::Connection peer_endpoint;
    //! the listening address this connection was accepted at
    const ipl::string local_address;

    friend class GHSConnection;
    friend class GHSServerConnection;
};

} // end namespace osal

#endif /* OSAL_GHSCONNECTION_HXX */

