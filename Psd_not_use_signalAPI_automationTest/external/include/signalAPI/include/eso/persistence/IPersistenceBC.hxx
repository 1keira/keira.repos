/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEBC_HXX
#define PERSISTENCE_IPERSISTENCEBC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <persistence/StructPartitionHandle.hxx>
#include <persistence/Definitions.hxx>

namespace persistence
{

    /**
    \brief The persistence::IPersistenceB interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class IPersistenceBC
    {
    public:
        // List of request methods
        /**
            open Method ID: 11
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool open(
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Close partition

            After sucessfully closing, the \a handle is invalid.
        
            close Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool close(
            const CIPtr< persistence::PartitionHandle >& handle
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get current version of partition \a name
        
            version Method ID: 21
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool version(
            const CIPtr< CIString >& name
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Destroy partition \a name

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 13
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool purge(
            const CIPtr< CIString >& name
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool flush(
            const CIPtr< persistence::PartitionHandle >& handle
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Check whether some persistence entry exists
        
            exists Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool exists(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Remove entry from persistence
        
            remove Method ID: 15
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool remove(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Set entry of binary data, create if needed

            Success or failure is reported via setResult reply.
            Additional blobValues calls may are triggered to all subscribed
            clients, but setResult comes first.
        
            setBlob Method ID: 19
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const CIPtr< CIUInt8Array >& val
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get binary data

            If no value can be provided before some point in time no later than
            \a timeout, the request fails.
            \a timeout can be a non-negative number of milliseconds or an
            importance classification and defaults to ESSENTIAL_VALUE.
        
            getBlob Method ID: 9
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            getBlob Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Request all existing keys on this partition
        
            getAllKeys Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getAllKeys(
            const CIPtr< persistence::PartitionHandle >& handle
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Remove all entries from persistence.

            In contrast to purge, the partition stays valid
            as well as all open connections to that partition.

            \see purge
        
            removeAll Method ID: 16
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool removeAll(
            const CIPtr< persistence::PartitionHandle >& handle
        ) const IPL_NOEXCEPT = 0;

        IPersistenceBC()  {}
        virtual ~IPersistenceBC() {}
    protected:
        friend class IPersistenceBProxy;
    };

}//namespace persistence
#endif// PERSISTENCE_IPERSISTENCEBC_HXX
