/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_RKA01STRUCT_HXX
#define ASI_SID_LHWAPP_RKA01STRUCT_HXX

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
    \brief struct lhwapp::RKA01Struct.
    */
    struct PROXY_EXPORT RKA01Struct
    {
        bool RKA_FMVSS138_Lampe_Raw; // optional=False
        uint8_t RKA_Warnungen_02_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            RKA01Struct()
            :
            RKA_FMVSS138_Lampe_Raw(),
            RKA_Warnungen_02_Raw(),
            PduState()
            { }
            friend class RKA01StructFactory;
            friend class CIFactory<RKA01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::RKA01Struct> >;
            friend class ipl::vector<RKA01Struct>;
            friend class ipl::allocator<RKA01Struct>;
#endif
    };

    typedef CIPtrArray<RKA01Struct> CIRKA01StructArray;

    /** \brief factory for lhwapp::RKA01Struct. */
    class PROXY_EXPORT RKA01StructFactory  : CIFactory<RKA01Struct> {
    public:
        static inline CIPtr<RKA01Struct> createRKA01Struct() {
            return CIFactory<RKA01Struct>::createObject();
        }
        static inline void createRKA01Struct(CIPtr<RKA01Struct> & s) {
            CIFactory<RKA01Struct>::createObject(s);
        }
        static inline CIPtr<CIRKA01StructArray> createRKA01StructArray(size_t size) {
            return CIFactory<RKA01Struct>::createArray(size);
        }
        static inline void createRKA01StructArray(CIPtr<CIRKA01StructArray>& a, size_t size) {
            CIFactory<RKA01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_RKA01STRUCT_HXX
