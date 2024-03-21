/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_DAEMPFER01STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_DAEMPFER01STRUCT_CSTYLE_HXX

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
struct Daempfer01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::Daempfer01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Daempfer01Struct &val);
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
    \brief struct lhwapp::Daempfer01Struct.
    */
    struct PROXY_EXPORT Daempfer01Struct
    {
        public:
            Daempfer01Struct()
            : m_DR_Gelbe_Warnlampe_Raw()
            , m_PduState()
            { }

            Daempfer01Struct (const Daempfer01Struct& other)
            : m_DR_Gelbe_Warnlampe_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Daempfer01Struct () {
            }
            bool operator==(const Daempfer01Struct& rhs) const {
                bool equal = true;
                if (m_DR_Gelbe_Warnlampe_Raw != rhs.m_DR_Gelbe_Warnlampe_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const Daempfer01Struct& rhs) const {
                return !operator==(rhs);
            }

            Daempfer01Struct& operator = (const Daempfer01Struct& src) {
                if (this == &src) return *this;
                m_DR_Gelbe_Warnlampe_Raw = src.m_DR_Gelbe_Warnlampe_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setDR_Gelbe_Warnlampe_Raw(const uint8_t _value) {
                    m_DR_Gelbe_Warnlampe_Raw = _value;
                }
                uint8_t getDR_Gelbe_Warnlampe_Raw() const {
                    return m_DR_Gelbe_Warnlampe_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_DR_Gelbe_Warnlampe_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Daempfer01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Daempfer01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_DAEMPFER01STRUCT_CSTYLE_HXX
