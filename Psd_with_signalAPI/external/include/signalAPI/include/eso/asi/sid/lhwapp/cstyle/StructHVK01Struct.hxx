/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_HVK01STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_HVK01STRUCT_CSTYLE_HXX

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
struct HVK01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::HVK01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::HVK01Struct &val);
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
    \brief struct lhwapp::HVK01Struct.
    */
    struct PROXY_EXPORT HVK01Struct
    {
        public:
            HVK01Struct()
            : m_HVK_HV_Netz_Warnungen_Raw()
            , m_PduState()
            { }

            HVK01Struct (const HVK01Struct& other)
            : m_HVK_HV_Netz_Warnungen_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~HVK01Struct () {
            }
            bool operator==(const HVK01Struct& rhs) const {
                bool equal = true;
                if (m_HVK_HV_Netz_Warnungen_Raw != rhs.m_HVK_HV_Netz_Warnungen_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const HVK01Struct& rhs) const {
                return !operator==(rhs);
            }

            HVK01Struct& operator = (const HVK01Struct& src) {
                if (this == &src) return *this;
                m_HVK_HV_Netz_Warnungen_Raw = src.m_HVK_HV_Netz_Warnungen_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setHVK_HV_Netz_Warnungen_Raw(const uint8_t _value) {
                    m_HVK_HV_Netz_Warnungen_Raw = _value;
                }
                uint8_t getHVK_HV_Netz_Warnungen_Raw() const {
                    return m_HVK_HV_Netz_Warnungen_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_HVK_HV_Netz_Warnungen_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::HVK01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::HVK01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_HVK01STRUCT_CSTYLE_HXX
