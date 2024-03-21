/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_EMERGENCYINFORMATIONSERVICESETTINGS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_EMERGENCYINFORMATIONSERVICESETTINGS_HXX

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
    \brief struct diagnostic::EmergencyInformationServiceSettings.
    */
    struct PROXY_EXPORT EmergencyInformationServiceSettings
    {
        uint32_t offlineTimeInterval; // optional=False
        uint16_t onlineDuration; // optional=False
        private:
            EmergencyInformationServiceSettings()
            :
            offlineTimeInterval(),
            onlineDuration()
            { }
            friend class EmergencyInformationServiceSettingsFactory;
            friend class CIFactory<EmergencyInformationServiceSettings>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::EmergencyInformationServiceSettings> >;
            friend class ipl::vector<EmergencyInformationServiceSettings>;
            friend class ipl::allocator<EmergencyInformationServiceSettings>;
#endif
    };

    typedef CIPtrArray<EmergencyInformationServiceSettings> CIEmergencyInformationServiceSettingsArray;

    /** \brief factory for diagnostic::EmergencyInformationServiceSettings. */
    class PROXY_EXPORT EmergencyInformationServiceSettingsFactory  : CIFactory<EmergencyInformationServiceSettings> {
    public:
        static inline CIPtr<EmergencyInformationServiceSettings> createEmergencyInformationServiceSettings() {
            return CIFactory<EmergencyInformationServiceSettings>::createObject();
        }
        static inline void createEmergencyInformationServiceSettings(CIPtr<EmergencyInformationServiceSettings> & s) {
            CIFactory<EmergencyInformationServiceSettings>::createObject(s);
        }
        static inline CIPtr<CIEmergencyInformationServiceSettingsArray> createEmergencyInformationServiceSettingsArray(size_t size) {
            return CIFactory<EmergencyInformationServiceSettings>::createArray(size);
        }
        static inline void createEmergencyInformationServiceSettingsArray(CIPtr<CIEmergencyInformationServiceSettingsArray>& a, size_t size) {
            CIFactory<EmergencyInformationServiceSettings>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_EMERGENCYINFORMATIONSERVICESETTINGS_HXX
