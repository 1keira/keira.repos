/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ANTENNAPOSTOREFPOINT_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ANTENNAPOSTOREFPOINT_CSTYLE_HXX

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
struct AntennaPosToRefPoint;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint &val);
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
    \brief struct diagnostic::AntennaPosToRefPoint.
    */
    struct PROXY_EXPORT AntennaPosToRefPoint
    {
        public:
            AntennaPosToRefPoint()
            : m_directionX()
            , m_directionY()
            , m_directionZ()
            { }

            AntennaPosToRefPoint (const AntennaPosToRefPoint& other)
            : m_directionX()
            , m_directionY()
            , m_directionZ()
            {
              *this = other;
            }

            ~AntennaPosToRefPoint () {
            }
            bool operator==(const AntennaPosToRefPoint& rhs) const {
                bool equal = true;
                if (m_directionX != rhs.m_directionX)
                    equal = false;
                if (m_directionY != rhs.m_directionY)
                    equal = false;
                if (m_directionZ != rhs.m_directionZ)
                    equal = false;
                return equal;
            }
            bool operator!=(const AntennaPosToRefPoint& rhs) const {
                return !operator==(rhs);
            }

            AntennaPosToRefPoint& operator = (const AntennaPosToRefPoint& src) {
                if (this == &src) return *this;
                m_directionX = src.m_directionX;
                m_directionY = src.m_directionY;
                m_directionZ = src.m_directionZ;
                return *this;
            }

                void setdirectionX(const uint16_t _value) {
                    m_directionX = _value;
                }
                uint16_t getdirectionX() const {
                    return m_directionX;
                }
                void setdirectionY(const uint16_t _value) {
                    m_directionY = _value;
                }
                uint16_t getdirectionY() const {
                    return m_directionY;
                }
                void setdirectionZ(const uint16_t _value) {
                    m_directionZ = _value;
                }
                uint16_t getdirectionZ() const {
                    return m_directionZ;
                }


        uint16_t m_directionX;
        uint16_t m_directionY;
        uint16_t m_directionZ;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::AntennaPosToRefPoint &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ANTENNAPOSTOREFPOINT_CSTYLE_HXX
