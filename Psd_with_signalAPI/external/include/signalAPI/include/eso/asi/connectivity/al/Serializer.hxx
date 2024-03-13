/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SERIALIZER_HXX
#define ASI_CONNECTIVITY_AL_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <asi/connectivity/al/StructBluetoothDevice.hxx>
#include <asi/connectivity/al/StructServiceVersions.hxx>
#include <asi/connectivity/al/StructSimplePairingInformation.hxx>
#include <asi/connectivity/al/StructBtDeviceLeSecurityKeys.hxx>
#include <asi/connectivity/al/StructBtDeviceRecord.hxx>
#include <asi/connectivity/al/StructCallStatus.hxx>
#include <asi/connectivity/al/StructHfpDeviceInformation.hxx>
#include <asi/connectivity/al/StructTimestamp.hxx>
#include <asi/connectivity/al/StructCallStackEntry.hxx>
#include <asi/connectivity/al/StructNadDeviceInformation.hxx>
#include <asi/connectivity/al/StructNetwork.hxx>
#include <asi/connectivity/al/StructCallForwardingStatus.hxx>
#include <asi/connectivity/al/StructSimDataInfo.hxx>
#include <asi/connectivity/al/StructSimDataConfig.hxx>
#include <asi/connectivity/al/StructIpInfo.hxx>
#include <asi/connectivity/al/StructDataConnectionInfo.hxx>
#include <asi/connectivity/al/StructDataConnectionStartResult.hxx>
#include <asi/connectivity/al/StructNetworkInfo.hxx>
#include <asi/connectivity/al/StructNetworkRejectInformation.hxx>
#include <asi/connectivity/al/StructAntennaInfo.hxx>
#include <asi/connectivity/al/StructTemperatureInfo.hxx>
#include <asi/connectivity/al/StructAudioScenario.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::BluetoothDevice& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::BluetoothDevice &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::ServiceVersions& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::ServiceVersions &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::SimplePairingInformation& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::SimplePairingInformation &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::BtDeviceLeSecurityKeys& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::BtDeviceLeSecurityKeys &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::BtDeviceRecord& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::BtDeviceRecord &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::CallStatus& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::CallStatus &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::HfpDeviceInformation& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::HfpDeviceInformation &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::Timestamp& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::Timestamp &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::CallStackEntry& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::CallStackEntry &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::NadDeviceInformation& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::NadDeviceInformation &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::Network& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::Network &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::CallForwardingStatus& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::CallForwardingStatus &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::SimDataInfo& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::SimDataInfo &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::SimDataConfig& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::SimDataConfig &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::IpInfo& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::IpInfo &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::DataConnectionInfo& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::DataConnectionInfo &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::DataConnectionStartResult& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::DataConnectionStartResult &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::NetworkInfo& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::NetworkInfo &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::NetworkRejectInformation& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::NetworkRejectInformation &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::AntennaInfo& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::AntennaInfo &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::TemperatureInfo& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::TemperatureInfo &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::AudioScenario& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::AudioScenario &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_CONNECTIVITY_AL_DEFINITIONS_HXX
