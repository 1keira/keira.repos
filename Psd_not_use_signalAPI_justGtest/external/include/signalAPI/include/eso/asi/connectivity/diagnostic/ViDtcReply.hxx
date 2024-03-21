/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDTCREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDTCREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/StructDtc.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class ViDtcReply {

    public:
    // List of reply methods
            /**
            setDtc Method ID: 3
            **/
        virtual void setDtc(
            const asi::connectivity::diagnostic::ViError error
        ) = 0;
            /**
            onDtcs Method ID: 2
            **/
        virtual void onDtcs(
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::Dtc > >& dtcs
        ) = 0;
            /**
            getDtcs Method ID: 1
            **/
        virtual void getDtcs(
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::Dtc > >& dtcs,
            const asi::connectivity::diagnostic::ViError error
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
        setDtc_ViErrorCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<ViDtcReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        onDtcsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<ViDtcReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }

        void
        getDtcs_aDtc_ViErrorCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<ViDtcReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }


        virtual ~ViDtcReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDTCREPLY_HXX
