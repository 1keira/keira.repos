/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_CODINGVALUES_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_CODINGVALUES_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
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
struct CodingValues;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::CodingValues& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::CodingValues &val);
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
    \brief struct diagnostic::CodingValues.
    */
    struct PROXY_EXPORT CodingValues
    {
        public:
            CodingValues()
            : m_audioSrcMute()
            , m_btLe1AntResist()
            , m_carBrand()
            , m_extCtrlElem()
            , m_isAirbagPwmOn()
            , m_isBackupBatteryOn()
            , m_isBapOn()
            , m_isBtLe1On()
            , m_isBtLe2On()
            , m_isBtWlanAnt1On()
            , m_isBtWlanAnt2On()
            , m_isBtWlanAnt3On()
            , m_isCv2xAnt1On()
            , m_isCv2xAnt2On()
            , m_isCv2xCompensorOn()
            , m_isEcallLoudspeakerOn()
            , m_isExtGpsAntOn()
            , m_isMicrophone1On()
            , m_isMicrophone2On()
            , m_isMicrophone3On()
            , m_isMicrophone4On()
            , m_isMobNetAnt1On()
            , m_isMobNetAnt2On()
            , m_isMobNetAnt3On()
            , m_isMobNetAnt4On()
            , m_isMobNetAnt5On()
            , m_isMuteWireOn()
            , m_isNadModulOn()
            , m_isSteerWheelPosOn()
            , m_isV2xModulOn()
            , m_isWidebandOn()
            , m_microphoneVariant()
            , m_v2xBsmFilterMode()
            { }

            CodingValues (const CodingValues& other)
            : m_audioSrcMute()
            , m_btLe1AntResist()
            , m_carBrand()
            , m_extCtrlElem()
            , m_isAirbagPwmOn()
            , m_isBackupBatteryOn()
            , m_isBapOn()
            , m_isBtLe1On()
            , m_isBtLe2On()
            , m_isBtWlanAnt1On()
            , m_isBtWlanAnt2On()
            , m_isBtWlanAnt3On()
            , m_isCv2xAnt1On()
            , m_isCv2xAnt2On()
            , m_isCv2xCompensorOn()
            , m_isEcallLoudspeakerOn()
            , m_isExtGpsAntOn()
            , m_isMicrophone1On()
            , m_isMicrophone2On()
            , m_isMicrophone3On()
            , m_isMicrophone4On()
            , m_isMobNetAnt1On()
            , m_isMobNetAnt2On()
            , m_isMobNetAnt3On()
            , m_isMobNetAnt4On()
            , m_isMobNetAnt5On()
            , m_isMuteWireOn()
            , m_isNadModulOn()
            , m_isSteerWheelPosOn()
            , m_isV2xModulOn()
            , m_isWidebandOn()
            , m_microphoneVariant()
            , m_v2xBsmFilterMode()
            {
              *this = other;
            }

            ~CodingValues () {
            }
            bool operator==(const CodingValues& rhs) const {
                bool equal = true;
                if (m_audioSrcMute != rhs.m_audioSrcMute)
                    equal = false;
                if (m_btLe1AntResist != rhs.m_btLe1AntResist)
                    equal = false;
                if (m_carBrand != rhs.m_carBrand)
                    equal = false;
                if (m_extCtrlElem != rhs.m_extCtrlElem)
                    equal = false;
                if (m_isAirbagPwmOn != rhs.m_isAirbagPwmOn)
                    equal = false;
                if (m_isBackupBatteryOn != rhs.m_isBackupBatteryOn)
                    equal = false;
                if (m_isBapOn != rhs.m_isBapOn)
                    equal = false;
                if (m_isBtLe1On != rhs.m_isBtLe1On)
                    equal = false;
                if (m_isBtLe2On != rhs.m_isBtLe2On)
                    equal = false;
                if (m_isBtWlanAnt1On != rhs.m_isBtWlanAnt1On)
                    equal = false;
                if (m_isBtWlanAnt2On != rhs.m_isBtWlanAnt2On)
                    equal = false;
                if (m_isBtWlanAnt3On != rhs.m_isBtWlanAnt3On)
                    equal = false;
                if (m_isCv2xAnt1On != rhs.m_isCv2xAnt1On)
                    equal = false;
                if (m_isCv2xAnt2On != rhs.m_isCv2xAnt2On)
                    equal = false;
                if (m_isCv2xCompensorOn != rhs.m_isCv2xCompensorOn)
                    equal = false;
                if (m_isEcallLoudspeakerOn != rhs.m_isEcallLoudspeakerOn)
                    equal = false;
                if (m_isExtGpsAntOn != rhs.m_isExtGpsAntOn)
                    equal = false;
                if (m_isMicrophone1On != rhs.m_isMicrophone1On)
                    equal = false;
                if (m_isMicrophone2On != rhs.m_isMicrophone2On)
                    equal = false;
                if (m_isMicrophone3On != rhs.m_isMicrophone3On)
                    equal = false;
                if (m_isMicrophone4On != rhs.m_isMicrophone4On)
                    equal = false;
                if (m_isMobNetAnt1On != rhs.m_isMobNetAnt1On)
                    equal = false;
                if (m_isMobNetAnt2On != rhs.m_isMobNetAnt2On)
                    equal = false;
                if (m_isMobNetAnt3On != rhs.m_isMobNetAnt3On)
                    equal = false;
                if (m_isMobNetAnt4On != rhs.m_isMobNetAnt4On)
                    equal = false;
                if (m_isMobNetAnt5On != rhs.m_isMobNetAnt5On)
                    equal = false;
                if (m_isMuteWireOn != rhs.m_isMuteWireOn)
                    equal = false;
                if (m_isNadModulOn != rhs.m_isNadModulOn)
                    equal = false;
                if (m_isSteerWheelPosOn != rhs.m_isSteerWheelPosOn)
                    equal = false;
                if (m_isV2xModulOn != rhs.m_isV2xModulOn)
                    equal = false;
                if (m_isWidebandOn != rhs.m_isWidebandOn)
                    equal = false;
                if (m_microphoneVariant != rhs.m_microphoneVariant)
                    equal = false;
                if (m_v2xBsmFilterMode != rhs.m_v2xBsmFilterMode)
                    equal = false;
                return equal;
            }
            bool operator!=(const CodingValues& rhs) const {
                return !operator==(rhs);
            }

            CodingValues& operator = (const CodingValues& src) {
                if (this == &src) return *this;
                m_audioSrcMute = src.m_audioSrcMute;
                m_btLe1AntResist = src.m_btLe1AntResist;
                m_carBrand = src.m_carBrand;
                m_extCtrlElem = src.m_extCtrlElem;
                m_isAirbagPwmOn = src.m_isAirbagPwmOn;
                m_isBackupBatteryOn = src.m_isBackupBatteryOn;
                m_isBapOn = src.m_isBapOn;
                m_isBtLe1On = src.m_isBtLe1On;
                m_isBtLe2On = src.m_isBtLe2On;
                m_isBtWlanAnt1On = src.m_isBtWlanAnt1On;
                m_isBtWlanAnt2On = src.m_isBtWlanAnt2On;
                m_isBtWlanAnt3On = src.m_isBtWlanAnt3On;
                m_isCv2xAnt1On = src.m_isCv2xAnt1On;
                m_isCv2xAnt2On = src.m_isCv2xAnt2On;
                m_isCv2xCompensorOn = src.m_isCv2xCompensorOn;
                m_isEcallLoudspeakerOn = src.m_isEcallLoudspeakerOn;
                m_isExtGpsAntOn = src.m_isExtGpsAntOn;
                m_isMicrophone1On = src.m_isMicrophone1On;
                m_isMicrophone2On = src.m_isMicrophone2On;
                m_isMicrophone3On = src.m_isMicrophone3On;
                m_isMicrophone4On = src.m_isMicrophone4On;
                m_isMobNetAnt1On = src.m_isMobNetAnt1On;
                m_isMobNetAnt2On = src.m_isMobNetAnt2On;
                m_isMobNetAnt3On = src.m_isMobNetAnt3On;
                m_isMobNetAnt4On = src.m_isMobNetAnt4On;
                m_isMobNetAnt5On = src.m_isMobNetAnt5On;
                m_isMuteWireOn = src.m_isMuteWireOn;
                m_isNadModulOn = src.m_isNadModulOn;
                m_isSteerWheelPosOn = src.m_isSteerWheelPosOn;
                m_isV2xModulOn = src.m_isV2xModulOn;
                m_isWidebandOn = src.m_isWidebandOn;
                m_microphoneVariant = src.m_microphoneVariant;
                m_v2xBsmFilterMode = src.m_v2xBsmFilterMode;
                return *this;
            }

                void setaudioSrcMute(const asi::connectivity::diagnostic::cstyle::AudioSourcesMute _value) {
                    m_audioSrcMute = _value;
                }
                asi::connectivity::diagnostic::cstyle::AudioSourcesMute getaudioSrcMute() const {
                    return m_audioSrcMute;
                }
                void setbtLe1AntResist(const asi::connectivity::diagnostic::cstyle::BtLe1AntennaResistance _value) {
                    m_btLe1AntResist = _value;
                }
                asi::connectivity::diagnostic::cstyle::BtLe1AntennaResistance getbtLe1AntResist() const {
                    return m_btLe1AntResist;
                }
                void setcarBrand(const asi::connectivity::diagnostic::cstyle::CarBrand _value) {
                    m_carBrand = _value;
                }
                asi::connectivity::diagnostic::cstyle::CarBrand getcarBrand() const {
                    return m_carBrand;
                }
                void setextCtrlElem(const asi::connectivity::diagnostic::cstyle::ExternalControlElement _value) {
                    m_extCtrlElem = _value;
                }
                asi::connectivity::diagnostic::cstyle::ExternalControlElement getextCtrlElem() const {
                    return m_extCtrlElem;
                }
                void setisAirbagPwmOn(const bool _value) {
                    m_isAirbagPwmOn = _value;
                }
                bool getisAirbagPwmOn() const {
                    return m_isAirbagPwmOn;
                }
                void setisBackupBatteryOn(const bool _value) {
                    m_isBackupBatteryOn = _value;
                }
                bool getisBackupBatteryOn() const {
                    return m_isBackupBatteryOn;
                }
                void setisBapOn(const bool _value) {
                    m_isBapOn = _value;
                }
                bool getisBapOn() const {
                    return m_isBapOn;
                }
                void setisBtLe1On(const bool _value) {
                    m_isBtLe1On = _value;
                }
                bool getisBtLe1On() const {
                    return m_isBtLe1On;
                }
                void setisBtLe2On(const bool _value) {
                    m_isBtLe2On = _value;
                }
                bool getisBtLe2On() const {
                    return m_isBtLe2On;
                }
                void setisBtWlanAnt1On(const bool _value) {
                    m_isBtWlanAnt1On = _value;
                }
                bool getisBtWlanAnt1On() const {
                    return m_isBtWlanAnt1On;
                }
                void setisBtWlanAnt2On(const bool _value) {
                    m_isBtWlanAnt2On = _value;
                }
                bool getisBtWlanAnt2On() const {
                    return m_isBtWlanAnt2On;
                }
                void setisBtWlanAnt3On(const bool _value) {
                    m_isBtWlanAnt3On = _value;
                }
                bool getisBtWlanAnt3On() const {
                    return m_isBtWlanAnt3On;
                }
                void setisCv2xAnt1On(const bool _value) {
                    m_isCv2xAnt1On = _value;
                }
                bool getisCv2xAnt1On() const {
                    return m_isCv2xAnt1On;
                }
                void setisCv2xAnt2On(const bool _value) {
                    m_isCv2xAnt2On = _value;
                }
                bool getisCv2xAnt2On() const {
                    return m_isCv2xAnt2On;
                }
                void setisCv2xCompensorOn(const bool _value) {
                    m_isCv2xCompensorOn = _value;
                }
                bool getisCv2xCompensorOn() const {
                    return m_isCv2xCompensorOn;
                }
                void setisEcallLoudspeakerOn(const bool _value) {
                    m_isEcallLoudspeakerOn = _value;
                }
                bool getisEcallLoudspeakerOn() const {
                    return m_isEcallLoudspeakerOn;
                }
                void setisExtGpsAntOn(const bool _value) {
                    m_isExtGpsAntOn = _value;
                }
                bool getisExtGpsAntOn() const {
                    return m_isExtGpsAntOn;
                }
                void setisMicrophone1On(const bool _value) {
                    m_isMicrophone1On = _value;
                }
                bool getisMicrophone1On() const {
                    return m_isMicrophone1On;
                }
                void setisMicrophone2On(const bool _value) {
                    m_isMicrophone2On = _value;
                }
                bool getisMicrophone2On() const {
                    return m_isMicrophone2On;
                }
                void setisMicrophone3On(const bool _value) {
                    m_isMicrophone3On = _value;
                }
                bool getisMicrophone3On() const {
                    return m_isMicrophone3On;
                }
                void setisMicrophone4On(const bool _value) {
                    m_isMicrophone4On = _value;
                }
                bool getisMicrophone4On() const {
                    return m_isMicrophone4On;
                }
                void setisMobNetAnt1On(const bool _value) {
                    m_isMobNetAnt1On = _value;
                }
                bool getisMobNetAnt1On() const {
                    return m_isMobNetAnt1On;
                }
                void setisMobNetAnt2On(const bool _value) {
                    m_isMobNetAnt2On = _value;
                }
                bool getisMobNetAnt2On() const {
                    return m_isMobNetAnt2On;
                }
                void setisMobNetAnt3On(const bool _value) {
                    m_isMobNetAnt3On = _value;
                }
                bool getisMobNetAnt3On() const {
                    return m_isMobNetAnt3On;
                }
                void setisMobNetAnt4On(const bool _value) {
                    m_isMobNetAnt4On = _value;
                }
                bool getisMobNetAnt4On() const {
                    return m_isMobNetAnt4On;
                }
                void setisMobNetAnt5On(const bool _value) {
                    m_isMobNetAnt5On = _value;
                }
                bool getisMobNetAnt5On() const {
                    return m_isMobNetAnt5On;
                }
                void setisMuteWireOn(const bool _value) {
                    m_isMuteWireOn = _value;
                }
                bool getisMuteWireOn() const {
                    return m_isMuteWireOn;
                }
                void setisNadModulOn(const bool _value) {
                    m_isNadModulOn = _value;
                }
                bool getisNadModulOn() const {
                    return m_isNadModulOn;
                }
                void setisSteerWheelPosOn(const bool _value) {
                    m_isSteerWheelPosOn = _value;
                }
                bool getisSteerWheelPosOn() const {
                    return m_isSteerWheelPosOn;
                }
                void setisV2xModulOn(const bool _value) {
                    m_isV2xModulOn = _value;
                }
                bool getisV2xModulOn() const {
                    return m_isV2xModulOn;
                }
                void setisWidebandOn(const bool _value) {
                    m_isWidebandOn = _value;
                }
                bool getisWidebandOn() const {
                    return m_isWidebandOn;
                }
                void setmicrophoneVariant(const asi::connectivity::diagnostic::cstyle::MicrophoneVariant _value) {
                    m_microphoneVariant = _value;
                }
                asi::connectivity::diagnostic::cstyle::MicrophoneVariant getmicrophoneVariant() const {
                    return m_microphoneVariant;
                }
                void setv2xBsmFilterMode(const asi::connectivity::diagnostic::cstyle::V2xBsmFilterMode _value) {
                    m_v2xBsmFilterMode = _value;
                }
                asi::connectivity::diagnostic::cstyle::V2xBsmFilterMode getv2xBsmFilterMode() const {
                    return m_v2xBsmFilterMode;
                }


        asi::connectivity::diagnostic::cstyle::AudioSourcesMute m_audioSrcMute;
        asi::connectivity::diagnostic::cstyle::BtLe1AntennaResistance m_btLe1AntResist;
        asi::connectivity::diagnostic::cstyle::CarBrand m_carBrand;
        asi::connectivity::diagnostic::cstyle::ExternalControlElement m_extCtrlElem;
        bool m_isAirbagPwmOn;
        bool m_isBackupBatteryOn;
        bool m_isBapOn;
        bool m_isBtLe1On;
        bool m_isBtLe2On;
        bool m_isBtWlanAnt1On;
        bool m_isBtWlanAnt2On;
        bool m_isBtWlanAnt3On;
        bool m_isCv2xAnt1On;
        bool m_isCv2xAnt2On;
        bool m_isCv2xCompensorOn;
        bool m_isEcallLoudspeakerOn;
        bool m_isExtGpsAntOn;
        bool m_isMicrophone1On;
        bool m_isMicrophone2On;
        bool m_isMicrophone3On;
        bool m_isMicrophone4On;
        bool m_isMobNetAnt1On;
        bool m_isMobNetAnt2On;
        bool m_isMobNetAnt3On;
        bool m_isMobNetAnt4On;
        bool m_isMobNetAnt5On;
        bool m_isMuteWireOn;
        bool m_isNadModulOn;
        bool m_isSteerWheelPosOn;
        bool m_isV2xModulOn;
        bool m_isWidebandOn;
        asi::connectivity::diagnostic::cstyle::MicrophoneVariant m_microphoneVariant;
        asi::connectivity::diagnostic::cstyle::V2xBsmFilterMode m_v2xBsmFilterMode;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::CodingValues& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::CodingValues &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_CODINGVALUES_CSTYLE_HXX
