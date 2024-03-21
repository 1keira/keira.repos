/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_CODINGVALUES_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_CODINGVALUES_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
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
    \brief struct diagnostic::CodingValues.
    */
    struct PROXY_EXPORT CodingValues
    {
        asi::connectivity::diagnostic::AudioSourcesMute audioSrcMute; // optional=False
        asi::connectivity::diagnostic::BtLe1AntennaResistance btLe1AntResist; // optional=False
        asi::connectivity::diagnostic::CarBrand carBrand; // optional=False
        asi::connectivity::diagnostic::ExternalControlElement extCtrlElem; // optional=False
        bool isAirbagPwmOn; // optional=False
        bool isBackupBatteryOn; // optional=False
        bool isBapOn; // optional=False
        bool isBtLe1On; // optional=False
        bool isBtLe2On; // optional=False
        bool isBtWlanAnt1On; // optional=False
        bool isBtWlanAnt2On; // optional=False
        bool isBtWlanAnt3On; // optional=False
        bool isCv2xAnt1On; // optional=False
        bool isCv2xAnt2On; // optional=False
        bool isCv2xCompensorOn; // optional=False
        bool isEcallLoudspeakerOn; // optional=False
        bool isExtGpsAntOn; // optional=False
        bool isMicrophone1On; // optional=False
        bool isMicrophone2On; // optional=False
        bool isMicrophone3On; // optional=False
        bool isMicrophone4On; // optional=False
        bool isMobNetAnt1On; // optional=False
        bool isMobNetAnt2On; // optional=False
        bool isMobNetAnt3On; // optional=False
        bool isMobNetAnt4On; // optional=False
        bool isMobNetAnt5On; // optional=False
        bool isMuteWireOn; // optional=False
        bool isNadModulOn; // optional=False
        bool isSteerWheelPosOn; // optional=False
        bool isV2xModulOn; // optional=False
        bool isWidebandOn; // optional=False
        asi::connectivity::diagnostic::MicrophoneVariant microphoneVariant; // optional=False
        asi::connectivity::diagnostic::V2xBsmFilterMode v2xBsmFilterMode; // optional=False
        private:
            CodingValues()
            :
            audioSrcMute(),
            btLe1AntResist(),
            carBrand(),
            extCtrlElem(),
            isAirbagPwmOn(),
            isBackupBatteryOn(),
            isBapOn(),
            isBtLe1On(),
            isBtLe2On(),
            isBtWlanAnt1On(),
            isBtWlanAnt2On(),
            isBtWlanAnt3On(),
            isCv2xAnt1On(),
            isCv2xAnt2On(),
            isCv2xCompensorOn(),
            isEcallLoudspeakerOn(),
            isExtGpsAntOn(),
            isMicrophone1On(),
            isMicrophone2On(),
            isMicrophone3On(),
            isMicrophone4On(),
            isMobNetAnt1On(),
            isMobNetAnt2On(),
            isMobNetAnt3On(),
            isMobNetAnt4On(),
            isMobNetAnt5On(),
            isMuteWireOn(),
            isNadModulOn(),
            isSteerWheelPosOn(),
            isV2xModulOn(),
            isWidebandOn(),
            microphoneVariant(),
            v2xBsmFilterMode()
            { }
            friend class CodingValuesFactory;
            friend class CIFactory<CodingValues>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::CodingValues> >;
            friend class ipl::vector<CodingValues>;
            friend class ipl::allocator<CodingValues>;
#endif
    };

    typedef CIPtrArray<CodingValues> CICodingValuesArray;

    /** \brief factory for diagnostic::CodingValues. */
    class PROXY_EXPORT CodingValuesFactory  : CIFactory<CodingValues> {
    public:
        static inline CIPtr<CodingValues> createCodingValues() {
            return CIFactory<CodingValues>::createObject();
        }
        static inline void createCodingValues(CIPtr<CodingValues> & s) {
            CIFactory<CodingValues>::createObject(s);
        }
        static inline CIPtr<CICodingValuesArray> createCodingValuesArray(size_t size) {
            return CIFactory<CodingValues>::createArray(size);
        }
        static inline void createCodingValuesArray(CIPtr<CICodingValuesArray>& a, size_t size) {
            CIFactory<CodingValues>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_CODINGVALUES_HXX
