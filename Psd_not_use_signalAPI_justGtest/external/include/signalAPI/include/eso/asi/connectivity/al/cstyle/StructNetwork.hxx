/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NETWORK_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_NETWORK_CSTYLE_HXX

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
struct Network;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::Network& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::Network &val);
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
    \brief struct al::Network.
    */
    struct PROXY_EXPORT Network
    {
        public:
            Network()
            : m_availibility()
            , m_accessTech()
            , m_operator_long(nullptr)
            , m_operator_short(nullptr)
            , m_operator_numeric(nullptr)
            { }

            Network (const Network& other)
            : m_availibility()
            , m_accessTech()
            , m_operator_long(nullptr)
            , m_operator_short(nullptr)
            , m_operator_numeric(nullptr)
            {
              *this = other;
            }

            ~Network () {
                if (m_operator_long) {
                    delete m_operator_long;
                }
                if (m_operator_short) {
                    delete m_operator_short;
                }
                if (m_operator_numeric) {
                    delete m_operator_numeric;
                }
            }
            bool operator==(const Network& rhs) const {
                bool equal = true;
                if (m_operator_long == nullptr && rhs.m_operator_long != nullptr)
                    equal = false;
                else if (m_operator_long != nullptr && rhs.m_operator_long == nullptr)
                    equal = false;
                else if ((m_operator_long != nullptr) && (rhs.m_operator_long != nullptr) && (*m_operator_long != *rhs.m_operator_long))
                    equal = false;
                if (m_operator_short == nullptr && rhs.m_operator_short != nullptr)
                    equal = false;
                else if (m_operator_short != nullptr && rhs.m_operator_short == nullptr)
                    equal = false;
                else if ((m_operator_short != nullptr) && (rhs.m_operator_short != nullptr) && (*m_operator_short != *rhs.m_operator_short))
                    equal = false;
                if (m_operator_numeric == nullptr && rhs.m_operator_numeric != nullptr)
                    equal = false;
                else if (m_operator_numeric != nullptr && rhs.m_operator_numeric == nullptr)
                    equal = false;
                else if ((m_operator_numeric != nullptr) && (rhs.m_operator_numeric != nullptr) && (*m_operator_numeric != *rhs.m_operator_numeric))
                    equal = false;
                if (m_availibility != rhs.m_availibility)
                    equal = false;
                if (m_accessTech != rhs.m_accessTech)
                    equal = false;
                return equal;
            }
            bool operator!=(const Network& rhs) const {
                return !operator==(rhs);
            }

            Network& operator = (const Network& src) {
                if (this == &src) return *this;
                if (m_operator_long)
                    delete m_operator_long;
                if (src.m_operator_long) {
                    m_operator_long = new (ipl::nothrow)ipl::string(*(src.m_operator_long));
                } else {
                    m_operator_long = nullptr;
                }
                if (m_operator_short)
                    delete m_operator_short;
                if (src.m_operator_short) {
                    m_operator_short = new (ipl::nothrow)ipl::string(*(src.m_operator_short));
                } else {
                    m_operator_short = nullptr;
                }
                if (m_operator_numeric)
                    delete m_operator_numeric;
                if (src.m_operator_numeric) {
                    m_operator_numeric = new (ipl::nothrow)ipl::string(*(src.m_operator_numeric));
                } else {
                    m_operator_numeric = nullptr;
                }
                m_availibility = src.m_availibility;
                m_accessTech = src.m_accessTech;
                return *this;
            }

                void setoperator_long(const ipl::string* _value) {
                    if (m_operator_long)
                        delete m_operator_long;
                    if (_value) {
                        m_operator_long = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_operator_long = nullptr;
                    }
                }
                const ipl::string* getoperator_long() const {
                    return m_operator_long;
                }
                    bool operator_longValid() const {
                        return m_operator_long != nullptr;
                    }
                void setoperator_short(const ipl::string* _value) {
                    if (m_operator_short)
                        delete m_operator_short;
                    if (_value) {
                        m_operator_short = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_operator_short = nullptr;
                    }
                }
                const ipl::string* getoperator_short() const {
                    return m_operator_short;
                }
                    bool operator_shortValid() const {
                        return m_operator_short != nullptr;
                    }
                void setoperator_numeric(const ipl::string* _value) {
                    if (m_operator_numeric)
                        delete m_operator_numeric;
                    if (_value) {
                        m_operator_numeric = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_operator_numeric = nullptr;
                    }
                }
                const ipl::string* getoperator_numeric() const {
                    return m_operator_numeric;
                }
                    bool operator_numericValid() const {
                        return m_operator_numeric != nullptr;
                    }
                void setavailibility(const asi::connectivity::al::cstyle::NetworkAvailibility _value) {
                    m_availibility = _value;
                }
                asi::connectivity::al::cstyle::NetworkAvailibility getavailibility() const {
                    return m_availibility;
                }
                void setaccessTech(const asi::connectivity::al::cstyle::NetworkType _value) {
                    m_accessTech = _value;
                }
                asi::connectivity::al::cstyle::NetworkType getaccessTech() const {
                    return m_accessTech;
                }


        asi::connectivity::al::cstyle::NetworkAvailibility m_availibility;
        asi::connectivity::al::cstyle::NetworkType m_accessTech;
    private:
        ipl::string* m_operator_long;
        ipl::string* m_operator_short;
        ipl::string* m_operator_numeric;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::Network& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::Network &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NETWORK_CSTYLE_HXX
