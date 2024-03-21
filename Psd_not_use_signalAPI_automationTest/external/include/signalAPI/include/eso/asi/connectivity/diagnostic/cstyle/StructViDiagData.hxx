/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructViDiagDataMetadata.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct ViDiagData;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::ViDiagData& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ViDiagData &val);
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
    \brief struct diagnostic::ViDiagData.
    */
    struct PROXY_EXPORT ViDiagData
    {
        public:
            ViDiagData()
            : m_lastChanged()
            , m_data(nullptr)
            , m_metadata(nullptr)
            { }

            ViDiagData (const ViDiagData& other)
            : m_lastChanged()
            , m_data(nullptr)
            , m_metadata(nullptr)
            {
              *this = other;
            }

            ~ViDiagData () {
                if (m_data) {
                    delete m_data;
                }
                if (m_metadata) {
                    delete m_metadata;
                }
            }
            bool operator==(const ViDiagData& rhs) const {
                bool equal = true;
                if (m_data == nullptr && rhs.m_data != nullptr)
                    equal = false;
                else if (m_data != nullptr && rhs.m_data == nullptr)
                    equal = false;
                else if ((m_data != nullptr) && (rhs.m_data != nullptr) && (*m_data != *rhs.m_data))
                    equal = false;
                if (m_lastChanged != rhs.m_lastChanged)
                    equal = false;
                if (m_metadata == nullptr && rhs.m_metadata != nullptr)
                    equal = false;
                else if (m_metadata != nullptr && rhs.m_metadata == nullptr)
                    equal = false;
                else if ((m_metadata != nullptr) && (rhs.m_metadata != nullptr) && (*m_metadata != *rhs.m_metadata))
                    equal = false;
                return equal;
            }
            bool operator!=(const ViDiagData& rhs) const {
                return !operator==(rhs);
            }

            ViDiagData& operator = (const ViDiagData& src) {
                if (this == &src) return *this;
                if (m_data)
                    delete m_data;
                if (src.m_data) {
                    m_data = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_data));
                } else {
                    m_data = nullptr;
                }
                m_lastChanged = src.m_lastChanged;
                if (m_metadata)
                    delete m_metadata;
                if (src.m_metadata) {
                    m_metadata = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata(*(src.m_metadata));
                } else {
                    m_metadata = nullptr;
                }
                return *this;
            }

                void setdata(const ipl::vector<uint8_t>* _value) {
                    if (m_data)
                        delete m_data;
                    if (_value) {
                        m_data = new (ipl::nothrow)ipl::vector<uint8_t>(*_value);
                    } else {
                        m_data = nullptr;
                    }
                }
                const ipl::vector<uint8_t>* getdata() const {
                    return m_data;
                }
                    bool dataValid() const {
                        return m_data != nullptr;
                    }
                void setlastChanged(const uint64_t _value) {
                    m_lastChanged = _value;
                }
                uint64_t getlastChanged() const {
                    return m_lastChanged;
                }
                void setmetadata(const asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata* _value) {
                    if (m_metadata)
                        delete m_metadata;
                    if (_value) {
                        m_metadata = new (ipl::nothrow)asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata(*_value);
                    } else {
                        m_metadata = nullptr;
                    }
                }
                const asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata* getmetadata() const {
                    return m_metadata;
                }
                    bool metadataValid() const {
                        return m_metadata != nullptr;
                    }


        uint64_t m_lastChanged;
    private:
        /**
            data Array Size: unlimited
        */
        ipl::vector<uint8_t>* m_data;
        asi::connectivity::diagnostic::cstyle::ViDiagDataMetadata* m_metadata;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::ViDiagData& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::ViDiagData &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_CSTYLE_HXX
