/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGSUSER_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGSUSER_HXX

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
    \brief struct diagnostic::PrivacySettingsUser.
    */
    struct PROXY_EXPORT PrivacySettingsUser
    {
        bool isDataCollectionEnabled; // optional=False
        bool isLocationDataEnabled; // optional=False
        bool isPersonalizedEvaluationDataEnabled; // optional=False
        bool isRemoteAccessDataEnabled; // optional=False
        bool isResearchDevelopmentDataEnabled; // optional=False
        bool isStatisticsAnalyticsDataEnabled; // optional=False
        bool isUserDataEnabled; // optional=False
        private:
            PrivacySettingsUser()
            :
            isDataCollectionEnabled(),
            isLocationDataEnabled(),
            isPersonalizedEvaluationDataEnabled(),
            isRemoteAccessDataEnabled(),
            isResearchDevelopmentDataEnabled(),
            isStatisticsAnalyticsDataEnabled(),
            isUserDataEnabled()
            { }
            friend class PrivacySettingsUserFactory;
            friend class CIFactory<PrivacySettingsUser>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::PrivacySettingsUser> >;
            friend class ipl::vector<PrivacySettingsUser>;
            friend class ipl::allocator<PrivacySettingsUser>;
#endif
    };

    typedef CIPtrArray<PrivacySettingsUser> CIPrivacySettingsUserArray;

    /** \brief factory for diagnostic::PrivacySettingsUser. */
    class PROXY_EXPORT PrivacySettingsUserFactory  : CIFactory<PrivacySettingsUser> {
    public:
        static inline CIPtr<PrivacySettingsUser> createPrivacySettingsUser() {
            return CIFactory<PrivacySettingsUser>::createObject();
        }
        static inline void createPrivacySettingsUser(CIPtr<PrivacySettingsUser> & s) {
            CIFactory<PrivacySettingsUser>::createObject(s);
        }
        static inline CIPtr<CIPrivacySettingsUserArray> createPrivacySettingsUserArray(size_t size) {
            return CIFactory<PrivacySettingsUser>::createArray(size);
        }
        static inline void createPrivacySettingsUserArray(CIPtr<CIPrivacySettingsUserArray>& a, size_t size) {
            CIFactory<PrivacySettingsUser>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGSUSER_HXX
