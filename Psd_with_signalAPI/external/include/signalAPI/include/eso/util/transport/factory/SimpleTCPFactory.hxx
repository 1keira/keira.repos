/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SIMPLETCPFACTORY_HXX
#define UTIL_TRANSPORT_SIMPLETCPFACTORY_HXX

#include <ipl_config.h>

#include <util/util_dso.h>

#include <iplbase/exceptions.hxx>
#include <common/types/string.hxx>
#include <osal/IPSocket.hxx>
#include <util/transport/factory/IFactory.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <util/transport/factory/tcp.hxx>

namespace osal
{
    class TCPSocket;
}

namespace util
{
namespace transport
{

/**
 * \brief
 *     Implementation of a concrete factory for simple TCP links
**/
class UTIL_EXPORT SimpleTCPFactory :
    public IFactory
{
public: // methods

    /**
     * \brief
     *    Construct a one-to-one link TCP factory
     * \param[in] cfg The confog - url
     **/
    SimpleTCPFactory( const ipl::string& cfg ) IPL_NOEXCEPT;

    virtual IDisposableTransport* createTransport() IPL_NOEXCEPT;

    //! \note currently does nothing
    virtual bool closeFactory() IPL_NOEXCEPT { return false; }

    const char* factoryType() const IPL_NOEXCEPT {
        return util::transport::TransportConfig::SCHEME_TCP;
    }

    virtual bool isValid() const IPL_NOEXCEPT;

    static IFactory* create(const ipl::string& config);
private:
    ipl::string m_url;
    bool        m_valid;
};

}
}

#endif // UTIL_TRANSPORT_SIMPLETCPFACTORY_HXX
