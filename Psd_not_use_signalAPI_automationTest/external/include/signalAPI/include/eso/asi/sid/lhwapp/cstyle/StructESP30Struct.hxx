/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_ESP30STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_ESP30STRUCT_CSTYLE_HXX

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
struct ESP30Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::ESP30Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP30Struct &val);
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
    \brief struct lhwapp::ESP30Struct.
    */
    struct PROXY_EXPORT ESP30Struct
    {
        public:
            ESP30Struct()
            : m_RLE_Anzeigen_Raw()
            , m_PduState()
            { }

            ESP30Struct (const ESP30Struct& other)
            : m_RLE_Anzeigen_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~ESP30Struct () {
            }
            bool operator==(const ESP30Struct& rhs) const {
                bool equal = true;
                if (m_RLE_Anzeigen_Raw != rhs.m_RLE_Anzeigen_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const ESP30Struct& rhs) const {
                return !operator==(rhs);
            }

            ESP30Struct& operator = (const ESP30Struct& src) {
                if (this == &src) return *this;
                m_RLE_Anzeigen_Raw = src.m_RLE_Anzeigen_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setRLE_Anzeigen_Raw(const uint8_t _value) {
                    m_RLE_Anzeigen_Raw = _value;
                }
                uint8_t getRLE_Anzeigen_Raw() const {
                    return m_RLE_Anzeigen_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_RLE_Anzeigen_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::ESP30Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP30Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_ESP30STRUCT_CSTYLE_HXX
