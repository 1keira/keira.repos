/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VTTSTATUS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VTTSTATUS_CSTYLE_HXX

#include <comm/commidltypes.hxx>
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
struct VttStatus;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::VttStatus& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::VttStatus &val);
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
    \brief struct diagnostic::VttStatus.
    */
    struct PROXY_EXPORT VttStatus
    {
        public:
            VttStatus()
            : m_isActivated()
            , m_isTransmissionRestricted()
            , m_networkStatus()
            { }

            VttStatus (const VttStatus& other)
            : m_isActivated()
            , m_isTransmissionRestricted()
            , m_networkStatus()
            {
              *this = other;
            }

            ~VttStatus () {
            }
            bool operator==(const VttStatus& rhs) const {
                bool equal = true;
                if (m_isActivated != rhs.m_isActivated)
                    equal = false;
                if (m_isTransmissionRestricted != rhs.m_isTransmissionRestricted)
                    equal = false;
                if (m_networkStatus != rhs.m_networkStatus)
                    equal = false;
                return equal;
            }
            bool operator!=(const VttStatus& rhs) const {
                return !operator==(rhs);
            }

            VttStatus& operator = (const VttStatus& src) {
                if (this == &src) return *this;
                m_isActivated = src.m_isActivated;
                m_isTransmissionRestricted = src.m_isTransmissionRestricted;
                m_networkStatus = src.m_networkStatus;
                return *this;
            }

                void setisActivated(const bool _value) {
                    m_isActivated = _value;
                }
                bool getisActivated() const {
                    return m_isActivated;
                }
                void setisTransmissionRestricted(const bool _value) {
                    m_isTransmissionRestricted = _value;
                }
                bool getisTransmissionRestricted() const {
                    return m_isTransmissionRestricted;
                }
                void setnetworkStatus(const asi::connectivity::diagnostic::cstyle::VttNetworkStatus _value) {
                    m_networkStatus = _value;
                }
                asi::connectivity::diagnostic::cstyle::VttNetworkStatus getnetworkStatus() const {
                    return m_networkStatus;
                }


        bool m_isActivated;
        bool m_isTransmissionRestricted;
        asi::connectivity::diagnostic::cstyle::VttNetworkStatus m_networkStatus;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::VttStatus& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::VttStatus &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VTTSTATUS_CSTYLE_HXX
