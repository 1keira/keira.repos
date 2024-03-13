/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef COMM_BROKER_INSTANCEID_CSTYLE_HXX
#define COMM_BROKER_INSTANCEID_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <comm/broker/cstyle/StructUUID844412Blob.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace comm
{
namespace broker
{
namespace  cstyle
{
struct InstanceID;
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const comm::broker::cstyle::InstanceID& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, comm::broker::cstyle::InstanceID &val);
}
}

namespace comm
{
namespace broker
{
namespace  cstyle
{

    /**
         
    \brief Instance id with interface identity key.
    
    */
    struct PROXY_EXPORT InstanceID
    {
        public:
            InstanceID()
            : m_handle()
            , m_id(nullptr)
            , m_key(nullptr)
            { }

            InstanceID (const InstanceID& other)
            : m_handle()
            , m_id(nullptr)
            , m_key(nullptr)
            {
              *this = other;
            }

            ~InstanceID () {
                if (m_id) {
                    delete m_id;
                }
                if (m_key) {
                    delete m_key;
                }
            }
            bool operator==(const InstanceID& rhs) const {
                bool equal = true;
                if (m_id == nullptr && rhs.m_id != nullptr)
                    equal = false;
                else if (m_id != nullptr && rhs.m_id == nullptr)
                    equal = false;
                else if ((m_id != nullptr) && (rhs.m_id != nullptr) && (*m_id != *rhs.m_id))
                    equal = false;
                if (m_handle != rhs.m_handle)
                    equal = false;
                if (m_key == nullptr && rhs.m_key != nullptr)
                    equal = false;
                else if (m_key != nullptr && rhs.m_key == nullptr)
                    equal = false;
                else if ((m_key != nullptr) && (rhs.m_key != nullptr) && (*m_key != *rhs.m_key))
                    equal = false;
                return equal;
            }
            bool operator!=(const InstanceID& rhs) const {
                return !operator==(rhs);
            }

            InstanceID& operator = (const InstanceID& src) {
                if (this == &src) return *this;
                if (m_id)
                    delete m_id;
                if (src.m_id) {
                    m_id = new (ipl::nothrow)comm::broker::cstyle::UUID844412Blob(*(src.m_id));
                } else {
                    m_id = nullptr;
                }
                m_handle = src.m_handle;
                if (m_key)
                    delete m_key;
                if (src.m_key) {
                    m_key = new (ipl::nothrow)comm::broker::cstyle::UUID844412Blob(*(src.m_key));
                } else {
                    m_key = nullptr;
                }
                return *this;
            }

                void setid(const comm::broker::cstyle::UUID844412Blob* _value) {
                    if (m_id)
                        delete m_id;
                    if (_value) {
                        m_id = new (ipl::nothrow)comm::broker::cstyle::UUID844412Blob(*_value);
                    } else {
                        m_id = nullptr;
                    }
                }
                const comm::broker::cstyle::UUID844412Blob* getid() const {
                    return m_id;
                }
                    bool idValid() const {
                        return m_id != nullptr;
                    }
                void sethandle(const uint32_t _value) {
                    m_handle = _value;
                }
                uint32_t gethandle() const {
                    return m_handle;
                }
                void setkey(const comm::broker::cstyle::UUID844412Blob* _value) {
                    if (m_key)
                        delete m_key;
                    if (_value) {
                        m_key = new (ipl::nothrow)comm::broker::cstyle::UUID844412Blob(*_value);
                    } else {
                        m_key = nullptr;
                    }
                }
                const comm::broker::cstyle::UUID844412Blob* getkey() const {
                    return m_key;
                }
                    bool keyValid() const {
                        return m_key != nullptr;
                    }


        uint32_t m_handle;
    private:
        comm::broker::cstyle::UUID844412Blob* m_id;
        comm::broker::cstyle::UUID844412Blob* m_key;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const comm::broker::cstyle::InstanceID& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, comm::broker::cstyle::InstanceID &val);
    };

} // cstyle
}//namespace comm
}//namespace broker

#endif// COMM_BROKER_INSTANCEID_CSTYLE_HXX
