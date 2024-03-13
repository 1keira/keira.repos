/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGSUSER_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGSUSER_CSTYLE_HXX

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
struct PrivacySettingsUser;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacySettingsUser &val);
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
    \brief struct diagnostic::PrivacySettingsUser.
    */
    struct PROXY_EXPORT PrivacySettingsUser
    {
        public:
            PrivacySettingsUser()
            : m_isDataCollectionEnabled()
            , m_isLocationDataEnabled()
            , m_isPersonalizedEvaluationDataEnabled()
            , m_isRemoteAccessDataEnabled()
            , m_isResearchDevelopmentDataEnabled()
            , m_isStatisticsAnalyticsDataEnabled()
            , m_isUserDataEnabled()
            { }

            PrivacySettingsUser (const PrivacySettingsUser& other)
            : m_isDataCollectionEnabled()
            , m_isLocationDataEnabled()
            , m_isPersonalizedEvaluationDataEnabled()
            , m_isRemoteAccessDataEnabled()
            , m_isResearchDevelopmentDataEnabled()
            , m_isStatisticsAnalyticsDataEnabled()
            , m_isUserDataEnabled()
            {
              *this = other;
            }

            ~PrivacySettingsUser () {
            }
            bool operator==(const PrivacySettingsUser& rhs) const {
                bool equal = true;
                if (m_isDataCollectionEnabled != rhs.m_isDataCollectionEnabled)
                    equal = false;
                if (m_isLocationDataEnabled != rhs.m_isLocationDataEnabled)
                    equal = false;
                if (m_isPersonalizedEvaluationDataEnabled != rhs.m_isPersonalizedEvaluationDataEnabled)
                    equal = false;
                if (m_isRemoteAccessDataEnabled != rhs.m_isRemoteAccessDataEnabled)
                    equal = false;
                if (m_isResearchDevelopmentDataEnabled != rhs.m_isResearchDevelopmentDataEnabled)
                    equal = false;
                if (m_isStatisticsAnalyticsDataEnabled != rhs.m_isStatisticsAnalyticsDataEnabled)
                    equal = false;
                if (m_isUserDataEnabled != rhs.m_isUserDataEnabled)
                    equal = false;
                return equal;
            }
            bool operator!=(const PrivacySettingsUser& rhs) const {
                return !operator==(rhs);
            }

            PrivacySettingsUser& operator = (const PrivacySettingsUser& src) {
                if (this == &src) return *this;
                m_isDataCollectionEnabled = src.m_isDataCollectionEnabled;
                m_isLocationDataEnabled = src.m_isLocationDataEnabled;
                m_isPersonalizedEvaluationDataEnabled = src.m_isPersonalizedEvaluationDataEnabled;
                m_isRemoteAccessDataEnabled = src.m_isRemoteAccessDataEnabled;
                m_isResearchDevelopmentDataEnabled = src.m_isResearchDevelopmentDataEnabled;
                m_isStatisticsAnalyticsDataEnabled = src.m_isStatisticsAnalyticsDataEnabled;
                m_isUserDataEnabled = src.m_isUserDataEnabled;
                return *this;
            }

                void setisDataCollectionEnabled(const bool _value) {
                    m_isDataCollectionEnabled = _value;
                }
                bool getisDataCollectionEnabled() const {
                    return m_isDataCollectionEnabled;
                }
                void setisLocationDataEnabled(const bool _value) {
                    m_isLocationDataEnabled = _value;
                }
                bool getisLocationDataEnabled() const {
                    return m_isLocationDataEnabled;
                }
                void setisPersonalizedEvaluationDataEnabled(const bool _value) {
                    m_isPersonalizedEvaluationDataEnabled = _value;
                }
                bool getisPersonalizedEvaluationDataEnabled() const {
                    return m_isPersonalizedEvaluationDataEnabled;
                }
                void setisRemoteAccessDataEnabled(const bool _value) {
                    m_isRemoteAccessDataEnabled = _value;
                }
                bool getisRemoteAccessDataEnabled() const {
                    return m_isRemoteAccessDataEnabled;
                }
                void setisResearchDevelopmentDataEnabled(const bool _value) {
                    m_isResearchDevelopmentDataEnabled = _value;
                }
                bool getisResearchDevelopmentDataEnabled() const {
                    return m_isResearchDevelopmentDataEnabled;
                }
                void setisStatisticsAnalyticsDataEnabled(const bool _value) {
                    m_isStatisticsAnalyticsDataEnabled = _value;
                }
                bool getisStatisticsAnalyticsDataEnabled() const {
                    return m_isStatisticsAnalyticsDataEnabled;
                }
                void setisUserDataEnabled(const bool _value) {
                    m_isUserDataEnabled = _value;
                }
                bool getisUserDataEnabled() const {
                    return m_isUserDataEnabled;
                }


        bool m_isDataCollectionEnabled;
        bool m_isLocationDataEnabled;
        bool m_isPersonalizedEvaluationDataEnabled;
        bool m_isRemoteAccessDataEnabled;
        bool m_isResearchDevelopmentDataEnabled;
        bool m_isStatisticsAnalyticsDataEnabled;
        bool m_isUserDataEnabled;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::PrivacySettingsUser& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacySettingsUser &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGSUSER_CSTYLE_HXX
