/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAMETADATA_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAMETADATA_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct ViDiagDataMetadata;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata &val);
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
    \brief struct diagnostic::ViDiagDataMetadata.
    */
    struct PROXY_EXPORT ViDiagDataMetadata
    {
        public:
            ViDiagDataMetadata()
            : m_id()
            , m_isModifiable()
            , m_isReadOnly()
            , m_maxLength()
            , m_minLength()
            , m_type()
            { }

            ViDiagDataMetadata (const ViDiagDataMetadata& other)
            : m_id()
            , m_isModifiable()
            , m_isReadOnly()
            , m_maxLength()
            , m_minLength()
            , m_type()
            {
              *this = other;
            }

            ~ViDiagDataMetadata () {
            }
            bool operator==(const ViDiagDataMetadata& rhs) const {
                bool equal = true;
                if (m_id != rhs.m_id)
                    equal = false;
                if (m_isModifiable != rhs.m_isModifiable)
                    equal = false;
                if (m_isReadOnly != rhs.m_isReadOnly)
                    equal = false;
                if (m_maxLength != rhs.m_maxLength)
                    equal = false;
                if (m_minLength != rhs.m_minLength)
                    equal = false;
                if (m_type != rhs.m_type)
                    equal = false;
                return equal;
            }
            bool operator!=(const ViDiagDataMetadata& rhs) const {
                return !operator==(rhs);
            }

            ViDiagDataMetadata& operator = (const ViDiagDataMetadata& src) {
                if (this == &src) return *this;
                m_id = src.m_id;
                m_isModifiable = src.m_isModifiable;
                m_isReadOnly = src.m_isReadOnly;
                m_maxLength = src.m_maxLength;
                m_minLength = src.m_minLength;
                m_type = src.m_type;
                return *this;
            }

                void setid(const uint32_t _value) {
                    m_id = _value;
                }
                uint32_t getid() const {
                    return m_id;
                }
                void setisModifiable(const bool _value) {
                    m_isModifiable = _value;
                }
                bool getisModifiable() const {
                    return m_isModifiable;
                }
                void setisReadOnly(const bool _value) {
                    m_isReadOnly = _value;
                }
                bool getisReadOnly() const {
                    return m_isReadOnly;
                }
                void setmaxLength(const uint32_t _value) {
                    m_maxLength = _value;
                }
                uint32_t getmaxLength() const {
                    return m_maxLength;
                }
                void setminLength(const uint32_t _value) {
                    m_minLength = _value;
                }
                uint32_t getminLength() const {
                    return m_minLength;
                }
                void settype(const asi::connectivity::diagnostic::cstyle::DiagDataType _value) {
                    m_type = _value;
                }
                asi::connectivity::diagnostic::cstyle::DiagDataType gettype() const {
                    return m_type;
                }


        uint32_t m_id;
        bool m_isModifiable;
        bool m_isReadOnly;
        uint32_t m_maxLength;
        uint32_t m_minLength;
        asi::connectivity::diagnostic::cstyle::DiagDataType m_type;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAMETADATA_CSTYLE_HXX
