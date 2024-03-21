/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NETWORKREJECTINFORMATION_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_NETWORKREJECTINFORMATION_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct NetworkRejectInformation;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::NetworkRejectInformation& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NetworkRejectInformation &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{

    /**
    \brief struct al::NetworkRejectInformation.
    */
    struct PROXY_EXPORT NetworkRejectInformation
    {
        public:
            NetworkRejectInformation()
            : m_rejectCause()
            , m_domain()
            , m_rat()
            , m_plmn(nullptr)
            { }

            NetworkRejectInformation (const NetworkRejectInformation& other)
            : m_rejectCause()
            , m_domain()
            , m_rat()
            , m_plmn(nullptr)
            {
              *this = other;
            }

            ~NetworkRejectInformation () {
                if (m_plmn) {
                    delete m_plmn;
                }
            }
            bool operator==(const NetworkRejectInformation& rhs) const {
                bool equal = true;
                if (m_rejectCause != rhs.m_rejectCause)
                    equal = false;
                if (m_plmn == nullptr && rhs.m_plmn != nullptr)
                    equal = false;
                else if (m_plmn != nullptr && rhs.m_plmn == nullptr)
                    equal = false;
                else if ((m_plmn != nullptr) && (rhs.m_plmn != nullptr) && (*m_plmn != *rhs.m_plmn))
                    equal = false;
                if (m_domain != rhs.m_domain)
                    equal = false;
                if (m_rat != rhs.m_rat)
                    equal = false;
                return equal;
            }
            bool operator!=(const NetworkRejectInformation& rhs) const {
                return !operator==(rhs);
            }

            NetworkRejectInformation& operator = (const NetworkRejectInformation& src) {
                if (this == &src) return *this;
                m_rejectCause = src.m_rejectCause;
                if (m_plmn)
                    delete m_plmn;
                if (src.m_plmn) {
                    m_plmn = new (ipl::nothrow)ipl::string(*(src.m_plmn));
                } else {
                    m_plmn = nullptr;
                }
                m_domain = src.m_domain;
                m_rat = src.m_rat;
                return *this;
            }

                void setrejectCause(const int32_t _value) {
                    m_rejectCause = _value;
                }
                int32_t getrejectCause() const {
                    return m_rejectCause;
                }
                void setplmn(const ipl::string* _value) {
                    if (m_plmn)
                        delete m_plmn;
                    if (_value) {
                        m_plmn = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_plmn = nullptr;
                    }
                }
                const ipl::string* getplmn() const {
                    return m_plmn;
                }
                    bool plmnValid() const {
                        return m_plmn != nullptr;
                    }
                void setdomain(const asi::connectivity::al::cstyle::ServiceDomain _value) {
                    m_domain = _value;
                }
                asi::connectivity::al::cstyle::ServiceDomain getdomain() const {
                    return m_domain;
                }
                void setrat(const asi::connectivity::al::cstyle::NetworkType _value) {
                    m_rat = _value;
                }
                asi::connectivity::al::cstyle::NetworkType getrat() const {
                    return m_rat;
                }


        int32_t m_rejectCause;
        asi::connectivity::al::cstyle::ServiceDomain m_domain;
        asi::connectivity::al::cstyle::NetworkType m_rat;
    private:
        ipl::string* m_plmn;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::NetworkRejectInformation& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NetworkRejectInformation &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NETWORKREJECTINFORMATION_CSTYLE_HXX
