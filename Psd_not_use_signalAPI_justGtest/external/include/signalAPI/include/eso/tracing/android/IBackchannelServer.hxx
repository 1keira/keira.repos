/*
    Copyright 2023 e.solutions GmbH
    All rights reserved
 */
#ifndef TRACING_BACKCHANNELSERVER_HXX_
#define TRACING_BACKCHANNELSERVER_HXX_

#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace tracing {

/**
 * \brief
 *    Tracecore sided representation of the Android AIDL parcelable 'EntityParams'.
**/
class AidlEntityParams
{
public:
    /**
     * \brief Constructor.
     *
     * \param[in] entity_name The entity name.
     * \param[in] level       The entity level.
     * \param[in] type        The entity type.
     * \param[in] id          The entity id.
     * \param[in] parent_type The parent entity type.
     * \param[in] parent_id   The parent entity id, a negative value indicates a
     *                        non-existing parent.
     **/
    AidlEntityParams(const std::string &name,
                    int16_t level, int16_t type, int16_t id,
                    int16_t parent_type, int16_t parent_id)
        : m_name(name), m_level(level), m_type(type), m_id(id)
        , m_parent_type(parent_type), m_parent_id(parent_id)
    {}

    AidlEntityParams()
        : m_name(""), m_level(-1), m_type(-1), m_id(-1)
        , m_parent_type(-1), m_parent_id(-1)
    {}

    std::string getName() const {return m_name;}
    int16_t getLevel() const {return m_level;}
    int16_t getType() const {return m_type;}
    int16_t getId() const {return m_id;}
    int16_t getParentType() const {return m_parent_type;}
    int16_t getParentId() const {return m_parent_id;}
    void setLevel(int16_t level) {m_level=level;}

    inline std::string toString() const
    {
        std::ostringstream os;
        os << "AidlEntity[" << "id=" << m_id << " type=" << m_type
            << " level=" << m_level << " name=<" << m_name
            << "> parent: type=" << m_parent_type << " id=" << m_parent_id
            << "]";
        return os.str();
    }
private:
    std::string m_name;
    int16_t m_level;
    int16_t m_type;
    int16_t m_id;
    int16_t m_parent_type;
    int16_t m_parent_id;
};

/**
 * \brief
 *    Interface which is used by tracecore for communication towards the Android
 *    Backchannel server.
 *
 *    The Android AOSP backchannel server needs to implement this interface offering
 *    callbacks to the server sided tracecore.
 *    Interface is defined and used but not built in scope of the esofw tracecore.
 *    It must be provided as shared aosp lib.
**/
class IBackchannelServerListener
{
public:
    virtual ~IBackchannelServerListener() = default;

    /**
     * \brief
     *    Will be called by tracecore server to inform Android AOSP backchannel server
     *    about an entity level change.
     *
     * The Backchannel service needs to forward accordingly if client with matching
     * name is registered.
     *
     * \param[in] level       The new entity level.
     * \param[in] type        The entity type.
     * \param[in] id          The client's entity id.
     * \param[in] client_name The name of client for which a level shall be changed.
     * \param[out] error      An error info in case of failure.
     * \return true if operation was successful, otherwise false.
     **/
    virtual bool requestFilterLevel(int16_t level,
                                    int16_t type,
                                    int16_t id,
                                    const std::string& client_name,
                                    std::ostream& error) noexcept = 0;

    /**
     * \brief
     *    Trigger execution of a trace callback on client side.
     *
     * \param[in]  cbid        The callback ID.
     * \param[in]  data        The optional user data of the callback.
     * \param[in]  client_name The name of client who shall execute the callback.
     * \return true if the callback id exists on client side and the callback was
     *              scheduled for execution.
     **/
    virtual bool executeCallback(int16_t cb_id,
                                 const std::vector<uint8_t> & data,
                                 const std::string & client_name) noexcept = 0;

    /**
     * \brief Will be called upon shutdown of tracecore backchannel server.
     **/
    virtual void shutdown() noexcept = 0;
};


/**
 * \brief
 *    Interface which is used by Android AOSP backchannel server for communication
 *    towards the tracecore server.
 *
 *    Tracecore server needs to implement this interface offering callbacks to the
 *    Android AOSP backchannel server.
**/
class IBackchannelServer
{
public:
    virtual ~IBackchannelServer() = default;

    /**
     * \brief
     *     Will be called by Android AOSP backchannel server to indicate its
     *     availability towards the tracecore.
     *
     * \param[in] listener The AOSP sided listener, listening for callbacks from
     *                     tracecore server.
     **/
    virtual void initBackchannel(std::shared_ptr<IBackchannelServerListener> listener) noexcept = 0;

    /**
     * \brief
     *     Will be called by Android AOSP backchannel server to indicate its
     *     termination towards the tracecore server.
     **/
    virtual void exitBackchannel() noexcept = 0;

    /**
     * \brief
     *     Will be called by Android AOSP backchannel server to forward a
     *     createEntity indication from client towards the tracecore server.
     *
     * \param[in] client_name The name of the client reporting this entity.
     * \param[in] entity      The entity parameters.
     * \return true if entity could be created, otherwise false.
     **/
    virtual bool createEntity(const std::string& client_name,
                              const AidlEntityParams& entity) noexcept = 0;

    /**
     * \brief
     *     Will be called by Android AOSP backchannel server to forward a
     *     createEntityBulk indication from client towards the tracecore server.
     *
     * \param[in] client_name The name of the client reporting this entity.
     * \param[in] entity      The array of entity parameters.
     * \return true if at least one entity could be created, otherwise false.
     **/
    virtual bool createEntityBulk(const std::string& client_name,
                                  const std::vector<AidlEntityParams>& entities) noexcept = 0;

    /**
     * \brief
     *     Will be called by Android AOSP backchannel server to forward a
     *     changeLevel acknowledgment from client towards the tracecore server.
     *
     * \param[in] client_name The name of the client reporting this entity.
     * \param[in] level       The entity level.
     * \param[in] type        The entity type.
     * \param[in] id          The client's entity id.
     * \return true if operation was successful, otherwise false.
     **/
    virtual bool changeFilterLevel(const std::string& client_name,
                                   int16_t level,
                                   int16_t type,
                                   int16_t id) noexcept = 0;
};

} /*  namespace tracing */

#endif /* TRACING_BACKCHANNELSERVER_HXX_ */
