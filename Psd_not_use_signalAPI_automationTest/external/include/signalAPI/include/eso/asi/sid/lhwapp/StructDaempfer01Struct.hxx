/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_DAEMPFER01STRUCT_HXX
#define ASI_SID_LHWAPP_DAEMPFER01STRUCT_HXX

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
    \brief struct lhwapp::Daempfer01Struct.
    */
    struct PROXY_EXPORT Daempfer01Struct
    {
        uint8_t DR_Gelbe_Warnlampe_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Daempfer01Struct()
            :
            DR_Gelbe_Warnlampe_Raw(),
            PduState()
            { }
            friend class Daempfer01StructFactory;
            friend class CIFactory<Daempfer01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::Daempfer01Struct> >;
            friend class ipl::vector<Daempfer01Struct>;
            friend class ipl::allocator<Daempfer01Struct>;
#endif
    };

    typedef CIPtrArray<Daempfer01Struct> CIDaempfer01StructArray;

    /** \brief factory for lhwapp::Daempfer01Struct. */
    class PROXY_EXPORT Daempfer01StructFactory  : CIFactory<Daempfer01Struct> {
    public:
        static inline CIPtr<Daempfer01Struct> createDaempfer01Struct() {
            return CIFactory<Daempfer01Struct>::createObject();
        }
        static inline void createDaempfer01Struct(CIPtr<Daempfer01Struct> & s) {
            CIFactory<Daempfer01Struct>::createObject(s);
        }
        static inline CIPtr<CIDaempfer01StructArray> createDaempfer01StructArray(size_t size) {
            return CIFactory<Daempfer01Struct>::createArray(size);
        }
        static inline void createDaempfer01StructArray(CIPtr<CIDaempfer01StructArray>& a, size_t size) {
            CIFactory<Daempfer01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_DAEMPFER01STRUCT_HXX
