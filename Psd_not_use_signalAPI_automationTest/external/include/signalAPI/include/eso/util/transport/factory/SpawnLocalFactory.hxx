/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SPAWNLOCALFACTORY_HXX
#define UTIL_TRANSPORT_SPAWNLOCALFACTORY_HXX

#include <ipl_config.h>

#include <common/types/string.hxx>
#include <osal/UnixSocket.hxx>
#include <util/transport/factory/ISpawnFactory.hxx>
#include <util/transport/factory/local.hxx>

namespace osal {
    class UnixServerSocket;
}

namespace util {
namespace transport {

/**
 * \brief
 *     Implementation of a concrete factory for spawning links over AF_UNIX sockets
**/
    class SpawnLocalFactory : public ISpawnFactory {
        public:

            /**
             * \brief
             *    Construct a spawning Local factory
             * \param[in] config transport config descriptor
             **/
            explicit SpawnLocalFactory( const ipl::string& config ) IPL_NOEXCEPT;
            virtual ~SpawnLocalFactory() IPL_NOEXCEPT;

            SpawnLocalFactory(const SpawnLocalFactory&) = delete;
            SpawnLocalFactory operator=(const SpawnLocalFactory&) = delete;

            virtual IDisposableTransport* createTransport() IPL_NOEXCEPT;

            virtual bool closeFactory() IPL_NOEXCEPT;

            const char* factoryType() const IPL_NOEXCEPT;

            virtual bool isValid() const IPL_NOEXCEPT;

            virtual bool enableFactory() IPL_NOEXCEPT;

            virtual bool isEnabled() const IPL_NOEXCEPT;

            static ISpawnFactory* create(const ipl::string& config);

        private:
            bool                         m_valid;
            ipl::string                  m_url;
            local::Param                 m_param;
            osal::UnixSocket::SocketType m_sockettype;
            osal::UnixServerSocket*      m_listen;

            // close the listening socket (ignore errors in close)
            void close(osal::UnixServerSocket* s);
    };

}
}

#endif /* UTIL_TRANSPORT_SPAWNLOCALFACTORY_HXX */


