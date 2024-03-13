#ifndef TRACING_PROTOCOL_ICONNECTIONFRONTENDLISTENER_HXX
#define TRACING_PROTOCOL_ICONNECTIONFRONTENDLISTENER_HXX

#include <common/types/string.hxx>

namespace tracing
{
namespace protocol
{

class Connection;
class ConnectionFrontendHandler;

class IConnectionFrontendListener
{
public:
    virtual ~IConnectionFrontendListener() {}

    virtual void registerConnection(ConnectionFrontendHandler * handler) = 0;
    virtual void unregisterConnection(ConnectionFrontendHandler * handler) = 0;
    virtual void deadConnection(ConnectionFrontendHandler * handler) = 0;
    virtual void destroyConnection(Connection * connection) = 0;
    virtual void log(const ipl::string & msg) = 0;
    virtual void log(int32_t level, const ipl::string & msg) = 0;
    /**
     * \brief get the time offset in milliseconds() since the beginning of the UNIX epoch.
     * \return The time in milliseconds(!) to keep the compatibility with older sytems
     **/
    virtual int64_t getTimeSyncOffset(const ipl::string & host) = 0;
    virtual bool getEarlyTimeSyncEnabled() = 0;
    virtual bool timeZoneExists(const ipl::string & name) = 0;
    virtual int16_t getFrontendId() const = 0;
};

} // end of namespace protocol
} // end of namespace tracing

#endif /* TRACING_PROTOCOL_ICONNECTIONFRONTENDLISTENER_HXX */

