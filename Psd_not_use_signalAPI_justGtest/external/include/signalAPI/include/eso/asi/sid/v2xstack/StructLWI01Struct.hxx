/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_LWI01STRUCT_HXX
#define ASI_SID_V2XSTACK_LWI01STRUCT_HXX

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
    \brief struct v2xstack::LWI01Struct.
    */
    struct PROXY_EXPORT LWI01Struct
    {
        uint16_t LWI_Lenkradwinkel_Raw; // optional=False
        uint64_t LWI_Lenkradwinkel_SignalState; // optional=False
        bool LWI_VZ_Lenkradwinkel_Raw; // optional=False
        bool LWI_QBit_Lenkradwinkel_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            LWI01Struct()
            :
            LWI_Lenkradwinkel_Raw(),
            LWI_Lenkradwinkel_SignalState(),
            LWI_VZ_Lenkradwinkel_Raw(),
            LWI_QBit_Lenkradwinkel_Raw(),
            PduState()
            { }
            friend class LWI01StructFactory;
            friend class CIFactory<LWI01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::LWI01Struct> >;
            friend class ipl::vector<LWI01Struct>;
            friend class ipl::allocator<LWI01Struct>;
#endif
    };

    typedef CIPtrArray<LWI01Struct> CILWI01StructArray;

    /** \brief factory for v2xstack::LWI01Struct. */
    class PROXY_EXPORT LWI01StructFactory  : CIFactory<LWI01Struct> {
    public:
        static inline CIPtr<LWI01Struct> createLWI01Struct() {
            return CIFactory<LWI01Struct>::createObject();
        }
        static inline void createLWI01Struct(CIPtr<LWI01Struct> & s) {
            CIFactory<LWI01Struct>::createObject(s);
        }
        static inline CIPtr<CILWI01StructArray> createLWI01StructArray(size_t size) {
            return CIFactory<LWI01Struct>::createArray(size);
        }
        static inline void createLWI01StructArray(CIPtr<CILWI01StructArray>& a, size_t size) {
            CIFactory<LWI01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_LWI01STRUCT_HXX
