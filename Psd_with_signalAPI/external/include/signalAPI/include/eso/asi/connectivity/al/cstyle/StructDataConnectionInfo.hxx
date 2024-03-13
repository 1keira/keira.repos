/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_DATACONNECTIONINFO_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_DATACONNECTIONINFO_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/StructIpInfo.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct DataConnectionInfo;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::DataConnectionInfo& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::DataConnectionInfo &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{

    /**
    \brief struct al::DataConnectionInfo.
    */
    struct PROXY_EXPORT DataConnectionInfo
    {
        public:
            DataConnectionInfo()
            : m_dataConnectionId()
            , m_state()
            , m_net_interface(nullptr)
            , m_apn(nullptr)
            , m_ipv4Info(nullptr)
            , m_ipv6Info(nullptr)
            { }

            DataConnectionInfo (const DataConnectionInfo& other)
            : m_dataConnectionId()
            , m_state()
            , m_net_interface(nullptr)
            , m_apn(nullptr)
            , m_ipv4Info(nullptr)
            , m_ipv6Info(nullptr)
            {
              *this = other;
            }

            ~DataConnectionInfo () {
                if (m_net_interface) {
                    delete m_net_interface;
                }
                if (m_apn) {
                    delete m_apn;
                }
                if (m_ipv4Info) {
                    delete m_ipv4Info;
                }
                if (m_ipv6Info) {
                    delete m_ipv6Info;
                }
            }
            bool operator==(const DataConnectionInfo& rhs) const {
                bool equal = true;
                if (m_dataConnectionId != rhs.m_dataConnectionId)
                    equal = false;
                if (m_state != rhs.m_state)
                    equal = false;
                if (m_net_interface == nullptr && rhs.m_net_interface != nullptr)
                    equal = false;
                else if (m_net_interface != nullptr && rhs.m_net_interface == nullptr)
                    equal = false;
                else if ((m_net_interface != nullptr) && (rhs.m_net_interface != nullptr) && (*m_net_interface != *rhs.m_net_interface))
                    equal = false;
                if (m_apn == nullptr && rhs.m_apn != nullptr)
                    equal = false;
                else if (m_apn != nullptr && rhs.m_apn == nullptr)
                    equal = false;
                else if ((m_apn != nullptr) && (rhs.m_apn != nullptr) && (*m_apn != *rhs.m_apn))
                    equal = false;
                if (m_ipv4Info == nullptr && rhs.m_ipv4Info != nullptr)
                    equal = false;
                else if (m_ipv4Info != nullptr && rhs.m_ipv4Info == nullptr)
                    equal = false;
                else if ((m_ipv4Info != nullptr) && (rhs.m_ipv4Info != nullptr) && (*m_ipv4Info != *rhs.m_ipv4Info))
                    equal = false;
                if (m_ipv6Info == nullptr && rhs.m_ipv6Info != nullptr)
                    equal = false;
                else if (m_ipv6Info != nullptr && rhs.m_ipv6Info == nullptr)
                    equal = false;
                else if ((m_ipv6Info != nullptr) && (rhs.m_ipv6Info != nullptr) && (*m_ipv6Info != *rhs.m_ipv6Info))
                    equal = false;
                return equal;
            }
            bool operator!=(const DataConnectionInfo& rhs) const {
                return !operator==(rhs);
            }

            DataConnectionInfo& operator = (const DataConnectionInfo& src) {
                if (this == &src) return *this;
                m_dataConnectionId = src.m_dataConnectionId;
                m_state = src.m_state;
                if (m_net_interface)
                    delete m_net_interface;
                if (src.m_net_interface) {
                    m_net_interface = new (ipl::nothrow)ipl::string(*(src.m_net_interface));
                } else {
                    m_net_interface = nullptr;
                }
                if (m_apn)
                    delete m_apn;
                if (src.m_apn) {
                    m_apn = new (ipl::nothrow)ipl::string(*(src.m_apn));
                } else {
                    m_apn = nullptr;
                }
                if (m_ipv4Info)
                    delete m_ipv4Info;
                if (src.m_ipv4Info) {
                    m_ipv4Info = new (ipl::nothrow)asi::connectivity::al::cstyle::IpInfo(*(src.m_ipv4Info));
                } else {
                    m_ipv4Info = nullptr;
                }
                if (m_ipv6Info)
                    delete m_ipv6Info;
                if (src.m_ipv6Info) {
                    m_ipv6Info = new (ipl::nothrow)asi::connectivity::al::cstyle::IpInfo(*(src.m_ipv6Info));
                } else {
                    m_ipv6Info = nullptr;
                }
                return *this;
            }

                void setdataConnectionId(const int32_t _value) {
                    m_dataConnectionId = _value;
                }
                int32_t getdataConnectionId() const {
                    return m_dataConnectionId;
                }
                void setstate(const asi::connectivity::al::cstyle::DataConnectionState _value) {
                    m_state = _value;
                }
                asi::connectivity::al::cstyle::DataConnectionState getstate() const {
                    return m_state;
                }
                void setnet_interface(const ipl::string* _value) {
                    if (m_net_interface)
                        delete m_net_interface;
                    if (_value) {
                        m_net_interface = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_net_interface = nullptr;
                    }
                }
                const ipl::string* getnet_interface() const {
                    return m_net_interface;
                }
                    bool net_interfaceValid() const {
                        return m_net_interface != nullptr;
                    }
                void setapn(const ipl::string* _value) {
                    if (m_apn)
                        delete m_apn;
                    if (_value) {
                        m_apn = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_apn = nullptr;
                    }
                }
                const ipl::string* getapn() const {
                    return m_apn;
                }
                    bool apnValid() const {
                        return m_apn != nullptr;
                    }
                void setipv4Info(const asi::connectivity::al::cstyle::IpInfo* _value) {
                    if (m_ipv4Info)
                        delete m_ipv4Info;
                    if (_value) {
                        m_ipv4Info = new (ipl::nothrow)asi::connectivity::al::cstyle::IpInfo(*_value);
                    } else {
                        m_ipv4Info = nullptr;
                    }
                }
                const asi::connectivity::al::cstyle::IpInfo* getipv4Info() const {
                    return m_ipv4Info;
                }
                    bool ipv4InfoValid() const {
                        return m_ipv4Info != nullptr;
                    }
                void setipv6Info(const asi::connectivity::al::cstyle::IpInfo* _value) {
                    if (m_ipv6Info)
                        delete m_ipv6Info;
                    if (_value) {
                        m_ipv6Info = new (ipl::nothrow)asi::connectivity::al::cstyle::IpInfo(*_value);
                    } else {
                        m_ipv6Info = nullptr;
                    }
                }
                const asi::connectivity::al::cstyle::IpInfo* getipv6Info() const {
                    return m_ipv6Info;
                }
                    bool ipv6InfoValid() const {
                        return m_ipv6Info != nullptr;
                    }


        int32_t m_dataConnectionId;
        asi::connectivity::al::cstyle::DataConnectionState m_state;
    private:
        ipl::string* m_net_interface;
        ipl::string* m_apn;
        asi::connectivity::al::cstyle::IpInfo* m_ipv4Info;
        asi::connectivity::al::cstyle::IpInfo* m_ipv6Info;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::DataConnectionInfo& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::DataConnectionInfo &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_DATACONNECTIONINFO_CSTYLE_HXX
