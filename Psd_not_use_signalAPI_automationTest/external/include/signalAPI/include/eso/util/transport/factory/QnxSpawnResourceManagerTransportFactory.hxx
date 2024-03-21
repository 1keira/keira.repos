/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_QNXSPAWNRESOURCEMANAGERTRANSPORTFACTORY_HXX
#define UTIL_TRANSPORT_QNXSPAWNRESOURCEMANAGERTRANSPORTFACTORY_HXX

#include <ipl_config.h>

#include <util/util.hxx>
#include "ISpawnFactory.hxx"
#include "QnxResourceManagerTransportFactoryUnderwear.hxx"
#include <util/transport/QnxResourceManagerTransport.hxx>
#include <util/transport/factory/TransportConfig.hxx>

namespace util
{

namespace transport
{

/**
 * \brief
 *     Implementation of a factory for spawning connections from a QNX
 *     resource manager
 * \see
 *    QnxResourceManagerTransport
 *
 *    This factory creates instances of QnxResourceManagerTransport
 *    upon open calls to the factory's resource manager device file.
 *
 *    Technically this is a thin wrapper around
 *    QnxResourceManagerTransportFactoryUnderwear, which does the
 *    actual work.
 *
 *    This seperation is necessary to allow the client-visible factory
 *    being deleted while the underwear part actually might continue
 *    existing. This is the result of the
 *    QnxResourceManagerTransport's lifetime being coupled to the
 *    lifetime of the associated factory's engine.
*/
class UTIL_EXPORT QnxSpawnResourceManagerTransportFactory :
    public ISpawnFactory
{
public: // types

//    /**
//     * \brief
//     *     Settings for the ThreadPool used by the internal
//     *     resource manager engine
//   *
//     *     Regarding the meaning of these settings please refer to
//     *     osal::qnxresourcemanager::ThreadPool.
//     *
//     *     Sensible defaults are chosen by the default ctor.
//     **/
//    struct ThreadPoolSettings
//    {
//        int min_blocking_threads;
//        int max_blocking_threads;
//        int creation_step;
//        int max_overall_threads;
//
//        ThreadPoolSettings() :
//            min_blocking_threads(1),
//            max_blocking_threads(5),
//            creation_step(1),
//            max_overall_threads(10)
//        { }
//    };

public: // functions

    /**
     * \brief
     *     Create a resource manager factory that creates a device
     *  file for clients to connect to
     **/
    QnxSpawnResourceManagerTransportFactory( const ipl::string &config ) IPL_NOEXCEPT;
    /**
     * \brief
     *     Destroys the client visible part of the factory. The
     *     underwear part of the factory will continue to exist
     *     until all QnxResourceManagerTransport instances spawned
     *     from it are disposed.
     * \pre
     *     The factory needs to be disabled before the object is
     *     destroyed
     **/
    ~QnxSpawnResourceManagerTransportFactory() IPL_NOEXCEPT;

    virtual bool enableFactory() IPL_NOEXCEPT
    {
        return m_underwear && m_underwear->enableUnderwear();
    }

    virtual bool closeFactory() IPL_NOEXCEPT
    {
        if( m_underwear )
            return m_underwear->disableUnderwear();

        return false;
    }

    virtual bool isEnabled() const IPL_NOEXCEPT
    {
        return m_underwear && m_underwear->isValid();
    }

    virtual bool isValid() const IPL_NOEXCEPT
    {
        return (bool)m_underwear;
    }

    /**
     * \brief
     *     Accept an open request on the resource manager device
     *     file
     *
     *     Open requests are accepted asynchronously by the factory
     *     so it can be the case that a transport is already
     *     available to accept. Otherwise if the call will block
     *     until an open request is coming in
     **/
    virtual QnxResourceManagerTransport* createTransport() IPL_NOEXCEPT;

    virtual const char* factoryType() const IPL_NOEXCEPT
    {
        return util::transport::TransportConfig::SCHEME_RESMAN;
    }

    static ISpawnFactory* create(const ipl::string& config);
protected: // data

    //! just a pseudo flag to make enable/disable do the expected stuff
    bool m_enabled;

    //! a shared ptr. to underwear
    QnxResourceManagerTransportFactoryUnderwear::UnderwearPtr m_underwear;
};


}  // end of namespace transport
}  // end of namespace util

#endif
