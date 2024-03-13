/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef COMM_BROKER_UPDATEEVENT_CSTYLE_HXX
#define COMM_BROKER_UPDATEEVENT_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <comm/broker/cstyle/StructInstanceID.hxx>
#include <comm/broker/cstyle/Definitions.hxx>
#include <comm/broker/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace comm
{
namespace broker
{
namespace  cstyle
{
struct UpdateEvent;
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const comm::broker::cstyle::UpdateEvent& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, comm::broker::cstyle::UpdateEvent &val);
}
}

namespace comm
{
namespace broker
{
namespace  cstyle
{

    /**
    \brief struct broker::UpdateEvent.
    */
    struct PROXY_EXPORT UpdateEvent
    {
        public:
            UpdateEvent()
            : m_action()
            , m_reason()
            , m_home_agent_id()
            , m_svc_id(nullptr)
            { }

            UpdateEvent (const UpdateEvent& other)
            : m_action()
            , m_reason()
            , m_home_agent_id()
            , m_svc_id(nullptr)
            {
              *this = other;
            }

            ~UpdateEvent () {
                if (m_svc_id) {
                    delete m_svc_id;
                }
            }
            bool operator==(const UpdateEvent& rhs) const {
                bool equal = true;
                if (m_action != rhs.m_action)
                    equal = false;
                if (m_reason != rhs.m_reason)
                    equal = false;
                if (m_svc_id == nullptr && rhs.m_svc_id != nullptr)
                    equal = false;
                else if (m_svc_id != nullptr && rhs.m_svc_id == nullptr)
                    equal = false;
                else if ((m_svc_id != nullptr) && (rhs.m_svc_id != nullptr) && (*m_svc_id != *rhs.m_svc_id))
                    equal = false;
                if (m_home_agent_id != rhs.m_home_agent_id)
                    equal = false;
                return equal;
            }
            bool operator!=(const UpdateEvent& rhs) const {
                return !operator==(rhs);
            }

            UpdateEvent& operator = (const UpdateEvent& src) {
                if (this == &src) return *this;
                m_action = src.m_action;
                m_reason = src.m_reason;
                if (m_svc_id)
                    delete m_svc_id;
                if (src.m_svc_id) {
                    m_svc_id = new (ipl::nothrow)comm::broker::cstyle::InstanceID(*(src.m_svc_id));
                } else {
                    m_svc_id = nullptr;
                }
                m_home_agent_id = src.m_home_agent_id;
                return *this;
            }

                void setaction(const comm::broker::cstyle::ServiceAction _value) {
                    m_action = _value;
                }
                comm::broker::cstyle::ServiceAction getaction() const {
                    return m_action;
                }
                void setreason(const comm::broker::cstyle::ServiceReason _value) {
                    m_reason = _value;
                }
                comm::broker::cstyle::ServiceReason getreason() const {
                    return m_reason;
                }
                void setsvc_id(const comm::broker::cstyle::InstanceID* _value) {
                    if (m_svc_id)
                        delete m_svc_id;
                    if (_value) {
                        m_svc_id = new (ipl::nothrow)comm::broker::cstyle::InstanceID(*_value);
                    } else {
                        m_svc_id = nullptr;
                    }
                }
                const comm::broker::cstyle::InstanceID* getsvc_id() const {
                    return m_svc_id;
                }
                    bool svc_idValid() const {
                        return m_svc_id != nullptr;
                    }
                void sethome_agent_id(const uint16_t _value) {
                    m_home_agent_id = _value;
                }
                uint16_t gethome_agent_id() const {
                    return m_home_agent_id;
                }


        comm::broker::cstyle::ServiceAction m_action;
        comm::broker::cstyle::ServiceReason m_reason;
        uint16_t m_home_agent_id;
    private:
        comm::broker::cstyle::InstanceID* m_svc_id;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const comm::broker::cstyle::UpdateEvent& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, comm::broker::cstyle::UpdateEvent &val);
    };

} // cstyle
}//namespace comm
}//namespace broker

#endif// COMM_BROKER_UPDATEEVENT_CSTYLE_HXX
