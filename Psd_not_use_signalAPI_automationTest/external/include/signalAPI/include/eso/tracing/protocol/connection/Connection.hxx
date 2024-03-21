/*
    Copyright 2021 e.solutions GmbH

    All rights reserved
*/

#ifndef TRACING_PROTOCOL_CONNECTION_HXX
#define TRACING_PROTOCOL_CONNECTION_HXX

#include <tracing/protocol/protocol_dso.h>
#include <util/transport/PeerInfoPtrForward.hxx>

namespace util
{

namespace transport
{
class IDisposableTransport;
}

namespace serializer
{
class IStreamSerializer;
class IStreamDeserializer;
}

}

namespace tracing
{
namespace protocol
{

class TRACING_PROTOCOL_EXPORT Connection
{
public:
    //! Get the transport used for this connection.
    util::transport::IDisposableTransport & getTransport()
    {
        return m_transport;
    }

    //! Get the serializer used for this connection.
    util::serializer::IStreamSerializer & getSerializer()
    {
        return m_serializer;
    }

    //! Get the deserializer used for this connection.
    util::serializer::IStreamDeserializer & getDeserializer()
    {
        return m_deserializer;
    }

    /**
        \brief
            Opens the connection.
        \return
            false if the underlying transport implementation encountered an error
            when opening the transport, true otherwise.
     **/
    bool open();

    /**
        \brief
            Closes the connection.
        \return
            false if the underlying transport implementation encountered an error
            when closing the transport, true otherwise.
     **/
    bool close();

    /**
        \brief
            Verify the peer identity.
        \param peer_info
            Contains some kind of credentials to use for verification. These can
            only be checked if they are suitable for the underlying transport type.
            An empty peer_info is valid and will always verify successful.
            A transport implementation that can not provide peer info will *only*
            verify successful with an empty peer_info.
        \return
            false if verification fails or the type of peer credentials are not
            supported by the actual transport implementation.
     **/
    bool verifyPeerCredentials(const util::transport::PeerInfoPtr & peer_info) const;
    std::string getPeerInfo() const;

    void setPacketSizeLimit(size_t size);
protected:
    friend class ConnectionFactory;
    friend class SpawnConnectionFactory;

    // Protect ctor/dtor so a connection can only be created
    // and deleted by its (Spawn)ConnectionFactory.
    Connection(util::transport::IDisposableTransport & transport,
            util::serializer::IStreamSerializer & serializer,
            util::serializer::IStreamDeserializer & deserializer);

    ~Connection();

    // Should also be called by Factories only
    static void setMaxProcNameSize(size_t max_size)
    {
        s_max_size = max_size;
    }

    util::transport::IDisposableTransport & m_transport;
    util::serializer::IStreamSerializer & m_serializer;
    util::serializer::IStreamDeserializer & m_deserializer;

    static size_t s_max_size;
};

} // end of namespace protocol
} // end of namespace tracing

#endif /* TRACING_PROTOCOL_CONNECTION_HXX */

