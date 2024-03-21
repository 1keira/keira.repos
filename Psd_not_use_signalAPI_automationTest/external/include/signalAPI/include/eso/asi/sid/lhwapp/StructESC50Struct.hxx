/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_ESC50STRUCT_HXX
#define ASI_SID_LHWAPP_ESC50STRUCT_HXX

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
    \brief struct lhwapp::ESC50Struct.
    */
    struct PROXY_EXPORT ESC50Struct
    {
        bool ESP_QBit_Gierrate_Raw; // optional=False
        bool ESP_QBit_Laengsbeschl_Raw; // optional=False
        bool ESP_QBit_Querb_Raw; // optional=False
        uint8_t ESP_Querbeschleunigung_Raw; // optional=False
        uint64_t ESP_Querbeschleunigung_SignalState; // optional=False
        bool ESP_Eingr_HL_Raw; // optional=False
        bool ESP_Eingr_HR_Raw; // optional=False
        bool ESP_Eingr_VL_Raw; // optional=False
        bool ESP_Eingr_VR_Raw; // optional=False
        uint16_t ESP_Laengsbeschl_Raw; // optional=False
        uint64_t ESP_Laengsbeschl_SignalState; // optional=False
        uint16_t ESP_Gierrate_Raw; // optional=False
        uint64_t ESP_Gierrate_SignalState; // optional=False
        bool ESP_VZ_Gierrate_Raw; // optional=False
        bool ESP_Notbremsanzeige_Raw; // optional=False
        bool ESP_Fahrer_bremst_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            ESC50Struct()
            :
            ESP_QBit_Gierrate_Raw(),
            ESP_QBit_Laengsbeschl_Raw(),
            ESP_QBit_Querb_Raw(),
            ESP_Querbeschleunigung_Raw(),
            ESP_Querbeschleunigung_SignalState(),
            ESP_Eingr_HL_Raw(),
            ESP_Eingr_HR_Raw(),
            ESP_Eingr_VL_Raw(),
            ESP_Eingr_VR_Raw(),
            ESP_Laengsbeschl_Raw(),
            ESP_Laengsbeschl_SignalState(),
            ESP_Gierrate_Raw(),
            ESP_Gierrate_SignalState(),
            ESP_VZ_Gierrate_Raw(),
            ESP_Notbremsanzeige_Raw(),
            ESP_Fahrer_bremst_Raw(),
            PduState()
            { }
            friend class ESC50StructFactory;
            friend class CIFactory<ESC50Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::ESC50Struct> >;
            friend class ipl::vector<ESC50Struct>;
            friend class ipl::allocator<ESC50Struct>;
#endif
    };

    typedef CIPtrArray<ESC50Struct> CIESC50StructArray;

    /** \brief factory for lhwapp::ESC50Struct. */
    class PROXY_EXPORT ESC50StructFactory  : CIFactory<ESC50Struct> {
    public:
        static inline CIPtr<ESC50Struct> createESC50Struct() {
            return CIFactory<ESC50Struct>::createObject();
        }
        static inline void createESC50Struct(CIPtr<ESC50Struct> & s) {
            CIFactory<ESC50Struct>::createObject(s);
        }
        static inline CIPtr<CIESC50StructArray> createESC50StructArray(size_t size) {
            return CIFactory<ESC50Struct>::createArray(size);
        }
        static inline void createESC50StructArray(CIPtr<CIESC50StructArray>& a, size_t size) {
            CIFactory<ESC50Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_ESC50STRUCT_HXX
