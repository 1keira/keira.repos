/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_DIAG_DTC_DTCREPLY_HXX
#define ASI_DIAG_DTC_DTCREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/diag/dtc/Definitions.hxx>

namespace asi
{
namespace diag
{
namespace dtc
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
        * Diagnosis service interface to test and report DTCs based on 3 Byte Diagnostic Fault Check Codes (DFCC).
     *
     * Every diagnosis node on system and android partition registers its own service instance of this interface.   
     * Every instance ID handles exactly the DTCs which are defined for that node.
     * The instance IDs of all nodes are defined in diag_common.idl.
    **/
    class DtcReply {

    public:
    // List of reply methods
            /**
            
         *  publishes dtc related events e.g. dtc storage cleared
         *
         *  @param event the occured event
         
            publishEvent Method ID: 1
            **/
        virtual void publishEvent(
            const asi::diag::dtc::eDtcEvent event
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
        publishEventCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DtcReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }


        virtual ~DtcReply() {}
    };

}//namespace asi
}//namespace diag
}//namespace dtc

#endif// ASI_DIAG_DTC_DTCREPLY_HXX
