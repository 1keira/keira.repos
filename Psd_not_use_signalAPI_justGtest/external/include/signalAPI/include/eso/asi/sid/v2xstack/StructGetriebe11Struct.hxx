/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_GETRIEBE11STRUCT_HXX
#define ASI_SID_V2XSTACK_GETRIEBE11STRUCT_HXX

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
    \brief struct v2xstack::Getriebe11Struct.
    */
    struct PROXY_EXPORT Getriebe11Struct
    {
        uint8_t GE_Fahrstufe_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Getriebe11Struct()
            :
            GE_Fahrstufe_Raw(),
            PduState()
            { }
            friend class Getriebe11StructFactory;
            friend class CIFactory<Getriebe11Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::Getriebe11Struct> >;
            friend class ipl::vector<Getriebe11Struct>;
            friend class ipl::allocator<Getriebe11Struct>;
#endif
    };

    typedef CIPtrArray<Getriebe11Struct> CIGetriebe11StructArray;

    /** \brief factory for v2xstack::Getriebe11Struct. */
    class PROXY_EXPORT Getriebe11StructFactory  : CIFactory<Getriebe11Struct> {
    public:
        static inline CIPtr<Getriebe11Struct> createGetriebe11Struct() {
            return CIFactory<Getriebe11Struct>::createObject();
        }
        static inline void createGetriebe11Struct(CIPtr<Getriebe11Struct> & s) {
            CIFactory<Getriebe11Struct>::createObject(s);
        }
        static inline CIPtr<CIGetriebe11StructArray> createGetriebe11StructArray(size_t size) {
            return CIFactory<Getriebe11Struct>::createArray(size);
        }
        static inline void createGetriebe11StructArray(CIPtr<CIGetriebe11StructArray>& a, size_t size) {
            CIFactory<Getriebe11Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_GETRIEBE11STRUCT_HXX
