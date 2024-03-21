/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_APNCONFIG_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_APNCONFIG_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct ApnConfig;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::ApnConfig& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ApnConfig &val);
}
}

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{

    /**
    \brief struct diagnostic::ApnConfig.
    */
    struct PROXY_EXPORT ApnConfig
    {
        public:
            ApnConfig()
            : m_password(nullptr)
            , m_providerName(nullptr)
            , m_username(nullptr)
            { }

            ApnConfig (const ApnConfig& other)
            : m_password(nullptr)
            , m_providerName(nullptr)
            , m_username(nullptr)
            {
              *this = other;
            }

            ~ApnConfig () {
                if (m_password) {
                    delete m_password;
                }
                if (m_providerName) {
                    delete m_providerName;
                }
                if (m_username) {
                    delete m_username;
                }
            }
            bool operator==(const ApnConfig& rhs) const {
                bool equal = true;
                if (m_password == nullptr && rhs.m_password != nullptr)
                    equal = false;
                else if (m_password != nullptr && rhs.m_password == nullptr)
                    equal = false;
                else if ((m_password != nullptr) && (rhs.m_password != nullptr) && (*m_password != *rhs.m_password))
                    equal = false;
                if (m_providerName == nullptr && rhs.m_providerName != nullptr)
                    equal = false;
                else if (m_providerName != nullptr && rhs.m_providerName == nullptr)
                    equal = false;
                else if ((m_providerName != nullptr) && (rhs.m_providerName != nullptr) && (*m_providerName != *rhs.m_providerName))
                    equal = false;
                if (m_username == nullptr && rhs.m_username != nullptr)
                    equal = false;
                else if (m_username != nullptr && rhs.m_username == nullptr)
                    equal = false;
                else if ((m_username != nullptr) && (rhs.m_username != nullptr) && (*m_username != *rhs.m_username))
                    equal = false;
                return equal;
            }
            bool operator!=(const ApnConfig& rhs) const {
                return !operator==(rhs);
            }

            ApnConfig& operator = (const ApnConfig& src) {
                if (this == &src) return *this;
                if (m_password)
                    delete m_password;
                if (src.m_password) {
                    m_password = new (ipl::nothrow)ipl::string(*(src.m_password));
                } else {
                    m_password = nullptr;
                }
                if (m_providerName)
                    delete m_providerName;
                if (src.m_providerName) {
                    m_providerName = new (ipl::nothrow)ipl::string(*(src.m_providerName));
                } else {
                    m_providerName = nullptr;
                }
                if (m_username)
                    delete m_username;
                if (src.m_username) {
                    m_username = new (ipl::nothrow)ipl::string(*(src.m_username));
                } else {
                    m_username = nullptr;
                }
                return *this;
            }

                void setpassword(const ipl::string* _value) {
                    if (m_password)
                        delete m_password;
                    if (_value) {
                        m_password = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_password = nullptr;
                    }
                }
                const ipl::string* getpassword() const {
                    return m_password;
                }
                    bool passwordValid() const {
                        return m_password != nullptr;
                    }
                void setproviderName(const ipl::string* _value) {
                    if (m_providerName)
                        delete m_providerName;
                    if (_value) {
                        m_providerName = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_providerName = nullptr;
                    }
                }
                const ipl::string* getproviderName() const {
                    return m_providerName;
                }
                    bool providerNameValid() const {
                        return m_providerName != nullptr;
                    }
                void setusername(const ipl::string* _value) {
                    if (m_username)
                        delete m_username;
                    if (_value) {
                        m_username = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_username = nullptr;
                    }
                }
                const ipl::string* getusername() const {
                    return m_username;
                }
                    bool usernameValid() const {
                        return m_username != nullptr;
                    }


    private:
        ipl::string* m_password;
        ipl::string* m_providerName;
        ipl::string* m_username;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ApnConfig& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ApnConfig &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_APNCONFIG_CSTYLE_HXX
