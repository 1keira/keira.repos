/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWER_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWER_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/StructTransmissionPowerMobNetAntenna.hxx>
#include <asi/connectivity/diagnostic/StructTransmissionPowerWlanAntenna.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::TransmissionPower.
    */
    struct PROXY_EXPORT TransmissionPower
    {
        uint8_t btExtAntenna; // optional=False
        uint8_t btIntAntenna; // optional=False
        CIPtr< asi::connectivity::diagnostic::TransmissionPowerMobNetAntenna > mobNetAnt1; // optional=True
        CIPtr< asi::connectivity::diagnostic::TransmissionPowerMobNetAntenna > mobNetAnt2; // optional=True
        CIPtr< asi::connectivity::diagnostic::TransmissionPowerMobNetAntenna > mobNetAnt3; // optional=True
        CIPtr< asi::connectivity::diagnostic::TransmissionPowerMobNetAntenna > mobNetAnt4; // optional=True
        CIPtr< asi::connectivity::diagnostic::TransmissionPowerWlanAntenna > wlanAnt1; // optional=True
        CIPtr< asi::connectivity::diagnostic::TransmissionPowerWlanAntenna > wlanAnt2; // optional=True
        private:
            TransmissionPower()
            :
            btExtAntenna(),
            btIntAntenna(),
            mobNetAnt1(),
            mobNetAnt2(),
            mobNetAnt3(),
            mobNetAnt4(),
            wlanAnt1(),
            wlanAnt2()
            { }
            friend class TransmissionPowerFactory;
            friend class CIFactory<TransmissionPower>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::TransmissionPower> >;
            friend class ipl::vector<TransmissionPower>;
            friend class ipl::allocator<TransmissionPower>;
#endif
    };

    typedef CIPtrArray<TransmissionPower> CITransmissionPowerArray;

    /** \brief factory for diagnostic::TransmissionPower. */
    class PROXY_EXPORT TransmissionPowerFactory  : CIFactory<TransmissionPower> {
    public:
        static inline CIPtr<TransmissionPower> createTransmissionPower() {
            return CIFactory<TransmissionPower>::createObject();
        }
        static inline void createTransmissionPower(CIPtr<TransmissionPower> & s) {
            CIFactory<TransmissionPower>::createObject(s);
        }
        static inline CIPtr<CITransmissionPowerArray> createTransmissionPowerArray(size_t size) {
            return CIFactory<TransmissionPower>::createArray(size);
        }
        static inline void createTransmissionPowerArray(CIPtr<CITransmissionPowerArray>& a, size_t size) {
            CIFactory<TransmissionPower>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWER_HXX
