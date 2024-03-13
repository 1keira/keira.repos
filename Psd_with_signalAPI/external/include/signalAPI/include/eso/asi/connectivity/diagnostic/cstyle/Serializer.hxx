/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_SERIALIZER_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructAnonymousGuestResetSettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructApnConfig.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructApnPaidServices.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructEmergencyInformationServiceSettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructGreyModeSettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructMobileTelecommunicationStandard.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructPrivacyGroupModifiabilitySettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructPrivacySettingsUser.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructPrivacySettings.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructProductionMode.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructTransmissionPowerMobNetAntenna.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructTransmissionPowerWlanAntenna.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructTransmissionPower.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructAdaptationValues.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructAntennaPosToRefPoint.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructCodingValues.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructDatasetParameter.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructDtc.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructEcallOperationStatus.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructGnssRefTime.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructRoutineRequest.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructRoutineRequestInfo.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructRoutineResponse.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructSokFreshness.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructSokTime.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructVehicleDimensions.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructViDiagDataMetadata.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructViDiagData.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructVttStatus.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct AnonymousGuestResetSettings;
struct ApnConfig;
struct ApnPaidServices;
struct EmergencyInformationServiceSettings;
struct GreyModeSettings;
struct MobileTelecommunicationStandard;
struct PrivacyGroupModifiabilitySettings;
struct PrivacySettingsUser;
struct PrivacySettings;
struct ProductionMode;
struct TransmissionPowerMobNetAntenna;
struct TransmissionPowerWlanAntenna;
struct TransmissionPower;
struct AdaptationValues;
struct AntennaPosToRefPoint;
struct CodingValues;
struct DatasetParameter;
struct Dtc;
struct EcallOperationStatus;
struct GnssRefTime;
struct RoutineRequest;
struct RoutineRequestInfo;
struct RoutineResponse;
struct SokFreshness;
struct SokTime;
struct VehicleDimensions;
struct ViDiagDataMetadata;
struct ViDiagData;
struct VttStatus;
} // cstyle
} // namespace asi
} // namespace connectivity
} // namespace diagnostic

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ApnConfig& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ApnConfig &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ApnPaidServices& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ApnPaidServices &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::GreyModeSettings& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::GreyModeSettings &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacySettingsUser &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::PrivacySettings& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacySettings &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ProductionMode& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ProductionMode &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::TransmissionPower& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPower &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::AdaptationValues& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AdaptationValues &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::CodingValues& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::CodingValues &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::DatasetParameter& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::DatasetParameter &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::Dtc& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::Dtc &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::EcallOperationStatus& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::EcallOperationStatus &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::GnssRefTime& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::GnssRefTime &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::RoutineRequest& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineRequest &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::RoutineRequestInfo& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineRequestInfo &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::RoutineResponse& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineResponse &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::SokFreshness& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::SokFreshness &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::SokTime& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::SokTime &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::VehicleDimensions& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::VehicleDimensions &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ViDiagData& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ViDiagData &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::VttStatus& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::VttStatus &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_SERIALIZER_CSTYLE_HXX
