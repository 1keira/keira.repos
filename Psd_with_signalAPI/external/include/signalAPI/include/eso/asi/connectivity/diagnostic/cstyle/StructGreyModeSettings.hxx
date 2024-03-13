/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_GREYMODESETTINGS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_GREYMODESETTINGS_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
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
struct GreyModeSettings;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::GreyModeSettings& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::GreyModeSettings &val);
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
    \brief struct diagnostic::GreyModeSettings.
    */
    struct PROXY_EXPORT GreyModeSettings
    {
        public:
            GreyModeSettings()
            : m_activeUserTakeover()
            , m_exitBehavior()
            , m_exitTrigger()
            { }

            GreyModeSettings (const GreyModeSettings& other)
            : m_activeUserTakeover()
            , m_exitBehavior()
            , m_exitTrigger()
            {
              *this = other;
            }

            ~GreyModeSettings () {
            }
            bool operator==(const GreyModeSettings& rhs) const {
                bool equal = true;
                if (m_activeUserTakeover != rhs.m_activeUserTakeover)
                    equal = false;
                if (m_exitBehavior != rhs.m_exitBehavior)
                    equal = false;
                if (m_exitTrigger != rhs.m_exitTrigger)
                    equal = false;
                return equal;
            }
            bool operator!=(const GreyModeSettings& rhs) const {
                return !operator==(rhs);
            }

            GreyModeSettings& operator = (const GreyModeSettings& src) {
                if (this == &src) return *this;
                m_activeUserTakeover = src.m_activeUserTakeover;
                m_exitBehavior = src.m_exitBehavior;
                m_exitTrigger = src.m_exitTrigger;
                return *this;
            }

                void setactiveUserTakeover(const asi::connectivity::diagnostic::cstyle::GmActiveUserTakeover _value) {
                    m_activeUserTakeover = _value;
                }
                asi::connectivity::diagnostic::cstyle::GmActiveUserTakeover getactiveUserTakeover() const {
                    return m_activeUserTakeover;
                }
                void setexitBehavior(const asi::connectivity::diagnostic::cstyle::GmExitBehavior _value) {
                    m_exitBehavior = _value;
                }
                asi::connectivity::diagnostic::cstyle::GmExitBehavior getexitBehavior() const {
                    return m_exitBehavior;
                }
                void setexitTrigger(const asi::connectivity::diagnostic::cstyle::GmExitTrigger _value) {
                    m_exitTrigger = _value;
                }
                asi::connectivity::diagnostic::cstyle::GmExitTrigger getexitTrigger() const {
                    return m_exitTrigger;
                }


        asi::connectivity::diagnostic::cstyle::GmActiveUserTakeover m_activeUserTakeover;
        asi::connectivity::diagnostic::cstyle::GmExitBehavior m_exitBehavior;
        asi::connectivity::diagnostic::cstyle::GmExitTrigger m_exitTrigger;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::GreyModeSettings& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::GreyModeSettings &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_GREYMODESETTINGS_CSTYLE_HXX
