/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_PRODUCTIONMODE_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_PRODUCTIONMODE_CSTYLE_HXX

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
struct ProductionMode;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::ProductionMode& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ProductionMode &val);
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
    \brief struct diagnostic::ProductionMode.
    */
    struct PROXY_EXPORT ProductionMode
    {
        public:
            ProductionMode()
            : m_isOnForBt()
            , m_isOnForMobNet()
            , m_isOnForWlan()
            { }

            ProductionMode (const ProductionMode& other)
            : m_isOnForBt()
            , m_isOnForMobNet()
            , m_isOnForWlan()
            {
              *this = other;
            }

            ~ProductionMode () {
            }
            bool operator==(const ProductionMode& rhs) const {
                bool equal = true;
                if (m_isOnForBt != rhs.m_isOnForBt)
                    equal = false;
                if (m_isOnForMobNet != rhs.m_isOnForMobNet)
                    equal = false;
                if (m_isOnForWlan != rhs.m_isOnForWlan)
                    equal = false;
                return equal;
            }
            bool operator!=(const ProductionMode& rhs) const {
                return !operator==(rhs);
            }

            ProductionMode& operator = (const ProductionMode& src) {
                if (this == &src) return *this;
                m_isOnForBt = src.m_isOnForBt;
                m_isOnForMobNet = src.m_isOnForMobNet;
                m_isOnForWlan = src.m_isOnForWlan;
                return *this;
            }

                void setisOnForBt(const bool _value) {
                    m_isOnForBt = _value;
                }
                bool getisOnForBt() const {
                    return m_isOnForBt;
                }
                void setisOnForMobNet(const bool _value) {
                    m_isOnForMobNet = _value;
                }
                bool getisOnForMobNet() const {
                    return m_isOnForMobNet;
                }
                void setisOnForWlan(const bool _value) {
                    m_isOnForWlan = _value;
                }
                bool getisOnForWlan() const {
                    return m_isOnForWlan;
                }


        bool m_isOnForBt;
        bool m_isOnForMobNet;
        bool m_isOnForWlan;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ProductionMode& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ProductionMode &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_PRODUCTIONMODE_CSTYLE_HXX
