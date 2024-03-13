/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_ESP24STRUCT_HXX
#define ASI_SID_LHWAPP_ESP24STRUCT_HXX

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
    \brief struct lhwapp::ESP24Struct.
    */
    struct PROXY_EXPORT ESP24Struct
    {
        bool ESP_Lampe_Raw; // optional=False
        bool ABS_Lampe_Raw; // optional=False
        uint8_t BK_Lampe_02_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            ESP24Struct()
            :
            ESP_Lampe_Raw(),
            ABS_Lampe_Raw(),
            BK_Lampe_02_Raw(),
            PduState()
            { }
            friend class ESP24StructFactory;
            friend class CIFactory<ESP24Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::ESP24Struct> >;
            friend class ipl::vector<ESP24Struct>;
            friend class ipl::allocator<ESP24Struct>;
#endif
    };

    typedef CIPtrArray<ESP24Struct> CIESP24StructArray;

    /** \brief factory for lhwapp::ESP24Struct. */
    class PROXY_EXPORT ESP24StructFactory  : CIFactory<ESP24Struct> {
    public:
        static inline CIPtr<ESP24Struct> createESP24Struct() {
            return CIFactory<ESP24Struct>::createObject();
        }
        static inline void createESP24Struct(CIPtr<ESP24Struct> & s) {
            CIFactory<ESP24Struct>::createObject(s);
        }
        static inline CIPtr<CIESP24StructArray> createESP24StructArray(size_t size) {
            return CIFactory<ESP24Struct>::createArray(size);
        }
        static inline void createESP24StructArray(CIPtr<CIESP24StructArray>& a, size_t size) {
            CIFactory<ESP24Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_ESP24STRUCT_HXX
