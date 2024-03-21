/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_FACTORY_SIMPLEFILETRANSPORTFACTORY_HXX
#define UTIL_TRANSPORT_FACTORY_SIMPLEFILETRANSPORTFACTORY_HXX

#include <ipl_config.h>

#include <common/types/string.hxx>

#include <util/util_dso.h>
#include <util/config/Values.hxx>
#include <util/transport/factory/IFactory.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <util/transport/FileTransport.hxx> // for Filename (or not)

namespace util
{

namespace transport
{

    /*!
        \brief Creates client transports that read a file

        \see FileTransport
    */
    class UTIL_EXPORT SimpleFileTransportFactory :
        public IFactory
    {
    public:


        //! Tries to open \a filename each \a poll_ms milliseconds,
        //! or if that is 0, fails if the file cannot be opened right away.
        SimpleFileTransportFactory( const ipl::string &cfg ) IPL_NOEXCEPT;

        virtual FileTransport* createTransport() IPL_NOEXCEPT;

        virtual bool closeFactory() IPL_NOEXCEPT;

        virtual bool isValid() const IPL_NOEXCEPT
        {
            // what else can we say at this time?
            return !m_filename.empty();
        }

        static ipl::string cfg_filename(const util::config::Value& cfg) IPL_NOEXCEPT;

        static unsigned    cfg_poll_ms(const util::config::Value& cfg) IPL_NOEXCEPT;

        const char* factoryType() const IPL_NOEXCEPT
        {
            return util::transport::TransportConfig::SCHEME_FILE;
        }

        static IFactory* create(const ipl::string& config);

    protected:
        ipl::string m_filename;
        unsigned m_poll_ms;
    };


} // end of namespace transport
} // end of namespace util

#endif
