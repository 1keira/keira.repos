/*
    Copyright 2022 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_PROTOCOL_ISPAWNCONNECTIONFACTORY_HXX
#define TRACING_PROTOCOL_ISPAWNCONNECTIONFACTORY_HXX

#include <tracing/protocol/protocol_dso.h>

namespace tracing
{
namespace protocol
{

class Connection;
class ISpawnedConnectionListener;

class ISpawnConnectionFactory
{
public:
	virtual ~ISpawnConnectionFactory() {}

	virtual void setListener(ISpawnedConnectionListener * listener) = 0;
	virtual void enableSpawning() = 0;
	virtual void disableSpawning() = 0;
	virtual void destroyConnection(Connection * connection) = 0;
	virtual bool isValid() = 0;
    virtual void setMaxProcNameSize(size_t max_size) const = 0;
};

} // end of namespace protocol
} // end of namespace tracing

#endif /* TRACING_PROTOCOL_ISPAWNCONNECTIONFACTORY_HXX */

