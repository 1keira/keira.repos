/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_AIRBAG01STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_AIRBAG01STRUCT_CSTYLE_HXX

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
struct Airbag01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::Airbag01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Airbag01Struct &val);
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
    \brief struct lhwapp::Airbag01Struct.
    */
    struct PROXY_EXPORT Airbag01Struct
    {
        public:
            Airbag01Struct()
            : m_AB_Crash_Int_Raw()
            , m_PduState()
            { }

            Airbag01Struct (const Airbag01Struct& other)
            : m_AB_Crash_Int_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Airbag01Struct () {
            }
            bool operator==(const Airbag01Struct& rhs) const {
                bool equal = true;
                if (m_AB_Crash_Int_Raw != rhs.m_AB_Crash_Int_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const Airbag01Struct& rhs) const {
                return !operator==(rhs);
            }

            Airbag01Struct& operator = (const Airbag01Struct& src) {
                if (this == &src) return *this;
                m_AB_Crash_Int_Raw = src.m_AB_Crash_Int_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setAB_Crash_Int_Raw(const uint8_t _value) {
                    m_AB_Crash_Int_Raw = _value;
                }
                uint8_t getAB_Crash_Int_Raw() const {
                    return m_AB_Crash_Int_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_AB_Crash_Int_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Airbag01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Airbag01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_AIRBAG01STRUCT_CSTYLE_HXX
