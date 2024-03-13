/*
    Copyright e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_UNIXSOCKETDATAGRAM_HXX
#define OSAL_UNIXSOCKETDATAGRAM_HXX

#include <ipl_config.h>

#include <osal/SocketDatagram.hxx>

#include <osal/UnixSocket.hxx>
#include <common/CommonError.hxx>
#include <osal/Path.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#   include "posix/UnixSocketDefs.hxx"
#elif defined IPL_OS_WINPC
#   error "Unix sockets not available for Windows."
#else
#   error "error undefined IPL_OS_ variant"
#endif

#include <osal/userinfo.hxx>
// for ProcessId
#include <osal/ProcessTNG.hxx>


namespace osal
{

class OSAL_EXPORT UnixSocketDatagram :
    public SocketDatagram
{
public:

    UnixSocketDatagram(const bool p_blocking, const osal::Path &p_src, 
            const UnixSocketBase::NameSpace p_name_space = UnixSocketBase::FILESYSTEM, UnixSocketBase::SocketType type=UnixSocketBase::SocketType::DGRAM);

    
    UnixSocketDatagram(const bool p_blocking, const UnixSocket::Description &p_desc);
    
    ~UnixSocketDatagram() override;

    bool close(bool discard_pending = false) override;

    const UnixSocketBase::NameSpace & getNameSpace() const
    {
        return m_name_space;
    }

    const osal::Path & getLocalAddress() const
    {
        return m_local_address;
    }

    const osal::Path & getPeerAddress() const
    {
        return m_peer_address;
    }

    void updatePeerAddress();
    void updateLocalAddress();

    //! \brief Retrieve the credentials of the peer.
    //!
    //! Once the socket is successfully connected the credentials of the peer can be
    //! retrieved.
    //! Credentials consist of user-, group- and process-id.
    //! The process id may be absent for some OSes.
    //! In that case ProcessTNG::INVALID_PROCESS_ID is returned in pid.
    //!
    //! If the credentials can't be retrieved (e.g. socket isn't connected or already closed)
    //! error values for uid, gid an pid are returned.
    //! The error value for uid is User::BAD_ID, for gid it is Group::BAD_ID.
    //!
    void getPeerCredentials(User::Id& uid, Group::Id& gid, ProcessId& pid);

    //! \brief Retrieve the group list of the peer
    //!
    //! Once the socket is successfully connected the list of supplementary/auxiliary
    //! groups of the peer can be retrieved.
    //!
    //! If the groups can't be retrieved (e.g. socket isn't connected or already closed,
    //! os doesn't support the feature etc.) an empty array is returned
    using Groups = std::vector<Group::Id>;
    Groups getPeerGroups();


    class UDSMessage : public Message
    {
    public:
        ~UDSMessage() override { /* NOP */}
        static ipl::Tag type;
        const ipl::Tag& tag() const IPL_NOEXCEPT override { return type; }
        osal::Path peer;
    };
    /**
        \brief
            Read a message from the socket

            See SocketDatagram::receive. The returned message is of type
            UDSMessage and has information about the peer.
     */
    std::unique_ptr<Message> receive() IPL_NOEXCEPT final;
    /**
        \brief
            Write a message to the socket

            On success send will free the message data
        \return
           true on error, false on success; also via hasError()
     */
    bool send(const ipl::Buf &data, const osal::Path &peer) IPL_NOEXCEPT;


private:
    size_t prepareAddress(sockaddr_un & sa, const osal::Path & path) IPL_NOEXCEPT;
    osal::Path convertAddress(const sockaddr_un &sa, size_t len) IPL_NOEXCEPT;

    osal::Path m_local_address;
    osal::Path m_peer_address;
    size_t m_local_addr_size;
    size_t m_peer_addr_size;
    UnixSocketHandle m_unix_socket_handle;
    bool m_bound_local_socket;

    const UnixSocketBase::NameSpace m_name_space;
};

} // end namespace osal

#endif /* OSAL_UNIXSOCKETDATAGRAM_HXX */
