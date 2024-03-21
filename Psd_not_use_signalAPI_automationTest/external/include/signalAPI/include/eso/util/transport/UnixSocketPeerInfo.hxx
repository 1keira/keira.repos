/****************************************************************************/
/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_TRANSPORT_UNIXSOCKETPEERINFO_HXX
#define UTIL_TRANSPORT_UNIXSOCKETPEERINFO_HXX
/****************************************************************************/

#include "PosixProcessPeerInfo.hxx"
#include <osal/UnixSocket.hxx>

/****************************************************************************/

namespace util {
    namespace transport {

/****************************************************************************/

        /*!
            \brief Adding a relevant constructor to PosixProcessPeerInfo
            
            This class works around the fact that plain PosixProcessPeerInfo
            is supposed to be framework-free code, i.e. cannot touch or
            even know about osal::UnixSocket.
        */
        class UnixSocketPeerInfo: public PosixProcessPeerInfo {
        
        public:
            UnixSocketPeerInfo(const osal::UnixSocket &socket) IPL_NOEXCEPT:
                PosixProcessPeerInfo(osal::User::BAD_ID, 0)
            {
                // peer info for unix domain sockets is available after either connect()
                // or bind()->listen()->accept()
                // for the client side we just succeeded to connect(), for the server side we were constructed
                // with a UnixSocket::Description that was acquired from accept()
                osal::User::Id uid;
                osal::Group::Id gid;
                osal::ProcessId pid;
                socket.getPeerCredentials(uid, gid, pid);
                // reset to non-negative if pid is missing
                if ( pid == osal::ProcessTNG::INVALID_PROCESS_ID ) pid = 0;
                // check error for getPeerCredentials

                m_uid=uid;
                m_pid=pid;
                // try to get peer groups from socket
                osal::UnixSocketBase::Groups peer_groups = socket.getPeerGroups();
                if ( peer_groups.empty() ) {
                    getGroups(gid);
                } else {
                    // add own group since ConnectClientInfoExt() doesn't do it
                    m_groups.push_back(gid);
                    for( unsigned i=0; i<peer_groups.size(); ++i ) {
                        // don't add gid twice
                        if ( peer_groups[i] != gid ) {
                            m_groups.push_back(static_cast<GroupID>(peer_groups[i]));
                        }
                    }
                }
            }
        };
        
/****************************************************************************/

    }  // end of namespace transport
}  // end of namespace util

/****************************************************************************/
#endif
