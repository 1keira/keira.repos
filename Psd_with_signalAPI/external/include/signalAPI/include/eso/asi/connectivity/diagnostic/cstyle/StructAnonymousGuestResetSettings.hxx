/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ANONYMOUSGUESTRESETSETTINGS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ANONYMOUSGUESTRESETSETTINGS_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
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
struct AnonymousGuestResetSettings;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings &val);
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
    \brief struct diagnostic::AnonymousGuestResetSettings.
    */
    struct PROXY_EXPORT AnonymousGuestResetSettings
    {
        public:
            AnonymousGuestResetSettings()
            : m_resetTrigger()
            , m_settingsChoice()
            { }

            AnonymousGuestResetSettings (const AnonymousGuestResetSettings& other)
            : m_resetTrigger()
            , m_settingsChoice()
            {
              *this = other;
            }

            ~AnonymousGuestResetSettings () {
            }
            bool operator==(const AnonymousGuestResetSettings& rhs) const {
                bool equal = true;
                if (m_resetTrigger != rhs.m_resetTrigger)
                    equal = false;
                if (m_settingsChoice != rhs.m_settingsChoice)
                    equal = false;
                return equal;
            }
            bool operator!=(const AnonymousGuestResetSettings& rhs) const {
                return !operator==(rhs);
            }

            AnonymousGuestResetSettings& operator = (const AnonymousGuestResetSettings& src) {
                if (this == &src) return *this;
                m_resetTrigger = src.m_resetTrigger;
                m_settingsChoice = src.m_settingsChoice;
                return *this;
            }

                void setresetTrigger(const asi::connectivity::diagnostic::cstyle::AgrsResetTrigger _value) {
                    m_resetTrigger = _value;
                }
                asi::connectivity::diagnostic::cstyle::AgrsResetTrigger getresetTrigger() const {
                    return m_resetTrigger;
                }
                void setsettingsChoice(const asi::connectivity::diagnostic::cstyle::AgrsSettingsChoice _value) {
                    m_settingsChoice = _value;
                }
                asi::connectivity::diagnostic::cstyle::AgrsSettingsChoice getsettingsChoice() const {
                    return m_settingsChoice;
                }


        asi::connectivity::diagnostic::cstyle::AgrsResetTrigger m_resetTrigger;
        asi::connectivity::diagnostic::cstyle::AgrsSettingsChoice m_settingsChoice;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AnonymousGuestResetSettings &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ANONYMOUSGUESTRESETSETTINGS_CSTYLE_HXX
