/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEBREPLY_HXX
#define PERSISTENCE_IPERSISTENCEBREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <persistence/StructPartitionHandle.hxx>
#include <persistence/Definitions.hxx>

namespace persistence
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class IPersistenceBReply {

    public:
    // List of reply methods
            /**
            openResult Method ID: 12
            **/
        virtual void openResult(
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version,
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) = 0;
            /**
            closeResult Method ID: 1
            **/
        virtual void closeResult(
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) = 0;
            /**
            versionResult Method ID: 22
            **/
        virtual void versionResult(
            const CIPtr< CIString >& name,
            const CIPtr< CIString >& version,
            const persistence::RequestStatus result
        ) = 0;
            /**
            purgeResult Method ID: 14
            **/
        virtual void purgeResult(
            const CIPtr< CIString >& name,
            const persistence::RequestStatus result
        ) = 0;
            /**
            flushResult Method ID: 5
            **/
        virtual void flushResult(
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
        ) = 0;
            /**
            existsResult Method ID: 3
            **/
        virtual void existsResult(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const persistence::RequestStatus result
        ) = 0;
            /**
            removeResult Method ID: 18
            **/
        virtual void removeResult(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const persistence::RequestStatus result
        ) = 0;
            /**
            getBlobResult Method ID: 10
            **/
        virtual void getBlobResult(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const CIPtr< CIUInt8Array >& val,
            const persistence::RequestStatus result
        ) = 0;
            /**
            
            \brief Report success or failure of set requests
        
            setResult Method ID: 20
            **/
        virtual void setResult(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIString >& key,
            const persistence::RequestStatus result
        ) = 0;
            /**
            getAllKeysResult Method ID: 7
            **/
        virtual void getAllKeysResult(
            const CIPtr< persistence::PartitionHandle >& handle,
            const CIPtr< CIStringArray >& keys,
            const persistence::RequestStatus result
        ) = 0;
            /**
            removeAllResult Method ID: 17
            **/
        virtual void removeAllResult(
            const CIPtr< persistence::PartitionHandle >& handle,
            const persistence::RequestStatus result
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
        openResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }

        void
        closeResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        versionResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }

        void
        purgeResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }

        void
        flushResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        existsResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        removeResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }

        void
        getBlobResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }

        void
        setResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }

        void
        getAllKeysResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }

        void
        removeAllResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IPersistenceBReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }


        virtual ~IPersistenceBReply() {}
    };

}//namespace persistence

#endif// PERSISTENCE_IPERSISTENCEBREPLY_HXX
