/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_LICHTVORNE01STRUCT_HXX
#define ASI_SID_V2XSTACK_LICHTVORNE01STRUCT_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace sid
{
namespace v2xstack
{

    /**
    \brief struct v2xstack::Lichtvorne01Struct.
    */
    struct PROXY_EXPORT Lichtvorne01Struct
    {
        bool LV_AFL_aktiv_Anzeige_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Lichtvorne01Struct()
            :
            LV_AFL_aktiv_Anzeige_Raw(),
            PduState()
            { }
            friend class Lichtvorne01StructFactory;
            friend class CIFactory<Lichtvorne01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::Lichtvorne01Struct> >;
            friend class ipl::vector<Lichtvorne01Struct>;
            friend class ipl::allocator<Lichtvorne01Struct>;
#endif
    };

    typedef CIPtrArray<Lichtvorne01Struct> CILichtvorne01StructArray;

    /** \brief factory for v2xstack::Lichtvorne01Struct. */
    class PROXY_EXPORT Lichtvorne01StructFactory  : CIFactory<Lichtvorne01Struct> {
    public:
        static inline CIPtr<Lichtvorne01Struct> createLichtvorne01Struct() {
            return CIFactory<Lichtvorne01Struct>::createObject();
        }
        static inline void createLichtvorne01Struct(CIPtr<Lichtvorne01Struct> & s) {
            CIFactory<Lichtvorne01Struct>::createObject(s);
        }
        static inline CIPtr<CILichtvorne01StructArray> createLichtvorne01StructArray(size_t size) {
            return CIFactory<Lichtvorne01Struct>::createArray(size);
        }
        static inline void createLichtvorne01StructArray(CIPtr<CILichtvorne01StructArray>& a, size_t size) {
            CIFactory<Lichtvorne01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_LICHTVORNE01STRUCT_HXX
