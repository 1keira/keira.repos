/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_MOTOR41STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_MOTOR41STRUCT_CSTYLE_HXX

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
struct Motor41Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::Motor41Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Motor41Struct &val);
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
    \brief struct lhwapp::Motor41Struct.
    */
    struct PROXY_EXPORT Motor41Struct
    {
        public:
            Motor41Struct()
            : m_MO_EM_Ueberhitzungswarnung_Raw()
            , m_FDR_Warnung_ALR_Raw()
            , m_PduState()
            { }

            Motor41Struct (const Motor41Struct& other)
            : m_MO_EM_Ueberhitzungswarnung_Raw()
            , m_FDR_Warnung_ALR_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Motor41Struct () {
            }
            bool operator==(const Motor41Struct& rhs) const {
                bool equal = true;
                if (m_MO_EM_Ueberhitzungswarnung_Raw != rhs.m_MO_EM_Ueberhitzungswarnung_Raw)
                    equal = false;
                if (m_FDR_Warnung_ALR_Raw != rhs.m_FDR_Warnung_ALR_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const Motor41Struct& rhs) const {
                return !operator==(rhs);
            }

            Motor41Struct& operator = (const Motor41Struct& src) {
                if (this == &src) return *this;
                m_MO_EM_Ueberhitzungswarnung_Raw = src.m_MO_EM_Ueberhitzungswarnung_Raw;
                m_FDR_Warnung_ALR_Raw = src.m_FDR_Warnung_ALR_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setMO_EM_Ueberhitzungswarnung_Raw(const uint8_t _value) {
                    m_MO_EM_Ueberhitzungswarnung_Raw = _value;
                }
                uint8_t getMO_EM_Ueberhitzungswarnung_Raw() const {
                    return m_MO_EM_Ueberhitzungswarnung_Raw;
                }
                void setFDR_Warnung_ALR_Raw(const uint8_t _value) {
                    m_FDR_Warnung_ALR_Raw = _value;
                }
                uint8_t getFDR_Warnung_ALR_Raw() const {
                    return m_FDR_Warnung_ALR_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_MO_EM_Ueberhitzungswarnung_Raw;
        uint8_t m_FDR_Warnung_ALR_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Motor41Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Motor41Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_MOTOR41STRUCT_CSTYLE_HXX
