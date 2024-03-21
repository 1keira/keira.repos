/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_UNIXSOCKETBASE_HXX
#define OSAL_UNIXSOCKETBASE_HXX

#include <ipl_config.h>

#include <osal/Socket.hxx>

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

class OSAL_EXPORT UnixSocketBase :
    public Socket
{
public: // types
    enum NameSpace
    {
        ABSTRACT,
        FILESYSTEM
    };

    enum class SocketType {
        STREAM,
        DGRAM,
        SEQPACKET
    };

public: // functions
    virtual ~UnixSocketBase();

    bool close(bool p_shutdown = false);

    const NameSpace & getNameSpace() const
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
    void getPeerCredentials(User::Id& uid, Group::Id& gid, ProcessId& pid) const;

    //! \brief Retrieve the group list of the peer
    //!
    //! Once the socket is successfully connected the list of supplementary/auxiliary
    //! groups of the peer can be retrieved.
    //!
    //! If the groups can't be retrieved (e.g. socket isn't connected or already closed,
    //! os doesn't support the feature etc.) an empty array is returned
    using Groups = std::vector<Group::Id>;
    Groups getPeerGroups() const;

protected: // functions
    UnixSocketBase(
        const bool p_blocking,
        const size_t p_input_buffer,
        const size_t p_output_buffer,
        const osal::Path & p_src,
        const osal::Path & p_dst,
        const NameSpace p_name_space = FILESYSTEM);

    size_t prepareAddress(sockaddr_un & sa, const osal::Path & path);
protected: // members
    osal::Path m_local_address;
    osal::Path m_peer_address;
    size_t m_local_addr_size;
    size_t m_peer_addr_size;
    UnixSocketHandle m_unix_socket_handle;
    bool m_bound_local_socket;

private: // members
    const NameSpace m_name_space;
};

} // end namespace osal

#endif /* OSAL_UNIXSOCKETBASE_HXX */
