/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReplyS_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEA_REPLYS_CSTYLE_HXX
#define PERSISTENCE_IPERSISTENCEA_REPLYS_CSTYLE_HXX
#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <persistence/cstyle/StructPartitionHandle.hxx>
#include <persistence/cstyle/Definitions.hxx>
namespace persistence
{
namespace cstyle {

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
            const ipl::string* version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            openResult Method ID: 54
            **/
        virtual bool openResult (
            const uint32_t number,
            const uint32_t profile,
            const ipl::string* version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            openResult Method ID: 51
            **/
        virtual bool openResult (
            const ipl::string* name,
            const ipl::string* version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            openResult Method ID: 52
            **/
        virtual bool openResult (
            const ipl::string* name,
            const uint32_t profile,
            const ipl::string* version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            convertResult Method ID: 11
            **/
        virtual bool convertResult (
            const uint32_t number,
            const ipl::string* from_version,
            const ipl::string* to_version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            convertResult Method ID: 12
            **/
        virtual bool convertResult (
            const uint32_t number,
            const uint32_t profile,
            const ipl::string* from_version,
            const ipl::string* to_version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            convertResult Method ID: 9
            **/
        virtual bool convertResult (
            const ipl::string* name,
            const ipl::string* from_version,
            const ipl::string* to_version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            convertResult Method ID: 10
            **/
        virtual bool convertResult (
            const ipl::string* name,
            const uint32_t profile,
            const ipl::string* from_version,
            const ipl::string* to_version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            closeResult Method ID: 4
            **/
        virtual bool closeResult (
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            versionResult Method ID: 81
            **/
        virtual bool versionResult (
            const uint32_t number,
            const ipl::string* version,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            versionResult Method ID: 82
            **/
        virtual bool versionResult (
            const uint32_t number,
            const uint32_t profile,
            const ipl::string* version,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            versionResult Method ID: 79
            **/
        virtual bool versionResult (
            const ipl::string* name,
            const ipl::string* version,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            versionResult Method ID: 80
            **/
        virtual bool versionResult (
            const ipl::string* name,
            const uint32_t profile,
            const ipl::string* version,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            purgeResult Method ID: 61
            **/
        virtual bool purgeResult (
            const uint32_t number,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            purgeResult Method ID: 62
            **/
        virtual bool purgeResult (
            const uint32_t number,
            const uint32_t profile,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            purgeResult Method ID: 59
            **/
        virtual bool purgeResult (
            const ipl::string* name,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            purgeResult Method ID: 60
            **/
        virtual bool purgeResult (
            const ipl::string* name,
            const uint32_t profile,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            copyResult Method ID: 19
            **/
        virtual bool copyResult (
            const persistence::cstyle::PartitionHandle* from_handle,
            const uint32_t to_number,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            copyResult Method ID: 20
            **/
        virtual bool copyResult (
            const persistence::cstyle::PartitionHandle* from_handle,
            const uint32_t to_number,
            const uint32_t to_profile,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            copyResult Method ID: 17
            **/
        virtual bool copyResult (
            const persistence::cstyle::PartitionHandle* from_handle,
            const ipl::string* to_name,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            copyResult Method ID: 18
            **/
        virtual bool copyResult (
            const persistence::cstyle::PartitionHandle* from_handle,
            const ipl::string* to_number,
            const uint32_t to_profile,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            beginTransactionResult Method ID: 1
            **/
        virtual bool beginTransactionResult (
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            endTransactionResult Method ID: 23
            **/
        virtual bool endTransactionResult (
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            flushResult Method ID: 27
            **/
        virtual bool flushResult (
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            existsResult Method ID: 25
            **/
        virtual bool existsResult (
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            removeResult Method ID: 64
            **/
        virtual bool removeResult (
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            getIntResult Method ID: 36
            **/
        virtual bool getIntResult (
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const uint32_t val,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            getIntsResult Method ID: 39
            **/
        virtual bool getIntsResult (
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector<uint32_t>* vals,
            const ipl::vector< persistence::cstyle::RequestStatus >* results
        ) = 0;

            /**
            getStringResult Method ID: 42
            **/
        virtual bool getStringResult (
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const ipl::string* val,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            getStringsResult Method ID: 45
            **/
        virtual bool getStringsResult (
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector<ipl::string>* vals,
            const ipl::vector< persistence::cstyle::RequestStatus >* results
        ) = 0;

            /**
            getBlobResult Method ID: 30
            **/
        virtual bool getBlobResult (
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const ipl::vector<uint8_t>* val,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            getBlobsResult Method ID: 33
            **/
        virtual bool getBlobsResult (
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector< ipl::vector<uint8_t> >* vals,
            const ipl::vector< persistence::cstyle::RequestStatus >* results
        ) = 0;

            /**
            
            \brief Report success or failure of set requests
        
            setResult Method ID: 67
            **/
        virtual bool setResult (
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const persistence::cstyle::RequestStatus result
        ) = 0;

            /**
            
            \brief Report success, failure and extend of unsubscription
        
            unsubscribeResult Method ID: 74
            **/
        virtual bool unsubscribeResult (
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector< persistence::cstyle::RequestStatus >* status
        ) = 0;

            /**
            
            \brief Notify of current (on subscribe) or changed (on set) value
            or deletion state of string values \a keys
        
            stringValues Method ID: 69
            **/
        virtual bool stringValues (
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector<ipl::string>* values,
            const ipl::vector< persistence::cstyle::RequestStatus >* status
        ) = 0;

            /**
            
            \brief Notify of current (on subscribe) or changed (on set) value
            or deletion state of integer values \a keys
        
            intValues Method ID: 46
            **/
        virtual bool intValues (
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector<uint32_t>* values,
            const ipl::vector< persistence::cstyle::RequestStatus >* status
        ) = 0;

            /**
            
            \brief Notify of current (on subscribe) or changed (on set) value
            or deletion state of blob values \a keys
        
            blobValues Method ID: 2
            **/
        virtual bool blobValues (
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector< ipl::vector<uint8_t> >* values,
            const ipl::vector< persistence::cstyle::RequestStatus >* status
        ) = 0;


        virtual ~IPersistenceAReplyS() {}
    protected:
        friend class IPersistenceAProxyReply;
    };

} // namespace cstyle
}// namespace persistence


#endif// PERSISTENCE_IPERSISTENCEA_REPLYS_CSTYLE_HXX
