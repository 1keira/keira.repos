/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYGROUPMODIFIABILITYSETTINGS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYGROUPMODIFIABILITYSETTINGS_CSTYLE_HXX

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
struct PrivacyGroupModifiabilitySettings;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings &val);
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
    \brief struct diagnostic::PrivacyGroupModifiabilitySettings.
    */
    struct PROXY_EXPORT PrivacyGroupModifiabilitySettings
    {
        public:
            PrivacyGroupModifiabilitySettings()
            : m_isDataCollectionModifiable()
            , m_isLocationDataModifiable()
            , m_isPersonalizedEvaluationDataModifiable()
            , m_isRemoteAccessDataModifiable()
            , m_isResearchDevelopmentDataModifiable()
            , m_isStatisticsAnalyticsDataModifiable()
            , m_isUserDataModifiable()
            { }

            PrivacyGroupModifiabilitySettings (const PrivacyGroupModifiabilitySettings& other)
            : m_isDataCollectionModifiable()
            , m_isLocationDataModifiable()
            , m_isPersonalizedEvaluationDataModifiable()
            , m_isRemoteAccessDataModifiable()
            , m_isResearchDevelopmentDataModifiable()
            , m_isStatisticsAnalyticsDataModifiable()
            , m_isUserDataModifiable()
            {
              *this = other;
            }

            ~PrivacyGroupModifiabilitySettings () {
            }
            bool operator==(const PrivacyGroupModifiabilitySettings& rhs) const {
                bool equal = true;
                if (m_isDataCollectionModifiable != rhs.m_isDataCollectionModifiable)
                    equal = false;
                if (m_isLocationDataModifiable != rhs.m_isLocationDataModifiable)
                    equal = false;
                if (m_isPersonalizedEvaluationDataModifiable != rhs.m_isPersonalizedEvaluationDataModifiable)
                    equal = false;
                if (m_isRemoteAccessDataModifiable != rhs.m_isRemoteAccessDataModifiable)
                    equal = false;
                if (m_isResearchDevelopmentDataModifiable != rhs.m_isResearchDevelopmentDataModifiable)
                    equal = false;
                if (m_isStatisticsAnalyticsDataModifiable != rhs.m_isStatisticsAnalyticsDataModifiable)
                    equal = false;
                if (m_isUserDataModifiable != rhs.m_isUserDataModifiable)
                    equal = false;
                return equal;
            }
            bool operator!=(const PrivacyGroupModifiabilitySettings& rhs) const {
                return !operator==(rhs);
            }

            PrivacyGroupModifiabilitySettings& operator = (const PrivacyGroupModifiabilitySettings& src) {
                if (this == &src) return *this;
                m_isDataCollectionModifiable = src.m_isDataCollectionModifiable;
                m_isLocationDataModifiable = src.m_isLocationDataModifiable;
                m_isPersonalizedEvaluationDataModifiable = src.m_isPersonalizedEvaluationDataModifiable;
                m_isRemoteAccessDataModifiable = src.m_isRemoteAccessDataModifiable;
                m_isResearchDevelopmentDataModifiable = src.m_isResearchDevelopmentDataModifiable;
                m_isStatisticsAnalyticsDataModifiable = src.m_isStatisticsAnalyticsDataModifiable;
                m_isUserDataModifiable = src.m_isUserDataModifiable;
                return *this;
            }

                void setisDataCollectionModifiable(const bool _value) {
                    m_isDataCollectionModifiable = _value;
                }
                bool getisDataCollectionModifiable() const {
                    return m_isDataCollectionModifiable;
                }
                void setisLocationDataModifiable(const bool _value) {
                    m_isLocationDataModifiable = _value;
                }
                bool getisLocationDataModifiable() const {
                    return m_isLocationDataModifiable;
                }
                void setisPersonalizedEvaluationDataModifiable(const bool _value) {
                    m_isPersonalizedEvaluationDataModifiable = _value;
                }
                bool getisPersonalizedEvaluationDataModifiable() const {
                    return m_isPersonalizedEvaluationDataModifiable;
                }
                void setisRemoteAccessDataModifiable(const bool _value) {
                    m_isRemoteAccessDataModifiable = _value;
                }
                bool getisRemoteAccessDataModifiable() const {
                    return m_isRemoteAccessDataModifiable;
                }
                void setisResearchDevelopmentDataModifiable(const bool _value) {
                    m_isResearchDevelopmentDataModifiable = _value;
                }
                bool getisResearchDevelopmentDataModifiable() const {
                    return m_isResearchDevelopmentDataModifiable;
                }
                void setisStatisticsAnalyticsDataModifiable(const bool _value) {
                    m_isStatisticsAnalyticsDataModifiable = _value;
                }
                bool getisStatisticsAnalyticsDataModifiable() const {
                    return m_isStatisticsAnalyticsDataModifiable;
                }
                void setisUserDataModifiable(const bool _value) {
                    m_isUserDataModifiable = _value;
                }
                bool getisUserDataModifiable() const {
                    return m_isUserDataModifiable;
                }


        bool m_isDataCollectionModifiable;
        bool m_isLocationDataModifiable;
        bool m_isPersonalizedEvaluationDataModifiable;
        bool m_isRemoteAccessDataModifiable;
        bool m_isResearchDevelopmentDataModifiable;
        bool m_isStatisticsAnalyticsDataModifiable;
        bool m_isUserDataModifiable;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::PrivacyGroupModifiabilitySettings &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYGROUPMODIFIABILITYSETTINGS_CSTYLE_HXX
