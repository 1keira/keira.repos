/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_ESP21STRUCT_HXX
#define ASI_SID_LHWAPP_ESP21STRUCT_HXX

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
    \brief struct lhwapp::ESP21Struct.
    */
    struct PROXY_EXPORT ESP21Struct
    {
        uint16_t ESP_v_Signal_Raw; // optional=False
        uint64_t ESP_v_Signal_SignalState; // optional=False
        bool ESP_QBit_v_Signal_Raw; // optional=False
        bool ABS_Bremsung_Raw; // optional=False
        bool ASR_Anf_Raw; // optional=False
        bool ESP_Eingriff_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            ESP21Struct()
            :
            ESP_v_Signal_Raw(),
            ESP_v_Signal_SignalState(),
            ESP_QBit_v_Signal_Raw(),
            ABS_Bremsung_Raw(),
            ASR_Anf_Raw(),
            ESP_Eingriff_Raw(),
            PduState()
            { }
            friend class ESP21StructFactory;
            friend class CIFactory<ESP21Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::ESP21Struct> >;
            friend class ipl::vector<ESP21Struct>;
            friend class ipl::allocator<ESP21Struct>;
#endif
    };

    typedef CIPtrArray<ESP21Struct> CIESP21StructArray;

    /** \brief factory for lhwapp::ESP21Struct. */
    class PROXY_EXPORT ESP21StructFactory  : CIFactory<ESP21Struct> {
    public:
        static inline CIPtr<ESP21Struct> createESP21Struct() {
            return CIFactory<ESP21Struct>::createObject();
        }
        static inline void createESP21Struct(CIPtr<ESP21Struct> & s) {
            CIFactory<ESP21Struct>::createObject(s);
        }
        static inline CIPtr<CIESP21StructArray> createESP21StructArray(size_t size) {
            return CIFactory<ESP21Struct>::createArray(size);
        }
        static inline void createESP21StructArray(CIPtr<CIESP21StructArray>& a, size_t size) {
            CIFactory<ESP21Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_ESP21STRUCT_HXX
