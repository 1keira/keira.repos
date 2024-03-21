/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERWLANANTENNA_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERWLANANTENNA_HXX

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
    \brief struct diagnostic::TransmissionPowerWlanAntenna.
    */
    struct PROXY_EXPORT TransmissionPowerWlanAntenna
    {
        uint8_t _2_4Ghz; // optional=False
        uint8_t _5Ghz; // optional=False
        private:
            TransmissionPowerWlanAntenna()
            :
            _2_4Ghz(),
            _5Ghz()
            { }
            friend class TransmissionPowerWlanAntennaFactory;
            friend class CIFactory<TransmissionPowerWlanAntenna>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::TransmissionPowerWlanAntenna> >;
            friend class ipl::vector<TransmissionPowerWlanAntenna>;
            friend class ipl::allocator<TransmissionPowerWlanAntenna>;
#endif
    };

    typedef CIPtrArray<TransmissionPowerWlanAntenna> CITransmissionPowerWlanAntennaArray;

    /** \brief factory for diagnostic::TransmissionPowerWlanAntenna. */
    class PROXY_EXPORT TransmissionPowerWlanAntennaFactory  : CIFactory<TransmissionPowerWlanAntenna> {
    public:
        static inline CIPtr<TransmissionPowerWlanAntenna> createTransmissionPowerWlanAntenna() {
            return CIFactory<TransmissionPowerWlanAntenna>::createObject();
        }
        static inline void createTransmissionPowerWlanAntenna(CIPtr<TransmissionPowerWlanAntenna> & s) {
            CIFactory<TransmissionPowerWlanAntenna>::createObject(s);
        }
        static inline CIPtr<CITransmissionPowerWlanAntennaArray> createTransmissionPowerWlanAntennaArray(size_t size) {
            return CIFactory<TransmissionPowerWlanAntenna>::createArray(size);
        }
        static inline void createTransmissionPowerWlanAntennaArray(CIPtr<CITransmissionPowerWlanAntennaArray>& a, size_t size) {
            CIFactory<TransmissionPowerWlanAntenna>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERWLANANTENNA_HXX
