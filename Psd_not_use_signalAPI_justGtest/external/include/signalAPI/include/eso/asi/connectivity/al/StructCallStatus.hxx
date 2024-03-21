/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLSTATUS_HXX
#define ASI_CONNECTIVITY_AL_CALLSTATUS_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::CallStatus.
    */
    struct PROXY_EXPORT CallStatus
    {
        int32_t callID; // optional=False
        asi::connectivity::al::CallState callState; // optional=False
        asi::connectivity::al::CallDirection callDirection; // optional=False
        bool isMultiCall; // optional=False
        CIPtr< CIString > telNumber; // optional=True
        private:
            CallStatus()
            :
            callID(),
            callState(),
            callDirection(),
            isMultiCall(),
            telNumber()
            { }
            friend class CallStatusFactory;
            friend class CIFactory<CallStatus>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::CallStatus> >;
            friend class ipl::vector<CallStatus>;
            friend class ipl::allocator<CallStatus>;
#endif
    };

    typedef CIPtrArray<CallStatus> CICallStatusArray;

    /** \brief factory for al::CallStatus. */
    class PROXY_EXPORT CallStatusFactory  : CIFactory<CallStatus> {
    public:
        static inline CIPtr<CallStatus> createCallStatus() {
            return CIFactory<CallStatus>::createObject();
        }
        static inline void createCallStatus(CIPtr<CallStatus> & s) {
            CIFactory<CallStatus>::createObject(s);
        }
        static inline CIPtr<CICallStatusArray> createCallStatusArray(size_t size) {
            return CIFactory<CallStatus>::createArray(size);
        }
        static inline void createCallStatusArray(CIPtr<CICallStatusArray>& a, size_t size) {
            CIFactory<CallStatus>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_CALLSTATUS_HXX
