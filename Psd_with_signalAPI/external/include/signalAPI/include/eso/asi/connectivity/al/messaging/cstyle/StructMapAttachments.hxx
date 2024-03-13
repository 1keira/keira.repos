/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPATTACHMENTS_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPATTACHMENTS_CSTYLE_HXX

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
struct MapAttachments;
}
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::messaging::cstyle::MapAttachments& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapAttachments &val);
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
        
    * Definition of a MAP attachment intended for pushing
    
    */
    struct PROXY_EXPORT MapAttachments
    {
        public:
            MapAttachments()
            : m_rfc822_encoded_mimepart()
            , m_local_path(nullptr)
            , m_display_name(nullptr)
            , m_content_type(nullptr)
            { }

            MapAttachments (const MapAttachments& other)
            : m_rfc822_encoded_mimepart()
            , m_local_path(nullptr)
            , m_display_name(nullptr)
            , m_content_type(nullptr)
            {
              *this = other;
            }

            ~MapAttachments () {
                if (m_local_path) {
                    delete m_local_path;
                }
                if (m_display_name) {
                    delete m_display_name;
                }
                if (m_content_type) {
                    delete m_content_type;
                }
            }
            bool operator==(const MapAttachments& rhs) const {
                bool equal = true;
                if (m_local_path == nullptr && rhs.m_local_path != nullptr)
                    equal = false;
                else if (m_local_path != nullptr && rhs.m_local_path == nullptr)
                    equal = false;
                else if ((m_local_path != nullptr) && (rhs.m_local_path != nullptr) && (*m_local_path != *rhs.m_local_path))
                    equal = false;
                if (m_rfc822_encoded_mimepart != rhs.m_rfc822_encoded_mimepart)
                    equal = false;
                if (m_display_name == nullptr && rhs.m_display_name != nullptr)
                    equal = false;
                else if (m_display_name != nullptr && rhs.m_display_name == nullptr)
                    equal = false;
                else if ((m_display_name != nullptr) && (rhs.m_display_name != nullptr) && (*m_display_name != *rhs.m_display_name))
                    equal = false;
                if (m_content_type == nullptr && rhs.m_content_type != nullptr)
                    equal = false;
                else if (m_content_type != nullptr && rhs.m_content_type == nullptr)
                    equal = false;
                else if ((m_content_type != nullptr) && (rhs.m_content_type != nullptr) && (*m_content_type != *rhs.m_content_type))
                    equal = false;
                return equal;
            }
            bool operator!=(const MapAttachments& rhs) const {
                return !operator==(rhs);
            }

            MapAttachments& operator = (const MapAttachments& src) {
                if (this == &src) return *this;
                if (m_local_path)
                    delete m_local_path;
                if (src.m_local_path) {
                    m_local_path = new (ipl::nothrow)ipl::string(*(src.m_local_path));
                } else {
                    m_local_path = nullptr;
                }
                m_rfc822_encoded_mimepart = src.m_rfc822_encoded_mimepart;
                if (m_display_name)
                    delete m_display_name;
                if (src.m_display_name) {
                    m_display_name = new (ipl::nothrow)ipl::string(*(src.m_display_name));
                } else {
                    m_display_name = nullptr;
                }
                if (m_content_type)
                    delete m_content_type;
                if (src.m_content_type) {
                    m_content_type = new (ipl::nothrow)ipl::string(*(src.m_content_type));
                } else {
                    m_content_type = nullptr;
                }
                return *this;
            }

                void setlocal_path(const ipl::string* _value) {
                    if (m_local_path)
                        delete m_local_path;
                    if (_value) {
                        m_local_path = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_local_path = nullptr;
                    }
                }
                const ipl::string* getlocal_path() const {
                    return m_local_path;
                }
                    bool local_pathValid() const {
                        return m_local_path != nullptr;
                    }
                void setrfc822_encoded_mimepart(const bool _value) {
                    m_rfc822_encoded_mimepart = _value;
                }
                bool getrfc822_encoded_mimepart() const {
                    return m_rfc822_encoded_mimepart;
                }
                void setdisplay_name(const ipl::string* _value) {
                    if (m_display_name)
                        delete m_display_name;
                    if (_value) {
                        m_display_name = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_display_name = nullptr;
                    }
                }
                const ipl::string* getdisplay_name() const {
                    return m_display_name;
                }
                    bool display_nameValid() const {
                        return m_display_name != nullptr;
                    }
                void setcontent_type(const ipl::string* _value) {
                    if (m_content_type)
                        delete m_content_type;
                    if (_value) {
                        m_content_type = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_content_type = nullptr;
                    }
                }
                const ipl::string* getcontent_type() const {
                    return m_content_type;
                }
                    bool content_typeValid() const {
                        return m_content_type != nullptr;
                    }


        bool m_rfc822_encoded_mimepart;
    private:
        ipl::string* m_local_path;
        ipl::string* m_display_name;
        ipl::string* m_content_type;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::MapAttachments& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapAttachments &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging

#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPATTACHMENTS_CSTYLE_HXX
