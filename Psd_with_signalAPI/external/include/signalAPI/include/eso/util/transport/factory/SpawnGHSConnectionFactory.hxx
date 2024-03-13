/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SPAWNGHSCONNECTIONFACTORY_HXX
#define UTIL_TRANSPORT_SPAWNGHSCONNECTIONFACTORY_HXX

#include <ipl_config.h>

#include <common/types/string.hxx>
#include <util/transport/factory/ISpawnFactory.hxx>

namespace osal
{
   class GHSServerConnection;
}

namespace util {
namespace transport {

/**
 * \brief
 *     Implementation of a concrete factory for spawning links over GHS connections
**/
   class SpawnGHSConnectionFactory : public ISpawnFactory
   {
   public:

      /**
       * \brief
       *    Construct a spawning GHS connection factory
       * \param[in] config transport config descriptor
       **/
      SpawnGHSConnectionFactory( const ipl::string& config ) IPL_NOEXCEPT;
      virtual ~SpawnGHSConnectionFactory() IPL_NOEXCEPT;

      virtual IDisposableTransport* createTransport() IPL_NOEXCEPT;

      virtual bool closeFactory() IPL_NOEXCEPT;

      const char* factoryType() const IPL_NOEXCEPT;

      virtual bool isValid() const IPL_NOEXCEPT;

      virtual bool enableFactory() IPL_NOEXCEPT;

      virtual bool isEnabled() const IPL_NOEXCEPT;

      static ISpawnFactory* create(const ipl::string& config);
   private:
      bool                       m_valid;
      ipl::string                m_url;
      osal::GHSServerConnection* m_listen;

      // close the listening socket (ignore errors in close)
      void close(osal::GHSServerConnection* s);
   };

}
}

#endif /* UTIL_TRANSPORT_SPAWNGHSCONNECTIONFACTORY_HXX */
