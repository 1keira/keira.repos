/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLFORWARDINGSTATUS_HXX
#define ASI_CONNECTIVITY_AL_CALLFORWARDINGSTATUS_HXX

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
    \brief struct al::CallForwardingStatus.
    */
    struct PROXY_EXPORT CallForwardingStatus
    {
        asi::connectivity::al::CfcReason reason; // optional=False
        asi::connectivity::al::ServiceClass service_class; // optional=False
        CIPtr< CIString > number; // optional=True
        uint32_t time; // optional=False
        private:
            CallForwardingStatus()
            :
            reason(),
            service_class(),
            number(),
            time()
            { }
            friend class CallForwardingStatusFactory;
            friend class CIFactory<CallForwardingStatus>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::CallForwardingStatus> >;
            friend class ipl::vector<CallForwardingStatus>;
            friend class ipl::allocator<CallForwardingStatus>;
#endif
    };

    typedef CIPtrArray<CallForwardingStatus> CICallForwardingStatusArray;

    /** \brief factory for al::CallForwardingStatus. */
    class PROXY_EXPORT CallForwardingStatusFactory  : CIFactory<CallForwardingStatus> {
    public:
        static inline CIPtr<CallForwardingStatus> createCallForwardingStatus() {
            return CIFactory<CallForwardingStatus>::createObject();
        }
        static inline void createCallForwardingStatus(CIPtr<CallForwardingStatus> & s) {
            CIFactory<CallForwardingStatus>::createObject(s);
        }
        static inline CIPtr<CICallForwardingStatusArray> createCallForwardingStatusArray(size_t size) {
            return CIFactory<CallForwardingStatus>::createArray(size);
        }
        static inline void createCallForwardingStatusArray(CIPtr<CICallForwardingStatusArray>& a, size_t size) {
            CIFactory<CallForwardingStatus>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_CALLFORWARDINGSTATUS_HXX
