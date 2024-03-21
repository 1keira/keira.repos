/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_RKA01STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_RKA01STRUCT_CSTYLE_HXX

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
struct RKA01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::RKA01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::RKA01Struct &val);
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
    \brief struct lhwapp::RKA01Struct.
    */
    struct PROXY_EXPORT RKA01Struct
    {
        public:
            RKA01Struct()
            : m_RKA_FMVSS138_Lampe_Raw()
            , m_RKA_Warnungen_02_Raw()
            , m_PduState()
            { }

            RKA01Struct (const RKA01Struct& other)
            : m_RKA_FMVSS138_Lampe_Raw()
            , m_RKA_Warnungen_02_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~RKA01Struct () {
            }
            bool operator==(const RKA01Struct& rhs) const {
                bool equal = true;
                if (m_RKA_FMVSS138_Lampe_Raw != rhs.m_RKA_FMVSS138_Lampe_Raw)
                    equal = false;
                if (m_RKA_Warnungen_02_Raw != rhs.m_RKA_Warnungen_02_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const RKA01Struct& rhs) const {
                return !operator==(rhs);
            }

            RKA01Struct& operator = (const RKA01Struct& src) {
                if (this == &src) return *this;
                m_RKA_FMVSS138_Lampe_Raw = src.m_RKA_FMVSS138_Lampe_Raw;
                m_RKA_Warnungen_02_Raw = src.m_RKA_Warnungen_02_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setRKA_FMVSS138_Lampe_Raw(const bool _value) {
                    m_RKA_FMVSS138_Lampe_Raw = _value;
                }
                bool getRKA_FMVSS138_Lampe_Raw() const {
                    return m_RKA_FMVSS138_Lampe_Raw;
                }
                void setRKA_Warnungen_02_Raw(const uint8_t _value) {
                    m_RKA_Warnungen_02_Raw = _value;
                }
                uint8_t getRKA_Warnungen_02_Raw() const {
                    return m_RKA_Warnungen_02_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_RKA_FMVSS138_Lampe_Raw;
        uint8_t m_RKA_Warnungen_02_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::RKA01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::RKA01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_RKA01STRUCT_CSTYLE_HXX
