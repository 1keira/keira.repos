/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DEFINITIONS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DEFINITIONS_CSTYLE_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>
#include <common/UUID.hxx>
#include <common/tracing/tracing.hxx>
#include <util/UnicodeString.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/SerializerErrors.hxx>

#ifdef IPL_OS_WIN32
#undef ERROR_SUCCESS
#undef ERROR_NOT_SUPPORTED
#undef ERROR_INVALID_PARAMETER
#undef ERROR_CONNECTION_REFUSED
#undef SHUTDOWN_RESTART
#endif 

namespace asi { namespace connectivity { namespace diagnostic { namespace cstyle {
    enum AdaptationId {

        PRODUCTION_MODE = 1278,
        CONNECT_BASIC_FUNCTIONS = 3020,
        ROLLENMODUS = 1275,
        CON_BOX_BASIC_FUNCTIONS = 3131,
        ECALL_CONFIGURATION = 1360,
        VERKAUFSLAND = 2889
    };
    enum AerialSwitchStatus {

        AERIAL_SWITCH_STATUS_INTERN = 0,
        AERIAL_SWITCH_STATUS_EXTERN_1 = 1,
        AERIAL_SWITCH_STATUS_EXTERN_2 = 2,
        AERIAL_SWITCH_STATUS_EXTERN_3 = 3,
        AERIAL_SWITCH_STATUS_EXTERN_4 = 4
    };
    enum AgrsResetTrigger {

        AGRS_RESET_TRIGGER_NO_TRIGGER = 0,
        AGRS_RESET_TRIGGER_ENTERING_VEHICLE = 1,
        AGRS_RESET_TRIGGER_LEAVING_VEHICLE = 2
    };
    enum AgrsSettingsChoice {

        AGRS_SETTINGS_CHOICE_DEFAULT_SETTINGS = 0,
        AGRS_SETTINGS_CHOICE_STORED_SETTINGS = 1,
        AGRS_SETTINGS_CHOICE_LAST_USER_SETTINGS = 2
    };
    enum AudioSourcesMute {

        AUDIO_SRC_MUTE_NO_MUTE = 0,
        AUDIO_SRC_MUTE_MUTE_DURING_MEC_ONLY = 1,
        AUDIO_SRC_MUTE_MUTE_DURING_ACN_ONLY = 2,
        AUDIO_SRC_MUTE_MUTE_DURING_MEC_AND_ACN = 3,
        AUDIO_SRC_MUTE_UNKNOWN = 255
    };
    enum BtLe1AntennaResistance {

        BTLE1_ANT_RESIST_10KOHM = 0,
        BTLE1_ANT_RESIST_5KOHM = 1,
        BTLE1_ANT_RESIST_UNKNOWN = 255
    };
    enum CarBrand {

        CAR_BRAND_NO_BRAND = 0,
        CAR_BRAND_AUDI = 1,
        CAR_BRAND_VW = 2,
        CAR_BRAND_SKODA = 3,
        CAR_BRAND_SEAT = 4,
        CAR_BRAND_BENTLEY = 5,
        CAR_BRAND_VW_NFZ = 6,
        CAR_BRAND_PORSCHE = 7,
        CAR_BRAND_MAN = 8,
        CAR_BRAND_LAMBORGHINI = 9,
        CAR_BRAND_UNKNOWN = 255
    };
    enum DiagDataType {

        DIAG_DATA_TYPE_ADAPTATION = 0,
        DIAG_DATA_TYPE_CODING = 1,
        DIAG_DATA_TYPE_DATASET = 2
    };
    enum DtcCode {

        MOBILE_NETWORK_ANTENNA1_SHORT_CIRCUITED_VCC = 1114369,
        MOBILE_NETWORK_ANTENNA1_SHORT_CIRCUITED_GND = 1114370,
        MOBILE_NETWORK_ANTENNA1_BREAKDOWN = 1114371,
        MOBILE_NETWORK_ANTENNA2_SHORT_CIRCUITED_VCC = 1114625,
        MOBILE_NETWORK_ANTENNA2_SHORT_CIRCUITED_GND = 1114626,
        MOBILE_NETWORK_ANTENNA2_BREAKDOWN = 1114627,
        MOBILE_NETWORK_ANTENNA3_SHORT_CIRCUITED_VCC = 1114881,
        MOBILE_NETWORK_ANTENNA3_SHORT_CIRCUITED_GND = 1114882,
        MOBILE_NETWORK_ANTENNA3_BREAKDOWN = 1114883
    };
    enum DtcErrorCondition {

        DTC_PASSED = 0,
        DTC_FAILED = 1
    };
    enum GnssDataRate {

        GNSS_DATA_RATE_1Hz = 0,
        GNSS_DATA_RATE_2Hz = 1,
        GNSS_DATA_RATE_5Hz = 2,
        GNSS_DATA_RATE_10Hz = 3,
        GNSS_DATA_RATE_UNKNOWN = 4
    };
    enum EcallDatasetAvailabilityState {

        ECALL_DATASET_AVAIL_STATE_AVAILABLE = 0,
        ECALL_DATASET_AVAIL_STATE_NOT_AVAILABLE = 1
    };
    enum EcallDatasetConfigState {

        ECALL_DATASET_CONFIG_STATE_ENABLED_VIA_DATASET = 0,
        ECALL_DATASET_CONFIG_STATE_ENABLED_VIA_BACKEND = 1,
        ECALL_DATASET_CONFIG_STATE_DISABLED_VIA_DATASET = 2,
        ECALL_DATASET_CONFIG_STATE_NOT_AVAILABLE = 3
    };
    enum EcallFunctionState {

        ECALL_FUNCTION_STATE_PRECONFIGURED = 0,
        ECALL_FUNCTION_STATE_ARMED = 1,
        ECALL_FUNCTION_STATE_DISABLED = 2,
        ECALL_FUNCTION_STATE_TEMPORAY_DISABLED = 3,
        ECALL_FUNCTION_STATE_NOT_AVAILABLE = 4
    };
    enum EcallLicenseState {

        ECALL_LICENSE_STATE_ACTIVATED = 0,
        ECALL_LICENSE_STATE_EXPIRED = 1,
        ECALL_LICENSE_STATE_NOT_LICENSED = 2,
        ECALL_LICENSE_STATE_NOT_ACTIVATED = 3,
        ECALL_LICENSE_STATE_CORE_SERVICE_STATE_NOT_RECEIVED = 4,
        ECALL_LICENSE_STATE_NOT_AVAILABLE = 5
    };
    enum EcallServiceDisabledReason {

        ECALL_SERVICE_DISABLED_REASON_INITIALY_DISABLED = 0,
        ECALL_SERVICE_DISABLED_REASON_DEACTIVATED = 1,
        ECALL_SERVICE_DISABLED_REASON_NO_PRIMARY_USER_NOMINATED = 2,
        ECALL_SERVICE_DISABLED_REASON_NO_ACTIVE_LICENSE = 3,
        ECALL_SERVICE_DISABLED_REASON_LOCALLY_SINGLE_SERVICE_DISABLED = 4,
        ECALL_SERVICE_DISABLED_REASON_LOCALLY_PRIVACY_GROUP_DISABLED = 5,
        ECALL_SERVICE_DISABLED_REASON_SWITCHED_OFF_BY_FRONTEND = 6,
        ECALL_SERVICE_DISABLED_REASON_TERMS_AND_CONDITIONS_NOT_ACCEPTED = 7,
        ECALL_SERVICE_DISABLED_REASON_NOT_CONFIGURED = 8,
        ECALL_SERVICE_DISABLED_REASON_LOCAL_VEHICLE_DISABLED = 9,
        ECALL_SERVICE_DISABLED_REASON_NONE = 10,
        ECALL_SERVICE_DISABLED_REASON_CORE_SERVICE_STATE_NOT_RECEIVED = 11,
        ECALL_SERVICE_DISABLED_REASON_NOT_AVAILABLE = 12
    };
    enum EcallServiceState {

        ECALL_SERVICE_STATE_ENABLED = 0,
        ECALL_SERVICE_STATE_DISABLED = 1,
        ECALL_SERVICE_STATE_CORE_SERVICE_STATE_NOT_RECEIVED = 2,
        ECALL_SERVICE_STATE_NOT_AVAILABLE = 3
    };
    enum ExternalControlElement {

        EXT_CTRL_ELEM_BUS_AND_DISCRETE = 0,
        EXT_CTRL_ELEM_DISCRETE = 1,
        EXT_CTRL_ELEM_NOT_INSTALLED = 2,
        EXT_CTRL_ELEM_UNKNOWN = 255
    };
    enum GmActiveUserTakeover {

        GM_ACTIVE_USER_TAKEOVER_AUTHENTICATION_NOT_REQUIRED = 0,
        GM_ACTIVE_USER_TAKEOVER_AUTHENTICATION_REQUIRED = 1
    };
    enum GmExitBehavior {

        GM_EXIT_BEHAVIOR_KEEP_PREVIOUS_ACTIVE_USER = 0,
        GM_EXIT_BEHAVIOR_ACTIVE_ASSIGNED_USER = 1,
        GM_EXIT_BEHAVIOR_ACTIVE_ANONYMOUS_GUEST = 2
    };
    enum GmExitTrigger {

        GM_EXIT_TRIGGER_LEAVING_VEHICLE = 0,
        GM_EXIT_TRIGGER_LOCKING_VEHICLE = 1
    };
    enum GpsSource {

        GPS_SOURCE_INTERN = 0,
        GPS_SOURCE_EXTERN = 1,
        GPS_SOURCE_COMBINED = 2,
        GPS_SOURCE_INTERN_AND_BUS = 3
    };
    enum MeasurementId {

        /*
        * EPP application
        */
        ROLLENMODUS_STATUS = 717,
        /*
        * GPS application
        */
        POSITION = 9264,
        RECEPTION = 9265,
        TIME = 8883,
        /*
        * NAD application
        */
        ECU_RESETS = 1025,
        SOFTWARE_VERSIONS = 4097,
        NETWORK_CONNECTIVITY = 6755,
        IMEI = 6172,
        SIM_STATUS = 6164,
        MOBILE_NETWORK_ANTENNA1_STATE = 21433,
        MOBILE_NETWORK_ANTENNA2_STATE = 21434,
        MOBILE_NETWORK_ANTENNA3_STATE = 21435,
        INTERNAL_MOBILE_NETWORK_ANTENNA_STATE = 0,
        X53CF = 1,
        TEMPERATURE = 6242,
        /*
        * Voice application
        */
        MOBILE_NETWORK_ANTENNA_SWITCH_STATUS = 21456,
        MOBILE_NETWORK_REGISTRATION_STATE = 20393,
        ONLINE_SERVICE_STATUS = 6785,
        ONLINE_SERVICE_PROVIDER_STATUS = 6764,
        CALL_STATE = 5636,
        RECENT_CALL_LIST = 6757,
        NETWORK_PROVIDER_LIST_BACKGROUND = 5635,
        ECALL_CURRENT_HEADING = 5642,
        ECALL_CURRENT_MOBILE_NETWORK_IDENTIFICATION = 20392,
        ECALL_ACTIVE_CELL_ID = 5632,
        ECALL_POSITION_CONFIDENCE = 5633,
        ECALL_DATA_SET = 16868,
        ECALL_ERA_PROFILE_STATUS = 21594,
        ECALL_ERA_ICCID = 21595
    };
    enum MicrophoneVariant {

        MIC_VARIANT_ANALOG = 0,
        MIC_VARIANT_DIGITAL = 1,
        MIC_VARIANT_UNKNOWN = 255
    };
    enum PrivacySimMode {

        PRIVACY_SIM_MODE_BACKGROUND_SCANNING = 0,
        PRIVACY_SIM_MODE_MODEM_COMPLETELY_SWITCHED_OFF = 1,
        PRIVACY_SIM_MODE_ALWAYS_ONLINE = 2
    };
    enum ResultType {

        RESULT_TYPE_SUCCESS = 0,
        RESULT_TYPE_ERROR = 1
    };
    enum RoutineId {

        ROUTINE_ID_HISTORY_DATA_RESET = 1287,
        ROUTINE_ID_DEAD_RECKONING_CALIBRATION_RESET = 1598,
        ROUTINE_ID_GNSS_RECEIVER_RESET = 1617,
        ROUTINE_ID_ANTENNA_SWITCHING_TEST = 9239,
        ROUTINE_ID_MOBILE_NETWORK_CONNECTION_TEST = 779,
        ROUTINE_ID_EMERGENCY_CALL_ESTABLISHMENT_TEST = 777,
        ROUTINE_ID_AUDIO_LOOP_BACK_TEST = 772,
        ROUTINE_ID_EMERGENCY_CALL_BACKUP_LOUDSPEAKER_TEST = 775,
        ROUTINE_ID_EMERGENCY_CALL_TESTMODE = 778,
        ROUTINE_ID_ETHERNET_TESTABILITY_ACTIVATE = 1406,
        ROUTINE_ID_ETHERNET_TESTABILITY_DEACTIVATE = 1407
    };
    enum RoutineRequestType {

        START_ROUTINE = 0,
        STOP_ROUTINE = 1,
        IDLE_ROUTINE = 2
    };
    enum RoutineState {

        ROUTINE_START_ERROR = 0,
        ROUTINE_STARTED = 1,
        ROUTINE_FINISHED = 2,
        ROUTINE_STOP_ERROR = 3,
        ROUTINE_STOPPED = 4,
        ROUTINE_ABORTED = 5
    };
    enum RtkLibrary {

        RTK_LIB_NONE = 0,
        RTK_LIB_QIANXUN = 1,
        RTK_LIB_SIXTENS = 2,
        RTK_LIB_CHINA_MOBILE = 3
    };
    enum V2xBsmFilterMode {

        V2X_BSM_FILT_MODE_STOP_ALL_BSMS = 0,
        V2X_BSM_FILT_MODE_SEND_BSMS_AFTER_FILTERING_AS_DEFINED = 1,
        V2X_BSM_FILT_MODE_SEND_BSMS_WITHOUT_FILTERING = 2,
        V2X_BSM_FILT_MODE_UNKNOWN = 255
    };
    enum ViError {

        VI_ERROR_NO_ERROR = 0,
        VI_ERROR_DATABASE_NOT_READABLE = 1,
        VI_ERROR_INVALID_DIAG_DATA_ID = 2,
        VI_ERROR_TMP_NOT_AVAILABLE = 6
    };
    enum VttNetworkStatus {

        VTT_NETWORK_STATUS_NO_INFO = 0,
        VTT_NETWORK_STATUS_NO_NETWORK_CONNECTION = 1,
        VTT_NETWORK_STATUS_PACKET_SWITCHED = 2,
        VTT_NETWORK_STATUS_CIRCUIT_SWITCHED = 3
    };
    enum Wlan2_4GHzMaxChannelBandwidth {

        WLAN_2_4_GHZ_MAX_CHANNEL_BANDWIDTH_20_MHZ = 0,
        WLAN_2_4_GHZ_MAX_CHANNEL_BANDWIDTH_40_MHZ = 1
    };
    enum Wlan5GHzMaxChannelBandwidth {

        WLAN_5_GHZ_MAX_CHANNEL_BANDWIDTH_20_MHZ = 0,
        WLAN_5_GHZ_MAX_CHANNEL_BANDWIDTH_40_MHZ = 1,
        WLAN_5_GHZ_MAX_CHANNEL_BANDWIDTH_80_MHZ = 2,
        WLAN_5_GHZ_MAX_CHANNEL_BANDWIDTH_160_MHZ = 3
    };

// Module Version
#define ASI_CONNECTIVITY_DIAGNOSTIC_VERSION ipl::string("2.8.0")
#define ASI_CONNECTIVITY_DIAGNOSTIC_VERSION_MAJOR 2
#define ASI_CONNECTIVITY_DIAGNOSTIC_VERSION_MINOR 8
#define ASI_CONNECTIVITY_DIAGNOSTIC_VERSION_PATCHLEVEL 0

// Module without version
#define ASI_CONNECTIVITY_DIAGNOSTIC_VERSION_FREE_NAMESPACE ipl::string("asi.connectivity.diagnostic")

// Interface Version
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_VERSION_MAJOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_VERSION_MINOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_VERSION_MINOR 2
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_VERSION_PATCHLEVEL 5
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTS_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTS_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTS_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_VERSION_MINOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVIMEASUREMENTS_VERSION_MAJOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVIMEASUREMENTS_VERSION_MINOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVIMEASUREMENTS_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_VERSION_MINOR 2
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_VERSION_MAJOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_VERSION_MINOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINE_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINE_VERSION_MINOR 0
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINE_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_REQUEST ipl::string("1c537063-0090-45ca-9a25-c332dfe0aef5")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_REQUEST ipl::UUID(0x1c537063, 0x0090, 0x45ca, 0x9a25, 0xc3, 0x32, 0xdf, 0xe0, 0xae, 0xf5)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_REPLY ipl::string("33f7d7dd-ae18-449c-8cd8-45686362e11d")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_REPLY ipl::UUID(0x33f7d7dd, 0xae18, 0x449c, 0x8cd8, 0x45, 0x68, 0x63, 0x62, 0xe1, 0x1d)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REQUEST ipl::string("f4b256db-a749-47a5-a343-5df73f193dcc")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REQUEST ipl::UUID(0xf4b256db, 0xa749, 0x47a5, 0xa343, 0x5d, 0xf7, 0x3f, 0x19, 0x3d, 0xcc)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REPLY ipl::string("2db9342a-fd81-4d35-a883-0f1c756ab037")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REPLY ipl::UUID(0x2db9342a, 0xfd81, 0x4d35, 0xa883, 0x0f, 0x1c, 0x75, 0x6a, 0xb0, 0x37)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST ipl::string("364e390c-6ae2-11e7-9107-1f4251663959")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST ipl::UUID(0x364e390c, 0x6ae2, 0x11e7, 0x9107, 0x1f, 0x42, 0x51, 0x66, 0x39, 0x59)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY ipl::string("3f21104a-6ae2-11e7-894d-cb47d4f48319")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY ipl::UUID(0x3f21104a, 0x6ae2, 0x11e7, 0x894d, 0xcb, 0x47, 0xd4, 0xf4, 0x83, 0x19)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_REQUEST ipl::string("61db5ecd-ef13-4c5c-8cab-fd1768bb6ddc")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_REQUEST ipl::UUID(0x61db5ecd, 0xef13, 0x4c5c, 0x8cab, 0xfd, 0x17, 0x68, 0xbb, 0x6d, 0xdc)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_REPLY ipl::string("b909453a-40cd-4916-afc4-d8e726bff095")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_REPLY ipl::UUID(0xb909453a, 0x40cd, 0x4916, 0xafc4, 0xd8, 0xe7, 0x26, 0xbf, 0xf0, 0x95)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_REQUEST ipl::string("45cf78b0-9c1d-4314-a943-f8075a4ac94e")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_REQUEST ipl::UUID(0x45cf78b0, 0x9c1d, 0x4314, 0xa943, 0xf8, 0x07, 0x5a, 0x4a, 0xc9, 0x4e)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_REPLY ipl::string("3ec0a06e-194c-4110-92b5-17753fb64e81")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_REPLY ipl::UUID(0x3ec0a06e, 0x194c, 0x4110, 0x92b5, 0x17, 0x75, 0x3f, 0xb6, 0x4e, 0x81)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTS_REQUEST ipl::string("aaa0705e-6c68-11e7-abf5-577e467e57f1")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTS_REQUEST ipl::UUID(0xaaa0705e, 0x6c68, 0x11e7, 0xabf5, 0x57, 0x7e, 0x46, 0x7e, 0x57, 0xf1)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REQUEST ipl::string("2705f76c-5d74-11e7-b49d-2b7217715e48")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REQUEST ipl::UUID(0x2705f76c, 0x5d74, 0x11e7, 0xb49d, 0x2b, 0x72, 0x17, 0x71, 0x5e, 0x48)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REPLY ipl::string("34ae4f9a-5d74-11e7-b43b-6fa63acc8a2f")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REPLY ipl::UUID(0x34ae4f9a, 0x5d74, 0x11e7, 0xb43b, 0x6f, 0xa6, 0x3a, 0xcc, 0x8a, 0x2f)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVIMEASUREMENTS_REQUEST ipl::string("00692806-a2d4-4809-ad5b-63a35adb49d7")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVIMEASUREMENTS_REQUEST ipl::UUID(0x00692806, 0xa2d4, 0x4809, 0xad5b, 0x63, 0xa3, 0x5a, 0xdb, 0x49, 0xd7)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVIMEASUREMENTS_REPLY ipl::string("684b2264-1c15-4b1c-8f1e-34f36e279a9e")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVIMEASUREMENTS_REPLY ipl::UUID(0x684b2264, 0x1c15, 0x4b1c, 0x8f1e, 0x34, 0xf3, 0x6e, 0x27, 0x9a, 0x9e)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REQUEST ipl::string("8f14ef76-6c69-11e7-a22a-eb671686647e")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REQUEST ipl::UUID(0x8f14ef76, 0x6c69, 0x11e7, 0xa22a, 0xeb, 0x67, 0x16, 0x86, 0x64, 0x7e)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REPLY ipl::string("96aa4f9c-6c69-11e7-a5a3-0b90c99268e4")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REPLY ipl::UUID(0x96aa4f9c, 0x6c69, 0x11e7, 0xa5a3, 0x0b, 0x90, 0xc9, 0x92, 0x68, 0xe4)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST ipl::string("d2a1733d-1ffd-44d8-b4a9-1c10a7b1081c")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST ipl::UUID(0xd2a1733d, 0x1ffd, 0x44d8, 0xb4a9, 0x1c, 0x10, 0xa7, 0xb1, 0x08, 0x1c)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY ipl::string("ec72087b-695b-47ed-9b0a-f6d9324f3d5e")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY ipl::UUID(0xec72087b, 0x695b, 0x47ed, 0x9b0a, 0xf6, 0xd9, 0x32, 0x4f, 0x3d, 0x5e)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_REQUEST ipl::string("de526441-ea1e-4915-b407-4f9ab714c83b")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_REQUEST ipl::UUID(0xde526441, 0xea1e, 0x4915, 0xb407, 0x4f, 0x9a, 0xb7, 0x14, 0xc8, 0x3b)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_REPLY ipl::string("bf16aad9-5d12-4dea-9cef-b5dffe370280")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_REPLY ipl::UUID(0xbf16aad9, 0x5d12, 0x4dea, 0x9cef, 0xb5, 0xdf, 0xfe, 0x37, 0x02, 0x80)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_REQUEST ipl::string("0d93867e-ab11-46ed-9cf6-eec4b456b244")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_REQUEST ipl::UUID(0x0d93867e, 0xab11, 0x46ed, 0x9cf6, 0xee, 0xc4, 0xb4, 0x56, 0xb2, 0x44)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_REPLY ipl::string("f8af161f-4021-41fc-8597-30b48e921a1c")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_REPLY ipl::UUID(0xf8af161f, 0x4021, 0x41fc, 0x8597, 0x30, 0xb4, 0x8e, 0x92, 0x1a, 0x1c)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_REQUEST ipl::string("22ee9726-6e7d-474f-a4c6-5ac37295a7ba")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_REQUEST ipl::UUID(0x22ee9726, 0x6e7d, 0x474f, 0xa4c6, 0x5a, 0xc3, 0x72, 0x95, 0xa7, 0xba)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_REPLY ipl::string("f4270931-9192-4875-91eb-7fb5f1e8818b")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_REPLY ipl::UUID(0xf4270931, 0x9192, 0x4875, 0x91eb, 0x7f, 0xb5, 0xf1, 0xe8, 0x81, 0x8b)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_REQUEST ipl::string("b9786c41-16a6-4094-8427-d93825d9041c")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_REQUEST ipl::UUID(0xb9786c41, 0x16a6, 0x4094, 0x8427, 0xd9, 0x38, 0x25, 0xd9, 0x04, 0x1c)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_REPLY ipl::string("0055c2e6-962d-400b-a240-66ff1ab4d328")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_REPLY ipl::UUID(0x0055c2e6, 0x962d, 0x400b, 0xa240, 0x66, 0xff, 0x1a, 0xb4, 0xd3, 0x28)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINE_REQUEST ipl::string("ce26f055-ea7b-475c-bcd7-e27a0c367348")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINE_REQUEST ipl::UUID(0xce26f055, 0xea7b, 0x475c, 0xbcd7, 0xe2, 0x7a, 0x0c, 0x36, 0x73, 0x48)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINE_REPLY ipl::string("23ae90df-8707-4c91-859c-0fadc468185f")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINE_REPLY ipl::UUID(0x23ae90df, 0x8707, 0x4c91, 0x859c, 0x0f, 0xad, 0xc4, 0x68, 0x18, 0x5f)

// IDSs for the attributes
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_ADAPTATIONVALUES 11
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_CODINGVALUES 9
// IDSs for the attributes
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_DATASETPARAMETERS 7
// IDSs for the attributes
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_DTCS 8
// IDSs for the attributes
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_ROUTINEREQUEST 8
// IDSs for the attributes
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVIMEASUREMENTS_HOSTNAMEREGISTERPAIRING 7
// IDSs for the attributes
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_OVERALLSOFTWAREVERSION 11
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_COMPANIONSOFTWAREVERSION 7
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_HARDWAREVERSION 10
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_SERIALNUMBER 12
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_SPAREPARTNUMBER 13
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_HARDWAREPARTNUMBER 8
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_HARDWAREVARIANT 9
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_ASSEMBLYINFORMATION 6
} //  end of namespace cstyle
} } }  // end of module namespace(s)

// Streaming operators for all enums arrays
namespace util { namespace serializer {
// Streaming operators for all enum arrays

        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::AdaptationId  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 1275:
                case 1278:
                case 1360:
                case 2889:
                case 3020:
                case 3131:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AdaptationId");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::AdaptationId & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 1275:
                    case 1278:
                    case 1360:
                    case 2889:
                    case 3020:
                    case 3131:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AdaptationId");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::AdaptationId) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::AerialSwitchStatus  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 4))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AerialSwitchStatus");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::AerialSwitchStatus & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 4))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AerialSwitchStatus");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::AerialSwitchStatus) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::AgrsResetTrigger  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AgrsResetTrigger");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::AgrsResetTrigger & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AgrsResetTrigger");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::AgrsResetTrigger) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::AgrsSettingsChoice  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AgrsSettingsChoice");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::AgrsSettingsChoice & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AgrsSettingsChoice");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::AgrsSettingsChoice) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::AudioSourcesMute  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 255:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AudioSourcesMute");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::AudioSourcesMute & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 255:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AudioSourcesMute");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::AudioSourcesMute) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::BtLe1AntennaResistance  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 0:
                case 1:
                case 255:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BtLe1AntennaResistance");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::BtLe1AntennaResistance & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 0:
                    case 1:
                    case 255:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BtLe1AntennaResistance");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::BtLe1AntennaResistance) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::CarBrand  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 255:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CarBrand");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::CarBrand & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 255:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CarBrand");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::CarBrand) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::DiagDataType  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DiagDataType");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::DiagDataType & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DiagDataType");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::DiagDataType) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::DtcCode  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 1114369:
                case 1114370:
                case 1114371:
                case 1114625:
                case 1114626:
                case 1114627:
                case 1114881:
                case 1114882:
                case 1114883:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DtcCode");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::DtcCode & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 1114369:
                    case 1114370:
                    case 1114371:
                    case 1114625:
                    case 1114626:
                    case 1114627:
                    case 1114881:
                    case 1114882:
                    case 1114883:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DtcCode");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::DtcCode) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::DtcErrorCondition  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 1))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DtcErrorCondition");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::DtcErrorCondition & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 1))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DtcErrorCondition");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::DtcErrorCondition) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::GnssDataRate  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 4))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GnssDataRate");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::GnssDataRate & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 4))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GnssDataRate");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::GnssDataRate) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 1))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallDatasetAvailabilityState");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 1))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallDatasetAvailabilityState");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 3))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallDatasetConfigState");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 3))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallDatasetConfigState");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::EcallFunctionState  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 4))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallFunctionState");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::EcallFunctionState & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 4))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallFunctionState");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::EcallFunctionState) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::EcallLicenseState  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 5))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallLicenseState");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::EcallLicenseState & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 5))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallLicenseState");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::EcallLicenseState) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 12))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallServiceDisabledReason");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 12))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallServiceDisabledReason");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::EcallServiceState  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 3))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallServiceState");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::EcallServiceState & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 3))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EcallServiceState");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::EcallServiceState) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::ExternalControlElement  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 0:
                case 1:
                case 2:
                case 255:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ExternalControlElement");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::ExternalControlElement & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 255:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ExternalControlElement");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::ExternalControlElement) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::GmActiveUserTakeover  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 1))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GmActiveUserTakeover");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::GmActiveUserTakeover & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 1))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GmActiveUserTakeover");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::GmActiveUserTakeover) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::GmExitBehavior  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GmExitBehavior");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::GmExitBehavior & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GmExitBehavior");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::GmExitBehavior) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::GmExitTrigger  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 1))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GmExitTrigger");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::GmExitTrigger & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 1))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GmExitTrigger");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::GmExitTrigger) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::GpsSource  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 3))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GpsSource");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::GpsSource & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 3))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "GpsSource");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::GpsSource) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::MeasurementId  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 0:
                case 1:
                case 717:
                case 1025:
                case 4097:
                case 5632:
                case 5633:
                case 5635:
                case 5636:
                case 5642:
                case 6164:
                case 6172:
                case 6242:
                case 6755:
                case 6757:
                case 6764:
                case 6785:
                case 8883:
                case 9264:
                case 9265:
                case 16868:
                case 20392:
                case 20393:
                case 21433:
                case 21434:
                case 21435:
                case 21456:
                case 21594:
                case 21595:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MeasurementId");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::MeasurementId & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 0:
                    case 1:
                    case 717:
                    case 1025:
                    case 4097:
                    case 5632:
                    case 5633:
                    case 5635:
                    case 5636:
                    case 5642:
                    case 6164:
                    case 6172:
                    case 6242:
                    case 6755:
                    case 6757:
                    case 6764:
                    case 6785:
                    case 8883:
                    case 9264:
                    case 9265:
                    case 16868:
                    case 20392:
                    case 20393:
                    case 21433:
                    case 21434:
                    case 21435:
                    case 21456:
                    case 21594:
                    case 21595:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MeasurementId");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::MeasurementId) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::MicrophoneVariant  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 0:
                case 1:
                case 255:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MicrophoneVariant");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::MicrophoneVariant & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 0:
                    case 1:
                    case 255:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MicrophoneVariant");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::MicrophoneVariant) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::PrivacySimMode  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "PrivacySimMode");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::PrivacySimMode & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "PrivacySimMode");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::PrivacySimMode) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::ResultType  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 1))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ResultType");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::ResultType & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 1))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ResultType");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::ResultType) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::RoutineId  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 772:
                case 775:
                case 777:
                case 778:
                case 779:
                case 1287:
                case 1406:
                case 1407:
                case 1598:
                case 1617:
                case 9239:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RoutineId");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::RoutineId & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 772:
                    case 775:
                    case 777:
                    case 778:
                    case 779:
                    case 1287:
                    case 1406:
                    case 1407:
                    case 1598:
                    case 1617:
                    case 9239:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RoutineId");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::RoutineId) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::RoutineRequestType  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RoutineRequestType");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::RoutineRequestType & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RoutineRequestType");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::RoutineRequestType) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::RoutineState  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 5))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RoutineState");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::RoutineState & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 5))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RoutineState");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::RoutineState) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::RtkLibrary  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 3))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RtkLibrary");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::RtkLibrary & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 3))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RtkLibrary");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::RtkLibrary) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::V2xBsmFilterMode  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 0:
                case 1:
                case 2:
                case 255:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "V2xBsmFilterMode");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::V2xBsmFilterMode & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 255:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "V2xBsmFilterMode");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::V2xBsmFilterMode) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::ViError  e)
        {
            int32_t value = int32_t(e);

            switch (value)
            {
                case 0:
                case 1:
                case 2:
                case 6:
                    break;
                default:
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ViError");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::ViError & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                switch (value)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 6:
                        break;
                    default:
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ViError");
                        return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::ViError) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::VttNetworkStatus  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 3))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "VttNetworkStatus");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::VttNetworkStatus & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 3))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "VttNetworkStatus");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::VttNetworkStatus) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::Wlan2_4GHzMaxChannelBandwidth  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 1))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "Wlan2_4GHzMaxChannelBandwidth");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::Wlan2_4GHzMaxChannelBandwidth & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 1))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "Wlan2_4GHzMaxChannelBandwidth");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::Wlan2_4GHzMaxChannelBandwidth) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::connectivity::diagnostic::cstyle::Wlan5GHzMaxChannelBandwidth  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 3))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "Wlan5GHzMaxChannelBandwidth");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::diagnostic::cstyle::Wlan5GHzMaxChannelBandwidth & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 3))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "Wlan5GHzMaxChannelBandwidth");
                    return true;
                }
                e = (asi::connectivity::diagnostic::cstyle::Wlan5GHzMaxChannelBandwidth) value;
            }
            return error;
        }


} } // namespace util::serializer

#endif  // ASI_CONNECTIVITY_DIAGNOSTIC_DEFINITIONS_CSTYLE_HXX
