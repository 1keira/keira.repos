/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
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
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    *
    * Clients, which are registered with the NadInformationService,
    * will receive updates of NAD related information.
    * All information will be cached and is read-only from a client perspective.
    **/
    class NadInformationServiceReplyS
    {
    public:
        // List of reply methods
            /**
            \brief
            reply for the attribute AntennaInfo
            updateAntennaInfo Method ID: 20
            **/
        virtual bool updateAntennaInfo (
            const CIPtr< CIPtrArray< asi::connectivity::al::AntennaInfo > >& AntennaInfo,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute DataConnectionInfo
            updateDataConnectionInfo Method ID: 21
            **/
        virtual bool updateDataConnectionInfo (
            const CIPtr< asi::connectivity::al::DataConnectionInfo >& DataConnectionInfo,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute SimDataConfig
            updateSimDataConfig Method ID: 31
            **/
        virtual bool updateSimDataConfig (
            const CIPtr< asi::connectivity::al::SimDataConfig >& SimDataConfig,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute DataConnectionStartResult
            updateDataConnectionStartResult Method ID: 22
            **/
        virtual bool updateDataConnectionStartResult (
            const CIPtr< asi::connectivity::al::DataConnectionStartResult >& DataConnectionStartResult,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute NadDeviceInformation
            updateNadDeviceInformation Method ID: 27
            **/
        virtual bool updateNadDeviceInformation (
            const CIPtr< asi::connectivity::al::NadDeviceInformation >& NadDeviceInformation,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute NetworkRejectInformation
            updateNetworkRejectInformation Method ID: 30
            **/
        virtual bool updateNetworkRejectInformation (
            const CIPtr< asi::connectivity::al::NetworkRejectInformation >& NetworkRejectInformation,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute SimDataInfo
            updateSimDataInfo Method ID: 32
            **/
        virtual bool updateSimDataInfo (
            const CIPtr< asi::connectivity::al::SimDataInfo >& SimDataInfo,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute TemperatureInfo
            updateTemperatureInfo Method ID: 33
            **/
        virtual bool updateTemperatureInfo (
            const CIPtr< asi::connectivity::al::TemperatureInfo >& TemperatureInfo,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute NetworkInfo
            updateNetworkInfo Method ID: 29
            **/
        virtual bool updateNetworkInfo (
            const CIPtr< asi::connectivity::al::NetworkInfo >& NetworkInfo,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute AirplaneMode
            updateAirplaneMode Method ID: 19
            **/
        virtual bool updateAirplaneMode (
            const asi::connectivity::al::AirplaneMode AirplaneMode,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute NadState
            updateNadState Method ID: 28
            **/
        virtual bool updateNadState (
            const asi::connectivity::al::NadState NadState,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute JammingState
            updateJammingState Method ID: 24
            **/
        virtual bool updateJammingState (
            const asi::connectivity::al::JammingStatus JammingState,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute DormantMode
            updateDormantMode Method ID: 23
            **/
        virtual bool updateDormantMode (
            const asi::connectivity::al::DormantMode DormantMode,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute MobileCountryCode
            \details
            *
         * Mobile country code of the SIM profile (extracted from IMSI)
         
            updateMobileCountryCode Method ID: 25
            **/
        virtual bool updateMobileCountryCode (
            const CIPtr< CIString >& MobileCountryCode,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute MobileNetworkCode
            \details
            *
         * Mobile network code of the SIM profile (extracted from IMSI)
         
            updateMobileNetworkCode Method ID: 26
            **/
        virtual bool updateMobileNetworkCode (
            const CIPtr< CIString >& MobileNetworkCode,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

        virtual ~NadInformationServiceReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REPLYS_HXX
