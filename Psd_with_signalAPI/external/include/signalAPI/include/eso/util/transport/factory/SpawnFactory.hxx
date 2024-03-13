/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SPAWNFACTORY_HXX
#define UTIL_TRANSPORT_SPAWNFACTORY_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <iplbase/exceptions.hxx>
#include <common/types/vector.hxx>
#include <common/types/map.hxx>
#include <common/types/string.hxx>

#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <util/transport/ITransport.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <util/transport/factory/ISpawnFactory.hxx>
#include <util/Thread.hxx>

namespace util
{
namespace transport
{

/**
 * \brief
 *     Create server side transports using a spawning transport
 *     mechanism

 *     A spawning transport is a transport that is able to let clients
 *     connect to a single server side transport instance and then
 *     spawns an individual server-client connection.
 *
 *     The SpawnFactory is only used on the server side. It is
 *     constructed using transport service identifiers (like "comm" or
 *     "tracing"). Additionally a callback interface for newly
 *     registered transports has to be specified. The factory is then
 *     set active via enableSpawning(). As soon as new client
 *     connections are established by the factory a callback providing
 *     the associated IDisposableTransport instance is done at the
 *     specified callback interface.
**/
class UTIL_EXPORT SpawnFactory :
    // thread interface
    public util::IRunnable
{
public: // subclasses / fwd. decl. / types

    //! different factory strategies what to do on creation errors
    enum CreationErrorStrategy
    {
        //! \brief
        //! discard the factory, doing an asynchronous error
        //! callback an once
        SHUTDOWN_FACTORY,
        /**
         * \brief
         *  Let the factory retry creation in an implementation
         *  defined manner

         *  The details of how retries are performed may be
         *  hard-wired into the spawn factory implementation or
         *  determined via transport configuration.
         *
         *  In this mode the creationError() callback will never
         *  be called but the errors will be transparently
         *  handled by the factory itself. Even if further
         *  creation of transports is given up at some point.
         **/
        RETRY_CREATION,
        //! \brief
        //! let the error callback decide what to do
        //! \see
        //! ISpawnHandler::setRetry(const bool, const
        //! uint_fast32_t)
        CALLBACK_DRIVEN
    };

    /**
     * \brief
     *     Callback interface for newly spawned client transports
     * \note
     *    One instance of ISpawnHandler should only be registered
     *    at one instance of SpawnFactory at any given time.
     **/
    class ISpawnHandler
    {
    public: // types
        //! \brief
        //! settings to control retry behaviour in case of
        //! creation errors
        struct RetrySettings
        {
            //! \brief
            //! whether to keep trying creation of new
            //! transports
            bool keep_trying;
            //! \brief
            //! time in milliseconds to wait before the next
            //! creation attempt
            uint_fast32_t retry_ms;
        };
    protected: // functions
        ISpawnHandler() IPL_NOEXCEPT : m_parent(NULL) { };

        virtual ~ISpawnHandler() IPL_NOEXCEPT { };

        /**
         * \brief
         *     A new client has connected to the spawning
         *     transport

         *     This function will be called asynchronously by
         *     the associated SpawnFactory as soon as a new
         *     connection from a client has been successfully made.
         *
         *     This callback is called concurrently for different
         *     concrete transport endpoints. E.g. if this factory
         *     manages incoming transports for several tcp addresses
         *     and unix domain sockets, callbacks for these endpoints
         *     are called concurrently.
         *     Callbacks for the same endpoint are sequential.
         *
         *     The ownership of the transport \c t is passed on
         *     to the callee. The transport needs to be closed
         *     via calling its close() function when it isn't
         *     needed any more. The transport needs to be freed
         *     by calling its dispose() function.
         * \param[in] factory
         *     The factory from which the new transport \c t
         *     has been spawned.
         * \param[in] t
         *     The newly connected transport instance. It will
         *     be in state OPEN.
         **/
        virtual void newTransport(const ISpawnFactory &factory,
            IDisposableTransport &t) = 0;

        /**
         * \brief
         *     One of the configured transport facilities
         *     caused an error during creation

         *     This is for asynchronous dispatching of an error
         *     that occured during an attempt to create a new
         *     transport.
         *
         *     Whether the underlying thread in SpawnFactory
         *     that is associated with the concrete factory that
         *     caused the error will try to spawn new clients
         *     depends on the CreationErrorStrategy that was
         *     set at the SpawnFactory.
         *
         *     If the set strategy is SHUTDOWN_FACTORY then the
         *     thread will no longer attempt to create new
         *     transports and shut down.
         *
         *     If the set strategy is RETRY_CREATION then this
         *     callback will not be called at all.
         *
         *     If the set strategy is CALLBACK_DRIVEN then the
         *     settings inc \c retry_settings determine the
         *     further creation attempts of the spawn factory.
         *     For other strategies \c retry_settings is
         *     ignored.
         *
         *     If factory->isEnabled() returns \c false then
         *     the error is concerned the creation or enabling
         *     of \c factory.
         * \param[in] factory
         *     The factory at which creation failed
         * \errors
         *     The errors specified at
         *     ITransport::createTransport() attached with
         *     transport implementation dependent errors can
         *     occur here
         **/
        virtual void creationError(
            const ISpawnFactory &factory,
            struct RetrySettings &retry_settings) = 0;

        /**
         * \brief
         *    One of the concrete spawning factories has gone
         *    online
         *
         **/
        virtual void factoryOnline(
            const ISpawnFactory &factory)
        { }

        /**
         * \brief
         *     One of the concrete spawning factories has gone
         *     offline
         **/
        virtual void factoryOffline(
            const ISpawnFactory &factory)
        { }

    private:
        // needs access to m_parent
        friend class SpawnFactory;
        //! \brief
        //! A pointer to the factory that this interface is
        //! associated with
        SpawnFactory *m_parent;
    };

public: // methods
    /**
     * \brief
     *     Construct a spawn factory for the given set of
     *     identifiers.

     *     The name of the process is not needed for connection
     *     specification here.  This is as SpawnFactory is for
     *     server operation only and thus the current process name
     *     is selected.
     *
     *     if \c link is set to an empty string then all defined
     *     links for \c user are considered by the factory.
     *
     *     If more than one link is matched in case of \c link
     *     being an empty string and one or more of those links
     *     caused errors than the factory will not be constructed
     *     and an according error is raised, even if some of the
     *     links might have had a valid configuration.
     * \param[in] handler
     *     An instance of the callback interface that will be
     *     called upon new client connections. This instance should
     *     not be registered at a different SpawnFactory instance
     *     already.
     * \param[in] service
     *     The name of the application/user of the transport (e.g
     *     comm, tracing)
     * \param[in] strategy
     *     Determines how creation errors at a concrete factory are
     *     handled. See \c CreationErrorStrategy.
     * \errorindicator
     *     via isValid()
     * \errors
     *     FactoryError
     **/
    SpawnFactory(ISpawnHandler &handler
                ,const ipl::vector< ipl::string >& configs
                ,const CreationErrorStrategy strategy) IPL_NOEXCEPT;

    /**
     * \brief
     *     Construct a spawn factory for the given pre-determined
     *     transport parameters

     *     In contract to the other constructor variant this
     *     constructor does not lookup transport parameter in the
     *     configuration system but instead uses hard-coded
     *     pre-determined information given in \c descriptor.
     *
     *     This is useful for more simple setups like in test
     *     environments where the need for configuration files is
     *     hindering the ease of use.
     *
     *     Apart from that the effects of this constructor are
     *     equal to the other constructor.
     **/
    SpawnFactory(
        ISpawnHandler &handler,
        const CreationErrorStrategy strategy,
        const ipl::string& cfg
        ) IPL_NOEXCEPT;

    //! creates an invalid SpawnFactory associated with \c handler
    SpawnFactory(
        ISpawnHandler &handler) IPL_NOEXCEPT :
        m_is_valid(),
        m_spawn_handler(handler),
        m_async_call(),
        m_error_strategy(SHUTDOWN_FACTORY)
    { }

    /**
     * \brief
     *     Checks that no transport instances are left over. Checks
     *     that spawning is disabled.

     *     In debug mode the destructor asserts that no transports
     *     created by the factory are still out there (i.e. all
     *     transports have been returned to the factory).
     *
     *     Also it will be asserted that spawning has been disabled
     *     before the destructor was called.
     **/
    ~SpawnFactory() IPL_NOEXCEPT
    {
        cleanup();
    }

    /**
     * \brief
     *     Enable spawning operation thereby allowing new client
     *     connections to be spawned.

     *     Before this function is called no new connections can be
     *     spawned and no calls to the associated ISpawnHandler
     *     interface are performed.
     *
     *     Before a SpawnFactory instance is destroyed
     *     disableSpawning() needs to be called, if spawning was
     *     previously enabled.
     *
     *     If enableSpawning() is called more than once than no
     *     error will occur but nothing will be done during any
     *     additional calls.
     * \param[in] factory
     *     If set to a valid factory object then only this specific
     *     factory will be enabled. If set to NULL then all
     *     factories will be enabled.
     * \errorindicator
     *     via return code (true on error)
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - INVALID_USAGE if enableSpawning is called after
     *     disableSpawning() has been called.
     *
     *     Also any errors as specified in util::Thread::start()
     **/
    bool enableSpawning(const ISpawnFactory *factory = NULL) IPL_NOEXCEPT;

    /**
     * \brief
     *     Disable spawning operation.

     *     When spawning is currently enabled then
     *     disableSpawning() disallows further client connections
     *     to be spawned. After return of this function no more
     *     calls to the associated ISpawnHandler will be performed.
     *
     *     After one cycle of enableSpawning() and
     *     disableSpawning(), future calls to enableSpawning() will
     *     fail. To resetup an active spawning factory you need to
     *     return any still active spawned transport instances,
     *     destroy the inactive SpawnFactory instance and setup a
     *     new SpawnFactory.
     *
     *     A call to disableSpawning() performed while spawning
     *     isn't enabled at all is not handled as an error. Nothing
     *     will happen in this case.
     * \param[in] factory
     *     If set to a valid factory object then only this specific
     *     factory will be disabled. If set to NULL then all
     *     factories will be disabled.
     * \errors
     *     none (aborts on error)
     **/
    void disableSpawning(const ISpawnFactory *factory = NULL) IPL_NOEXCEPT;

    /**
     * \brief
     *     return the state of the factory, whether it's valid
     *     (successfully created) or not. Reason for invalidation
     *     may be an invalid configuration
     **/
    bool isValid() const IPL_NOEXCEPT
    { return m_is_valid; }

    //! \brief
    //! returns a copy of the set of the registered concrete
    //! factories
    const ipl::set<ISpawnFactory*> getFactories() const IPL_NOEXCEPT
    {
        MutexGuard guard(m_lock);
        return m_factories;
    }
protected: // functions
    //! entry functions for the connection handling threads
    virtual void threadLoop(const Thread* const);

    /**
     * \brief
     *     Called by threads in case of transport creation error to
     *     handle the situation
     * \return
     *     \c true if thread is to continue attempting creating a
     *     transport, \c false if it is to give up
     **/
    bool handleFactoryError(ISpawnFactory *factory,
        util::Thread &thread) IPL_NOEXCEPT;

    /**
     * \brief
     *     Process one transport connection configuration entry

     *     Processes the given configuration entry by doing the
     *     following steps:
     *
     *     - create the according concrete factory for this link
     *     - create a thread associated with the concrete factory
     *     - store thread, factory and the thread-factory
     *     association in the according data structure members.
     *
     *     On error condition errors will be raised according to
     *     constructor specifications (this function is expected to
     *     be called from the constructor)
     * \return
     *     true on error, false otherwise
    **/
    bool processEntry(const ipl::string& cfg) IPL_NOEXCEPT;


    //! free any ressources at destruction time
    void cleanup() IPL_NOEXCEPT;

    //! using this is deprecated, callbacks for different concrete factories are called concurrently.
    void prepareAsyncCall() IPL_NOEXCEPT;

    //! using this is deprecated, callbacks for different concrete factories are called concurrently.
    void finishAsyncCall() IPL_NOEXCEPT;

private:

    typedef ipl::map< ipl::string , ISpawnFactory::SpawnFactoryCreator > FactoryRegistry;
    FactoryRegistry m_registered_factories;
    void registerFactories();
protected: // data
    //! marker whether the factory was created successfully or not
    bool m_is_valid;

    //! \brief
    //! callback to the user, which is called each time something
    //! has changed
    ISpawnHandler &m_spawn_handler;

    //! threads that are connected to spawning transports
    ipl::set<util::Thread*> m_threads;

    //! all concrete factories needed
    ipl::set<ISpawnFactory*> m_factories;
    //! association of threads to factories
    ipl::map<util::Thread*, ISpawnFactory*> m_factory_assoc;

    //! Lock for all data structures
    osal::Mutex m_lock;

    //! Condition used to wait for an async call to start or end
    osal::Condition m_async_call_cond;

    //! \brief
    //! Set to true if an asynchorous call to m_spawn_handler is
    //! currently active
    bool m_async_call;

    //! the selected strategy for creation errors
    const CreationErrorStrategy m_error_strategy;
}; // class SpawnFactory

} // end namespace transport
} // end namespace util

#endif
