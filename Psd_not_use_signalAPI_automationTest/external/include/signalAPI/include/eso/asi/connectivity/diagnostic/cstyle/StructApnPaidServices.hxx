/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_APNPAIDSERVICES_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_APNPAIDSERVICES_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructApnConfig.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct ApnPaidServices;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::ApnPaidServices& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ApnPaidServices &val);
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
    \brief struct diagnostic::ApnPaidServices.
    */
    struct PROXY_EXPORT ApnPaidServices
    {
        public:
            ApnPaidServices()
            : m_customerPaid(nullptr)
            , m_vwPaid(nullptr)
            { }

            ApnPaidServices (const ApnPaidServices& other)
            : m_customerPaid(nullptr)
            , m_vwPaid(nullptr)
            {
              *this = other;
            }

            ~ApnPaidServices () {
                if (m_customerPaid) {
                    delete m_customerPaid;
                }
                if (m_vwPaid) {
                    delete m_vwPaid;
                }
            }
            bool operator==(const ApnPaidServices& rhs) const {
                bool equal = true;
                if (m_customerPaid == nullptr && rhs.m_customerPaid != nullptr)
                    equal = false;
                else if (m_customerPaid != nullptr && rhs.m_customerPaid == nullptr)
                    equal = false;
                else if ((m_customerPaid != nullptr) && (rhs.m_customerPaid != nullptr) && (*m_customerPaid != *rhs.m_customerPaid))
                    equal = false;
                if (m_vwPaid == nullptr && rhs.m_vwPaid != nullptr)
                    equal = false;
                else if (m_vwPaid != nullptr && rhs.m_vwPaid == nullptr)
                    equal = false;
                else if ((m_vwPaid != nullptr) && (rhs.m_vwPaid != nullptr) && (*m_vwPaid != *rhs.m_vwPaid))
                    equal = false;
                return equal;
            }
            bool operator!=(const ApnPaidServices& rhs) const {
                return !operator==(rhs);
            }

            ApnPaidServices& operator = (const ApnPaidServices& src) {
                if (this == &src) return *this;
                if (m_customerPaid)
                    delete m_customerPaid;
                if (src.m_customerPaid) {
                    m_customerPaid = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ApnConfig(*(src.m_customerPaid));
                } else {
                    m_customerPaid = nullptr;
                }
                if (m_vwPaid)
                    delete m_vwPaid;
                if (src.m_vwPaid) {
                    m_vwPaid = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ApnConfig(*(src.m_vwPaid));
                } else {
                    m_vwPaid = nullptr;
                }
                return *this;
            }

                void setcustomerPaid(const asi::connectivity::diagnostic::cstyle::ApnConfig* _value) {
                    if (m_customerPaid)
                        delete m_customerPaid;
                    if (_value) {
                        m_customerPaid = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ApnConfig(*_value);
                    } else {
                        m_customerPaid = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::ApnConfig* getcustomerPaid() const {
                    return m_customerPaid;
                }
                    bool customerPaidValid() const {
                        return m_customerPaid != nullptr;
                    }
                void setvwPaid(const asi::connectivity::diagnostic::cstyle::ApnConfig* _value) {
                    if (m_vwPaid)
                        delete m_vwPaid;
                    if (_value) {
                        m_vwPaid = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ApnConfig(*_value);
                    } else {
                        m_vwPaid = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::ApnConfig* getvwPaid() const {
                    return m_vwPaid;
                }
                    bool vwPaidValid() const {
                        return m_vwPaid != nullptr;
                    }


    private:
        asi::connectivity::diagnostic::cstyle::ApnConfig* m_customerPaid;
        asi::connectivity::diagnostic::cstyle::ApnConfig* m_vwPaid;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ApnPaidServices& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ApnPaidServices &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_APNPAIDSERVICES_CSTYLE_HXX
