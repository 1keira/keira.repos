/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SIMDATAINFO_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_SIMDATAINFO_CSTYLE_HXX

#include <comm/commidltypes.hxx>
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
struct SimDataInfo;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::SimDataInfo& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimDataInfo &val);
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
    \brief struct al::SimDataInfo.
    */
    struct PROXY_EXPORT SimDataInfo
    {
        public:
            SimDataInfo()
            : m_simState()
            , m_sim_type()
            , m_serviceProviderNameRetrieved()
            , m_iccid(nullptr)
            , m_euiccid(nullptr)
            , m_imsi(nullptr)
            , m_serviceProviderName(nullptr)
            , m_msisdn(nullptr)
            { }

            SimDataInfo (const SimDataInfo& other)
            : m_simState()
            , m_sim_type()
            , m_serviceProviderNameRetrieved()
            , m_iccid(nullptr)
            , m_euiccid(nullptr)
            , m_imsi(nullptr)
            , m_serviceProviderName(nullptr)
            , m_msisdn(nullptr)
            {
              *this = other;
            }

            ~SimDataInfo () {
                if (m_iccid) {
                    delete m_iccid;
                }
                if (m_euiccid) {
                    delete m_euiccid;
                }
                if (m_imsi) {
                    delete m_imsi;
                }
                if (m_serviceProviderName) {
                    delete m_serviceProviderName;
                }
                if (m_msisdn) {
                    delete m_msisdn;
                }
            }
            bool operator==(const SimDataInfo& rhs) const {
                bool equal = true;
                if (m_simState != rhs.m_simState)
                    equal = false;
                if (m_sim_type != rhs.m_sim_type)
                    equal = false;
                if (m_iccid == nullptr && rhs.m_iccid != nullptr)
                    equal = false;
                else if (m_iccid != nullptr && rhs.m_iccid == nullptr)
                    equal = false;
                else if ((m_iccid != nullptr) && (rhs.m_iccid != nullptr) && (*m_iccid != *rhs.m_iccid))
                    equal = false;
                if (m_euiccid == nullptr && rhs.m_euiccid != nullptr)
                    equal = false;
                else if (m_euiccid != nullptr && rhs.m_euiccid == nullptr)
                    equal = false;
                else if ((m_euiccid != nullptr) && (rhs.m_euiccid != nullptr) && (*m_euiccid != *rhs.m_euiccid))
                    equal = false;
                if (m_imsi == nullptr && rhs.m_imsi != nullptr)
                    equal = false;
                else if (m_imsi != nullptr && rhs.m_imsi == nullptr)
                    equal = false;
                else if ((m_imsi != nullptr) && (rhs.m_imsi != nullptr) && (*m_imsi != *rhs.m_imsi))
                    equal = false;
                if (m_serviceProviderName == nullptr && rhs.m_serviceProviderName != nullptr)
                    equal = false;
                else if (m_serviceProviderName != nullptr && rhs.m_serviceProviderName == nullptr)
                    equal = false;
                else if ((m_serviceProviderName != nullptr) && (rhs.m_serviceProviderName != nullptr) && (*m_serviceProviderName != *rhs.m_serviceProviderName))
                    equal = false;
                if (m_msisdn == nullptr && rhs.m_msisdn != nullptr)
                    equal = false;
                else if (m_msisdn != nullptr && rhs.m_msisdn == nullptr)
                    equal = false;
                else if ((m_msisdn != nullptr) && (rhs.m_msisdn != nullptr) && (*m_msisdn != *rhs.m_msisdn))
                    equal = false;
                if (m_serviceProviderNameRetrieved != rhs.m_serviceProviderNameRetrieved)
                    equal = false;
                return equal;
            }
            bool operator!=(const SimDataInfo& rhs) const {
                return !operator==(rhs);
            }

            SimDataInfo& operator = (const SimDataInfo& src) {
                if (this == &src) return *this;
                m_simState = src.m_simState;
                m_sim_type = src.m_sim_type;
                if (m_iccid)
                    delete m_iccid;
                if (src.m_iccid) {
                    m_iccid = new (ipl::nothrow)ipl::string(*(src.m_iccid));
                } else {
                    m_iccid = nullptr;
                }
                if (m_euiccid)
                    delete m_euiccid;
                if (src.m_euiccid) {
                    m_euiccid = new (ipl::nothrow)ipl::string(*(src.m_euiccid));
                } else {
                    m_euiccid = nullptr;
                }
                if (m_imsi)
                    delete m_imsi;
                if (src.m_imsi) {
                    m_imsi = new (ipl::nothrow)ipl::string(*(src.m_imsi));
                } else {
                    m_imsi = nullptr;
                }
                if (m_serviceProviderName)
                    delete m_serviceProviderName;
                if (src.m_serviceProviderName) {
                    m_serviceProviderName = new (ipl::nothrow)ipl::string(*(src.m_serviceProviderName));
                } else {
                    m_serviceProviderName = nullptr;
                }
                if (m_msisdn)
                    delete m_msisdn;
                if (src.m_msisdn) {
                    m_msisdn = new (ipl::nothrow)ipl::string(*(src.m_msisdn));
                } else {
                    m_msisdn = nullptr;
                }
                m_serviceProviderNameRetrieved = src.m_serviceProviderNameRetrieved;
                return *this;
            }

                void setsimState(const asi::connectivity::al::cstyle::SimState _value) {
                    m_simState = _value;
                }
                asi::connectivity::al::cstyle::SimState getsimState() const {
                    return m_simState;
                }
                void setsim_type(const asi::connectivity::al::cstyle::SimType _value) {
                    m_sim_type = _value;
                }
                asi::connectivity::al::cstyle::SimType getsim_type() const {
                    return m_sim_type;
                }
                void seticcid(const ipl::string* _value) {
                    if (m_iccid)
                        delete m_iccid;
                    if (_value) {
                        m_iccid = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_iccid = nullptr;
                    }
                }
                const ipl::string* geticcid() const {
                    return m_iccid;
                }
                    bool iccidValid() const {
                        return m_iccid != nullptr;
                    }
                void seteuiccid(const ipl::string* _value) {
                    if (m_euiccid)
                        delete m_euiccid;
                    if (_value) {
                        m_euiccid = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_euiccid = nullptr;
                    }
                }
                const ipl::string* geteuiccid() const {
                    return m_euiccid;
                }
                    bool euiccidValid() const {
                        return m_euiccid != nullptr;
                    }
                void setimsi(const ipl::string* _value) {
                    if (m_imsi)
                        delete m_imsi;
                    if (_value) {
                        m_imsi = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_imsi = nullptr;
                    }
                }
                const ipl::string* getimsi() const {
                    return m_imsi;
                }
                    bool imsiValid() const {
                        return m_imsi != nullptr;
                    }
                void setserviceProviderName(const ipl::string* _value) {
                    if (m_serviceProviderName)
                        delete m_serviceProviderName;
                    if (_value) {
                        m_serviceProviderName = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_serviceProviderName = nullptr;
                    }
                }
                const ipl::string* getserviceProviderName() const {
                    return m_serviceProviderName;
                }
                    bool serviceProviderNameValid() const {
                        return m_serviceProviderName != nullptr;
                    }
                void setmsisdn(const ipl::string* _value) {
                    if (m_msisdn)
                        delete m_msisdn;
                    if (_value) {
                        m_msisdn = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_msisdn = nullptr;
                    }
                }
                const ipl::string* getmsisdn() const {
                    return m_msisdn;
                }
                    bool msisdnValid() const {
                        return m_msisdn != nullptr;
                    }
                void setserviceProviderNameRetrieved(const bool _value) {
                    m_serviceProviderNameRetrieved = _value;
                }
                bool getserviceProviderNameRetrieved() const {
                    return m_serviceProviderNameRetrieved;
                }


        asi::connectivity::al::cstyle::SimState m_simState;
        asi::connectivity::al::cstyle::SimType m_sim_type;
        bool m_serviceProviderNameRetrieved;
    private:
        ipl::string* m_iccid;
        ipl::string* m_euiccid;
        ipl::string* m_imsi;
        ipl::string* m_serviceProviderName;
        ipl::string* m_msisdn;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::SimDataInfo& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::SimDataInfo &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_SIMDATAINFO_CSTYLE_HXX
