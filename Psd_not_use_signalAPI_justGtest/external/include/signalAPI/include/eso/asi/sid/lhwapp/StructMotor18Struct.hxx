/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_MOTOR18STRUCT_HXX
#define ASI_SID_LHWAPP_MOTOR18STRUCT_HXX

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
    \brief struct lhwapp::Motor18Struct.
    */
    struct PROXY_EXPORT Motor18Struct
    {
        uint8_t MO_EPCL_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Motor18Struct()
            :
            MO_EPCL_Raw(),
            PduState()
            { }
            friend class Motor18StructFactory;
            friend class CIFactory<Motor18Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::Motor18Struct> >;
            friend class ipl::vector<Motor18Struct>;
            friend class ipl::allocator<Motor18Struct>;
#endif
    };

    typedef CIPtrArray<Motor18Struct> CIMotor18StructArray;

    /** \brief factory for lhwapp::Motor18Struct. */
    class PROXY_EXPORT Motor18StructFactory  : CIFactory<Motor18Struct> {
    public:
        static inline CIPtr<Motor18Struct> createMotor18Struct() {
            return CIFactory<Motor18Struct>::createObject();
        }
        static inline void createMotor18Struct(CIPtr<Motor18Struct> & s) {
            CIFactory<Motor18Struct>::createObject(s);
        }
        static inline CIPtr<CIMotor18StructArray> createMotor18StructArray(size_t size) {
            return CIFactory<Motor18Struct>::createArray(size);
        }
        static inline void createMotor18StructArray(CIPtr<CIMotor18StructArray>& a, size_t size) {
            CIFactory<Motor18Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_MOTOR18STRUCT_HXX
