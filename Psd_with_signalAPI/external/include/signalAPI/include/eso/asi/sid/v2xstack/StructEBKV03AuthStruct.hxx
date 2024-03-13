/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_EBKV03AUTHSTRUCT_HXX
#define ASI_SID_V2XSTACK_EBKV03AUTHSTRUCT_HXX

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
    \brief struct v2xstack::EBKV03AuthStruct.
    */
    struct PROXY_EXPORT EBKV03AuthStruct
    {
        bool EBKV_QBit_Fahrer_bremst_Raw; // optional=False
        bool EBKV_Fahrer_bremst_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            EBKV03AuthStruct()
            :
            EBKV_QBit_Fahrer_bremst_Raw(),
            EBKV_Fahrer_bremst_Raw(),
            PduState()
            { }
            friend class EBKV03AuthStructFactory;
            friend class CIFactory<EBKV03AuthStruct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::EBKV03AuthStruct> >;
            friend class ipl::vector<EBKV03AuthStruct>;
            friend class ipl::allocator<EBKV03AuthStruct>;
#endif
    };

    typedef CIPtrArray<EBKV03AuthStruct> CIEBKV03AuthStructArray;

    /** \brief factory for v2xstack::EBKV03AuthStruct. */
    class PROXY_EXPORT EBKV03AuthStructFactory  : CIFactory<EBKV03AuthStruct> {
    public:
        static inline CIPtr<EBKV03AuthStruct> createEBKV03AuthStruct() {
            return CIFactory<EBKV03AuthStruct>::createObject();
        }
        static inline void createEBKV03AuthStruct(CIPtr<EBKV03AuthStruct> & s) {
            CIFactory<EBKV03AuthStruct>::createObject(s);
        }
        static inline CIPtr<CIEBKV03AuthStructArray> createEBKV03AuthStructArray(size_t size) {
            return CIFactory<EBKV03AuthStruct>::createArray(size);
        }
        static inline void createEBKV03AuthStructArray(CIPtr<CIEBKV03AuthStructArray>& a, size_t size) {
            CIFactory<EBKV03AuthStruct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_EBKV03AUTHSTRUCT_HXX
