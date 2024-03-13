/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEBS_HXX
#define PERSISTENCE_IPERSISTENCEBS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <persistence/IPersistenceBServiceRegistration.hxx>
#include <persistence/StructPartitionHandle.hxx>

#include <persistence/Definitions.hxx>

#include <persistence/IPersistenceBProxyReply.hxx>
#include <persistence/IPersistenceBReplyS.hxx>

namespace persistence
{

    /**
    \brief  The persistence::IPersistenceB interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class IPersistenceBS
    {
    public:
        IPersistenceBS () {}
    // List of request methods
        /**
            open Method ID: 11
        **/
        virtual void open(
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Close partition

            After sucessfully closing, the \a handle is invalid.
        
            close Method ID: 0
        **/
        virtual void close(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Get current version of partition \a name
        
            version Method ID: 21
        **/
        virtual void version(
            const CIPtr< CIString >& name
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Destroy partition \a name

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 13
        **/
        virtual void purge(
            const CIPtr< CIString >& name
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Flush all changes to persistent storage

            Needs to be called \e outside any transaction, i.e. right after
            endTransaction().

            \b Note: This is reserved for special cases where the customer's
            spec explicitly states that the values written must not be lost
            on power failure.
            If you use this excessively, flash wear might cause premature hardware
            failure, which is too expensive as that you would like to be the one
            to blame.
        
            flush Method ID: 4
        **/
        virtual void flush(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Check whether some persistence entry exists
        
            exists Method ID: 2
        **/
        virtual void exists(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Remove entry from persistence
        
            remove Method ID: 15
        **/
        virtual void remove(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Set entry of binary data, create if needed

            Success or failure is reported via setResult reply.
            Additional blobValues calls may are triggered to all subscribed
            clients, but setResult comes first.
        
            setBlob Method ID: 19
        **/
        virtual void setBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const CIPtr< CIUInt8Array >& val
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Get binary data

            If no value can be provided before some point in time no later than
            \a timeout, the request fails.
            \a timeout can be a non-negative number of milliseconds or an
            importance classification and defaults to ESSENTIAL_VALUE.
        
            getBlob Method ID: 9
        **/
        virtual void getBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const int32_t timeout
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            getBlob Method ID: 8
        **/
        virtual void getBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Request all existing keys on this partition
        
            getAllKeys Method ID: 6
        **/
        virtual void getAllKeys(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceBProxyReply& reply
        ) = 0;
        /**
            
            \brief Remove all entries from persistence.

            In contrast to purge, the partition stays valid
            as well as all open connections to that partition.

            \see purge
        
            removeAll Method ID: 16
        **/
        virtual void removeAll(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceBProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,IPersistenceBProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,IPersistenceBProxyReply& reply
        ) {}

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service.
        \param  p a user provided ActiveObject factory. This gives control over the threads that call the service.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, const comm::ActiveObjectFactoryPtr& factory, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                IPersistenceBServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), instance_no), static_cast<IPersistenceBS*>(this), l, factory );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface.
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                IPersistenceBServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), instance_no), static_cast<IPersistenceBS*>(this), l );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener& l)
        {
            return registerSelf (instance_no, &l);
        }

        /*!
        \brief  Unregisters this service instance.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                none
        */
        bool unregisterSelf()
        {
            if (!m_registration.isAlive()) {
                // not registered -> nothing to do.
                return false;
            }
            m_registration.unregisterService();
            // must not be alive after unregistration
            IPL_ASSERT(!m_registration.isAlive());
            // let go of the reference
            m_registration = IPersistenceBServiceRegistration();
            return false;
        }

        /*!
        \brief  Unregisters this service instance and calls a callback.
        \return false if the service is being unregistered, true on error
                The callback is called only if false is returned.
                Errors are:
                <ul>
                <li>the service registration is not valid
                <li>an unregisterSelf() or ServiceRegistration::unregisterService() or
                    or ServiceRegistration::unregisterAndNotify had already been called.
                <li>the callback is NULL.
                </ul>
        \errorindicator
                return code
        \errors
                \see comm::ServiceRegistration::unregisterAndNotify
        */
        bool unregisterSelf(comm::ServiceReleasedFct callback, void* ctx) // NOSONAR - must not be changed because of API compatibility
        {
            // to not race with the callback. we can't touch m_registration after
            // calling unregisterAndNotify
            // make a temporary copy
            IPersistenceBServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = IPersistenceBServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~IPersistenceBS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        openCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }
        void
        closeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        versionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }
        void
        purgeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }
        void
        flushCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        existsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        removeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }
        void
        setBlobCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }
        void
        getBlob_PartitionHandle_S_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }
        void
        getBlob_PartitionHandle_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        getAllKeysCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        removeAllCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }

    protected:
        IPersistenceBServiceRegistration m_registration;
    };

} //namespace persistence
#endif// PERSISTENCE_IPERSISTENCEBS_HXX
