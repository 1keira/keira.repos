/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_TRANSPORTSERVER_SPAWNFACTORY_HXX
#define UTIL_TRANSPORT_TRANSPORTSERVER_SPAWNFACTORY_HXX

#include <ipl_config.h>

#include <common/types/string.hxx>
#include <osal/AtomicCounter.hxx>
#include <util/util_dso.h>

#include <util/transport/factory/ISpawnFactory.hxx>
#include <util/transport/factory/TransportConfig.hxx>

namespace util
{

namespace transport
{
    class FileTransport;
/*
 * \brief
 *    Interface for the Qnx crossboard transport server spawn transport factory.
 */
    class UTIL_EXPORT TransportServerSpawnFactory : public ISpawnFactory {
        public:
            TransportServerSpawnFactory(const ipl::string& config ) IPL_NOEXCEPT;

            virtual ~TransportServerSpawnFactory() IPL_NOEXCEPT;

            /**
             * @see util::transport::ISpawnFactory::isEnabled()
             */
            virtual bool isEnabled() const IPL_NOEXCEPT;

            /**
             * @see util::transport::ISpawnFactory::enableFactory()
             **/
            virtual bool enableFactory() IPL_NOEXCEPT;

            /**
             * @see util::transport::IFactory::closeFactory()
             **/
            virtual bool closeFactory() IPL_NOEXCEPT;

            /**
             * @see util::transport::IFactory::isValid()
             **/
            virtual bool isValid() const IPL_NOEXCEPT;

            /**
             * @see util::transport::IFactory::createTransport()
             **/
            virtual IDisposableTransport* createTransport() IPL_NOEXCEPT;

            /**
             * @see util::transport::IFactory::factoryType()
             **/
            virtual const char* factoryType() const IPL_NOEXCEPT {
                return util::transport::TransportConfig::SCHEME_TS;
            }

            static ISpawnFactory* create(const ipl::string& config);
        private:
            ipl::string         m_path;
            size_t                m_rx_size;
            size_t                m_tx_size;
            osal::AtomicCounter    m_enabled;

    };

}
}

#endif /* UTIL_TRANSPORT_TRANSPORTSERVER_SPAWNFACTORY_HXX */
