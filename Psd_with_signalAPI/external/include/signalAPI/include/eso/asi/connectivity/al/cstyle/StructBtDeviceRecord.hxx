/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BTDEVICERECORD_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_BTDEVICERECORD_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/cstyle/StructBtDeviceLeSecurityKeys.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct BtDeviceRecord;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::BtDeviceRecord& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BtDeviceRecord &val);
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
    \brief struct al::BtDeviceRecord.
    */
    struct PROXY_EXPORT BtDeviceRecord
    {
        public:
            BtDeviceRecord()
            : m_address()
            , m_linkKeyType()
            , m_pinLen()
            , m_psRepMode()
            , m_leLinkKeyType()
            , m_linkKey(nullptr)
            , m_leLocalKeys(nullptr)
            , m_leRemoteKeys(nullptr)
            { }

            BtDeviceRecord (const BtDeviceRecord& other)
            : m_address()
            , m_linkKeyType()
            , m_pinLen()
            , m_psRepMode()
            , m_leLinkKeyType()
            , m_linkKey(nullptr)
            , m_leLocalKeys(nullptr)
            , m_leRemoteKeys(nullptr)
            {
              *this = other;
            }

            ~BtDeviceRecord () {
                if (m_linkKey) {
                    delete m_linkKey;
                }
                if (m_leLocalKeys) {
                    delete m_leLocalKeys;
                }
                if (m_leRemoteKeys) {
                    delete m_leRemoteKeys;
                }
            }
            bool operator==(const BtDeviceRecord& rhs) const {
                bool equal = true;
                if (m_address != rhs.m_address)
                    equal = false;
                if (m_linkKeyType != rhs.m_linkKeyType)
                    equal = false;
                if (m_linkKey == nullptr && rhs.m_linkKey != nullptr)
                    equal = false;
                else if (m_linkKey != nullptr && rhs.m_linkKey == nullptr)
                    equal = false;
                else if ((m_linkKey != nullptr) && (rhs.m_linkKey != nullptr) && (*m_linkKey != *rhs.m_linkKey))
                    equal = false;
                if (m_pinLen != rhs.m_pinLen)
                    equal = false;
                if (m_psRepMode != rhs.m_psRepMode)
                    equal = false;
                if (m_leLinkKeyType != rhs.m_leLinkKeyType)
                    equal = false;
                if (m_leLocalKeys == nullptr && rhs.m_leLocalKeys != nullptr)
                    equal = false;
                else if (m_leLocalKeys != nullptr && rhs.m_leLocalKeys == nullptr)
                    equal = false;
                else if ((m_leLocalKeys != nullptr) && (rhs.m_leLocalKeys != nullptr) && (*m_leLocalKeys != *rhs.m_leLocalKeys))
                    equal = false;
                if (m_leRemoteKeys == nullptr && rhs.m_leRemoteKeys != nullptr)
                    equal = false;
                else if (m_leRemoteKeys != nullptr && rhs.m_leRemoteKeys == nullptr)
                    equal = false;
                else if ((m_leRemoteKeys != nullptr) && (rhs.m_leRemoteKeys != nullptr) && (*m_leRemoteKeys != *rhs.m_leRemoteKeys))
                    equal = false;
                return equal;
            }
            bool operator!=(const BtDeviceRecord& rhs) const {
                return !operator==(rhs);
            }

            BtDeviceRecord& operator = (const BtDeviceRecord& src) {
                if (this == &src) return *this;
                m_address = src.m_address;
                m_linkKeyType = src.m_linkKeyType;
                if (m_linkKey)
                    delete m_linkKey;
                if (src.m_linkKey) {
                    m_linkKey = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_linkKey));
                } else {
                    m_linkKey = nullptr;
                }
                m_pinLen = src.m_pinLen;
                m_psRepMode = src.m_psRepMode;
                m_leLinkKeyType = src.m_leLinkKeyType;
                if (m_leLocalKeys)
                    delete m_leLocalKeys;
                if (src.m_leLocalKeys) {
                    m_leLocalKeys = new (ipl::nothrow)asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys(*(src.m_leLocalKeys));
                } else {
                    m_leLocalKeys = nullptr;
                }
                if (m_leRemoteKeys)
                    delete m_leRemoteKeys;
                if (src.m_leRemoteKeys) {
                    m_leRemoteKeys = new (ipl::nothrow)asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys(*(src.m_leRemoteKeys));
                } else {
                    m_leRemoteKeys = nullptr;
                }
                return *this;
            }

                void setaddress(const int64_t _value) {
                    m_address = _value;
                }
                int64_t getaddress() const {
                    return m_address;
                }
                void setlinkKeyType(const uint8_t _value) {
                    m_linkKeyType = _value;
                }
                uint8_t getlinkKeyType() const {
                    return m_linkKeyType;
                }
                void setlinkKey(const ipl::vector<uint8_t>* _value) {
                    if (m_linkKey)
                        delete m_linkKey;
                    if (_value) {
                        m_linkKey = new (ipl::nothrow)ipl::vector<uint8_t>(*_value);
                    } else {
                        m_linkKey = nullptr;
                    }
                }
                const ipl::vector<uint8_t>* getlinkKey() const {
                    return m_linkKey;
                }
                    bool linkKeyValid() const {
                        return m_linkKey != nullptr;
                    }
                void setpinLen(const uint8_t _value) {
                    m_pinLen = _value;
                }
                uint8_t getpinLen() const {
                    return m_pinLen;
                }
                void setpsRepMode(const uint8_t _value) {
                    m_psRepMode = _value;
                }
                uint8_t getpsRepMode() const {
                    return m_psRepMode;
                }
                void setleLinkKeyType(const uint8_t _value) {
                    m_leLinkKeyType = _value;
                }
                uint8_t getleLinkKeyType() const {
                    return m_leLinkKeyType;
                }
                void setleLocalKeys(const asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys* _value) {
                    if (m_leLocalKeys)
                        delete m_leLocalKeys;
                    if (_value) {
                        m_leLocalKeys = new (ipl::nothrow)asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys(*_value);
                    } else {
                        m_leLocalKeys = nullptr;
                    }
                }
                const asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys* getleLocalKeys() const {
                    return m_leLocalKeys;
                }
                    bool leLocalKeysValid() const {
                        return m_leLocalKeys != nullptr;
                    }
                void setleRemoteKeys(const asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys* _value) {
                    if (m_leRemoteKeys)
                        delete m_leRemoteKeys;
                    if (_value) {
                        m_leRemoteKeys = new (ipl::nothrow)asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys(*_value);
                    } else {
                        m_leRemoteKeys = nullptr;
                    }
                }
                const asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys* getleRemoteKeys() const {
                    return m_leRemoteKeys;
                }
                    bool leRemoteKeysValid() const {
                        return m_leRemoteKeys != nullptr;
                    }


        int64_t m_address;
        uint8_t m_linkKeyType;
        uint8_t m_pinLen;
        uint8_t m_psRepMode;
        uint8_t m_leLinkKeyType;
    private:
        /**
            linkKey Array Size: unlimited
        */
        ipl::vector<uint8_t>* m_linkKey;
        asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys* m_leLocalKeys;
        asi::connectivity::al::cstyle::BtDeviceLeSecurityKeys* m_leRemoteKeys;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::BtDeviceRecord& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BtDeviceRecord &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_BTDEVICERECORD_CSTYLE_HXX
