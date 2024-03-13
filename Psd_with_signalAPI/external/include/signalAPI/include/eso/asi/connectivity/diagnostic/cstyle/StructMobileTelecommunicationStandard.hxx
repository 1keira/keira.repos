/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_MOBILETELECOMMUNICATIONSTANDARD_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_MOBILETELECOMMUNICATIONSTANDARD_CSTYLE_HXX

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
struct MobileTelecommunicationStandard;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard &val);
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
    \brief struct diagnostic::MobileTelecommunicationStandard.
    */
    struct PROXY_EXPORT MobileTelecommunicationStandard
    {
        public:
            MobileTelecommunicationStandard()
            : m_is2gOn()
            , m_is3gOn()
            , m_is4gOn()
            , m_is4gCaOn()
            , m_is5gNsaOn()
            , m_is5gSaCaOn()
            , m_is5gSaOn()
            , m_isMsdViaSipOn()
            , m_isSoundRefSignalOn()
            , m_isVoLteOn()
            , m_isVoNrOn()
            { }

            MobileTelecommunicationStandard (const MobileTelecommunicationStandard& other)
            : m_is2gOn()
            , m_is3gOn()
            , m_is4gOn()
            , m_is4gCaOn()
            , m_is5gNsaOn()
            , m_is5gSaCaOn()
            , m_is5gSaOn()
            , m_isMsdViaSipOn()
            , m_isSoundRefSignalOn()
            , m_isVoLteOn()
            , m_isVoNrOn()
            {
              *this = other;
            }

            ~MobileTelecommunicationStandard () {
            }
            bool operator==(const MobileTelecommunicationStandard& rhs) const {
                bool equal = true;
                if (m_is2gOn != rhs.m_is2gOn)
                    equal = false;
                if (m_is3gOn != rhs.m_is3gOn)
                    equal = false;
                if (m_is4gOn != rhs.m_is4gOn)
                    equal = false;
                if (m_is4gCaOn != rhs.m_is4gCaOn)
                    equal = false;
                if (m_is5gNsaOn != rhs.m_is5gNsaOn)
                    equal = false;
                if (m_is5gSaCaOn != rhs.m_is5gSaCaOn)
                    equal = false;
                if (m_is5gSaOn != rhs.m_is5gSaOn)
                    equal = false;
                if (m_isMsdViaSipOn != rhs.m_isMsdViaSipOn)
                    equal = false;
                if (m_isSoundRefSignalOn != rhs.m_isSoundRefSignalOn)
                    equal = false;
                if (m_isVoLteOn != rhs.m_isVoLteOn)
                    equal = false;
                if (m_isVoNrOn != rhs.m_isVoNrOn)
                    equal = false;
                return equal;
            }
            bool operator!=(const MobileTelecommunicationStandard& rhs) const {
                return !operator==(rhs);
            }

            MobileTelecommunicationStandard& operator = (const MobileTelecommunicationStandard& src) {
                if (this == &src) return *this;
                m_is2gOn = src.m_is2gOn;
                m_is3gOn = src.m_is3gOn;
                m_is4gOn = src.m_is4gOn;
                m_is4gCaOn = src.m_is4gCaOn;
                m_is5gNsaOn = src.m_is5gNsaOn;
                m_is5gSaCaOn = src.m_is5gSaCaOn;
                m_is5gSaOn = src.m_is5gSaOn;
                m_isMsdViaSipOn = src.m_isMsdViaSipOn;
                m_isSoundRefSignalOn = src.m_isSoundRefSignalOn;
                m_isVoLteOn = src.m_isVoLteOn;
                m_isVoNrOn = src.m_isVoNrOn;
                return *this;
            }

                void setis2gOn(const bool _value) {
                    m_is2gOn = _value;
                }
                bool getis2gOn() const {
                    return m_is2gOn;
                }
                void setis3gOn(const bool _value) {
                    m_is3gOn = _value;
                }
                bool getis3gOn() const {
                    return m_is3gOn;
                }
                void setis4gOn(const bool _value) {
                    m_is4gOn = _value;
                }
                bool getis4gOn() const {
                    return m_is4gOn;
                }
                void setis4gCaOn(const bool _value) {
                    m_is4gCaOn = _value;
                }
                bool getis4gCaOn() const {
                    return m_is4gCaOn;
                }
                void setis5gNsaOn(const bool _value) {
                    m_is5gNsaOn = _value;
                }
                bool getis5gNsaOn() const {
                    return m_is5gNsaOn;
                }
                void setis5gSaCaOn(const bool _value) {
                    m_is5gSaCaOn = _value;
                }
                bool getis5gSaCaOn() const {
                    return m_is5gSaCaOn;
                }
                void setis5gSaOn(const bool _value) {
                    m_is5gSaOn = _value;
                }
                bool getis5gSaOn() const {
                    return m_is5gSaOn;
                }
                void setisMsdViaSipOn(const bool _value) {
                    m_isMsdViaSipOn = _value;
                }
                bool getisMsdViaSipOn() const {
                    return m_isMsdViaSipOn;
                }
                void setisSoundRefSignalOn(const bool _value) {
                    m_isSoundRefSignalOn = _value;
                }
                bool getisSoundRefSignalOn() const {
                    return m_isSoundRefSignalOn;
                }
                void setisVoLteOn(const bool _value) {
                    m_isVoLteOn = _value;
                }
                bool getisVoLteOn() const {
                    return m_isVoLteOn;
                }
                void setisVoNrOn(const bool _value) {
                    m_isVoNrOn = _value;
                }
                bool getisVoNrOn() const {
                    return m_isVoNrOn;
                }


        bool m_is2gOn;
        bool m_is3gOn;
        bool m_is4gOn;
        bool m_is4gCaOn;
        bool m_is5gNsaOn;
        bool m_is5gSaCaOn;
        bool m_is5gSaOn;
        bool m_isMsdViaSipOn;
        bool m_isSoundRefSignalOn;
        bool m_isVoLteOn;
        bool m_isVoNrOn;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::MobileTelecommunicationStandard &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_MOBILETELECOMMUNICATIONSTANDARD_CSTYLE_HXX
