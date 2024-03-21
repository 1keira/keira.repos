/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DATASETPARAMETER_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DATASETPARAMETER_CSTYLE_HXX

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
struct DatasetParameter;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::DatasetParameter& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::DatasetParameter &val);
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
    \brief struct diagnostic::DatasetParameter.
    */
    struct PROXY_EXPORT DatasetParameter
    {
        public:
            DatasetParameter()
            : m_key(nullptr)
            , m_value(nullptr)
            { }

            DatasetParameter (const DatasetParameter& other)
            : m_key(nullptr)
            , m_value(nullptr)
            {
              *this = other;
            }

            ~DatasetParameter () {
                if (m_key) {
                    delete m_key;
                }
                if (m_value) {
                    delete m_value;
                }
            }
            bool operator==(const DatasetParameter& rhs) const {
                bool equal = true;
                if (m_key == nullptr && rhs.m_key != nullptr)
                    equal = false;
                else if (m_key != nullptr && rhs.m_key == nullptr)
                    equal = false;
                else if ((m_key != nullptr) && (rhs.m_key != nullptr) && (*m_key != *rhs.m_key))
                    equal = false;
                if (m_value == nullptr && rhs.m_value != nullptr)
                    equal = false;
                else if (m_value != nullptr && rhs.m_value == nullptr)
                    equal = false;
                else if ((m_value != nullptr) && (rhs.m_value != nullptr) && (*m_value != *rhs.m_value))
                    equal = false;
                return equal;
            }
            bool operator!=(const DatasetParameter& rhs) const {
                return !operator==(rhs);
            }

            DatasetParameter& operator = (const DatasetParameter& src) {
                if (this == &src) return *this;
                if (m_key)
                    delete m_key;
                if (src.m_key) {
                    m_key = new (ipl::nothrow)ipl::string(*(src.m_key));
                } else {
                    m_key = nullptr;
                }
                if (m_value)
                    delete m_value;
                if (src.m_value) {
                    m_value = new (ipl::nothrow)ipl::string(*(src.m_value));
                } else {
                    m_value = nullptr;
                }
                return *this;
            }

                void setkey(const ipl::string* _value) {
                    if (m_key)
                        delete m_key;
                    if (_value) {
                        m_key = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_key = nullptr;
                    }
                }
                const ipl::string* getkey() const {
                    return m_key;
                }
                    bool keyValid() const {
                        return m_key != nullptr;
                    }
                void setvalue(const ipl::string* _value) {
                    if (m_value)
                        delete m_value;
                    if (_value) {
                        m_value = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_value = nullptr;
                    }
                }
                const ipl::string* getvalue() const {
                    return m_value;
                }
                    bool valueValid() const {
                        return m_value != nullptr;
                    }


    private:
        ipl::string* m_key;
        ipl::string* m_value;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::DatasetParameter& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::DatasetParameter &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DATASETPARAMETER_CSTYLE_HXX
