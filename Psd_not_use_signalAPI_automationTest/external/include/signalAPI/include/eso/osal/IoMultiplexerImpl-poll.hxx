/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_IOMULTIPLEXERIMPL_POLL_HXX
#define OSAL_IOMULTIPLEXERIMPL_POLL_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifdef USE_EPOLL
#error Only valid if epoll is not available
#elif !defined IPL_OS_POSIX && !defined IPL_OS_INTEGRITY
#error Only valid on Posix / Integrity OS
#endif

#include <osal/osal_dso.h>
#include "IoMultiplexerBase.hxx"

/****************************************************************************/

namespace osal {

/****************************************************************************/

/*!
    \internal Posix implementation for IoMultiplexer
*/
class OSAL_EXPORT IoMultiplexerImpl {
    
public:
    
    class Channel;
    using Client=IoMultiplexerBase::Client;
    class Impl;
};


/****************************************************************************/

class OSAL_EXPORT IoMultiplexerImpl::Channel:
    public IoMultiplexerBase::Channel {
public:
    using Fd=SocketHandle::socket_type;
    struct SocketPair
    {
        Fd rxfd;
        Fd txfd;
    };
    virtual SocketPair fds() const IPL_NOEXCEPT=0;
    /*! \brief
        return whether the socket can be used with poll functionality,
        e.g. IoMultiplexer or IoUring
    */
    virtual bool isPollable() const IPL_NOEXCEPT { return true; }
};

/****************************************************************************/

    class OSAL_EXPORT IoMultiplexerImpl::Impl:
        public IoMultiplexerImpl,
        public IoMultiplexerBase::Impl<IoMultiplexerImpl::Channel> {
            
    public:
        
        using Channel=IoMultiplexerImpl::Channel;
        using Client=IoMultiplexerImpl::Client;
        
        Impl() IPL_NOEXCEPT;
        ~Impl() IPL_NOEXCEPT override;
        
        void run() IPL_NOEXCEPT;
        
    protected:
        void update(threadsafe::Mutex::Guard &) override;
        
        //! \brief Used by update() to wake up main loop
        int self_pipe[2];  // or event fd (the same, twice) under Linux
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
