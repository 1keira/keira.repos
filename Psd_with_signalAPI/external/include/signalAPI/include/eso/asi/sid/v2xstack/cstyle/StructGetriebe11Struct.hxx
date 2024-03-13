/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_GETRIEBE11STRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_GETRIEBE11STRUCT_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace sid
{
namespace v2xstack
{
namespace  cstyle
{
struct Getriebe11Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::Getriebe11Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Getriebe11Struct &val);
}
}

namespace asi
{
namespace sid
{
namespace v2xstack
{
namespace  cstyle
{

    /**
    \brief struct v2xstack::Getriebe11Struct.
    */
    struct PROXY_EXPORT Getriebe11Struct
    {
        public:
            Getriebe11Struct()
            : m_GE_Fahrstufe_Raw()
            , m_PduState()
            { }

            Getriebe11Struct (const Getriebe11Struct& other)
            : m_GE_Fahrstufe_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Getriebe11Struct () {
            }
            bool operator==(const Getriebe11Struct& rhs) const {
                bool equal = true;
                if (m_GE_Fahrstufe_Raw != rhs.m_GE_Fahrstufe_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const Getriebe11Struct& rhs) const {
                return !operator==(rhs);
            }

            Getriebe11Struct& operator = (const Getriebe11Struct& src) {
                if (this == &src) return *this;
                m_GE_Fahrstufe_Raw = src.m_GE_Fahrstufe_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setGE_Fahrstufe_Raw(const uint8_t _value) {
                    m_GE_Fahrstufe_Raw = _value;
                }
                uint8_t getGE_Fahrstufe_Raw() const {
                    return m_GE_Fahrstufe_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_GE_Fahrstufe_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Getriebe11Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Getriebe11Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_GETRIEBE11STRUCT_CSTYLE_HXX
