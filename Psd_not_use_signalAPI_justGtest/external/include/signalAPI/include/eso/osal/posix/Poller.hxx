/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_POSIX_POLLER_HXX
#define OSAL_POSIX_POLLER_HXX
/*****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_POSIX
#error Only valid on Posix
#endif

#include <osal/osal_dso.h>

#include <threadsafe/Mutex.hxx>
#include <common/Shared.hxx>
#include <common/types/vector.hxx>
// #include <common/types/map.hxx>
#include <common/types/list.hxx>

#include <poll.h>

/*****************************************************************************/

namespace osal {

/*****************************************************************************/

    /*!
        \brief Convenient Wrapper around poll() system call
        
        Add Clients (file descriptors) to be polled via add(),
        wait for something to happen and call callbacks with poll().
    */
    class OSAL_EXPORT Poller {
        
    public:
        
        class Client;
        
        Poller();
        ~Poller();
        
        //! \brief Wait once for something to happen and call all needed handlers
        bool poll();
        //! \brief Add another file descriptor/handler
        void add(Client &client, int fd);
        //! \brief Remove a handler
        void remove(const Client &client);
        //! \brief Remove a file descriptor
        void remove(int fd);
        //! \brief Make poll() return, unsuccessfully
        void stop();
        
        static ipl::Shared<Poller> DEFAULT;

    protected:
        
        enum Command { STOP, RESCAN };
        
        struct Subscription {
            Client *client;
            int fd;
            Subscription(Client *client, int fd): client(client), fd(fd) {}
            bool operator == (const Subscription &other) const {
                return client==other.client && fd==other.fd;
            }
        };

        int self_pipe[2];

        threadsafe::Mutex mutex;
        typedef std::list<Subscription> Subscriptions;
        Subscriptions add_us;
        Subscriptions remove_us;
        Subscriptions subscriptions;
        
        typedef std::vector<pollfd> PollFds;
        PollFds poll_fds;  // must only be touched by poll()!
    };

/*****************************************************************************/

    class Poller::Client {
        
    public:
        virtual ~Client();
        
        //! \brief What events to poll for, some combination of POLLIN, POLLOUT
        //!
        //! While calling this the Poller \e might \e hold some internal locks.
        virtual short poll_events(int fd);
        //! \brief Gets called on POLLIN event
        //!
        //! While calling this the Poller \e does \e not hold any internal locks.
        virtual void read(int fd);
        //! \brief Gets called on POLLOUT event
        //!
        //! While calling this the Poller \e does \e not hold any internal locks.
        virtual void write(int fd);
        //! \brief Gets called on any error during polling
        //!
        //! \a fd is removed from polling and you should close it.
        //!
        //! While calling this the Poller \e does \e not hold any internal locks.
        virtual void error(int fd)=0;
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/
#endif
