/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_MSGQUEUESERVER_HXX
#define OSAL_MSGQUEUESERVER_HXX

#include <common/NonCopyable.hxx>

#include <osal/osal.hxx>
#include <osal/IPC.hxx>
#include <osal/UnicodeString.hxx>
#include <osal/MsgQueueBase.hxx>

namespace osal {

    /**
    * \brief
    *
    **/
    class OSAL_EXPORT MsgQueueServer :
        public MsgQueueBase,
        public Creatable
    {
    public: // functions

        /**
        * \brief
        *     Construct an invalid MsgQueueServer

        *     The constructor will not yet create or attach any message
        *     queue. This is done via the create() member function.
        * \param[in] delete_on_close
        *     If set to \c true then a currently opened message queue will
        *     be removed from the file system upon closing the object.
        **/
        MsgQueueServer(const bool delete_on_close = true) :
            m_server_handle(delete_on_close)
        {}

        /**
        * \brief
        *     Delete the Message Queue identifier from the file system
        **/
        bool deleteName();

        /**
        * \brief
        *     Detach from a currently opened message queue and possibly
        *     delete it from the file system
        **/
        bool close();

        /**
        * \brief
        *     Create a new Message Queue Object in the System

        *     According to \c strategy a new message queue object will be
        *     created using \c name as a label.
        *
        *     If \c strategy is set to ATTACH_IF_EXISTS then if a message
        *     queue already existed under \c name the properties of the
        *     existing queue will be kept and \c max_msg_size and \c
        *     max_msg_count aren't applied. Query the actual queue
        *     parameters from MsgQueueBase after successfull attachment in
        *     that case.
        * \param[in] max_msg_size
        *     Determines the maximum message size for a message transmitted
        *     via the queue
        * \param[in] max_msg_count
        *     Determines the maximum number of messages that can be kept in
        *     the queue at the same time without sending processes to block
        * \param[in] strategy
        *     Determines how to deal with possibly already existing message
        *     queue objects found under \c name
        * \return
        *     \c true on error, \c false on success
        **/
        bool create(
            const char *name,
            const size_t max_msg_size,
            const size_t max_msg_count,
            const CreationStrategy &strategy = FAIL_IF_EXISTS);

        /**
        * \brief
        *     Variant of create() that takes an STL string object
        **/
        bool create(
            const ipl::string &name,
            const size_t max_msg_size,
            const size_t max_msg_count,
            const CreationStrategy &strategy = FAIL_IF_EXISTS)
        {
            return this->create(
                name.c_str(),
                max_msg_size,
                max_msg_count,
                strategy);
        }

        /**
        * \brief
        *     Variant of create() that takes an osal::UnicodeString object
        **/
        bool create(
            const osal::UnicodeString &name,
            const size_t max_msg_size,
            const size_t max_msg_count,
            const CreationStrategy &strategy = FAIL_IF_EXISTS);

    public: // static functions

        /**
        * \brief
        *     Delete the Message Queue of the given Name from the File
        *     System
        **/
        static bool deleteName(const char *name);

        /**
        * \brief
        *     Variant of deleteName(const char*) taking an STL string object
        **/
        static bool deleteName(const ipl::string &name)
        {
            return deleteName(name.c_str());
        }

        /**
        * \brief
        *     Variant of deleteName(const char*) taking an
        *     osal::UnicodeString object
        **/
        static inline bool deleteName(const osal::UnicodeString &ucs);

    protected: // data

        MsgQueueServerHandle m_server_handle;
    };

}  // end of namespace osal

#endif
