/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReply_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEAREPLY_CSTYLE_HXX
#define PERSISTENCE_IPERSISTENCEAREPLY_CSTYLE_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <persistence/cstyle/StructPartitionHandle.hxx>
#include <persistence/cstyle/Definitions.hxx>

namespace persistence
{
namespace cstyle
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class IPersistenceAReply {

    public:
    // List of reply methods
            /**
            openResult Method ID: 53
            **/
        virtual void openResult(
            const uint32_t number,
            const ipl::string* version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            openResult Method ID: 54
            **/
        virtual void openResult(
            const uint32_t number,
            const uint32_t profile,
            const ipl::string* version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            openResult Method ID: 51
            **/
        virtual void openResult(
            const ipl::string* name,
            const ipl::string* version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            openResult Method ID: 52
            **/
        virtual void openResult(
            const ipl::string* name,
            const uint32_t profile,
            const ipl::string* version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            convertResult Method ID: 11
            **/
        virtual void convertResult(
            const uint32_t number,
            const ipl::string* from_version,
            const ipl::string* to_version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            convertResult Method ID: 12
            **/
        virtual void convertResult(
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
        virtual void convertResult(
            const ipl::string* name,
            const ipl::string* from_version,
            const ipl::string* to_version,
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            convertResult Method ID: 10
            **/
        virtual void convertResult(
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
        virtual void closeResult(
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            versionResult Method ID: 81
            **/
        virtual void versionResult(
            const uint32_t number,
            const ipl::string* version,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            versionResult Method ID: 82
            **/
        virtual void versionResult(
            const uint32_t number,
            const uint32_t profile,
            const ipl::string* version,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            versionResult Method ID: 79
            **/
        virtual void versionResult(
            const ipl::string* name,
            const ipl::string* version,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            versionResult Method ID: 80
            **/
        virtual void versionResult(
            const ipl::string* name,
            const uint32_t profile,
            const ipl::string* version,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            purgeResult Method ID: 61
            **/
        virtual void purgeResult(
            const uint32_t number,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            purgeResult Method ID: 62
            **/
        virtual void purgeResult(
            const uint32_t number,
            const uint32_t profile,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            purgeResult Method ID: 59
            **/
        virtual void purgeResult(
            const ipl::string* name,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            purgeResult Method ID: 60
            **/
        virtual void purgeResult(
            const ipl::string* name,
            const uint32_t profile,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            copyResult Method ID: 19
            **/
        virtual void copyResult(
            const persistence::cstyle::PartitionHandle* from_handle,
            const uint32_t to_number,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            copyResult Method ID: 20
            **/
        virtual void copyResult(
            const persistence::cstyle::PartitionHandle* from_handle,
            const uint32_t to_number,
            const uint32_t to_profile,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            copyResult Method ID: 17
            **/
        virtual void copyResult(
            const persistence::cstyle::PartitionHandle* from_handle,
            const ipl::string* to_name,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            copyResult Method ID: 18
            **/
        virtual void copyResult(
            const persistence::cstyle::PartitionHandle* from_handle,
            const ipl::string* to_number,
            const uint32_t to_profile,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            beginTransactionResult Method ID: 1
            **/
        virtual void beginTransactionResult(
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            endTransactionResult Method ID: 23
            **/
        virtual void endTransactionResult(
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            flushResult Method ID: 27
            **/
        virtual void flushResult(
            const persistence::cstyle::PartitionHandle* handle,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            existsResult Method ID: 25
            **/
        virtual void existsResult(
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            removeResult Method ID: 64
            **/
        virtual void removeResult(
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            getIntResult Method ID: 36
            **/
        virtual void getIntResult(
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const uint32_t val,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            getIntsResult Method ID: 39
            **/
        virtual void getIntsResult(
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector<uint32_t>* vals,
            const ipl::vector< persistence::cstyle::RequestStatus >* results
        ) = 0;
            /**
            getStringResult Method ID: 42
            **/
        virtual void getStringResult(
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const ipl::string* val,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            getStringsResult Method ID: 45
            **/
        virtual void getStringsResult(
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector<ipl::string>* vals,
            const ipl::vector< persistence::cstyle::RequestStatus >* results
        ) = 0;
            /**
            getBlobResult Method ID: 30
            **/
        virtual void getBlobResult(
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const ipl::vector<uint8_t>* val,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            getBlobsResult Method ID: 33
            **/
        virtual void getBlobsResult(
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector< ipl::vector<uint8_t> >* vals,
            const ipl::vector< persistence::cstyle::RequestStatus >* results
        ) = 0;
            /**
            
            \brief Report success or failure of set requests
        
            setResult Method ID: 67
            **/
        virtual void setResult(
            const persistence::cstyle::PartitionHandle* handle,
            const uint32_t key,
            const persistence::cstyle::RequestStatus result
        ) = 0;
            /**
            
            \brief Report success, failure and extend of unsubscription
        
            unsubscribeResult Method ID: 74
            **/
        virtual void unsubscribeResult(
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector< persistence::cstyle::RequestStatus >* status
        ) = 0;
            /**
            
            \brief Notify of current (on subscribe) or changed (on set) value
            or deletion state of string values \a keys
        
            stringValues Method ID: 69
            **/
        virtual void stringValues(
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
        virtual void intValues(
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
        virtual void blobValues(
            const persistence::cstyle::PartitionHandle* handle,
            const ipl::vector<uint32_t>* keys,
            const ipl::vector< ipl::vector<uint8_t> >* values,
            const ipl::vector< persistence::cstyle::RequestStatus >* status
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count) {}

        // call ids
        void
        openResult_U32_S_PartitionHandle_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 53;
            ce.assign(inst, mid);
        }

        void
        openResult_U32_U32_S_PartitionHandle_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 54;
            ce.assign(inst, mid);
        }

        void
        openResult_S_S_PartitionHandle_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 51;
            ce.assign(inst, mid);
        }

        void
        openResult_S_U32_S_PartitionHandle_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 52;
            ce.assign(inst, mid);
        }

        void
        convertResult_U32_S_S_PartitionHandle_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        convertResult_U32_U32_S_S_PartitionHandle_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }

        void
        convertResult_S_S_S_PartitionHandle_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        convertResult_S_U32_S_S_PartitionHandle_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }

        void
        closeResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

        void
        versionResult_U32_S_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 81;
            ce.assign(inst, mid);
        }

        void
        versionResult_U32_U32_S_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 82;
            ce.assign(inst, mid);
        }

        void
        versionResult_S_S_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 79;
            ce.assign(inst, mid);
        }

        void
        versionResult_S_U32_S_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 80;
            ce.assign(inst, mid);
        }

        void
        purgeResult_U32_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 61;
            ce.assign(inst, mid);
        }

        void
        purgeResult_U32_U32_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 62;
            ce.assign(inst, mid);
        }

        void
        purgeResult_S_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 59;
            ce.assign(inst, mid);
        }

        void
        purgeResult_S_U32_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 60;
            ce.assign(inst, mid);
        }

        void
        copyResult_PartitionHandle_U32_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }

        void
        copyResult_PartitionHandle_U32_U32_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }

        void
        copyResult_PartitionHandle_S_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }

        void
        copyResult_PartitionHandle_S_U32_RequestStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }

        void
        beginTransactionResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        endTransactionResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 23;
            ce.assign(inst, mid);
        }

        void
        flushResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 27;
            ce.assign(inst, mid);
        }

        void
        existsResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 25;
            ce.assign(inst, mid);
        }

        void
        removeResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 64;
            ce.assign(inst, mid);
        }

        void
        getIntResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 36;
            ce.assign(inst, mid);
        }

        void
        getIntsResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 39;
            ce.assign(inst, mid);
        }

        void
        getStringResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 42;
            ce.assign(inst, mid);
        }

        void
        getStringsResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 45;
            ce.assign(inst, mid);
        }

        void
        getBlobResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 30;
            ce.assign(inst, mid);
        }

        void
        getBlobsResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 33;
            ce.assign(inst, mid);
        }

        void
        setResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 67;
            ce.assign(inst, mid);
        }

        void
        unsubscribeResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 74;
            ce.assign(inst, mid);
        }

        void
        stringValuesCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 69;
            ce.assign(inst, mid);
        }

        void
        intValuesCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 46;
            ce.assign(inst, mid);
        }

        void
        blobValuesCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceAReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }


        virtual ~IPersistenceAReply() {}
    };

} // namespace cstyle
}//namespace persistence

#endif// PERSISTENCE_IPERSISTENCEAREPLY_CSTYLE_HXX
