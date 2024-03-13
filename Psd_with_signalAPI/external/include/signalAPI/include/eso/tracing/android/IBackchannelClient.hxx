/*
    Copyright 2023 e.solutions GmbH
    All rights reserved
 */
#ifndef TRACING_BACKCHANNELCLIENT_HXX_
#define TRACING_BACKCHANNELCLIENT_HXX_

#include <memory>
#include <string>
#include <sstream>
#include <vector>

namespace tracing {

class AidlEntityParams;

/**
 * \brief
 *    Interface which is used by tracecore client for communication towards the Android
 *    AOSP Backchannel.
 *
 *    The Android AOSP backchannel client needs to implement this interface offering
 *    callbacks to the client sided tracecore.
 *    Interface is defined and used but not built in scope of the esofw tracecore.
 *    It must be provided as shared aosp lib.
**/
class IBackchannelClientListener
{
public:
    virtual ~IBackchannelClientListener() = default;

    /**
     * \brief
     *     Will be called by client tracecore to forward a
     *     createEntity indication via AIDL towards the tracecore server.
     *
     * \param[in] entity      The entity parameters.
     **/
    virtual void createEntity(const AidlEntityParams& entity) noexcept = 0;

    /**
     * \brief
     *     Will be called by client tracecore to forward a
     *     createEntityBulk indication via AIDL towards the tracecore server.
     *
     * \param[in] entity      The array of entity parameters.
     **/
    virtual void createEntityBulk(const std::vector<AidlEntityParams>& entities) noexcept = 0;

    /**
     * \brief
     *     Will be called by client tracecore to forward a
     *     changeLevel acknowledgment via AIDL towards the tracecore server.
     *
     * \param[in] level       The entity level.
     * \param[in] type        The entity type.
     * \param[in] id          The client's entity id.
     **/
    virtual void changeFilterLevel(int16_t level,
                                   int16_t type,
                                   int16_t id) noexcept = 0;

    /**
     * \brief Will be called upon shutdown of client tracecore.
     **/
    virtual void shutdown() noexcept = 0;
};

/**
 * \brief
 *    Interface which is used by Android AOSP backchannel client for communication
 *    towards the tracecore client.
 *
 *    Tracecore client side needs to implement this interface offering callbacks to the
 *    Android AOSP backchannel client.
 **/
class IBackchannelClient
{
public:
    virtual ~IBackchannelClient() = default;

    /**
     * \brief
     *     Will be called by Android AOSP backchannel client to indicate its
     *     availability towards the tracecore client.
     **/
    virtual void initBackchannel(std::shared_ptr<IBackchannelClientListener> listener) noexcept = 0;

    /**
     * \brief
     *     Will be called by Android AOSP backchannel client to indicate its
     *     termination towards the tracecore client.
     **/
    virtual void exitBackchannel() noexcept = 0;

    /**
     * \brief
     *     Will be called by Android AOSP backchannel client to inform
     *     tracecore client about a requested entity level change which has to
     *     performed on client tracecore side.
     *
     * \param[in] level  The new entity level.
     * \param[in] type   The entity type.
     * \param[in] id     The entity id on client side.
     * \param[out] error An error info in case of failure.
     * \return true if operation was successful, otherwise false.
     *
     **/
    virtual bool requestFilterLevel(int16_t level,
                                    int16_t type,
                                    int16_t id,
                                    std::ostream& error) noexcept = 0;
    /**
     * \brief
     *    Trigger via AIDL from server to execute callback on client side.
     *
     * \param[in]  cbid        The callback ID.
     * \param[in]  data        The optional user data of the callback.
     * \return true if the callback id exists on client side and the callback was
     *              scheduled for execution.
     **/
    virtual bool executeCallback(int16_t cb_id,
                                 const std::vector<uint8_t> & data) noexcept = 0;
};

} /*  namespace tracing */

#endif /* TRACING_BACKCHANNELCLIENT_HXX_ */

