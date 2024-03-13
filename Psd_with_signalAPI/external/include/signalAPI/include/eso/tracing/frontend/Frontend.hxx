/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_FRONTEND_HXX
#define TRACING_FRONTEND_HXX

#include <ipl_config.h>

#include <set>

#include <tracing/tracing_dso.h>
#include <common/types/map.hxx>
#include <common/types/string.hxx>
#include <osal/StreamFmtFileW.hxx>
#include <osal/AtomicCounter.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <osal/SharedObj.hxx>
#include <tracing/message/Message.hxx>
#include <tracing/message/IMessageFilter.hxx>
#include <tracing/entity/EntityURI.hxx>
#include <tracing/entity/EntityType.hxx>
#include <tracing/frontend/PluginState.hxx>
#include <tracing/util/TraceMe.hxx>

namespace util
{
namespace config
{
class Value;
} // end of namespace config
} // end of namespace util

namespace tracing
{

class AttachmentPool;
class Config;
class Core;
class IBackend;
class IBackendStateListener;
class IClockSource;
class IEventListener;
class IFrontendListener;
class IFileOperationFinishedCallback;
class IFileTransferData;
class InternalListener;
class LogBufTracingPlugin;
class ThreadCache;
struct BackendFactory;
struct FileStatus;

namespace protocol
{

class EntityBackRef;
class ConnectionFrontendHandler;
class RemoteListenFrontend;

} // end of namespace protocol

namespace slogreader
{

class SlogReader;

} // end of namespace slogreader


/*!
 *  \brief
 *      Low-level tracing API client implementation.

 *      An instance of this class is automatically created by the high-level
 *      tracing API's client class contained in Client.hxx. To use it, you
 *      only have to include tracing.hxx and use its declared macros. Of
 *      course you need to initialize Osal and Util before, see osal.hxx
 *      and util.hxx.
 */
class TRACINGIMPL_EXPORT Frontend
{
public:
    using FrontendPluginsList = std::vector<std::pair<IFrontendListener *, std::string> >;

    /*!
     * \brief
     *      Create a global instance of the frontend if none is registered
     * \param
     *      name name of tracing process
     * \param
     *      type of trace core. DEPRECATED! It is no longer evaluated. \deprecated
     * \param
     *      readConfig true to read config files, false to work without.
     *      If readConfig is true and the config file is not available
     *      then tracing is disabled.
     *      If readConfig is false then the core is setup always.
     * \param
     *      config provide a manually constructed Config object. This is
     *      intended to be used for unit tests, etc.
     * \param
     *      development Flag to indicate whether development mode should
     *      be forced. This will take precedence over the configured
     *      value and the value determined by the environment.
     * \return
     *      true if tracing is enabled
     */
    static bool init(const ipl::string &name, const ipl::string &type,
            bool readConfig=true, Config * config = nullptr,
            bool development = false) IPL_NOEXCEPT;

    /*!
     * \brief
     *      Get global frontend instance.
     *
     * \return
     *      Valid frontend if init was called otherwise NULL
     */
    static Frontend * getTraceFrontend() IPL_NOEXCEPT;

    /*!
     * \brief
     *      Get the config of the tracing framework.
     *
     * \return
     *      Get the config of the tracing framework
     */
    static Config * getTraceConfig() IPL_NOEXCEPT;

    /*!
     * \brief
     *      Shutdown frontend
     */
    static void exit() IPL_NOEXCEPT;

    /*!
     * \brief
     *      Set the development mode.
     * \note
     *      This has an effect only if called before constructing the Util object.
     */
    static void setDevelopmentMode(bool active) IPL_NOEXCEPT;

    /*!
     * \brief
     *      Determine whether development mode is active.
     * \return
     *      True when development mode is active.
     */
    static bool getDevelopmentMode() IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Constructs a concrete new frontend.
     *  \param
     *      config The configuration data of the core
     */
    explicit Frontend(Config &config) IPL_NOEXCEPT;

    //! \brief Destructor.
    ~Frontend() IPL_NOEXCEPT;

    //! \brief Return configuration of trace core.
    Config &getConfig() IPL_NOEXCEPT { return m_config; }

    //! \brief Return the client name.
    const ipl::string & getClientName() IPL_NOEXCEPT;

    //! \brief Creates a frontend listener by its name
    IFrontendListener * createListener(const ipl::string & name) IPL_NOEXCEPT;

    //! \brief Destroys a frontend listener, created by createListener
    void destroyListener(IFrontendListener * listener) IPL_NOEXCEPT;

    //! \brief Register a listener
    void registerListener(IFrontendListener * listener) IPL_NOEXCEPT;

    //! \brief Unregister a listener
    void unregisterListener(IFrontendListener * listener) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Registers a backend.
     *    \param
     *        backend Reference to the backend.
     *    \param
     *      key Name of the backend. This should be the class name or the name
     *      specified in the configuration file for the backend.
     *    \return
     *        true if registration succeeded, false otherwise.
     */
    bool registerBackend(IBackend & backend, const ipl::string & key) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Registers a backend in optional tapping mode used for monitoring
     *        backend specific traffic.
     *    \param
     *        backend Reference to the backend.
     *    \param
     *      key Name of the backend. This should be the class name or the name
     *      specified in the configuration file for the backend.
     *    \param
     *        tapping When true this backend can be used as tapping source to monitor
     *        the traffic as seen by the backend.
     *    \return
     *        true if registration succeeded, false otherwise.
     */
    bool registerBackend(IBackend & backend, const ipl::string & key,
                         const bool tapping) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Unregister a backend.
     *    \param
     *        backend Reference to the backend.
     *    \return
     *        true if unregistration succeeded, false otherwise.
     */
    bool unregisterBackend(IBackend & backend) IPL_NOEXCEPT;

    //! \brief Register a listener for backend state changes (connects/disconnects).
    void registerBackendStateListener(IBackendStateListener * listener) IPL_NOEXCEPT;

    //! \brief Unregister a listener for backend state changes.
    void unregisterBackendStateListener(IBackendStateListener * listener) IPL_NOEXCEPT;

private:
    //! \brief Get the list of frontend plugins found in the tracing config file
    const ipl::vector<ipl::pair<IFrontendListener *, ipl::string> > & getFrontendPlugins() const IPL_NOEXCEPT;
public:
    /*!
     *    \brief
     *        Wait given maximum time for frontend termination or until notification
     *        via \sa notifyQuit got triggered.
     *    \param
     *        timeout Maximum time to wait for.
     *    \return
     *        true if frontend termination succeeded, false otherwise.
     */
    bool waitForQuit(osal::TimeT timeout) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Send notification to frontend to indicate its state via
     *        \sa waitForQuit.
     */
    void notifyQuit() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Check if tracing and the frontend is actually enabled.
     *    \return
     *        true if frontend is enabled, false otherwise.
     */
    bool isEnabled() const IPL_NOEXCEPT
    {
        return m_enabled;
    }

    /*!
     *    \brief
     *        Start the frontend and launch core worker.
     *    \return
     *        true if frontend is enabled and core worker could be started, false otherwise.
     */
    bool start() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Stop the frontend and the core worker.
     *    \return
     *        true if frontend and core worker could be stopped, false otherwise.
     */
    bool stop() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Check if frontend is enabled and the core is running.
     *    \return
     *        true if frontend and core worker are running, false otherwise.
     */
    bool isRunning() const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Create a new channel entity at the core.
     *    \param
     *        name Channel name.
     *    \param
     *        filterlevel The initial channel filter level. \sa Levels.
     *    \param
     *        parent_uri The entity URI of the parent for the new channel.
     *    \return
     *        ID of the new channel entity. Negative value indicates failure, otherwise success.
     */
    int32_t createChannel(const ipl::string & name, int16_t & filterlevel,
            const EntityURI & parent_uri = EntityURI()) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Enable a channel at the core.
     *    \param
     *        cid Channel entity ID.
     *    \return
     *        true if successful, false otherwise.
     */
    bool enableChannel(int32_t cid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Disable a channel at the core.
     *    \param
     *        cid Channel entity ID.
     *    \return
     *        true if successful, false otherwise.
     */
    bool disableChannel(int32_t cid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Check if a given channel is enabled at the trace core.
     *    \param
     *        cid Channel entity ID.
     *    \return
     *        true if enabled, false otherwise.
     */
    bool isChannelEnabled(int32_t cid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Create a new thread entity at the core.
     *    \param
     *        name thread name.
     *    \param
     *        filterlevel The initial thread filter level. \sa Levels.
     *    \param
     *        parent_uri The entity URI of the parent for the new thread.
     *    \return
     *        ID of the new thread entity. Negative value indicates failure, otherwise success.
     */
    int32_t createThread(const ipl::string & name, int16_t & filterlevel,
            const EntityURI & parent_uri = EntityURI()) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Enable a thread at the core.
     *    \param
     *        tid thread entity ID.
     *    \return
     *        true if successful, false otherwise.
     */
    bool enableThread(int32_t tid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Disable a thread at the core.
     *    \param
     *        tid thread entity ID.
     *    \return
     *        true if successful, false otherwise.
     */
    bool disableThread(int32_t tid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Check if a given thread is enabled at the trace core.
     *    \param
     *        tid thread entity ID.
     *    \return
     *        true if enabled, false otherwise.
     */
    bool isThreadEnabled(int32_t tid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Create a new callback entity at the core.
     *    \param
     *        name callback name.
     *    \param
     *        parent_uri The entity URI of the parent for the new callback.
     *    \return
     *        ID of the new callback entity. Negative value indicates failure,
     *        otherwise success.
     */
    int32_t createCallback(const ipl::string & name,
            const EntityURI & parent_uri = EntityURI()) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Enable a callback at the core.
     *    \param
     *        cbid callback entity ID.
     *    \return
     *        true if successful, false otherwise.
     */
    bool enableCallback(int32_t cbid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Disable a callback at the core.
     *    \param
     *        cbid callback entity ID.
     *    \return
     *        true if successful, false otherwise.
     */
    bool disableCallback(int32_t cbid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Check if a given callback is enabled at the trace core.
     *    \param
     *        cbid callback entity ID.
     *    \return
     *        true if enabled, false otherwise.
     */
    bool isCallbackEnabled(int32_t cbid) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Get timestamp in nanoseconds from loaded clock source.
     *  \note
     *      The timestamp returned is only valid after Frontend::start()
     *      has been called.
     *  \return
     *      Timestamp in nanoseconds. In case the frontend was not started
     *      yet, 0 is returned.
     */
    osal::TimeT getTimestampNS();

    /*!
     *  \brief
     *      Get timestamp in milliseconds from loaded clock source.
     *  \note
     *      The timestamp returned is only valid after Frontend::start()
     *      has been called.
     *  \return
     *      Timestamp in milliseconds. In case the frontend was not started
     *      yet, 0 is returned.
     */
    osal::TimeT getTimestamp();

    /*!
     *  \brief
     *      Get the flags of the loaded clocksource.
     *
     *  \return
     *      The flags of the loaded clocksource \sa IClockSource.
     */
    uint32_t getClocksourceFlags();

    /*!
     *  \brief
     *      Log a string message.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      msg The message string.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers,
            const ipl::string & msg) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a string message with message attributes.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      attr The attributes containing a list of tags and/or objects to be associated
     *           to the message. \sa MessageAttributes.
     *  \param
     *      msg The message string.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers,
            const ipl::string & msg, MessageAttributes&& attr) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a raw data message.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      type The raw data message type, usually non-utf8. \sa MessageTypes.
     *  \param
     *      data The message payload.
     *  \param
     *      len The message payload length.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers, int16_t type,
            const void * data, size_t len) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a string message with option to take ownership of allocated resources.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      data The message string.
     *  \param
     *      take_ownership Flag to indicate if ownership shall be taken.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers, char * data,
            bool take_ownership) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a string message with attributes and option to take ownership of
     *      allocated resources.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      data The message string.
     *  \param
     *      take_ownership Flag to indicate if ownership shall be taken.
     *  \param
     *      attr The attributes containing a list of tags and/or objects to be
     *           associated to the message. \sa MessageAttributes.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers, char * data,
            bool take_ownership, MessageAttributes&& attr) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a string message with custom timestamp and option to take ownership
     *      of allocated resources.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      timestamp The timestamp to be applied for the message.
     *  \param
     *      data The message string.
     *  \param
     *      take_ownership Flag to indicate if ownership shall be taken.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers,
            osal::TimeT timestamp, char * data, bool take_ownership) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a raw data message with custom timestamp.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      type The raw data message type, usually non-utf8. \sa MessageTypes.
     *  \param
     *      timestamp The timestamp to be applied for the message.
     *  \param
     *      data The message payload.
     *  \param
     *      len The message payload length.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers, int16_t type,
            osal::TimeT timestamp, const void * data, size_t len) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a raw data message with custom timestamp and message attributes.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      type The raw data message type, usually non-utf8. \sa MessageTypes.
     *  \param
     *      timestamp The timestamp to be applied for the message.
     *  \param
     *      data The message payload.
     *  \param
     *      len The message payload length.
     *  \param
     *      attr The attributes containing a list of tags and/or objects to be associated
     *           to the message. \sa MessageAttributes.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers, int16_t type,
            osal::TimeT timestamp, const void * data, size_t len,
            MessageAttributes && attr) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a raw data message with custom timestamp, ownership option and message attributes.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      type The raw data message type, usually non-utf8. \sa MessageTypes.
     *  \param
     *      timestamp The timestamp to be applied for the message.
     *  \param
     *      data The message payload.
     *  \param
     *      len The message payload length.
     *  \param
     *      take_ownership Flag to indicate if ownership shall be taken.
     *  \param
     *      attr The attributes containing a list of tags and/or objects to be associated
     *           to the message. \sa MessageAttributes.
     */
    void log(int32_t cid, int32_t tid, int16_t level, int16_t modifiers, int16_t type,
            osal::TimeT timestamp, void * data, size_t len, bool take_ownership,
            MessageAttributes && attr) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Try to log a string message, if it does not block.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      level The message filter level of the trace message. \sa Levels.
     *  \param
     *      modifiers The message parameters or extensions to be applied. \sa Modifiers.
     *  \param
     *      msg The message string.
     *  \return
     *      true when message could be transmitted, false when message got lost.
     */
    bool tryLog(int32_t cid, int32_t tid, int16_t level, int16_t modifiers,
            const ipl::string & msg) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Write an emergency log entry.
     *
     *  \param
     *      message The message string.
     */
    void emergencyLog(const ipl::string & message) IPL_NOEXCEPT;

    //! \brief send an emergency break
    void emergencyBreak() IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Check filter level for related channel and thread context.
     *
     *  \param
     *      msg_level The message filter level of the trace message. \sa Levels.
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \return
     *      true when message level is enabled, otherwise false.
     */
    bool isLevelEnabled(const int16_t msg_level, const int32_t cid, const int32_t tid) const;

    /*!
     *  \brief
     *      Send an echo log entry.
     *
     *  \param
     *      message The message string.
     */
    void echoEvent(const std::string & message) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Create a new entity at the core.
     *  \param
     *      type The entity type. \sa EntityType.
     *  \param
     *      name entity name.
     *  \param
     *      filterlevel The initial entity filter level. \sa Levels.
     *  \param
     *      parent_uri The entity URI of the parent for the new entity.
     *  \param
     *      proc_name Optional process name relevant for evaluation of process specific
     *                filter level for the new entity.
     *  \return
     *      URI of the new entity. Negative URI ID indicates failure, otherwise success.
     */
    const EntityURI & createEntity(int16_t type, const ipl::string & name,
            int16_t & filterlevel, const EntityURI & parent_uri,
            const std::string & proc_name = "") IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Create a new root entity at the core.
     *  \param
     *      type The entity type. \sa EntityType.
     *  \param
     *      name entity name.
     *  \param
     *      filterlevel The initial entity filter level. \sa Levels.
     *  \return
     *      URI of the new entity. Negative URI ID indicates failure, otherwise success.
     */
    const EntityURI & createRootEntity(int16_t type, const ipl::string & name,
            int16_t & filterlevel) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Enable an entity.
     *  \param
     *      uri of the entity.
     *  \return
     *      true upon success, otherwise false.
     */
    bool enableEntity(const EntityURI & uri) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Disable an entity.
     *  \param
     *      uri of the entity.
     *  \return
     *      true when successful, otherwise false.
     */
    bool disableEntity(const EntityURI & uri) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Check if an entity is enabled.
     *  \param
     *      uri of the entity.
     *  \return
     *      true when enabled, otherwise false.
     */
    bool isEntityEnabled(const EntityURI & uri) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Set the level of an entity.
     *  \param
     *      uri of the entity.
     *  \param
     *      level The new level. \sa Levels.
     *  \return
     *      true when successful, otherwise false.
     */
    bool changeFilterLevel(const EntityURI & uri, int16_t level) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Set a new privacy flags of the given type for a channel entity.
     *  \param
     *      uri The URI of the channel entity whose privacy flags should be changed.
     *  \param
     *      privacy_flags The new privacy flags for the entity.
     *  \param
     *      type The type of privacy flags to be changed.
     *  \return
     *      true if change was sucessful.
     */
    bool changePrivacyFlags(const EntityURI & uri,
            const uint32_t privacy_flags, const int16_t type) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Get the privacy flags of given type for a channel entity.
     *  \param
     *      uri The URI of the channel entity whose privacy flags should be changed.
     *  \param
     *      type The type of privacy flags.
     *  \param
     *      filter_level The optional filter level, only relevant for CONFIG_DEFAULT type.
     *                   \sa PrivacyFlagsType.
     *  \return
     *      privacy_flags The privacy flags for the entity.
     */
    uint32_t getPrivacyFlags(const EntityURI & uri, int16_t type,
            int16_t filter_level=Levels::LevelNONE) const IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Set a new message filter for frontend or default backend.
     *  \param
     *      filter The new filter to be applied by frontend. A valid filter
     *      must have a valid destroy method.
     *  \param
     *      type The message filter type \sa IMessageFilter::FilterType.
     *  \return
     *      true when sucessful, otherwise false.
     */
    bool setMessageFilter(IMessageFilter * filter, const int16_t type) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Get the message filter name for frontend or default backend.
     *  \param
     *      type The message filter type \sa IMessageFilter::FilterType.
     *  \return
     *      the filter name.
     */
    const ipl::string getMessageFilterName(const int16_t type) const IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Resolve the name of an entity, i.e. for channels the last substring
     *      tokenized by '_'.
     *  \param
     *      uri The entity URI.
     *  \return
     *      The entity name.
     */
    const char * resolveName(const EntityURI & uri) const IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Resolve the path of an entity, i.e. name prefixed with parent names
     *      separated by '_'.
     *  \param
     *      uri The entity URI.
     *  \param
     *      local_path Flag indicating if it is a local path.
     *  \return
     *      The entity name.
     */
    const ipl::string resolvePath(const EntityURI & uri, bool local_path = true) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Resolve the name of an entity's parent.
     *    \param
     *        uri The URI of the entity whose parent name should be resolved.
     *    \param
     *        type The entity type as specified in EntityType.hxx.
     *    \return
     *        A string containing the parent name which may be empty if no parent exists.
     */
    const std::string resolveParentName(const EntityURI & uri, const int16_t type) const;

    /*!
     *  \brief
     *      Triggers trace core to flush all pending messages.
     *
     *  \param
     *        doBlock Flag indicating if the operation shall be blocking.
     *  \param
     *      timeout The duration in milliseconds where the operation is blocking.
     *              A value of 0 indicates no timeout.
     *  \return
     *      true when sucessful, otherwise false.
     */
    bool flushMessages(bool doBlock, osal::TimeT timeout = 1000) IPL_NOEXCEPT;

    //! \brief Clears all messages currently stored in buffer
    void clearMessageBuffer() IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Provides the root entity of given entity type.
     *  \param
     *      type The entity type. \sa EntityType.
     *  \return
     *      URI of the root entity.
     */
    const EntityURI & getRootEntityURI(int16_t type) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Report number of dropped messages to trace core to update statistics and
     *      message buffers.
     *  \param
     *      num The number of messages.
     *  \return
     *      true when sucessful, otherwise false.
     */
    bool reportLostMessages(size_t num) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Register a timezone at the trace core.
     *
     *      There may be different time sources active at the trace core which may even
     *      advance with different speed.
     *  \param
     *      name The name the timezone.
     *  \param
     *      resolution The clock resolution of the timezone. Following values are defined:
     *          0: seconds
     *          1: milliseconds
     *          2: microseconds
     *          3: nanoseconds
     *  \return
     *      the unique ID of new timezone or -1 in case of failure.
     */
    int32_t registerTimeZone(const ipl::string & name, int32_t resolution = 1) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Update a time zone's current time using trace core internal reference.
     *  \param
     *      id The timezone id.
     *  \param
     *      current_time The current timezone time.
     */
    void updateTimeZone(int32_t id, int64_t current_time) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Update a time zone's current time together with the reference core_time.
     *  \param
     *      id The timezone id.
     *  \param
     *      timezone_time The current timezone time.
     *  \param
     *      core_time The reference core time.
     */
    void updateTimeZone(int32_t id, int64_t timezone_time, int64_t core_time) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Request the last time update of a timezone.
     *  \param
     *      name The name of the timezone.
     *  \param
     *      timezone_time Result parameter containing the last time update.
     *  \return
     *      True if the timezone was updated at least once, false otherwise or
     *      if the timezone does not exist. In case false is returned the value
     *      in timezone_time is unspecified.
     */
    bool getLastTimeZoneUpdateByName(const ipl::string & name, int64_t & timezone_time) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Tries to provide a clocksource with given name.
     *  \param
     *      name The name of the clocksource.
     *  \return
     *      The clocksource or nullptr upon failure.
     */
    IClockSource* getClockSource(const std::string& name);

    /*!
     *  \brief
     *      Provides the configured clock suspend threshold.
     *  \return
     *      Suspend threshold value in milliseconds.
     */
    int32_t getClockSuspendThresMS() const IPL_NOEXCEPT;

    /*!
     *    \brief
     *       Request uploading a file to the trace core.
     *    \param
     *       path Storage path of the uploaded file.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the file transfer.
     *    \param
     *       bid The id of the backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     */
    int32_t transmitFile(const osal::Path & path,
            IFileOperationFinishedCallback * cb = nullptr, int16_t bid = -1) IPL_NOEXCEPT;

    /*!
     *    \brief
     *       Request uploading a file to the trace core.
     *    \param
     *       path Storage path of the uploaded file.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the file transfer.
     *    \param
     *       bid The id of the backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     */
    int32_t requestFile(const osal::Path & path,
            IFileOperationFinishedCallback * cb = nullptr, int16_t bid = -1) IPL_NOEXCEPT;

    /*!
     *    \brief
     *       Request sending a file status to the trace core.
     *    \param
     *       path Storage path of the file whose existence shall be signalled.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the file transfer.
     *    \param
     *       bid The id of the backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     *    \note
     *       This method is intended to be used for notifying the trace core
     *       of file existence on a remote node.
     */
    int32_t transmitFileStatus(const osal::Path & path,
            IFileOperationFinishedCallback * cb = nullptr, int16_t bid = -1) IPL_NOEXCEPT;

    /*!
     *    \brief
     *       Request a file status from the trace core.
     *    \param
     *       path Storage path of the file whose status should be queried.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the file transfer.
     *    \param
     *       bid The id of the backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     */
    int32_t requestFileStatus(const osal::Path & path,
            IFileOperationFinishedCallback * cb = nullptr, int16_t bid = -1) IPL_NOEXCEPT;

    /*!
     *    \brief
     *       Transmits data to the trace core.
     *    \param
     *       vpath Storage path of the file to read from.
     *    \param
     *       data The data to be transmitted.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the transfer.
     *    \param
     *       bid The id of the backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     */
    int32_t transmitData(
            const osal::Path & vpath,
            IFileTransferData * data,
            IFileOperationFinishedCallback * cb = nullptr,
            int16_t bid = -1) IPL_NOEXCEPT;

    /*!
     *    \brief
     *       Provides core statistics numbers of transmitted and dropped messages.
     *    \param
     *       msgs Number of total transmitted messages.
     *    \param
     *       drops Number of total dropped messages.
     *    \return
     *       true when sucessful, otherwise false.
     */
    bool getCoreStatistics(size_t & msgs, size_t & drops) const IPL_NOEXCEPT;

    //! \brief DEPRECATED! Use getConfigString(int16_t...) instead. \deprecated
    ipl::string getConfigString(const ipl::string & plugin_name, const ipl::string & key, const ipl::string & default_value = "") const IPL_NOEXCEPT;
    //! \brief DEPRECATED! Use getConfigInteger(int16_t...) instead. \deprecated
    int32_t getConfigInteger(const ipl::string & plugin_name, const ipl::string & key, int32_t default_value = 0) const IPL_NOEXCEPT;
    //! \brief DEPRECATED! Use getConfigBool(int16_t...) instead. \deprecated
    bool getConfigBool(const ipl::string & plugin_name, const ipl::string & key, bool default_value = false) const IPL_NOEXCEPT;
    //! \brief DEPRECATED! Use getConfigDictionary() instead. \deprecated
    ipl::vector<int32_t> getConfigIntegerArray(const ipl::string & plugin_name, const ipl::string & key, const ipl::vector<int32_t> & default_value = ipl::vector<int32_t>()) const IPL_NOEXCEPT;
    //! \brief DEPRECATED! Use getConfigDictionary() instead. \deprecated
    ipl::vector<ipl::string> getConfigStringArray(const ipl::string & plugin_name, const ipl::string & key, const ipl::vector<ipl::string> & default_value = ipl::vector<ipl::string>()) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *       Registers a generic resource manager with callback.
     *    \param
     *       name Resource manager name.
     *    \param
     *       func Callback function.
     *    \param
     *       data Callback payload, usually the caller.
     *    \return
     *       true when sucessful, otherwise false.
     */
    bool registerTriggerResMan(const ipl::string & name, void (*func)(void *),
            void * data) IPL_NOEXCEPT;

    /*!
     *    \brief
     *       Unregisters a generic resource manager.
     *    \param
     *       name Resource manager name.
     *    \return
     *       true when sucessful, otherwise false.
     */
    bool unregisterTriggerResMan(const ipl::string & name) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Post an event towards core.
     *    \param
     *        name The name of the event.
     *    \param
     *        push_back A flag indicating if event shall be pushed at back or front
     *        of the event queue.
     */
    void postEvent(const ipl::string & name, bool push_back = true) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Register a listener for "generic" trace core events.
     *    \param
     *        l An implementation of the IEventListener interface.
     *    \param
     *        event_name The event that the listener should be registered for.
     */
    void registerEventListener(IEventListener * l, const ipl::string & event_name) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Unregister a listener for "generic" trace core events.
     *    \param
     *        l An implementation of the IEventListener interface.
     *    \param
     *        event_name The event that the listener should be unregistered from.
     *        An empty string will unregister the listener from all events it
     *        currently is registered for.
     */
    void unregisterEventListener(IEventListener * l, const ipl::string & event_name = ipl::string()) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Initialize the configured frontend plugins.
     *
     *    \note
     *        Only normal plugins without 'early' flag are initialized.
     */
    void initializeFrontendPlugins() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Initialize the configured early frontend plugins, which are.
     *
     *    \note
     *        Only plugins with 'early' flag are initialized.
     */
    void initializeEarlyFrontendPlugins() IPL_NOEXCEPT;

    //! \brief Shutdown the configured and active frontend plugins
    void shutdownFrontendPlugins() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get a string value from the configuration.
     *    \param
     *      fid The requesting plugin's ID.
     *    \param
     *        key The name of the configuration key.
     *    \param
     *        default_value The value to return, if the key is not found in the
     *        configuration.
     *    \return
     *        default_value if the key is not found in the configuration, a
     *        string as specified in the configuration otherwise.
     */
    ipl::string getConfigString(int16_t fid, const ipl::string & key,
            const ipl::string & default_value = "") const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get an integer value from the configuration.
     *    \param
     *      fid The requesting plugin's ID.
     *    \param
     *        key The name of the configuration key.
     *    \param
     *        default_value The value to return, if the key is not found in the
     *        configuration.
     *    \return
     *        default_value if the key is not found in the configuration, an
     *        integer as specified in the configuration otherwise.
     */
    int32_t getConfigInteger(int16_t fid, const ipl::string & key,
            int32_t default_value = 0) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get a boolean value from the configuration.
     *    \param
     *      fid The requesting plugin's ID.
     *    \param
     *        key The name of the configuration key.
     *    \param
     *        default_value The value to return, if the key is not found in the
     *        configuration.
     *    \return
     *        default_value if the key is not found in the configuration, a
     *        boolean as specified in the configuration otherwise.
     */
    bool getConfigBool(int16_t fid, const ipl::string & key,
            bool default_value = false) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get the backend's dictionary (if available) from the tracing
     *        configuration.
     *    \param
     *        fid The requesting plugin's ID.
     *    \return
     *        A dictionary containing additional configuration entries for the
     *        backend.
     */
    const util::config::Value & getConfigDictionary(int16_t fid) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Indicates if a preset config exists for given client.
     *    \param
     *        client The client name.
     *    \return
     *        true if preset config for given client name exists, otherwise false.
     */
    bool isClientWithPresetConfig(const std::string & client) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Provides the JSON formatted levels configuration string for the
     *        given entity_type of a client.
     *
     *    \param
     *        entity_type The entity type.
     *    \param
     *        client The client name.
     *    \param[out]
     *        cfg The client configuration.
     *    \return
     *        true if client config for given client was found, otherwise false.
     */
    bool getClientLevelsConfig(int16_t entity_type, const std::string & client,
                               std::string & cfg) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Replaces the filter levels configuration for the given entity_type.
     *
     *    \param
     *        entity_type The entity type.
     *    \param
     *        cfg The new levels configuration string in JSON format.
     */
    void replaceLevelsConfig(int16_t entity_type, const std::string & cfg) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get the factory function struct of a backend.
     *    \param
     *        name The name of the backend as found in tracing.json.
     *    \return
     *        Pointer to the struct containing backend factory function pointers,
     *        NULL if the backend is not found.
     */
    BackendFactory * getBackendFactory(const std::string & name);

    /*!
     *    \brief
     *        Register a key for creating key/value pairs in trace statistics messages.
     *    \param
     *        key A short (typically two letters) identifier of the statistic indicator.
     *    \param
     *        flags An or-ed int of flags defined in CoreStatistics.hxx
     *    \note
     *        There is no indication wether your key registration collides with another
     *        key, so this needs to be coordinated on a project level.
     */
    void registerStatisticsKey(const ipl::string & key, uint8_t flags) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Update the value of a statistic indicator.
     *    \param
     *        key The key name of the indicator that should be updated. The key needs
     *        to be registered before using it otherwise the update will be silently
     *        ignored.
     *    \param
     *        value The current value of the statistic indicator.
     */
    void updateStatistics(const ipl::string & key, int32_t value) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Register frontend plugin for usage of entity attachments.
     *    \param
     *        fid The requesting plugin's ID.
     *    \return
     *        true if attachments can be used by the plugin.
     */
    bool registerAttachments(int16_t fid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Unregister frontend plugin for usage of entity attachments.
     *
     *        This will invalidate the stored pointers for this plugin. Further
     *        calls to getAttachment() will return nullptr only.
     *    \param
     *        fid The requesting plugin's ID.
     */
    void unregisterAttachments(int16_t fid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Retrieve a previously stored attachment.
     *    \param
     *        fid The requesting plugin's ID.
     *    \param
     *        uri The entity URI which was used for storing the attachment.
     *    \return
     *        The stored pointer or nullptr if not set.
     */
    void * getAttachment(int16_t fid, const EntityURI & uri) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Store a pointer referencing an entity.
     *    \param
     *        fid The requesting plugin's ID.
     *    \param
     *        uri The entity URI which shall be used for storing the attachment.
     *    \param
     *        attachment The pointer that shall be stored.
     */
    void setAttachment(int16_t fid, const EntityURI & uri, void * attachment) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get the accumulated time offset where system was suspended.
     *        This allows to align the timestamps of non-suspend-aware clocksources,
     *        provided a suitable clocksource is active.
     *    \param
     *        offset_ns The suspend time offset in [ns] (out).
     *    \return
     *        boolean flag, only when true the offset is valid.
     */
    bool getSuspendTimeOffset(int64_t & offset_ns) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Check if the active clocksource supports provisioning of the suspend time
     *        offset.
     *    \return
     *        true when supported.
     */
    bool isSuspendTimeOffsetSupported() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Check whether authorization for tracing exists.
     *
     *        Some tracing functionality may be restricted in customer environments
     *        and require special authorization to be enabled. How this is
     *        determined is project-specific, but backends can query this method
     *        to check whether authorization was granted.
     *    \return
     *        true if trace output is allowed.
     */
    bool getTraceOutputAuthorized() const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Check whether authorization for controlling certain tracing features exists.
     *
     *    \return
     *        true if trace control functionality is enabled.
     */
    bool getTraceControlAuthorized() const IPL_NOEXCEPT;

protected:
    Config &               m_config;                //! The configuration (which usually comes from reading a config file).
    Core *                 m_core;                  //! The trace core doing all the real work.
    bool                   m_enabled;               //! Is tracing enabled at all?
    bool                   m_do_quit;               //! Shall we quit?
    const ipl::string &    m_emergency_file_name;   //! The name of the emergency log file.
    osal::StreamFmtFileW * m_emergency_file;        //! The file used for storing emergency log messages.
    EntityURI              m_root_entities[EntityType::LAST_ENTITY];  //! The root entities in the entity model.

    static Frontend *          g_instance;
    static Config *            g_config;
    static osal::AtomicCounter g_instance_counter;
    static bool                g_enabled;

    osal::Mutex         m_frontend_lock;
    osal::Condition     m_frontend_cond;
    osal::AtomicCounter m_num_listeners;
    InternalListener *  m_internal_listener;

    size_t m_max_msg_len;

    int16_t m_next_fid;
    ipl::map<int16_t, ipl::string> m_fids;
    ipl::vector<PluginState> m_plugin_states;
    std::set<IFrontendListener *> m_registered_listeners;
    //! TraceMe client channel
    IPL_TRACEME_DECLARE_SCOPE(Frontend);

    //! Friend declaration for setAttachment()/getAttachment()
    friend class tracing::protocol::ConnectionFrontendHandler;

    //! Friend declaration for setAttachment()/getAttachment()
    friend class tracing::protocol::RemoteListenFrontend;

    friend class InternalListener;
    friend class tracing::slogreader::SlogReader;
    friend class ThreadCache;
    friend class LogBufTracingPlugin;

    //! \brief DEPRECATED! Set a custom attachment to an entity. \deprecated
    void setAttachment(EntityURI & uri, tracing::protocol::EntityBackRef * back_reference) IPL_NOEXCEPT;
    //! \brief DEPRECATED! Retrieve the attachment from the entity. \deprecated
    tracing::protocol::EntityBackRef * getAttachment(const EntityURI & uri) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Create a new entity at the core.
     *  \param
     *      type The entity type. \sa EntityType.
     *  \param
     *      name entity name.
     *  \param
     *      filterlevel The initial entity filter level. \sa Levels.
     *  \param
     *      parent_uri The entity URI of the parent for the new entity.
     *  \param
     *      fid The requesting plugin's ID.
     *  \param
     *      attachment Used by the traceserver to store references to external
     *      entity URIs
     *  \param
     *      proc_name Optional process name relevant for evaluation of process specific
     *                filter level for the new entity.
     *  \return
     *      URI of the new entity. A negative URI ID indicates failure, otherwise success.
     */
    const EntityURI & createEntity(int16_t type, const ipl::string & name,
            int16_t & filterlevel, const EntityURI & parent_uri,
            int16_t fid, tracing::protocol::EntityBackRef * attachment,
            const std::string & proc_name) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Create a unique new entity at the core.
     *      Note: This is expensive and it may modify \a name, try to avoid it
     *  \param
     *      type The entity type. \sa EntityType.
     *  \param
     *      name entity name.
     *  \param
     *      filterlevel The initial entity filter level. \sa Levels.
     *  \param
     *      parent_uri The entity URI of the parent for the new entity.
     *  \param
     *      fid The requesting plugin's ID.
     *  \param
     *      attachment Used by the traceserver to store references to external
     *      entity URIs
     *  \return
     *      URI of the new unique entity.
     *      A negative URI ID indicates failure, otherwise success.
     */
    const EntityURI & createUniqueEntity(int16_t type, ipl::string & name,
            int16_t & filterlevel, const EntityURI & parent_uri,
            int16_t fid, tracing::protocol::EntityBackRef * attachment) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Log a trace message received as MessagePtr already.
     *  \param
     *      msg The MessagePtr reference.
     */
    void log(MessagePtr & msg) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Handle a message length error, print a warning and report message drop to core.
     *
     *  \param
     *      cid The channel entity ID of the trace channel used for message transmission.
     *  \param
     *      tid The thread entity ID of the trace channel used for message transmission.
     *  \param
     *      len The message length.
     */
    void messageLengthError(int32_t cid, int32_t tid, size_t len) const IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Set the thread cache in the trace core.
     *
     *  \param
     *      cache The thread cache instance.
     */
    void setThreadCache(ThreadCache * cache) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Get the name of a frontend plugin.
     *  \param
     *      fid The requesting plugin's ID.
     *  \return
     *      The name of the plugin.
     */
    const ipl::string & getPluginName(int16_t fid) const IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Register and initialize a list of frontend plugins.
     *  \param
     *      plugins The list of plugin instances and names.
     */
    void initPlugins(const FrontendPluginsList & plugins) IPL_NOEXCEPT;
};

}//namespace tracing

#endif /* TRACING_FRONTEND_HXX */
