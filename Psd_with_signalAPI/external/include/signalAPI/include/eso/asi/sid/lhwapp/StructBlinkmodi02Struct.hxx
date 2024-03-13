/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_BLINKMODI02STRUCT_HXX
#define ASI_SID_LHWAPP_BLINKMODI02STRUCT_HXX

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
    \brief struct lhwapp::Blinkmodi02Struct.
    */
    struct PROXY_EXPORT Blinkmodi02Struct
    {
        bool BM_Recas_Raw; // optional=False
        bool BM_Crash_Raw; // optional=False
        bool BM_Warnblinken_Raw; // optional=False
        bool BM_Not_Bremsung_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Blinkmodi02Struct()
            :
            BM_Recas_Raw(),
            BM_Crash_Raw(),
            BM_Warnblinken_Raw(),
            BM_Not_Bremsung_Raw(),
            PduState()
            { }
            friend class Blinkmodi02StructFactory;
            friend class CIFactory<Blinkmodi02Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::Blinkmodi02Struct> >;
            friend class ipl::vector<Blinkmodi02Struct>;
            friend class ipl::allocator<Blinkmodi02Struct>;
#endif
    };

    typedef CIPtrArray<Blinkmodi02Struct> CIBlinkmodi02StructArray;

    /** \brief factory for lhwapp::Blinkmodi02Struct. */
    class PROXY_EXPORT Blinkmodi02StructFactory  : CIFactory<Blinkmodi02Struct> {
    public:
        static inline CIPtr<Blinkmodi02Struct> createBlinkmodi02Struct() {
            return CIFactory<Blinkmodi02Struct>::createObject();
        }
        static inline void createBlinkmodi02Struct(CIPtr<Blinkmodi02Struct> & s) {
            CIFactory<Blinkmodi02Struct>::createObject(s);
        }
        static inline CIPtr<CIBlinkmodi02StructArray> createBlinkmodi02StructArray(size_t size) {
            return CIFactory<Blinkmodi02Struct>::createArray(size);
        }
        static inline void createBlinkmodi02StructArray(CIPtr<CIBlinkmodi02StructArray>& a, size_t size) {
            CIFactory<Blinkmodi02Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_BLINKMODI02STRUCT_HXX
