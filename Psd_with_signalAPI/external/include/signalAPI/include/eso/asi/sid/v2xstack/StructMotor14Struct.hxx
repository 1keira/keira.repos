/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_MOTOR14STRUCT_HXX
#define ASI_SID_V2XSTACK_MOTOR14STRUCT_HXX

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
    \brief struct v2xstack::Motor14Struct.
    */
    struct PROXY_EXPORT Motor14Struct
    {
        bool MO_Fahrer_bremst_Raw; // optional=False
        bool MO_QBit_Fahrer_bremst_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Motor14Struct()
            :
            MO_Fahrer_bremst_Raw(),
            MO_QBit_Fahrer_bremst_Raw(),
            PduState()
            { }
            friend class Motor14StructFactory;
            friend class CIFactory<Motor14Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::Motor14Struct> >;
            friend class ipl::vector<Motor14Struct>;
            friend class ipl::allocator<Motor14Struct>;
#endif
    };

    typedef CIPtrArray<Motor14Struct> CIMotor14StructArray;

    /** \brief factory for v2xstack::Motor14Struct. */
    class PROXY_EXPORT Motor14StructFactory  : CIFactory<Motor14Struct> {
    public:
        static inline CIPtr<Motor14Struct> createMotor14Struct() {
            return CIFactory<Motor14Struct>::createObject();
        }
        static inline void createMotor14Struct(CIPtr<Motor14Struct> & s) {
            CIFactory<Motor14Struct>::createObject(s);
        }
        static inline CIPtr<CIMotor14StructArray> createMotor14StructArray(size_t size) {
            return CIFactory<Motor14Struct>::createArray(size);
        }
        static inline void createMotor14StructArray(CIPtr<CIMotor14StructArray>& a, size_t size) {
            CIFactory<Motor14Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_MOTOR14STRUCT_HXX
