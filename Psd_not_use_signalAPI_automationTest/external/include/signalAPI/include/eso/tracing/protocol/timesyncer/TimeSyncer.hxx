#ifndef TRACING_PROTOCOL_TIMESYNCER_HXX
#define TRACING_PROTOCOL_TIMESYNCER_HXX

#include <common/types/vector.hxx>
#include <osal/osal.hxx>
#include <osal/Mutex.hxx>

namespace tracing
{
namespace protocol
{

class ProtocolHandler;
class TimeSyncMessage;

class ITimeSyncCallback
{
public:
    virtual ~ITimeSyncCallback() {}
    virtual void updateDelta(int32_t callback_id, int64_t delta) = 0;
};

class TimeSyncer
{
public:
    TimeSyncer(ProtocolHandler & handler, ITimeSyncCallback * callback = NULL) :
        m_start_time(0),
        m_serial(0),
        m_handler(handler),
        m_callback_id(-1),
        m_callback(callback),
        m_sync_valid(false),
        m_sync_in_progress(false)
    {
    }

    void setCallbackHandler(int32_t id, ITimeSyncCallback * callback)
    {
        m_callback_id = id;
        m_callback = callback;
    }

    void start();
    void handleIncomingMessage(TimeSyncMessage * msg);
    bool isSyncValid() const
    {
        return m_sync_valid;
    }

protected:
    osal::TimeT m_start_time;
    int8_t m_serial;
    ProtocolHandler & m_handler;

    int32_t m_callback_id;
    ITimeSyncCallback * m_callback;

    bool m_sync_valid;
    bool m_sync_in_progress;
    osal::Mutex m_mutex;
    ipl::vector<osal::TimeT> m_deltas;
    ipl::vector<osal::TimeT> m_latencies;

    int64_t analyseSamples();
};

} // end of namespace protocol
} // end of namespace tracing


#endif /* TRACING_PROTOCOL_TIMESYNCER_HXX */

