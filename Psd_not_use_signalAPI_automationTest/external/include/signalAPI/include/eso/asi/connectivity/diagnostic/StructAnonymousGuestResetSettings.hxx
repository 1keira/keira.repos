/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ANONYMOUSGUESTRESETSETTINGS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ANONYMOUSGUESTRESETSETTINGS_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::AnonymousGuestResetSettings.
    */
    struct PROXY_EXPORT AnonymousGuestResetSettings
    {
        asi::connectivity::diagnostic::AgrsResetTrigger resetTrigger; // optional=False
        asi::connectivity::diagnostic::AgrsSettingsChoice settingsChoice; // optional=False
        private:
            AnonymousGuestResetSettings()
            :
            resetTrigger(),
            settingsChoice()
            { }
            friend class AnonymousGuestResetSettingsFactory;
            friend class CIFactory<AnonymousGuestResetSettings>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::AnonymousGuestResetSettings> >;
            friend class ipl::vector<AnonymousGuestResetSettings>;
            friend class ipl::allocator<AnonymousGuestResetSettings>;
#endif
    };

    typedef CIPtrArray<AnonymousGuestResetSettings> CIAnonymousGuestResetSettingsArray;

    /** \brief factory for diagnostic::AnonymousGuestResetSettings. */
    class PROXY_EXPORT AnonymousGuestResetSettingsFactory  : CIFactory<AnonymousGuestResetSettings> {
    public:
        static inline CIPtr<AnonymousGuestResetSettings> createAnonymousGuestResetSettings() {
            return CIFactory<AnonymousGuestResetSettings>::createObject();
        }
        static inline void createAnonymousGuestResetSettings(CIPtr<AnonymousGuestResetSettings> & s) {
            CIFactory<AnonymousGuestResetSettings>::createObject(s);
        }
        static inline CIPtr<CIAnonymousGuestResetSettingsArray> createAnonymousGuestResetSettingsArray(size_t size) {
            return CIFactory<AnonymousGuestResetSettings>::createArray(size);
        }
        static inline void createAnonymousGuestResetSettingsArray(CIPtr<CIAnonymousGuestResetSettingsArray>& a, size_t size) {
            CIFactory<AnonymousGuestResetSettings>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ANONYMOUSGUESTRESETSETTINGS_HXX
