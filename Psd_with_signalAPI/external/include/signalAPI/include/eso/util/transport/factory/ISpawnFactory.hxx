/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_ISPAWNFACTORY_HXX
#define UTIL_TRANSPORT_ISPAWNFACTORY_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <util/transport/factory/IFactory.hxx>

namespace util
{

namespace transport
{

/**
 * \brief
 *    Interface for Spawn Transport Factories

 *     This is an extended IFactory interface for spawn factories.
 *
 *     Currently it essentially adds a call to "enable" the factory.
 *     This is necessary to prevent a race condition when a
 *     communication node wants to tell another communication node that
 *     connection to it's spawn factory are now possible.
 *
 *     The IFactory::closeFactory() function causes this spawning mode
 *     to be disabled again such that no further connections from
 *     clients are possible.
**/
class UTIL_EXPORT ISpawnFactory :
    public IFactory
{
public: // functions
    virtual ~ISpawnFactory() IPL_NOEXCEPT { };

    /**
     * \brief
     *     Returns \c true if the factory is currently enabled
     **/
    virtual bool isEnabled() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Enable the factory in a way that transports can be
     *     created

     *     After a successful return from this function, calls to
     *     createTransport() shall become possible and also remote
     *     nodes shall be able to connect to the spawn factories
     *     transport facility.
     * \return
     *     \c true on error, \c false on success
     **/
    virtual bool enableFactory() IPL_NOEXCEPT = 0;

    typedef ISpawnFactory* (*SpawnFactoryCreator)(const ipl::string& config);
}; // class

} // end namespace transport
} // end namespace util

#endif
