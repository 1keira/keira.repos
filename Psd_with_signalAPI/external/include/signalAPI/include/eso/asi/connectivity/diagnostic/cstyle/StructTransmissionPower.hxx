/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWER_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWER_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructTransmissionPowerMobNetAntenna.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructTransmissionPowerWlanAntenna.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct TransmissionPower;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::TransmissionPower& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPower &val);
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
    \brief struct diagnostic::TransmissionPower.
    */
    struct PROXY_EXPORT TransmissionPower
    {
        public:
            TransmissionPower()
            : m_btExtAntenna()
            , m_btIntAntenna()
            , m_mobNetAnt1(nullptr)
            , m_mobNetAnt2(nullptr)
            , m_mobNetAnt3(nullptr)
            , m_mobNetAnt4(nullptr)
            , m_wlanAnt1(nullptr)
            , m_wlanAnt2(nullptr)
            { }

            TransmissionPower (const TransmissionPower& other)
            : m_btExtAntenna()
            , m_btIntAntenna()
            , m_mobNetAnt1(nullptr)
            , m_mobNetAnt2(nullptr)
            , m_mobNetAnt3(nullptr)
            , m_mobNetAnt4(nullptr)
            , m_wlanAnt1(nullptr)
            , m_wlanAnt2(nullptr)
            {
              *this = other;
            }

            ~TransmissionPower () {
                if (m_mobNetAnt1) {
                    delete m_mobNetAnt1;
                }
                if (m_mobNetAnt2) {
                    delete m_mobNetAnt2;
                }
                if (m_mobNetAnt3) {
                    delete m_mobNetAnt3;
                }
                if (m_mobNetAnt4) {
                    delete m_mobNetAnt4;
                }
                if (m_wlanAnt1) {
                    delete m_wlanAnt1;
                }
                if (m_wlanAnt2) {
                    delete m_wlanAnt2;
                }
            }
            bool operator==(const TransmissionPower& rhs) const {
                bool equal = true;
                if (m_btExtAntenna != rhs.m_btExtAntenna)
                    equal = false;
                if (m_btIntAntenna != rhs.m_btIntAntenna)
                    equal = false;
                if (m_mobNetAnt1 == nullptr && rhs.m_mobNetAnt1 != nullptr)
                    equal = false;
                else if (m_mobNetAnt1 != nullptr && rhs.m_mobNetAnt1 == nullptr)
                    equal = false;
                else if ((m_mobNetAnt1 != nullptr) && (rhs.m_mobNetAnt1 != nullptr) && (*m_mobNetAnt1 != *rhs.m_mobNetAnt1))
                    equal = false;
                if (m_mobNetAnt2 == nullptr && rhs.m_mobNetAnt2 != nullptr)
                    equal = false;
                else if (m_mobNetAnt2 != nullptr && rhs.m_mobNetAnt2 == nullptr)
                    equal = false;
                else if ((m_mobNetAnt2 != nullptr) && (rhs.m_mobNetAnt2 != nullptr) && (*m_mobNetAnt2 != *rhs.m_mobNetAnt2))
                    equal = false;
                if (m_mobNetAnt3 == nullptr && rhs.m_mobNetAnt3 != nullptr)
                    equal = false;
                else if (m_mobNetAnt3 != nullptr && rhs.m_mobNetAnt3 == nullptr)
                    equal = false;
                else if ((m_mobNetAnt3 != nullptr) && (rhs.m_mobNetAnt3 != nullptr) && (*m_mobNetAnt3 != *rhs.m_mobNetAnt3))
                    equal = false;
                if (m_mobNetAnt4 == nullptr && rhs.m_mobNetAnt4 != nullptr)
                    equal = false;
                else if (m_mobNetAnt4 != nullptr && rhs.m_mobNetAnt4 == nullptr)
                    equal = false;
                else if ((m_mobNetAnt4 != nullptr) && (rhs.m_mobNetAnt4 != nullptr) && (*m_mobNetAnt4 != *rhs.m_mobNetAnt4))
                    equal = false;
                if (m_wlanAnt1 == nullptr && rhs.m_wlanAnt1 != nullptr)
                    equal = false;
                else if (m_wlanAnt1 != nullptr && rhs.m_wlanAnt1 == nullptr)
                    equal = false;
                else if ((m_wlanAnt1 != nullptr) && (rhs.m_wlanAnt1 != nullptr) && (*m_wlanAnt1 != *rhs.m_wlanAnt1))
                    equal = false;
                if (m_wlanAnt2 == nullptr && rhs.m_wlanAnt2 != nullptr)
                    equal = false;
                else if (m_wlanAnt2 != nullptr && rhs.m_wlanAnt2 == nullptr)
                    equal = false;
                else if ((m_wlanAnt2 != nullptr) && (rhs.m_wlanAnt2 != nullptr) && (*m_wlanAnt2 != *rhs.m_wlanAnt2))
                    equal = false;
                return equal;
            }
            bool operator!=(const TransmissionPower& rhs) const {
                return !operator==(rhs);
            }

            TransmissionPower& operator = (const TransmissionPower& src) {
                if (this == &src) return *this;
                m_btExtAntenna = src.m_btExtAntenna;
                m_btIntAntenna = src.m_btIntAntenna;
                if (m_mobNetAnt1)
                    delete m_mobNetAnt1;
                if (src.m_mobNetAnt1) {
                    m_mobNetAnt1 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna(*(src.m_mobNetAnt1));
                } else {
                    m_mobNetAnt1 = nullptr;
                }
                if (m_mobNetAnt2)
                    delete m_mobNetAnt2;
                if (src.m_mobNetAnt2) {
                    m_mobNetAnt2 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna(*(src.m_mobNetAnt2));
                } else {
                    m_mobNetAnt2 = nullptr;
                }
                if (m_mobNetAnt3)
                    delete m_mobNetAnt3;
                if (src.m_mobNetAnt3) {
                    m_mobNetAnt3 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna(*(src.m_mobNetAnt3));
                } else {
                    m_mobNetAnt3 = nullptr;
                }
                if (m_mobNetAnt4)
                    delete m_mobNetAnt4;
                if (src.m_mobNetAnt4) {
                    m_mobNetAnt4 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna(*(src.m_mobNetAnt4));
                } else {
                    m_mobNetAnt4 = nullptr;
                }
                if (m_wlanAnt1)
                    delete m_wlanAnt1;
                if (src.m_wlanAnt1) {
                    m_wlanAnt1 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna(*(src.m_wlanAnt1));
                } else {
                    m_wlanAnt1 = nullptr;
                }
                if (m_wlanAnt2)
                    delete m_wlanAnt2;
                if (src.m_wlanAnt2) {
                    m_wlanAnt2 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna(*(src.m_wlanAnt2));
                } else {
                    m_wlanAnt2 = nullptr;
                }
                return *this;
            }

                void setbtExtAntenna(const uint8_t _value) {
                    m_btExtAntenna = _value;
                }
                uint8_t getbtExtAntenna() const {
                    return m_btExtAntenna;
                }
                void setbtIntAntenna(const uint8_t _value) {
                    m_btIntAntenna = _value;
                }
                uint8_t getbtIntAntenna() const {
                    return m_btIntAntenna;
                }
                void setmobNetAnt1(const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* _value) {
                    if (m_mobNetAnt1)
                        delete m_mobNetAnt1;
                    if (_value) {
                        m_mobNetAnt1 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna(*_value);
                    } else {
                        m_mobNetAnt1 = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* getmobNetAnt1() const {
                    return m_mobNetAnt1;
                }
                    bool mobNetAnt1Valid() const {
                        return m_mobNetAnt1 != nullptr;
                    }
                void setmobNetAnt2(const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* _value) {
                    if (m_mobNetAnt2)
                        delete m_mobNetAnt2;
                    if (_value) {
                        m_mobNetAnt2 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna(*_value);
                    } else {
                        m_mobNetAnt2 = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* getmobNetAnt2() const {
                    return m_mobNetAnt2;
                }
                    bool mobNetAnt2Valid() const {
                        return m_mobNetAnt2 != nullptr;
                    }
                void setmobNetAnt3(const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* _value) {
                    if (m_mobNetAnt3)
                        delete m_mobNetAnt3;
                    if (_value) {
                        m_mobNetAnt3 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna(*_value);
                    } else {
                        m_mobNetAnt3 = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* getmobNetAnt3() const {
                    return m_mobNetAnt3;
                }
                    bool mobNetAnt3Valid() const {
                        return m_mobNetAnt3 != nullptr;
                    }
                void setmobNetAnt4(const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* _value) {
                    if (m_mobNetAnt4)
                        delete m_mobNetAnt4;
                    if (_value) {
                        m_mobNetAnt4 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna(*_value);
                    } else {
                        m_mobNetAnt4 = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* getmobNetAnt4() const {
                    return m_mobNetAnt4;
                }
                    bool mobNetAnt4Valid() const {
                        return m_mobNetAnt4 != nullptr;
                    }
                void setwlanAnt1(const asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna* _value) {
                    if (m_wlanAnt1)
                        delete m_wlanAnt1;
                    if (_value) {
                        m_wlanAnt1 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna(*_value);
                    } else {
                        m_wlanAnt1 = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna* getwlanAnt1() const {
                    return m_wlanAnt1;
                }
                    bool wlanAnt1Valid() const {
                        return m_wlanAnt1 != nullptr;
                    }
                void setwlanAnt2(const asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna* _value) {
                    if (m_wlanAnt2)
                        delete m_wlanAnt2;
                    if (_value) {
                        m_wlanAnt2 = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna(*_value);
                    } else {
                        m_wlanAnt2 = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna* getwlanAnt2() const {
                    return m_wlanAnt2;
                }
                    bool wlanAnt2Valid() const {
                        return m_wlanAnt2 != nullptr;
                    }


        uint8_t m_btExtAntenna;
        uint8_t m_btIntAntenna;
    private:
        asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* m_mobNetAnt1;
        asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* m_mobNetAnt2;
        asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* m_mobNetAnt3;
        asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna* m_mobNetAnt4;
        asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna* m_wlanAnt1;
        asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna* m_wlanAnt2;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::TransmissionPower& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPower &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWER_CSTYLE_HXX
