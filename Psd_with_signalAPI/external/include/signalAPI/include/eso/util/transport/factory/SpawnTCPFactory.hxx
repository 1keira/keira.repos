/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SPAWNTCPFACTORY_HXX
#define UTIL_TRANSPORT_SPAWNTCPFACTORY_HXX

#include <ipl_config.h>

#include <util/util_dso.h>

#include <common/types/string.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <util/transport/TCPTransport.hxx>
#include <util/transport/factory/ISpawnFactory.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <util/transport/TransportErrors.hxx>
#include <util/transport/factory/tcp.hxx>

namespace osal {

    class TCPServerSocket;

}

namespace util {
    namespace transport {

        /**
        * \brief
        *     Implementation of a concrete factory for spawn TCP links

        *     Checks provided link configuration entry for compatibility upon
        *     construction time.
        *
        *     A TCPServerSocket is setup according to configuration settings.
        *
        *     createTransport enables listening mode of server socket and does
        *     one accept call on it. It may be called multiple times to obtain
        *     multiple clients. This is a blocking call.
        **/
        class UTIL_EXPORT SpawnTCPFactory :
            public ISpawnFactory
        {
        public: // methods
            /**
            * \brief
            *     Construct a spawn TCP factory

            *     The constructor won't perform any validity checks.
            *     Actual operations are only performed within
            *     enableFactory().
            * \param[in] hostname
            *     The DNS hostname or IP address to listen on
            * \param[in] port
            *     The TCP port to listen on
            * \param[in] rx_buffer
            *     Size of the receive buffer in bytes for spawned
            *     connections. If zero then defaults apply.
            * \param[in] tx_buffer
            *     Size of the transmit buffer in bytes for spawned
            *     connections. If zero then defaults apply.
            * \errorindicator
            *     via isValid()
            **/
            SpawnTCPFactory( const ipl::string& cfg ) IPL_NOEXCEPT;

            /**
            * \brief
            *     Destroy the spawn TCP factory
            * \pre
            *     The factory is currently disabled i.e. isEnabled()
            *     returns \c false
            **/
            virtual ~SpawnTCPFactory() IPL_NOEXCEPT;

            /**
            * \brief
            *     Create a new transport by means of accepting an incoming
            *     TCP connection

            *     This call will block until a new TCP connection is
            *     accepted.
            * \return
            *     NULL on error, otherwise a new transport
            **/
            virtual IDisposableTransport* createTransport() IPL_NOEXCEPT;

            /**
            * \brief
            *     Creates a new socket and sets it into listening state

            *     If the factory is already enabled then \c false is
            *     returned without any operations being performed.
            * \pre
            *     Factory must not currently be enabled i.e. isEnabled()
            *     returns \c false.
            * \post
            *     On success the factory becomes valid i.e. isEnabled()
            *     returns \c true. Calls to createTransport() become
            *     possible.
            * \errorindicator
            *     via return code
            * \return
            *     \c true on error, \c false on success
            **/
            virtual bool enableFactory() IPL_NOEXCEPT;

            /**
            * \brief
            *     Closes the socket, disallowing further connections

            *     If the factory is not currently enabled then \c false is
            *     returned without doing anything.
            * \pre
            *     The factory must currently be enabled i.e. isEnabled()
            *     returns \c true.
            * \post
            *     On success further calls to createTransport() will fail,
            *     the factory will be disabled i.e. isEnabled() will return
            *    \c false.
            * \errorindicator
            *     via return code
            * \return
            *     \c true on error, \c false on success
            **/
            virtual bool closeFactory() IPL_NOEXCEPT;

            virtual bool isEnabled() const IPL_NOEXCEPT;

            virtual bool isValid() const IPL_NOEXCEPT
            {
                // errors can only be determined at enable-time
                return true;
            }

            virtual const char* factoryType() const IPL_NOEXCEPT
            {
                return util::transport::TransportConfig::SCHEME_TCP;
            }

            static ISpawnFactory* create(const ipl::string& config);
        protected: // types

        protected: // methods
            //! Frees dynamically allocated stuff, if needed
            void cleanup() IPL_NOEXCEPT;

        protected: // members
            //! the server socket used for accepting new connections
            osal::TCPServerSocket *m_serv;

            //! \brief
            //! to prevent parallel access to m_serv in createTransport()
            //! and releaseCallers()
            osal::Mutex m_lock;

            //! for waiting for blocking calls to end
            osal::Condition m_cond;

            //! \brief
            //! whether currently a thread is doing a blocking call on
            //! m_serv
            bool m_blocking_call;

            ipl::string m_url;
            tcp::Param  m_param;
        private:
            void closeSocket(osal::TCPSocket* socket) const IPL_NOEXCEPT;
        };

    }  // end of namespace transport
}  // end of namespace util

#endif
