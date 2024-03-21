/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SIMPLEFACTORY_HXX
#define UTIL_TRANSPORT_SIMPLEFACTORY_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <common/types/string.hxx>
#include <common/types/map.hxx>

#include <util/transport/ITransport.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <util/transport/factory/IFactory.hxx>

namespace util
{
namespace transport
{

/**
 * \brief
 *     Creates a transport for simple one-to-one link from one process
 *     to another
 *
 *     Clients of SimpleFactory need to pass logical connection
 *     identifiers and the factory will return a correctly configured
 *     transport for communication. This factory is for one-to-one
 *     links only i.e. for types of transports that establish a single
 *     connection between two users. No second parallel connection or
 *     connection of multiple users at the same time is possible.
 *
 *     The logical connection identifiers are made up of the source
 *     process name, the destination process name and the service name
 *     (like comm or tracing).
**/
class UTIL_EXPORT SimpleFactory
{
public: // subclasses / fwd. decl. / types

public: // methods
    /**
     * \brief
     *     Constructs a factory with the passed parameters
     *
     *     In contrast to the other constructor variant this one
     *     does not rely on a suitable configuration file but
     *     instead it takes a ConnectionEntryDescriptor that
     *     already contains transport type and addressing
     *     parameters.
     *
     *     This is especially useful for more simple setups like in
     *     testing environments.
     **/
    SimpleFactory(const ipl::string& cfg ) IPL_NOEXCEPT;

    //! \brief
    //!    In debug mode asserts that no alive transport
    //!     constructed by this factory is left out there
    ~SimpleFactory() IPL_NOEXCEPT;
    
    SimpleFactory(const SimpleFactory &)=delete;
    SimpleFactory &operator = (const SimpleFactory &)=delete;

    /**
     * \brief
     *    Create a new transport according to construction time
     *    specifications
     *
     *    The returned transport will already be in the OPEN
     *    state. As the open operation on transports can be
     *    blocking, the call to this function can also be
     *    blocking.
     *
     *    After the client is finished with using the transport,
     *    it has to be closed via its close() function and freed
     *    by calling the dispose() function.
     *
     *    If multiple calls to createTransport are performed
     *    without disposing a previously acquired transport first
     *    then an error is raised.
     * \errorindicator
     *    NULL return is an error.
     * \errors
     *    FactoryError with IDs:
     *
     *    - CREATION_ERROR in case the construction or setup of
     *    the actual transport instance failed.
     *    - TRANSPORT_IN_USE in case there is already a transport
     *    instance active created by this factory, that has not
     *    been disposed via calling dispose() on it.
     * \return
     *    A pointer to a new transport instance according to
     *    construction time specifications. The transport will be
     *    in state OPEN.
     **/
    IDisposableTransport* createTransport() IPL_NOEXCEPT;

    /**
     * \brief
     *     Returns a ptr. to the instance of the concrete factory
     **/
    const IFactory* getFactory() const IPL_NOEXCEPT
    {
        return m_concrete_factory;
    }

    //! whether construction succeeded
    bool isValid() const IPL_NOEXCEPT
    { return m_is_valid; }

protected: // functions
    /**
     * \brief
     *    creates a concrete transport instance based on the found
     *    configuration
     * \param[in] connection
     *    contains the settings for the transport connection
     * \return
     *    true on error, false otherwise
     **/
    bool processEntry(const ipl::string& cfg ) IPL_NOEXCEPT;

private:

    typedef ipl::map< ipl::string , IFactory::FactoryCreator > FactoryRegistry;
    FactoryRegistry m_registered_factories;
    void registerFactories();

protected: // data
    //! flag whether construction succeeded or not
    bool m_is_valid;

    //! The actual factory that handles creation of the transport
    IFactory *m_concrete_factory;
}; // class SimpleFactory

} // end namespace transport
} // end namespace util

#endif
