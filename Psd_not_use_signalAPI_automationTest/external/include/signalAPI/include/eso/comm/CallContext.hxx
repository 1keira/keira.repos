#ifndef COMM_CALL_CONTEXT_HXX
#define COMM_CALL_CONTEXT_HXX

#include <comm/comm_dso.h>
#include <common/types/string.hxx>
#include <common/types/vector.hxx>
#include <osal/ProcessTNG.hxx>
#include <osal/IPSocket.hxx>
#include <osal/userinfo.hxx>

namespace comm {

    struct CallContext;

    // gcc docs say
    // void __attribute__ ((visibility ("default")))
    // f () { /* Do something. */; }
    // but this causes
    // warning: ‘visibility’ attribute ignored on non-class types [-Wattributes]
    // this:
    // __attribute__ ((visibility ("default"))) void f ();
    // seem to work

    /*!
        \brief An opaque ID that identifies a proxy-stub session.
        The session ID will be unique for a specific proxy-stub session and
        hence have the same value for all calls including clientConnected
        and clientDisconnected from the same proxy.
    */
    typedef uint64_t SessionID;

    /*!
        \brief Gets the session id
    */
    COMM_EXPORT SessionID getSessionID ( const CallContext& ctx );

    /*!
        \brief Gets the type of the peer info as a string
        Return values are
        "ProcessPeer" a process on the same OS instance as this one.
        "IPPeer" a process connected via TCP/UDP/TLS
        "Unknown" peer infomation is not available
    */
    COMM_EXPORT const char* getPeerInfoType ( const CallContext& ctx );

    /*!
        \brief Gets the peer info as a string.
    */
    COMM_EXPORT ipl::string getPeerInfo ( const CallContext& ctx );

    /*!
        \brief Information about a peer presented as Posix-like process-, user- and group ids.
        If pid is the process id of this process, user and groups are not filled in.
        Numerical Id to name conversion can be done with osal::User and osal::Group
    */
    struct COMM_EXPORT ProcessPeerInfo {
        using UserID = osal::User::Id;
        using GroupID = osal::Group::Id;

        // invalid USER ID
        static const UserID	INVALID_USER_ID;

        // invalid group ID
        static const GroupID INVALID_GROUP_ID;

        ProcessPeerInfo()
        : version_tag(1)
        , pid(osal::ProcessTNG::INVALID_PROCESS_ID)
        , uid(INVALID_USER_ID)
        {}

        const uint8_t				version_tag;
        osal::ProcessId				pid;
        UserID						uid;
        ipl::vector<GroupID>		gids;
    };

    /*!
        \brief Gets the peer info as as ProcessPeerInfo.
        Fails with return value true if the peer is not a process of the same OS instance
        as this process.
    */
    COMM_EXPORT bool getProcessPeerInfo ( const CallContext& ctx, ProcessPeerInfo& info );

    /*!
        \brief Information about a peer's IP address
    */
    struct COMM_EXPORT IPPeerInfo {
        IPPeerInfo()
        : version_tag(1)
        , ip_version(osal::IPSocket::IPVUNSPEC)
        {}

        const uint8_t						version_tag;
        osal::IPSocket::IPAddress			address;
        osal::IPSocket::IPProtocolVersion	ip_version;
    };

    /*!
        \brief Gets the peer info as an IP address.
        Fails with return value true if the peer is not connected to this process by an ip based
        connection.
    */
    COMM_EXPORT bool getIPPeerInfo ( const CallContext& ctx, IPPeerInfo& info );

}


#endif // COMM_CALL_CONTEXT_HXX

