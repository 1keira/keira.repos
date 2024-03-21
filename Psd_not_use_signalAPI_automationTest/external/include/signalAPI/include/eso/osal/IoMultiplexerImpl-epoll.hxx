/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_IOMULTIPLEXERIMPL_EPOLL_HXX
#define OSAL_IOMULTIPLEXERIMPL_EPOLL_HXX
/****************************************************************************/

#include <ipl_config.h>

#if !defined USE_EPOLL
#error Only valid if epoll is enabled
#endif

#include <osal/osal_dso.h>
#include "IoMultiplexerBase.hxx"

#include <list>
#include <map>
#include <set>

/****************************************************************************/

namespace osal {

/****************************************************************************/

/*!
    \internal Posix implementation for IoMultiplexer using epoll
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
        return wether the socket can be used with poll functionality,
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

    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;
    
    void run() IPL_NOEXCEPT;
    
    bool add(Channel &channel, IoMultiplexerBase::Client &client,
                bool for_read=true, bool for_write=false) IPL_NOEXCEPT override;
    void remove(Channel &channel) IPL_NOEXCEPT override;
    void remove(const IoMultiplexerBase::Client &client) IPL_NOEXCEPT override;
    
protected:
    void update(threadsafe::Mutex::Guard &) override;
    
    //! \brief Used by update() to wake up main loop
    int self_pipe[2];  // or event fd (the same, twice) under Linux
    int epoll_fd;
    bool remove_seen;
    struct EpollData
    {
        Channel::Fd rxfd{osal::SocketHandle::INVALID_SOCKET_VALUE};
        Channel::Fd txfd{osal::SocketHandle::INVALID_SOCKET_VALUE};
        Channel* channel{nullptr};
        std::list<Subscription>* subscriptions{nullptr};
        bool for_read{false};
        bool for_write{false};
    };
    //! Updates the subscriptions and epolldata structures, and modifies the Epollset accordingly
    void update(EpollData *data, IoMultiplexerBase::Client* client = nullptr, 
                                    bool remove_from_read = false, bool remove_from_write = false) IPL_NOEXCEPT;
    EpollData pipeData;
    std::map<Channel*, EpollData* > fd_mapping; // For safe deletion from epoll
    std::set<EpollData*> epoll_datas;
};

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
