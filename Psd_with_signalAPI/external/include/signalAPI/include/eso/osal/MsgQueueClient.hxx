/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_MSGQUEUECLIENT_HXX
#define OSAL_MSGQUEUECLIENT_HXX

#include <common/NonCopyable.hxx>
#include <osal/osal.hxx>
#include <osal/MsgQueueBase.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    class OSAL_EXPORT MsgQueueClient :
        public MsgQueueBase
    {
    public: // functions

        //! creates an invalid shared memory object
        MsgQueueClient() { }

        /**
        * \brief
        *     Attach to the given Message Queue Object

        *    If currently a message queue object is already opened then
        *    first an attempt is made to close it. If closing fails then
        *    the operation will not continue and \c true is returned.
        *
        *     Regarding the requirements and semantics of \c name
        *     please have a look at MsgQueueServer::create().
        *
        *     After successful attachment to the message queue object
        *     the maximum message size and maximum queue length are
        *     queriable from MessageQueueBase.
        * \return
        *     \c true on error, \c false otherwise
        * \errorindicator
        *     via return code, via isValid()
        * \errors
        *    If close() fails then the error from it is kept.
        *    Otherwise:
        *
        *     osal::SysError with IDs:
        *
        *     - PERMISSION_DENIED if you're not allowed to access \c
        *     name at all or using the given \c access
        *     - SYSTEM_RESSOURCES_EXHAUSTED if there are too many file
        *     descriptors open in the system or process
        *
        *     osal::FileAccessError with IDs:
        *
        *     - PATH_TOO_LONG if \c name is too long
        *     - BAD_PATH if \c name isn't existing
        *
        *    ipl::CommonError with IDs:
        *
        *    - INVALID_PARAMETER if the given \c name is invalid
        *    - PAR_OUT_OF_RANGE if \c name is too long
        **/
        bool attach(const char *name);

        //! \brief
        //! variant of attach(const char*, const
        //! MemMapping::MemAccessFlags&) taking an STL string
        bool attach(const ipl::string &name)
        {
            return this->attach(name.c_str());
        }

        //! \brief
        //! variant of attach(const char*, const
        //! MemMapping::MemAccessFlags&) taking a unicode string
        bool attach(const osal::UnicodeString &name);
    };

};  // end of namespace osal

#endif
