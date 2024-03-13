/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_POSGNSSDR01STRUCT_HXX
#define ASI_SID_LHWAPP_POSGNSSDR01STRUCT_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace sid
{
namespace lhwapp
{

    /**
    \brief struct lhwapp::POSGNSSDR01Struct.
    */
    struct PROXY_EXPORT POSGNSSDR01Struct
    {
        uint64_t POS_GNSS_DR_Breite_Ortung_Raw; // optional=False
        uint64_t POS_GNSS_DR_Breite_Ortung_SignalState; // optional=False
        uint16_t POS_GNSS_DR_Guete_E_GrH_Ausr_Raw; // optional=False
        uint64_t POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState; // optional=False
        uint16_t POS_GNSS_DR_Guete_E_GrHalbachse_Raw; // optional=False
        uint64_t POS_GNSS_DR_Guete_E_GrHalbachse_SignalState; // optional=False
        uint16_t POS_GNSS_DR_Guete_E_KlHalbachse_Raw; // optional=False
        uint64_t POS_GNSS_DR_Guete_E_KlHalbachse_SignalState; // optional=False
        uint64_t POS_GNSS_DR_Laenge_Ortung_Raw; // optional=False
        uint64_t POS_GNSS_DR_Laenge_Ortung_SignalState; // optional=False
        uint16_t POS_GNSS_DR_Ausrichtung_Geschw_Raw; // optional=False
        uint64_t POS_GNSS_DR_Ausrichtung_Geschw_SignalState; // optional=False
        uint16_t POS_GNSS_DR_Guete_Ausricht_Gesch_Raw; // optional=False
        uint64_t POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState; // optional=False
        uint64_t PduState; // optional=False
        private:
            POSGNSSDR01Struct()
            :
            POS_GNSS_DR_Breite_Ortung_Raw(),
            POS_GNSS_DR_Breite_Ortung_SignalState(),
            POS_GNSS_DR_Guete_E_GrH_Ausr_Raw(),
            POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState(),
            POS_GNSS_DR_Guete_E_GrHalbachse_Raw(),
            POS_GNSS_DR_Guete_E_GrHalbachse_SignalState(),
            POS_GNSS_DR_Guete_E_KlHalbachse_Raw(),
            POS_GNSS_DR_Guete_E_KlHalbachse_SignalState(),
            POS_GNSS_DR_Laenge_Ortung_Raw(),
            POS_GNSS_DR_Laenge_Ortung_SignalState(),
            POS_GNSS_DR_Ausrichtung_Geschw_Raw(),
            POS_GNSS_DR_Ausrichtung_Geschw_SignalState(),
            POS_GNSS_DR_Guete_Ausricht_Gesch_Raw(),
            POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState(),
            PduState()
            { }
            friend class POSGNSSDR01StructFactory;
            friend class CIFactory<POSGNSSDR01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::POSGNSSDR01Struct> >;
            friend class ipl::vector<POSGNSSDR01Struct>;
            friend class ipl::allocator<POSGNSSDR01Struct>;
#endif
    };

    typedef CIPtrArray<POSGNSSDR01Struct> CIPOSGNSSDR01StructArray;

    /** \brief factory for lhwapp::POSGNSSDR01Struct. */
    class PROXY_EXPORT POSGNSSDR01StructFactory  : CIFactory<POSGNSSDR01Struct> {
    public:
        static inline CIPtr<POSGNSSDR01Struct> createPOSGNSSDR01Struct() {
            return CIFactory<POSGNSSDR01Struct>::createObject();
        }
        static inline void createPOSGNSSDR01Struct(CIPtr<POSGNSSDR01Struct> & s) {
            CIFactory<POSGNSSDR01Struct>::createObject(s);
        }
        static inline CIPtr<CIPOSGNSSDR01StructArray> createPOSGNSSDR01StructArray(size_t size) {
            return CIFactory<POSGNSSDR01Struct>::createArray(size);
        }
        static inline void createPOSGNSSDR01StructArray(CIPtr<CIPOSGNSSDR01StructArray>& a, size_t size) {
            CIFactory<POSGNSSDR01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_POSGNSSDR01STRUCT_HXX
