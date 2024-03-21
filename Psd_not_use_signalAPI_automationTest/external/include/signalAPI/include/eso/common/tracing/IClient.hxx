/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_ICLIENT_HXX
#define TRACING_ICLIENT_HXX

#include <ipl_config.h>
#include <iplbase/exceptions.hxx>
#include <common/iplcommon_dso.h>
#include <common/stdint.h>
#include <common/types/string.hxx>
#include <common/tracing/IClientHelper.hxx>
#include <common/tracing/MessageAttributes.hxx>
#include <osal/Time.hxx>
#include <stdlib.h>

namespace tracing
{

class Channel;
class CallbackObject;

extern IPLCOMMON_EXPORT IClientHelper * client_helper;

/*!
 *  \brief
 *      Interface class which is implemented by all trace clients.

 *      The client is necessary when using the high-level tracing API. Usually you
 *      create an instance of this class and call its init()
 *      method. Calling init() more than once should be ok, but you need to remember
 *      calling exit() the same number of times for shutting down correctly.
 */
class IPLCOMMON_EXPORT IClient
{
public:
    //! \brief Virtual destructor.
    virtual ~IClient() IPL_NOEXCEPT {/* nop */}

    //! \brief Describes the signature that user callback functions must have.
    typedef void (*CallbackFunc)(int32_t, void * const, size_t);

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
     *      type The type of the trace core.
     *  \param
     *      readConfig Use the configuration files to setup trace core. If false
     *      then no configuration file is used
     *  \return
     *      true if tracing is enabled, false if disabled
     */
    static bool init(const ipl::string & name,
                     const ipl::string & type = "client",
                     bool readConfig = true) IPL_NOEXCEPT
    {
        return client_helper->init(name, type, readConfig);
    }

    /*!
     *  \brief
     *      (Possibly) uninitialize the tracing system.
     *  \note
     *      If init() was called more than once, you need to call exit the same
     *      number of times for really shutting down the trace system.
     */
    static void exit() IPL_NOEXCEPT
    {
        client_helper->exit();
    }

    //! \brief Singleton-like construction method for the Client.
    static IClient * getTraceClient() IPL_NOEXCEPT
    {
        return client_helper->getClient();
    }

    //! \brief Set the static client instance
    static void setClient(IClient * client) IPL_NOEXCEPT
    {
        s_client = client;
    }

    /*!
     *  \brief
     *      Register a thread at the trace core.
     *
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
    virtual void registerThread(const ipl::string & name) IPL_NOEXCEPT = 0;

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
    virtual void unregisterThread() IPL_NOEXCEPT = 0;

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
    virtual int32_t registerCallback(const ipl::string & name,
                                     CallbackFunc func) IPL_NOEXCEPT = 0;

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
    virtual int32_t registerCallback(const ipl::string & name,
                                     CallbackObject * obj) IPL_NOEXCEPT = 0;

    /*!
     *  \brief
     *      Unregister a callback.
     *  \param
     *      callback_id The ID as returned from registerCallback().
     *  \return
     *      true if unregistration was successful.
     */
    virtual bool unregisterCallback(int32_t callback_id) IPL_NOEXCEPT = 0;

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
    virtual int32_t registerTimeZone(const ipl::string & name,
                                     int32_t resolution = 1) IPL_NOEXCEPT = 0;

    //! \brief Update a time zone's current time.
    virtual void updateTimeZone(int32_t id, int64_t current_time) IPL_NOEXCEPT = 0;

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
    virtual void emergencyLog(const ipl::string & message) IPL_NOEXCEPT = 0;

    /*!
     *    \brief
     *        Trigger an emergency break at the trace core.
     *
     *        This can be used to notify the core of some exceptional
     *        state. It will flush the currently stored trace messages to
     *        all backends and notify all connected backends about the
     *        break.
     */
    virtual void emergencyBreak() IPL_NOEXCEPT = 0;

    //! \brief Enable a channel at the core
    virtual bool enableChannel(Channel *channel) IPL_NOEXCEPT = 0;
    //! \brief Disable a channel at the core
    virtual bool disableChannel(Channel *channel) IPL_NOEXCEPT = 0;
    //! \brief Change the filter level of a channel at the core
    virtual bool changeChannelFilterLevel(Channel *channel, int16_t level) IPL_NOEXCEPT = 0;

    //! \brief Log a trace message with given signature
    virtual void logMessage(const Channel & channel, int16_t level,
                            int16_t modifiers, const ipl::string & message) IPL_NOEXCEPT = 0;
    //! \brief Log a trace message with given signature
    virtual void logMessage(const Channel & channel, int16_t level,
                            int16_t modifiers, int16_t type, const void * data,
                            size_t len ) IPL_NOEXCEPT = 0;
    //! \brief Log a trace message with given signature
    virtual void logMessage(const Channel & channel, int16_t level,
                            int16_t modifiers, const ipl::string & message,
                            MessageAttributes&& attr) IPL_NOEXCEPT = 0;
    //! \brief Log a trace message with given signature
    virtual void logMessage(const Channel & channel, int16_t level,
                            int16_t modifiers, char * data,
                            bool take_ownership) IPL_NOEXCEPT = 0;
    //! \brief Log a trace message with given signature
    virtual void logMessage(const Channel & channel, int16_t level,
                            int16_t modifiers, char * data,
                            bool take_ownership,
                            MessageAttributes&& attr) IPL_NOEXCEPT = 0;
    //! \brief Log a trace message with given signature
    virtual void logMessage(const Channel & channel, int16_t level,
                            int16_t modifiers, int64_t timestamp,
                            char * data, bool take_ownership) IPL_NOEXCEPT = 0;

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
    virtual void flushMessages(bool do_block, osal::TimeT timeout_ms = 1000) IPL_NOEXCEPT = 0;

    /*!
     *  \brief
     *      Get the name of the client as supplied to the util::Util constructor.
     *  \return
     *      String containing the client name.
     */
    virtual const ipl::string & getClientId() IPL_NOEXCEPT = 0;

    /*!
     *    \brief
     *        Check filter level at the core.
     *
     *      This method is used to check if a specific message level
     *      on a certain channel within a thread's context would be filtered away.
     */
    virtual bool isLevelEnabled(const int16_t msg_level, const Channel & channel) const IPL_NOEXCEPT = 0;

protected:
    //! the static client instance
    static IClient * s_client;
};

}

#endif /* TRACING_ICLIENT_HXX */

