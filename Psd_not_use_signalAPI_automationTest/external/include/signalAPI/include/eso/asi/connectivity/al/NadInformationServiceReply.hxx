/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICEREPLY_HXX
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICEREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/StructAntennaInfo.hxx>
#include <asi/connectivity/al/StructDataConnectionInfo.hxx>
#include <asi/connectivity/al/StructDataConnectionStartResult.hxx>
#include <asi/connectivity/al/StructNadDeviceInformation.hxx>
#include <asi/connectivity/al/StructNetworkInfo.hxx>
#include <asi/connectivity/al/StructNetworkRejectInformation.hxx>
#include <asi/connectivity/al/StructSimDataConfig.hxx>
#include <asi/connectivity/al/StructSimDataInfo.hxx>
#include <asi/connectivity/al/StructTemperatureInfo.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
        *
    * Clients, which are registered with the NadInformationService,
    * will receive updates of NAD related information.
    * All information will be cached and is read-only from a client perspective.
    **/
    class NadInformationServiceReply {

    public:
    // List of reply methods
            /**
            \brief
            reply for the attribute AntennaInfo
            updateAntennaInfo Method ID: 20
            **/
        virtual void updateAntennaInfo(
            const CIPtr< CIPtrArray< asi::connectivity::al::AntennaInfo > >& AntennaInfo,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute DataConnectionInfo
            updateDataConnectionInfo Method ID: 21
            **/
        virtual void updateDataConnectionInfo(
            const CIPtr< asi::connectivity::al::DataConnectionInfo >& DataConnectionInfo,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute SimDataConfig
            updateSimDataConfig Method ID: 31
            **/
        virtual void updateSimDataConfig(
            const CIPtr< asi::connectivity::al::SimDataConfig >& SimDataConfig,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute DataConnectionStartResult
            updateDataConnectionStartResult Method ID: 22
            **/
        virtual void updateDataConnectionStartResult(
            const CIPtr< asi::connectivity::al::DataConnectionStartResult >& DataConnectionStartResult,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute NadDeviceInformation
            updateNadDeviceInformation Method ID: 27
            **/
        virtual void updateNadDeviceInformation(
            const CIPtr< asi::connectivity::al::NadDeviceInformation >& NadDeviceInformation,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute NetworkRejectInformation
            updateNetworkRejectInformation Method ID: 30
            **/
        virtual void updateNetworkRejectInformation(
            const CIPtr< asi::connectivity::al::NetworkRejectInformation >& NetworkRejectInformation,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute SimDataInfo
            updateSimDataInfo Method ID: 32
            **/
        virtual void updateSimDataInfo(
            const CIPtr< asi::connectivity::al::SimDataInfo >& SimDataInfo,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute TemperatureInfo
            updateTemperatureInfo Method ID: 33
            **/
        virtual void updateTemperatureInfo(
            const CIPtr< asi::connectivity::al::TemperatureInfo >& TemperatureInfo,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute NetworkInfo
            updateNetworkInfo Method ID: 29
            **/
        virtual void updateNetworkInfo(
            const CIPtr< asi::connectivity::al::NetworkInfo >& NetworkInfo,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute AirplaneMode
            updateAirplaneMode Method ID: 19
            **/
        virtual void updateAirplaneMode(
            const asi::connectivity::al::AirplaneMode AirplaneMode,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute NadState
            updateNadState Method ID: 28
            **/
        virtual void updateNadState(
            const asi::connectivity::al::NadState NadState,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute JammingState
            updateJammingState Method ID: 24
            **/
        virtual void updateJammingState(
            const asi::connectivity::al::JammingStatus JammingState,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute DormantMode
            updateDormantMode Method ID: 23
            **/
        virtual void updateDormantMode(
            const asi::connectivity::al::DormantMode DormantMode,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute MobileCountryCode
            \details
            *
         * Mobile country code of the SIM profile (extracted from IMSI)
         
            updateMobileCountryCode Method ID: 25
            **/
        virtual void updateMobileCountryCode(
            const CIPtr< CIString >& MobileCountryCode,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute MobileNetworkCode
            \details
            *
         * Mobile network code of the SIM profile (extracted from IMSI)
         
            updateMobileNetworkCode Method ID: 26
            **/
        virtual void updateMobileNetworkCode(
            const CIPtr< CIString >& MobileNetworkCode,
            const bool isValid
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
        updateAntennaInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }

        void
        updateDataConnectionInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }

        void
        updateSimDataConfigCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 31;
            ce.assign(inst, mid);
        }

        void
        updateDataConnectionStartResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }

        void
        updateNadDeviceInformationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 27;
            ce.assign(inst, mid);
        }

        void
        updateNetworkRejectInformationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 30;
            ce.assign(inst, mid);
        }

        void
        updateSimDataInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32;
            ce.assign(inst, mid);
        }

        void
        updateTemperatureInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 33;
            ce.assign(inst, mid);
        }

        void
        updateNetworkInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 29;
            ce.assign(inst, mid);
        }

        void
        updateAirplaneModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }

        void
        updateNadStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 28;
            ce.assign(inst, mid);
        }

        void
        updateJammingStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 24;
            ce.assign(inst, mid);
        }

        void
        updateDormantModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 23;
            ce.assign(inst, mid);
        }

        void
        updateMobileCountryCodeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 25;
            ce.assign(inst, mid);
        }

        void
        updateMobileNetworkCodeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 26;
            ce.assign(inst, mid);
        }


        virtual ~NadInformationServiceReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICEREPLY_HXX
