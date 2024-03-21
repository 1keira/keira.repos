/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef COMM_BROKER_UPDATEEVENT_HXX
#define COMM_BROKER_UPDATEEVENT_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <comm/broker/StructInstanceID.hxx>
#include <comm/broker/Definitions.hxx>
#include <comm/broker/Definitions.hxx>

#undef unix

namespace comm
{
namespace broker
{

    /**
    \brief struct broker::UpdateEvent.
    */
    struct PROXY_EXPORT UpdateEvent
    {
        comm::broker::ServiceAction action; // optional=False
        comm::broker::ServiceReason reason; // optional=False
        CIPtr< comm::broker::InstanceID > svc_id; // optional=True
        uint16_t home_agent_id; // optional=False
        private:
            UpdateEvent()
            :
            action(),
            reason(),
            svc_id(),
            home_agent_id()
            { }
            friend class UpdateEventFactory;
            friend class CIFactory<UpdateEvent>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<comm::broker::UpdateEvent> >;
            friend class ipl::vector<UpdateEvent>;
            friend class ipl::allocator<UpdateEvent>;
#endif
    };

    typedef CIPtrArray<UpdateEvent> CIUpdateEventArray;

    /** \brief factory for broker::UpdateEvent. */
    class PROXY_EXPORT UpdateEventFactory  : CIFactory<UpdateEvent> {
    public:
        static inline CIPtr<UpdateEvent> createUpdateEvent() {
            return CIFactory<UpdateEvent>::createObject();
        }
        static inline void createUpdateEvent(CIPtr<UpdateEvent> & s) {
            CIFactory<UpdateEvent>::createObject(s);
        }
        static inline CIPtr<CIUpdateEventArray> createUpdateEventArray(size_t size) {
            return CIFactory<UpdateEvent>::createArray(size);
        }
        static inline void createUpdateEventArray(CIPtr<CIUpdateEventArray>& a, size_t size) {
            CIFactory<UpdateEvent>::createArray(a, size);
        }
    };
}//namespace comm
}//namespace broker


#endif// COMM_BROKER_UPDATEEVENT_HXX
