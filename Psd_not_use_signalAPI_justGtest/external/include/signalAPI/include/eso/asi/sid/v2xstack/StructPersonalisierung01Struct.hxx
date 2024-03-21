/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_PERSONALISIERUNG01STRUCT_HXX
#define ASI_SID_V2XSTACK_PERSONALISIERUNG01STRUCT_HXX

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
    \brief struct v2xstack::Personalisierung01Struct.
    */
    struct PROXY_EXPORT Personalisierung01Struct
    {
        uint8_t Perso_Steuerung_Raw; // optional=False
        uint8_t Perso_Steuerungsparameter_Raw; // optional=False
        uint8_t Perso_Status_Raw; // optional=False
        uint8_t Perso_Kontonummer_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Personalisierung01Struct()
            :
            Perso_Steuerung_Raw(),
            Perso_Steuerungsparameter_Raw(),
            Perso_Status_Raw(),
            Perso_Kontonummer_Raw(),
            PduState()
            { }
            friend class Personalisierung01StructFactory;
            friend class CIFactory<Personalisierung01Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::Personalisierung01Struct> >;
            friend class ipl::vector<Personalisierung01Struct>;
            friend class ipl::allocator<Personalisierung01Struct>;
#endif
    };

    typedef CIPtrArray<Personalisierung01Struct> CIPersonalisierung01StructArray;

    /** \brief factory for v2xstack::Personalisierung01Struct. */
    class PROXY_EXPORT Personalisierung01StructFactory  : CIFactory<Personalisierung01Struct> {
    public:
        static inline CIPtr<Personalisierung01Struct> createPersonalisierung01Struct() {
            return CIFactory<Personalisierung01Struct>::createObject();
        }
        static inline void createPersonalisierung01Struct(CIPtr<Personalisierung01Struct> & s) {
            CIFactory<Personalisierung01Struct>::createObject(s);
        }
        static inline CIPtr<CIPersonalisierung01StructArray> createPersonalisierung01StructArray(size_t size) {
            return CIFactory<Personalisierung01Struct>::createArray(size);
        }
        static inline void createPersonalisierung01StructArray(CIPtr<CIPersonalisierung01StructArray>& a, size_t size) {
            CIFactory<Personalisierung01Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_PERSONALISIERUNG01STRUCT_HXX
