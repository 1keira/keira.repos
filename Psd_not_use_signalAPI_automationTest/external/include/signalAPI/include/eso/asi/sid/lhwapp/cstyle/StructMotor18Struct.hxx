/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_MOTOR18STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_MOTOR18STRUCT_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace sid
{
namespace lhwapp
{
namespace  cstyle
{
struct Motor18Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::Motor18Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Motor18Struct &val);
}
}

namespace asi
{
namespace sid
{
namespace lhwapp
{
namespace  cstyle
{

    /**
    \brief struct lhwapp::Motor18Struct.
    */
    struct PROXY_EXPORT Motor18Struct
    {
        public:
            Motor18Struct()
            : m_MO_EPCL_Raw()
            , m_PduState()
            { }

            Motor18Struct (const Motor18Struct& other)
            : m_MO_EPCL_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Motor18Struct () {
            }
            bool operator==(const Motor18Struct& rhs) const {
                bool equal = true;
                if (m_MO_EPCL_Raw != rhs.m_MO_EPCL_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const Motor18Struct& rhs) const {
                return !operator==(rhs);
            }

            Motor18Struct& operator = (const Motor18Struct& src) {
                if (this == &src) return *this;
                m_MO_EPCL_Raw = src.m_MO_EPCL_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setMO_EPCL_Raw(const uint8_t _value) {
                    m_MO_EPCL_Raw = _value;
                }
                uint8_t getMO_EPCL_Raw() const {
                    return m_MO_EPCL_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_MO_EPCL_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Motor18Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Motor18Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_MOTOR18STRUCT_CSTYLE_HXX
