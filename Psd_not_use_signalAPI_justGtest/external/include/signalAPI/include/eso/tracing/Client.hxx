/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_CLIENT_HXX
#define TRACING_CLIENT_HXX

#include <ipl_config.h>

#include <tracing/tracing_dso.h>
#include <tracing/util/TraceMe.hxx>
#include <common/types/string.hxx>
#include <common/types/map.hxx>
#include <common/tracing/IClient.hxx>
#include <common/tracing/Levels.hxx>
#include <common/tracing/Channel.hxx>
#include <common/tracing/IChannelListListener.hxx>
#include <common/tracing/ChannelList.hxx>
#include <osal/AtomicCounter.hxx>
#include <osal/Mutex.hxx>
#include <tracing/frontend/IFrontendListener.hxx>

namespace tracing
{

class Config;
class CallbackObject;
class Frontend;
class ThreadCache;
class IThreadCache;

/*!
 *  \brief
 *      This class is one of two main entry points for the high-level tracing API.

 *      The client is necessary when using the high-level tracing API. Usually you
 *      create an instance of this class (either by using a macro defined in
 *      tracing.hxx or by simply declaring it in your sources) and call its init()
 *      method. Calling init() more than once should be ok, but you need to remember
 *      calling exit() the same number of times for shutting down correctly.
 */
class TRACINGIMPL_EXPORT Client : public IClient, public IFrontendListener, public IChannelListListener
{
public:

    /*!
     *  \brief
     *      Initialize the tracing system.
     *  \note
     *      You should call this before creating any threads.
     *  \param
     *      name The client's name. This name should be present in the framework's transport
     *      configuration file if the client should establish connections to the traceserver.
     *      Furthermore it is used to select a specific client node in the tracing config
     *      file. If this name is not found in tracing's config file, the default node of the
     *      client top-node will be used.
     *  \param
     *      type The type of the trace core. DEPRECATED! It is no longer evaluated. \deprecated
     *  \param
     *      readConfig Use the configuration files to setup trace core. If false
     *      then no configuration file is used
     *  \return
     *      true if tracing is enabled, false if disabled
     */
    static bool init(const ipl::string & name, const ipl::string & type = "client", bool readConfig = true) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      (Possibly) uninitialize the tracing system.
     *  \note
     *      If init() was called more than once, you need to call exit the same
     *      number of times for really shutting down the trace system.
     */
    static void exit() IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Singleton-like construction method for the Client.
     *  \return
     *      If a client is initialized then return the client otherwise NULL
     */
    static Client * getTraceClient() IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Create an own client for the trace core
     */
    explicit Client(Frontend & frontend) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Non-virtual destructor.
     */
    ~Client() IPL_NOEXCEPT override;
    
    Client(const Client &)=delete;
    Client &operator = (const Client &)=delete;

    /*!
     *  \brief
     *      Start the client and the associated frontend
     */
    void start() IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Stop the client and the associated frontend
     */
    void stop() IPL_NOEXCEPT;

    /*!
     * \brief
     *      Listen on changes from the ChannelList: registration of a new channel
     */
    void registerChannel(Channel *channel) IPL_NOEXCEPT override;

    /*!
     * \brief
     *      Listen on changes from the ChannelList: unregistration of a new channel
     */
    void unregisterChannel(Channel *channel) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Determines if tracing's inner working thread is running.
     *  \return
     *      True, if initializing was successful and the tracing worker thread is running.
     */
    bool isRunning() IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Enable tracing (at run-time).
     */
    void enable() IPL_NOEXCEPT
    {
        enableChannel(&m_root_channel);
    }

    /*!
     *  \brief
     *      Disable tracing (at run-time).
     */
    void disable() IPL_NOEXCEPT
    {
        disableChannel(&m_root_channel);
    }

    /*!
     *  \brief
     *      Get the client's trace frontend.

     *      Sometimes it may be useful to call some low-level tracing functions directly,
     *      mostly for test purposes. So this method provides a reference for the client's
     *      low-level trace frontend. You should think twice, if you really need this, or
     *      if it would be better to use the low-level interface alone. E.g. it is not
     *      advisable to create channels both at the high- and low-level API at the same
     *      time.
     *  \return
     *      The low-level frontend.
     */
    Frontend & getFrontend() IPL_NOEXCEPT
    {
        return m_frontend;
    }

    //! \brief Describes the signature that user callback functions must have.
    typedef void (*CallbackFunc)(int32_t, void * const, size_t);

    /*!
     *  \brief
     *      Register a function as callback.
     *  \param
     *      name A unique name for this callback function.
     *  \param
     *      func The function that should get executed when the callback is issued.
     *  \return
     *      The ID of the registered callback, or -1 if registration failed.
     */
    int32_t registerCallback(const ipl::string & name, CallbackFunc func) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Register a callback object.
     *  \param
     *      name A unique name for this callback object.
     *  \param
     *      obj The object implementing the interface as declared in CallbackObject.hxx.
     *  \return
     *      The ID of the registered callback, or -1 if registration failed.
     */
    int32_t registerCallback(const ipl::string & name, CallbackObject * obj) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Unregister a callback function again.
     *  \param
     *      callback_id The ID as returned from registerCallback().
     *  \return
     *      true if unregistration was successful.
     */
    bool unregisterCallback(int32_t callback_id) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Register a thread at the trace core.

     *      This function shall be called from the thread's context which will
     *      be associated with the name specified. This only works if the call
     *      to this function is the first tracing-related call within this thread,
     *      i.e. no trace message etc. was emitted before from the caller thread.
     *      Otherwise the trace core will have an entity for this thread already
     *      which carries the thread's OSAL thread ID as name. Updating names is
     *      not supported. You may want to use the IPL_TRACE_REGISTER_THREAD()
     *      macro defined in tracing.hxx instead of this function.
     *  \param
     *      name The name the thread should carry in the trace core. This will
     *      be visible in the viewer or other backends, too.
     */
    void registerThread(const ipl::string & name) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Unregister a thread at the trace core.
     *
     *      You can call this function (or maybe even better the macro
     *      IPL_TRACE_UNREGISTER_THREAD()) to disable a thread's entity in the
     *      trace core and free resources that were created for the thread's name.
     *      This function must be called from within the thread context which
     *      should be disabled and is best placed right before the return-
     *      statement in the caller thread's thread loop.
     *      This also works if registerThread() was not called before.
     */
    void unregisterThread() IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Register a timezone at the trace core.
     *
     *      There may be different time sources active at the trace core which may even
     *      advance with different speed.
     *  \param
     *      name The name the timezone.
     *  \param
     *      resolution The clock resolution of the timezone. \sa IClockSource::ClockResolution
     *  \return
     *      the unique ID of new timezone or -1 in case of failure.
     */
    int32_t registerTimeZone(const ipl::string & name, int32_t resolution = 1) IPL_NOEXCEPT override;

    //! \brief Update a time zone's current time.
    void updateTimeZone(int32_t id, int64_t current_time) IPL_NOEXCEPT override;

    /*!
     *    \brief
     *        Initialise the frontend listener.
     *        Callback from core to this frontend listener
     *
     *    \param
     *        fid The frontend plugin id.
     *    \param
     *        frontend A pointer to the frontend instance, acquired by e.g. calling
     *        Frontend::getTraceFrontend()
     */
    void init(int16_t fid, Frontend * frontend) IPL_NOEXCEPT override
    {
        IFrontendListener::init(fid, frontend);
    }

    //! \sa IFrontendListener::shutdown
    void shutdown() IPL_NOEXCEPT override { /* nop */ }

    //! \sa IFrontendListener::executeCallback
    void executeCallback(int32_t cbid, void * data, size_t len) IPL_NOEXCEPT override;

    //! \sa IFrontendListener::requestFilterLevel
    void requestFilterLevel(const EntityURI & uri, int16_t level) IPL_NOEXCEPT override;

    //! \sa IFrontendListener::requestQuit
    void requestQuit() IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Log a trace message.

     *      This method should probably be called by channels only. It creates a new trace
     *      message and forwards it to the frontend for further processing.
     *  \param
     *      channel The trace channel this message is associated with.
     *  \param
     *      level The trace level for this message. See Levels.hxx.
     *  \param
     *      modifiers A bit-field of message modifiers. See Modifiers.hxx.
     *  \param
     *      message A string containing the actual message body.
     *  \note
     *      You probably don't want to use this method. Instead use the channel's log
     *      method.
     */
    void logMessage(const Channel & channel, int16_t level, int16_t modifiers, const ipl::string & message) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Log a trace message.

     *      This method should probably be called by channels only. It creates a new trace
     *      message and forwards it to the frontend for further processing.
     *  \param
     *      channel The trace channel this message is associated with.
     *  \param
     *      level The trace level for this message. See Levels.hxx.
     *  \param
     *      modifiers A bit-field of message modifiers. See Modifiers.hxx.
     *  \param
     *      type of  message
     *  \param
     *      data buffer holding the message
     *  \param
     *      len length of message in bytes
     *  \note
     *      You probably don't want to use this method. Instead use the channel's log
     *      method.
     */
    void logMessage(const Channel & channel, int16_t level, int16_t modifiers, int16_t type, const void * data, size_t len ) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Log a trace message.

     *  \details
     *      This method should probably be called by channels only. It creates a new trace
     *      message and forwards it to the frontend for further processing.
     *  \param
     *      channel The trace channel this message is associated with.
     *  \param
     *      level The trace level for this message. See Levels.hxx.
     *  \param
     *      modifiers A bit-field of message modifiers. See Modifiers.hxx.
     *  \param
     *      data buffer holding the message
     *  \param
     *      take_ownership If true the data supplied will not be copied. Deletion
     *      takes place inside the tracing library. The data must have been
     *      allocated using ipl::new and must not be modified after this call.
     *  \note
     *      You probably don't want to use this method. Instead use the channel's log
     *      method.
     */
    void logMessage(const Channel & channel, int16_t level, int16_t modifiers, char * data, bool take_ownership) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Log a trace message.
     *  \details
     *      This method should probably be called by channels only. It creates a new trace
     *      message and forwards it to the frontend for further processing.
     *  \param
     *      channel The trace channel this message is associated with.
     *  \param
     *      level The trace level for this message. See Levels.hxx.
     *  \param
     *      modifiers A bit-field of message modifiers. See Modifiers.hxx.
     *  \param
     *      timestamp A custom timestamp, i.e. the trace core will not acquire its own
     *      timestamp when this message is processed.
     *  \param
     *      data buffer holding the message
     *  \param
     *      take_ownership If true the data supplied will not be copied. Deletion
     *      takes place inside the tracing library. The data must have been
     *      allocated using ipl::new and must not be modified after this call.
     *  \note
     *      You probably don't want to use this method. Instead use the channel's log
     *      method.
     */
    void logMessage(const Channel & channel, int16_t level, int16_t modifiers, int64_t timestamp, char * data, bool take_ownership) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Log a trace message.
     *  \details
     *      This method should probably be called by channels only. It creates a new trace
     *      message and forwards it to the frontend for further processing.
     *  \param
     *      channel The trace channel this message is associated with.
     *  \param
     *      level The trace level for this message. See Levels.hxx.
     *  \param
     *      modifiers A bit-field of message modifiers. See Modifiers.hxx.
     *  \param
     *      message A string containing the actual message body.
     *  \param
     *      attr A message attribute that contains a list of tags and objects, associated with message
     *  \note
     *      You probably don't want to use this method. Instead use the channel's log
     *      method.
     */
    void logMessage(const Channel & channel, int16_t level, int16_t modifiers, const ipl::string & message, MessageAttributes&& attr) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Log a trace message.
     *  \details
     *      This method should probably be called by channels only. It creates a new trace
     *      message and forwards it to the frontend for further processing.
     *  \param
     *      channel The trace channel this message is associated with.
     *  \param
     *      level The trace level for this message. See Levels.hxx.
     *  \param
     *      modifiers A bit-field of message modifiers. See Modifiers.hxx.
     *  \param
     *      data buffer holding the message
     *  \param
     *      take_ownership If true the data supplied will not be copied. Deletion
     *      takes place inside the tracing library. The data must have been
     *      allocated using ipl::new and must not be modified after this call.
     *  \param
     *      attr A message attribute that contains a list of tags and objects, associated with message
     *  \note
     *      You probably don't want to use this method. Instead use the channel's log
     *      method.
     */
    void logMessage(const Channel & channel, int16_t level, int16_t modifiers, char * data, bool take_ownership, MessageAttributes&& attr) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Synchronously write a log message to the emergency log.
     *
     *      The logMessage() call will not write the message supplied to the trace log
     *      immediately, but store it in a ring-buffer and return to the caller. The
     *      message is then processed and delivered to the backends (log sinks) by a
     *      separate thread.
     *
     *      In case of exceptional situations (e.g. right before your process dies)
     *      this may not be what you want. Instead this member function is provided
     *      which will synchronously write the message to a so-called emergency log
     *      and will return only after flushing the message -- at least from the
     *      framework and OS perspective. Someone else (e.g. a hard-disk) might
     *      perform additional buffering that is out of reach for us.
     *
     *      This function has no influence on execution of your program, so you can
     *      call this and continue working as if nothing happened. But you should
     *      reserve calling this function for exceptional reasons because it is
     *      considered more expensive than a normal logMessage() call.
     *
     *  \param
     *      message The message which should be written to the emergency log.
     */
    void emergencyLog(const ipl::string & message) IPL_NOEXCEPT override;

    //! \brief Trigger an emergency break to flush buffered messages.
    void emergencyBreak() IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Triggers trace core to flush all pending messages.
     *
     *  \param
     *      do_block Flag indicating if the operation shall be blocking.
     *  \param
     *      timeout_ms The duration in milliseconds where the operation is blocking.
     *      A value of 0 indicates no timeout.
     */
    void flushMessages(bool do_block, osal::TimeT timeout_ms = 1000) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Get the name of the client as supplied to the util::Util constructor.
     *  \return
     *      String containing the client name.
     */
    const ipl::string & getClientId() IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Check filter level at the core.

     *      This method is used to check if a specific message level
     *      on a certain channel within a thread's context would be filtered away.
     *  \param
     *      msg_level The message level to be checked.
     *  \param
     *      channel The trace channel this message is associated with.
     *  \return
     *      true if both the channel and the related thread have a lower or equal filter level
     *      setting than the message level.
     */
    bool isLevelEnabled(const int16_t msg_level, const Channel & channel) const IPL_NOEXCEPT override;

protected:
    /*!
     *  \brief
     *      Utility function for converting a channel name to a "path" through
     *      the channel tree. Actually this is only tokenizing channel names
     *      for now by splitting them at the underscore ('_') character.
     */
    ipl::vector<ipl::string> nameToPath(const ipl::string & name) IPL_NOEXCEPT;

    Frontend & m_frontend;
    Config & m_config;
    Channel m_root_channel;
    ThreadCache * m_cache;
    bool m_startedFrontend;
    ipl::map<int32_t, CallbackObject *> m_callback_objs;
    osal::Mutex m_channel_mutex;
    osal::Mutex m_callback_mutex;
    ipl::list<Channel *> m_dynamic_channels;
    //! TraceMe client channel
    IPL_TRACEME_DECLARE_SCOPE(Client);

    static Client * s_client_instance;
    static osal::AtomicCounter s_start_count;
    static bool s_enabled;

    //! \brief Creates channel entities for the already available channels upon startup.
    void setupChannels(const ChannelList::ChannelVector &channels) IPL_NOEXCEPT;
    //! \brief DEPRECATED! \deprecated
    void cleanupChannelTree(Channel *channel) IPL_NOEXCEPT;
    //! \brief Tokenizes the channel path name via '_' separator.
    ipl::vector<ipl::string> splitPathName(const ipl::string & name) const IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Create any needed internal channel nodes for a new channel with channel
     *      path and link with parent(s) and children accordingly.
     *
     *  \param
     *      parent The parent channel node of the new channel.
     *  \param
     *      path The list of tokenized channel names of the new channel path.
     *  \param
     *      pos The position of the tokenized channel name within \sa path to be handled.
     *  \param
     *      new_channel The new channel for which mising nodes shall be inserted.
     *  \return
     *      true when successful, otherwise false.
     */
    bool createMissingChannelNodes(Channel *parent,
            const ipl::vector<ipl::string> & path,
            size_t pos, Channel *new_channel) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Detaches the channel from its channel entity which gets disabled.
     *      Optionally also all children will be detached recursively, too.
     *
     *  \param
     *      channel The channel to be detached.
     *  \param
     *      recurse Indicaton if also all children shall be detached.
     */
    void detachEntityFromChannel(Channel *channel, bool recurse) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Attaches the channel to a channel entity.
     *      Optionally also all children of the channel will be attached recursively, too.
     *
     *  \param
     *      channel The channel to be attached.
     *  \param
     *      recurse Indicaton if also all children shall be attached.
     */
    bool attachEntityToChannel(Channel *channel, bool recurse) IPL_NOEXCEPT;

    //! \brief Enable a channel at the core
    bool enableChannel(Channel *channel) IPL_NOEXCEPT override;
    //! \brief Disable a channel at the core
    bool disableChannel(Channel *channel) IPL_NOEXCEPT override;
    //! \brief Change the filter level of a channel at the core
    bool changeChannelFilterLevel(Channel *channel, int16_t level) IPL_NOEXCEPT override;

    /*!
     *  \brief
     *      Register a function as callback.
     *  \param
     *      name A unique name for this callback.
     *  \param
     *      func The function that should get executed when the callback is issued.
     *  \return
     *      The ID of the registered callback, or -1 if registration failed.
     */
    int32_t registerCallbackIntern(const ipl::string & name, CallbackFunc func) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Register a callback object.
     *  \param
     *      name A unique name for this callback.
     *  \param
     *      obj The object implementing the interface as declared in CallbackObject.hxx.
     *  \return
     *      The ID of the registered callback, or -1 if registration failed.
     */
    int32_t registerCallbackIntern(const ipl::string & name, CallbackObject * obj) IPL_NOEXCEPT;

    /*!
     *  \brief
     *      Unregister a callback.
     *  \param
     *      callback_id The callback ID.
     *  \return
     *      true if unregistration was successful.
     */
    bool unregisterCallbackIntern(int32_t callback_id) IPL_NOEXCEPT;

    //! \brief Get the client thread cache.
    IThreadCache * getThreadCache() IPL_NOEXCEPT;

    private:
    friend class TraceServer;
    friend class LogPrinter;
    friend class Channel;
};

}

#endif /* TRACING_CLIENT_HXX */

