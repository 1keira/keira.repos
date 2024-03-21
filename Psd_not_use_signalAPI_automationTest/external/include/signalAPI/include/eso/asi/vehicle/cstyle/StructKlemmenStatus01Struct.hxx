/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_VEHICLE_KLEMMENSTATUS01STRUCT_CSTYLE_HXX
#define ASI_VEHICLE_KLEMMENSTATUS01STRUCT_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace vehicle
{
namespace  cstyle
{
struct KlemmenStatus01Struct;
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::vehicle::cstyle::KlemmenStatus01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::vehicle::cstyle::KlemmenStatus01Struct &val);
}
}

namespace asi
{
namespace vehicle
{
namespace  cstyle
{

    /**
    \brief struct vehicle::KlemmenStatus01Struct.
    */
    struct PROXY_EXPORT KlemmenStatus01Struct
    {
        public:
            KlemmenStatus01Struct()
            : m_ZAS_Kl_15()
            , m_pdustate()
            { }

            KlemmenStatus01Struct (const KlemmenStatus01Struct& other)
            : m_ZAS_Kl_15()
            , m_pdustate()
            {
              *this = other;
            }

            ~KlemmenStatus01Struct () {
            }
            bool operator==(const KlemmenStatus01Struct& rhs) const {
                bool equal = true;
                if (m_ZAS_Kl_15 != rhs.m_ZAS_Kl_15)
                    equal = false;
                if (m_pdustate != rhs.m_pdustate)
                    equal = false;
                return equal;
            }
            bool operator!=(const KlemmenStatus01Struct& rhs) const {
                return !operator==(rhs);
            }

            KlemmenStatus01Struct& operator = (const KlemmenStatus01Struct& src) {
                if (this == &src) return *this;
                m_ZAS_Kl_15 = src.m_ZAS_Kl_15;
                m_pdustate = src.m_pdustate;
                return *this;
            }

                void setZAS_Kl_15(const uint64_t _value) {
                    m_ZAS_Kl_15 = _value;
                }
                uint64_t getZAS_Kl_15() const {
                    return m_ZAS_Kl_15;
                }
                void setpdustate(const uint64_t _value) {
                    m_pdustate = _value;
                }
                uint64_t getpdustate() const {
                    return m_pdustate;
                }


        uint64_t m_ZAS_Kl_15;
        uint64_t m_pdustate;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::vehicle::cstyle::KlemmenStatus01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::vehicle::cstyle::KlemmenStatus01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace vehicle

#endif// ASI_VEHICLE_KLEMMENSTATUS01STRUCT_CSTYLE_HXX
