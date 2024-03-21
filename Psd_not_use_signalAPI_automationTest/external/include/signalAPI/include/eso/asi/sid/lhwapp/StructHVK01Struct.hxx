/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_HVK01STRUCT_HXX
#define ASI_SID_LHWAPP_HVK01STRUCT_HXX

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
    \brief struct lhwapp::HVK01Struct.
    */
    struct PROXY_EXPORT HVK01Struct
    {
        uint8_t HVK_HV_Netz_Warnungen_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            HVK01Struct()
            :
            HVK_HV_Netz_Warnungen_Raw(),
            PduState()
            { }
            friend class HVK01StructFactory;
            friend class CIFactory<HVK01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::HVK01Struct> >;
            friend class ipl::vector<HVK01Struct>;
            friend class ipl::allocator<HVK01Struct>;
#endif
    };

    typedef CIPtrArray<HVK01Struct> CIHVK01StructArray;

    /** \brief factory for lhwapp::HVK01Struct. */
    class PROXY_EXPORT HVK01StructFactory  : CIFactory<HVK01Struct> {
    public:
        static inline CIPtr<HVK01Struct> createHVK01Struct() {
            return CIFactory<HVK01Struct>::createObject();
        }
        static inline void createHVK01Struct(CIPtr<HVK01Struct> & s) {
            CIFactory<HVK01Struct>::createObject(s);
        }
        static inline CIPtr<CIHVK01StructArray> createHVK01StructArray(size_t size) {
            return CIFactory<HVK01Struct>::createArray(size);
        }
        static inline void createHVK01StructArray(CIPtr<CIHVK01StructArray>& a, size_t size) {
            CIFactory<HVK01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_HVK01STRUCT_HXX
