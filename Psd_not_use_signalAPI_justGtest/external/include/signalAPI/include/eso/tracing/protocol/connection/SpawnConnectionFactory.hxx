#ifndef TRACING_PROTOCOL_SPAWNCONNECTIONFACTORY_HXX
#define TRACING_PROTOCOL_SPAWNCONNECTIONFACTORY_HXX

#include <ipl_config.h>

#include <osal/Mutex.hxx>

#include <tracing/protocol/protocol_dso.h>
#include <util/transport/factory/SpawnFactory.hxx>
#include <util/serializer/factory/Factory.hxx>

#include <tracing/protocol/connection/Connection.hxx>
#include <tracing/protocol/connection/ISpawnConnectionFactory.hxx>
#include <tracing/protocol/connection/ISpawnedConnectionListener.hxx>

namespace tracing
{
namespace protocol
{

class TRACING_PROTOCOL_EXPORT SpawnConnectionFactory :
    public ISpawnConnectionFactory
{
public:
    /**
     *    \brief
     *        Create a new factory for incoming connections.
     *    \param[in] : service
     *        Is the service the factory shall support (e.g. comm, tracing).
     *        Must be in some configuration file (e.g. framework.json).
     **/
    SpawnConnectionFactory(const ipl::string & service) IPL_NOEXCEPT;
    ~SpawnConnectionFactory() IPL_NOEXCEPT {}

    //! Enable spawning of new/incoming connections.
    void enableSpawning() IPL_NOEXCEPT;
    //! Disable spawning new connections.
    void disableSpawning() IPL_NOEXCEPT;
    //! Set a listener which gets notified when new connections are spawned.
    void setListener(ISpawnedConnectionListener * listener) IPL_NOEXCEPT;

    /**
     *    \brief
     *        Destroy a connection created by this factory.

     *        Connections can only be destroyed by their spawning factory as
     *        their destructor is protected. This is required now to ensure
     *        that associated serializer/deserializer pairs are returned to
     *        their factory when their transport is closed.
     *    \param[in]
     *        conn The connection which should be destroyed; and which must
     *        have been created by this factory.
     **/
    void destroyConnection(Connection * conn) IPL_NOEXCEPT;

    bool isValid() IPL_NOEXCEPT
    {
        return m_transport_factory.isValid() && m_serializer_factory.isValid();
    }

    //! Create an additional serializer suitable to be used by connections
    //! which are created by this factory.
    util::serializer::IStreamSerializer & createSerializer() IPL_NOEXCEPT;

    //! Destroy additionally created serializers.
    void returnSerializer(util::serializer::IStreamSerializer & serializer) IPL_NOEXCEPT;

    //! Sets the maximum length of peer process names expected.
    void setMaxProcNameSize(size_t max_size) const override;

protected:

    // TODO: I can't remember why this is an inner class, surely there must have
    // been a reason why SpawnConnectionFactory doesn't derive from ISpawnHandler
    // itself...
    class TRACING_PROTOCOL_EXPORT TransportListenerAdapter :
        public util::transport::SpawnFactory::ISpawnHandler
    {
    public:
        TransportListenerAdapter(osal::Mutex & mutex) IPL_NOEXCEPT;

        //! Sets a serializer factory (i.e. the one from the parent class).
        void setSerializerFactory(util::serializer::Factory * factory) IPL_NOEXCEPT;
        //! Set a listener which gets notified when new connections are spawned.
        void setListener(ISpawnedConnectionListener * listener) IPL_NOEXCEPT;
        //! Callback from SpawnFactory when a new transport has been spawned.
        void newTransport(const util::transport::ISpawnFactory &f,
            util::transport::IDisposableTransport & t);
        //! Callback from SpawnFactory when creating a new transport has failed.
        void creationError(
            const util::transport::ISpawnFactory &factory,
            util::transport::SpawnFactory::ISpawnHandler::RetrySettings &retry_settings);

    protected:
        //! Lock for protecting creation/destruction of serializers/deserializers.
        osal::Mutex & m_mutex;
        //! Factory for creating serializers/deserializers suitable
        //! for use with spawned transports.
        util::serializer::Factory * m_serializer_factory;
        //! Listener which gets notified when new connections are spawned.
        ISpawnedConnectionListener * m_connection_listener;
    };

    //! Lock for protecting creation/destruction of serializers/deserializers.
    osal::Mutex m_mutex;
    //! The instance of the internal ISpawnHandler implementation.
    TransportListenerAdapter m_adapter;
    //! The (abstract) factory which creates new incoming transports.
    util::transport::SpawnFactory m_transport_factory;
    //! Factory for creating serializers/deserializers suitable
    //! for use with spawned transports.
    util::serializer::Factory m_serializer_factory;
};


} // end of namespace protocol
} // end of namespace tracing

#endif /* TRACING_PROTOCOL_SPAWNCONNECTIONFACTORY_HXX */
