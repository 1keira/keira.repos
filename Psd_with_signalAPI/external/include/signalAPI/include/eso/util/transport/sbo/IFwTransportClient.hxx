/*
    Copyright 2023 e.solutions GmbH
    All rights reserved
 */

#ifndef UTIL_TRANSPORT_SBO_IFWTRANSPORTCLIENT_HXX_
#define UTIL_TRANSPORT_SBO_IFWTRANSPORTCLIENT_HXX_


#include <memory>
#include <string>
#include <vector>

#include <common/types/optional.hxx>

namespace util {
namespace transport {
namespace sbo {
// ##############################
// ### it is all a stable API ###
// ##############################
// located in esofw_core_sdk and will be copied to aosp src directory
// the SBOGenericlient builds against this interface

/**
 * \brief Contains information about a peer.
 **/
class PeerInfo {
public:
    PeerInfo(const std::string& processName, int32_t uid, int32_t pid, const std::vector<int64_t>& groupIds):
        m_processName(processName), m_uid(uid), m_pid(pid), m_groupIds(groupIds) {}

    //! \note the framework process name
    const std::string m_processName;
    //! \note  the uid of the peer
    const int32_t m_uid;
    //! \note  the pid of the peer
    const int32_t m_pid;
    //! \note group ids of the peer
    const std::vector<int64_t> m_groupIds;
};

/**
 * \brief Contains the neccessary stuff to communicate 
 * with a remote peer
 **/
class TransportParams {
public:
    TransportParams(const PeerInfo& peerInfo, const std::vector<int> fds) :
        m_peerInfo(peerInfo), m_fds(fds) {}

    //! \note some necessary params about the remote peer
    const PeerInfo m_peerInfo;
    //! \note file descriptors which can be used to communicate with another peer 
    //   m_fds.size == 2: [0] = readFd, [1] = writeFd, m_fds.size == 1: [0] = readFd/writeFd
    const std::vector<int32_t> m_fds;
};

/**
 * \brief Contains an error or TransportParams
 **/
class TransportParamsOrError {
public:
    TransportParamsOrError(const TransportParams& tParams): m_tParams(tParams) {}
    TransportParamsOrError(const std::string& error): m_error(error) {}

    //! \note is set when the connection is successful established
    const ipl::optional<TransportParams> m_tParams;
    //! \note is set when an error happens
    const ipl::optional<std::string> m_error;

    bool isError() {
        return m_error.has_value();
    }
};

/**
 * \brief Contains an error or file descriptors
 **/
class FdsOrError {
public:
    FdsOrError(const std::vector<int>& fds): m_fds(fds) {}
    FdsOrError(const std::string& error): m_error(error) {}

    bool isError() {
        return m_error.has_value();
    }

    //! \note m_fds.size == 2: [0] = readFd, [1] = writeFd, m_fds.size == 1: [0] = readFd/writeFd
    const std::vector<int> m_fds;
    //! \note can contain an error string
    const ipl::optional<std::string> m_error;
};

/**
 * \brief
 *    Interface which is used to inform a peer about incoming connection calls.
**/
class ISpawningListenerClient
{
public:
    ISpawningListenerClient() { };
    virtual ~ISpawningListenerClient() {};
    /**
     * \brief Will be called for incoming connect calls.
     *
     * The spawnListener must decide whether to reject the incoming connection and to return an error or
     * to accept the incoming connection and create some file descriptors which are used for the communication
     * between the peers.
     *
     * \param protocol for which the connection should be established
     * \param localId is used to distinguish when there are more than one spawning side for the same protocol is defined
     * \param params about the remote peer
     *
     * \return FdsOrError containing an error when the connection can not be established or a vector of file
     *         descriptors for a successful connection
     *
     **/
    virtual FdsOrError peerConnected(const std::string& protocol, int32_t localId ,const PeerInfo& params) noexcept = 0;
};

/**
 * \brief Interface of a transport facility for file descriptor based communication.
 * 
 *    Interface which is defined and used but not implemented in util transport sbo. It must be
 *    implemented by another component. So the util transport sbo can dynamically load it via corresponding mechanisms.
 *
 *    The interface allow to initialize the own communication via a init function. The interface provides
 *    a method to connect to other peers.
**/
class IFwTransportClient
{
public:
    IFwTransportClient() {};
    virtual ~IFwTransportClient() {};

    /**
     * \brief
     *     Initialize the transport with the in_ownAppId and a spawning listener
     *
     * The spawnListener will be triggered when another client calls connect with the given appId.
     * The spawnListener must decide whether to accept or reject the incoming connection and create some
     * file descriptors which are used for communication between the peers.
     *
     * \param ownProcessName the framework process name
     * \param spawnListener, must not be null, for incomming connect calls
     **/
    virtual void init(const std::string& ownProcessName, std::shared_ptr<ISpawningListenerClient> spawnListener) noexcept = 0;
    /**
     * \brief
     *     Connect to a remote peer for the given protocol and remoteAppId
     *
     * The spawnListener will be triggered when another client calls connect with the given appId.
     *
     * \param remoteProcessName the framework process name of the peer to connect
     * \param protocol the protocol for which the connection should be established
     * \param localId is used to distinguish when there are more than one spawning side for the same protocol is defined
     *
     * \return a TransportParamsOrError object which includes an error when the connect call fails, or
     *         TransportParams of the connection, when the connect call was successful
     **/
    virtual TransportParamsOrError connect( const std::string& remoteProcessName, const std::string& protocol, int32_t localId) noexcept = 0;
};

} /*  namespace sbo */
} /*  namespace transport */
} /*  namespace util */

#endif /* UTIL_TRANSPORT_SBO_IFWTRANSPORTCLIENT_HXX_ */
