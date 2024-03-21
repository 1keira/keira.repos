/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_VMM02AUTHSTRUCT_HXX
#define ASI_SID_V2XSTACK_VMM02AUTHSTRUCT_HXX

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
    \brief struct v2xstack::VMM02AuthStruct.
    */
    struct PROXY_EXPORT VMM02AuthStruct
    {
        uint8_t HMS_aktives_System_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            VMM02AuthStruct()
            :
            HMS_aktives_System_Raw(),
            PduState()
            { }
            friend class VMM02AuthStructFactory;
            friend class CIFactory<VMM02AuthStruct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::VMM02AuthStruct> >;
            friend class ipl::vector<VMM02AuthStruct>;
            friend class ipl::allocator<VMM02AuthStruct>;
#endif
    };

    typedef CIPtrArray<VMM02AuthStruct> CIVMM02AuthStructArray;

    /** \brief factory for v2xstack::VMM02AuthStruct. */
    class PROXY_EXPORT VMM02AuthStructFactory  : CIFactory<VMM02AuthStruct> {
    public:
        static inline CIPtr<VMM02AuthStruct> createVMM02AuthStruct() {
            return CIFactory<VMM02AuthStruct>::createObject();
        }
        static inline void createVMM02AuthStruct(CIPtr<VMM02AuthStruct> & s) {
            CIFactory<VMM02AuthStruct>::createObject(s);
        }
        static inline CIPtr<CIVMM02AuthStructArray> createVMM02AuthStructArray(size_t size) {
            return CIFactory<VMM02AuthStruct>::createArray(size);
        }
        static inline void createVMM02AuthStructArray(CIPtr<CIVMM02AuthStructArray>& a, size_t size) {
            CIFactory<VMM02AuthStruct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_VMM02AUTHSTRUCT_HXX
