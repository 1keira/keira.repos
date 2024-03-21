/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_KLEMMENSTATUS01STRUCT_HXX
#define ASI_SID_V2XSTACK_KLEMMENSTATUS01STRUCT_HXX

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
    \brief struct v2xstack::KlemmenStatus01Struct.
    */
    struct PROXY_EXPORT KlemmenStatus01Struct
    {
        bool ZAS_Kl_15_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            KlemmenStatus01Struct()
            :
            ZAS_Kl_15_Raw(),
            PduState()
            { }
            friend class KlemmenStatus01StructFactory;
            friend class CIFactory<KlemmenStatus01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::KlemmenStatus01Struct> >;
            friend class ipl::vector<KlemmenStatus01Struct>;
            friend class ipl::allocator<KlemmenStatus01Struct>;
#endif
    };

    typedef CIPtrArray<KlemmenStatus01Struct> CIKlemmenStatus01StructArray;

    /** \brief factory for v2xstack::KlemmenStatus01Struct. */
    class PROXY_EXPORT KlemmenStatus01StructFactory  : CIFactory<KlemmenStatus01Struct> {
    public:
        static inline CIPtr<KlemmenStatus01Struct> createKlemmenStatus01Struct() {
            return CIFactory<KlemmenStatus01Struct>::createObject();
        }
        static inline void createKlemmenStatus01Struct(CIPtr<KlemmenStatus01Struct> & s) {
            CIFactory<KlemmenStatus01Struct>::createObject(s);
        }
        static inline CIPtr<CIKlemmenStatus01StructArray> createKlemmenStatus01StructArray(size_t size) {
            return CIFactory<KlemmenStatus01Struct>::createArray(size);
        }
        static inline void createKlemmenStatus01StructArray(CIPtr<CIKlemmenStatus01StructArray>& a, size_t size) {
            CIFactory<KlemmenStatus01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_KLEMMENSTATUS01STRUCT_HXX
