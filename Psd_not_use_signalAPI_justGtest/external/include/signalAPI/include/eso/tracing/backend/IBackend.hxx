/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IBACKEND_HXX
#define TRACING_IBACKEND_HXX

#include <common/types/string.hxx>
#include <common/tracing/Levels.hxx>
#include <tracing/message/Message.hxx>
#include <tracing/message/IMessageFilter.hxx>
#include <tracing/entity/EntityType.hxx>
#include <tracing/backend/IBackendListener.hxx>
#include <tracing/filetransfer/FileTransfer.hxx>
#include <tracing/backend/PluginFactories.hxx>
#include <tracing/util/Common.hxx>

namespace osal
{
class Path;
}

namespace tracing
{

class IEntity;
class EntityURI;

/*!
 *  \brief
 *      Interface class which is implemented by all trace backends.

 *      A backend is simply speaking a log sink. All trace messages created and
 *      received by the trace core get forwarded to all backends connected to the
 *      core. Additionally a backend receives notifications about the trace core's
 *      model, which consists of entities (and their relationship to each other).
 *
 *      You can implement your own backends if none of the supplied backends suits
 *      your needs by following these simple steps:
 *
 *      -# Create a class and derive from IBackend.
 *      -# Implement at least the pure virtual functions declared in this class.
 *      -# Implement the static functions declared in this class.
 *      -# In a source file, include your backend header file and BackendFactory.hxx and:
 *          - Declare an instance of BackendFactory, filling in the addresses of the
 *            static methods of your backend.
 *          - Provide a function with C linkage that returns the address of the struct.
 *      -# Compile this into a shared library.
 *      -# In the framework's configuration file specify the name of your backend to
 *         use for tracing and specify the directory where your shared library is
 *         placed.
 *
 *      A sample is provided for this purpose, briefly demonstrating how to use
 *      the BackendFactory struct.
 */
class IBackend
{
public:
    //! \brief The backend requires decoded trace messages.
    //! This is currently ignored which means each backend needs to decode messages itself.
    static const int32_t FLAGS_DECODE_MESSAGE = 1 << 0;
    //! \brief The backend wants to receive file transfer related messages.
    static const int32_t FLAGS_FILE_TRANSFER  = 1 << 1;
    //! \brief The backend reacts on filter level changes for trace entities.
    //! If this flag is not set, the backend's entity levels will be determined from
    //! the tracing configuration and never changed during runtime.
    static const int32_t FLAGS_ADJUST_TO_CHANGE_LEVEL = 1 << 2;
    //! \brief The backend supports processing of bulked log data messages.
    //! \sa logBulk()
    static const int32_t FLAGS_ACCEPT_BULK_LOG_DATA = 1 << 3;
    //! \brief The backend supports processing of bulked create entity messages.
    //! \sa createEntityBulk()
    static const int32_t FLAGS_ACCEPT_BULK_CREATE_ENTITY = 1 << 4;
    //! \brief The backend supports processing of bulked change level messages.
    //! \sa changeFilterLevelBulk()
    static const int32_t FLAGS_ACCEPT_BULK_CHANGE_LEVEL = 1 << 5;
    //! \brief The backend overrides backendFilterLevel(). If this flag is not set,
    //! the backend's method might never be called for optimization reasons.
    static const int32_t FLAGS_CUSTOM_BACKEND_FILTER_LEVEL_SETUP = 1 << 6;
    //! \brief The backend must be connected at the core before flush operations
    //! succeed.
    static const int32_t FLAGS_FLUSH_WAIT = 1 << 7;
    //! \brief The backend traffic is recorded via tapping
    static const int32_t FLAGS_BACKEND_TAPPING_SOURCE = 1 << 8;
    //! \brief The backend is used to record traffic of another tapping Backend
    static const int32_t FLAGS_BACKEND_TAPPING_SINK = 1 << 9;
    //! The backend shall not be notified about disabling entities.
    static const int32_t FLAGS_IGNORE_DISABLE_ENTITY = 1 << 10;
public:
    /*!
     *  \brief
     *      Default constructor.
     */
    IBackend() :
        m_bid(-1),
        m_tapping(false),
        m_flags(FLAGS_DECODE_MESSAGE|FLAGS_BACKEND_TAPPING_SOURCE),
        m_listener(nullptr),
        m_message_filter(nullptr),
        m_message_filter_destroy_fkt(nullptr)
    {
        for (int16_t i = 0; i < EntityType::LAST_ENTITY; ++i)
        {
            m_default_levels[i] = Levels::LevelNONE;
        }
    }

    //! \brief Copy Constructor, disabled.
    IBackend(const IBackend& other)=delete;
    //! \brief Move Constructor, disabled.
    IBackend(const IBackend&& other)=delete;
    //! \brief Assignment operator, disabled.
    IBackend& operator=(const IBackend& other)=delete;
    //! \brief Move assignment operator, disabled.
    IBackend& operator=(const IBackend&& other)=delete;

    /*!
     *  \brief
     *      Virtual destructor.
     */
    virtual ~IBackend()
    {
        if (m_message_filter && m_message_filter_destroy_fkt)
            m_message_filter_destroy_fkt(m_message_filter);
    }

    /*************** Start of Backend factory functions interface ***************/

    /*!
     *  \brief
     *      Returns a C string containing the name of the backend.
     *
     *      If you derive from this interface and implement your own backend you
     *      are expected to return a C string containing a unique name for your
     *      backend. This string will be compared with entries found in the config
     *      file, to decide which backends to instantiate. The config file entry
     *      relevant is named "backends" in namespace "ESOL_FW_TRACING".
     *
     *  \return
     *      C-style string with backend's name.
     */
    static const char * getBackendName() { return nullptr; }

    /*!
     *  \brief
     *      Returns the backend interface version number.
     *
     *      This is not yet checked, so you can return 0 in your own backends for
     *      the moment, but this may change in the future. The current version
     *      number will be defined in this header when this feature is used.
     *
     *      Future versions of the tracing module may refuse to work with backends
     *      that return version numbers too low.
     *
     *  \return
     *      Version number of backend interface.
     */
    static int32_t getBackendVersion() { return 0; }

    /*!
     *  \brief
     *      Creates a new backend.
     *
     *      When implementing your own backends you are expected to implement this
     *      function in a way, such that calling it will create a new backend of
     *      the type you declared (and which derives itself from this interface
     *      class) and return a pointer to an object of your backend class or NULL
     *      if construction failed. Your backend will not be used by the trace
     *      core in the latter case.
     *
     *  \return
     *      A pointer to the newly created backend.
     */
    static IBackend * create() { return nullptr; }

    /*!
     *  \brief
     *      Destroys a backend again.
     *
     *      This is the counter-part to create(), it will be called when shutting
     *      down the trace core. You can implement this just like shown here, but
     *      possibly you want to do some other cleanup work in your backend first.
     *      The pointer provided as parameter is the one received from create().
     *
     *  \param
     *      backend A pointer to a backend object.
     */
    static void destroy(IBackend * backend) { delete backend; }

    /*************** End of Backend factory functions interface *****************/

    /*************** Start of backend interface *********************************/

    /*!
     *  \brief
     *      Initializes the backend.
     *
     *      This is the initialization function of a backend. It gets called after
     *      successfully constructing a new backend object. Here you are expected
     *      to setup everything your backend needs to work correctly, e.g. open a
     *      file or get some other resources etc.
     *
     *      You will be supplied a unique backend id which you must store in
     *      m_bid. Also you will get a pointer to a IBackendListener instance
     *      which you should store in m_listener. These two values are required
     *      when trying to interact with the trace core, as your only entry point
     *      (from the backend's perspective) is the backend listener supplied here
     *      which expects your unique id as one of the parameters in each of its
     *      interface functions.
     *
     *      If you implement your own backend and write a custom init() function
     *      you may of course simply call IBackend::init() to set the m_bid and
     *      m_listener members.
     *
     *      If initialization of your backend fails for whatever reason you can't
     *      notify the trace core here. Instead you should return "false" as soon
     *      as the connect() function of your backend gets called.
     *
     *  \param
     *      bid The id assigned to this backend by the trace core.
     *
     *  \param
     *      listener An instance of a backend listener, which the backend may use
     *      to interact with the trace core. \sa IBackendListener
     */
    virtual void init(int16_t bid, IBackendListener * listener)
    {
        m_bid = bid;
        m_listener = listener;

        initFlags();

        for (int16_t i = 0; i < EntityType::LAST_ENTITY; ++i)
        {
            m_default_levels[i] = m_listener->getConfigDefaultFilterLevel(m_bid, i);
        }
    }

    /*!
     *  \brief
     *      Asynchronous notification of registration errors.
     *      If an error occurs after calling registerBackend() at the frontend
     *      interface and before init() of your backend was called, you should
     *      implement this method and clean up any resources allocated by the
     *      backend. Maybe you even want to call the backend's destructor from
     *      this method if you can't reuse this backend instance.
     */
    virtual void registrationError()
    {
        /* nop */
    }

    /*!
     *  \brief
     *      Shuts down the backend.
     *
     *      This will be called before your backend's destroy() function is called.
     *      So you should probably release any resources your backend uses here
     *      already.
     */
    virtual void exit() = 0;

    /*!
     *  \brief
     *      Return the backend's name.
     *
     *      This should return the name of your backend, but as a IPL string.
     *      You may want to just call getBackendName() in your implementation of
     *      this method.
     *
     *  \return
     *      C++ string with the backend's name.
     */
    virtual const ipl::string & getName() = 0;

    /*!
     *  \brief
     *      Connects the backend to the trace core.
     *
     *      This will be called after init() has been called on the backend. There
     *      will be no notifications about entity changes or log messages before
     *      this call has happened.
     *
     *      If your backend succeeded in initializing itself and is able to process
     *      notifications you must return true here. Otherwise your backend will be
     *      removed from the trace core's list of backends and will receive no
     *      further calls except exit() and destroy().
     *
     *  \return
     *      Return true if your backend is working correctly.
     */
    virtual bool connect() = 0;

    /*!
     *  \brief
     *      Disconnects the backend from the trace core.
     *
     *      This will usually be called just before exit() is called on a backend.
     *      After this call a backend will receive no notifications of entity
     *      changes or log messages.
     *
     *      Note that it is possible that connect() will be called again on the
     *      backend after it was disconnected. Your backend should be able to
     *      handle this situation and possibly release required resources only in
     *      the implementation of the exit() method.
     */
    virtual void disconnect() = 0;

    /*!
     *  \brief
     *      Disconnect method for exceptional circumstances.
     *
     *      This will be called if your backend is blocking the trace core
     *      worker's watchdog for too long (depending on configuration).
     *      Release any resources here, don't acquire new ones and prepare for
     *      exit().
     */
    virtual void forceDisconnect()
    {
        disconnect();
    }

    /*!
     *  \brief
     *      Queries a backend's filter level for an entity.
     *
     *      This will be called by the trace core for each new entity created.
     *      A backend can then specify the filter level for this entity to the
     *      core which will be taken into account when creating new log messages.
     *
     *      You may want to use the IBackendListener::getConfigFilterLevel()
     *      interface to determine the filter level in your implementation of
     *      this method. If you don't care, return LevelNONE so a default level
     *      will be assigned to the entity.
     *
     *      You should NOT return a hard-coded value of LevelTRACE for each
     *      entity created here. If this is what you want then specify the
     *      default level in the configuration file instead.
     *
     *      Note: This method will only be called if the backend's flags
     *      contain FLAGS_CUSTOM_BACKEND_FILTER_LEVEL_SETUP.
     *
     *  \param
     *      entity The new entity whose filter level should be queried.
     *
     *  \return
     *      A filter level as specified in Levels.hxx.
     */
    virtual int16_t backendFilterLevel(const IEntity & entity)
    {
        int16_t level = Levels::LevelNONE;
        if (m_listener)
        {
            level = m_listener->getConfigFilterLevel(m_bid, entity);
        }
        return level;
    }

    /*!
     *  \brief
     *      Queries a backend's default filter level for an entity type.
     *
     *      This will be called by the trace core for newly created entities
     *      that don't match any criteria specified in the configuration file
     *      or anywhere else.
     *
     *      This is a default implementation used by all built-in backends.
     *
     *  \param
     *      type The type of entity as specified in EntityType.hxx
     *
     *  \return
     *      A filter level as specified in Levels.hxx
     */
    virtual int16_t backendDefaultFilterLevel(int16_t type)
    {
        return m_default_levels[type];
    }

    /*!
     *  \brief
     *      Notifies the backend about creation of a new entity.
     *
     *  \param
     *      entity The newly created entity. \sa IEntity
     *
     *  \return
     *      Return true if you acknowledge the creation. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual bool createEntity(const IEntity & entity)
    {
        return true;
    }

    /*!
     *  \brief
     *      Notifies the backend about creation of multiple new entities.
     *
     *      This is basically the same as createEntity() except the caller
     *      supplies multiple entities at once.
     *
     *      Note: this will only be called on a backend if it returns the flag
     *      FLAGS_ACCEPT_BULK_CREATE_ENTITY when getFlags() is called.
     *
     *  \param
     *      entities The entities that were created. \sa IEntity
     *
     *  \return
     *      Return true if you acknowledge the creations. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual bool createEntityBulk(const ipl::vector<const IEntity *> & entities)
    {
        return true;
    }

    /*!
     *  \brief
     *      Notifies the backend about a changed filter level on some entity.
     *
     *  \param
     *      uri The URI of the entity whose filter level was changed.
     *
     *  \param
     *      level The new filter level of the entity as specified in Levels.hxx.
     *
     *  \return
     *      Return true if you acknowledge the level change. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual bool changeFilterLevel(const EntityURI & uri, int16_t level)
    {
        return true;
    }

    /*!
     *  \brief
     *      Notifies the backend about filter level changes on multiple entities.
     *
     *      This is basically the same as changeFilterLevel() except the caller
     *      supplies multiple changes at once.
     *
     *      Note: this will only be called on a backend if it returns the flag
     *      FLAGS_ACCEPT_BULK_CHANGE_LEVEL when getFlags() is called.
     *
     *  \param
     *      changes A vector of pairs with URIs and their corresponding new
     *      trace level.
     *
     *  \return
     *      Return true if you acknowledge the level changes. If false is
     *      returned here, your backend will be disconnected from the trace core.
     */
    virtual bool changeFilterLevelBulk(const ipl::vector<ipl::pair<EntityURI, int16_t> > & changes)
    {
        return true;
    }

    /*!
     *  \brief
     *      Logs a trace message.
     *
     *      This method will be called by the trace core when a new log message
     *      was created and made its way through the filtering mechanism inside
     *      the core. Do with the message as you like, e.g. extract the timestamp
     *      and the message string and print it, maybe formatting it into some
     *      other representation, etc.
     *
     *      The message supplied to the backend is contained in a shared pointer,
     *      so its content is valid as long as you hold on to this pointer even
     *      if the trace core itself no longer has any references to the message
     *      contained in the pointer.
     *
     *      PLEASE release the pointer if you no longer need it, otherwise your
     *      backend might cause lots of memory usage.
     *
     *  \param
     *      msg A shared pointer containing a message as specified in Message.hxx.
     *
     *  \return
     *      Return true if you acknowledge the log message. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual bool log(MessagePtr msg) = 0;

    /*!
     *  \brief
     *    Logs multiple trace messages.
     *
     *      This is basically the same as log(MessagePtr msg) but instead of a
     *      single trace message the backend will be supplied a vector of
     *      multiple messages.
     *
     *      Note: this will only be called on a backend if it returns the flag
     *      FLAGS_ACCEPT_BULK_LOG_DATA when getFlags() is called.
     *
     *  \param
     *      msgs A vector containing shared pointers containing a message as
     *      specified in Message.hxx.
     *
     *  \return
     *      Return true if you acknowledge the log message. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual MessagePtr logBulk(const ipl::vector<MessagePtr> & msgs)
    {
        return nullptr;
    }

    /*!
     *  \brief
     *      Notifies the backend about dropped messages.
     *
     *      Sometimes the number of trace messages created is so large that they
     *      can't be reasonably stored in the trace core anymore. In this case
     *      messages in the core's ring buffer will be overwritten and all
     *      connected backends will get notified about the number of messages lost
     *      via this function.
     *
     *  \param
     *      num The number of messages dropped in the trace core.
     *
     *  \return
     *      Return true if you acknowledge the message. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual bool droppedMessages(int32_t num) = 0;


    /*!
     *  \brief
     *      Notifies the backend about a new timezone.
     *
     *      There may be different time sources in a system which may even
     *      advance with different speed. This method is called when a new
     *      timezone is registered at the trace core before the first
     *      updateTimeZone() call occurs.
     *
     *  \param
     *      id The unique ID of the timezone.
     *
     *  \param
     *      resolution Time resolution in milliseconds.
     *
     *  \param
     *      name Unique timezone name.
     *
     *  \return
     *      Return true if you acknowledge the message. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual bool registerTimeZone(int32_t id, int32_t resolution, const ipl::string & name)
    {
        return true;
    }

    /*!
     *  \brief
     *      Updates a timezone's current time.
     *
     *  \param
     *      id The unique ID of the timezone.
     *
     *  \param
     *      timezone_time The current time of the specified timezone.
     *
     *  \param
     *      core_time Trace core time when timezone_time was determined.
     *
     *  \return
     *      Return true if you acknowledge the message. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual bool updateTimeZone(int32_t id, int64_t timezone_time, int64_t core_time)
    {
        return true;
    }

    /*!
     *  \brief
     *      Creates a sync marker.
     *
     *      Sync markers are special messages which will be used for
     *      synchronizing reads on a binary trace stream, especially if the
     *      stream is not guaranteed to be complete. Backends creating binary
     *      streams should encode the parameters and place them inside the
     *      stream whenever this method is called.
     *  \param
     *      tag A constant byte sequence.
     *
     *  \param
     *      sequence_number Strict monotonic increasing counter starting at 0.
     *
     *  \param
     *      core_time Trace core time when the sync marker was created.
     *
     *  \return
     *      Return true if you acknowledge the message. If false is returned
     *      here, your backend will be disconnected from the trace core.
     */
    virtual bool syncMarker(int8_t tag[3], int32_t sequence_number, int64_t core_time)
    {
        return true;
    }

    /*!
     *  \brief
     *      Send a file request message.
     *
     *  \note
     *      Implementing this makes only sense for interactive backends.
     *
     *  \param
     *      id The ID of the file request.
     *
     *  \param
     *      path Path of the file requested.
     *
     *  \param
     *      operation Type of file request:
     *      \li 0 request file download
     *      \li 1 request file upload
     *      \li 2 request file status
     *
     */
    virtual void fileRequest(int32_t id, const osal::Path & path, int8_t operation)
    {
        return;
    }

    /*!
     *  \brief
     *      Send a file status message.
     *
     *  \note
     *      Implementing this makes only sense for interactive backends.
     *
     *  \param
     *      status A file status object containing information about the
     *      requested file. \sa FileStatusFlags
     */
    virtual void fileStatus(const FileStatus & status)
    {
        return;
    }

    /*!
     *  \brief
     *      Sends a block of file data.
     *
     *  \note
     *      This might be useful for non-interactive backends for embedding
     *      file data in a binary trace stream.
     *
     *  \param
     *      id The file transfer ID. This ID is valid until the file transfer
     *      is finished, indicated by flags.
     *
     *  \param
     *      block_no Block number of transferred file.
     *
     *  \param
     *      flags Flags indicating type of file transfer and block type.
     *      \sa FileTransferFlags
     *
     *  \param
     *      data Points to the current block's data.
     *
     *  \param
     *      len Number of bytes contained in block.
     */
    virtual void fileTransfer(int32_t id, int32_t block_no, int32_t flags, void * data, size_t len)
    {
        return;
    }

    /*!
     *  \brief
     *      Interface for signalling backends exceptional conditions.
     *
     *      This can be called via Frontend::emergencyBreak() and should flush
     *      all available messages as fast as possible. Most backends don't
     *      implement this because they don't store log messages themselves but
     *      the FileBackend for example may call an explicit flush() on its
     *      file in this case. The EmergencyRecorderBackend will dump its ring
     *      buffer to some defined location. \sa Frontend::emergencyBreak()
     */
    virtual void handleBreak()
    {
        /* nop */
    }

    /*!
     *  \brief
     *      Get flags indicating supported backend capabilities.
     *
     *  \return
     *      An or'ed combination of IBackend::FLAGS_* constants depending on
     *      the implementation's capabilities.
     */
    virtual int32_t getFlags() const
    {
        return m_flags;
    }

    /*!
     *  \brief
     *      Set the tapping flag via API.
     *
     *      It must be set before backend initialization is done.
     *      When set the flag FLAGS_BACKEND_TAPPING_SOURCE will be enabled.
     *
     */
    void enableTapping()
    {
        m_tapping = true;
    }

    /*!
     *  \brief
     *      Updates the backend specific message filter.
     *  \param
     *      filter The new message filter instance. A valid filter
     *      must have a valid destroy method.
     *  \return
     *      true For backends always true as of now
     */
    bool setMessageFilter(IMessageFilter * filter)
    {
        if (m_message_filter && m_message_filter_destroy_fkt)
            m_message_filter_destroy_fkt(m_message_filter);

        m_message_filter = filter;
        if (filter == nullptr)
            m_message_filter_destroy_fkt = nullptr;
        else
            m_message_filter_destroy_fkt = filter->destroy;

        return true;
    }
    /*!
     *  \brief
     *      Returns the optional backend message filter.
     *  \return
     *      The optional message filter instance or NULL
     */
    IMessageFilter * getMessageFilter() const {return m_message_filter;}
    /*************** End of backend interface ***********************************/

    //! \brief Returns the unique backend id.
    int16_t getId()
    {
        return m_bid;
    }

protected:
    //! The unique backend id which will be supplied by the core through the init() call.
    int16_t m_bid;
    //! Flag to enable backend as tapping source. It is evaluated during initialization only.
    bool m_tapping;
    //! Flags indicating backend capabilities.
    uint32_t m_flags;
    //! The backend's name.
    ipl::string m_name;
    //! The backend listener providing config reading and other functionality, supplied
    //! by the core through the init() call.
    IBackendListener * m_listener;
    //! Default levels for entities if not overridden by more specific config entries.
    int16_t m_default_levels[EntityType::LAST_ENTITY];
    //! The backend individual message filter functor
    IMessageFilter * m_message_filter;
    //! The destroy function for the backend message filter
    MessageFilterDestroy m_message_filter_destroy_fkt;

    //! \brief Initialize the backend capability flags.
    virtual void initFlags()
    {
        if (m_bid >= 0 && m_listener != nullptr)
        {
            m_flags = (int32_t)m_listener->initConfiguredBackendFlags(m_bid, m_flags);
        }
        if (m_tapping)
            m_flags |= FLAGS_BACKEND_TAPPING_SOURCE;
    }
};

}

#endif /* TRACING_IBACKEND_HXX */

