/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_LWI01STRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_LWI01STRUCT_CSTYLE_HXX

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
struct LWI01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::LWI01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::LWI01Struct &val);
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
    \brief struct v2xstack::LWI01Struct.
    */
    struct PROXY_EXPORT LWI01Struct
    {
        public:
            LWI01Struct()
            : m_LWI_Lenkradwinkel_Raw()
            , m_LWI_Lenkradwinkel_SignalState()
            , m_LWI_VZ_Lenkradwinkel_Raw()
            , m_LWI_QBit_Lenkradwinkel_Raw()
            , m_PduState()
            { }

            LWI01Struct (const LWI01Struct& other)
            : m_LWI_Lenkradwinkel_Raw()
            , m_LWI_Lenkradwinkel_SignalState()
            , m_LWI_VZ_Lenkradwinkel_Raw()
            , m_LWI_QBit_Lenkradwinkel_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~LWI01Struct () {
            }
            bool operator==(const LWI01Struct& rhs) const {
                bool equal = true;
                if (m_LWI_Lenkradwinkel_Raw != rhs.m_LWI_Lenkradwinkel_Raw)
                    equal = false;
                if (m_LWI_Lenkradwinkel_SignalState != rhs.m_LWI_Lenkradwinkel_SignalState)
                    equal = false;
                if (m_LWI_VZ_Lenkradwinkel_Raw != rhs.m_LWI_VZ_Lenkradwinkel_Raw)
                    equal = false;
                if (m_LWI_QBit_Lenkradwinkel_Raw != rhs.m_LWI_QBit_Lenkradwinkel_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const LWI01Struct& rhs) const {
                return !operator==(rhs);
            }

            LWI01Struct& operator = (const LWI01Struct& src) {
                if (this == &src) return *this;
                m_LWI_Lenkradwinkel_Raw = src.m_LWI_Lenkradwinkel_Raw;
                m_LWI_Lenkradwinkel_SignalState = src.m_LWI_Lenkradwinkel_SignalState;
                m_LWI_VZ_Lenkradwinkel_Raw = src.m_LWI_VZ_Lenkradwinkel_Raw;
                m_LWI_QBit_Lenkradwinkel_Raw = src.m_LWI_QBit_Lenkradwinkel_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setLWI_Lenkradwinkel_Raw(const uint16_t _value) {
                    m_LWI_Lenkradwinkel_Raw = _value;
                }
                uint16_t getLWI_Lenkradwinkel_Raw() const {
                    return m_LWI_Lenkradwinkel_Raw;
                }
                void setLWI_Lenkradwinkel_SignalState(const uint64_t _value) {
                    m_LWI_Lenkradwinkel_SignalState = _value;
                }
                uint64_t getLWI_Lenkradwinkel_SignalState() const {
                    return m_LWI_Lenkradwinkel_SignalState;
                }
                void setLWI_VZ_Lenkradwinkel_Raw(const bool _value) {
                    m_LWI_VZ_Lenkradwinkel_Raw = _value;
                }
                bool getLWI_VZ_Lenkradwinkel_Raw() const {
                    return m_LWI_VZ_Lenkradwinkel_Raw;
                }
                void setLWI_QBit_Lenkradwinkel_Raw(const bool _value) {
                    m_LWI_QBit_Lenkradwinkel_Raw = _value;
                }
                bool getLWI_QBit_Lenkradwinkel_Raw() const {
                    return m_LWI_QBit_Lenkradwinkel_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint16_t m_LWI_Lenkradwinkel_Raw;
        uint64_t m_LWI_Lenkradwinkel_SignalState;
        bool m_LWI_VZ_Lenkradwinkel_Raw;
        bool m_LWI_QBit_Lenkradwinkel_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::LWI01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::LWI01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_LWI01STRUCT_CSTYLE_HXX
