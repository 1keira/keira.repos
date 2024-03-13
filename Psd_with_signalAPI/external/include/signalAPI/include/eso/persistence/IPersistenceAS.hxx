/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEAS_HXX
#define PERSISTENCE_IPERSISTENCEAS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <persistence/IPersistenceAServiceRegistration.hxx>
#include <persistence/StructPartitionHandle.hxx>

#include <persistence/Definitions.hxx>

#include <persistence/IPersistenceAProxyReply.hxx>
#include <persistence/IPersistenceAReplyS.hxx>

namespace persistence
{

    /**
    \brief  The persistence::IPersistenceA interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class IPersistenceAS
    {
    public:
        IPersistenceAS () {}
    // List of request methods
        /**
            
            \brief Open partition \a number for this \a version

            If the partition doesn't exist yet, it gets created with \a version.
            If the partition already exists with a different version, this fails.
        
            open Method ID: 49
        **/
        virtual void open(
            const uint32_t number,
            const CIPtr< CIString >& version
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Open partition \a number at \a profile for this \a version

            If the partition doesn't exist yet, it gets created with \a version.
            If the partition already exists with a different version, this fails.
        
            open Method ID: 50
        **/
        virtual void open(
            const uint32_t number,
            const uint32_t profile,
            const CIPtr< CIString >& version
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Open partition \a name for this \a version

            \b Note: \a name mustn't be the empty string.

            If the partition doesn't exist yet, it gets created with \a version.
            If the partition already exists with a different version, this fails.
        
            open Method ID: 47
        **/
        virtual void open(
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Open partition \a name at \a profile for this \a version

            \b Note: \a name mustn't be the empty string.

            If the partition doesn't exist yet, it gets created with \a version.
            If the partition already exists with a different version, this fails.
        
            open Method ID: 48
        **/
        virtual void open(
            const CIPtr< CIString >& name,
            const uint32_t profile,
            const CIPtr< CIString >& version
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Open partition \a number for conversion
            \a from_version \a to_version

            If the partition doesn't exist yet, it gets created with
            \a to_version on commit.
            If the partition already exists with a different version, this fails.
            
            This is not your normal open(), instead a transaction is started
            implicitly.
            Closing the convert without committing the transaction
            (via endTransaction()) \e rolls \e back the conversion.
            After endTransaction() the conversion (i.e. the handle) cannot be
            used anymore -- close it and open the newly converted Partition
            normally.
        
            convert Method ID: 7
        **/
        virtual void convert(
            const uint32_t number,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Open partition \a number at \a profile for conversion
            \a from_version \a to_version

            If the partition doesn't exist yet, it gets created with \a to_version
            on commit.
            If the partition already exists with a different version, this fails.
            
            This is not your normal open(), instead a transaction is started
            implicitly.
            Closing the convert without committing the transaction
            (via endTransaction()) \e rolls \e back the conversion.
            After endTransaction() the conversion (i.e. the handle) cannot be
            used anymore -- close it and open the newly converted Partition
            normally.
        
            convert Method ID: 8
        **/
        virtual void convert(
            const uint32_t number,
            const uint32_t profile,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Open partition \a name for conversion
            \a from_version \a to_version

            If the partition doesn't exist yet, it gets created with \a to_version
            on commit.
            If the partition already exists with a different version, this fails.
            
            This is not your normal open(), instead a transaction is started
            implicitly.
            Closing the convert without committing the transaction
            (via endTransaction()) \e rolls \e back the conversion.
            After endTransaction() the conversion (i.e. the handle) cannot be
            used anymore -- close it and open the newly converted Partition
            normally.
        
            convert Method ID: 5
        **/
        virtual void convert(
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Open partition \a name at \a profile for conversion
            \a from_version \a to_version

            If the partition doesn't exist yet, it gets created with \a to_version
            on commit.
            If the partition already exists with a different version, this fails.
            
            This is not your normal open(), instead a transaction is started
            implicitly.
            Closing the convert without committing the transaction
            (via endTransaction()) \e rolls \e back the conversion.
            After endTransaction() the conversion (i.e. the handle) cannot be 
            used anymore -- close it and open the newly converted Partition
            normally.
        
            convert Method ID: 6
        **/
        virtual void convert(
            const CIPtr< CIString >& name,
            const uint32_t profile,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Close partition

            After sucessfully closing, the \a handle is invalid.
        
            close Method ID: 3
        **/
        virtual void close(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get current version of partition \a number
        
            version Method ID: 77
        **/
        virtual void version(
            const uint32_t number
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get current version of partition \a number at \a profile
        
            version Method ID: 78
        **/
        virtual void version(
            const uint32_t number,
            const uint32_t profile
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get current version of partition \a name
        
            version Method ID: 75
        **/
        virtual void version(
            const CIPtr< CIString >& name
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get current version of partition \a name at \a profile
        
            version Method ID: 76
        **/
        virtual void version(
            const CIPtr< CIString >& name,
            const uint32_t profile
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Destroy partition \a number

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 57
        **/
        virtual void purge(
            const uint32_t number
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Destroy partition \a number at \a profile

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 58
        **/
        virtual void purge(
            const uint32_t number,
            const uint32_t profile
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Destroy partition \a name

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 55
        **/
        virtual void purge(
            const CIPtr< CIString >& name
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Destroy partition \a name at \a profile

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 56
        **/
        virtual void purge(
            const CIPtr< CIString >& name,
            const uint32_t profile
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Copy the opened partition behind \a from_handle to
            unopened partition \a to_number

            \b Note: If target partition exists, it is replaced by the copy
            \b Note: Target partition must not be open, else the result is undefined.
        
            copy Method ID: 15
        **/
        virtual void copy(
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const uint32_t to_number
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Copy the opened partition behind \a from_handle to
            unopened partition \a to_number at \a to_profile

            \b Note: If target partition exists, it is replaced by the copy
            \b Note: Target partition must not be open, else the result is undefined.
        
            copy Method ID: 16
        **/
        virtual void copy(
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const uint32_t to_number,
            const uint32_t to_profile
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Copy the opened partition behind \a from_handle to
            unopened partition \a to_name

            \b Note: \a name mustn't be the empty string.

            \b Note: If target partition exists, it is replaced by the copy

            \b Note: Target partition must not be open, else the result is undefined.
        
            copy Method ID: 13
        **/
        virtual void copy(
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const CIPtr< CIString >& to_name
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Copy the opened partition behind \a from_handle to
            unopened partition \a to_name at \a to_profile

            \b Note: \a name mustn't be the empty string.

            \b Note: If target partition exists, it is replaced by the copy

            \b Note: Target partition must not be open, else the result is undefined.
        
            copy Method ID: 14
        **/
        virtual void copy(
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const CIPtr< CIString >& to_name,
            const uint32_t to_profile
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Start an atomic group of writes

            A transaction is required for the remove and setX methods to succeed.
            Its effect is that all changes made during the transaction will be
            committed or thrown away in one go at the end of the transaction
            (endTransaction()).
            There is no guarantee of durability, i.e. the changes can still
            get lost on power failure later, but they are guaranteed to
            get lost atomically, i.e. either none or all.

            At each moment there can be at most one transaction be active on the
            same partition handle.
            Starting a second one fails.

            The effect of transactions on reading, i.e. on the getX methods is
            partly undefined.
            Reading before starting the transaction obviously yields the old
            value, and reading after successfully ending the transaction yields
            the new value, but reading during the transaction might yield
            either one, depending on implementation details and phase of moon.
        
            beginTransaction Method ID: 0
        **/
        virtual void beginTransaction(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief End an atomic group of writes and try to commit the changes

            This tries to commit the changes made during the current transaction.
            This might succeed or fail (atomically),
            but the transaction is always ended.

            If \a flush is present and \c true, the partition is flushed
            right after committing as if flush() was called (but without
            calling flushResult()).

            \b Note: \a flush is reserved for special cases where the customer's
            spec explicitly states that the values written must not be lost
            on power failure.
            If you use it excessively, flash wear might cause premature hardware
            failure, which is too expensive as that you would like to be the one
            to blame.

            Calling this while no transaction is pending yields an error.
        
            endTransaction Method ID: 22
        **/
        virtual void endTransaction(
            const CIPtr< persistence::PartitionHandle >& handle,
            const bool flush
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            endTransaction Method ID: 21
        **/
        virtual void endTransaction(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceAProxyReply& reply
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
        
            flush Method ID: 26
        **/
        virtual void flush(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Check whether some persistence entry exists
        
            exists Method ID: 24
        **/
        virtual void exists(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Remove entry from persistence
        
            remove Method ID: 63
        **/
        virtual void remove(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Set integer entry, create if needed

            Success or failure is reported via setResult reply.
            Additional intValues calls may are triggered to all subscribed
            clients, but setResult comes first.
        
            setInt Method ID: 66
        **/
        virtual void setInt(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const uint32_t val
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get integer value

            If no value can be provided before some point in time no later than
            \a timeout, the request fails.
            \a timeout can be a non-negative number of milliseconds or an
            importance classification and defaults to ESSENTIAL_VALUE.
        
            getInt Method ID: 35
        **/
        virtual void getInt(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const int32_t timeout
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            getInt Method ID: 34
        **/
        virtual void getInt(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get multiple integer values

            This is guaranteed to return as many values and results as requested.
            Of course each value may individually be invalid due to an individual
            error (e.g. key doesn't exist).

            If no value can be provided before some point in time no later than
            \a timeout, the request fails (individually).
            \a timeout can be a non-negative number of milliseconds
            or an importance classification and defaults to ESSENTIAL_VALUE.
        
            getInts Method ID: 38
        **/
        virtual void getInts(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const int32_t timeout
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            getInts Method ID: 37
        **/
        virtual void getInts(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Set string entry, create if needed

            Success or failure is reported via setResult reply.
            Additional stringValues calls may are triggered to all subscribed
            clients, but setResult comes first.
        
            setString Method ID: 68
        **/
        virtual void setString(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const CIPtr< CIString >& val
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get string value

            If no value can be provided before some point in time no later than
            \a timeout, the request fails.
            \a timeout can be a non-negative number of milliseconds or an
            importance classification and defaults to ESSENTIAL_VALUE.
        
            getString Method ID: 41
        **/
        virtual void getString(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const int32_t timeout
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            getString Method ID: 40
        **/
        virtual void getString(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get multiple string values

            This is guaranteed to return as many values and results as requested.
            Of course each value may individually be invalid due to an individual
            error (e.g. key doesn't exist).

            If no value can be provided before some point in time no later than
            \a timeout, the request fails (individually).
            \a timeout can be a non-negative number of milliseconds
            or an importance classification and defaults to ESSENTIAL_VALUE.
        
            getStrings Method ID: 44
        **/
        virtual void getStrings(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const int32_t timeout
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            getStrings Method ID: 43
        **/
        virtual void getStrings(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Set entry of binary data, create if needed

            Success or failure is reported via setResult reply.
            Additional blobValues calls may are triggered to all subscribed
            clients, but setResult comes first.
        
            setBlob Method ID: 65
        **/
        virtual void setBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const CIPtr< CIUInt8Array >& val
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get binary data

            If no value can be provided before some point in time no later than
            \a timeout, the request fails.
            \a timeout can be a non-negative number of milliseconds or an
            importance classification and defaults to ESSENTIAL_VALUE.
        
            getBlob Method ID: 29
        **/
        virtual void getBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const int32_t timeout
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            getBlob Method ID: 28
        **/
        virtual void getBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Get multiple binary data blocks

            This is guaranteed to return as many values and results as requested.
            Of course each value may individually be invalid due to an individual
            error (e.g. key doesn't exist).

            If no value can be provided before some point in time no later than
            \a timeout, the request fails (individually).
            \a timeout can be a non-negative number of milliseconds
            or an importance classification and defaults to ESSENTIAL_VALUE.
        
            getBlobs Method ID: 32
        **/
        virtual void getBlobs(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const int32_t timeout
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            getBlobs Method ID: 31
        **/
        virtual void getBlobs(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Subscribe for being notified when \a keys change, triggering
            a guaranteed initial notification

            If no initial value can be provided before some point in time no later than
            \a timeout, the initial notification fails (yields PERS_RESULT_TIMEOUT).
            \a timeout can be a non-negative number of milliseconds
            or an importance classification and defaults to ESSENTIAL_VALUE.

            Note that subscribing for a non-existing entry is legal and succeeds.
            The initial notification will convey a status of
            PERS_STATUS_DOES_NOT_EXIST, but subsequent writes will be notified of
            normally.
        
            subscribe Method ID: 71
        **/
        virtual void subscribe(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const int32_t timeout
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            subscribe Method ID: 70
        **/
        virtual void subscribe(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Stop being notified when values at \a keys change

            Success or failure is reported via unsubscribeResult reply.
        
            unsubscribe Method ID: 72
        **/
        virtual void unsubscribe(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
            ,IPersistenceAProxyReply& reply
        ) = 0;
        /**
            
            \brief Stop being notified when \e any value in the partition changes

            Success or failure is reported via unsubscribeResult reply.
        
            unsubscribeAll Method ID: 73
        **/
        virtual void unsubscribeAll(
            const CIPtr< persistence::PartitionHandle >& handle
            ,IPersistenceAProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,IPersistenceAProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,IPersistenceAProxyReply& reply
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
                IPersistenceAServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), instance_no), static_cast<IPersistenceAS*>(this), l, factory );
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
                IPersistenceAServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), instance_no), static_cast<IPersistenceAS*>(this), l );
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
            m_registration = IPersistenceAServiceRegistration();
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
            IPersistenceAServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = IPersistenceAServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~IPersistenceAS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        open_U32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 49;
            ce.assign(inst, mid);
        }
        void
        open_U32_U32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 50;
            ce.assign(inst, mid);
        }
        void
        open_S_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 47;
            ce.assign(inst, mid);
        }
        void
        open_S_U32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 48;
            ce.assign(inst, mid);
        }
        void
        convert_U32_S_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }
        void
        convert_U32_U32_S_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        convert_S_S_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }
        void
        convert_S_U32_S_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        closeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }
        void
        version_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 77;
            ce.assign(inst, mid);
        }
        void
        version_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 78;
            ce.assign(inst, mid);
        }
        void
        version_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 75;
            ce.assign(inst, mid);
        }
        void
        version_S_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 76;
            ce.assign(inst, mid);
        }
        void
        purge_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 57;
            ce.assign(inst, mid);
        }
        void
        purge_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 58;
            ce.assign(inst, mid);
        }
        void
        purge_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 55;
            ce.assign(inst, mid);
        }
        void
        purge_S_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 56;
            ce.assign(inst, mid);
        }
        void
        copy_PartitionHandle_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }
        void
        copy_PartitionHandle_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }
        void
        copy_PartitionHandle_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }
        void
        copy_PartitionHandle_S_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }
        void
        beginTransactionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        endTransaction_PartitionHandle_BCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }
        void
        endTransaction_PartitionHandleCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }
        void
        flushCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 26;
            ce.assign(inst, mid);
        }
        void
        existsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 24;
            ce.assign(inst, mid);
        }
        void
        removeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 63;
            ce.assign(inst, mid);
        }
        void
        setIntCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 66;
            ce.assign(inst, mid);
        }
        void
        getInt_PartitionHandle_U32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 35;
            ce.assign(inst, mid);
        }
        void
        getInt_PartitionHandle_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 34;
            ce.assign(inst, mid);
        }
        void
        getInts_PartitionHandle_aU32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 38;
            ce.assign(inst, mid);
        }
        void
        getInts_PartitionHandle_aU32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 37;
            ce.assign(inst, mid);
        }
        void
        setStringCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 68;
            ce.assign(inst, mid);
        }
        void
        getString_PartitionHandle_U32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 41;
            ce.assign(inst, mid);
        }
        void
        getString_PartitionHandle_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 40;
            ce.assign(inst, mid);
        }
        void
        getStrings_PartitionHandle_aU32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 44;
            ce.assign(inst, mid);
        }
        void
        getStrings_PartitionHandle_aU32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 43;
            ce.assign(inst, mid);
        }
        void
        setBlobCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 65;
            ce.assign(inst, mid);
        }
        void
        getBlob_PartitionHandle_U32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 29;
            ce.assign(inst, mid);
        }
        void
        getBlob_PartitionHandle_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 28;
            ce.assign(inst, mid);
        }
        void
        getBlobs_PartitionHandle_aU32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32;
            ce.assign(inst, mid);
        }
        void
        getBlobs_PartitionHandle_aU32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 31;
            ce.assign(inst, mid);
        }
        void
        subscribe_PartitionHandle_aU32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 71;
            ce.assign(inst, mid);
        }
        void
        subscribe_PartitionHandle_aU32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 70;
            ce.assign(inst, mid);
        }
        void
        unsubscribeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 72;
            ce.assign(inst, mid);
        }
        void
        unsubscribeAllCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 73;
            ce.assign(inst, mid);
        }

    protected:
        IPersistenceAServiceRegistration m_registration;
    };

} //namespace persistence
#endif// PERSISTENCE_IPERSISTENCEAS_HXX
