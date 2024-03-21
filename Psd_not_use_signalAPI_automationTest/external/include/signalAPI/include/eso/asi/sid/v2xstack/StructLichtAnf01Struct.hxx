/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_LICHTANF01STRUCT_HXX
#define ASI_SID_V2XSTACK_LICHTANF01STRUCT_HXX

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
    \brief struct v2xstack::LichtAnf01Struct.
    */
    struct PROXY_EXPORT LichtAnf01Struct
    {
        bool BCM1_Nebellicht_Anf_Raw; // optional=False
        bool BCM1_Parklicht_li_Anf_Raw; // optional=False
        bool BCM1_Parklicht_re_Anf_Raw; // optional=False
        bool BCM1_Nebelschluss_Fzg_Anf_Raw; // optional=False
        bool BCM1_Tagfahrlicht_Anf_Raw; // optional=False
        bool BCM1_Abblendlicht_Anf_Raw; // optional=False
        bool BCM1_Fernlicht_Anf_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            LichtAnf01Struct()
            :
            BCM1_Nebellicht_Anf_Raw(),
            BCM1_Parklicht_li_Anf_Raw(),
            BCM1_Parklicht_re_Anf_Raw(),
            BCM1_Nebelschluss_Fzg_Anf_Raw(),
            BCM1_Tagfahrlicht_Anf_Raw(),
            BCM1_Abblendlicht_Anf_Raw(),
            BCM1_Fernlicht_Anf_Raw(),
            PduState()
            { }
            friend class LichtAnf01StructFactory;
            friend class CIFactory<LichtAnf01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::LichtAnf01Struct> >;
            friend class ipl::vector<LichtAnf01Struct>;
            friend class ipl::allocator<LichtAnf01Struct>;
#endif
    };

    typedef CIPtrArray<LichtAnf01Struct> CILichtAnf01StructArray;

    /** \brief factory for v2xstack::LichtAnf01Struct. */
    class PROXY_EXPORT LichtAnf01StructFactory  : CIFactory<LichtAnf01Struct> {
    public:
        static inline CIPtr<LichtAnf01Struct> createLichtAnf01Struct() {
            return CIFactory<LichtAnf01Struct>::createObject();
        }
        static inline void createLichtAnf01Struct(CIPtr<LichtAnf01Struct> & s) {
            CIFactory<LichtAnf01Struct>::createObject(s);
        }
        static inline CIPtr<CILichtAnf01StructArray> createLichtAnf01StructArray(size_t size) {
            return CIFactory<LichtAnf01Struct>::createArray(size);
        }
        static inline void createLichtAnf01StructArray(CIPtr<CILichtAnf01StructArray>& a, size_t size) {
            CIFactory<LichtAnf01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_LICHTANF01STRUCT_HXX
