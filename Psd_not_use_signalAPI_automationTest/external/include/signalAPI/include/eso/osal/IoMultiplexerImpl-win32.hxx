/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_IOMULTIPLEXERIMPL_WIN32_HXX
#define OSAL_IOMULTIPLEXERIMPL_WIN32_HXX
/****************************************************************************/

#include <ipl_config.h>

#if !defined IPL_OS_WIN32
#error Only valid on Windows
#endif

#include <osal/osal_dso.h>
#include "IoMultiplexerBase.hxx"

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal Windows implementation for IoMultiplexer
    */
    class OSAL_EXPORT IoMultiplexerImpl {
        
    public:
        
        class Channel;
        using Client = IoMultiplexerBase::Client;
        class Impl;
    };

/****************************************************************************/

    class OSAL_EXPORT IoMultiplexerImpl::Channel:
        public IoMultiplexerBase::Channel {

    public:
        static const uint32_t EVENT_READ = 1 << 0;
        static const uint32_t EVENT_WRITE = 1 << 1;
        static const uint32_t EVENT_CONNECT = 1 << 2;
        static const uint32_t EVENT_CLOSE = 1 << 3;
        static const uint32_t EVENT_ERROR = 1 << 4;

        virtual ~Channel() IPL_NOEXCEPT = default;
        /**
        * Set the events to poll for. EVENT_CLOSE and EVENT_ERROR are always polled.
        */
        void setPollEvents(uint32_t events) IPL_NOEXCEPT;
        struct EventPair
        {
            WSAEVENT rxevt;
            WSAEVENT txevt;
        };
        virtual EventPair events() const IPL_NOEXCEPT = 0;
        virtual uint32_t parseEvents(WSAEVENT handle, short poll_events) const = 0;
        virtual void closeHandle(WSAEVENT handle) const IPL_NOEXCEPT;
        bool isWritable() const IPL_NOEXCEPT;

        /*! \brief
            return whether the socket can be used with poll functionality,
            e.g. IoMultiplexer or IoUring
        */
        virtual bool isPollable() const IPL_NOEXCEPT { return true; }

    protected:
        uint32_t poll_events;
        mutable bool writable;
    };

    class OSAL_EXPORT IoMultiplexerImpl::Impl:
        public IoMultiplexerImpl,
        public IoMultiplexerBase::Impl<IoMultiplexerImpl::Channel> {
    public:
        using Channel = IoMultiplexerImpl::Channel;

        Impl() IPL_NOEXCEPT;
        ~Impl() IPL_NOEXCEPT;

        void run() IPL_NOEXCEPT;
    protected:
        void update(threadsafe::Mutex::Guard &) override;
        WSAEVENT wakeup_handle;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
