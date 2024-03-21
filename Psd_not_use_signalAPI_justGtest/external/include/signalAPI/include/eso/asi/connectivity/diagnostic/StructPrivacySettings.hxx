/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGS_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/StructPrivacySettingsUser.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::PrivacySettings.
    */
    struct PROXY_EXPORT PrivacySettings
    {
        CIPtr< asi::connectivity::diagnostic::PrivacySettingsUser > anonymousGuestUser; // optional=True
        CIPtr< asi::connectivity::diagnostic::PrivacySettingsUser > offlineGuestUser; // optional=True
        CIPtr< asi::connectivity::diagnostic::PrivacySettingsUser > onlineGuestUser; // optional=True
        CIPtr< asi::connectivity::diagnostic::PrivacySettingsUser > primaryUser; // optional=True
        CIPtr< asi::connectivity::diagnostic::PrivacySettingsUser > secondaryUser; // optional=True
        asi::connectivity::diagnostic::PrivacySimMode simMode; // optional=False
        private:
            PrivacySettings()
            :
            anonymousGuestUser(),
            offlineGuestUser(),
            onlineGuestUser(),
            primaryUser(),
            secondaryUser(),
            simMode()
            { }
            friend class PrivacySettingsFactory;
            friend class CIFactory<PrivacySettings>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::PrivacySettings> >;
            friend class ipl::vector<PrivacySettings>;
            friend class ipl::allocator<PrivacySettings>;
#endif
    };

    typedef CIPtrArray<PrivacySettings> CIPrivacySettingsArray;

    /** \brief factory for diagnostic::PrivacySettings. */
    class PROXY_EXPORT PrivacySettingsFactory  : CIFactory<PrivacySettings> {
    public:
        static inline CIPtr<PrivacySettings> createPrivacySettings() {
            return CIFactory<PrivacySettings>::createObject();
        }
        static inline void createPrivacySettings(CIPtr<PrivacySettings> & s) {
            CIFactory<PrivacySettings>::createObject(s);
        }
        static inline CIPtr<CIPrivacySettingsArray> createPrivacySettingsArray(size_t size) {
            return CIFactory<PrivacySettings>::createArray(size);
        }
        static inline void createPrivacySettingsArray(CIPtr<CIPrivacySettingsArray>& a, size_t size) {
            CIFactory<PrivacySettings>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_PRIVACYSETTINGS_HXX
