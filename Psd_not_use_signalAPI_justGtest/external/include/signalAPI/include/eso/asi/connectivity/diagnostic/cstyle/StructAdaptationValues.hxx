/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ADAPTATIONVALUES_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ADAPTATIONVALUES_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructAnonymousGuestResetSettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructAntennaPosToRefPoint.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructApnPaidServices.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructEmergencyInformationServiceSettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructGnssRefTime.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructGreyModeSettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructMobileTelecommunicationStandard.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructPrivacyGroupModifiabilitySettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructPrivacySettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructProductionMode.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructTransmissionPower.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructVehicleDimensions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct AdaptationValues;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::AdaptationValues& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AdaptationValues &val);
}
}

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{

    /**
    \brief struct diagnostic::AdaptationValues.
    */
    struct PROXY_EXPORT AdaptationValues
    {
        public:
            AdaptationValues()
            : m_dhcpLeaseTime()
            , m_era_glonass_switch()
            , m_gnssDataRate()
            , m_gnssMinElevation()
            , m_gpsSource()
            , m_isAppleCarPlayWirelessOn()
            , m_isBaiduCarLifeIosWirelessOn()
            , m_isBaiduCarLifeWirelessOn()
            , m_isBeiDouOn()
            , m_isRtkHdOn()
            , m_isRtkSdOn()
            , m_isCShiftHdOn()
            , m_isCShiftSdOn()
            , m_isGalileoOn()
            , m_isGlonassOn()
            , m_isGnssFrequencyL1On()
            , m_isGnssFrequencyL2On()
            , m_isGnssFrequencyL3On()
            , m_isGnssHdOverSomeIpOn()
            , m_isGoogleAndroidAutoWirelessOn()
            , m_isGpsOn()
            , m_isFlightModeActive()
            , m_isInternetAccessViaWifiOn()
            , m_isInternetOverWlanActive()
            , m_isRollenmodusActive()
            , m_isVoLteOn()
            , m_isVttLocalizationActive()
            , m_isWifiHotspot2_4GHzOn()
            , m_isWifiHotspot5GHzOn()
            , m_isWlan2_4GHzVisible()
            , m_isWlan5GHzOn()
            , m_isWlan5GHzVisible()
            , m_isWlanClientMode2_4GHzOn()
            , m_isWlanClientMode5GHzOn()
            , m_isWlanOn()
            , m_isWlanPasswordSynchronized()
            , m_onlineServiceActivationDistanceInKm()
            , m_rtkLib()
            , m_wlan2_4GHzChannelNumber()
            , m_wlan2_4GHzMaxChannelBandwidth()
            , m_wlan5GHzChannelNumber()
            , m_wlan5GHzMaxChannelBandwidth()
            , m_anonymousGuestResetSettings(nullptr)
            , m_antennaPosToRefPoint(nullptr)
            , m_apnPaidServices(nullptr)
            , m_eisSettings(nullptr)
            , m_gnssRefTime(nullptr)
            , m_greyModeSettings(nullptr)
            , m_mmiNameDefaultPrefix(nullptr)
            , m_mobTelStandard(nullptr)
            , m_onlineServiceBackendPrimaryHostname(nullptr)
            , m_privacyGroupModifiabilitySettings(nullptr)
            , m_pmode(nullptr)
            , m_privacySettings(nullptr)
            , m_region(nullptr)
            , m_ssid2_4GHzPostfix(nullptr)
            , m_ssid5GHzPostfix(nullptr)
            , m_transmissionPower(nullptr)
            , m_vehicleDimensions(nullptr)
            , m_verkaufsland(nullptr)
            { }

            AdaptationValues (const AdaptationValues& other)
            : m_dhcpLeaseTime()
            , m_era_glonass_switch()
            , m_gnssDataRate()
            , m_gnssMinElevation()
            , m_gpsSource()
            , m_isAppleCarPlayWirelessOn()
            , m_isBaiduCarLifeIosWirelessOn()
            , m_isBaiduCarLifeWirelessOn()
            , m_isBeiDouOn()
            , m_isRtkHdOn()
            , m_isRtkSdOn()
            , m_isCShiftHdOn()
            , m_isCShiftSdOn()
            , m_isGalileoOn()
            , m_isGlonassOn()
            , m_isGnssFrequencyL1On()
            , m_isGnssFrequencyL2On()
            , m_isGnssFrequencyL3On()
            , m_isGnssHdOverSomeIpOn()
            , m_isGoogleAndroidAutoWirelessOn()
            , m_isGpsOn()
            , m_isFlightModeActive()
            , m_isInternetAccessViaWifiOn()
            , m_isInternetOverWlanActive()
            , m_isRollenmodusActive()
            , m_isVoLteOn()
            , m_isVttLocalizationActive()
            , m_isWifiHotspot2_4GHzOn()
            , m_isWifiHotspot5GHzOn()
            , m_isWlan2_4GHzVisible()
            , m_isWlan5GHzOn()
            , m_isWlan5GHzVisible()
            , m_isWlanClientMode2_4GHzOn()
            , m_isWlanClientMode5GHzOn()
            , m_isWlanOn()
            , m_isWlanPasswordSynchronized()
            , m_onlineServiceActivationDistanceInKm()
            , m_rtkLib()
            , m_wlan2_4GHzChannelNumber()
            , m_wlan2_4GHzMaxChannelBandwidth()
            , m_wlan5GHzChannelNumber()
            , m_wlan5GHzMaxChannelBandwidth()
            , m_anonymousGuestResetSettings(nullptr)
            , m_antennaPosToRefPoint(nullptr)
            , m_apnPaidServices(nullptr)
            , m_eisSettings(nullptr)
            , m_gnssRefTime(nullptr)
            , m_greyModeSettings(nullptr)
            , m_mmiNameDefaultPrefix(nullptr)
            , m_mobTelStandard(nullptr)
            , m_onlineServiceBackendPrimaryHostname(nullptr)
            , m_privacyGroupModifiabilitySettings(nullptr)
            , m_pmode(nullptr)
            , m_privacySettings(nullptr)
            , m_region(nullptr)
            , m_ssid2_4GHzPostfix(nullptr)
            , m_ssid5GHzPostfix(nullptr)
            , m_transmissionPower(nullptr)
            , m_vehicleDimensions(nullptr)
            , m_verkaufsland(nullptr)
            {
              *this = other;
            }

            ~AdaptationValues () {
                if (m_anonymousGuestResetSettings) {
                    delete m_anonymousGuestResetSettings;
                }
                if (m_antennaPosToRefPoint) {
                    delete m_antennaPosToRefPoint;
                }
                if (m_apnPaidServices) {
                    delete m_apnPaidServices;
                }
                if (m_eisSettings) {
                    delete m_eisSettings;
                }
                if (m_gnssRefTime) {
                    delete m_gnssRefTime;
                }
                if (m_greyModeSettings) {
                    delete m_greyModeSettings;
                }
                if (m_mmiNameDefaultPrefix) {
                    delete m_mmiNameDefaultPrefix;
                }
                if (m_mobTelStandard) {
                    delete m_mobTelStandard;
                }
                if (m_onlineServiceBackendPrimaryHostname) {
                    delete m_onlineServiceBackendPrimaryHostname;
                }
                if (m_privacyGroupModifiabilitySettings) {
                    delete m_privacyGroupModifiabilitySettings;
                }
                if (m_pmode) {
                    delete m_pmode;
                }
                if (m_privacySettings) {
                    delete m_privacySettings;
                }
                if (m_region) {
                    delete m_region;
                }
                if (m_ssid2_4GHzPostfix) {
                    delete m_ssid2_4GHzPostfix;
                }
                if (m_ssid5GHzPostfix) {
                    delete m_ssid5GHzPostfix;
                }
                if (m_transmissionPower) {
                    delete m_transmissionPower;
                }
                if (m_vehicleDimensions) {
                    delete m_vehicleDimensions;
                }
                if (m_verkaufsland) {
                    delete m_verkaufsland;
                }
            }
            bool operator==(const AdaptationValues& rhs) const {
                bool equal = true;
                if (m_anonymousGuestResetSettings == nullptr && rhs.m_anonymousGuestResetSettings != nullptr)
                    equal = false;
                else if (m_anonymousGuestResetSettings != nullptr && rhs.m_anonymousGuestResetSettings == nullptr)
                    equal = false;
                else if ((m_anonymousGuestResetSettings != nullptr) && (rhs.m_anonymousGuestResetSettings != nullptr) && (*m_anonymousGuestResetSettings != *rhs.m_anonymousGuestResetSettings))
                    equal = false;
                if (m_antennaPosToRefPoint == nullptr && rhs.m_antennaPosToRefPoint != nullptr)
                    equal = false;
                else if (m_antennaPosToRefPoint != nullptr && rhs.m_antennaPosToRefPoint == nullptr)
                    equal = false;
                else if ((m_antennaPosToRefPoint != nullptr) && (rhs.m_antennaPosToRefPoint != nullptr) && (*m_antennaPosToRefPoint != *rhs.m_antennaPosToRefPoint))
                    equal = false;
                if (m_apnPaidServices == nullptr && rhs.m_apnPaidServices != nullptr)
                    equal = false;
                else if (m_apnPaidServices != nullptr && rhs.m_apnPaidServices == nullptr)
                    equal = false;
                else if ((m_apnPaidServices != nullptr) && (rhs.m_apnPaidServices != nullptr) && (*m_apnPaidServices != *rhs.m_apnPaidServices))
                    equal = false;
                if (m_dhcpLeaseTime != rhs.m_dhcpLeaseTime)
                    equal = false;
                if (m_eisSettings == nullptr && rhs.m_eisSettings != nullptr)
                    equal = false;
                else if (m_eisSettings != nullptr && rhs.m_eisSettings == nullptr)
                    equal = false;
                else if ((m_eisSettings != nullptr) && (rhs.m_eisSettings != nullptr) && (*m_eisSettings != *rhs.m_eisSettings))
                    equal = false;
                if (m_era_glonass_switch != rhs.m_era_glonass_switch)
                    equal = false;
                if (m_gnssDataRate != rhs.m_gnssDataRate)
                    equal = false;
                if (m_gnssMinElevation != rhs.m_gnssMinElevation)
                    equal = false;
                if (m_gnssRefTime == nullptr && rhs.m_gnssRefTime != nullptr)
                    equal = false;
                else if (m_gnssRefTime != nullptr && rhs.m_gnssRefTime == nullptr)
                    equal = false;
                else if ((m_gnssRefTime != nullptr) && (rhs.m_gnssRefTime != nullptr) && (*m_gnssRefTime != *rhs.m_gnssRefTime))
                    equal = false;
                if (m_gpsSource != rhs.m_gpsSource)
                    equal = false;
                if (m_greyModeSettings == nullptr && rhs.m_greyModeSettings != nullptr)
                    equal = false;
                else if (m_greyModeSettings != nullptr && rhs.m_greyModeSettings == nullptr)
                    equal = false;
                else if ((m_greyModeSettings != nullptr) && (rhs.m_greyModeSettings != nullptr) && (*m_greyModeSettings != *rhs.m_greyModeSettings))
                    equal = false;
                if (m_isAppleCarPlayWirelessOn != rhs.m_isAppleCarPlayWirelessOn)
                    equal = false;
                if (m_isBaiduCarLifeIosWirelessOn != rhs.m_isBaiduCarLifeIosWirelessOn)
                    equal = false;
                if (m_isBaiduCarLifeWirelessOn != rhs.m_isBaiduCarLifeWirelessOn)
                    equal = false;
                if (m_isBeiDouOn != rhs.m_isBeiDouOn)
                    equal = false;
                if (m_isRtkHdOn != rhs.m_isRtkHdOn)
                    equal = false;
                if (m_isRtkSdOn != rhs.m_isRtkSdOn)
                    equal = false;
                if (m_isCShiftHdOn != rhs.m_isCShiftHdOn)
                    equal = false;
                if (m_isCShiftSdOn != rhs.m_isCShiftSdOn)
                    equal = false;
                if (m_isGalileoOn != rhs.m_isGalileoOn)
                    equal = false;
                if (m_isGlonassOn != rhs.m_isGlonassOn)
                    equal = false;
                if (m_isGnssFrequencyL1On != rhs.m_isGnssFrequencyL1On)
                    equal = false;
                if (m_isGnssFrequencyL2On != rhs.m_isGnssFrequencyL2On)
                    equal = false;
                if (m_isGnssFrequencyL3On != rhs.m_isGnssFrequencyL3On)
                    equal = false;
                if (m_isGnssHdOverSomeIpOn != rhs.m_isGnssHdOverSomeIpOn)
                    equal = false;
                if (m_isGoogleAndroidAutoWirelessOn != rhs.m_isGoogleAndroidAutoWirelessOn)
                    equal = false;
                if (m_isGpsOn != rhs.m_isGpsOn)
                    equal = false;
                if (m_isFlightModeActive != rhs.m_isFlightModeActive)
                    equal = false;
                if (m_isInternetAccessViaWifiOn != rhs.m_isInternetAccessViaWifiOn)
                    equal = false;
                if (m_isInternetOverWlanActive != rhs.m_isInternetOverWlanActive)
                    equal = false;
                if (m_isRollenmodusActive != rhs.m_isRollenmodusActive)
                    equal = false;
                if (m_isVoLteOn != rhs.m_isVoLteOn)
                    equal = false;
                if (m_isVttLocalizationActive != rhs.m_isVttLocalizationActive)
                    equal = false;
                if (m_isWifiHotspot2_4GHzOn != rhs.m_isWifiHotspot2_4GHzOn)
                    equal = false;
                if (m_isWifiHotspot5GHzOn != rhs.m_isWifiHotspot5GHzOn)
                    equal = false;
                if (m_isWlan2_4GHzVisible != rhs.m_isWlan2_4GHzVisible)
                    equal = false;
                if (m_isWlan5GHzOn != rhs.m_isWlan5GHzOn)
                    equal = false;
                if (m_isWlan5GHzVisible != rhs.m_isWlan5GHzVisible)
                    equal = false;
                if (m_isWlanClientMode2_4GHzOn != rhs.m_isWlanClientMode2_4GHzOn)
                    equal = false;
                if (m_isWlanClientMode5GHzOn != rhs.m_isWlanClientMode5GHzOn)
                    equal = false;
                if (m_isWlanOn != rhs.m_isWlanOn)
                    equal = false;
                if (m_isWlanPasswordSynchronized != rhs.m_isWlanPasswordSynchronized)
                    equal = false;
                if (m_mmiNameDefaultPrefix == nullptr && rhs.m_mmiNameDefaultPrefix != nullptr)
                    equal = false;
                else if (m_mmiNameDefaultPrefix != nullptr && rhs.m_mmiNameDefaultPrefix == nullptr)
                    equal = false;
                else if ((m_mmiNameDefaultPrefix != nullptr) && (rhs.m_mmiNameDefaultPrefix != nullptr) && (*m_mmiNameDefaultPrefix != *rhs.m_mmiNameDefaultPrefix))
                    equal = false;
                if (m_mobTelStandard == nullptr && rhs.m_mobTelStandard != nullptr)
                    equal = false;
                else if (m_mobTelStandard != nullptr && rhs.m_mobTelStandard == nullptr)
                    equal = false;
                else if ((m_mobTelStandard != nullptr) && (rhs.m_mobTelStandard != nullptr) && (*m_mobTelStandard != *rhs.m_mobTelStandard))
                    equal = false;
                if (m_onlineServiceActivationDistanceInKm != rhs.m_onlineServiceActivationDistanceInKm)
                    equal = false;
                if (m_onlineServiceBackendPrimaryHostname == nullptr && rhs.m_onlineServiceBackendPrimaryHostname != nullptr)
                    equal = false;
                else if (m_onlineServiceBackendPrimaryHostname != nullptr && rhs.m_onlineServiceBackendPrimaryHostname == nullptr)
                    equal = false;
                else if ((m_onlineServiceBackendPrimaryHostname != nullptr) && (rhs.m_onlineServiceBackendPrimaryHostname != nullptr) && (*m_onlineServiceBackendPrimaryHostname != *rhs.m_onlineServiceBackendPrimaryHostname))
                    equal = false;
                if (m_privacyGroupModifiabilitySettings == nullptr && rhs.m_privacyGroupModifiabilitySettings != nullptr)
                    equal = false;
                else if (m_privacyGroupModifiabilitySettings != nullptr && rhs.m_privacyGroupModifiabilitySettings == nullptr)
                    equal = false;
                else if ((m_privacyGroupModifiabilitySettings != nullptr) && (rhs.m_privacyGroupModifiabilitySettings != nullptr) && (*m_privacyGroupModifiabilitySettings != *rhs.m_privacyGroupModifiabilitySettings))
                    equal = false;
                if (m_pmode == nullptr && rhs.m_pmode != nullptr)
                    equal = false;
                else if (m_pmode != nullptr && rhs.m_pmode == nullptr)
                    equal = false;
                else if ((m_pmode != nullptr) && (rhs.m_pmode != nullptr) && (*m_pmode != *rhs.m_pmode))
                    equal = false;
                if (m_privacySettings == nullptr && rhs.m_privacySettings != nullptr)
                    equal = false;
                else if (m_privacySettings != nullptr && rhs.m_privacySettings == nullptr)
                    equal = false;
                else if ((m_privacySettings != nullptr) && (rhs.m_privacySettings != nullptr) && (*m_privacySettings != *rhs.m_privacySettings))
                    equal = false;
                if (m_region == nullptr && rhs.m_region != nullptr)
                    equal = false;
                else if (m_region != nullptr && rhs.m_region == nullptr)
                    equal = false;
                else if ((m_region != nullptr) && (rhs.m_region != nullptr) && (*m_region != *rhs.m_region))
                    equal = false;
                if (m_rtkLib != rhs.m_rtkLib)
                    equal = false;
                if (m_ssid2_4GHzPostfix == nullptr && rhs.m_ssid2_4GHzPostfix != nullptr)
                    equal = false;
                else if (m_ssid2_4GHzPostfix != nullptr && rhs.m_ssid2_4GHzPostfix == nullptr)
                    equal = false;
                else if ((m_ssid2_4GHzPostfix != nullptr) && (rhs.m_ssid2_4GHzPostfix != nullptr) && (*m_ssid2_4GHzPostfix != *rhs.m_ssid2_4GHzPostfix))
                    equal = false;
                if (m_ssid5GHzPostfix == nullptr && rhs.m_ssid5GHzPostfix != nullptr)
                    equal = false;
                else if (m_ssid5GHzPostfix != nullptr && rhs.m_ssid5GHzPostfix == nullptr)
                    equal = false;
                else if ((m_ssid5GHzPostfix != nullptr) && (rhs.m_ssid5GHzPostfix != nullptr) && (*m_ssid5GHzPostfix != *rhs.m_ssid5GHzPostfix))
                    equal = false;
                if (m_transmissionPower == nullptr && rhs.m_transmissionPower != nullptr)
                    equal = false;
                else if (m_transmissionPower != nullptr && rhs.m_transmissionPower == nullptr)
                    equal = false;
                else if ((m_transmissionPower != nullptr) && (rhs.m_transmissionPower != nullptr) && (*m_transmissionPower != *rhs.m_transmissionPower))
                    equal = false;
                if (m_vehicleDimensions == nullptr && rhs.m_vehicleDimensions != nullptr)
                    equal = false;
                else if (m_vehicleDimensions != nullptr && rhs.m_vehicleDimensions == nullptr)
                    equal = false;
                else if ((m_vehicleDimensions != nullptr) && (rhs.m_vehicleDimensions != nullptr) && (*m_vehicleDimensions != *rhs.m_vehicleDimensions))
                    equal = false;
                if (m_verkaufsland == nullptr && rhs.m_verkaufsland != nullptr)
                    equal = false;
                else if (m_verkaufsland != nullptr && rhs.m_verkaufsland == nullptr)
                    equal = false;
                else if ((m_verkaufsland != nullptr) && (rhs.m_verkaufsland != nullptr) && (*m_verkaufsland != *rhs.m_verkaufsland))
                    equal = false;
                if (m_wlan2_4GHzChannelNumber != rhs.m_wlan2_4GHzChannelNumber)
                    equal = false;
                if (m_wlan2_4GHzMaxChannelBandwidth != rhs.m_wlan2_4GHzMaxChannelBandwidth)
                    equal = false;
                if (m_wlan5GHzChannelNumber != rhs.m_wlan5GHzChannelNumber)
                    equal = false;
                if (m_wlan5GHzMaxChannelBandwidth != rhs.m_wlan5GHzMaxChannelBandwidth)
                    equal = false;
                return equal;
            }
            bool operator!=(const AdaptationValues& rhs) const {
                return !operator==(rhs);
            }

            AdaptationValues& operator = (const AdaptationValues& src) {
                if (this == &src) return *this;
                if (m_anonymousGuestResetSettings)
                    delete m_anonymousGuestResetSettings;
                if (src.m_anonymousGuestResetSettings) {
                    m_anonymousGuestResetSettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings(*(src.m_anonymousGuestResetSettings));
                } else {
                    m_anonymousGuestResetSettings = nullptr;
                }
                if (m_antennaPosToRefPoint)
                    delete m_antennaPosToRefPoint;
                if (src.m_antennaPosToRefPoint) {
                    m_antennaPosToRefPoint = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint(*(src.m_antennaPosToRefPoint));
                } else {
                    m_antennaPosToRefPoint = nullptr;
                }
                if (m_apnPaidServices)
                    delete m_apnPaidServices;
                if (src.m_apnPaidServices) {
                    m_apnPaidServices = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ApnPaidServices(*(src.m_apnPaidServices));
                } else {
                    m_apnPaidServices = nullptr;
                }
                m_dhcpLeaseTime = src.m_dhcpLeaseTime;
                if (m_eisSettings)
                    delete m_eisSettings;
                if (src.m_eisSettings) {
                    m_eisSettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings(*(src.m_eisSettings));
                } else {
                    m_eisSettings = nullptr;
                }
                m_era_glonass_switch = src.m_era_glonass_switch;
                m_gnssDataRate = src.m_gnssDataRate;
                m_gnssMinElevation = src.m_gnssMinElevation;
                if (m_gnssRefTime)
                    delete m_gnssRefTime;
                if (src.m_gnssRefTime) {
                    m_gnssRefTime = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::GnssRefTime(*(src.m_gnssRefTime));
                } else {
                    m_gnssRefTime = nullptr;
                }
                m_gpsSource = src.m_gpsSource;
                if (m_greyModeSettings)
                    delete m_greyModeSettings;
                if (src.m_greyModeSettings) {
                    m_greyModeSettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::GreyModeSettings(*(src.m_greyModeSettings));
                } else {
                    m_greyModeSettings = nullptr;
                }
                m_isAppleCarPlayWirelessOn = src.m_isAppleCarPlayWirelessOn;
                m_isBaiduCarLifeIosWirelessOn = src.m_isBaiduCarLifeIosWirelessOn;
                m_isBaiduCarLifeWirelessOn = src.m_isBaiduCarLifeWirelessOn;
                m_isBeiDouOn = src.m_isBeiDouOn;
                m_isRtkHdOn = src.m_isRtkHdOn;
                m_isRtkSdOn = src.m_isRtkSdOn;
                m_isCShiftHdOn = src.m_isCShiftHdOn;
                m_isCShiftSdOn = src.m_isCShiftSdOn;
                m_isGalileoOn = src.m_isGalileoOn;
                m_isGlonassOn = src.m_isGlonassOn;
                m_isGnssFrequencyL1On = src.m_isGnssFrequencyL1On;
                m_isGnssFrequencyL2On = src.m_isGnssFrequencyL2On;
                m_isGnssFrequencyL3On = src.m_isGnssFrequencyL3On;
                m_isGnssHdOverSomeIpOn = src.m_isGnssHdOverSomeIpOn;
                m_isGoogleAndroidAutoWirelessOn = src.m_isGoogleAndroidAutoWirelessOn;
                m_isGpsOn = src.m_isGpsOn;
                m_isFlightModeActive = src.m_isFlightModeActive;
                m_isInternetAccessViaWifiOn = src.m_isInternetAccessViaWifiOn;
                m_isInternetOverWlanActive = src.m_isInternetOverWlanActive;
                m_isRollenmodusActive = src.m_isRollenmodusActive;
                m_isVoLteOn = src.m_isVoLteOn;
                m_isVttLocalizationActive = src.m_isVttLocalizationActive;
                m_isWifiHotspot2_4GHzOn = src.m_isWifiHotspot2_4GHzOn;
                m_isWifiHotspot5GHzOn = src.m_isWifiHotspot5GHzOn;
                m_isWlan2_4GHzVisible = src.m_isWlan2_4GHzVisible;
                m_isWlan5GHzOn = src.m_isWlan5GHzOn;
                m_isWlan5GHzVisible = src.m_isWlan5GHzVisible;
                m_isWlanClientMode2_4GHzOn = src.m_isWlanClientMode2_4GHzOn;
                m_isWlanClientMode5GHzOn = src.m_isWlanClientMode5GHzOn;
                m_isWlanOn = src.m_isWlanOn;
                m_isWlanPasswordSynchronized = src.m_isWlanPasswordSynchronized;
                if (m_mmiNameDefaultPrefix)
                    delete m_mmiNameDefaultPrefix;
                if (src.m_mmiNameDefaultPrefix) {
                    m_mmiNameDefaultPrefix = new (ipl::nothrow)ipl::string(*(src.m_mmiNameDefaultPrefix));
                } else {
                    m_mmiNameDefaultPrefix = nullptr;
                }
                if (m_mobTelStandard)
                    delete m_mobTelStandard;
                if (src.m_mobTelStandard) {
                    m_mobTelStandard = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard(*(src.m_mobTelStandard));
                } else {
                    m_mobTelStandard = nullptr;
                }
                m_onlineServiceActivationDistanceInKm = src.m_onlineServiceActivationDistanceInKm;
                if (m_onlineServiceBackendPrimaryHostname)
                    delete m_onlineServiceBackendPrimaryHostname;
                if (src.m_onlineServiceBackendPrimaryHostname) {
                    m_onlineServiceBackendPrimaryHostname = new (ipl::nothrow)ipl::string(*(src.m_onlineServiceBackendPrimaryHostname));
                } else {
                    m_onlineServiceBackendPrimaryHostname = nullptr;
                }
                if (m_privacyGroupModifiabilitySettings)
                    delete m_privacyGroupModifiabilitySettings;
                if (src.m_privacyGroupModifiabilitySettings) {
                    m_privacyGroupModifiabilitySettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings(*(src.m_privacyGroupModifiabilitySettings));
                } else {
                    m_privacyGroupModifiabilitySettings = nullptr;
                }
                if (m_pmode)
                    delete m_pmode;
                if (src.m_pmode) {
                    m_pmode = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ProductionMode(*(src.m_pmode));
                } else {
                    m_pmode = nullptr;
                }
                if (m_privacySettings)
                    delete m_privacySettings;
                if (src.m_privacySettings) {
                    m_privacySettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettings(*(src.m_privacySettings));
                } else {
                    m_privacySettings = nullptr;
                }
                if (m_region)
                    delete m_region;
                if (src.m_region) {
                    m_region = new (ipl::nothrow)ipl::string(*(src.m_region));
                } else {
                    m_region = nullptr;
                }
                m_rtkLib = src.m_rtkLib;
                if (m_ssid2_4GHzPostfix)
                    delete m_ssid2_4GHzPostfix;
                if (src.m_ssid2_4GHzPostfix) {
                    m_ssid2_4GHzPostfix = new (ipl::nothrow)ipl::string(*(src.m_ssid2_4GHzPostfix));
                } else {
                    m_ssid2_4GHzPostfix = nullptr;
                }
                if (m_ssid5GHzPostfix)
                    delete m_ssid5GHzPostfix;
                if (src.m_ssid5GHzPostfix) {
                    m_ssid5GHzPostfix = new (ipl::nothrow)ipl::string(*(src.m_ssid5GHzPostfix));
                } else {
                    m_ssid5GHzPostfix = nullptr;
                }
                if (m_transmissionPower)
                    delete m_transmissionPower;
                if (src.m_transmissionPower) {
                    m_transmissionPower = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPower(*(src.m_transmissionPower));
                } else {
                    m_transmissionPower = nullptr;
                }
                if (m_vehicleDimensions)
                    delete m_vehicleDimensions;
                if (src.m_vehicleDimensions) {
                    m_vehicleDimensions = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::VehicleDimensions(*(src.m_vehicleDimensions));
                } else {
                    m_vehicleDimensions = nullptr;
                }
                if (m_verkaufsland)
                    delete m_verkaufsland;
                if (src.m_verkaufsland) {
                    m_verkaufsland = new (ipl::nothrow)ipl::string(*(src.m_verkaufsland));
                } else {
                    m_verkaufsland = nullptr;
                }
                m_wlan2_4GHzChannelNumber = src.m_wlan2_4GHzChannelNumber;
                m_wlan2_4GHzMaxChannelBandwidth = src.m_wlan2_4GHzMaxChannelBandwidth;
                m_wlan5GHzChannelNumber = src.m_wlan5GHzChannelNumber;
                m_wlan5GHzMaxChannelBandwidth = src.m_wlan5GHzMaxChannelBandwidth;
                return *this;
            }

                void setanonymousGuestResetSettings(const asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings* _value) {
                    if (m_anonymousGuestResetSettings)
                        delete m_anonymousGuestResetSettings;
                    if (_value) {
                        m_anonymousGuestResetSettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings(*_value);
                    } else {
                        m_anonymousGuestResetSettings = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings* getanonymousGuestResetSettings() const {
                    return m_anonymousGuestResetSettings;
                }
                    bool anonymousGuestResetSettingsValid() const {
                        return m_anonymousGuestResetSettings != nullptr;
                    }
                void setantennaPosToRefPoint(const asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint* _value) {
                    if (m_antennaPosToRefPoint)
                        delete m_antennaPosToRefPoint;
                    if (_value) {
                        m_antennaPosToRefPoint = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint(*_value);
                    } else {
                        m_antennaPosToRefPoint = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint* getantennaPosToRefPoint() const {
                    return m_antennaPosToRefPoint;
                }
                    bool antennaPosToRefPointValid() const {
                        return m_antennaPosToRefPoint != nullptr;
                    }
                void setapnPaidServices(const asi::connectivity::diagnostic::cstyle::ApnPaidServices* _value) {
                    if (m_apnPaidServices)
                        delete m_apnPaidServices;
                    if (_value) {
                        m_apnPaidServices = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ApnPaidServices(*_value);
                    } else {
                        m_apnPaidServices = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::ApnPaidServices* getapnPaidServices() const {
                    return m_apnPaidServices;
                }
                    bool apnPaidServicesValid() const {
                        return m_apnPaidServices != nullptr;
                    }
                void setdhcpLeaseTime(const uint8_t _value) {
                    m_dhcpLeaseTime = _value;
                }
                uint8_t getdhcpLeaseTime() const {
                    return m_dhcpLeaseTime;
                }
                void seteisSettings(const asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings* _value) {
                    if (m_eisSettings)
                        delete m_eisSettings;
                    if (_value) {
                        m_eisSettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings(*_value);
                    } else {
                        m_eisSettings = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings* geteisSettings() const {
                    return m_eisSettings;
                }
                    bool eisSettingsValid() const {
                        return m_eisSettings != nullptr;
                    }
                void setera_glonass_switch(const int32_t _value) {
                    m_era_glonass_switch = _value;
                }
                int32_t getera_glonass_switch() const {
                    return m_era_glonass_switch;
                }
                void setgnssDataRate(const asi::connectivity::diagnostic::cstyle::GnssDataRate _value) {
                    m_gnssDataRate = _value;
                }
                asi::connectivity::diagnostic::cstyle::GnssDataRate getgnssDataRate() const {
                    return m_gnssDataRate;
                }
                void setgnssMinElevation(const uint16_t _value) {
                    m_gnssMinElevation = _value;
                }
                uint16_t getgnssMinElevation() const {
                    return m_gnssMinElevation;
                }
                void setgnssRefTime(const asi::connectivity::diagnostic::cstyle::GnssRefTime* _value) {
                    if (m_gnssRefTime)
                        delete m_gnssRefTime;
                    if (_value) {
                        m_gnssRefTime = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::GnssRefTime(*_value);
                    } else {
                        m_gnssRefTime = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::GnssRefTime* getgnssRefTime() const {
                    return m_gnssRefTime;
                }
                    bool gnssRefTimeValid() const {
                        return m_gnssRefTime != nullptr;
                    }
                void setgpsSource(const asi::connectivity::diagnostic::cstyle::GpsSource _value) {
                    m_gpsSource = _value;
                }
                asi::connectivity::diagnostic::cstyle::GpsSource getgpsSource() const {
                    return m_gpsSource;
                }
                void setgreyModeSettings(const asi::connectivity::diagnostic::cstyle::GreyModeSettings* _value) {
                    if (m_greyModeSettings)
                        delete m_greyModeSettings;
                    if (_value) {
                        m_greyModeSettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::GreyModeSettings(*_value);
                    } else {
                        m_greyModeSettings = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::GreyModeSettings* getgreyModeSettings() const {
                    return m_greyModeSettings;
                }
                    bool greyModeSettingsValid() const {
                        return m_greyModeSettings != nullptr;
                    }
                void setisAppleCarPlayWirelessOn(const bool _value) {
                    m_isAppleCarPlayWirelessOn = _value;
                }
                bool getisAppleCarPlayWirelessOn() const {
                    return m_isAppleCarPlayWirelessOn;
                }
                void setisBaiduCarLifeIosWirelessOn(const bool _value) {
                    m_isBaiduCarLifeIosWirelessOn = _value;
                }
                bool getisBaiduCarLifeIosWirelessOn() const {
                    return m_isBaiduCarLifeIosWirelessOn;
                }
                void setisBaiduCarLifeWirelessOn(const bool _value) {
                    m_isBaiduCarLifeWirelessOn = _value;
                }
                bool getisBaiduCarLifeWirelessOn() const {
                    return m_isBaiduCarLifeWirelessOn;
                }
                void setisBeiDouOn(const bool _value) {
                    m_isBeiDouOn = _value;
                }
                bool getisBeiDouOn() const {
                    return m_isBeiDouOn;
                }
                void setisRtkHdOn(const bool _value) {
                    m_isRtkHdOn = _value;
                }
                bool getisRtkHdOn() const {
                    return m_isRtkHdOn;
                }
                void setisRtkSdOn(const bool _value) {
                    m_isRtkSdOn = _value;
                }
                bool getisRtkSdOn() const {
                    return m_isRtkSdOn;
                }
                void setisCShiftHdOn(const bool _value) {
                    m_isCShiftHdOn = _value;
                }
                bool getisCShiftHdOn() const {
                    return m_isCShiftHdOn;
                }
                void setisCShiftSdOn(const bool _value) {
                    m_isCShiftSdOn = _value;
                }
                bool getisCShiftSdOn() const {
                    return m_isCShiftSdOn;
                }
                void setisGalileoOn(const bool _value) {
                    m_isGalileoOn = _value;
                }
                bool getisGalileoOn() const {
                    return m_isGalileoOn;
                }
                void setisGlonassOn(const bool _value) {
                    m_isGlonassOn = _value;
                }
                bool getisGlonassOn() const {
                    return m_isGlonassOn;
                }
                void setisGnssFrequencyL1On(const bool _value) {
                    m_isGnssFrequencyL1On = _value;
                }
                bool getisGnssFrequencyL1On() const {
                    return m_isGnssFrequencyL1On;
                }
                void setisGnssFrequencyL2On(const bool _value) {
                    m_isGnssFrequencyL2On = _value;
                }
                bool getisGnssFrequencyL2On() const {
                    return m_isGnssFrequencyL2On;
                }
                void setisGnssFrequencyL3On(const bool _value) {
                    m_isGnssFrequencyL3On = _value;
                }
                bool getisGnssFrequencyL3On() const {
                    return m_isGnssFrequencyL3On;
                }
                void setisGnssHdOverSomeIpOn(const bool _value) {
                    m_isGnssHdOverSomeIpOn = _value;
                }
                bool getisGnssHdOverSomeIpOn() const {
                    return m_isGnssHdOverSomeIpOn;
                }
                void setisGoogleAndroidAutoWirelessOn(const bool _value) {
                    m_isGoogleAndroidAutoWirelessOn = _value;
                }
                bool getisGoogleAndroidAutoWirelessOn() const {
                    return m_isGoogleAndroidAutoWirelessOn;
                }
                void setisGpsOn(const bool _value) {
                    m_isGpsOn = _value;
                }
                bool getisGpsOn() const {
                    return m_isGpsOn;
                }
                void setisFlightModeActive(const bool _value) {
                    m_isFlightModeActive = _value;
                }
                bool getisFlightModeActive() const {
                    return m_isFlightModeActive;
                }
                void setisInternetAccessViaWifiOn(const bool _value) {
                    m_isInternetAccessViaWifiOn = _value;
                }
                bool getisInternetAccessViaWifiOn() const {
                    return m_isInternetAccessViaWifiOn;
                }
                void setisInternetOverWlanActive(const bool _value) {
                    m_isInternetOverWlanActive = _value;
                }
                bool getisInternetOverWlanActive() const {
                    return m_isInternetOverWlanActive;
                }
                void setisRollenmodusActive(const bool _value) {
                    m_isRollenmodusActive = _value;
                }
                bool getisRollenmodusActive() const {
                    return m_isRollenmodusActive;
                }
                void setisVoLteOn(const bool _value) {
                    m_isVoLteOn = _value;
                }
                bool getisVoLteOn() const {
                    return m_isVoLteOn;
                }
                void setisVttLocalizationActive(const bool _value) {
                    m_isVttLocalizationActive = _value;
                }
                bool getisVttLocalizationActive() const {
                    return m_isVttLocalizationActive;
                }
                void setisWifiHotspot2_4GHzOn(const bool _value) {
                    m_isWifiHotspot2_4GHzOn = _value;
                }
                bool getisWifiHotspot2_4GHzOn() const {
                    return m_isWifiHotspot2_4GHzOn;
                }
                void setisWifiHotspot5GHzOn(const bool _value) {
                    m_isWifiHotspot5GHzOn = _value;
                }
                bool getisWifiHotspot5GHzOn() const {
                    return m_isWifiHotspot5GHzOn;
                }
                void setisWlan2_4GHzVisible(const bool _value) {
                    m_isWlan2_4GHzVisible = _value;
                }
                bool getisWlan2_4GHzVisible() const {
                    return m_isWlan2_4GHzVisible;
                }
                void setisWlan5GHzOn(const bool _value) {
                    m_isWlan5GHzOn = _value;
                }
                bool getisWlan5GHzOn() const {
                    return m_isWlan5GHzOn;
                }
                void setisWlan5GHzVisible(const bool _value) {
                    m_isWlan5GHzVisible = _value;
                }
                bool getisWlan5GHzVisible() const {
                    return m_isWlan5GHzVisible;
                }
                void setisWlanClientMode2_4GHzOn(const bool _value) {
                    m_isWlanClientMode2_4GHzOn = _value;
                }
                bool getisWlanClientMode2_4GHzOn() const {
                    return m_isWlanClientMode2_4GHzOn;
                }
                void setisWlanClientMode5GHzOn(const bool _value) {
                    m_isWlanClientMode5GHzOn = _value;
                }
                bool getisWlanClientMode5GHzOn() const {
                    return m_isWlanClientMode5GHzOn;
                }
                void setisWlanOn(const bool _value) {
                    m_isWlanOn = _value;
                }
                bool getisWlanOn() const {
                    return m_isWlanOn;
                }
                void setisWlanPasswordSynchronized(const bool _value) {
                    m_isWlanPasswordSynchronized = _value;
                }
                bool getisWlanPasswordSynchronized() const {
                    return m_isWlanPasswordSynchronized;
                }
                void setmmiNameDefaultPrefix(const ipl::string* _value) {
                    if (m_mmiNameDefaultPrefix)
                        delete m_mmiNameDefaultPrefix;
                    if (_value) {
                        m_mmiNameDefaultPrefix = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_mmiNameDefaultPrefix = nullptr;
                    }
                }
                const ipl::string* getmmiNameDefaultPrefix() const {
                    return m_mmiNameDefaultPrefix;
                }
                    bool mmiNameDefaultPrefixValid() const {
                        return m_mmiNameDefaultPrefix != nullptr;
                    }
                void setmobTelStandard(const asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard* _value) {
                    if (m_mobTelStandard)
                        delete m_mobTelStandard;
                    if (_value) {
                        m_mobTelStandard = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard(*_value);
                    } else {
                        m_mobTelStandard = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard* getmobTelStandard() const {
                    return m_mobTelStandard;
                }
                    bool mobTelStandardValid() const {
                        return m_mobTelStandard != nullptr;
                    }
                void setonlineServiceActivationDistanceInKm(const uint8_t _value) {
                    m_onlineServiceActivationDistanceInKm = _value;
                }
                uint8_t getonlineServiceActivationDistanceInKm() const {
                    return m_onlineServiceActivationDistanceInKm;
                }
                void setonlineServiceBackendPrimaryHostname(const ipl::string* _value) {
                    if (m_onlineServiceBackendPrimaryHostname)
                        delete m_onlineServiceBackendPrimaryHostname;
                    if (_value) {
                        m_onlineServiceBackendPrimaryHostname = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_onlineServiceBackendPrimaryHostname = nullptr;
                    }
                }
                const ipl::string* getonlineServiceBackendPrimaryHostname() const {
                    return m_onlineServiceBackendPrimaryHostname;
                }
                    bool onlineServiceBackendPrimaryHostnameValid() const {
                        return m_onlineServiceBackendPrimaryHostname != nullptr;
                    }
                void setprivacyGroupModifiabilitySettings(const asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings* _value) {
                    if (m_privacyGroupModifiabilitySettings)
                        delete m_privacyGroupModifiabilitySettings;
                    if (_value) {
                        m_privacyGroupModifiabilitySettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings(*_value);
                    } else {
                        m_privacyGroupModifiabilitySettings = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings* getprivacyGroupModifiabilitySettings() const {
                    return m_privacyGroupModifiabilitySettings;
                }
                    bool privacyGroupModifiabilitySettingsValid() const {
                        return m_privacyGroupModifiabilitySettings != nullptr;
                    }
                void setpmode(const asi::connectivity::diagnostic::cstyle::ProductionMode* _value) {
                    if (m_pmode)
                        delete m_pmode;
                    if (_value) {
                        m_pmode = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ProductionMode(*_value);
                    } else {
                        m_pmode = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::ProductionMode* getpmode() const {
                    return m_pmode;
                }
                    bool pmodeValid() const {
                        return m_pmode != nullptr;
                    }
                void setprivacySettings(const asi::connectivity::diagnostic::cstyle::PrivacySettings* _value) {
                    if (m_privacySettings)
                        delete m_privacySettings;
                    if (_value) {
                        m_privacySettings = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettings(*_value);
                    } else {
                        m_privacySettings = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::PrivacySettings* getprivacySettings() const {
                    return m_privacySettings;
                }
                    bool privacySettingsValid() const {
                        return m_privacySettings != nullptr;
                    }
                void setregion(const ipl::string* _value) {
                    if (m_region)
                        delete m_region;
                    if (_value) {
                        m_region = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_region = nullptr;
                    }
                }
                const ipl::string* getregion() const {
                    return m_region;
                }
                    bool regionValid() const {
                        return m_region != nullptr;
                    }
                void setrtkLib(const asi::connectivity::diagnostic::cstyle::RtkLibrary _value) {
                    m_rtkLib = _value;
                }
                asi::connectivity::diagnostic::cstyle::RtkLibrary getrtkLib() const {
                    return m_rtkLib;
                }
                void setssid2_4GHzPostfix(const ipl::string* _value) {
                    if (m_ssid2_4GHzPostfix)
                        delete m_ssid2_4GHzPostfix;
                    if (_value) {
                        m_ssid2_4GHzPostfix = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_ssid2_4GHzPostfix = nullptr;
                    }
                }
                const ipl::string* getssid2_4GHzPostfix() const {
                    return m_ssid2_4GHzPostfix;
                }
                    bool ssid2_4GHzPostfixValid() const {
                        return m_ssid2_4GHzPostfix != nullptr;
                    }
                void setssid5GHzPostfix(const ipl::string* _value) {
                    if (m_ssid5GHzPostfix)
                        delete m_ssid5GHzPostfix;
                    if (_value) {
                        m_ssid5GHzPostfix = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_ssid5GHzPostfix = nullptr;
                    }
                }
                const ipl::string* getssid5GHzPostfix() const {
                    return m_ssid5GHzPostfix;
                }
                    bool ssid5GHzPostfixValid() const {
                        return m_ssid5GHzPostfix != nullptr;
                    }
                void settransmissionPower(const asi::connectivity::diagnostic::cstyle::TransmissionPower* _value) {
                    if (m_transmissionPower)
                        delete m_transmissionPower;
                    if (_value) {
                        m_transmissionPower = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPower(*_value);
                    } else {
                        m_transmissionPower = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::TransmissionPower* gettransmissionPower() const {
                    return m_transmissionPower;
                }
                    bool transmissionPowerValid() const {
                        return m_transmissionPower != nullptr;
                    }
                void setvehicleDimensions(const asi::connectivity::diagnostic::cstyle::VehicleDimensions* _value) {
                    if (m_vehicleDimensions)
                        delete m_vehicleDimensions;
                    if (_value) {
                        m_vehicleDimensions = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::VehicleDimensions(*_value);
                    } else {
                        m_vehicleDimensions = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::VehicleDimensions* getvehicleDimensions() const {
                    return m_vehicleDimensions;
                }
                    bool vehicleDimensionsValid() const {
                        return m_vehicleDimensions != nullptr;
                    }
                void setverkaufsland(const ipl::string* _value) {
                    if (m_verkaufsland)
                        delete m_verkaufsland;
                    if (_value) {
                        m_verkaufsland = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_verkaufsland = nullptr;
                    }
                }
                const ipl::string* getverkaufsland() const {
                    return m_verkaufsland;
                }
                    bool verkaufslandValid() const {
                        return m_verkaufsland != nullptr;
                    }
                void setwlan2_4GHzChannelNumber(const uint8_t _value) {
                    m_wlan2_4GHzChannelNumber = _value;
                }
                uint8_t getwlan2_4GHzChannelNumber() const {
                    return m_wlan2_4GHzChannelNumber;
                }
                void setwlan2_4GHzMaxChannelBandwidth(const asi::connectivity::diagnostic::cstyle::Wlan2_4GHzMaxChannelBandwidth _value) {
                    m_wlan2_4GHzMaxChannelBandwidth = _value;
                }
                asi::connectivity::diagnostic::cstyle::Wlan2_4GHzMaxChannelBandwidth getwlan2_4GHzMaxChannelBandwidth() const {
                    return m_wlan2_4GHzMaxChannelBandwidth;
                }
                void setwlan5GHzChannelNumber(const uint8_t _value) {
                    m_wlan5GHzChannelNumber = _value;
                }
                uint8_t getwlan5GHzChannelNumber() const {
                    return m_wlan5GHzChannelNumber;
                }
                void setwlan5GHzMaxChannelBandwidth(const asi::connectivity::diagnostic::cstyle::Wlan5GHzMaxChannelBandwidth _value) {
                    m_wlan5GHzMaxChannelBandwidth = _value;
                }
                asi::connectivity::diagnostic::cstyle::Wlan5GHzMaxChannelBandwidth getwlan5GHzMaxChannelBandwidth() const {
                    return m_wlan5GHzMaxChannelBandwidth;
                }


        uint8_t m_dhcpLeaseTime;
        int32_t m_era_glonass_switch;
        asi::connectivity::diagnostic::cstyle::GnssDataRate m_gnssDataRate;
        uint16_t m_gnssMinElevation;
        asi::connectivity::diagnostic::cstyle::GpsSource m_gpsSource;
        bool m_isAppleCarPlayWirelessOn;
        bool m_isBaiduCarLifeIosWirelessOn;
        bool m_isBaiduCarLifeWirelessOn;
        bool m_isBeiDouOn;
        bool m_isRtkHdOn;
        bool m_isRtkSdOn;
        bool m_isCShiftHdOn;
        bool m_isCShiftSdOn;
        bool m_isGalileoOn;
        bool m_isGlonassOn;
        bool m_isGnssFrequencyL1On;
        bool m_isGnssFrequencyL2On;
        bool m_isGnssFrequencyL3On;
        bool m_isGnssHdOverSomeIpOn;
        bool m_isGoogleAndroidAutoWirelessOn;
        bool m_isGpsOn;
        bool m_isFlightModeActive;
        bool m_isInternetAccessViaWifiOn;
        bool m_isInternetOverWlanActive;
        bool m_isRollenmodusActive;
        bool m_isVoLteOn;
        bool m_isVttLocalizationActive;
        bool m_isWifiHotspot2_4GHzOn;
        bool m_isWifiHotspot5GHzOn;
        bool m_isWlan2_4GHzVisible;
        bool m_isWlan5GHzOn;
        bool m_isWlan5GHzVisible;
        bool m_isWlanClientMode2_4GHzOn;
        bool m_isWlanClientMode5GHzOn;
        bool m_isWlanOn;
        bool m_isWlanPasswordSynchronized;
        uint8_t m_onlineServiceActivationDistanceInKm;
        asi::connectivity::diagnostic::cstyle::RtkLibrary m_rtkLib;
        uint8_t m_wlan2_4GHzChannelNumber;
        asi::connectivity::diagnostic::cstyle::Wlan2_4GHzMaxChannelBandwidth m_wlan2_4GHzMaxChannelBandwidth;
        uint8_t m_wlan5GHzChannelNumber;
        asi::connectivity::diagnostic::cstyle::Wlan5GHzMaxChannelBandwidth m_wlan5GHzMaxChannelBandwidth;
    private:
        asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings* m_anonymousGuestResetSettings;
        asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint* m_antennaPosToRefPoint;
        asi::connectivity::diagnostic::cstyle::ApnPaidServices* m_apnPaidServices;
        asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings* m_eisSettings;
        asi::connectivity::diagnostic::cstyle::GnssRefTime* m_gnssRefTime;
        asi::connectivity::diagnostic::cstyle::GreyModeSettings* m_greyModeSettings;
        ipl::string* m_mmiNameDefaultPrefix;
        asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard* m_mobTelStandard;
        ipl::string* m_onlineServiceBackendPrimaryHostname;
        asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings* m_privacyGroupModifiabilitySettings;
        asi::connectivity::diagnostic::cstyle::ProductionMode* m_pmode;
        asi::connectivity::diagnostic::cstyle::PrivacySettings* m_privacySettings;
        ipl::string* m_region;
        ipl::string* m_ssid2_4GHzPostfix;
        ipl::string* m_ssid5GHzPostfix;
        asi::connectivity::diagnostic::cstyle::TransmissionPower* m_transmissionPower;
        asi::connectivity::diagnostic::cstyle::VehicleDimensions* m_vehicleDimensions;
        ipl::string* m_verkaufsland;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::AdaptationValues& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AdaptationValues &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ADAPTATIONVALUES_CSTYLE_HXX
