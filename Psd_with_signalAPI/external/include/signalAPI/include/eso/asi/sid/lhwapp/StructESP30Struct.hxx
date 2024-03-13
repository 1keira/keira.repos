/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_ESP30STRUCT_HXX
#define ASI_SID_LHWAPP_ESP30STRUCT_HXX

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
    \brief struct lhwapp::ESP30Struct.
    */
    struct PROXY_EXPORT ESP30Struct
    {
        uint8_t RLE_Anzeigen_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            ESP30Struct()
            :
            RLE_Anzeigen_Raw(),
            PduState()
            { }
            friend class ESP30StructFactory;
            friend class CIFactory<ESP30Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::ESP30Struct> >;
            friend class ipl::vector<ESP30Struct>;
            friend class ipl::allocator<ESP30Struct>;
#endif
    };

    typedef CIPtrArray<ESP30Struct> CIESP30StructArray;

    /** \brief factory for lhwapp::ESP30Struct. */
    class PROXY_EXPORT ESP30StructFactory  : CIFactory<ESP30Struct> {
    public:
        static inline CIPtr<ESP30Struct> createESP30Struct() {
            return CIFactory<ESP30Struct>::createObject();
        }
        static inline void createESP30Struct(CIPtr<ESP30Struct> & s) {
            CIFactory<ESP30Struct>::createObject(s);
        }
        static inline CIPtr<CIESP30StructArray> createESP30StructArray(size_t size) {
            return CIFactory<ESP30Struct>::createArray(size);
        }
        static inline void createESP30StructArray(CIPtr<CIESP30StructArray>& a, size_t size) {
            CIFactory<ESP30Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_ESP30STRUCT_HXX
