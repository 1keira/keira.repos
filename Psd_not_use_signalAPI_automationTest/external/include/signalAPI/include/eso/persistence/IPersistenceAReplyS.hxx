/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEA_REPLYS_HXX
#define PERSISTENCE_IPERSISTENCEA_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <persistence/StructPartitionHandle.hxx>
#include <persistence/Definitions.hxx>
namespace persistence
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class IPersistenceAReplyS
    {
    public:
        // List of reply methods
            /**
            openResult Method ID: 53
            **/
        virtual bool openResult (
            const uint32_t number,
            const CIPtr< CIString >& version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            openResult Method ID: 54
            **/
        virtual bool openResult (
            const uint32_t number,
            const uint32_t profile,
            const CIPtr< CIString >& version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            openResult Method ID: 51
            **/
        virtual bool openResult (
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            openResult Method ID: 52
            **/
        virtual bool openResult (
            const CIPtr< CIString >& name,
            const uint32_t profile,
            const CIPtr< CIString >& version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            convertResult Method ID: 11
            **/
        virtual bool convertResult (
            const uint32_t number,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            convertResult Method ID: 12
            **/
        virtual bool convertResult (
            const uint32_t number,
            const uint32_t profile,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            convertResult Method ID: 9
            **/
        virtual bool convertResult (
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            convertResult Method ID: 10
            **/
        virtual bool convertResult (
            const CIPtr< CIString >& name,
            const uint32_t profile,
            const CIPtr< CIString >& from_version,
            const CIPtr< CIString >& to_version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            closeResult Method ID: 4
            **/
        virtual bool closeResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            versionResult Method ID: 81
            **/
        virtual bool versionResult (
            const uint32_t number,
            const CIPtr< CIString >& version,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            versionResult Method ID: 82
            **/
        virtual bool versionResult (
            const uint32_t number,
            const uint32_t profile,
            const CIPtr< CIString >& version,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            versionResult Method ID: 79
            **/
        virtual bool versionResult (
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            versionResult Method ID: 80
            **/
        virtual bool versionResult (
            const CIPtr< CIString >& name,
            const uint32_t profile,
            const CIPtr< CIString >& version,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            purgeResult Method ID: 61
            **/
        virtual bool purgeResult (
            const uint32_t number,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            purgeResult Method ID: 62
            **/
        virtual bool purgeResult (
            const uint32_t number,
            const uint32_t profile,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            purgeResult Method ID: 59
            **/
        virtual bool purgeResult (
            const CIPtr< CIString >& name,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            purgeResult Method ID: 60
            **/
        virtual bool purgeResult (
            const CIPtr< CIString >& name,
            const uint32_t profile,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            copyResult Method ID: 19
            **/
        virtual bool copyResult (
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const uint32_t to_number,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            copyResult Method ID: 20
            **/
        virtual bool copyResult (
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const uint32_t to_number,
            const uint32_t to_profile,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            copyResult Method ID: 17
            **/
        virtual bool copyResult (
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const CIPtr< CIString >& to_name,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            copyResult Method ID: 18
            **/
        virtual bool copyResult (
            const CIPtr< persistence::PartitionHandle >& from_handle,
            const CIPtr< CIString >& to_number,
            const uint32_t to_profile,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            beginTransactionResult Method ID: 1
            **/
        virtual bool beginTransactionResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            endTransactionResult Method ID: 23
            **/
        virtual bool endTransactionResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            flushResult Method ID: 27
            **/
        virtual bool flushResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            existsResult Method ID: 25
            **/
        virtual bool existsResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            removeResult Method ID: 64
            **/
        virtual bool removeResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            getIntResult Method ID: 36
            **/
        virtual bool getIntResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const uint32_t val,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            getIntsResult Method ID: 39
            **/
        virtual bool getIntsResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const CIPtr< CIUInt32Array >& vals,
            const CIPtr< CIArray< persistence::RequestStatus > >& results
        ) IPL_NOEXCEPT = 0;

            /**
            getStringResult Method ID: 42
            **/
        virtual bool getStringResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const CIPtr< CIString >& val,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            getStringsResult Method ID: 45
            **/
        virtual bool getStringsResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const CIPtr< CIStringArray >& vals,
            const CIPtr< CIArray< persistence::RequestStatus > >& results
        ) IPL_NOEXCEPT = 0;

            /**
            getBlobResult Method ID: 30
            **/
        virtual bool getBlobResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const CIPtr< CIUInt8Array >& val,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            getBlobsResult Method ID: 33
            **/
        virtual bool getBlobsResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const CIPtr< CIPtrArray< CIUInt8Array > >& vals,
            const CIPtr< CIArray< persistence::RequestStatus > >& results
        ) IPL_NOEXCEPT = 0;

            /**
            
            \brief Report success or failure of set requests
        
            setResult Method ID: 67
            **/
        virtual bool setResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const uint32_t key,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            
            \brief Report success, failure and extend of unsubscription
        
            unsubscribeResult Method ID: 74
            **/
        virtual bool unsubscribeResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const CIPtr< CIArray< persistence::RequestStatus > >& status
        ) IPL_NOEXCEPT = 0;

            /**
            
            \brief Notify of current (on subscribe) or changed (on set) value
            or deletion state of string values \a keys
        
            stringValues Method ID: 69
            **/
        virtual bool stringValues (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const CIPtr< CIStringArray >& values,
            const CIPtr< CIArray< persistence::RequestStatus > >& status
        ) IPL_NOEXCEPT = 0;

            /**
            
            \brief Notify of current (on subscribe) or changed (on set) value
            or deletion state of integer values \a keys
        
            intValues Method ID: 46
            **/
        virtual bool intValues (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const CIPtr< CIUInt32Array >& values,
            const CIPtr< CIArray< persistence::RequestStatus > >& status
        ) IPL_NOEXCEPT = 0;

            /**
            
            \brief Notify of current (on subscribe) or changed (on set) value
            or deletion state of blob values \a keys
        
            blobValues Method ID: 2
            **/
        virtual bool blobValues (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIUInt32Array >& keys,
            const CIPtr< CIPtrArray< CIUInt8Array > >& values,
            const CIPtr< CIArray< persistence::RequestStatus > >& status
        ) IPL_NOEXCEPT = 0;

        virtual ~IPersistenceAReplyS() {}
    };

}// namespace persistence


#endif// PERSISTENCE_IPERSISTENCEA_REPLYS_HXX
