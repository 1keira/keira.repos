/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NETWORKINFO_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_NETWORKINFO_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct NetworkInfo;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::NetworkInfo& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NetworkInfo &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{

    /**
    \brief struct al::NetworkInfo.
    */
    struct PROXY_EXPORT NetworkInfo
    {
        public:
            NetworkInfo()
            : m_regState()
            , m_domain()
            , m_isVoLTESupported()
            , m_is2G3GAvailable()
            , m_type()
            , m_signalStrength()
            , m_rsrp()
            , m_rsrq()
            , m_sinr()
            , m_rssi()
            , m_ecio()
            , m_operatorName(nullptr)
            , m_plmn(nullptr)
            , m_lac(nullptr)
            , m_cellId(nullptr)
            { }

            NetworkInfo (const NetworkInfo& other)
            : m_regState()
            , m_domain()
            , m_isVoLTESupported()
            , m_is2G3GAvailable()
            , m_type()
            , m_signalStrength()
            , m_rsrp()
            , m_rsrq()
            , m_sinr()
            , m_rssi()
            , m_ecio()
            , m_operatorName(nullptr)
            , m_plmn(nullptr)
            , m_lac(nullptr)
            , m_cellId(nullptr)
            {
              *this = other;
            }

            ~NetworkInfo () {
                if (m_operatorName) {
                    delete m_operatorName;
                }
                if (m_plmn) {
                    delete m_plmn;
                }
                if (m_lac) {
                    delete m_lac;
                }
                if (m_cellId) {
                    delete m_cellId;
                }
            }
            bool operator==(const NetworkInfo& rhs) const {
                bool equal = true;
                if (m_regState != rhs.m_regState)
                    equal = false;
                if (m_domain != rhs.m_domain)
                    equal = false;
                if (m_isVoLTESupported != rhs.m_isVoLTESupported)
                    equal = false;
                if (m_is2G3GAvailable != rhs.m_is2G3GAvailable)
                    equal = false;
                if (m_type != rhs.m_type)
                    equal = false;
                if (m_signalStrength != rhs.m_signalStrength)
                    equal = false;
                if (m_rsrp != rhs.m_rsrp)
                    equal = false;
                if (m_rsrq != rhs.m_rsrq)
                    equal = false;
                if (m_sinr != rhs.m_sinr)
                    equal = false;
                if (m_rssi != rhs.m_rssi)
                    equal = false;
                if (m_ecio != rhs.m_ecio)
                    equal = false;
                if (m_operatorName == nullptr && rhs.m_operatorName != nullptr)
                    equal = false;
                else if (m_operatorName != nullptr && rhs.m_operatorName == nullptr)
                    equal = false;
                else if ((m_operatorName != nullptr) && (rhs.m_operatorName != nullptr) && (*m_operatorName != *rhs.m_operatorName))
                    equal = false;
                if (m_plmn == nullptr && rhs.m_plmn != nullptr)
                    equal = false;
                else if (m_plmn != nullptr && rhs.m_plmn == nullptr)
                    equal = false;
                else if ((m_plmn != nullptr) && (rhs.m_plmn != nullptr) && (*m_plmn != *rhs.m_plmn))
                    equal = false;
                if (m_lac == nullptr && rhs.m_lac != nullptr)
                    equal = false;
                else if (m_lac != nullptr && rhs.m_lac == nullptr)
                    equal = false;
                else if ((m_lac != nullptr) && (rhs.m_lac != nullptr) && (*m_lac != *rhs.m_lac))
                    equal = false;
                if (m_cellId == nullptr && rhs.m_cellId != nullptr)
                    equal = false;
                else if (m_cellId != nullptr && rhs.m_cellId == nullptr)
                    equal = false;
                else if ((m_cellId != nullptr) && (rhs.m_cellId != nullptr) && (*m_cellId != *rhs.m_cellId))
                    equal = false;
                return equal;
            }
            bool operator!=(const NetworkInfo& rhs) const {
                return !operator==(rhs);
            }

            NetworkInfo& operator = (const NetworkInfo& src) {
                if (this == &src) return *this;
                m_regState = src.m_regState;
                m_domain = src.m_domain;
                m_isVoLTESupported = src.m_isVoLTESupported;
                m_is2G3GAvailable = src.m_is2G3GAvailable;
                m_type = src.m_type;
                m_signalStrength = src.m_signalStrength;
                m_rsrp = src.m_rsrp;
                m_rsrq = src.m_rsrq;
                m_sinr = src.m_sinr;
                m_rssi = src.m_rssi;
                m_ecio = src.m_ecio;
                if (m_operatorName)
                    delete m_operatorName;
                if (src.m_operatorName) {
                    m_operatorName = new (ipl::nothrow)ipl::string(*(src.m_operatorName));
                } else {
                    m_operatorName = nullptr;
                }
                if (m_plmn)
                    delete m_plmn;
                if (src.m_plmn) {
                    m_plmn = new (ipl::nothrow)ipl::string(*(src.m_plmn));
                } else {
                    m_plmn = nullptr;
                }
                if (m_lac)
                    delete m_lac;
                if (src.m_lac) {
                    m_lac = new (ipl::nothrow)ipl::string(*(src.m_lac));
                } else {
                    m_lac = nullptr;
                }
                if (m_cellId)
                    delete m_cellId;
                if (src.m_cellId) {
                    m_cellId = new (ipl::nothrow)ipl::string(*(src.m_cellId));
                } else {
                    m_cellId = nullptr;
                }
                return *this;
            }

                void setregState(const asi::connectivity::al::cstyle::RegState _value) {
                    m_regState = _value;
                }
                asi::connectivity::al::cstyle::RegState getregState() const {
                    return m_regState;
                }
                void setdomain(const asi::connectivity::al::cstyle::ServiceDomain _value) {
                    m_domain = _value;
                }
                asi::connectivity::al::cstyle::ServiceDomain getdomain() const {
                    return m_domain;
                }
                void setisVoLTESupported(const asi::connectivity::al::cstyle::VolteSupport _value) {
                    m_isVoLTESupported = _value;
                }
                asi::connectivity::al::cstyle::VolteSupport getisVoLTESupported() const {
                    return m_isVoLTESupported;
                }
                void setis2G3GAvailable(const asi::connectivity::al::cstyle::CSRatsSupport _value) {
                    m_is2G3GAvailable = _value;
                }
                asi::connectivity::al::cstyle::CSRatsSupport getis2G3GAvailable() const {
                    return m_is2G3GAvailable;
                }
                void settype(const asi::connectivity::al::cstyle::NetworkType _value) {
                    m_type = _value;
                }
                asi::connectivity::al::cstyle::NetworkType gettype() const {
                    return m_type;
                }
                void setsignalStrength(const int32_t _value) {
                    m_signalStrength = _value;
                }
                int32_t getsignalStrength() const {
                    return m_signalStrength;
                }
                void setrsrp(const int16_t _value) {
                    m_rsrp = _value;
                }
                int16_t getrsrp() const {
                    return m_rsrp;
                }
                void setrsrq(const int8_t _value) {
                    m_rsrq = _value;
                }
                int8_t getrsrq() const {
                    return m_rsrq;
                }
                void setsinr(const int16_t _value) {
                    m_sinr = _value;
                }
                int16_t getsinr() const {
                    return m_sinr;
                }
                void setrssi(const int8_t _value) {
                    m_rssi = _value;
                }
                int8_t getrssi() const {
                    return m_rssi;
                }
                void setecio(const int16_t _value) {
                    m_ecio = _value;
                }
                int16_t getecio() const {
                    return m_ecio;
                }
                void setoperatorName(const ipl::string* _value) {
                    if (m_operatorName)
                        delete m_operatorName;
                    if (_value) {
                        m_operatorName = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_operatorName = nullptr;
                    }
                }
                const ipl::string* getoperatorName() const {
                    return m_operatorName;
                }
                    bool operatorNameValid() const {
                        return m_operatorName != nullptr;
                    }
                void setplmn(const ipl::string* _value) {
                    if (m_plmn)
                        delete m_plmn;
                    if (_value) {
                        m_plmn = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_plmn = nullptr;
                    }
                }
                const ipl::string* getplmn() const {
                    return m_plmn;
                }
                    bool plmnValid() const {
                        return m_plmn != nullptr;
                    }
                void setlac(const ipl::string* _value) {
                    if (m_lac)
                        delete m_lac;
                    if (_value) {
                        m_lac = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_lac = nullptr;
                    }
                }
                const ipl::string* getlac() const {
                    return m_lac;
                }
                    bool lacValid() const {
                        return m_lac != nullptr;
                    }
                void setcellId(const ipl::string* _value) {
                    if (m_cellId)
                        delete m_cellId;
                    if (_value) {
                        m_cellId = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_cellId = nullptr;
                    }
                }
                const ipl::string* getcellId() const {
                    return m_cellId;
                }
                    bool cellIdValid() const {
                        return m_cellId != nullptr;
                    }


        asi::connectivity::al::cstyle::RegState m_regState;
        asi::connectivity::al::cstyle::ServiceDomain m_domain;
        asi::connectivity::al::cstyle::VolteSupport m_isVoLTESupported;
        asi::connectivity::al::cstyle::CSRatsSupport m_is2G3GAvailable;
        asi::connectivity::al::cstyle::NetworkType m_type;
        int32_t m_signalStrength;
        int16_t m_rsrp;
        int8_t m_rsrq;
        int16_t m_sinr;
        int8_t m_rssi;
        int16_t m_ecio;
    private:
        ipl::string* m_operatorName;
        ipl::string* m_plmn;
        ipl::string* m_lac;
        ipl::string* m_cellId;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::NetworkInfo& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NetworkInfo &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NETWORKINFO_CSTYLE_HXX
