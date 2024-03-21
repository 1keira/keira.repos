/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_IPINFO_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_IPINFO_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct IpInfo;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::IpInfo& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::IpInfo &val);
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
    \brief struct al::IpInfo.
    */
    struct PROXY_EXPORT IpInfo
    {
        public:
            IpInfo()
            : m_ip(nullptr)
            , m_mask(nullptr)
            , m_gateway(nullptr)
            , m_pdns(nullptr)
            , m_sdns(nullptr)
            { }

            IpInfo (const IpInfo& other)
            : m_ip(nullptr)
            , m_mask(nullptr)
            , m_gateway(nullptr)
            , m_pdns(nullptr)
            , m_sdns(nullptr)
            {
              *this = other;
            }

            ~IpInfo () {
                if (m_ip) {
                    delete m_ip;
                }
                if (m_mask) {
                    delete m_mask;
                }
                if (m_gateway) {
                    delete m_gateway;
                }
                if (m_pdns) {
                    delete m_pdns;
                }
                if (m_sdns) {
                    delete m_sdns;
                }
            }
            bool operator==(const IpInfo& rhs) const {
                bool equal = true;
                if (m_ip == nullptr && rhs.m_ip != nullptr)
                    equal = false;
                else if (m_ip != nullptr && rhs.m_ip == nullptr)
                    equal = false;
                else if ((m_ip != nullptr) && (rhs.m_ip != nullptr) && (*m_ip != *rhs.m_ip))
                    equal = false;
                if (m_mask == nullptr && rhs.m_mask != nullptr)
                    equal = false;
                else if (m_mask != nullptr && rhs.m_mask == nullptr)
                    equal = false;
                else if ((m_mask != nullptr) && (rhs.m_mask != nullptr) && (*m_mask != *rhs.m_mask))
                    equal = false;
                if (m_gateway == nullptr && rhs.m_gateway != nullptr)
                    equal = false;
                else if (m_gateway != nullptr && rhs.m_gateway == nullptr)
                    equal = false;
                else if ((m_gateway != nullptr) && (rhs.m_gateway != nullptr) && (*m_gateway != *rhs.m_gateway))
                    equal = false;
                if (m_pdns == nullptr && rhs.m_pdns != nullptr)
                    equal = false;
                else if (m_pdns != nullptr && rhs.m_pdns == nullptr)
                    equal = false;
                else if ((m_pdns != nullptr) && (rhs.m_pdns != nullptr) && (*m_pdns != *rhs.m_pdns))
                    equal = false;
                if (m_sdns == nullptr && rhs.m_sdns != nullptr)
                    equal = false;
                else if (m_sdns != nullptr && rhs.m_sdns == nullptr)
                    equal = false;
                else if ((m_sdns != nullptr) && (rhs.m_sdns != nullptr) && (*m_sdns != *rhs.m_sdns))
                    equal = false;
                return equal;
            }
            bool operator!=(const IpInfo& rhs) const {
                return !operator==(rhs);
            }

            IpInfo& operator = (const IpInfo& src) {
                if (this == &src) return *this;
                if (m_ip)
                    delete m_ip;
                if (src.m_ip) {
                    m_ip = new (ipl::nothrow)ipl::string(*(src.m_ip));
                } else {
                    m_ip = nullptr;
                }
                if (m_mask)
                    delete m_mask;
                if (src.m_mask) {
                    m_mask = new (ipl::nothrow)ipl::string(*(src.m_mask));
                } else {
                    m_mask = nullptr;
                }
                if (m_gateway)
                    delete m_gateway;
                if (src.m_gateway) {
                    m_gateway = new (ipl::nothrow)ipl::string(*(src.m_gateway));
                } else {
                    m_gateway = nullptr;
                }
                if (m_pdns)
                    delete m_pdns;
                if (src.m_pdns) {
                    m_pdns = new (ipl::nothrow)ipl::string(*(src.m_pdns));
                } else {
                    m_pdns = nullptr;
                }
                if (m_sdns)
                    delete m_sdns;
                if (src.m_sdns) {
                    m_sdns = new (ipl::nothrow)ipl::string(*(src.m_sdns));
                } else {
                    m_sdns = nullptr;
                }
                return *this;
            }

                void setip(const ipl::string* _value) {
                    if (m_ip)
                        delete m_ip;
                    if (_value) {
                        m_ip = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_ip = nullptr;
                    }
                }
                const ipl::string* getip() const {
                    return m_ip;
                }
                    bool ipValid() const {
                        return m_ip != nullptr;
                    }
                void setmask(const ipl::string* _value) {
                    if (m_mask)
                        delete m_mask;
                    if (_value) {
                        m_mask = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_mask = nullptr;
                    }
                }
                const ipl::string* getmask() const {
                    return m_mask;
                }
                    bool maskValid() const {
                        return m_mask != nullptr;
                    }
                void setgateway(const ipl::string* _value) {
                    if (m_gateway)
                        delete m_gateway;
                    if (_value) {
                        m_gateway = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_gateway = nullptr;
                    }
                }
                const ipl::string* getgateway() const {
                    return m_gateway;
                }
                    bool gatewayValid() const {
                        return m_gateway != nullptr;
                    }
                void setpdns(const ipl::string* _value) {
                    if (m_pdns)
                        delete m_pdns;
                    if (_value) {
                        m_pdns = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_pdns = nullptr;
                    }
                }
                const ipl::string* getpdns() const {
                    return m_pdns;
                }
                    bool pdnsValid() const {
                        return m_pdns != nullptr;
                    }
                void setsdns(const ipl::string* _value) {
                    if (m_sdns)
                        delete m_sdns;
                    if (_value) {
                        m_sdns = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_sdns = nullptr;
                    }
                }
                const ipl::string* getsdns() const {
                    return m_sdns;
                }
                    bool sdnsValid() const {
                        return m_sdns != nullptr;
                    }


    private:
        ipl::string* m_ip;
        ipl::string* m_mask;
        ipl::string* m_gateway;
        ipl::string* m_pdns;
        ipl::string* m_sdns;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::IpInfo& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::IpInfo &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_IPINFO_CSTYLE_HXX
