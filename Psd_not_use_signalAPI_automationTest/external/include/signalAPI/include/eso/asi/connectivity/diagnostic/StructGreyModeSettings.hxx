/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_GREYMODESETTINGS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_GREYMODESETTINGS_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
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
    \brief struct diagnostic::GreyModeSettings.
    */
    struct PROXY_EXPORT GreyModeSettings
    {
        asi::connectivity::diagnostic::GmActiveUserTakeover activeUserTakeover; // optional=False
        asi::connectivity::diagnostic::GmExitBehavior exitBehavior; // optional=False
        asi::connectivity::diagnostic::GmExitTrigger exitTrigger; // optional=False
        private:
            GreyModeSettings()
            :
            activeUserTakeover(),
            exitBehavior(),
            exitTrigger()
            { }
            friend class GreyModeSettingsFactory;
            friend class CIFactory<GreyModeSettings>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::GreyModeSettings> >;
            friend class ipl::vector<GreyModeSettings>;
            friend class ipl::allocator<GreyModeSettings>;
#endif
    };

    typedef CIPtrArray<GreyModeSettings> CIGreyModeSettingsArray;

    /** \brief factory for diagnostic::GreyModeSettings. */
    class PROXY_EXPORT GreyModeSettingsFactory  : CIFactory<GreyModeSettings> {
    public:
        static inline CIPtr<GreyModeSettings> createGreyModeSettings() {
            return CIFactory<GreyModeSettings>::createObject();
        }
        static inline void createGreyModeSettings(CIPtr<GreyModeSettings> & s) {
            CIFactory<GreyModeSettings>::createObject(s);
        }
        static inline CIPtr<CIGreyModeSettingsArray> createGreyModeSettingsArray(size_t size) {
            return CIFactory<GreyModeSettings>::createArray(size);
        }
        static inline void createGreyModeSettingsArray(CIPtr<CIGreyModeSettingsArray>& a, size_t size) {
            CIFactory<GreyModeSettings>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_GREYMODESETTINGS_HXX
