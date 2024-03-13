/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPHEADERENTRY_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPHEADERENTRY_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/messaging/cstyle/Definitions.hxx>
#include <asi/connectivity/al/messaging/cstyle/Definitions.hxx>

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
struct MapHeaderEntry;
}
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::messaging::cstyle::MapHeaderEntry& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapHeaderEntry &val);
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
        
    * MAP header entry of header listing
    
    */
    struct PROXY_EXPORT MapHeaderEntry
    {
        public:
            MapHeaderEntry()
            : m_type()
            , m_messageSize()
            , m_text()
            , m_receptionStatus()
            , m_attachmentSize()
            , m_priority()
            , m_readStatus()
            , m_transmitted()
            , m_is_protected()
            , m_messageId(nullptr)
            , m_subject(nullptr)
            , m_datetime(nullptr)
            , m_senderName(nullptr)
            , m_senderAddress(nullptr)
            , m_replyAddress(nullptr)
            , m_recipientName(nullptr)
            , m_recipientAddress(nullptr)
            { }

            MapHeaderEntry (const MapHeaderEntry& other)
            : m_type()
            , m_messageSize()
            , m_text()
            , m_receptionStatus()
            , m_attachmentSize()
            , m_priority()
            , m_readStatus()
            , m_transmitted()
            , m_is_protected()
            , m_messageId(nullptr)
            , m_subject(nullptr)
            , m_datetime(nullptr)
            , m_senderName(nullptr)
            , m_senderAddress(nullptr)
            , m_replyAddress(nullptr)
            , m_recipientName(nullptr)
            , m_recipientAddress(nullptr)
            {
              *this = other;
            }

            ~MapHeaderEntry () {
                if (m_messageId) {
                    delete m_messageId;
                }
                if (m_subject) {
                    delete m_subject;
                }
                if (m_datetime) {
                    delete m_datetime;
                }
                if (m_senderName) {
                    delete m_senderName;
                }
                if (m_senderAddress) {
                    delete m_senderAddress;
                }
                if (m_replyAddress) {
                    delete m_replyAddress;
                }
                if (m_recipientName) {
                    delete m_recipientName;
                }
                if (m_recipientAddress) {
                    delete m_recipientAddress;
                }
            }
            bool operator==(const MapHeaderEntry& rhs) const {
                bool equal = true;
                if (m_messageId == nullptr && rhs.m_messageId != nullptr)
                    equal = false;
                else if (m_messageId != nullptr && rhs.m_messageId == nullptr)
                    equal = false;
                else if ((m_messageId != nullptr) && (rhs.m_messageId != nullptr) && (*m_messageId != *rhs.m_messageId))
                    equal = false;
                if (m_subject == nullptr && rhs.m_subject != nullptr)
                    equal = false;
                else if (m_subject != nullptr && rhs.m_subject == nullptr)
                    equal = false;
                else if ((m_subject != nullptr) && (rhs.m_subject != nullptr) && (*m_subject != *rhs.m_subject))
                    equal = false;
                if (m_datetime == nullptr && rhs.m_datetime != nullptr)
                    equal = false;
                else if (m_datetime != nullptr && rhs.m_datetime == nullptr)
                    equal = false;
                else if ((m_datetime != nullptr) && (rhs.m_datetime != nullptr) && (*m_datetime != *rhs.m_datetime))
                    equal = false;
                if (m_senderName == nullptr && rhs.m_senderName != nullptr)
                    equal = false;
                else if (m_senderName != nullptr && rhs.m_senderName == nullptr)
                    equal = false;
                else if ((m_senderName != nullptr) && (rhs.m_senderName != nullptr) && (*m_senderName != *rhs.m_senderName))
                    equal = false;
                if (m_senderAddress == nullptr && rhs.m_senderAddress != nullptr)
                    equal = false;
                else if (m_senderAddress != nullptr && rhs.m_senderAddress == nullptr)
                    equal = false;
                else if ((m_senderAddress != nullptr) && (rhs.m_senderAddress != nullptr) && (*m_senderAddress != *rhs.m_senderAddress))
                    equal = false;
                if (m_replyAddress == nullptr && rhs.m_replyAddress != nullptr)
                    equal = false;
                else if (m_replyAddress != nullptr && rhs.m_replyAddress == nullptr)
                    equal = false;
                else if ((m_replyAddress != nullptr) && (rhs.m_replyAddress != nullptr) && (*m_replyAddress != *rhs.m_replyAddress))
                    equal = false;
                if (m_recipientName == nullptr && rhs.m_recipientName != nullptr)
                    equal = false;
                else if (m_recipientName != nullptr && rhs.m_recipientName == nullptr)
                    equal = false;
                else if ((m_recipientName != nullptr) && (rhs.m_recipientName != nullptr) && (*m_recipientName != *rhs.m_recipientName))
                    equal = false;
                if (m_recipientAddress == nullptr && rhs.m_recipientAddress != nullptr)
                    equal = false;
                else if (m_recipientAddress != nullptr && rhs.m_recipientAddress == nullptr)
                    equal = false;
                else if ((m_recipientAddress != nullptr) && (rhs.m_recipientAddress != nullptr) && (*m_recipientAddress != *rhs.m_recipientAddress))
                    equal = false;
                if (m_type != rhs.m_type)
                    equal = false;
                if (m_messageSize != rhs.m_messageSize)
                    equal = false;
                if (m_text != rhs.m_text)
                    equal = false;
                if (m_receptionStatus != rhs.m_receptionStatus)
                    equal = false;
                if (m_attachmentSize != rhs.m_attachmentSize)
                    equal = false;
                if (m_priority != rhs.m_priority)
                    equal = false;
                if (m_readStatus != rhs.m_readStatus)
                    equal = false;
                if (m_transmitted != rhs.m_transmitted)
                    equal = false;
                if (m_is_protected != rhs.m_is_protected)
                    equal = false;
                return equal;
            }
            bool operator!=(const MapHeaderEntry& rhs) const {
                return !operator==(rhs);
            }

            MapHeaderEntry& operator = (const MapHeaderEntry& src) {
                if (this == &src) return *this;
                if (m_messageId)
                    delete m_messageId;
                if (src.m_messageId) {
                    m_messageId = new (ipl::nothrow)ipl::string(*(src.m_messageId));
                } else {
                    m_messageId = nullptr;
                }
                if (m_subject)
                    delete m_subject;
                if (src.m_subject) {
                    m_subject = new (ipl::nothrow)ipl::string(*(src.m_subject));
                } else {
                    m_subject = nullptr;
                }
                if (m_datetime)
                    delete m_datetime;
                if (src.m_datetime) {
                    m_datetime = new (ipl::nothrow)ipl::string(*(src.m_datetime));
                } else {
                    m_datetime = nullptr;
                }
                if (m_senderName)
                    delete m_senderName;
                if (src.m_senderName) {
                    m_senderName = new (ipl::nothrow)ipl::string(*(src.m_senderName));
                } else {
                    m_senderName = nullptr;
                }
                if (m_senderAddress)
                    delete m_senderAddress;
                if (src.m_senderAddress) {
                    m_senderAddress = new (ipl::nothrow)ipl::string(*(src.m_senderAddress));
                } else {
                    m_senderAddress = nullptr;
                }
                if (m_replyAddress)
                    delete m_replyAddress;
                if (src.m_replyAddress) {
                    m_replyAddress = new (ipl::nothrow)ipl::string(*(src.m_replyAddress));
                } else {
                    m_replyAddress = nullptr;
                }
                if (m_recipientName)
                    delete m_recipientName;
                if (src.m_recipientName) {
                    m_recipientName = new (ipl::nothrow)ipl::string(*(src.m_recipientName));
                } else {
                    m_recipientName = nullptr;
                }
                if (m_recipientAddress)
                    delete m_recipientAddress;
                if (src.m_recipientAddress) {
                    m_recipientAddress = new (ipl::nothrow)ipl::string(*(src.m_recipientAddress));
                } else {
                    m_recipientAddress = nullptr;
                }
                m_type = src.m_type;
                m_messageSize = src.m_messageSize;
                m_text = src.m_text;
                m_receptionStatus = src.m_receptionStatus;
                m_attachmentSize = src.m_attachmentSize;
                m_priority = src.m_priority;
                m_readStatus = src.m_readStatus;
                m_transmitted = src.m_transmitted;
                m_is_protected = src.m_is_protected;
                return *this;
            }

                void setmessageId(const ipl::string* _value) {
                    if (m_messageId)
                        delete m_messageId;
                    if (_value) {
                        m_messageId = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_messageId = nullptr;
                    }
                }
                const ipl::string* getmessageId() const {
                    return m_messageId;
                }
                    bool messageIdValid() const {
                        return m_messageId != nullptr;
                    }
                void setsubject(const ipl::string* _value) {
                    if (m_subject)
                        delete m_subject;
                    if (_value) {
                        m_subject = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_subject = nullptr;
                    }
                }
                const ipl::string* getsubject() const {
                    return m_subject;
                }
                    bool subjectValid() const {
                        return m_subject != nullptr;
                    }
                void setdatetime(const ipl::string* _value) {
                    if (m_datetime)
                        delete m_datetime;
                    if (_value) {
                        m_datetime = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_datetime = nullptr;
                    }
                }
                const ipl::string* getdatetime() const {
                    return m_datetime;
                }
                    bool datetimeValid() const {
                        return m_datetime != nullptr;
                    }
                void setsenderName(const ipl::string* _value) {
                    if (m_senderName)
                        delete m_senderName;
                    if (_value) {
                        m_senderName = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_senderName = nullptr;
                    }
                }
                const ipl::string* getsenderName() const {
                    return m_senderName;
                }
                    bool senderNameValid() const {
                        return m_senderName != nullptr;
                    }
                void setsenderAddress(const ipl::string* _value) {
                    if (m_senderAddress)
                        delete m_senderAddress;
                    if (_value) {
                        m_senderAddress = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_senderAddress = nullptr;
                    }
                }
                const ipl::string* getsenderAddress() const {
                    return m_senderAddress;
                }
                    bool senderAddressValid() const {
                        return m_senderAddress != nullptr;
                    }
                void setreplyAddress(const ipl::string* _value) {
                    if (m_replyAddress)
                        delete m_replyAddress;
                    if (_value) {
                        m_replyAddress = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_replyAddress = nullptr;
                    }
                }
                const ipl::string* getreplyAddress() const {
                    return m_replyAddress;
                }
                    bool replyAddressValid() const {
                        return m_replyAddress != nullptr;
                    }
                void setrecipientName(const ipl::string* _value) {
                    if (m_recipientName)
                        delete m_recipientName;
                    if (_value) {
                        m_recipientName = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_recipientName = nullptr;
                    }
                }
                const ipl::string* getrecipientName() const {
                    return m_recipientName;
                }
                    bool recipientNameValid() const {
                        return m_recipientName != nullptr;
                    }
                void setrecipientAddress(const ipl::string* _value) {
                    if (m_recipientAddress)
                        delete m_recipientAddress;
                    if (_value) {
                        m_recipientAddress = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_recipientAddress = nullptr;
                    }
                }
                const ipl::string* getrecipientAddress() const {
                    return m_recipientAddress;
                }
                    bool recipientAddressValid() const {
                        return m_recipientAddress != nullptr;
                    }
                void settype(const asi::connectivity::al::messaging::cstyle::MapMessageType _value) {
                    m_type = _value;
                }
                asi::connectivity::al::messaging::cstyle::MapMessageType gettype() const {
                    return m_type;
                }
                void setmessageSize(const uint32_t _value) {
                    m_messageSize = _value;
                }
                uint32_t getmessageSize() const {
                    return m_messageSize;
                }
                void settext(const bool _value) {
                    m_text = _value;
                }
                bool gettext() const {
                    return m_text;
                }
                void setreceptionStatus(const uint8_t _value) {
                    m_receptionStatus = _value;
                }
                uint8_t getreceptionStatus() const {
                    return m_receptionStatus;
                }
                void setattachmentSize(const uint32_t _value) {
                    m_attachmentSize = _value;
                }
                uint32_t getattachmentSize() const {
                    return m_attachmentSize;
                }
                void setpriority(const asi::connectivity::al::messaging::cstyle::MapMessagePriority _value) {
                    m_priority = _value;
                }
                asi::connectivity::al::messaging::cstyle::MapMessagePriority getpriority() const {
                    return m_priority;
                }
                void setreadStatus(const bool _value) {
                    m_readStatus = _value;
                }
                bool getreadStatus() const {
                    return m_readStatus;
                }
                void settransmitted(const bool _value) {
                    m_transmitted = _value;
                }
                bool gettransmitted() const {
                    return m_transmitted;
                }
                void setis_protected(const bool _value) {
                    m_is_protected = _value;
                }
                bool getis_protected() const {
                    return m_is_protected;
                }


        asi::connectivity::al::messaging::cstyle::MapMessageType m_type;
        uint32_t m_messageSize;
        bool m_text;
        /**
            * uint8: 0: complete 1: fractioned 2: notification
        */
        /**
            * uint8: 0: complete 1: fractioned 2: notification
        */
        uint8_t m_receptionStatus;
        uint32_t m_attachmentSize;
        asi::connectivity::al::messaging::cstyle::MapMessagePriority m_priority;
        /**
            * bool: Message read status (decimal, 1=read, 0=unread).
        */
        /**
            * bool: Message read status (decimal, 1=read, 0=unread).
        */
        bool m_readStatus;
        bool m_transmitted;
        bool m_is_protected;
    private:
        ipl::string* m_messageId;
        ipl::string* m_subject;
        ipl::string* m_datetime;
        ipl::string* m_senderName;
        ipl::string* m_senderAddress;
        ipl::string* m_replyAddress;
        ipl::string* m_recipientName;
        ipl::string* m_recipientAddress;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::MapHeaderEntry& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapHeaderEntry &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging

#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPHEADERENTRY_CSTYLE_HXX
