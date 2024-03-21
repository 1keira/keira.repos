/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERMOBNETANTENNA_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERMOBNETANTENNA_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::TransmissionPowerMobNetAntenna.
    */
    struct PROXY_EXPORT TransmissionPowerMobNetAntenna
    {
        uint8_t _2g; // optional=False
        uint8_t _3g; // optional=False
        uint8_t _4g; // optional=False
        uint8_t _5g; // optional=False
        private:
            TransmissionPowerMobNetAntenna()
            :
            _2g(),
            _3g(),
            _4g(),
            _5g()
            { }
            friend class TransmissionPowerMobNetAntennaFactory;
            friend class CIFactory<TransmissionPowerMobNetAntenna>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::TransmissionPowerMobNetAntenna> >;
            friend class ipl::vector<TransmissionPowerMobNetAntenna>;
            friend class ipl::allocator<TransmissionPowerMobNetAntenna>;
#endif
    };

    typedef CIPtrArray<TransmissionPowerMobNetAntenna> CITransmissionPowerMobNetAntennaArray;

    /** \brief factory for diagnostic::TransmissionPowerMobNetAntenna. */
    class PROXY_EXPORT TransmissionPowerMobNetAntennaFactory  : CIFactory<TransmissionPowerMobNetAntenna> {
    public:
        static inline CIPtr<TransmissionPowerMobNetAntenna> createTransmissionPowerMobNetAntenna() {
            return CIFactory<TransmissionPowerMobNetAntenna>::createObject();
        }
        static inline void createTransmissionPowerMobNetAntenna(CIPtr<TransmissionPowerMobNetAntenna> & s) {
            CIFactory<TransmissionPowerMobNetAntenna>::createObject(s);
        }
        static inline CIPtr<CITransmissionPowerMobNetAntennaArray> createTransmissionPowerMobNetAntennaArray(size_t size) {
            return CIFactory<TransmissionPowerMobNetAntenna>::createArray(size);
        }
        static inline void createTransmissionPowerMobNetAntennaArray(CIPtr<CITransmissionPowerMobNetAntennaArray>& a, size_t size) {
            CIFactory<TransmissionPowerMobNetAntenna>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERMOBNETANTENNA_HXX
