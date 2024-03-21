/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SERIALIZER_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <asi/connectivity/al/cstyle/StructBluetoothDevice.hxx>
#include <asi/connectivity/al/cstyle/StructServiceVersions.hxx>
#include <asi/connectivity/al/cstyle/StructSimplePairingInformation.hxx>
#include <asi/connectivity/al/cstyle/StructBtDeviceLeSecurityKeys.hxx>
#include <asi/connectivity/al/cstyle/StructBtDeviceRecord.hxx>
#include <asi/connectivity/al/cstyle/StructCallStatus.hxx>
#include <asi/connectivity/al/cstyle/StructHfpDeviceInformation.hxx>
#include <asi/connectivity/al/cstyle/StructTimestamp.hxx>
#include <asi/connectivity/al/cstyle/StructCallStackEntry.hxx>
#include <asi/connectivity/al/cstyle/StructNadDeviceInformation.hxx>
#include <asi/connectivity/al/cstyle/StructNetwork.hxx>
#include <asi/connectivity/al/cstyle/StructCallForwardingStatus.hxx>
#include <asi/connectivity/al/cstyle/StructSimDataInfo.hxx>
#include <asi/connectivity/al/cstyle/StructSimDataConfig.hxx>
#include <asi/connectivity/al/cstyle/StructIpInfo.hxx>
#include <asi/connectivity/al/cstyle/StructDataConnectionInfo.hxx>
#include <asi/connectivity/al/cstyle/StructDataConnectionStartResult.hxx>
#include <asi/connectivity/al/cstyle/StructNetworkInfo.hxx>
#include <asi/connectivity/al/cstyle/StructNetworkRejectInformation.hxx>
#include <asi/connectivity/al/cstyle/StructAntennaInfo.hxx>
#include <asi/connectivity/al/cstyle/StructTemperatureInfo.hxx>
#include <asi/connectivity/al/cstyle/StructAudioScenario.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct BluetoothDevice;
struct ServiceVersions;
struct SimplePairingInformation;
struct BtDeviceLeSecurityKeys;
struct BtDeviceRecord;
struct CallStatus;
struct HfpDeviceInformation;
struct Timestamp;
struct CallStackEntry;
struct NadDeviceInformation;
struct Network;
struct CallForwardingStatus;
struct SimDataInfo;
struct SimDataConfig;
struct IpInfo;
struct DataConnectionInfo;
struct DataConnectionStartResult;
struct NetworkInfo;
struct NetworkRejectInformation;
struct AntennaInfo;
struct TemperatureInfo;
struct AudioScenario;
} // cstyle
} // namespace asi
} // namespace connectivity
} // namespace al

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::BluetoothDevice& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BluetoothDevice &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::ServiceVersions& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::ServiceVersions &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::SimplePairingInformation& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimplePairingInformation &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::BtDeviceRecord& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BtDeviceRecord &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::CallStatus& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallStatus &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::HfpDeviceInformation& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::HfpDeviceInformation &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::Timestamp& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::Timestamp &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::CallStackEntry& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallStackEntry &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::NadDeviceInformation& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NadDeviceInformation &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::Network& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::Network &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::CallForwardingStatus& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallForwardingStatus &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::SimDataInfo& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimDataInfo &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::SimDataConfig& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimDataConfig &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::IpInfo& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::IpInfo &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::DataConnectionInfo& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::DataConnectionInfo &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::DataConnectionStartResult& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::DataConnectionStartResult &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::NetworkInfo& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NetworkInfo &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::NetworkRejectInformation& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NetworkRejectInformation &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::AntennaInfo& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::AntennaInfo &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::TemperatureInfo& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::TemperatureInfo &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::cstyle::AudioScenario& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::AudioScenario &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_CONNECTIVITY_AL_SERIALIZER_CSTYLE_HXX
