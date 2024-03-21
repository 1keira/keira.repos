/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPENVELOPEVCARD_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPENVELOPEVCARD_CSTYLE_HXX

#include <comm/commidltypes.hxx>

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
struct MapEnvelopeVcard;
}
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::messaging::cstyle::MapEnvelopeVcard& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapEnvelopeVcard &val);
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
        
    * MAP specifies so called envelope vcards which describe the final recipients using 
    * limited number of vcard fields (e.g. N, TEL, EMAIL)
    
    */
    struct PROXY_EXPORT MapEnvelopeVcard
    {
        public:
            MapEnvelopeVcard()
            : m_name(nullptr)
            , m_email(nullptr)
            , m_tel(nullptr)
            { }

            MapEnvelopeVcard (const MapEnvelopeVcard& other)
            : m_name(nullptr)
            , m_email(nullptr)
            , m_tel(nullptr)
            {
              *this = other;
            }

            ~MapEnvelopeVcard () {
                if (m_name) {
                    delete m_name;
                }
                if (m_email) {
                    delete m_email;
                }
                if (m_tel) {
                    delete m_tel;
                }
            }
            bool operator==(const MapEnvelopeVcard& rhs) const {
                bool equal = true;
                if (m_name == nullptr && rhs.m_name != nullptr)
                    equal = false;
                else if (m_name != nullptr && rhs.m_name == nullptr)
                    equal = false;
                else if ((m_name != nullptr) && (rhs.m_name != nullptr) && (*m_name != *rhs.m_name))
                    equal = false;
                if (m_email == nullptr && rhs.m_email != nullptr)
                    equal = false;
                else if (m_email != nullptr && rhs.m_email == nullptr)
                    equal = false;
                else if ((m_email != nullptr) && (rhs.m_email != nullptr) && (*m_email != *rhs.m_email))
                    equal = false;
                if (m_tel == nullptr && rhs.m_tel != nullptr)
                    equal = false;
                else if (m_tel != nullptr && rhs.m_tel == nullptr)
                    equal = false;
                else if ((m_tel != nullptr) && (rhs.m_tel != nullptr) && (*m_tel != *rhs.m_tel))
                    equal = false;
                return equal;
            }
            bool operator!=(const MapEnvelopeVcard& rhs) const {
                return !operator==(rhs);
            }

            MapEnvelopeVcard& operator = (const MapEnvelopeVcard& src) {
                if (this == &src) return *this;
                if (m_name)
                    delete m_name;
                if (src.m_name) {
                    m_name = new (ipl::nothrow)ipl::string(*(src.m_name));
                } else {
                    m_name = nullptr;
                }
                if (m_email)
                    delete m_email;
                if (src.m_email) {
                    m_email = new (ipl::nothrow)ipl::string(*(src.m_email));
                } else {
                    m_email = nullptr;
                }
                if (m_tel)
                    delete m_tel;
                if (src.m_tel) {
                    m_tel = new (ipl::nothrow)ipl::string(*(src.m_tel));
                } else {
                    m_tel = nullptr;
                }
                return *this;
            }

                void setname(const ipl::string* _value) {
                    if (m_name)
                        delete m_name;
                    if (_value) {
                        m_name = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_name = nullptr;
                    }
                }
                const ipl::string* getname() const {
                    return m_name;
                }
                    bool nameValid() const {
                        return m_name != nullptr;
                    }
                void setemail(const ipl::string* _value) {
                    if (m_email)
                        delete m_email;
                    if (_value) {
                        m_email = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_email = nullptr;
                    }
                }
                const ipl::string* getemail() const {
                    return m_email;
                }
                    bool emailValid() const {
                        return m_email != nullptr;
                    }
                void settel(const ipl::string* _value) {
                    if (m_tel)
                        delete m_tel;
                    if (_value) {
                        m_tel = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_tel = nullptr;
                    }
                }
                const ipl::string* gettel() const {
                    return m_tel;
                }
                    bool telValid() const {
                        return m_tel != nullptr;
                    }


    private:
        ipl::string* m_name;
        ipl::string* m_email;
        ipl::string* m_tel;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::MapEnvelopeVcard& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapEnvelopeVcard &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging

#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPENVELOPEVCARD_CSTYLE_HXX
