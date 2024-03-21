/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ADAPTATIONVALUES_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ADAPTATIONVALUES_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/StructAnonymousGuestResetSettings.hxx>
#include <asi/connectivity/diagnostic/StructAntennaPosToRefPoint.hxx>
#include <asi/connectivity/diagnostic/StructApnPaidServices.hxx>
#include <asi/connectivity/diagnostic/StructEmergencyInformationServiceSettings.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/StructGnssRefTime.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/StructGreyModeSettings.hxx>
#include <asi/connectivity/diagnostic/StructMobileTelecommunicationStandard.hxx>
#include <asi/connectivity/diagnostic/StructPrivacyGroupModifiabilitySettings.hxx>
#include <asi/connectivity/diagnostic/StructPrivacySettings.hxx>
#include <asi/connectivity/diagnostic/StructProductionMode.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/StructTransmissionPower.hxx>
#include <asi/connectivity/diagnostic/StructVehicleDimensions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::AdaptationValues.
    */
    struct PROXY_EXPORT AdaptationValues
    {
        CIPtr< asi::connectivity::diagnostic::AnonymousGuestResetSettings > anonymousGuestResetSettings; // optional=True
        CIPtr< asi::connectivity::diagnostic::AntennaPosToRefPoint > antennaPosToRefPoint; // optional=True
        CIPtr< asi::connectivity::diagnostic::ApnPaidServices > apnPaidServices; // optional=True
        uint8_t dhcpLeaseTime; // optional=False
        CIPtr< asi::connectivity::diagnostic::EmergencyInformationServiceSettings > eisSettings; // optional=True
        int32_t era_glonass_switch; // optional=False
        asi::connectivity::diagnostic::GnssDataRate gnssDataRate; // optional=False
        uint16_t gnssMinElevation; // optional=False
        CIPtr< asi::connectivity::diagnostic::GnssRefTime > gnssRefTime; // optional=True
        asi::connectivity::diagnostic::GpsSource gpsSource; // optional=False
        CIPtr< asi::connectivity::diagnostic::GreyModeSettings > greyModeSettings; // optional=True
        bool isAppleCarPlayWirelessOn; // optional=False
        bool isBaiduCarLifeIosWirelessOn; // optional=False
        bool isBaiduCarLifeWirelessOn; // optional=False
        bool isBeiDouOn; // optional=False
        bool isRtkHdOn; // optional=False
        bool isRtkSdOn; // optional=False
        bool isCShiftHdOn; // optional=False
        bool isCShiftSdOn; // optional=False
        bool isGalileoOn; // optional=False
        bool isGlonassOn; // optional=False
        bool isGnssFrequencyL1On; // optional=False
        bool isGnssFrequencyL2On; // optional=False
        bool isGnssFrequencyL3On; // optional=False
        bool isGnssHdOverSomeIpOn; // optional=False
        bool isGoogleAndroidAutoWirelessOn; // optional=False
        bool isGpsOn; // optional=False
        bool isFlightModeActive; // optional=False
        bool isInternetAccessViaWifiOn; // optional=False
        bool isInternetOverWlanActive; // optional=False
        bool isRollenmodusActive; // optional=False
        bool isVoLteOn; // optional=False
        bool isVttLocalizationActive; // optional=False
        bool isWifiHotspot2_4GHzOn; // optional=False
        bool isWifiHotspot5GHzOn; // optional=False
        bool isWlan2_4GHzVisible; // optional=False
        bool isWlan5GHzOn; // optional=False
        bool isWlan5GHzVisible; // optional=False
        bool isWlanClientMode2_4GHzOn; // optional=False
        bool isWlanClientMode5GHzOn; // optional=False
        bool isWlanOn; // optional=False
        bool isWlanPasswordSynchronized; // optional=False
        CIPtr< CIString > mmiNameDefaultPrefix; // optional=True
        CIPtr< asi::connectivity::diagnostic::MobileTelecommunicationStandard > mobTelStandard; // optional=True
        uint8_t onlineServiceActivationDistanceInKm; // optional=False
        CIPtr< CIString > onlineServiceBackendPrimaryHostname; // optional=True
        CIPtr< asi::connectivity::diagnostic::PrivacyGroupModifiabilitySettings > privacyGroupModifiabilitySettings; // optional=True
        CIPtr< asi::connectivity::diagnostic::ProductionMode > pmode; // optional=True
        CIPtr< asi::connectivity::diagnostic::PrivacySettings > privacySettings; // optional=True
        CIPtr< CIString > region; // optional=True
        asi::connectivity::diagnostic::RtkLibrary rtkLib; // optional=False
        CIPtr< CIString > ssid2_4GHzPostfix; // optional=True
        CIPtr< CIString > ssid5GHzPostfix; // optional=True
        CIPtr< asi::connectivity::diagnostic::TransmissionPower > transmissionPower; // optional=True
        CIPtr< asi::connectivity::diagnostic::VehicleDimensions > vehicleDimensions; // optional=True
        CIPtr< CIString > verkaufsland; // optional=True
        uint8_t wlan2_4GHzChannelNumber; // optional=False
        asi::connectivity::diagnostic::Wlan2_4GHzMaxChannelBandwidth wlan2_4GHzMaxChannelBandwidth; // optional=False
        uint8_t wlan5GHzChannelNumber; // optional=False
        asi::connectivity::diagnostic::Wlan5GHzMaxChannelBandwidth wlan5GHzMaxChannelBandwidth; // optional=False
        private:
            AdaptationValues()
            :
            anonymousGuestResetSettings(),
            antennaPosToRefPoint(),
            apnPaidServices(),
            dhcpLeaseTime(),
            eisSettings(),
            era_glonass_switch(),
            gnssDataRate(),
            gnssMinElevation(),
            gnssRefTime(),
            gpsSource(),
            greyModeSettings(),
            isAppleCarPlayWirelessOn(),
            isBaiduCarLifeIosWirelessOn(),
            isBaiduCarLifeWirelessOn(),
            isBeiDouOn(),
            isRtkHdOn(),
            isRtkSdOn(),
            isCShiftHdOn(),
            isCShiftSdOn(),
            isGalileoOn(),
            isGlonassOn(),
            isGnssFrequencyL1On(),
            isGnssFrequencyL2On(),
            isGnssFrequencyL3On(),
            isGnssHdOverSomeIpOn(),
            isGoogleAndroidAutoWirelessOn(),
            isGpsOn(),
            isFlightModeActive(),
            isInternetAccessViaWifiOn(),
            isInternetOverWlanActive(),
            isRollenmodusActive(),
            isVoLteOn(),
            isVttLocalizationActive(),
            isWifiHotspot2_4GHzOn(),
            isWifiHotspot5GHzOn(),
            isWlan2_4GHzVisible(),
            isWlan5GHzOn(),
            isWlan5GHzVisible(),
            isWlanClientMode2_4GHzOn(),
            isWlanClientMode5GHzOn(),
            isWlanOn(),
            isWlanPasswordSynchronized(),
            mmiNameDefaultPrefix(),
            mobTelStandard(),
            onlineServiceActivationDistanceInKm(),
            onlineServiceBackendPrimaryHostname(),
            privacyGroupModifiabilitySettings(),
            pmode(),
            privacySettings(),
            region(),
            rtkLib(),
            ssid2_4GHzPostfix(),
            ssid5GHzPostfix(),
            transmissionPower(),
            vehicleDimensions(),
            verkaufsland(),
            wlan2_4GHzChannelNumber(),
            wlan2_4GHzMaxChannelBandwidth(),
            wlan5GHzChannelNumber(),
            wlan5GHzMaxChannelBandwidth()
            { }
            friend class AdaptationValuesFactory;
            friend class CIFactory<AdaptationValues>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::AdaptationValues> >;
            friend class ipl::vector<AdaptationValues>;
            friend class ipl::allocator<AdaptationValues>;
#endif
    };

    typedef CIPtrArray<AdaptationValues> CIAdaptationValuesArray;

    /** \brief factory for diagnostic::AdaptationValues. */
    class PROXY_EXPORT AdaptationValuesFactory  : CIFactory<AdaptationValues> {
    public:
        static inline CIPtr<AdaptationValues> createAdaptationValues() {
            return CIFactory<AdaptationValues>::createObject();
        }
        static inline void createAdaptationValues(CIPtr<AdaptationValues> & s) {
            CIFactory<AdaptationValues>::createObject(s);
        }
        static inline CIPtr<CIAdaptationValuesArray> createAdaptationValuesArray(size_t size) {
            return CIFactory<AdaptationValues>::createArray(size);
        }
        static inline void createAdaptationValuesArray(CIPtr<CIAdaptationValuesArray>& a, size_t size) {
            CIFactory<AdaptationValues>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ADAPTATIONVALUES_HXX
