/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENTREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENTREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
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
    class ViMeasurementReply {

    public:
    // List of reply methods
            /**
            getMeasurementValues Method ID: 0
            **/
        virtual void getMeasurementValues(
            const uint32_t measurementId
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
        getMeasurementValues_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<ViMeasurementReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }


        virtual ~ViMeasurementReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENTREPLY_HXX
