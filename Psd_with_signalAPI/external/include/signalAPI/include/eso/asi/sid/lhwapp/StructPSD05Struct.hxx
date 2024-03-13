/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_PSD05STRUCT_HXX
#define ASI_SID_LHWAPP_PSD05STRUCT_HXX

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
    \brief struct lhwapp::PSD05Struct.
    */
    struct PROXY_EXPORT PSD05Struct
    {
        uint8_t PSD_Pos_Segment_ID_Raw; // optional=False
        uint64_t PSD_Pos_Segment_ID_SignalState; // optional=False
        uint8_t PSD_Pos_Segmentlaenge_Raw; // optional=False
        bool PSD_Pos_Standort_Eindeutig_Raw; // optional=False
        uint8_t PSD_Pos_Fehler_Laengsrichtung_Raw; // optional=False
        uint8_t PSD_Attribut_1_ID_Raw; // optional=False
        uint64_t PSD_Attribut_1_ID_SignalState; // optional=False
        uint8_t PSD_Attribut_1_Wert_Raw; // optional=False
        uint8_t PSD_Attribut_2_ID_Raw; // optional=False
        uint64_t PSD_Attribut_2_ID_SignalState; // optional=False
        uint8_t PSD_Attribut_2_Wert_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            PSD05Struct()
            :
            PSD_Pos_Segment_ID_Raw(),
            PSD_Pos_Segment_ID_SignalState(),
            PSD_Pos_Segmentlaenge_Raw(),
            PSD_Pos_Standort_Eindeutig_Raw(),
            PSD_Pos_Fehler_Laengsrichtung_Raw(),
            PSD_Attribut_1_ID_Raw(),
            PSD_Attribut_1_ID_SignalState(),
            PSD_Attribut_1_Wert_Raw(),
            PSD_Attribut_2_ID_Raw(),
            PSD_Attribut_2_ID_SignalState(),
            PSD_Attribut_2_Wert_Raw(),
            PduState()
            { }
            friend class PSD05StructFactory;
            friend class CIFactory<PSD05Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::PSD05Struct> >;
            friend class ipl::vector<PSD05Struct>;
            friend class ipl::allocator<PSD05Struct>;
#endif
    };

    typedef CIPtrArray<PSD05Struct> CIPSD05StructArray;

    /** \brief factory for lhwapp::PSD05Struct. */
    class PROXY_EXPORT PSD05StructFactory  : CIFactory<PSD05Struct> {
    public:
        static inline CIPtr<PSD05Struct> createPSD05Struct() {
            return CIFactory<PSD05Struct>::createObject();
        }
        static inline void createPSD05Struct(CIPtr<PSD05Struct> & s) {
            CIFactory<PSD05Struct>::createObject(s);
        }
        static inline CIPtr<CIPSD05StructArray> createPSD05StructArray(size_t size) {
            return CIFactory<PSD05Struct>::createArray(size);
        }
        static inline void createPSD05StructArray(CIPtr<CIPSD05StructArray>& a, size_t size) {
            CIFactory<PSD05Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_PSD05STRUCT_HXX
