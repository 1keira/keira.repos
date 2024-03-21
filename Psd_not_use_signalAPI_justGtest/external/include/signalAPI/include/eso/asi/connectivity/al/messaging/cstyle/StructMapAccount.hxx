/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPACCOUNT_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPACCOUNT_CSTYLE_HXX

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
struct MapAccount;
}
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::messaging::cstyle::MapAccount& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapAccount &val);
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
        *
    * Describes a map account.
    
    */
    struct PROXY_EXPORT MapAccount
    {
        public:
            MapAccount()
            : m_deviceId()
            , m_accountId()
            , m_connected()
            , m_supportedMessageTypes()
            , m_mapSupportedFeatures()
            , m_title(nullptr)
            { }

            MapAccount (const MapAccount& other)
            : m_deviceId()
            , m_accountId()
            , m_connected()
            , m_supportedMessageTypes()
            , m_mapSupportedFeatures()
            , m_title(nullptr)
            {
              *this = other;
            }

            ~MapAccount () {
                if (m_title) {
                    delete m_title;
                }
            }
            bool operator==(const MapAccount& rhs) const {
                bool equal = true;
                if (m_deviceId != rhs.m_deviceId)
                    equal = false;
                if (m_accountId != rhs.m_accountId)
                    equal = false;
                if (m_connected != rhs.m_connected)
                    equal = false;
                if (m_supportedMessageTypes != rhs.m_supportedMessageTypes)
                    equal = false;
                if (m_mapSupportedFeatures != rhs.m_mapSupportedFeatures)
                    equal = false;
                if (m_title == nullptr && rhs.m_title != nullptr)
                    equal = false;
                else if (m_title != nullptr && rhs.m_title == nullptr)
                    equal = false;
                else if ((m_title != nullptr) && (rhs.m_title != nullptr) && (*m_title != *rhs.m_title))
                    equal = false;
                return equal;
            }
            bool operator!=(const MapAccount& rhs) const {
                return !operator==(rhs);
            }

            MapAccount& operator = (const MapAccount& src) {
                if (this == &src) return *this;
                m_deviceId = src.m_deviceId;
                m_accountId = src.m_accountId;
                m_connected = src.m_connected;
                m_supportedMessageTypes = src.m_supportedMessageTypes;
                m_mapSupportedFeatures = src.m_mapSupportedFeatures;
                if (m_title)
                    delete m_title;
                if (src.m_title) {
                    m_title = new (ipl::nothrow)ipl::string(*(src.m_title));
                } else {
                    m_title = nullptr;
                }
                return *this;
            }

                void setdeviceId(const uint32_t _value) {
                    m_deviceId = _value;
                }
                uint32_t getdeviceId() const {
                    return m_deviceId;
                }
                void setaccountId(const int32_t _value) {
                    m_accountId = _value;
                }
                int32_t getaccountId() const {
                    return m_accountId;
                }
                void setconnected(const bool _value) {
                    m_connected = _value;
                }
                bool getconnected() const {
                    return m_connected;
                }
                void setsupportedMessageTypes(const uint8_t _value) {
                    m_supportedMessageTypes = _value;
                }
                uint8_t getsupportedMessageTypes() const {
                    return m_supportedMessageTypes;
                }
                void setmapSupportedFeatures(const uint32_t _value) {
                    m_mapSupportedFeatures = _value;
                }
                uint32_t getmapSupportedFeatures() const {
                    return m_mapSupportedFeatures;
                }
                void settitle(const ipl::string* _value) {
                    if (m_title)
                        delete m_title;
                    if (_value) {
                        m_title = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_title = nullptr;
                    }
                }
                const ipl::string* gettitle() const {
                    return m_title;
                }
                    bool titleValid() const {
                        return m_title != nullptr;
                    }


        /**
            * Device identifier.
        */
        /**
            * Device identifier.
        */
        uint32_t m_deviceId;
        /**
            * Account identifier.
        */
        /**
            * Account identifier.
        */
        int32_t m_accountId;
        /**
            *
       * Describes the connect state of the account.
       * (true: connected - false: disconnected)
        */
        /**
            *
       * Describes the connect state of the account.
       * (true: connected - false: disconnected)
        */
        bool m_connected;
        /**
            * Bitmask of supported features. (ACCOUNT_FEATURE_EMAIL, ACCOUNT_FEATURE_SMS_GSM, ...)
        */
        /**
            * Bitmask of supported features. (ACCOUNT_FEATURE_EMAIL, ACCOUNT_FEATURE_SMS_GSM, ...)
        */
        uint8_t m_supportedMessageTypes;
        uint32_t m_mapSupportedFeatures;
    private:
        /**
            * Account name.
        */
        ipl::string* m_title;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::MapAccount& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapAccount &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging

#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPACCOUNT_CSTYLE_HXX
