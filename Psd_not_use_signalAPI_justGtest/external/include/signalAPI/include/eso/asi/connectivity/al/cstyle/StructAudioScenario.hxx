/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_AUDIOSCENARIO_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_AUDIOSCENARIO_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct AudioScenario;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::AudioScenario& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::AudioScenario &val);
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
    \brief struct al::AudioScenario.
    */
    struct PROXY_EXPORT AudioScenario
    {
        public:
            AudioScenario()
            : m_micLevel()
            , m_speakerLevel()
            , m_echoSwitchOn()
            , m_configFile(nullptr)
            { }

            AudioScenario (const AudioScenario& other)
            : m_micLevel()
            , m_speakerLevel()
            , m_echoSwitchOn()
            , m_configFile(nullptr)
            {
              *this = other;
            }

            ~AudioScenario () {
                if (m_configFile) {
                    delete m_configFile;
                }
            }
            bool operator==(const AudioScenario& rhs) const {
                bool equal = true;
                if (m_configFile == nullptr && rhs.m_configFile != nullptr)
                    equal = false;
                else if (m_configFile != nullptr && rhs.m_configFile == nullptr)
                    equal = false;
                else if ((m_configFile != nullptr) && (rhs.m_configFile != nullptr) && (*m_configFile != *rhs.m_configFile))
                    equal = false;
                if (m_micLevel != rhs.m_micLevel)
                    equal = false;
                if (m_speakerLevel != rhs.m_speakerLevel)
                    equal = false;
                if (m_echoSwitchOn != rhs.m_echoSwitchOn)
                    equal = false;
                return equal;
            }
            bool operator!=(const AudioScenario& rhs) const {
                return !operator==(rhs);
            }

            AudioScenario& operator = (const AudioScenario& src) {
                if (this == &src) return *this;
                if (m_configFile)
                    delete m_configFile;
                if (src.m_configFile) {
                    m_configFile = new (ipl::nothrow)ipl::string(*(src.m_configFile));
                } else {
                    m_configFile = nullptr;
                }
                m_micLevel = src.m_micLevel;
                m_speakerLevel = src.m_speakerLevel;
                m_echoSwitchOn = src.m_echoSwitchOn;
                return *this;
            }

                void setconfigFile(const ipl::string* _value) {
                    if (m_configFile)
                        delete m_configFile;
                    if (_value) {
                        m_configFile = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_configFile = nullptr;
                    }
                }
                const ipl::string* getconfigFile() const {
                    return m_configFile;
                }
                    bool configFileValid() const {
                        return m_configFile != nullptr;
                    }
                void setmicLevel(const int32_t _value) {
                    m_micLevel = _value;
                }
                int32_t getmicLevel() const {
                    return m_micLevel;
                }
                void setspeakerLevel(const int32_t _value) {
                    m_speakerLevel = _value;
                }
                int32_t getspeakerLevel() const {
                    return m_speakerLevel;
                }
                void setechoSwitchOn(const bool _value) {
                    m_echoSwitchOn = _value;
                }
                bool getechoSwitchOn() const {
                    return m_echoSwitchOn;
                }


        int32_t m_micLevel;
        int32_t m_speakerLevel;
        bool m_echoSwitchOn;
    private:
        ipl::string* m_configFile;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::AudioScenario& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::AudioScenario &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_AUDIOSCENARIO_CSTYLE_HXX
