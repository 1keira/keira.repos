/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_PSD04STRUCT_HXX
#define ASI_SID_LHWAPP_PSD04STRUCT_HXX

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
    \brief struct lhwapp::PSD04Struct.
    */
    struct PROXY_EXPORT PSD04Struct
    {
        bool PSD_Endkruemmung_Vorz_Raw; // optional=False
        bool PSD_wahrscheinlichster_Pfad_Raw; // optional=False
        bool PSD_Geradester_Pfad_Raw; // optional=False
        bool PSD_Segment_Komplett_Raw; // optional=False
        uint8_t PSD_Anfangskruemmung_Raw; // optional=False
        uint64_t PSD_Anfangskruemmung_SignalState; // optional=False
        bool PSD_Anfangskruemmung_Vorz_Raw; // optional=False
        bool PSD_Abzweigerichtung_Raw; // optional=False
        uint8_t PSD_Abzweigewinkel_Raw; // optional=False
        uint8_t PSD_Segment_ID_Raw; // optional=False
        uint64_t PSD_Segment_ID_SignalState; // optional=False
        uint8_t PSD_Vorgaenger_Segment_ID_Raw; // optional=False
        uint64_t PSD_Vorgaenger_Segment_ID_SignalState; // optional=False
        uint8_t PSD_Segmentlaenge_Raw; // optional=False
        uint8_t PSD_Strassenkategorie_Raw; // optional=False
        uint8_t PSD_Endkruemmung_Raw; // optional=False
        uint64_t PSD_Endkruemmung_SignalState; // optional=False
        uint64_t PduState; // optional=False
        private:
            PSD04Struct()
            :
            PSD_Endkruemmung_Vorz_Raw(),
            PSD_wahrscheinlichster_Pfad_Raw(),
            PSD_Geradester_Pfad_Raw(),
            PSD_Segment_Komplett_Raw(),
            PSD_Anfangskruemmung_Raw(),
            PSD_Anfangskruemmung_SignalState(),
            PSD_Anfangskruemmung_Vorz_Raw(),
            PSD_Abzweigerichtung_Raw(),
            PSD_Abzweigewinkel_Raw(),
            PSD_Segment_ID_Raw(),
            PSD_Segment_ID_SignalState(),
            PSD_Vorgaenger_Segment_ID_Raw(),
            PSD_Vorgaenger_Segment_ID_SignalState(),
            PSD_Segmentlaenge_Raw(),
            PSD_Strassenkategorie_Raw(),
            PSD_Endkruemmung_Raw(),
            PSD_Endkruemmung_SignalState(),
            PduState()
            { }
            friend class PSD04StructFactory;
            friend class CIFactory<PSD04Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::PSD04Struct> >;
            friend class ipl::vector<PSD04Struct>;
            friend class ipl::allocator<PSD04Struct>;
#endif
    };

    typedef CIPtrArray<PSD04Struct> CIPSD04StructArray;

    /** \brief factory for lhwapp::PSD04Struct. */
    class PROXY_EXPORT PSD04StructFactory  : CIFactory<PSD04Struct> {
    public:
        static inline CIPtr<PSD04Struct> createPSD04Struct() {
            return CIFactory<PSD04Struct>::createObject();
        }
        static inline void createPSD04Struct(CIPtr<PSD04Struct> & s) {
            CIFactory<PSD04Struct>::createObject(s);
        }
        static inline CIPtr<CIPSD04StructArray> createPSD04StructArray(size_t size) {
            return CIFactory<PSD04Struct>::createArray(size);
        }
        static inline void createPSD04StructArray(CIPtr<CIPSD04StructArray>& a, size_t size) {
            CIFactory<PSD04Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_PSD04STRUCT_HXX
