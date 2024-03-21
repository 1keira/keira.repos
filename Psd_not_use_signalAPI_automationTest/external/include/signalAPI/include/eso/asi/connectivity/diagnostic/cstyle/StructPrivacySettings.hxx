/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGS_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructPrivacySettingsUser.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct PrivacySettings;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::PrivacySettings& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacySettings &val);
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
    \brief struct diagnostic::PrivacySettings.
    */
    struct PROXY_EXPORT PrivacySettings
    {
        public:
            PrivacySettings()
            : m_simMode()
            , m_anonymousGuestUser(nullptr)
            , m_offlineGuestUser(nullptr)
            , m_onlineGuestUser(nullptr)
            , m_primaryUser(nullptr)
            , m_secondaryUser(nullptr)
            { }

            PrivacySettings (const PrivacySettings& other)
            : m_simMode()
            , m_anonymousGuestUser(nullptr)
            , m_offlineGuestUser(nullptr)
            , m_onlineGuestUser(nullptr)
            , m_primaryUser(nullptr)
            , m_secondaryUser(nullptr)
            {
              *this = other;
            }

            ~PrivacySettings () {
                if (m_anonymousGuestUser) {
                    delete m_anonymousGuestUser;
                }
                if (m_offlineGuestUser) {
                    delete m_offlineGuestUser;
                }
                if (m_onlineGuestUser) {
                    delete m_onlineGuestUser;
                }
                if (m_primaryUser) {
                    delete m_primaryUser;
                }
                if (m_secondaryUser) {
                    delete m_secondaryUser;
                }
            }
            bool operator==(const PrivacySettings& rhs) const {
                bool equal = true;
                if (m_anonymousGuestUser == nullptr && rhs.m_anonymousGuestUser != nullptr)
                    equal = false;
                else if (m_anonymousGuestUser != nullptr && rhs.m_anonymousGuestUser == nullptr)
                    equal = false;
                else if ((m_anonymousGuestUser != nullptr) && (rhs.m_anonymousGuestUser != nullptr) && (*m_anonymousGuestUser != *rhs.m_anonymousGuestUser))
                    equal = false;
                if (m_offlineGuestUser == nullptr && rhs.m_offlineGuestUser != nullptr)
                    equal = false;
                else if (m_offlineGuestUser != nullptr && rhs.m_offlineGuestUser == nullptr)
                    equal = false;
                else if ((m_offlineGuestUser != nullptr) && (rhs.m_offlineGuestUser != nullptr) && (*m_offlineGuestUser != *rhs.m_offlineGuestUser))
                    equal = false;
                if (m_onlineGuestUser == nullptr && rhs.m_onlineGuestUser != nullptr)
                    equal = false;
                else if (m_onlineGuestUser != nullptr && rhs.m_onlineGuestUser == nullptr)
                    equal = false;
                else if ((m_onlineGuestUser != nullptr) && (rhs.m_onlineGuestUser != nullptr) && (*m_onlineGuestUser != *rhs.m_onlineGuestUser))
                    equal = false;
                if (m_primaryUser == nullptr && rhs.m_primaryUser != nullptr)
                    equal = false;
                else if (m_primaryUser != nullptr && rhs.m_primaryUser == nullptr)
                    equal = false;
                else if ((m_primaryUser != nullptr) && (rhs.m_primaryUser != nullptr) && (*m_primaryUser != *rhs.m_primaryUser))
                    equal = false;
                if (m_secondaryUser == nullptr && rhs.m_secondaryUser != nullptr)
                    equal = false;
                else if (m_secondaryUser != nullptr && rhs.m_secondaryUser == nullptr)
                    equal = false;
                else if ((m_secondaryUser != nullptr) && (rhs.m_secondaryUser != nullptr) && (*m_secondaryUser != *rhs.m_secondaryUser))
                    equal = false;
                if (m_simMode != rhs.m_simMode)
                    equal = false;
                return equal;
            }
            bool operator!=(const PrivacySettings& rhs) const {
                return !operator==(rhs);
            }

            PrivacySettings& operator = (const PrivacySettings& src) {
                if (this == &src) return *this;
                if (m_anonymousGuestUser)
                    delete m_anonymousGuestUser;
                if (src.m_anonymousGuestUser) {
                    m_anonymousGuestUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*(src.m_anonymousGuestUser));
                } else {
                    m_anonymousGuestUser = nullptr;
                }
                if (m_offlineGuestUser)
                    delete m_offlineGuestUser;
                if (src.m_offlineGuestUser) {
                    m_offlineGuestUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*(src.m_offlineGuestUser));
                } else {
                    m_offlineGuestUser = nullptr;
                }
                if (m_onlineGuestUser)
                    delete m_onlineGuestUser;
                if (src.m_onlineGuestUser) {
                    m_onlineGuestUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*(src.m_onlineGuestUser));
                } else {
                    m_onlineGuestUser = nullptr;
                }
                if (m_primaryUser)
                    delete m_primaryUser;
                if (src.m_primaryUser) {
                    m_primaryUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*(src.m_primaryUser));
                } else {
                    m_primaryUser = nullptr;
                }
                if (m_secondaryUser)
                    delete m_secondaryUser;
                if (src.m_secondaryUser) {
                    m_secondaryUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*(src.m_secondaryUser));
                } else {
                    m_secondaryUser = nullptr;
                }
                m_simMode = src.m_simMode;
                return *this;
            }

                void setanonymousGuestUser(const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* _value) {
                    if (m_anonymousGuestUser)
                        delete m_anonymousGuestUser;
                    if (_value) {
                        m_anonymousGuestUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*_value);
                    } else {
                        m_anonymousGuestUser = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* getanonymousGuestUser() const {
                    return m_anonymousGuestUser;
                }
                    bool anonymousGuestUserValid() const {
                        return m_anonymousGuestUser != nullptr;
                    }
                void setofflineGuestUser(const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* _value) {
                    if (m_offlineGuestUser)
                        delete m_offlineGuestUser;
                    if (_value) {
                        m_offlineGuestUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*_value);
                    } else {
                        m_offlineGuestUser = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* getofflineGuestUser() const {
                    return m_offlineGuestUser;
                }
                    bool offlineGuestUserValid() const {
                        return m_offlineGuestUser != nullptr;
                    }
                void setonlineGuestUser(const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* _value) {
                    if (m_onlineGuestUser)
                        delete m_onlineGuestUser;
                    if (_value) {
                        m_onlineGuestUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*_value);
                    } else {
                        m_onlineGuestUser = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* getonlineGuestUser() const {
                    return m_onlineGuestUser;
                }
                    bool onlineGuestUserValid() const {
                        return m_onlineGuestUser != nullptr;
                    }
                void setprimaryUser(const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* _value) {
                    if (m_primaryUser)
                        delete m_primaryUser;
                    if (_value) {
                        m_primaryUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*_value);
                    } else {
                        m_primaryUser = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* getprimaryUser() const {
                    return m_primaryUser;
                }
                    bool primaryUserValid() const {
                        return m_primaryUser != nullptr;
                    }
                void setsecondaryUser(const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* _value) {
                    if (m_secondaryUser)
                        delete m_secondaryUser;
                    if (_value) {
                        m_secondaryUser = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::PrivacySettingsUser(*_value);
                    } else {
                        m_secondaryUser = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* getsecondaryUser() const {
                    return m_secondaryUser;
                }
                    bool secondaryUserValid() const {
                        return m_secondaryUser != nullptr;
                    }
                void setsimMode(const asi::connectivity::diagnostic::cstyle::PrivacySimMode _value) {
                    m_simMode = _value;
                }
                asi::connectivity::diagnostic::cstyle::PrivacySimMode getsimMode() const {
                    return m_simMode;
                }


        asi::connectivity::diagnostic::cstyle::PrivacySimMode m_simMode;
    private:
        asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* m_anonymousGuestUser;
        asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* m_offlineGuestUser;
        asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* m_onlineGuestUser;
        asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* m_primaryUser;
        asi::connectivity::diagnostic::cstyle::PrivacySettingsUser* m_secondaryUser;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::PrivacySettings& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacySettings &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGS_CSTYLE_HXX
