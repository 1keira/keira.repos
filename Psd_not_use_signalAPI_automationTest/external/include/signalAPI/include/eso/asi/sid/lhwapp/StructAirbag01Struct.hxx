/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_AIRBAG01STRUCT_HXX
#define ASI_SID_LHWAPP_AIRBAG01STRUCT_HXX

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
    \brief struct lhwapp::Airbag01Struct.
    */
    struct PROXY_EXPORT Airbag01Struct
    {
        uint8_t AB_Crash_Int_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Airbag01Struct()
            :
            AB_Crash_Int_Raw(),
            PduState()
            { }
            friend class Airbag01StructFactory;
            friend class CIFactory<Airbag01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::Airbag01Struct> >;
            friend class ipl::vector<Airbag01Struct>;
            friend class ipl::allocator<Airbag01Struct>;
#endif
    };

    typedef CIPtrArray<Airbag01Struct> CIAirbag01StructArray;

    /** \brief factory for lhwapp::Airbag01Struct. */
    class PROXY_EXPORT Airbag01StructFactory  : CIFactory<Airbag01Struct> {
    public:
        static inline CIPtr<Airbag01Struct> createAirbag01Struct() {
            return CIFactory<Airbag01Struct>::createObject();
        }
        static inline void createAirbag01Struct(CIPtr<Airbag01Struct> & s) {
            CIFactory<Airbag01Struct>::createObject(s);
        }
        static inline CIPtr<CIAirbag01StructArray> createAirbag01StructArray(size_t size) {
            return CIFactory<Airbag01Struct>::createArray(size);
        }
        static inline void createAirbag01StructArray(CIPtr<CIAirbag01StructArray>& a, size_t size) {
            CIFactory<Airbag01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_AIRBAG01STRUCT_HXX
