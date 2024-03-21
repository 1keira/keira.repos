/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_PSD06STRUCT_HXX
#define ASI_SID_LHWAPP_PSD06STRUCT_HXX

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
    \brief struct lhwapp::PSD06Struct.
    */
    struct PROXY_EXPORT PSD06Struct
    {
        uint8_t PSD_06_Mux_Raw; // optional=False
        uint8_t PSD_Attribut_5_ID_Raw; // optional=False
        uint64_t PSD_Attribut_5_ID_SignalState; // optional=False
        uint8_t PSD_Attribut_3_Wert_Raw; // optional=False
        uint8_t PSD_Attribut_5_Wert_Raw; // optional=False
        uint8_t PSD_Attribut_4_ID_Raw; // optional=False
        uint64_t PSD_Attribut_4_ID_SignalState; // optional=False
        uint8_t PSD_Attribut_4_Wert_Raw; // optional=False
        uint8_t PSD_Attribut_Segment_ID_Raw; // optional=False
        uint64_t PSD_Attribut_Segment_ID_SignalState; // optional=False
        uint8_t PSD_Attribut_3_ID_Raw; // optional=False
        uint64_t PSD_Attribut_3_ID_SignalState; // optional=False
        uint64_t PduState; // optional=False
        private:
            PSD06Struct()
            :
            PSD_06_Mux_Raw(),
            PSD_Attribut_5_ID_Raw(),
            PSD_Attribut_5_ID_SignalState(),
            PSD_Attribut_3_Wert_Raw(),
            PSD_Attribut_5_Wert_Raw(),
            PSD_Attribut_4_ID_Raw(),
            PSD_Attribut_4_ID_SignalState(),
            PSD_Attribut_4_Wert_Raw(),
            PSD_Attribut_Segment_ID_Raw(),
            PSD_Attribut_Segment_ID_SignalState(),
            PSD_Attribut_3_ID_Raw(),
            PSD_Attribut_3_ID_SignalState(),
            PduState()
            { }
            friend class PSD06StructFactory;
            friend class CIFactory<PSD06Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::PSD06Struct> >;
            friend class ipl::vector<PSD06Struct>;
            friend class ipl::allocator<PSD06Struct>;
#endif
    };

    typedef CIPtrArray<PSD06Struct> CIPSD06StructArray;

    /** \brief factory for lhwapp::PSD06Struct. */
    class PROXY_EXPORT PSD06StructFactory  : CIFactory<PSD06Struct> {
    public:
        static inline CIPtr<PSD06Struct> createPSD06Struct() {
            return CIFactory<PSD06Struct>::createObject();
        }
        static inline void createPSD06Struct(CIPtr<PSD06Struct> & s) {
            CIFactory<PSD06Struct>::createObject(s);
        }
        static inline CIPtr<CIPSD06StructArray> createPSD06StructArray(size_t size) {
            return CIFactory<PSD06Struct>::createArray(size);
        }
        static inline void createPSD06StructArray(CIPtr<CIPSD06StructArray>& a, size_t size) {
            CIFactory<PSD06Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_PSD06STRUCT_HXX
