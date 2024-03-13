/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEAC_HXX
#define PERSISTENCE_IPERSISTENCEAC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <persistence/StructPartitionHandle.hxx>
#include <persistence/Definitions.hxx>

namespace persistence
{

    /**
    \brief The persistence::IPersistenceA interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class IPersistenceAC
    {
    public:
        // List of request methods
        /**
            
            \brief Open partition \a number for this \a version

            If the partition doesn't exist yet, it gets created with \a version.
            If the partition already exists with a different version, this fails.
        
            open Method ID: 49
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool open(
            const uint32_t number,
            const CIPtr< CIString >& version
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Open partition \a number at \a profile for this \a version

            If the partition doesn't exist yet, it gets created with \a version.
            If the partition already exists with a different version, this fails.
        
            open Method ID: 50
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool open(
            const uint32_t number,
            const uint32_t profile,
            const CIPtr< CIString >& version
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Open partition \a name for this \a version

            \b Note: \a name mustn't be the empty string.

            If the partition doesn't exist yet, it gets created with \a version.
            If the partition already exists with a different version, this fails.
        
            open Method ID: 47
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
            
            \brief Open partition \a name at \a profile for this \a version

            \b Note: \a name mustn't be the empty string.

            If the partition doesn't exist yet, it gets created with \a version.
            If the partition already exists with a different version, this fails.
        
            open Method ID: 48
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool open(
            const CIPtr< CIString >& name,
            const uint32_t profile,
            const CIPtr< CIString >& version
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool convert(
            const uint32_t number,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool convert(
            const uint32_t number,
            const uint32_t profile,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool convert(
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool convert(
            const CIPtr< CIString >& name,
            const uint32_t profile,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Close partition

            After sucessfully closing, the \a handle is invalid.
        
            close Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool close(
            const CIPtr< persistence::PartitionHandle >& handle
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get current version of partition \a number
        
            version Method ID: 77
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool version(
            const uint32_t number
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get current version of partition \a number at \a profile
        
            version Method ID: 78
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool version(
            const uint32_t number,
            const uint32_t profile
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get current version of partition \a name
        
            version Method ID: 75
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool version(
            const CIPtr< CIString >& name
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get current version of partition \a name at \a profile
        
            version Method ID: 76
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool version(
            const CIPtr< CIString >& name,
            const uint32_t profile
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Destroy partition \a number

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 57
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool purge(
            const uint32_t number
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Destroy partition \a number at \a profile

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 58
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool purge(
            const uint32_t number,
            const uint32_t profile
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Destroy partition \a name

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 55
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool purge(
            const CIPtr< CIString >& name
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Destroy partition \a name at \a profile

            \b Note: Partition must not be open, else the result is undefined.

            \b Note: It is OK to purge a non-existing partition.
        
            purge Method ID: 56
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool purge(
            const CIPtr< CIString >& name,
            const uint32_t profile
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Copy the opened partition behind \a from_handle to
            unopened partition \a to_number

            \b Note: If target partition exists, it is replaced by the copy
            \b Note: Target partition must not be open, else the result is undefined.
        
            copy Method ID: 15
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool copy(
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const uint32_t to_number
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Copy the opened partition behind \a from_handle to
            unopened partition \a to_number at \a to_profile

            \b Note: If target partition exists, it is replaced by the copy
            \b Note: Target partition must not be open, else the result is undefined.
        
            copy Method ID: 16
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool copy(
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const uint32_t to_number,
            const uint32_t to_profile
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Copy the opened partition behind \a from_handle to
            unopened partition \a to_name

            \b Note: \a name mustn't be the empty string.

            \b Note: If target partition exists, it is replaced by the copy

            \b Note: Target partition must not be open, else the result is undefined.
        
            copy Method ID: 13
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool copy(
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const CIPtr< CIString >& to_name
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Copy the opened partition behind \a from_handle to
            unopened partition \a to_name at \a to_profile

            \b Note: \a name mustn't be the empty string.

            \b Note: If target partition exists, it is replaced by the copy

            \b Note: Target partition must not be open, else the result is undefined.
        
            copy Method ID: 14
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool copy(
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const CIPtr< CIString >& to_name,
            const uint32_t to_profile
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool beginTransaction(
            const CIPtr< persistence::PartitionHandle >& handle
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool endTransaction(
            const CIPtr< persistence::PartitionHandle >& handle,
            const bool flush
        ) const IPL_NOEXCEPT = 0;

        /**
            endTransaction Method ID: 21
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool endTransaction(
            const CIPtr< persistence::PartitionHandle >& handle
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
        
            flush Method ID: 26
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
        
            exists Method ID: 24
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool exists(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Remove entry from persistence
        
            remove Method ID: 63
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool remove(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Set integer entry, create if needed

            Success or failure is reported via setResult reply.
            Additional intValues calls may are triggered to all subscribed
            clients, but setResult comes first.
        
            setInt Method ID: 66
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setInt(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const uint32_t val
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get integer value

            If no value can be provided before some point in time no later than
            \a timeout, the request fails.
            \a timeout can be a non-negative number of milliseconds or an
            importance classification and defaults to ESSENTIAL_VALUE.
        
            getInt Method ID: 35
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getInt(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            getInt Method ID: 34
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getInt(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getInts(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            getInts Method ID: 37
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getInts(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Set string entry, create if needed

            Success or failure is reported via setResult reply.
            Additional stringValues calls may are triggered to all subscribed
            clients, but setResult comes first.
        
            setString Method ID: 68
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setString(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const CIPtr< CIString >& val
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get string value

            If no value can be provided before some point in time no later than
            \a timeout, the request fails.
            \a timeout can be a non-negative number of milliseconds or an
            importance classification and defaults to ESSENTIAL_VALUE.
        
            getString Method ID: 41
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getString(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            getString Method ID: 40
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getString(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getStrings(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            getStrings Method ID: 43
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getStrings(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Set entry of binary data, create if needed

            Success or failure is reported via setResult reply.
            Additional blobValues calls may are triggered to all subscribed
            clients, but setResult comes first.
        
            setBlob Method ID: 65
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const CIPtr< CIUInt8Array >& val
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Get binary data

            If no value can be provided before some point in time no later than
            \a timeout, the request fails.
            \a timeout can be a non-negative number of milliseconds or an
            importance classification and defaults to ESSENTIAL_VALUE.
        
            getBlob Method ID: 29
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            getBlob Method ID: 28
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getBlob(
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getBlobs(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            getBlobs Method ID: 31
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getBlobs(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool subscribe(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            subscribe Method ID: 70
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool subscribe(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Stop being notified when values at \a keys change

            Success or failure is reported via unsubscribeResult reply.
        
            unsubscribe Method ID: 72
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unsubscribe(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Stop being notified when \e any value in the partition changes

            Success or failure is reported via unsubscribeResult reply.
        
            unsubscribeAll Method ID: 73
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unsubscribeAll(
            const CIPtr< persistence::PartitionHandle >& handle
        ) const IPL_NOEXCEPT = 0;

        IPersistenceAC()  {}
        virtual ~IPersistenceAC() {}
    protected:
        friend class IPersistenceAProxy;
    };

}//namespace persistence
#endif// PERSISTENCE_IPERSISTENCEAC_HXX
