/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IBACKENDLISTENER_HXX
#define TRACING_IBACKENDLISTENER_HXX

#include <tracing/tracing_dso.h>
#include <common/types/string.hxx>
#include <common/types/vector.hxx>
#include <stdlib.h>
#include <tracing/entity/EntityURI.hxx>

namespace osal
{
class Path;
}

namespace util
{
namespace config
{
class Value;
}
}

namespace tracing
{

class IEntity;
class EntityURI;
class Message;
class IMessageFormatter;
class IFileOperationFinishedCallback;
class IEventListener;
struct FileStatus;

/*!
 *    \brief
 *        Interface class providing interaction with the trace core for backends.

 *        This class declares all methods that are available for backends to call
 *        into the trace core. A pointer to an IBackendListener is supplied to
 *        each backend instance upon calling IBackend::init(), so the backend can
 *        actually use the methods provided here.
 *        See the method's documentation for what they do, most probably you want
 *        to know about the getConfig*() methods for reading backend-specific
 *        configuration entries.
 *        Furthermore you should have a look at the IBackend documentation and
 *        the sample backend implementation if you want to write your own
 *        backends.
 */
class TRACINGIMPL_EXPORT IBackendListener
{
public:
    //! \brief Virtual default destructor.
    virtual ~IBackendListener() = default;

    /*!
     *    \brief
     *        Signal connection state of backend.
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     *    \param
     *        ok Resource acquisition (if any) was successful, backend can be used.
     *    \param
     *        retransmit_model Indication if trace core shall retransmit the entity model.
     */
    virtual void connected(int16_t bid, bool ok, bool retransmit_model = false) = 0;

    /*!
     *    \brief
     *        Signal disconnection of backend.
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     */
    virtual void disconnected(int16_t bid) = 0;

    /*!
     *    \brief
     *        Notify the trace core to change the filter level for some entity.
     *    \param
     *        uri The URI for the entity whose filter level should be changed.
     *    \param
     *        level The new filter level, as specified in Levels.hxx
     *    \return
     *        true if the entity exists and its level is scheduled for change.
     */
    virtual bool triggerRequestFilterLevel(const EntityURI & uri, int16_t level) = 0;

    /*!
     *    \brief
     *        Notify the trace core to change the filter level for some entity
     *        including all its children.
     *    \param
     *        uri The URI for the parent entity whose subtree filter levels
     *        should be changed.
     *    \param
     *        level The new filter level, as specified in Levels.hxx
     *    \return
     *        true if the entity exists and its level is scheduled for change.
     */
    virtual bool triggerRequestFilterLevelTree(const EntityURI & uri, int16_t level) = 0;

    /*!
     *    \brief
     *        Trigger execution of a trace callback.
     *    \param
     *        cbid The callback ID as returned from Frontend::createCallback().
     *    \param
     *        data The user data that should be delivered to the callback's code,
     *        may be NULL.
     *    \param
     *        len The length of data in bytes. May be 0 if data is NULL.
     *    \return
     *        true if the callback id exists and the callback is scheduled for
     *        execution.
     */
    virtual bool triggerExecuteCallback(int32_t cbid, const void * data, size_t len) = 0;

    /*!
     *    \brief
     *        Resolve an entity's URI to a name.
     *    \param
     *        uri The URI which should be resolved.
     *    \return
     *        A string containing the entity's name.
     */
    virtual const char * resolveName(const EntityURI & uri) const = 0;

    /*!
     *    \brief
     *        Resolve an entity's full path name.
     *    \param
     *        uri The URI which should be resolved.
     *    \param
     *        local_path Flag indicating if it is a local path.
     *    \return
     *        A string containing the full path name of the entity.
     */
    virtual const ipl::string resolvePath(const EntityURI & uri, bool local_path) const = 0;

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
    virtual const ipl::string resolveParentName(const EntityURI & uri, int16_t type) const = 0;

    /*!
     *    \brief
     *        Forward a message string to core for output to stderr.
     *    \param
     *        msg A message string to be written to stderr.
     */
    virtual void logMessage(const ipl::string & msg) const = 0;

    /*!
     *    \brief
     *        Get a string value from the configuration.
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     *    \param
     *        key The name of the configuration key.
     *    \param
     *        default_value The value to return, if the key is not found in the
     *        configuration.
     *    \return
     *        default_value if the key is not found in the configuration, a
     *        string as specified in the configuration otherwise.
     */
    virtual ipl::string getConfigString(int16_t bid, const ipl::string & key, const ipl::string & default_value = "") = 0;

    /*!
     *    \brief
     *        Get an integer value from the configuration.
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     *    \param
     *        key The name of the configuration key.
     *    \param
     *        default_value The value to return, if the key is not found in the
     *        configuration.
     *    \return
     *        default_value if the key is not found in the configuration, an
     *        integer as specified in the configuration otherwise.
     */
    virtual int32_t getConfigInteger(int16_t bid, const ipl::string & key, int32_t default_value = 0) = 0;

    /*!
     *    \brief
     *        Get a boolean value from the configuration.
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     *    \param
     *        key The name of the configuration key.
     *    \param
     *        default_value The value to return, if the key is not found in the
     *        configuration.
     *    \return
     *        default_value if the key is not found in the configuration, a
     *        boolean as specified in the configuration otherwise.
     */
    virtual bool getConfigBool(int16_t bid, const ipl::string & key, bool default_value = false) = 0;

    /*!
     *    \brief
     *        Get the filter level for a specific entity from the configuration.
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     *    \param
     *        entity The entity whose level should be queried.
     *    \return
     *        A filter level as specified in Levels.hxx (may be Levels::NONE).
     */
    virtual int16_t getConfigFilterLevel(int16_t bid, const IEntity & entity) = 0;

    /*!
     *    \brief
     *        Get the default filter level from the configuration.
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     *    \param
     *        type The entity type as specified in EntityType.hxx.
     *    \return
     *        A filter level as specified in Levels.hxx (may be Levels::NONE).
     */
    virtual int16_t getConfigDefaultFilterLevel(int16_t bid, int16_t type) = 0;

    /*!
     *    \brief
     *        Get the filter privacy flags for a specific channel entity from the configuration.
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     *    \param
     *        entity The entity whose level should be queried.
     *    \return
     *        The filter privacy flags, the value PRIV_FLAG_NONE \sa LogTag.hxx indicates invalid.
     */
    virtual uint32_t getConfigFilterPrivacyFlags(int16_t bid, const IEntity & entity) = 0;

    /*!
     *    \brief
     *        Check if filter attributes are configured for a backends entity.
     *    \param
     *        bid The backend id.
     *    \param
     *        entity The entity to be queried.
     *    \return
     *        true if filter attributes are configured.
     */
    virtual bool checkConfigFilterAttributes(int16_t bid, const IEntity & entity) const {return false;}

    /*!
     *  \brief
     *      Get a file name specified either by "fileName"
     *      or "outputDirectory", "useClientName", "logfileSuffix"
     *  \return
     *      File name
     */
    virtual ipl::string getConfigFileName(int16_t bid, const ipl::string &default_suffix) = 0;

    /*!
     *    \brief
     *      Get the backend's dictionary (if available) from the tracing
     *      configuration.
     *  \param
     *      bid The backend's id as provided when IBackend::init() was called.
     *  \return
     *      A dictionary containing additional configuration entries for the
     *      backend.
     */
    virtual const util::config::Value & getConfigDictionary(int16_t bid) = 0;

    /*!
     *    \brief
     *        Gets the maximum number of entities for this core instance.

     *        Each process using the tracing module has an embedded 'trace core',
     *        which is responsible for keeping track of entities (such as channels,
     *        threads, callbacks, etc.) and providing the glue between creation of
     *        trace messages, filtering them and forwarding them to a backend based
     *        on the filter levels associated with each entity. The maximum number
     *        of entities a core can manage, can be configured in the framework's
     *        configuration file. This method returns that number or the default
     *        value if it is not specified in the config file.
     *    \return
     *        The maximum number of entities.
     */
    virtual int32_t getCoreMaxEntities() = 0;

    /*!
     *    \brief
     *        Get the core id.

     *        This provides the name of the client instance, if set.
     *    \return
     *        A string with the client core name.
     */
    virtual const ipl::string & getCoreId() const = 0;

    /*!
     *    \brief
     *        Get the configured plugins directory.

     *        This provides the path of the tracing plugins directory.
     *    \return
     *        A string with the plugins directory path.
     */
    virtual const std::string & getPluginsDirectory() const = 0;

    /*!
     *    \brief
     *        Get global maximum size of packets in util::transport.
     *
     *        This value is used for setting the upper limit in util::transport
     *        instances for send and receive buffers. Note that a packet may
     *        consist of multiple 'messages', e.g. more than one LogData message
     *        or more than a single CreateEntity. Thus this value should be
     *        considerably larger than a single trace message, e.g. in the range
     *        of MB.
     *    \return
     *        Maximum configured size.
     */
    virtual size_t getMaxPacketSize() const = 0;

    /*!
     *    \brief
     *        Get maximum length of entity names.
     *
     *    \return
     *        Maximum number of bytes allowed for entity names.
     */
    virtual size_t getEntityNameLimit() const = 0;

    /*!
     *    \brief
     *        Decode a (user-defined) message.
     *    \param
     *        msg The message that should be decoded.
     *    \param
     *        decoded_message A string where the decoded message will be stored.
     *    \return
     *        true if the message was decoded successfully, false otherwise.
     *        decoded_message will not be altered in that case.
     */
    virtual bool decodeMessage(const Message & msg, ipl::string & decoded_message) = 0;

    /*!
     *    \brief
     *        Get a configured formatter instance by name.
     *    \param
     *        formatter_name The name of the formatter. This name must be found in
     *        the configuration file (tracing.json) otherwise the formatter won't
     *        be created.
     *    \return
     *        Pointer to an instance of a formatter. \sa IMessageFormatter NULL in
     *        case of error.
     */
    virtual IMessageFormatter * getFormatter(const ipl::string & formatter_name) const = 0;

    /*!
     *    \brief
     *        Request to quit the trace core.

     *        Call this only if you know what you are doing[tm]. After this call
     *        is issued tracing will no longer be possible in your process. Don't
     *        mix this up with disconnected(), which will only disable the
     *        backend from which it was called.
     */
    virtual void requestQuit() = 0;

    /*!
     *    \brief
     *        Get child entities of a specific type.
     *    \param
     *        parent The parent entity URI whose children shall be returned.
     *    \param
     *        type The type of entities that are requested. Only child entities
     *        of that type will be in the result.
     *    \return
     *        The children of the specified parent entity. An empty vector in
     *        case the entity has no children of the requested type.
     */
    virtual ipl::vector<const IEntity *> getChildEntities(const EntityURI & parent,
                                                          int16_t type) = 0;

    /*!
     *    \brief
     *       Request uploading a file to the trace core.
     *    \param
     *       path Storage path of the uploaded file.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the file transfer.
     *    \param
     *       backend_id The backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     */
    virtual int32_t transmitFile(const osal::Path & path,
                                 IFileOperationFinishedCallback * cb = nullptr,
                                 int16_t backend_id = -1) = 0;

    /*!
     *    \brief
     *       Request downloading a file from the trace core.
     *    \param
     *       path Storage path of the file to be downloaded.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the file transfer.
     *    \param
     *       backend_id The backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     */
    virtual int32_t requestFile(const osal::Path & path,
                                IFileOperationFinishedCallback * cb = nullptr,
                                int16_t backend_id = -1) = 0;

    /*!
     *    \brief
     *       Request sending a file status to the trace core.
     *    \param
     *       path Storage path of the file whose existence shall be signalled.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the file transfer.
     *    \param
     *       backend_id The backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     *    \note
     *       This method is intended to be used for notifying the trace core
     *       of file existence on a remote node.
     */
    virtual int32_t transmitFileStatus(const osal::Path & path,
                                       IFileOperationFinishedCallback * cb = nullptr,
                                       int16_t backend_id = -1) = 0;

    /*!
     *    \brief
     *       Request a file status from the trace core.
     *    \param
     *       path Storage path of the file whose status should be queried.
     *    \param
     *       cb An implementation of the IFileOperationFinishedCallback interface
     *       that will be notified upon completion of the file transfer.
     *    \param
     *       backend_id The backend that shall be associated with this transfer,
     *       -1 if it is for all backends handling file transfers.
     *    \return
     *       An ID that identifies this file transfer, -1 in case of errors. Note
     *       that the ID may be re-used when a file transfer was finished.
     */
    virtual int32_t requestFileStatus(const osal::Path & path,
                                      IFileOperationFinishedCallback * cb = nullptr,
                                      int16_t backend_id = -1) = 0;

    /*!
     *    \brief
     *        Trigger a file request, received by the backend, to be processed
     *        by the local trace core.
     *    \param
     *        id The ID of the current file request.
     *    \param
     *        path The path of the file or file status which is requested.
     *    \param
     *        operation The requested operation, one of:
     *        - OPERATION_TRANSFER_DOWNLOAD = 0
     *        - OPERATION_TRANSFER_UPLOAD = 1
     *        - OPERATION_STATUS = 2
     *    \param
     *        backend_id The backend's id as provided when IBackend::init() was called.
     */
    virtual void triggerFileRequest(int32_t id, const osal::Path & path,
                                    int8_t operation, int16_t backend_id) = 0;

    /*!
     *    \brief
     *        Trigger a file status.
     *    \param
     *        status A FileStatus reference received by the backend, to be
     *        processed by the trace core. \sa struct FileStatus.
     */
    virtual void triggerFileStatus(const FileStatus & status) = 0;

    /*!
     *    \brief
     *        Trigger a file transfer, received by the backend, to be processed
     *        by the local trace core.
     *    \param
     *        id The ID of the current file request.
     *    \param
     *        block_no The block number of the file that is currently transferred.
     *    \param
     *        flag File transfer flags, \sa struct FileTransferFlags.
     *    \param
     *        data Pointer to the memory of the data received by the backend.
     *    \param
     *        len Size of the memory pointed to by data.
     */
    virtual void triggerFileTransfer(int32_t id, int32_t block_no, int32_t flag, void * data, size_t len) = 0;

    /*!
     *    \brief
     *        Get an entity by its URI.
     *    \param
     *        uri The URI of the requested entity.
     *    \return
     *        A reference to the requested entity. If the entity does not exist
     *        a reference to an invalid entity will be returned. Check with
     *        getURI().isValid().
     */
    virtual const IEntity & getEntityByURI(const EntityURI & uri) const = 0;

    /*!
     *    \brief
     *        Get an entity by name and type.
     *    \param
     *        name The entity name, i.e. ignoring any parent prefixes.
     *    \param
     *        type The entity type to search for, \sa EntityType.
     *    \return
     *        A pointer to the entity if it exists. NULL if it does not exist
     *        or if an invalid type was provided.
     */
    virtual const IEntity * findEntity(const ipl::string & name, int16_t type) const = 0;

    /*!
     *    \brief
     *        Get an entity by path and type.
     *    \param
     *        path The path of the entity, i.e. this needs to contain all parent prefixes.
     *    \param
     *        type The entity type to search for, \sa EntityType.
     *    \param
     *        root_uri The URI of the root entity where searching should start. If
     *        not provided, the trace core will first find the root entity URI of
     *        the requested type and start searching from this parent. Otherwise
     *        only children of the entity identified by root_uri will be searched.
     *    \return
     *        A pointer to the entity if it exists. NULL if it does not exist
     *        or if an invalid type was provided.
     */
    virtual const IEntity * findEntityByPath(const ipl::string & path, int16_t type,
                                    const EntityURI & root_uri = EntityURI()) const = 0;

    /*!
     *    \brief
     *        Request a complete update of the entity model.
     *
     *        Usually every backend gets updates of the entity model as they
     *        happen. This method is intended for backends that do not handle
     *        each change in the trace model but need to get the current
     *        state of the complete model at some point during run-time. E.g.
     *        the Lazy* set of backends will only forward entity creation
     *        packets for channels that are actually in use by a trace
     *        message. It can be instructed however, to transmit the complete
     *        entity tree after a timer expires.
     *    \param
     *        backend_id the backend's id as provided when IBackend::init() was called.
     *    \note
     *        This is a potentially expensive operation. Depending on the size
     *        of the trace entity model (i.e. the number of channels created)
     *        the trace core may be blocked for a significant time while it
     *        updates the requesting backend with the current state of the model.
     */
    virtual void requestModelRetransmission(int16_t backend_id) = 0;

    /*!
     *    \brief
     *        Request the last time update of a timezone.
     *    \param
     *        name The name of the timezone.
     *    \param
     *        timezone_time Result parameter containing the last time update.
     *    \return
     *        True if the timezone was updated at least once, false otherwise or
     *        if the timezone does not exist. In case false is returned the value
     *        in timezone_time is unspecified.
     */
    virtual bool getLastTimeZoneUpdateByName(const ipl::string & name, int64_t & timezone_time) = 0;

    /*!
     *    \brief
     *        Trigger an emergency break in the trace core.
     *
     *        This can be used to notify the core of some exceptional
     *        state. It will signal the core worker thread which in
     *        turn will flush the currently stored trace messages to
     *        all backends and notify all connected backends about the
     *        break.
     */
    virtual void triggerEmergencyBreak() = 0;

    /*!
     *    \brief
     *        Check if an entity may be present in the tracing configuration.
     *
     *        This is an optimization that is useful for startup and entity
     *        level configuration. This method takes the first part of an
     *        entity name (i.e. the top-most parent) and checks if it has an
     *        entry in the backend's section in the tracing configuration file.
     *        In most cases this returns false, so further checks about the
     *        entity's level are not necessary.
     *
     *    \param
     *        bid The backend's id as provided when IBackend::init() was called.
     *    \param
     *        entity The entity to query for config presence.
     *    \return
     *        True if there is a top-most parent in the tracing configuration,
     *        false otherwise.
     *
     *    \note
     *        This works on the first level of entity names *only*. E.g. if
     *        there is a configuration entry for channels "A" and "B_C" in the
     *        tracing.json, this method will return:
     *          - true for "A_X_Y"
     *          - false for "B", "B_C", "B_C_Z"
     *        While this may seem counter-intuitive, an entry with a single
     *        entity name part ("A" in this example) is a very common case.
     */
    virtual bool checkConfigFilterPrefix(int16_t bid, const IEntity & entity) const = 0;

    /*!
     *    \brief
     *        Register a listener for "generic" trace core events.
     *    \param
     *        l An implementation of the IEventListener interface.
     *    \param
     *        event_name The event that the listener should be registered for.
     */
    virtual void registerEventListener(IEventListener * l, const ipl::string & event_name) = 0;

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
    virtual void unregisterEventListener(IEventListener * l, const ipl::string & event_name = ipl::string()) = 0;

    /*!
     *    \brief
     *        Notify the trace core to change the filter level for some entity's backend filter level.
     *    \param
     *        bid The requesting backend's ID.
     *    \param
     *        uri The URI for the entity whose filter level should be changed.
     *    \param
     *        level The new filter level, as specified in Levels.hxx
     *    \return
     *        true if the entity exists and its backend level is scheduled for change.
     */
    virtual bool triggerRequestBackendFilterLevel(int16_t bid, const EntityURI & uri, int16_t level) = 0;

    /*!
     *    \brief
     *        Notify the trace core to change the filter level for some entity's
     *        backend filter level including all its children.
     *    \param
     *        bid The requesting backend's ID.
     *    \param
     *        uri The URI for the parent entity whose subtree filter levels
     *        should be changed.
     *    \param
     *        level The new filter level, as specified in Levels.hxx
     *    \return
     *        true if the entity exists and its backend level is scheduled for change.
     */
    virtual bool triggerRequestBackendFilterLevelTree(int16_t bid, const EntityURI & uri, int16_t level) = 0;

    /*!
     *    \brief
     *        Check whether development mode is active.
     *
     *        This is determined at startup of the trace core and not expected
     *        to change during runtime. Depending on the platform this setting
     *        is derived from a hard-coded default, OS-specific property
     *        functionality, configuration entry in tracing.json, environment
     *        variable or a manually set flag at startup where each of these
     *        settings may override the previous one.
     *    \return
     *        true if development mode is active.
     */
    virtual bool getDevelopmentMode() const = 0;

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
    virtual bool getTraceOutputAuthorized() const = 0;

    /*!
     *    \brief
     *        Check whether authorization for controlling certain tracing features exists.
     *
     *    \return
     *        true if trace control functionality is enabled.
     */
    virtual bool getTraceControlAuthorized() const = 0;

    /*!
     *    \brief
     *        Register backend for usage of entity attachments.
     *    \param
     *        bid The requesting backend's ID.
     *    \return
     *        true if attachments can be used by the backend.
     */
    virtual bool registerAttachments(int16_t bid) = 0;

    /*!
     *    \brief
     *        Unregister backend for usage of entity attachments.
     *
     *        This will invalidate the stored pointers for this backend. Further
     *        calls to getAttachment() will return nullptr only.
     *    \param
     *        bid The requesting backend's ID.
     */
    virtual void unregisterAttachments(int16_t bid) = 0;

    /*!
     *    \brief
     *        Retrieve a previously stored attachment.
     *    \param
     *        bid The requesting backend's ID.
     *    \param
     *        uri The entity URI which was used for storing the attachment.
     *    \return
     *        The stored pointer or nullptr if not set.
     */
    virtual void * getAttachment(int16_t bid, const EntityURI & uri) const = 0;

    /*!
     *    \brief
     *        Store a pointer referencing an entity.
     *    \param
     *        bid The requesting backend's ID.
     *    \param
     *        uri The entity URI which shall be used for storing the attachment.
     *    \param
     *        attachment The pointer that shall be stored.
     */
    virtual void setAttachment(int16_t bid, const EntityURI & uri, void * attachment) = 0;

    /*!
     *    \brief
     *        Initialize the backend capability flags.
     *    \param
     *        bid The requesting backend's ID.
     *    \param
     *        supported_flags The supported flags as defined in IBackend.
     */
    virtual uint32_t initConfiguredBackendFlags(int16_t bid, uint32_t supported_flags) = 0;
};

}

#endif /* TRACING_IBACKENDLISTENER_HXX */

