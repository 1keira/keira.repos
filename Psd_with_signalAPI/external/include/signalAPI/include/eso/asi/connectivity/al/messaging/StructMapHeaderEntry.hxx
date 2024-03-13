/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPHEADERENTRY_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPHEADERENTRY_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/messaging/Definitions.hxx>
#include <asi/connectivity/al/messaging/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{

    /**
        
    * MAP header entry of header listing
    
    */
    struct PROXY_EXPORT MapHeaderEntry
    {
        CIPtr< CIString > messageId; // optional=True
        CIPtr< CIString > subject; // optional=True
        CIPtr< CIString > datetime; // optional=True
        CIPtr< CIString > senderName; // optional=True
        CIPtr< CIString > senderAddress; // optional=True
        CIPtr< CIString > replyAddress; // optional=True
        CIPtr< CIString > recipientName; // optional=True
        CIPtr< CIString > recipientAddress; // optional=True
        asi::connectivity::al::messaging::MapMessageType type; // optional=False
        uint32_t messageSize; // optional=False
        bool text; // optional=False
        /**
            * uint8: 0: complete 1: fractioned 2: notification
        */
        uint8_t receptionStatus; // optional=False
        uint32_t attachmentSize; // optional=False
        asi::connectivity::al::messaging::MapMessagePriority priority; // optional=False
        /**
            * bool: Message read status (decimal, 1=read, 0=unread).
        */
        bool readStatus; // optional=False
        bool transmitted; // optional=False
        bool is_protected; // optional=False
        private:
            MapHeaderEntry()
            :
            messageId(),
            subject(),
            datetime(),
            senderName(),
            senderAddress(),
            replyAddress(),
            recipientName(),
            recipientAddress(),
            type(),
            messageSize(),
            text(),
            receptionStatus(),
            attachmentSize(),
            priority(),
            readStatus(),
            transmitted(),
            is_protected()
            { }
            friend class MapHeaderEntryFactory;
            friend class CIFactory<MapHeaderEntry>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::messaging::MapHeaderEntry> >;
            friend class ipl::vector<MapHeaderEntry>;
            friend class ipl::allocator<MapHeaderEntry>;
#endif
    };

    typedef CIPtrArray<MapHeaderEntry> CIMapHeaderEntryArray;

    /** \brief factory for messaging::MapHeaderEntry. */
    class PROXY_EXPORT MapHeaderEntryFactory  : CIFactory<MapHeaderEntry> {
    public:
        static inline CIPtr<MapHeaderEntry> createMapHeaderEntry() {
            return CIFactory<MapHeaderEntry>::createObject();
        }
        static inline void createMapHeaderEntry(CIPtr<MapHeaderEntry> & s) {
            CIFactory<MapHeaderEntry>::createObject(s);
        }
        static inline CIPtr<CIMapHeaderEntryArray> createMapHeaderEntryArray(size_t size) {
            return CIFactory<MapHeaderEntry>::createArray(size);
        }
        static inline void createMapHeaderEntryArray(CIPtr<CIMapHeaderEntryArray>& a, size_t size) {
            CIFactory<MapHeaderEntry>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging


#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPHEADERENTRY_HXX
