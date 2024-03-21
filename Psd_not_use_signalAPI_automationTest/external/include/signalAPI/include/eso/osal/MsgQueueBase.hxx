/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_MSGQUEUEBASE_HXX
#define OSAL_MSGQUEUEBASE_HXX

#include <ipl_config.h>

#if defined (IPL_OS_ANDROID)
#include "android/MsgQueueDefs.hxx"
#elif defined (IPL_OS_LINUX) || defined (IPL_OS_QNX)
#include "posix/MsgQueueDefs.hxx"
#elif defined (IPL_OS_WINPC)
#include "winpc/MsgQueueDefs.hxx"
#else
#error "error undefined IPL_OS_ variant"
#endif

#include <common/NonCopyable.hxx>

#include <osal/osal.hxx>
#include <osal/Time.hxx>

namespace osal {

    /**
    * \brief
    *     base class for the message queue IPC facility

    *     A message queue is a unidirectional communication channel, somewhat
    *     similar to a pipe. The basic differences are:
    *
    *     - message queues are always named and can thus be used for IPC between
    *     different processes
    *     - message queues process complete messages instead of unknown chunks
    *     of data
    *     - message queues can apply priorities to messages and deliver them
    *     accordingly
    *
    *    communication via message queues is reliable and ordered according to
    *    the appointed priorities.
    *
    *    A message queue is associated with a maximum message size upon
    *    creation. Messages written to the queue must not be larger than that
    *    size. Message buffers used during receiving from the queue must be at
    *    least as large as that size.
    *
    *    Also a maximum number of messages is set at that time. The maximum
    *    number of messages determines how many messages can be written to the
    *    queue without the writer(s) to block. They will only be unblocked when
    *    a reader takes messages out of the queue.
    **/
    class OSAL_EXPORT MsgQueueBase :
        public ipl::NonCopyable
    {
    public: // types

        /**
        * \brief
        *     Structure for a single message in a queue
        **/
        struct Message
        {
            //! the actual message content
            char *data;
            //! the length of the message in \c data, in bytes
            size_t length;
            //! the message priority
            QueuePriority prio;

            Message() :
                data(),
                length(),
                prio()
            {}
        };

        static const int TIMEOUT = 1;
        static const int SUCCESS = 0;
        static const int ERROR = -1;

    public: // functions

        MsgQueueBase() :
            m_handle()
        {}

        virtual ~MsgQueueBase()
        {
            if( this->isValid() && MsgQueueBase::close() ) // BRANCH_COVERAGE_UNTESTABLE
            {
                IPL_WARN("error closing message queue");
                ipl_error.ack();
            }
        }

        bool readMsg(Message *msg);
        int readMsgTimeout(Message *msg, const osal::TimeT &max);
        bool writeMsg(const Message *msg);
        int writeMsgTimeout(const Message *msg, const osal::TimeT &max);

        /**
        * \brief
        *     Returns the maximum message size for the currently opened
        *     queue
        **/
        size_t maxMsgSize();

        /**
        * \brief
        *     Returns the maximum message count for the currently opened
        *     queue
        **/
        size_t maxMsgCount();

        /**
        * \brief
        *     Returns the number of messages currently present in the queue
        * \note
        *     This number can change at any time if other threads read or
        *     write messages to the queue. If there's only one reader or
        *     writer thread then this value can be used to determine whether
        *     reading or writing to the queue might block or not.
        **/
        size_t availMsgs();

        /**
        * \brief
        *     Closes any opened message queue

        *     After the close operation no more messages can be sent or
        *     received until another queue has been attached to.
        * \return
        *     \c true on error, \c false on success
        **/
        virtual bool close();

        bool isValid() const
        {
            return m_handle.isValid();
        }

    public: // static functions

        /**
        * \brief
        *     Returns the minimum priority value supported by the system
        **/
        static QueuePriority getMinPrio();

        /**
        * \brief
        *     Returns the maximum priority value supported by the system
        **/
        static QueuePriority getMaxPrio();

        /**
        * \brief
        *     Returns the number of distinct priority values available for
        *     message queueing.
        **/
        static size_t getNumPrios()
        {
            return getMaxPrio() - getMinPrio();
        }

        /**
        * \brief
        *     Returns the maximum queue message size supported by the system

        *     This call may return zero which means that there are no limits
        *     or no known limits. You can attempt any size parameter during
        *     a MsgQueueServer::create() call and the call will fail if the
        *     system cannot fullfil the request.
        **/
        static size_t systemMaxMsgSize();

        /**
        * \brief
        *     Returns the maximum queue length supported by the system

        *     This call may return zero which means that there are no limits
        *     or no known limits.
        **/
        static size_t systemMaxMsgCount();

    protected:
        MsgQueueHandle m_handle;
    };

};  // end of namespace osal

#endif
