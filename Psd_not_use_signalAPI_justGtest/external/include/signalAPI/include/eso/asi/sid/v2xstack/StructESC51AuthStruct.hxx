/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_ESC51AUTHSTRUCT_HXX
#define ASI_SID_V2XSTACK_ESC51AUTHSTRUCT_HXX

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
    \brief struct v2xstack::ESC51AuthStruct.
    */
    struct PROXY_EXPORT ESC51AuthStruct
    {
        uint8_t ESP_HR_Bremsmoment_Raw; // optional=False
        uint64_t ESP_HR_Bremsmoment_SignalState; // optional=False
        uint8_t ESP_VR_Bremsmoment_Raw; // optional=False
        uint64_t ESP_VR_Bremsmoment_SignalState; // optional=False
        uint8_t ESP_VL_Bremsmoment_Raw; // optional=False
        uint64_t ESP_VL_Bremsmoment_SignalState; // optional=False
        uint8_t ESP_HL_Bremsmoment_Raw; // optional=False
        uint64_t ESP_HL_Bremsmoment_SignalState; // optional=False
        uint64_t PduState; // optional=False
        private:
            ESC51AuthStruct()
            :
            ESP_HR_Bremsmoment_Raw(),
            ESP_HR_Bremsmoment_SignalState(),
            ESP_VR_Bremsmoment_Raw(),
            ESP_VR_Bremsmoment_SignalState(),
            ESP_VL_Bremsmoment_Raw(),
            ESP_VL_Bremsmoment_SignalState(),
            ESP_HL_Bremsmoment_Raw(),
            ESP_HL_Bremsmoment_SignalState(),
            PduState()
            { }
            friend class ESC51AuthStructFactory;
            friend class CIFactory<ESC51AuthStruct>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::sid::v2xstack::ESC51AuthStruct> >;
            friend class ipl::vector<ESC51AuthStruct>;
            friend class ipl::allocator<ESC51AuthStruct>;
#endif
    };

    typedef CIPtrArray<ESC51AuthStruct> CIESC51AuthStructArray;

    /** \brief factory for v2xstack::ESC51AuthStruct. */
    class PROXY_EXPORT ESC51AuthStructFactory  : CIFactory<ESC51AuthStruct> {
    public:
        static inline CIPtr<ESC51AuthStruct> createESC51AuthStruct() {
            return CIFactory<ESC51AuthStruct>::createObject();
        }
        static inline void createESC51AuthStruct(CIPtr<ESC51AuthStruct> & s) {
            CIFactory<ESC51AuthStruct>::createObject(s);
        }
        static inline CIPtr<CIESC51AuthStructArray> createESC51AuthStructArray(size_t size) {
            return CIFactory<ESC51AuthStruct>::createArray(size);
        }
        static inline void createESC51AuthStructArray(CIPtr<CIESC51AuthStructArray>& a, size_t size) {
            CIFactory<ESC51AuthStruct>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace sid
}//namespace v2xstack


#endif// ASI_SID_V2XSTACK_ESC51AUTHSTRUCT_HXX
