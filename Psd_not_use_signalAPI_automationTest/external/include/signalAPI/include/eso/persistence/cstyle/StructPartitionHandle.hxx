/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef PERSISTENCE_PARTITIONHANDLE_CSTYLE_HXX
#define PERSISTENCE_PARTITIONHANDLE_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace persistence
{
namespace  cstyle
{
struct PartitionHandle;
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const persistence::cstyle::PartitionHandle& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, persistence::cstyle::PartitionHandle &val);
}
}

namespace persistence
{
namespace  cstyle
{

    /**
        
        \brief Opaque handle for an open partition
    
    */
    struct PROXY_EXPORT PartitionHandle
    {
        public:
            PartitionHandle()
            : m_index()
            { }

            PartitionHandle (const PartitionHandle& other)
            : m_index()
            {
              *this = other;
            }

            ~PartitionHandle () {
            }
            bool operator==(const PartitionHandle& rhs) const {
                bool equal = true;
                if (m_index != rhs.m_index)
                    equal = false;
                return equal;
            }
            bool operator!=(const PartitionHandle& rhs) const {
                return !operator==(rhs);
            }

            PartitionHandle& operator = (const PartitionHandle& src) {
                if (this == &src) return *this;
                m_index = src.m_index;
                return *this;
            }

                void setindex(const uint32_t _value) {
                    m_index = _value;
                }
                uint32_t getindex() const {
                    return m_index;
                }


        uint32_t m_index;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const persistence::cstyle::PartitionHandle& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, persistence::cstyle::PartitionHandle &val);
    };

} // cstyle
}//namespace persistence

#endif// PERSISTENCE_PARTITIONHANDLE_CSTYLE_HXX
