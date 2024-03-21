/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VEHICLEDIMENSIONS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VEHICLEDIMENSIONS_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct VehicleDimensions;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::VehicleDimensions& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::VehicleDimensions &val);
}
}

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{

    /**
    \brief struct diagnostic::VehicleDimensions.
    */
    struct PROXY_EXPORT VehicleDimensions
    {
        public:
            VehicleDimensions()
            : m_height()
            , m_length()
            , m_width()
            { }

            VehicleDimensions (const VehicleDimensions& other)
            : m_height()
            , m_length()
            , m_width()
            {
              *this = other;
            }

            ~VehicleDimensions () {
            }
            bool operator==(const VehicleDimensions& rhs) const {
                bool equal = true;
                if (m_height != rhs.m_height)
                    equal = false;
                if (m_length != rhs.m_length)
                    equal = false;
                if (m_width != rhs.m_width)
                    equal = false;
                return equal;
            }
            bool operator!=(const VehicleDimensions& rhs) const {
                return !operator==(rhs);
            }

            VehicleDimensions& operator = (const VehicleDimensions& src) {
                if (this == &src) return *this;
                m_height = src.m_height;
                m_length = src.m_length;
                m_width = src.m_width;
                return *this;
            }

                void setheight(const uint16_t _value) {
                    m_height = _value;
                }
                uint16_t getheight() const {
                    return m_height;
                }
                void setlength(const uint16_t _value) {
                    m_length = _value;
                }
                uint16_t getlength() const {
                    return m_length;
                }
                void setwidth(const uint16_t _value) {
                    m_width = _value;
                }
                uint16_t getwidth() const {
                    return m_width;
                }


        uint16_t m_height;
        uint16_t m_length;
        uint16_t m_width;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::VehicleDimensions& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::VehicleDimensions &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VEHICLEDIMENSIONS_CSTYLE_HXX
