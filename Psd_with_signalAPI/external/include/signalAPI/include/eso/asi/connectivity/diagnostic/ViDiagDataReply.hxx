/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/StructViDiagData.hxx>
#include <asi/connectivity/diagnostic/StructViDiagDataMetadata.hxx>
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
    class ViDiagDataReply {

    public:
    // List of reply methods
            /**
            getDiagData Method ID: 1
            **/
        virtual void getDiagData(
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::ViDiagData > >& data,
            const asi::connectivity::diagnostic::ViError error
        ) = 0;
            /**
            onDiagData Method ID: 4
            **/
        virtual void onDiagData(
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::ViDiagData > >& data
        ) = 0;
            /**
            getDiagDataMetadata Method ID: 3
            **/
        virtual void getDiagDataMetadata(
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::ViDiagDataMetadata > >& metadata,
            const asi::connectivity::diagnostic::ViError error
        ) = 0;
            /**
            writeDiagData Method ID: 7
            **/
        virtual void writeDiagData(
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
        getDiagData_aViDiagData_ViErrorCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<ViDiagDataReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        onDiagDataCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<ViDiagDataReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

        void
        getDiagDataMetadata_aViDiagDataMetadata_ViErrorCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<ViDiagDataReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        writeDiagData_ViErrorCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<ViDiagDataReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }


        virtual ~ViDiagDataReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAREPLY_HXX
