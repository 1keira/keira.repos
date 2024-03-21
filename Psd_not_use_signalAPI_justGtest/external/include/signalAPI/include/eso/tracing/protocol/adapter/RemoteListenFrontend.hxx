/*
    Copyright 2022 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_PROTOCOL_REMOTELISTENFRONTEND_HXX
#define TRACING_PROTOCOL_REMOTELISTENFRONTEND_HXX

#include <tracing/protocol/protocol_dso.h>
#include <common/types/string.hxx>
#include <common/types/vector.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <osal/Timer.hxx>
#include <osal/RWLock.hxx>
#include <tracing/frontend/IFrontendListener.hxx>
#include <tracing/protocol/connection/ISpawnedConnectionListener.hxx>
#include <tracing/protocol/adapter/IConnectionFrontendListener.hxx>
#include <tracing/protocol/adapter/Authenticator.hxx>
#include <tracing/entity/EntityURI.hxx>
#include <tracing/protocol/timesyncer/TimeSyncer.hxx>
#include <tracing/util/TraceMe.hxx>

namespace tracing
{

class EntityURI;
class Frontend;

namespace protocol
{

class Connection;
class ConnectionFrontendHandler;
class ISpawnConnectionFactory;

class TRACING_PROTOCOL_EXPORT RemoteListenFrontend :
        public IConnectionFrontendListener,
        public IFrontendListener,
        public ISpawnedConnectionListener,
        public ITimeSyncCallback
{
public:
    RemoteListenFrontend(ISpawnConnectionFactory & factory, Frontend & frontend, bool early_timesync = false);
    ~RemoteListenFrontend();

    void start();
    void stop();

    /*************** Start of ISpawnedConnectionListener interface ****************/

    void spawnedConnection(Connection * connection) override;
    void creationError() override;

    /*************** End of ISpawnedConnectionListener interface ******************/

    /*************** Start of IConnectionFrontendListener interface ***************/

    void registerConnection(ConnectionFrontendHandler * handler) override;
    void unregisterConnection(ConnectionFrontendHandler * handler) override;
    void deadConnection(ConnectionFrontendHandler * handler) override;
    void destroyConnection(Connection * connection) override;
    void log(const ipl::string & msg) override;
    void log(int32_t level, const ipl::string & msg) override;
    /**
     * \brief get the time offset in milliseconds() since the beginning of the UNIX epoch.
     * \return The time in milliseconds(!) to keep the compatibility with older sytems
     **/
    int64_t getTimeSyncOffset(const ipl::string & host) override;
    bool getEarlyTimeSyncEnabled() override
    {
        return m_early_timesync_enabled;
    }
    bool timeZoneExists(const ipl::string & name) override;
    int16_t getFrontendId() const override
    {
        return m_fid;
    }

    /*************** End of IConnectionFrontendListener interface *****************/

    /*************** Start of IFrontendListener interface *************************/

	void init(int16_t fid, Frontend * frontend) override;
    void shutdown() override;
    void requestFilterLevel(const EntityURI & uri, int16_t level) override;
    void executeCallback(int32_t cbid, void * data, size_t len) override;
    void requestQuit() override;

    /*************** End of IFrontendListener interface ***************************/

    /*************** Start of ITimeSyncCallback interface *************************/

    void updateDelta(int32_t callback_id, int64_t delta) override;

    /*************** End of ITimeSyncCallback interface ***************************/

    bool waitForQuit();

    int32_t getLogChannelId() { return m_cid; }
    int32_t getLogThreadId() { return m_tid; }

protected:
    class TimeSyncTimer : public osal::Timer
    {
    public:
        TimeSyncTimer(RemoteListenFrontend * parent, int32_t id);
        RemoteListenFrontend * m_parent;
        int32_t m_id;
        static void timerCallbackFunc(osal::Timer * const which);
    };

    friend class TimeSyncTimer;
protected:
    ISpawnConnectionFactory & m_factory;
    Frontend & m_frontend;
    ipl::vector<ConnectionFrontendHandler *> m_handlers;
    ipl::vector<ConnectionFrontendHandler *> m_dead_handlers;
    osal::Mutex m_mutex;
    osal::Mutex m_entity_mutex;
    osal::Mutex m_tzname_mutex;
    osal::Condition m_cond;
    osal::RWLock m_timezone_lock;
    EntityURI m_uri;
    int32_t m_cid;
    int32_t m_tid;
    int16_t m_channel_level;
    int16_t m_thread_level;
    bool m_do_quit;
    bool m_early_timesync_enabled;

    Authenticator m_authenticator;

    ipl::map<int32_t, ConnectionFrontendHandler *> m_timezones;
    ipl::map<int32_t, TimeSyncTimer *> m_timesync_timers;
    ipl::map<ipl::string, int64_t> m_timezone_offsets;
    ipl::map<ipl::string, size_t> m_peer_names_count;
    //! timestamps of client connect
    ipl::map<ipl::string, osal::TimeT> m_peer_connect_ts;
    ipl::set<ipl::string> m_timezone_names;
    //! TraceMe client channel
    IPL_TRACEME_DECLARE_SCOPE(RemoteListenFrontend);

    bool isTimeSyncMaster(const ConnectionFrontendHandler * handler, int32_t & id) const;
    ConnectionFrontendHandler * chooseTimeSyncMaster(int32_t id, const ipl::string & node_name);
    void addPeerName(const ipl::string & name);
    void removePeerName(const ipl::string & name);
    osal::TimeT getConnectDuration(const ipl::string & name);
};

} // end of namespace protocol
} // end of namespace tracing

#endif /* TRACING_PROTOCOL_REMOTELISTENFRONTEND_HXX */

