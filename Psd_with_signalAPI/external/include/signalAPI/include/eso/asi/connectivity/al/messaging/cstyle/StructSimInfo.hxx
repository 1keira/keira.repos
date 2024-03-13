/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_SIMINFO_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_SIMINFO_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/messaging/cstyle/Definitions.hxx>
#include <asi/connectivity/al/messaging/cstyle/Definitions.hxx>
#include <asi/connectivity/al/messaging/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{
namespace  cstyle
{
struct SimInfo;
}
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::messaging::cstyle::SimInfo& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::SimInfo &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{
namespace  cstyle
{

    /**
    \brief struct messaging::SimInfo.
    */
    struct PROXY_EXPORT SimInfo
    {
        public:
            SimInfo()
            : m_simReady()
            , m_simType()
            , m_simMode()
            , m_iccid(nullptr)
            { }

            SimInfo (const SimInfo& other)
            : m_simReady()
            , m_simType()
            , m_simMode()
            , m_iccid(nullptr)
            {
              *this = other;
            }

            ~SimInfo () {
                if (m_iccid) {
                    delete m_iccid;
                }
            }
            bool operator==(const SimInfo& rhs) const {
                bool equal = true;
                if (m_simReady != rhs.m_simReady)
                    equal = false;
                if (m_simType != rhs.m_simType)
                    equal = false;
                if (m_simMode != rhs.m_simMode)
                    equal = false;
                if (m_iccid == nullptr && rhs.m_iccid != nullptr)
                    equal = false;
                else if (m_iccid != nullptr && rhs.m_iccid == nullptr)
                    equal = false;
                else if ((m_iccid != nullptr) && (rhs.m_iccid != nullptr) && (*m_iccid != *rhs.m_iccid))
                    equal = false;
                return equal;
            }
            bool operator!=(const SimInfo& rhs) const {
                return !operator==(rhs);
            }

            SimInfo& operator = (const SimInfo& src) {
                if (this == &src) return *this;
                m_simReady = src.m_simReady;
                m_simType = src.m_simType;
                m_simMode = src.m_simMode;
                if (m_iccid)
                    delete m_iccid;
                if (src.m_iccid) {
                    m_iccid = new (ipl::nothrow)ipl::string(*(src.m_iccid));
                } else {
                    m_iccid = nullptr;
                }
                return *this;
            }

                void setsimReady(const asi::connectivity::al::messaging::cstyle::SimReady _value) {
                    m_simReady = _value;
                }
                asi::connectivity::al::messaging::cstyle::SimReady getsimReady() const {
                    return m_simReady;
                }
                void setsimType(const asi::connectivity::al::messaging::cstyle::SimType _value) {
                    m_simType = _value;
                }
                asi::connectivity::al::messaging::cstyle::SimType getsimType() const {
                    return m_simType;
                }
                void setsimMode(const asi::connectivity::al::messaging::cstyle::SimMode _value) {
                    m_simMode = _value;
                }
                asi::connectivity::al::messaging::cstyle::SimMode getsimMode() const {
                    return m_simMode;
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


        asi::connectivity::al::messaging::cstyle::SimReady m_simReady;
        asi::connectivity::al::messaging::cstyle::SimType m_simType;
        asi::connectivity::al::messaging::cstyle::SimMode m_simMode;
    private:
        ipl::string* m_iccid;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::SimInfo& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::SimInfo &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging

#endif// ASI_CONNECTIVITY_AL_MESSAGING_SIMINFO_CSTYLE_HXX
