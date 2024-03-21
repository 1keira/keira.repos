/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYGROUPMODIFIABILITYSETTINGS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYGROUPMODIFIABILITYSETTINGS_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::PrivacyGroupModifiabilitySettings.
    */
    struct PROXY_EXPORT PrivacyGroupModifiabilitySettings
    {
        bool isDataCollectionModifiable; // optional=False
        bool isLocationDataModifiable; // optional=False
        bool isPersonalizedEvaluationDataModifiable; // optional=False
        bool isRemoteAccessDataModifiable; // optional=False
        bool isResearchDevelopmentDataModifiable; // optional=False
        bool isStatisticsAnalyticsDataModifiable; // optional=False
        bool isUserDataModifiable; // optional=False
        private:
            PrivacyGroupModifiabilitySettings()
            :
            isDataCollectionModifiable(),
            isLocationDataModifiable(),
            isPersonalizedEvaluationDataModifiable(),
            isRemoteAccessDataModifiable(),
            isResearchDevelopmentDataModifiable(),
            isStatisticsAnalyticsDataModifiable(),
            isUserDataModifiable()
            { }
            friend class PrivacyGroupModifiabilitySettingsFactory;
            friend class CIFactory<PrivacyGroupModifiabilitySettings>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::PrivacyGroupModifiabilitySettings> >;
            friend class ipl::vector<PrivacyGroupModifiabilitySettings>;
            friend class ipl::allocator<PrivacyGroupModifiabilitySettings>;
#endif
    };

    typedef CIPtrArray<PrivacyGroupModifiabilitySettings> CIPrivacyGroupModifiabilitySettingsArray;

    /** \brief factory for diagnostic::PrivacyGroupModifiabilitySettings. */
    class PROXY_EXPORT PrivacyGroupModifiabilitySettingsFactory  : CIFactory<PrivacyGroupModifiabilitySettings> {
    public:
        static inline CIPtr<PrivacyGroupModifiabilitySettings> createPrivacyGroupModifiabilitySettings() {
            return CIFactory<PrivacyGroupModifiabilitySettings>::createObject();
        }
        static inline void createPrivacyGroupModifiabilitySettings(CIPtr<PrivacyGroupModifiabilitySettings> & s) {
            CIFactory<PrivacyGroupModifiabilitySettings>::createObject(s);
        }
        static inline CIPtr<CIPrivacyGroupModifiabilitySettingsArray> createPrivacyGroupModifiabilitySettingsArray(size_t size) {
            return CIFactory<PrivacyGroupModifiabilitySettings>::createArray(size);
        }
        static inline void createPrivacyGroupModifiabilitySettingsArray(CIPtr<CIPrivacyGroupModifiabilitySettingsArray>& a, size_t size) {
            CIFactory<PrivacyGroupModifiabilitySettings>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYGROUPMODIFIABILITYSETTINGS_HXX
