/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_WATCHDOGMISSEDEVENT_HXX
#define SERVMNGT_EXTENSIONS_WATCHDOGMISSEDEVENT_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace servmngt
{
namespace extensions
{

    /**
    \brief struct extensions::WatchdogMissedEvent.
    */
    struct PROXY_EXPORT WatchdogMissedEvent
    {
        int64_t timestamp; // optional=False
        CIPtr< CIString > appName; // optional=True
        uint64_t count; // optional=False
        private:
            WatchdogMissedEvent()
            :
            timestamp(),
            appName(),
            count()
            { }
            friend class WatchdogMissedEventFactory;
            friend class CIFactory<WatchdogMissedEvent>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<servmngt::extensions::WatchdogMissedEvent> >;
            friend class ipl::vector<WatchdogMissedEvent>;
            friend class ipl::allocator<WatchdogMissedEvent>;
#endif
    };

    typedef CIPtrArray<WatchdogMissedEvent> CIWatchdogMissedEventArray;

    /** \brief factory for extensions::WatchdogMissedEvent. */
    class PROXY_EXPORT WatchdogMissedEventFactory  : CIFactory<WatchdogMissedEvent> {
    public:
        static inline CIPtr<WatchdogMissedEvent> createWatchdogMissedEvent() {
            return CIFactory<WatchdogMissedEvent>::createObject();
        }
        static inline void createWatchdogMissedEvent(CIPtr<WatchdogMissedEvent> & s) {
            CIFactory<WatchdogMissedEvent>::createObject(s);
        }
        static inline CIPtr<CIWatchdogMissedEventArray> createWatchdogMissedEventArray(size_t size) {
            return CIFactory<WatchdogMissedEvent>::createArray(size);
        }
        static inline void createWatchdogMissedEventArray(CIPtr<CIWatchdogMissedEventArray>& a, size_t size) {
            CIFactory<WatchdogMissedEvent>::createArray(a, size);
        }
    };
}//namespace servmngt
}//namespace extensions


#endif// SERVMNGT_EXTENSIONS_WATCHDOGMISSEDEVENT_HXX
