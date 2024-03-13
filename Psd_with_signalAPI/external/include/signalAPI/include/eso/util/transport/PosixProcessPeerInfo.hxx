/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_PROCESS_PEERINFO_HXX
#define UTIL_TRANSPORT_PROCESS_PEERINFO_HXX

#include <ipl_config.h>

#include <common/stdint.h>
#include <util/transport/PeerInfo.hxx>
#include <osal/userinfo.hxx>

#include <vector>
#include <iostream>

// This should build without runtime dependencies to framework libs
// so that it can be used in jni without dragging all framewerk libs into
// the Java VM.
// so: careful with includes


namespace util {
namespace transport {
    // Peer info for a process using a Posix user and group ID concept
    class UTIL_EXPORT PosixProcessPeerInfo : public PeerInfo {
        public:
            PosixProcessPeerInfo() IPL_NOEXCEPT;
            ~PosixProcessPeerInfo() IPL_NOEXCEPT override = default;

            static ipl::Tag TYPE;
            const ipl::Tag& tag() const IPL_NOEXCEPT override { return TYPE; }

            using UserID = osal::User::Id;
            using GroupID = osal::Group::Id;
            using ProcessID = int64_t;

            // effective uid, gid of peer, pid of peer. pid might be invalid (0)
            PosixProcessPeerInfo(UserID uid, GroupID gid, ProcessID pid) IPL_NOEXCEPT;
            // effective uid, gid of peer, pid of peer, number and array
            // of supplementary groups
            PosixProcessPeerInfo(UserID uid, GroupID gid, ProcessID pid
                            , uint32_t nsupp, GroupID* supp) IPL_NOEXCEPT;

            // with uid, gid of peer, pid of peer and groups vector
            PosixProcessPeerInfo(UserID uid, GroupID gid, ProcessID pid
                            , const std::vector<osal::Group::Id>& groups) IPL_NOEXCEPT;
                            
            // an array of group ids
            typedef std::vector<GroupID> Groups;

            // process id of the peer
            ProcessID pid() const IPL_NOEXCEPT { return m_pid; }
            // user id of the peer
            UserID uid() const IPL_NOEXCEPT { return m_uid; }
            // returns the group ids of the peer. has at least the primary group of the peer
            const Groups& gids() const IPL_NOEXCEPT { return m_groups; }

            std::string toString() const IPL_NOEXCEPT override;

        protected:
            PosixProcessPeerInfo(UserID uid, ProcessID pid) IPL_NOEXCEPT:
                m_uid(uid), m_pid(pid) {}

            UserID       m_uid;
            ProcessID    m_pid;
            Groups       m_groups;

            void getGroups(GroupID gid) IPL_NOEXCEPT;
    };

    UTIL_EXPORT std::ostream& operator<<(std::ostream& out, const PosixProcessPeerInfo& peer_info) IPL_NOEXCEPT;
}
}
#endif


