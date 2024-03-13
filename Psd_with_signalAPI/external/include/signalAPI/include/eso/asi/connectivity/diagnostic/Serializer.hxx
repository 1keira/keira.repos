/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_SERIALIZER_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <asi/connectivity/diagnostic/StructAnonymousGuestResetSettings.hxx>
#include <asi/connectivity/diagnostic/StructApnConfig.hxx>
#include <asi/connectivity/diagnostic/StructApnPaidServices.hxx>
#include <asi/connectivity/diagnostic/StructEmergencyInformationServiceSettings.hxx>
#include <asi/connectivity/diagnostic/StructGreyModeSettings.hxx>
#include <asi/connectivity/diagnostic/StructMobileTelecommunicationStandard.hxx>
#include <asi/connectivity/diagnostic/StructPrivacyGroupModifiabilitySettings.hxx>
#include <asi/connectivity/diagnostic/StructPrivacySettingsUser.hxx>
#include <asi/connectivity/diagnostic/StructPrivacySettings.hxx>
#include <asi/connectivity/diagnostic/StructProductionMode.hxx>
#include <asi/connectivity/diagnostic/StructTransmissionPowerMobNetAntenna.hxx>
#include <asi/connectivity/diagnostic/StructTransmissionPowerWlanAntenna.hxx>
#include <asi/connectivity/diagnostic/StructTransmissionPower.hxx>
#include <asi/connectivity/diagnostic/StructAdaptationValues.hxx>
#include <asi/connectivity/diagnostic/StructAntennaPosToRefPoint.hxx>
#include <asi/connectivity/diagnostic/StructCodingValues.hxx>
#include <asi/connectivity/diagnostic/StructDatasetParameter.hxx>
#include <asi/connectivity/diagnostic/StructDtc.hxx>
#include <asi/connectivity/diagnostic/StructEcallOperationStatus.hxx>
#include <asi/connectivity/diagnostic/StructGnssRefTime.hxx>
#include <asi/connectivity/diagnostic/StructRoutineRequest.hxx>
#include <asi/connectivity/diagnostic/StructRoutineRequestInfo.hxx>
#include <asi/connectivity/diagnostic/StructRoutineResponse.hxx>
#include <asi/connectivity/diagnostic/StructSokFreshness.hxx>
#include <asi/connectivity/diagnostic/StructSokTime.hxx>
#include <asi/connectivity/diagnostic/StructVehicleDimensions.hxx>
#include <asi/connectivity/diagnostic/StructViDiagDataMetadata.hxx>
#include <asi/connectivity/diagnostic/StructViDiagData.hxx>
#include <asi/connectivity/diagnostic/StructVttStatus.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::AnonymousGuestResetSettings& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::AnonymousGuestResetSettings &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::ApnConfig& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::ApnConfig &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::ApnPaidServices& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::ApnPaidServices &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::EmergencyInformationServiceSettings& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::EmergencyInformationServiceSettings &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::GreyModeSettings& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::GreyModeSettings &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::MobileTelecommunicationStandard& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::MobileTelecommunicationStandard &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::PrivacyGroupModifiabilitySettings& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::PrivacyGroupModifiabilitySettings &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::PrivacySettingsUser& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::PrivacySettingsUser &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::PrivacySettings& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::PrivacySettings &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::ProductionMode& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::ProductionMode &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::TransmissionPowerMobNetAntenna& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::TransmissionPowerMobNetAntenna &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::TransmissionPowerWlanAntenna& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::TransmissionPowerWlanAntenna &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::TransmissionPower& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::TransmissionPower &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::AdaptationValues& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::AdaptationValues &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::AntennaPosToRefPoint& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::AntennaPosToRefPoint &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::CodingValues& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::CodingValues &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::DatasetParameter& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::DatasetParameter &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::Dtc& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::Dtc &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::EcallOperationStatus& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::EcallOperationStatus &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::GnssRefTime& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::GnssRefTime &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::RoutineRequest& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::RoutineRequest &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::RoutineRequestInfo& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::RoutineRequestInfo &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::RoutineResponse& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::RoutineResponse &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::SokFreshness& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::SokFreshness &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::SokTime& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::SokTime &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::VehicleDimensions& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::VehicleDimensions &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::ViDiagDataMetadata& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::ViDiagDataMetadata &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::ViDiagData& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::ViDiagData &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::diagnostic::VttStatus& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::diagnostic::VttStatus &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DEFINITIONS_HXX
