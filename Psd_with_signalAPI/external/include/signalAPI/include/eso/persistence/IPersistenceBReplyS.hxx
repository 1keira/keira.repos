/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEB_REPLYS_HXX
#define PERSISTENCE_IPERSISTENCEB_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <persistence/StructPartitionHandle.hxx>
#include <persistence/Definitions.hxx>
namespace persistence
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class IPersistenceBReplyS
    {
    public:
        // List of reply methods
            /**
            openResult Method ID: 12
            **/
        virtual bool openResult (
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            closeResult Method ID: 1
            **/
        virtual bool closeResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            versionResult Method ID: 22
            **/
        virtual bool versionResult (
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            purgeResult Method ID: 14
            **/
        virtual bool purgeResult (
            const CIPtr< CIString >& name,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            flushResult Method ID: 5
            **/
        virtual bool flushResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            existsResult Method ID: 3
            **/
        virtual bool existsResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            removeResult Method ID: 18
            **/
        virtual bool removeResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            getBlobResult Method ID: 10
            **/
        virtual bool getBlobResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const CIPtr< CIUInt8Array >& val,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            
            \brief Report success or failure of set requests
        
            setResult Method ID: 20
            **/
        virtual bool setResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            getAllKeysResult Method ID: 7
            **/
        virtual bool getAllKeysResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIStringArray >& keys,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

            /**
            removeAllResult Method ID: 17
            **/
        virtual bool removeAllResult (
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) IPL_NOEXCEPT = 0;

        virtual ~IPersistenceBReplyS() {}
    };

}// namespace persistence


#endif// PERSISTENCE_IPERSISTENCEB_REPLYS_HXX
