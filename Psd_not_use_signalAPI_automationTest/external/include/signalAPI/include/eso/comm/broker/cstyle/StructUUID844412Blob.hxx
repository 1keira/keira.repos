/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef COMM_BROKER_UUID844412BLOB_CSTYLE_HXX
#define COMM_BROKER_UUID844412BLOB_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace comm
{
namespace broker
{
namespace  cstyle
{
struct UUID844412Blob;
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const comm::broker::cstyle::UUID844412Blob& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, comm::broker::cstyle::UUID844412Blob &val);
}
}

namespace comm
{
namespace broker
{
namespace  cstyle
{

    /**
        
    \brief This is a UUID in 8-4-4-4-12 notation.

    When the bytes member is created, the uuid is read left to right, dashes between groups are omitted,
    each group is written most significant bytes first - all written with growing index into bytes.
    
    */
    struct PROXY_EXPORT UUID844412Blob
    {
        public:
            UUID844412Blob()
            : m_bytes(nullptr)
            { }

            UUID844412Blob (const UUID844412Blob& other)
            : m_bytes(nullptr)
            {
              *this = other;
            }

            ~UUID844412Blob () {
                if (m_bytes) {
                    delete m_bytes;
                }
            }
            bool operator==(const UUID844412Blob& rhs) const {
                bool equal = true;
                if (m_bytes == nullptr && rhs.m_bytes != nullptr)
                    equal = false;
                else if (m_bytes != nullptr && rhs.m_bytes == nullptr)
                    equal = false;
                else if ((m_bytes != nullptr) && (rhs.m_bytes != nullptr) && (*m_bytes != *rhs.m_bytes))
                    equal = false;
                return equal;
            }
            bool operator!=(const UUID844412Blob& rhs) const {
                return !operator==(rhs);
            }

            UUID844412Blob& operator = (const UUID844412Blob& src) {
                if (this == &src) return *this;
                if (m_bytes)
                    delete m_bytes;
                if (src.m_bytes) {
                    m_bytes = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_bytes));
                } else {
                    m_bytes = nullptr;
                }
                return *this;
            }

                void setbytes(const ipl::vector<uint8_t>* _value) {
                    if (m_bytes)
                        delete m_bytes;
                    if (_value) {
                        m_bytes = new (ipl::nothrow)ipl::vector<uint8_t>(*_value);
                    } else {
                        m_bytes = nullptr;
                    }
                }
                const ipl::vector<uint8_t>* getbytes() const {
                    return m_bytes;
                }
                    bool bytesValid() const {
                        return m_bytes != nullptr;
                    }


    private:
        /**
            bytes Array Size [min,max]: [32,32]
        */
        ipl::vector<uint8_t>* m_bytes;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const comm::broker::cstyle::UUID844412Blob& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, comm::broker::cstyle::UUID844412Blob &val);
    };

} // cstyle
}//namespace comm
}//namespace broker

#endif// COMM_BROKER_UUID844412BLOB_CSTYLE_HXX
