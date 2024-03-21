/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_DEFINITIONS_HXX
#define ASI_CONNECTIVITY_AL_DEFINITIONS_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>
#include <common/UUID.hxx>
#include <tracing/tracing.hxx>
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

namespace asi { namespace connectivity { namespace al { 
    /**
        Bluetooth Vendor IDs as registered with the Bluetooth SIG
    */
    const uint16_t BT_VENDOR_ID_AU = 270;
    const uint16_t BT_VENDOR_ID_SK = 286;
    const uint16_t BT_VENDOR_ID_VW = 287;
    const uint16_t BT_VENDOR_ID_PAG = 288;
    const uint16_t BT_VENDOR_ID_SE = 293;
    /**
        For updBtError
    */
    const uint32_t BT_BLUETOOTH_ERROR_RFCOMM_NOT_FUNCTIONAL = 1UL;
    const uint32_t BT_BLUETOOTH_ERROR_BT_CHIP_ERROR = 2UL;
    const uint32_t BT_BLUETOOTH_ERROR_OBEX_NOT_FUNCTIONAL = 3UL;
    const uint32_t BT_BLUETOOTH_ERROR_UNEXPECTED_SAP_DISC = 4UL;
    const uint32_t BT_BLUETOOTH_ERROR_AUTHENTICATE_FAILURE = 5UL;
    /**
        Extended error
    */
    const uint32_t BT_EXT_ERR_GENERAL = 0UL;
    /**
        Request cannot be served, since another action is already running
    */
    const uint32_t BT_EXT_ERR_IN_PROGRESS = 1UL;
    /**
        Service to requested device already started or beeing started
    */
    const uint32_t BT_EXT_ERR_ALREADY_STARTED = 200UL;
    const uint16_t BLUETOOTH_SERVICES_INTERFACE_ID = 1;
    const uint16_t NUM_SIMULTANEOUS_IAP_CONNECTIONS = 5;
    const int64_t INVALID_HANDLE = -1LL;
    // asi::connectivity::al
    enum ResultType {

        RESULT_TYPE_OK = 0,
        RESULT_TYPE_COMMUNICATION_ERROR = 1,
        RESULT_TYPE_ERROR = 2,
        RESULT_TYPE_INVALID_PARAMETER = 3,
        RESULT_TYPE_ERROR_NOT_SUPPORTED = 4,
        RESULT_TYPE_ERROR_WRONG_STATE = 5,
        RESULT_TYPE_ENDED_SUCCESSFULLY = 6,
        RESULT_TYPE_SERVER_TIMEOUT = 7,
        RESULT_TYPE_ERROR_BACKOFF = 8
    };
    // asi::connectivity::al
    enum InquiryMode {

        INQUIRY_MODE_DEVICES_ONLY = 0,
        INQUIRY_MODE_INCLUDE_NAME_REQUEST = 1,
        INQUIRY_MODE_INCLUDE_SERVICE_REQUEST = 2,
        INQUIRY_MODE_INCLUDE_NAME_AND_SERVICE_REQUEST = 3
    };
    // asi::connectivity::al
    enum BluetoothService {

        BLUETOOTH_SERVICE_HFP = 1,
        BLUETOOTH_SERVICE_SAP = 2,
        BLUETOOTH_SERVICE_A2DP_SNK = 4,
        BLUETOOTH_SERVICE_A2DP_SRC = 8,
        BLUETOOTH_SERVICE_AVRCP = 16,
        BLUETOOTH_SERVICE_MAP = 32,
        BLUETOOTH_SERVICE_SYNC = 64,
        BLUETOOTH_SERVICE_AT_SYNC = 128,
        BLUETOOTH_SERVICE_CTN = 256,
        BLUETOOTH_SERVICE_OPP = 512,
        BLUETOOTH_SERVICE_PAN = 1024,
        BLUETOOTH_SERVICE_IAP2 = 2048,
        BLUETOOTH_SERVICE_WIRELESS_CARPLAY = 4096,
        BLUETOOTH_SERVICE_HFP_HF = 8192,
        BLUETOOTH_SERVICE_WIRELESS_AA = 16384,
        BLUETOOTH_LE_SERVICE_LNP = 1048576,
        BLUETOOTH_LE_SERVICE_DTS = 2097152,
        BLUETOOTH_LE_SERVICE_TDS = 4194304,
        BLUETOOTH_LE_SERVICE_HOS_WIFI = 8388608
    };
    // asi::connectivity::al
    enum BluetoothServiceA2dpDetails {

        BLUETOOTH_SERVICE_DETAIL_A2DP_AAC = 1,
        BLUETOOTH_SERVICE_DETAIL_A2DP_MP3 = 2,
        BLUETOOTH_SERVICE_DETAIL_A2DP_APTX = 4
    };
    // asi::connectivity::al
    enum BluetoothServiceStatus {

        BLUETOOTH_STATUS_STARTED = 0,
        BLUETOOTH_STATUS_STARTING_FAILED = 1,
        BLUETOOTH_STATUS_STOPPED = 2,
        BLUETOOTH_STATUS_STOPPING_FAILED = 3
    };
    // asi::connectivity::al
    enum PairingState {

        PAIRING_STATE_CONNECT_FAILED_UNKNOWN_REASON = 0,
        PAIRING_STATE_CONNECT_FAILED_WRONG_PASSKEY = 1,
        PAIRING_STATE_CONNECT_FAILED_TOO_MANY_DEVICES = 2,
        PAIRING_STATE_CONNECT_FAILED_TIMEOUT = 3,
        PAIRING_STATE_CONNECT_FAILED_SECURITY_REASONS = 4,
        PAIRING_STATE_CONNECT_FAILED_REJECTED = 5,
        PAIRING_STATE_CONNECT_FAILED_AUTH_FAILURE = 6,
        PAIRING_STATE_CONNECT_NOT_FOUND = 7,
        PAIRING_STATE_DISCONNECT_OK = 8,
        PAIRING_STATE_PAIRING_OK = 9
    };
    // asi::connectivity::al
    enum SecureSimplePairingMethod {

        SSP_METHOD_JUST_WORKS = 1,
        SSP_METHOD_PASSKEY_ENTRY_INPUT = 2,
        SSP_METHOD_PASSKEY_ENTRY_DISPLAY = 3
    };
    // asi::connectivity::al
    enum SecureSimplePairingCapability {

        SSP_CAPABILITY_DISPLAY_ONLY = 0,
        SSP_CAPABILITY_DISPLAY_YES_NO = 1,
        SSP_CAPABILITY_KEYBOARD_ONLY = 2,
        SSP_CAPABILITY_NO_INPUT_NO_OUTPUT = 3
    };
    // asi::connectivity::al
    enum SupportedPairingMethod {

        SPM_UNKNOWN = 0,
        SPM_LEGACY = 1,
        SPM_SSP = 2
    };
    // asi::connectivity::al
    enum BtSniffMode {

        BTSM_OFF = 0,
        BTSM_PASSIVE = 1,
        BTSM_ACTIVE = 2
    };
    // asi::connectivity::al
    enum LinkkeyType {

        LKT_UNKNOWN = 0,
        LKT_WEAK = 1,
        LKT_STRONG = 2
    };
    // asi::connectivity::al
    enum MobileDeviceInfoType {

        MDIT_CGMI = 0,
        MDIT_CGMM = 1,
        MDIT_CGMR = 2
    };
    /**
         Set Handsfree mode
    *  possible handsfree modes to set
    
    */
    // asi::connectivity::al
    enum HandsfreeMode {

        HandsfreeMode_Off = 0,
        HandsfreeMode_On = 1
    };
    /**
         Network registration state 
    */
    // asi::connectivity::al
    enum NetworkState {

        NETWORK_STATE_UNKNOWN = 0,
        NETWORK_STATE_REGISTERED = 1,
        NETWORK_STATE_NOT_REGISTERED = 2
    };
    /**
         Roaming status (home or visited) 
    */
    // asi::connectivity::al
    enum RoamingState {

        ROAMING_STATE_UNKNOWN = 0,
        ROAMING_STATE_HOME_NETWORK = 1,
        ROAMING_STATE_VISITED_NETWORK = 2
    };
    // asi::connectivity::al
    enum CallState {

        CallState_Free = -1,
        CallState_Active = 0,
        CallState_Hold = 1,
        CallState_Outgoing_Dialing = 2,
        CallState_Outgoing_Ringing = 3,
        CallState_Incoming = 4,
        CallState_Waiting = 5,
        CallState_Call_Terminated = 6
    };
    // asi::connectivity::al
    enum CallDirection {

        Mobile_Originated_Call = 0,
        Mobile_Terminated_Call = 1
    };
    // asi::connectivity::al
    enum SupportedHfpFeatures {

        HFP_FEATURE_REJECT_CALL = 1,
        HFP_FEATURE_INBAND_RING = 2,
        HFP_FEATURE_3WAY_CALL = 4,
        HFP_FEATURE_JOIN_CONF = 8,
        HFP_FEATURE_ENHANCED_CALL_STATUS = 16,
        HFP_FEATURE_ENHANCED_CALL_CTRL = 32,
        HFP_FEATURE_ENHANCED_CONF_TRANSFER = 64,
        HFP_FEATURE_RESPONSE_AND_HOLD = 128,
        HFP_FEATURE_VOICE_RECOGNITION = 256,
        HFP_FEATURE_INVALID = 65535
    };
    // asi::connectivity::al
    enum HfpVersion {

        HFP_VERSION_0_96 = 0,
        HFP_VERSION_1_00 = 1,
        HFP_VERSION_1_50 = 2,
        HFP_VERSION_1_60 = 3,
        HFP_VERSION_1_70 = 4,
        HFP_VERSION_UNKNOWN = 5,
        HFP_VERSION_INVALID = 6
    };
    // asi::connectivity::al
    enum HfpAudioPolicy {

        HFP_AUDIO_POLICY_ACCEPT = 0,
        HFP_AUDIO_POLICY_REJECT = 1
    };
    // asi::connectivity::al
    enum VoiceRecognitionFlavor {

        VOICE_RECOGNTION_NO_FLAVOR = 0,
        VOICE_RECOGNTION_SIRI_FLAVOR = 1,
        VOICE_RECOGNTION_GOOGLE_NOW_FLAVOR = 2
    };
    // asi::connectivity::al
    enum NetworkType {

        NETWORK_TYPE_UNKNOWN = 0,
        NETWORK_TYPE_GSM = 1,
        NETWORK_TYPE_GPRS = 2,
        NETWORK_TYPE_EDGE = 3,
        NETWORK_TYPE_UMTS = 4,
        NETWORK_TYPE_HSPA = 5,
        NETWORK_TYPE_LTE = 6,
        NETWORK_TYPE_LTE_ADVANCED = 7,
        NETWORK_TYPE_5G = 8
    };
    // asi::connectivity::al
    enum NetworkDomain {

        NETWORK_DOMAIN_UNKNOWN = 0,
        NETWORK_TYPE_CS = 1,
        NETWORK_TYPE_PS = 2,
        NETWORK_TYPE_CS_PS = 3
    };
    // asi::connectivity::al
    enum DeviceType {

        DEVICE_TYPE_HFP_PHONE = 0,
        DEVICE_TYPE_NAD = 1,
        DEVICE_TYPE_UNKNOWN = 2
    };
    // asi::connectivity::al
    enum SimType {

        /*
        Unknown SIM type
        */
        ST_UNKNOWN = 0,
        /*
        Local/SAP costumer SIM available
        */
        ST_CUSTOMER = 1,
        /*
        Only embedded SIM available
        */
        ST_EMBEDDED = 2
    };
    // asi::connectivity::al
    enum UssdResultCode {

        USSD_IDLE = 0,
        USSD_SESSION = 1,
        USSD_TERMINATED = 2,
        USSD_OTHER_CLIENT_RESPONDED = 3,
        USSD_OPERATION_NOT_SUPPORTED = 4,
        USSD_NETWORK_TIMEOUT = 5
    };
    // asi::connectivity::al
    enum HfpError {

        /*
        Error communicating with phone
        */
        HFP_ERROR = 0,
        /*
        General error on dialing
        */
        HFP_DIAL_ERROR = 1,
        HFP_ERROR_BTRH_NOT_SUPPORTED = 2,
        /*
        HFP disconnect reason
        */
        HFP_DIAL_ERROR_NO_CARRIER = 3,
        HFP_DIAL_ERROR_NO_DIALTONE = 4,
        HFP_DIAL_ERROR_BUSY = 5,
        HFP_DIAL_ERROR_BLACKLISTED = 6,
        HFP_DIAL_ERROR_NO_ANSWER = 7,
        HFP_DIAL_ERROR_DELAYED = 8
    };
    // asi::connectivity::al
    enum CallStackType {

        CALLSTACKTYPE_FIRST = 0,
        CALLSTACKTYPE_LAST_DIALED = 0,
        CALLSTACKTYPE_LAST_RECEIVED = 1,
        CALLSTACKTYPE_MISSED_CALLS = 2,
        CALLSTACKTYPE_MAX = 3
    };
    // asi::connectivity::al
    enum CallStackDownloadStatus {

        CALLSTACK_DOWNLOAD_FINISHED = 0,
        CALLSTACK_DOWNLOAD_FINISHED_NOTHING_CHANGED = 1,
        CALLSTACK_DOWNLOAD_ABORTED = 2,
        CALLSTACK_DOWNLOAD_FAILED = 3,
        CALLSTACK_DOWNLOAD_SOURCE_DISAPPEARED = 4
    };
    // asi::connectivity::al
    enum NadState {

        NAD_OFF = 0,
        NAD_ON = 1,
        NAD_ON_CPIN = 2,
        NAD_ON_CPIN2 = 3,
        NAD_ON_CPUK = 4,
        NAD_ON_CPUK2 = 5,
        NAD_READY = 6,
        NAD_TEMP_OFF = 7,
        NAD_UNKNOWN = 8
    };
    // asi::connectivity::al
    enum SimSource {

        SIM_SOURCE_INTERNAL = 0,
        SIM_SOURCE_SAP = 1,
        SIM_SOURCE_EMBEDDED = 2,
        SIM_SOURCE_EXTERNAL = 3
    };
    // asi::connectivity::al
    enum ActiveSimSource {

        ACTIVE_SIM_SOURCE_INTERNAL = 0,
        ACTIVE_SIM_SOURCE_SAP = 1,
        ACTIVE_SIM_SOURCE_EMBEDDED = 2,
        ACTIVE_SIM_SOURCE_EXTERNAL = 3,
        ACTIVE_SIM_SOURCE_NONE = 255
    };
    // asi::connectivity::al
    enum SimPinType {

        SIM_PIN_TYPE_PIN = 0,
        SIM_PIN_TYPE_PIN2 = 1,
        SIM_PIN_TYPE_PUK = 2,
        SIM_PIN_TYPE_PUK2 = 3
    };
    // asi::connectivity::al
    enum NadError {

        NAD_ERR_INIT_FAIL = 0,
        NAD_ERR_NO_SIM = 1,
        NAD_ERR_SIM_FAILURE = 2,
        NAD_ERR_BAD_PIN = 3,
        NAD_ERR_BAD_PUK = 4,
        NAD_ERR_SIM_TYPE = 5,
        NAD_ERR_SIM_BUSY = 6,
        NAD_ERR_SIM_LOCKED = 7,
        NAD_ERR_DIAL = 8,
        NAD_ERR_NO_CARRIER = 9,
        NAD_ERR_BUSY = 10,
        NAD_ERR_NO_ANSWER = 11,
        NAD_ERR_NO_DIALTONE = 12,
        NAD_ERR_BAD_LOGIN = 13,
        NAD_ERR_BAD_NETWORK = 14,
        NAD_ERR_BAD_STATE = 15,
        NAD_ERR_SAP_FAILURE = 16,
        NAD_ERR_CONN_REJECTED = 17,
        NAD_ERR_CONN_TIMEOUT = 18,
        NAD_ERR_NO_DNS = 19,
        NAD_ERR_CMEE = 20,
        NAD_ERR_UNKNOWN = 21
    };
    // asi::connectivity::al
    enum NetworkAvailibility {

        NET_AVAIL_UNKNOWN = 0,
        NET_AVAIL_AVAILABLE = 1,
        NET_AVAIL_CURRENT = 2,
        NET_AVAIL_FORBIDDEN = 3
    };
    // asi::connectivity::al
    enum ClirState {

        CLIR_STATE_NETWORK = 0,
        CLIR_STATE_SUPPRESSED = 1,
        CLIR_STATE_NOT_SUPPRESSED = 2
    };
    // asi::connectivity::al
    enum ClirNwState {

        CLIR_NW_STATE_NOT_PROVISIONED = 0,
        CLIR_NW_STATE_PROVISIONED_PERMANENTLY = 1,
        CLIR_NW_STATE_UNKNOWN = 2,
        CLIR_NW_STATE_TEMPORARY_RESTRICED = 3,
        CLIR_NW_STATE_TEMPORARY_ALLOWED = 4
    };
    // asi::connectivity::al
    enum CfcReason {

        CFC_REASON_UNCONDITIONAL = 0,
        CFC_REASON_BUSY = 1,
        CFC_REASON_NO_REPLY = 2,
        CFC_REASON_NOT_REACHABLE = 3,
        CFC_REASON_ALL_CALLS = 4,
        CFC_REASON_ALL_CONDITIONAL_CALLS = 5
    };
    // asi::connectivity::al
    enum ServiceClass {

        SERVICE_CLASS_VOICE = 1,
        SERVICE_CLASS_DATA = 2,
        SERVICE_CLASS_FAX = 4,
        SERVICE_CLASS_SMS = 8,
        SERVICE_CLASS_DATA_CIRCUIT_SYNC = 16,
        SERVICE_CLASS_DATA_CIRCUIT_ASYNC = 32,
        SERVICE_CLASS_PACKET_ACCESS = 64,
        SERVICE_CLASS_PAD_ACCESS = 128
    };
    // asi::connectivity::al
    enum NadTempThresholdLevel {

        NAD_TEMP_LEVEL_EXTREME_LOWER_BOUND = -2,
        NAD_TEMP_LEVEL_OPERATING_LOWER_BOUND = -1,
        NAD_TEMP_LEVEL_NORMAL_TEMPERATURE = 0,
        NAD_TEMP_LEVEL_HIGHER_TEMPERATURE = 1,
        NAD_TEMP_LEVEL_OPERATING_UPPER_BOUND = 2,
        NAD_TEMP_LEVEL_EXTREME_UPPER_BOUND = 3
    };
    // asi::connectivity::al
    enum NadEvent {

        NAD_EVENT_SIM_PIN_CHANGED = 0,
        NAD_EVENT_SAP_MODE_CHANGED = 1,
        NAD_EVENT_NETWORK_SELECTION_MODE_CHANGED = 2,
        NAD_EVENT_HANDOVER_PARAMETERS_SET = 3,
        NAD_EVENT_AIRPLANE_MODE_SWITCHED = 4
    };
    // asi::connectivity::al
    enum AntennaState {

        ANTENNA_STATE_UNKNOWN = 0,
        ANTENNA_STATE_OK = 1,
        ANTENNA_STATE_DISCONNECTED = 2,
        ANTENNA_STATE_SHORT_CIRCUITED_GND = 3,
        ANTENNA_STATE_SHORT_CIRCUITED_VCC = 4
    };
    // asi::connectivity::al
    enum RegState {

        REG_STATE_NOT_REGISTERED = 0,
        REG_STATE_NOT_REGISTERED_LIMITED_SERVICE = 1,
        REG_STATE_REGISTERED_HOME = 2,
        REG_STATE_SEARCHING = 3,
        REG_STATE_DENIED = 4,
        REG_STATE_UNKNOWN = 5,
        REG_STATE_REGISTERED_ROAMING = 6
    };
    // asi::connectivity::al
    enum ServiceDomain {

        SERVICE_DOMAIN_NO_SERVICE = 0,
        SERVICE_DOMAIN_CS_ONLY = 1,
        SERVICE_DOMAIN_PS_ONLY = 2,
        SERVICE_DOMAIN_CS_PS = 3
    };
    // asi::connectivity::al
    enum DataConnectionState {

        DCS_UNKNOWN = 0,
        DCS_CONNECTING = 1,
        DCS_CONNECTED = 2,
        DCS_SUSPENDED = 3,
        DCS_DISCONNECTING = 4,
        DCS_DISCONNECTED = 5,
        DCS_TEMPORARY_DISCONNECTED = 6
    };
    // asi::connectivity::al
    enum AirplaneMode {

        AIRPLANE_MODE_OFF = 0,
        /*
        RF off
        */
        AIRPLANE_MODE_ON = 1,
        /*
        RF off, SIM off
        */
        AIRPLANE_MODE_ON_NO_SIM = 2,
        /*
        RF off, SIM off, Safety Mode
        */
        AIRPLANE_MODE_ON_SAFETY_MODE = 3
    };
    // asi::connectivity::al
    enum DormantMode {

        DORMANT_MODE_UNKNOWN = -1,
        DORMANT_MODE_OFF = 0,
        DORMANT_MODE_ON = 1
    };
    // asi::connectivity::al
    enum EraGlonassStatus {

        ERA_GLONASS_STATUS_NOT_AVAILABLE = 0,
        ERA_GLONASS_STATUS_AVAIL_NOT_ACTIVE = 1,
        ERA_GLONASS_STATUS_AVAIL_IS_ACTIVE = 2
    };
    /**
        
     * These values have been deliberately kept the same as those returned by the Huawei SDK
     * All the statuses, including the non-erroneous ones must be present.
     
    */
    // asi::connectivity::al
    enum SIMError {

        SIM_STATUS_UNKNOWN = -1,
        SIM_STATUS_NO_SIM = 0,
        SIM_STATUS_INSERTED = 1,
        SIM_STATUS_PIN_PUK_LOCK = 2,
        SIM_STATUS_BEING_INIT = 10,
        SIM_STATUS_INITED = 11,
        SIM_STATUS_READY = 12,
        SIM_STATUS_INVALID = 98,
        SIM_STATUS_REMOVED = 99,
        SIM_STATUS_EXP_EXCEP = 100
    };
    // asi::connectivity::al
    enum SimState {

        SIM_STATE_UNKNOWN = 0,
        SIM_STATE_NO_SIM = 1,
        SIM_STATE_PRESENT = 2,
        SIM_STATE_READY = 3,
        SIM_STATE_INVALID = 4
    };
    // asi::connectivity::al
    enum SimProfileId {

        SIM_PROFILE_ID_COMMERCIAL = 0,
        SIM_PROFILE_ID_ERA_GLONASS = 1,
        SIM_PROFILE_ID_BOOTSTRAP = 2
    };
    // asi::connectivity::al
    enum AntennasScenario {

        ANTENNAS_SCENARIO_UNKNOWN = -1,
        ANTENNAS_SCENARIO_0 = 0,
        ANTENNAS_SCENARIO_1 = 1,
        ANTENNAS_SCENARIO_2 = 2,
        ANTENNAS_SCENARIO_3 = 3,
        ANTENNAS_SCENARIO_4 = 4,
        ANTENNAS_SCENARIO_5 = 5,
        ANTENNAS_SCENARIO_6 = 6
    };
    // asi::connectivity::al
    enum BatteryState {

        NORMAL = 0,
        BACKUP = 1,
        BACKUP_LOW_TEMPERATURE = 2
    };
    // asi::connectivity::al
    enum configParam {

        CP_IMSI = 0,
        CP_ICCID = 1,
        CP_IMEI = 2,
        CP_NAME = 3,
        CP_ESPN = 4,
        CP_APN = 5,
        CP_LOGIN = 6,
        CP_PASSWORD = 7,
        CP_MANUFACTURER = 8,
        CP_MODEL = 9,
        CP_REVISION = 10,
        CP_SERIALNUMBER = 11,
        CP_DATA_MODE = 12
    };
    // asi::connectivity::al
    enum VolteSupport {

        VOLTE_SUPPORT_UNKNOWN = -1,
        VOLTE_NOT_SUPPORTED = 0,
        VOLTE_SUPPORTED = 1
    };
    // asi::connectivity::al
    enum CSRatsSupport {

        CS_2G_3G_SUPPORT_UNKNOWN = -1,
        CS_2G_3G_NOT_SUPPORTED = 0,
        CS_2G_3G_SUPPORTED = 1
    };
    // asi::connectivity::al
    enum BipRouteResult {

        BIP_ROUTE_RESULT_OK = 0,
        BIP_ROUTE_RESULT_GENERAL_ERROR = 1
    };
    // asi::connectivity::al
    enum SmsType {

        SMS_TYPE_UNKNOWN = -1,
        SMS_TYPE_NORMAL_NEW_MSG = 0,
        SMS_TYPE_STATUS_REPORT = 1,
        SMS_TYPE_SUBMIT_REPORT = 2
    };
    // asi::connectivity::al
    enum SmsCbmReportType {

        SMS_CBS_REPORT_UNKNOWN = -1,
        SMS_CBS_CMAS_MSG = 0,
        SMS_CBS_ETWS_MSG = 1
    };
    // asi::connectivity::al
    enum JammingStatus {

        JAMMING_STATUS_UNKNOWN = -1,
        JAMMING_STATUS_NOT_JAMMED = 0,
        JAMMING_STATUS_JAMMED = 1
    };
    // asi::connectivity::al
    enum AudioState {

        UNKNOWN = -1,
        IDLE = 0,
        PLAYING = 1,
        RECORDING = 2,
        PLAYBACK_STOPPED = 3,
        RECORDING_STOPPED = 4
    };

// Module Version
#define ASI_CONNECTIVITY_AL_VERSION ipl::string("1.0.1")
#define ASI_CONNECTIVITY_AL_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_VERSION_MINOR 0
#define ASI_CONNECTIVITY_AL_VERSION_PATCHLEVEL 1

// Module without version
#define ASI_CONNECTIVITY_AL_VERSION_FREE_NAMESPACE ipl::string("asi.connectivity.al")

// Interface Version
#define ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_VERSION_MINOR 5
#define ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_HANDSFREESERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_HANDSFREESERVICES_VERSION_MINOR 0
#define ASI_CONNECTIVITY_AL_HANDSFREESERVICES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_VERSION_MINOR 1
#define ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_VERSION_MINOR 1
#define ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_VERSION_MINOR 3
#define ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_NADSERVICES_VERSION_MAJOR 2
#define ASI_CONNECTIVITY_AL_NADSERVICES_VERSION_MINOR 1
#define ASI_CONNECTIVITY_AL_NADSERVICES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_NADDATASERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_NADDATASERVICES_VERSION_MINOR 2
#define ASI_CONNECTIVITY_AL_NADDATASERVICES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_VERSION_MINOR 0
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_VERSION_PATCHLEVEL 1
#define ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_VERSION_MINOR 0
#define ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_VERSION_MINOR 0
#define ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST ipl::string("3b8fb5ed-21b3-47c4-cafe-f6b50bdbfec1")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST ipl::UUID(0x3b8fb5ed, 0x21b3, 0x47c4, 0xcafe, 0xf6, 0xb5, 0x0b, 0xdb, 0xfe, 0xc1)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x05, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000100050000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY ipl::string("326375d1-4601-4e9b-cafe-2e22e311dc74")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY ipl::UUID(0x326375d1, 0x4601, 0x4e9b, 0xcafe, 0x2e, 0x22, 0xe3, 0x11, 0xdc, 0x74)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x05, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY ipl::string("00010000-0001-6000-0000-000100050000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REQUEST ipl::string("aeab146d-92a1-4ee7-a63a-b294a35dede6")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REQUEST ipl::UUID(0xaeab146d, 0x92a1, 0x4ee7, 0xa63a, 0xb2, 0x94, 0xa3, 0x5d, 0xed, 0xe6)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REPLY ipl::string("16369430-dfdd-402b-b811-2367f0361ddc")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REPLY ipl::UUID(0x16369430, 0xdfdd, 0x402b, 0xb811, 0x23, 0x67, 0xf0, 0x36, 0x1d, 0xdc)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REPLY ipl::string("00010000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REQUEST ipl::string("1986cd30-6f54-4b96-93fc-168c74920c51")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REQUEST ipl::UUID(0x1986cd30, 0x6f54, 0x4b96, 0x93fc, 0x16, 0x8c, 0x74, 0x92, 0x0c, 0x51)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000100010000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REPLY ipl::string("26dc280b-4ec2-43dc-9104-893d0c3ba09a")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REPLY ipl::UUID(0x26dc280b, 0x4ec2, 0x43dc, 0x9104, 0x89, 0x3d, 0x0c, 0x3b, 0xa0, 0x9a)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REPLY ipl::string("00010000-0001-6000-0000-000100010000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REQUEST ipl::string("5b293249-abd0-43d9-9d52-e9d1105afcb5")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REQUEST ipl::UUID(0x5b293249, 0xabd0, 0x43d9, 0x9d52, 0xe9, 0xd1, 0x10, 0x5a, 0xfc, 0xb5)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000100010000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REPLY ipl::string("d27a4ee3-3e2d-4c50-8a65-775c6d7a3bda")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REPLY ipl::UUID(0xd27a4ee3, 0x3e2d, 0x4c50, 0x8a65, 0x77, 0x5c, 0x6d, 0x7a, 0x3b, 0xda)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REPLY ipl::string("00010000-0001-6000-0000-000100010000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REQUEST ipl::string("d5501999-2658-4fd3-ac09-1b180c346f9a")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REQUEST ipl::UUID(0xd5501999, 0x2658, 0x4fd3, 0xac09, 0x1b, 0x18, 0x0c, 0x34, 0x6f, 0x9a)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000100030000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REPLY ipl::string("5b591800-60b9-4e17-889a-bb0f32b7b61c")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REPLY ipl::UUID(0x5b591800, 0x60b9, 0x4e17, 0x889a, 0xbb, 0x0f, 0x32, 0xb7, 0xb6, 0x1c)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REPLY ipl::string("00010000-0001-6000-0000-000100030000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADSERVICES_REQUEST ipl::string("55498ae5-236a-4872-8cda-db255d76c364")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADSERVICES_REQUEST ipl::UUID(0x55498ae5, 0x236a, 0x4872, 0x8cda, 0xdb, 0x25, 0x5d, 0x76, 0xc3, 0x64)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADSERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADSERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000200010000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADSERVICES_REPLY ipl::string("d7a8f11d-195f-44b1-a336-0ad032cc8c82")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADSERVICES_REPLY ipl::UUID(0xd7a8f11d, 0x195f, 0x44b1, 0xa336, 0x0a, 0xd0, 0x32, 0xcc, 0x8c, 0x82)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADSERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADSERVICES_REPLY ipl::string("00010000-0001-6000-0000-000200010000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADDATASERVICES_REQUEST ipl::string("89e38ea2-5d36-448d-a4cb-b0066b71563f")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADDATASERVICES_REQUEST ipl::UUID(0x89e38ea2, 0x5d36, 0x448d, 0xa4cb, 0xb0, 0x06, 0x6b, 0x71, 0x56, 0x3f)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADDATASERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADDATASERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000100020000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADDATASERVICES_REPLY ipl::string("dac3d630-56a1-479b-a0ad-b597180245b7")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADDATASERVICES_REPLY ipl::UUID(0xdac3d630, 0x56a1, 0x479b, 0xa0ad, 0xb5, 0x97, 0x18, 0x02, 0x45, 0xb7)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADDATASERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADDATASERVICES_REPLY ipl::string("00010000-0001-6000-0000-000100020000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REQUEST ipl::string("f3eaa829-27f0-4dbd-9839-885a8ed77b50")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REQUEST ipl::UUID(0xf3eaa829, 0x27f0, 0x4dbd, 0x9839, 0x88, 0x5a, 0x8e, 0xd7, 0x7b, 0x50)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REQUEST ipl::string("00010000-0001-6000-0000-000100000001")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REPLY ipl::string("627977d9-d125-411c-86d3-4aaa7f89621d")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REPLY ipl::UUID(0x627977d9, 0xd125, 0x411c, 0x86d3, 0x4a, 0xaa, 0x7f, 0x89, 0x62, 0x1d)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REPLY ipl::string("00010000-0001-6000-0000-000100000001")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REQUEST ipl::string("8fdd3d31-76f0-4260-a429-07111bf5809b")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REQUEST ipl::UUID(0x8fdd3d31, 0x76f0, 0x4260, 0xa429, 0x07, 0x11, 0x1b, 0xf5, 0x80, 0x9b)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLY ipl::string("6afd1802-4ddc-40de-af28-411544ef7f95")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLY ipl::UUID(0x6afd1802, 0x4ddc, 0x40de, 0xaf28, 0x41, 0x15, 0x44, 0xef, 0x7f, 0x95)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLY ipl::string("00010000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REQUEST ipl::string("bc8db989-6e8f-4554-9600-936795b71722")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REQUEST ipl::UUID(0xbc8db989, 0x6e8f, 0x4554, 0x9600, 0x93, 0x67, 0x95, 0xb7, 0x17, 0x22)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REQUEST ipl::string("00010000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REPLY ipl::string("5b3b1f6b-bbd9-4327-9757-701b5f0421a8")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REPLY ipl::UUID(0x5b3b1f6b, 0xbbd9, 0x4327, 0x9757, 0x70, 0x1b, 0x5f, 0x04, 0x21, 0xa8)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REPLY ipl::string("00010000-0001-6000-0000-000100000000")

// IDSs for the attributes
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_ANTENNAINFO 20
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_DATACONNECTIONINFO 21
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_SIMDATACONFIG 31
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_DATACONNECTIONSTARTRESULT 22
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_NADDEVICEINFORMATION 27
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_NETWORKREJECTINFORMATION 30
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_SIMDATAINFO 32
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_TEMPERATUREINFO 33
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_NETWORKINFO 29
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_AIRPLANEMODE 19
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_NADSTATE 28
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_JAMMINGSTATE 24
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_DORMANTMODE 23
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_MOBILECOUNTRYCODE 25
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_MOBILENETWORKCODE 26
} } }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::ResultType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 8))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ResultType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::ResultType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 8))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ResultType");
                        return true;
                    }
                    e = (asi::connectivity::al::ResultType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::InquiryMode  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "InquiryMode");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::InquiryMode & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "InquiryMode");
                        return true;
                    }
                    e = (asi::connectivity::al::InquiryMode) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::BluetoothService  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 1:
                    case 2:
                    case 4:
                    case 8:
                    case 16:
                    case 32:
                    case 64:
                    case 128:
                    case 256:
                    case 512:
                    case 1024:
                    case 2048:
                    case 4096:
                    case 8192:
                    case 16384:
                    case 1048576:
                    case 2097152:
                    case 4194304:
                    case 8388608:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BluetoothService");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::BluetoothService & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 1:
                        case 2:
                        case 4:
                        case 8:
                        case 16:
                        case 32:
                        case 64:
                        case 128:
                        case 256:
                        case 512:
                        case 1024:
                        case 2048:
                        case 4096:
                        case 8192:
                        case 16384:
                        case 1048576:
                        case 2097152:
                        case 4194304:
                        case 8388608:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BluetoothService");
                            return true;
                    }
                    e = (asi::connectivity::al::BluetoothService) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::BluetoothServiceA2dpDetails  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 1:
                    case 2:
                    case 4:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BluetoothServiceA2dpDetails");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::BluetoothServiceA2dpDetails & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 1:
                        case 2:
                        case 4:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BluetoothServiceA2dpDetails");
                            return true;
                    }
                    e = (asi::connectivity::al::BluetoothServiceA2dpDetails) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::BluetoothServiceStatus  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BluetoothServiceStatus");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::BluetoothServiceStatus & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BluetoothServiceStatus");
                        return true;
                    }
                    e = (asi::connectivity::al::BluetoothServiceStatus) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::PairingState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 9))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "PairingState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::PairingState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 9))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "PairingState");
                        return true;
                    }
                    e = (asi::connectivity::al::PairingState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SecureSimplePairingMethod  e)
            {
                int32_t value = int32_t(e);

                if ((value < 1) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SecureSimplePairingMethod");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SecureSimplePairingMethod & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 1) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SecureSimplePairingMethod");
                        return true;
                    }
                    e = (asi::connectivity::al::SecureSimplePairingMethod) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SecureSimplePairingCapability  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SecureSimplePairingCapability");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SecureSimplePairingCapability & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SecureSimplePairingCapability");
                        return true;
                    }
                    e = (asi::connectivity::al::SecureSimplePairingCapability) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SupportedPairingMethod  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SupportedPairingMethod");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SupportedPairingMethod & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SupportedPairingMethod");
                        return true;
                    }
                    e = (asi::connectivity::al::SupportedPairingMethod) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::BtSniffMode  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BtSniffMode");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::BtSniffMode & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BtSniffMode");
                        return true;
                    }
                    e = (asi::connectivity::al::BtSniffMode) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::LinkkeyType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "LinkkeyType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::LinkkeyType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "LinkkeyType");
                        return true;
                    }
                    e = (asi::connectivity::al::LinkkeyType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::MobileDeviceInfoType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MobileDeviceInfoType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::MobileDeviceInfoType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MobileDeviceInfoType");
                        return true;
                    }
                    e = (asi::connectivity::al::MobileDeviceInfoType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::HandsfreeMode  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "HandsfreeMode");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::HandsfreeMode & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "HandsfreeMode");
                        return true;
                    }
                    e = (asi::connectivity::al::HandsfreeMode) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::NetworkState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NetworkState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::NetworkState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NetworkState");
                        return true;
                    }
                    e = (asi::connectivity::al::NetworkState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::RoamingState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RoamingState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::RoamingState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RoamingState");
                        return true;
                    }
                    e = (asi::connectivity::al::RoamingState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::CallState  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 6))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CallState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::CallState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 6))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CallState");
                        return true;
                    }
                    e = (asi::connectivity::al::CallState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::CallDirection  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CallDirection");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::CallDirection & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CallDirection");
                        return true;
                    }
                    e = (asi::connectivity::al::CallDirection) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SupportedHfpFeatures  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 1:
                    case 2:
                    case 4:
                    case 8:
                    case 16:
                    case 32:
                    case 64:
                    case 128:
                    case 256:
                    case 65535:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SupportedHfpFeatures");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SupportedHfpFeatures & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 1:
                        case 2:
                        case 4:
                        case 8:
                        case 16:
                        case 32:
                        case 64:
                        case 128:
                        case 256:
                        case 65535:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SupportedHfpFeatures");
                            return true;
                    }
                    e = (asi::connectivity::al::SupportedHfpFeatures) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::HfpVersion  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 6))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "HfpVersion");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::HfpVersion & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 6))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "HfpVersion");
                        return true;
                    }
                    e = (asi::connectivity::al::HfpVersion) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::HfpAudioPolicy  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "HfpAudioPolicy");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::HfpAudioPolicy & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "HfpAudioPolicy");
                        return true;
                    }
                    e = (asi::connectivity::al::HfpAudioPolicy) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::VoiceRecognitionFlavor  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "VoiceRecognitionFlavor");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::VoiceRecognitionFlavor & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "VoiceRecognitionFlavor");
                        return true;
                    }
                    e = (asi::connectivity::al::VoiceRecognitionFlavor) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::NetworkType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 8))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NetworkType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::NetworkType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 8))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NetworkType");
                        return true;
                    }
                    e = (asi::connectivity::al::NetworkType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::NetworkDomain  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NetworkDomain");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::NetworkDomain & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NetworkDomain");
                        return true;
                    }
                    e = (asi::connectivity::al::NetworkDomain) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::DeviceType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DeviceType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::DeviceType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DeviceType");
                        return true;
                    }
                    e = (asi::connectivity::al::DeviceType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SimType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SimType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimType");
                        return true;
                    }
                    e = (asi::connectivity::al::SimType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::UssdResultCode  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 5))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "UssdResultCode");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::UssdResultCode & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 5))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "UssdResultCode");
                        return true;
                    }
                    e = (asi::connectivity::al::UssdResultCode) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::HfpError  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 8))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "HfpError");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::HfpError & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 8))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "HfpError");
                        return true;
                    }
                    e = (asi::connectivity::al::HfpError) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::CallStackType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CallStackType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::CallStackType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CallStackType");
                        return true;
                    }
                    e = (asi::connectivity::al::CallStackType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::CallStackDownloadStatus  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 4))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CallStackDownloadStatus");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::CallStackDownloadStatus & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 4))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CallStackDownloadStatus");
                        return true;
                    }
                    e = (asi::connectivity::al::CallStackDownloadStatus) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::NadState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 8))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::NadState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 8))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadState");
                        return true;
                    }
                    e = (asi::connectivity::al::NadState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SimSource  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimSource");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SimSource & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimSource");
                        return true;
                    }
                    e = (asi::connectivity::al::SimSource) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::ActiveSimSource  e)
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
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ActiveSimSource");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::ActiveSimSource & e)
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
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ActiveSimSource");
                            return true;
                    }
                    e = (asi::connectivity::al::ActiveSimSource) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SimPinType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimPinType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SimPinType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimPinType");
                        return true;
                    }
                    e = (asi::connectivity::al::SimPinType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::NadError  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 21))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadError");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::NadError & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 21))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadError");
                        return true;
                    }
                    e = (asi::connectivity::al::NadError) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::NetworkAvailibility  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NetworkAvailibility");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::NetworkAvailibility & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NetworkAvailibility");
                        return true;
                    }
                    e = (asi::connectivity::al::NetworkAvailibility) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::ClirState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ClirState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::ClirState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ClirState");
                        return true;
                    }
                    e = (asi::connectivity::al::ClirState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::ClirNwState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 4))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ClirNwState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::ClirNwState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 4))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ClirNwState");
                        return true;
                    }
                    e = (asi::connectivity::al::ClirNwState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::CfcReason  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 5))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CfcReason");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::CfcReason & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 5))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CfcReason");
                        return true;
                    }
                    e = (asi::connectivity::al::CfcReason) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::ServiceClass  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 1:
                    case 2:
                    case 4:
                    case 8:
                    case 16:
                    case 32:
                    case 64:
                    case 128:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceClass");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::ServiceClass & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 1:
                        case 2:
                        case 4:
                        case 8:
                        case 16:
                        case 32:
                        case 64:
                        case 128:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceClass");
                            return true;
                    }
                    e = (asi::connectivity::al::ServiceClass) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::NadTempThresholdLevel  e)
            {
                int32_t value = int32_t(e);

                if ((value < -2) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadTempThresholdLevel");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::NadTempThresholdLevel & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -2) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadTempThresholdLevel");
                        return true;
                    }
                    e = (asi::connectivity::al::NadTempThresholdLevel) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::NadEvent  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 4))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadEvent");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::NadEvent & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 4))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadEvent");
                        return true;
                    }
                    e = (asi::connectivity::al::NadEvent) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::AntennaState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 4))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AntennaState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::AntennaState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 4))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AntennaState");
                        return true;
                    }
                    e = (asi::connectivity::al::AntennaState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::RegState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 6))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RegState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::RegState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 6))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RegState");
                        return true;
                    }
                    e = (asi::connectivity::al::RegState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::ServiceDomain  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceDomain");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::ServiceDomain & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceDomain");
                        return true;
                    }
                    e = (asi::connectivity::al::ServiceDomain) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::DataConnectionState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 6))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DataConnectionState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::DataConnectionState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 6))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DataConnectionState");
                        return true;
                    }
                    e = (asi::connectivity::al::DataConnectionState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::AirplaneMode  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AirplaneMode");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::AirplaneMode & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AirplaneMode");
                        return true;
                    }
                    e = (asi::connectivity::al::AirplaneMode) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::DormantMode  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DormantMode");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::DormantMode & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "DormantMode");
                        return true;
                    }
                    e = (asi::connectivity::al::DormantMode) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::EraGlonassStatus  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EraGlonassStatus");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::EraGlonassStatus & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "EraGlonassStatus");
                        return true;
                    }
                    e = (asi::connectivity::al::EraGlonassStatus) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SIMError  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case -1:
                    case 0:
                    case 1:
                    case 2:
                    case 10:
                    case 11:
                    case 12:
                    case 98:
                    case 99:
                    case 100:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SIMError");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SIMError & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    switch (value)
                    {
                        case -1:
                        case 0:
                        case 1:
                        case 2:
                        case 10:
                        case 11:
                        case 12:
                        case 98:
                        case 99:
                        case 100:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SIMError");
                            return true;
                    }
                    e = (asi::connectivity::al::SIMError) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SimState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 4))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SimState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 4))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimState");
                        return true;
                    }
                    e = (asi::connectivity::al::SimState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SimProfileId  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimProfileId");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SimProfileId & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimProfileId");
                        return true;
                    }
                    e = (asi::connectivity::al::SimProfileId) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::AntennasScenario  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 6))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AntennasScenario");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::AntennasScenario & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 6))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AntennasScenario");
                        return true;
                    }
                    e = (asi::connectivity::al::AntennasScenario) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::BatteryState  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BatteryState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::BatteryState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BatteryState");
                        return true;
                    }
                    e = (asi::connectivity::al::BatteryState) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::configParam  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 12))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "configParam");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::configParam & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 12))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "configParam");
                        return true;
                    }
                    e = (asi::connectivity::al::configParam) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::VolteSupport  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "VolteSupport");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::VolteSupport & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "VolteSupport");
                        return true;
                    }
                    e = (asi::connectivity::al::VolteSupport) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::CSRatsSupport  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CSRatsSupport");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::CSRatsSupport & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "CSRatsSupport");
                        return true;
                    }
                    e = (asi::connectivity::al::CSRatsSupport) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::BipRouteResult  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BipRouteResult");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::BipRouteResult & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "BipRouteResult");
                        return true;
                    }
                    e = (asi::connectivity::al::BipRouteResult) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SmsType  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SmsType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SmsType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SmsType");
                        return true;
                    }
                    e = (asi::connectivity::al::SmsType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::SmsCbmReportType  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SmsCbmReportType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::SmsCbmReportType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SmsCbmReportType");
                        return true;
                    }
                    e = (asi::connectivity::al::SmsCbmReportType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::JammingStatus  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "JammingStatus");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::JammingStatus & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "JammingStatus");
                        return true;
                    }
                    e = (asi::connectivity::al::JammingStatus) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::AudioState  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 4))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AudioState");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::AudioState & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 4))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AudioState");
                        return true;
                    }
                    e = (asi::connectivity::al::AudioState) value;
                }
                return error;
            }
} } // namespace util::serializer

namespace asi
{
namespace connectivity
{
namespace al
{
}// namespace asi
}// namespace connectivity
}// namespace al

#endif  // ASI_CONNECTIVITY_AL_DEFINITIONS_HXX
