/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_MOTOR41STRUCT_HXX
#define ASI_SID_LHWAPP_MOTOR41STRUCT_HXX

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
    \brief struct lhwapp::Motor41Struct.
    */
    struct PROXY_EXPORT Motor41Struct
    {
        uint8_t MO_EM_Ueberhitzungswarnung_Raw; // optional=False
        uint8_t FDR_Warnung_ALR_Raw; // optional=False
        uint64_t PduState; // optional=False
        private:
            Motor41Struct()
            :
            MO_EM_Ueberhitzungswarnung_Raw(),
            FDR_Warnung_ALR_Raw(),
            PduState()
            { }
            friend class Motor41StructFactory;
            friend class CIFactory<Motor41Struct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::lhwapp::Motor41Struct> >;
            friend class ipl::vector<Motor41Struct>;
            friend class ipl::allocator<Motor41Struct>;
#endif
    };

    typedef CIPtrArray<Motor41Struct> CIMotor41StructArray;

    /** \brief factory for lhwapp::Motor41Struct. */
    class PROXY_EXPORT Motor41StructFactory  : CIFactory<Motor41Struct> {
    public:
        static inline CIPtr<Motor41Struct> createMotor41Struct() {
            return CIFactory<Motor41Struct>::createObject();
        }
        static inline void createMotor41Struct(CIPtr<Motor41Struct> & s) {
            CIFactory<Motor41Struct>::createObject(s);
        }
        static inline CIPtr<CIMotor41StructArray> createMotor41StructArray(size_t size) {
            return CIFactory<Motor41Struct>::createArray(size);
        }
        static inline void createMotor41StructArray(CIPtr<CIMotor41StructArray>& a, size_t size) {
            CIFactory<Motor41Struct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace lhwapp


#endif// ASI_SID_LHWAPP_MOTOR41STRUCT_HXX
