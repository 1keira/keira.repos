/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SIMPLEGHSCONNECTIONFACTORY_HXX
#define UTIL_TRANSPORT_SIMPLEGHSCONNECTIONFACTORY_HXX

#include <ipl_config.h>

#include <util/util_dso.h>

#include <common/types/string.hxx>
#include <osal/AtomicCounter.hxx>
#include <util/transport/factory/IFactory.hxx>
#include <util/transport/factory/TransportConfig.hxx>

namespace util
{
namespace transport
{

/**
 * \brief
 *     Implementation of a concrete factory for simple GHS connection links
**/
class UTIL_EXPORT SimpleGHSConnectionFactory :
    public IFactory
{
public:

    /**
     * \brief
     *    Construct the client side for a communication link via GHS connection
     * \param[in] url
     *    The url representing the communication endpoint with a "GHSconn" scheme
     **/
    SimpleGHSConnectionFactory( const ipl::string &url ) IPL_NOEXCEPT;

    virtual ~SimpleGHSConnectionFactory() IPL_NOEXCEPT;

    virtual IDisposableTransport* createTransport() IPL_NOEXCEPT;

    virtual bool closeFactory() IPL_NOEXCEPT;

    const char* factoryType() const IPL_NOEXCEPT
    {
        return util::transport::TransportConfig::SCHEME_GHSCONN;
    }

    virtual bool isValid() const IPL_NOEXCEPT;

    static IFactory* create(const ipl::string& config);
protected:
    ipl::string         m_url;
    bool                m_valid;
    osal::AtomicCounter m_closed;
};

}
}

#endif
