/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_IFACTORY_HXX
#define UTIL_TRANSPORT_IFACTORY_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <util/transport/ITransport.hxx>

namespace util
{

namespace transport
{

/**
 * \brief
 *    Interface for Transport Factories

 *     The actual user visible factories rely on concrete factories to
 *     actually produce transports.
 *
 *     These concrete factories need to implement this common interface
 *     for the abstract factories being able to generically operate on
 *     them.
**/
class UTIL_EXPORT IFactory
{
public: // functions

    IFactory() IPL_NOEXCEPT
    {}

    //! \brief
    //! virtual to make sure derived-class destructor is always
    //! called
    virtual ~IFactory() IPL_NOEXCEPT
    { };

    /**
     * \brief
     *    Return a new transport according to impl. defined
     *    specifications
     * \errorindicator
     *    On error NULL is returned
     * \errors
     *    FactoryError with IDs:
     *
     *    - CREATION_ERROR if the transport couldn't be created
     **/
    virtual IDisposableTransport* createTransport() IPL_NOEXCEPT = 0;

    /**
     * \brief
     *    Stop any blocking calls associated with the factory
     *
     *    Any blocking calls in createTransport() will be released
     *    and an error will be returned to the callers to notify
     *    them about the error condition.
     *
     *     The factory will cease to function after this call
     *     returned. It needs to be re-constructed to work again.
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code
     * \errors
     *    implementation defined
     **/
    virtual bool closeFactory() IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Returns the type of the factory implementation (the scheme of the factory url)
     *
     *     Using this information should be used with care as it
     *     weakens the factory abstraction layer. It is only
     *     provided for special situations like e.g. the error
     *     handling of asynchronous transport creation errors.
     **/
    virtual const char* factoryType() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Returns whether the factory is currently in a functional
     *     state and calls to createTransport() should work.
     **/
    virtual bool isValid() const IPL_NOEXCEPT = 0;

    typedef IFactory* (*FactoryCreator)(const ipl::string& config);
}; // class

} // end namespace transport
} // end namespace util

#endif
