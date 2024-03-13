/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SIMDATACONFIG_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_SIMDATACONFIG_CSTYLE_HXX

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
struct SimDataConfig;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::SimDataConfig& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimDataConfig &val);
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
    \brief struct al::SimDataConfig.
    */
    struct PROXY_EXPORT SimDataConfig
    {
        public:
            SimDataConfig()
            : m_dataConnectionId()
            , m_apn(nullptr)
            , m_login(nullptr)
            , m_password(nullptr)
            { }

            SimDataConfig (const SimDataConfig& other)
            : m_dataConnectionId()
            , m_apn(nullptr)
            , m_login(nullptr)
            , m_password(nullptr)
            {
              *this = other;
            }

            ~SimDataConfig () {
                if (m_apn) {
                    delete m_apn;
                }
                if (m_login) {
                    delete m_login;
                }
                if (m_password) {
                    delete m_password;
                }
            }
            bool operator==(const SimDataConfig& rhs) const {
                bool equal = true;
                if (m_dataConnectionId != rhs.m_dataConnectionId)
                    equal = false;
                if (m_apn == nullptr && rhs.m_apn != nullptr)
                    equal = false;
                else if (m_apn != nullptr && rhs.m_apn == nullptr)
                    equal = false;
                else if ((m_apn != nullptr) && (rhs.m_apn != nullptr) && (*m_apn != *rhs.m_apn))
                    equal = false;
                if (m_login == nullptr && rhs.m_login != nullptr)
                    equal = false;
                else if (m_login != nullptr && rhs.m_login == nullptr)
                    equal = false;
                else if ((m_login != nullptr) && (rhs.m_login != nullptr) && (*m_login != *rhs.m_login))
                    equal = false;
                if (m_password == nullptr && rhs.m_password != nullptr)
                    equal = false;
                else if (m_password != nullptr && rhs.m_password == nullptr)
                    equal = false;
                else if ((m_password != nullptr) && (rhs.m_password != nullptr) && (*m_password != *rhs.m_password))
                    equal = false;
                return equal;
            }
            bool operator!=(const SimDataConfig& rhs) const {
                return !operator==(rhs);
            }

            SimDataConfig& operator = (const SimDataConfig& src) {
                if (this == &src) return *this;
                m_dataConnectionId = src.m_dataConnectionId;
                if (m_apn)
                    delete m_apn;
                if (src.m_apn) {
                    m_apn = new (ipl::nothrow)ipl::string(*(src.m_apn));
                } else {
                    m_apn = nullptr;
                }
                if (m_login)
                    delete m_login;
                if (src.m_login) {
                    m_login = new (ipl::nothrow)ipl::string(*(src.m_login));
                } else {
                    m_login = nullptr;
                }
                if (m_password)
                    delete m_password;
                if (src.m_password) {
                    m_password = new (ipl::nothrow)ipl::string(*(src.m_password));
                } else {
                    m_password = nullptr;
                }
                return *this;
            }

                void setdataConnectionId(const int32_t _value) {
                    m_dataConnectionId = _value;
                }
                int32_t getdataConnectionId() const {
                    return m_dataConnectionId;
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
                void setlogin(const ipl::string* _value) {
                    if (m_login)
                        delete m_login;
                    if (_value) {
                        m_login = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_login = nullptr;
                    }
                }
                const ipl::string* getlogin() const {
                    return m_login;
                }
                    bool loginValid() const {
                        return m_login != nullptr;
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


        int32_t m_dataConnectionId;
    private:
        ipl::string* m_apn;
        ipl::string* m_login;
        ipl::string* m_password;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::SimDataConfig& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimDataConfig &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_SIMDATACONFIG_CSTYLE_HXX
