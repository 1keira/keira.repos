/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_ITRANSPORT_HXX
#define UTIL_ITRANSPORT_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <util/transport/Buffer.hxx>
#include <util/transport/IMsgWriter.hxx>
#include <util/SharedPtr.hxx>
#include <util/NoOpPtr.hxx>
#include <util/transport/TransportErrors.hxx>
#include <util/transport/factory/IDisposable.hxx>
#include <util/transport/PeerInfoPtrForward.hxx>
#include <util/transport/ISelectable.hxx>

namespace util
{
namespace transport
{

/**
 * \brief
 *    Base interface for transport layer facilities

 *    Applications should be able to handle different types of
 *    communication transports uniformly. This abstract transport
 *    interface aims to provide an infrastructure to achieve this. The
 *    design principles of this mechanism are as follows:
 *
 *    - A transport facility is able to transport unstructured data
 *    (from it's POV).
 *
 *    - All operations are in blocking mode (send,receive,flush,...).
 *
 *    - Unnecessary copy operations are avoided by means of
 *    intelligent data buffer management. This includes buffer
 *    windows, a request/submit API supported by the IMsgWriter
 *    callback interface.
 *
 *    - The user of a transport facility is able to query a number of
 *    properties of the actual facility implementation to be able to
 *    assert certain guarantees or to adapt to them by means of e.g.
 *    added application level mechanisms.
 *
 *    - An instance of a transport always reflects a one to one
 *    communication link.  Multiple logical communication channels may
 *    be multiplexed by the application over the same transport. If
 *    parallel connections to different peers are needed then several
 *    transports are required. TCPSocket-like spawning behaviour
 *    cannot be realized with a transport alone. This is something
 *    that needs to be handled on a transport factory level.
 *
 *    This is merely an abstract interface to be handled by clients of
 *    transport facilities. Actual transport facilities need to
 *    implement this interface.
 *
 *    The lifecycle of a transport instance is reflected by
 *    transport::TransportState. A transport instance is usually
 *    obtained in a prepared but unopened state (i.e.  state NOT_OPEN,
 *    prepared means: addressing etc. is setup and the transport is
 *    ready for connection). Then by calling the virtual open function
 *    an open attempt is made. Once the transport is operational the
 *    OPEN state is entered. If ever a transport fails for some reason
 *    then it enters the DEAD state. From this state no other state
 *    can be reached any more. The transport is then rendered unusable
 *    and a new transport instance needs to be obtained.
 *
 *    This state does not necessarily map to a connection of some
 *    kind. All transports are treated equally whether connection
 *    oriented or not. Thus clients always have to operate the
 *    open/close API and monitor the transport lifecycle.
 *
 *    Serveral transport layers may be added by using an adapter
 *    structure i.e. a higher level transport layer implements
 *    ITransport and has an ITransport member where requests are
 *    forwarded to after additional processing has been done.
**/
class UTIL_EXPORT ITransport : public ISelectable
{
public: // subclasses / fwd. decl. / types

    //! \brief
    //! shared pointer that cares for correct lifetime of IMsgWriter
    //! objects turned to send()
    typedef util::SharedPtr<IMsgWriter> MsgWriterPtr;

    //! \brief
    //! shared pointer that cares for correct lifetime of IMsgWriter
    //! objects turned to send()
    typedef util::NoOpPtr<IMsgWriter> MsgWriterNoOpPtr;

    //! state a transport instance can be in
    enum State
    {
        //! transport is pristine and prepared to be connected
        NOT_OPEN,
        //! \brief
        //! transport has been successfully connected and is
        //! operational
        OPEN,
        //! \brief
        //! a previous connection has been lost and the
        //! transport is defective
        DEAD
    };

public: // methods
    ITransport() IPL_NOEXCEPT : m_has_error(false)
    { };

    //! \brief
    //! virtual destructor to ensure derived classes dtor always
    //! gets called
    virtual ~ITransport() { };

    //! returns true if a previous operation failed, false otherwise
    bool hasError() const IPL_NOEXCEPT
    { return m_has_error; }

public: // interface

    //! Returns the current state the transport is in
    virtual State getState() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *    Request a buffer of the given size for sending via the
     *    given message writer instance

     *    The IMsgWriter instance \a writer will be called with a
     *    new Writable object able to hold p_size bytes. The
     *    transport layer may add private header and/or footer
     *    data that will be hidden by means of the window
     *    mechanism of Writeable.
     *
     *    The send operation will occur synchronously i.e. after
     *    return of the function call the data will have been
     *    processed by the transport and no reference to \a writer
     *    will be left in the transport implementation.
     * \param[in]
     *    p_size The size of the to be sent message in bytes.
     * \param[in,out]
     *    writer A pointer to an IMsgWriter instance that will be
     *    synchronously called with a Writable object able to hold
     *    \c p_size bytes.
     * \pre
     *    transport needs to be in state OPEN.
     * \errorindicator
     *    via hasError(), via return code
     * \errors
     *    transport::Error with IDs:
     *
     *    - COMMUNICATION_ERROR
     *    - MESSAGE_TOO_BIG
     *    - others
     * \return
     *     \c true on error, \c false on success
     **/
    virtual bool send(const size_t p_size, IMsgWriter* writer) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *    Request a buffer of the given size for sending via the
     *    given message writer instance. Asynchronous/zero-copy
     *    version

     *    Follows the same rules as send(const size_t,
     *    IMsgWriter*) except for the following differences:
     *
     *    This variant of send() allows for asynchronous execution
     *    of the send operation. This has the following
     *    implications:
     *
     *    If the transport implementation makes use of the
     *    possibility to send asynchronously then \a writer will
     *    only be called at a later time. Thus \a writer needs to
     *    be valid until the writer operation actually finished.
     *    The advantage is in this case, that no copy operation
     *    needs to be performed by the transport implementation.
     *    The drawback is increased complexity as the client needs
     *    to handle the shared ptr. and to make sure the \a writer
     *    is valid until the send operation completed.
     *
     *    For transport implementations that don't make use of
     *    asynchronous operations the usage of this variant of
     *    send() imposes merely overhead. The transport
     *    implementation may still choose to call \a writer
     *    synchronously before the call to the function returns.
     * \param[in,out]
     *    writer A SharedPtr to an IMsgWriter instance. The
     *    ownership of the object is turned to the ITransport
     *    implementation. The user should not keep hold of the
     *    object after the function call returns or access it by
     *    any means. If the user still wants to keep access to it
     *    (by holding its own MsgWriterPtr to it) then he needs to
     *    ensure that parallel access to that instance works
     *    correctly. This is because the ITransport instance might
     *    call writer in a separate thread at an unpredictable
     *    time.
     * \return
     *     \c true on error, \c false on success
     * \errorindicator
     *     via hasError(), via return code
     **/
    virtual bool send(const size_t p_size, MsgWriterPtr writer) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *    Receive data from the transport and return a new buffer
     *    containing that data

     *    The amount of data received depend completely upon the
     *    properties and state of the actual transport
     *    facility. Especially if the transport doesn't keep
     *    records boundaries (i.e. keepsRecordBoundaries() ==
     *    false) then you might receive partial or multiple
     *    packets.
     * \pre
     *    transport needs to be in state OPEN.
     * \errorindicator
     *    via hasError(), via return value
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if transport state doesn't match
     * \return
     *     On error an empty Readable, on success a Readable
     *     containg the received data.
     **/
    virtual Readable receive() IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Flush any unwritten data by writing it to the underlying
     *     device

     *     If anything actual happens here depends on the transport
     *     implementation. If a client wants to make sure at a
     *     certain time that priorly sent message are actually
     *     going out onto the underlying device then a call to this
     *     function should be made.
     *
     *     Some transports may cache sent data until a certain
     *     amount of data has been receive or until a certain time
     *     period has passed. In these cases the use of flush is
     *     useful. Client code should be written as though every
     *     transport makes use of flush() without relying on
     *     concrete transport properties.
     * \pre
     *    transport needs to be in state OPEN.
     * \errorindicator
     *    via hasError();
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if transport state doesn't match
     *
     *    transport::Error with IDs:
     *
     **/
    virtual void flush() IPL_NOEXCEPT = 0;

    /**
     * \brief
     *    Open the transport for communication

     *    A new transport instance that's in state NOT_OPEN needs
     *    to be opened via this call before any operation.
     *
     *    This is a blocking operation. On return the transport
     *    will be in the OPEN mode and fully operational.
     *
     *    Calling this function in state OPEN or DEAD will raise
     *    an error.
     * \note
     *    A transport being in the OPEN state does not mean that
     *    communication is sure to work with the peer. Operations
     *    still may fail during receive() or send() calls. This is
     *    merely a preparatory step required before performing
     *    actual communicaton.
     * \pre
     *    transport is in state NOT_OPEN
     * \post
     *    transport is in state OPEN
     * \errorindicator
     *    via hasError();
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_LOGIC if the transport state doesn't match
     *
     *    transport::Error with IDs:
     *
     *    - NO_PEER is raised in case the peer is rejecting the
     *    connection or doesn't respond.
     **/
    virtual void open() IPL_NOEXCEPT = 0;

    /**
     * \brief
     *    Close the transport and disallow further communication

     *    An opened transport instance that is in state OPEN is
     *    shutdown via this call. Afterwards the new state of the
     *    transport will be DEAD.
     *
     *    If the state is already DEAD upon entry then nothing
     *    will be done. If the state is NOT_OPEN than the state
     *    will be transitioned to DEAD without any additional
     *    operations.
     *
     *    Any possibly blocking receive/send calls that are still
     *    active in other threads during a call to close will be
     *    canceled and possibly errors will be raised in those
     *    threads.
     *
     *    May block trying to flush buffered data.
     * \post
     *    transport is in state DEAD
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code instead of hasError() to avoid race
     *    condition with parallel send/receive calls regarding
     *    error indication.
     * \errors
     *    several.
     **/
    virtual bool close() IPL_NOEXCEPT = 0;

    ///////////////////////////////
    // transport feature queries //
    ///////////////////////////////

    /**
     * \brief
     *     Whether the transport is able to notice if the peer dies
     *     in some way

     *     If this returns true then the application doesn't need
     *     to add additional logic to ensure that the communication
     *     link is still up. The transport implementation will
     *     itself report such conditions.
     **/
    virtual bool detectsPeerReset() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Whether the transport stream allows for reliable, loss
     *     free, non-reordered communication
     **/
    virtual bool isReliable() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Gives the maximum message size in bytes that can be sent
     *     over the transport in one go

     *     If you send buffers bigger than this size over the
     *     transport then you'll most likely get an error or
     *     strange behaviour like truncated/lost messages.
     * \warning
     *     This value is only valid in state OPEN.
     **/
    virtual size_t maxMsgSize() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Whether the receiving side gets the same chunks that
     *     were send

     *     If this is not the case than chunks that have been sent
     *     can be received as several, broken up parts on the
     *     receiving side. Also multiple chunks may be received as
     *     a single, merged data block.
     **/
    virtual bool keepsRecordBoundaries() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Returns information about the peer of this transport connection.

     *     PeerInfo can by definition only exist when the peer of the given transport
     *     connection is established.
     *     There are also cases (e.g. connectionless transports) where a PeerInfo doesn't
     *     ever exist.
     *     In those cases the retuned PeerInfoPtr will not be valid.
     * \see util::SharedPtr::valid()
     **/
    virtual PeerInfoPtr getPeerInfo() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Enables a size limit for sending and receiving.

     *     If packets received or to be sent exceed the limit, the send or receive call
     *     will return with error transport::Error MESSAGE_EXCEEDS_LIMIT.
     **/
    virtual void enablePacketSizeLimit(size_t limit) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Disables the size limit for sending and receiving.

     *     Removes the packet size limit established by a prior enablePacketSizeLimit()
     *     call. If no limit was set the call has no effect.
     *
     * \see enablePacketSizeLimit(size_t limit)
     **/
    virtual void disablePacketSizeLimit() IPL_NOEXCEPT = 0;

protected: // functions
    void setError() const IPL_NOEXCEPT
    { m_has_error = true; }

    void resetError() const IPL_NOEXCEPT
    { m_has_error = false; }

protected: // types

    //! A pair of a Writeable object and a Window settings object
    typedef ipl::pair<Writeable, Writeable::Window> ReqWriteable;

protected: // interface

    /**
     * \brief
     *    Protected variant of zero-copy request/submit handling
     *    for sending

     *    The only public variant for sending data via the
     *    ITransport is the send(const size_t, IMsgWriter&)
     *    function. This makes it only possible to request a new
     *    Writeable object that is synchronously filled and sent
     *    vie the provided IMsgWriter object.
     *
     *    In some circumstances this does not suffice and a client
     *    needs to be able to request a Writeable buffer that is
     *    not immediatly sent but kept for some time and sent
     *    later or maybe even never.
     *
     *    Turning a Writeable object with applied window settings
     *    freely to the outside complicates matters for the
     *    ITransport implementor as the user may do whatever he
     *    wants with it (e.g. resizing it, randomly changing
     *    window settings, turn it into different ITransport
     *    instances that didn't issue it etc.).
     *
     *    Thus the possibility to get a Writeable from an
     *    ITransport instance without immediatly sending it is
     *    kept protected in the interface, allowing a stack of
     *    ITransport instances where each instance may operate on
     *    the protected API of the lower instance.
     *
     *    These functions returns a ReqWritable object which
     *    consists of two parts. The first part is a Writeable
     *    able to hold p_size bytes from the callers POV. The
     *    second part is a Writeable::Window that contains the
     *    private Window state of the transport implementation.
     *    The second part should never be touched by the caller.
     *    The complete ReqWritable can be passed at any later time
     *    to the same transport instance where it was obtained via
     *    sendWriteable().
     * \note
     *    A transport implementation may choose not to support
     *    this function due to incompatibility with the internal
     *    transport logic. In this case a NotSupported error will
     *    be raised.
     * \return
     *    A ReqWriteable consisting of a Writeable able to hold
     *    p_size bytes in the first part and a Writeable::Window
     *    state object in the second part. The latter is private
     *    to the ITransport implementation.
     * \pre
     *    transport needs to be in state OPEN.
     * \errorindicator
     *    via hasError()
     * \errors
     *    check the returned writable for validity in case of
     *    allocation errors!
     **/
    virtual ReqWriteable getWriteable(const size_t p_size) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *    Send out a ReqWriteable object previously obtained via
     *    getWriteable()

     *    The Writeable in the first part of w will be sent on the
     *    transport implementation with zero copy semantics.
     *    What's actually happening there depends on the
     *    implementation (i.e. whether the Writeable is sent
     *    immediatly of something else happens).
     *
     *    The Writeable in w.first will be commited and not be
     *    valid any more afterwards. It is to be discarded by the
     *    caller.
     * \pre
     *    transport needs to be in state OPEN.
     * \errorindicator
     *    via hasError()
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if transport state doesn't match
     *
     *    transport::Error with IDs:
     *
     *    - COMMUNICATION_ERROR
     *    - MESSAGE_TOO_BIG
     *    - others
     **/
    virtual bool sendWriteable(ReqWriteable &w) IPL_NOEXCEPT = 0;

private: // data
    mutable bool m_has_error;
}; // class

/**
 * \brief
 *     Use this for transports created by a factory

 *     This exists to avoid mixing up the two orthogonal interfaces of
 *     transporting messages (ITransport) and deleting objects
 *     (IDisposable).
 *
 *    If you inherit this, you should make all constructors and the
 *    destructor non-public and declare friendship to your factory
 *    class.
 * \see
 *     IDisposal for more information.
*/
class UTIL_EXPORT IDisposableTransport: public ITransport, public IDisposable {};

} // end namespace transport
} // end namespace util

#endif
