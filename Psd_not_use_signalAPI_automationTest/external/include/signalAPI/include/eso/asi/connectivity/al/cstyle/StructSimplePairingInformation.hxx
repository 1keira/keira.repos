/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SIMPLEPAIRINGINFORMATION_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_SIMPLEPAIRINGINFORMATION_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct SimplePairingInformation;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::SimplePairingInformation& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimplePairingInformation &val);
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
    \brief struct al::SimplePairingInformation.
    */
    struct PROXY_EXPORT SimplePairingInformation
    {
        public:
            SimplePairingInformation()
            : m_isSimplePairingActive()
            , m_method()
            , m_deviceCapability()
            , m_pin(nullptr)
            { }

            SimplePairingInformation (const SimplePairingInformation& other)
            : m_isSimplePairingActive()
            , m_method()
            , m_deviceCapability()
            , m_pin(nullptr)
            {
              *this = other;
            }

            ~SimplePairingInformation () {
                if (m_pin) {
                    delete m_pin;
                }
            }
            bool operator==(const SimplePairingInformation& rhs) const {
                bool equal = true;
                if (m_isSimplePairingActive != rhs.m_isSimplePairingActive)
                    equal = false;
                if (m_method != rhs.m_method)
                    equal = false;
                if (m_deviceCapability != rhs.m_deviceCapability)
                    equal = false;
                if (m_pin == nullptr && rhs.m_pin != nullptr)
                    equal = false;
                else if (m_pin != nullptr && rhs.m_pin == nullptr)
                    equal = false;
                else if ((m_pin != nullptr) && (rhs.m_pin != nullptr) && (*m_pin != *rhs.m_pin))
                    equal = false;
                return equal;
            }
            bool operator!=(const SimplePairingInformation& rhs) const {
                return !operator==(rhs);
            }

            SimplePairingInformation& operator = (const SimplePairingInformation& src) {
                if (this == &src) return *this;
                m_isSimplePairingActive = src.m_isSimplePairingActive;
                m_method = src.m_method;
                m_deviceCapability = src.m_deviceCapability;
                if (m_pin)
                    delete m_pin;
                if (src.m_pin) {
                    m_pin = new (ipl::nothrow)ipl::string(*(src.m_pin));
                } else {
                    m_pin = nullptr;
                }
                return *this;
            }

                void setisSimplePairingActive(const bool _value) {
                    m_isSimplePairingActive = _value;
                }
                bool getisSimplePairingActive() const {
                    return m_isSimplePairingActive;
                }
                void setmethod(const int32_t _value) {
                    m_method = _value;
                }
                int32_t getmethod() const {
                    return m_method;
                }
                void setdeviceCapability(const int32_t _value) {
                    m_deviceCapability = _value;
                }
                int32_t getdeviceCapability() const {
                    return m_deviceCapability;
                }
                void setpin(const ipl::string* _value) {
                    if (m_pin)
                        delete m_pin;
                    if (_value) {
                        m_pin = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_pin = nullptr;
                    }
                }
                const ipl::string* getpin() const {
                    return m_pin;
                }
                    bool pinValid() const {
                        return m_pin != nullptr;
                    }


        bool m_isSimplePairingActive;
        int32_t m_method;
        int32_t m_deviceCapability;
    private:
        ipl::string* m_pin;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::SimplePairingInformation& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimplePairingInformation &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_SIMPLEPAIRINGINFORMATION_CSTYLE_HXX
