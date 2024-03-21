#ifndef TRACING_PROTOCOL_ISPAWNEDCONNECTIONLISTENER_HXX
#define TRACING_PROTOCOL_ISPAWNEDCONNECTIONLISTENER_HXX

namespace tracing
{
namespace protocol
{

class Connection;

class ISpawnedConnectionListener
{
public:
	virtual ~ISpawnedConnectionListener() {}
	virtual void spawnedConnection(Connection * connection) = 0;
	virtual void creationError() = 0;
};

} // end of namespace protocol
} // end of namespace tracing

#endif /* TRACING_PROTOCOL_ISPAWNEDCONNECTIONLISTENER_HXX */

