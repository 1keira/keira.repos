/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef OSAL_IPCAPI_HXX
#define OSAL_IPCAPI_HXX

namespace osal
{

/**
 * \brief
 *     Helper construct for being able to import the contained enum
 *     definition into multiple other class definitions via 'using'
 **/
struct Creatable
{

    /**
     * \brief
     *     Different strategies for what to do if a named IPC object
     *     already exists

     *     On POSIX systems IPC objects can be persistent even if nobody
     *     is using them anymore. This raises the problem what to do if
     *     an IPC object of a certain name is already there upon the
     *     attempt to create it.
     *
     *     Via this enum different strategies can be selected in that
     *     event. This applies to different IPC mechanisms like shared
     *     memory, semaphores and message queues.
     **/
    enum CreationStrategy
    {
        /**
         * \brief
         *     Fail if the IPC object already exists

         *     This is the default behaviour if not explicitly
         *     selected otherwise
         **/
        FAIL_IF_EXISTS,
        /**
         * \brief
         *     Attach to an existing IPC object without altering it

         *     In this case if the object already exists then it will
         *     be attached to without changing any of its properties.
         *
         *     This means that the initial IPC object state is
         *     undefined and your application might need to deal with
         *     an unknown number of processes still/already working
         *     with the object
         **/
        ATTACH_IF_EXISTS,
        /**
         * \brief
         *     Remove an existing IPC object and create a pristine
         *     one

         *     This only works on POSIX systems as on WIN32 semaphore
         *     objects always have users left if they still exist,
         *     they also cannot be removed or renamed. Thus on WIN32
         *     this strategy behaves like FAIL_IF_EXISTS.
         *
         *     On POSIX systems an existing object will be removed.
         *     If no users of the existing object are left then the
         *     semaphore will be removed from the system. If users
         *     are left then the already existing semaphore will
         *     remain valid for that users but no new users can
         *     attach to the object via its name (but possibly by
         *     other means, e.g.  by direct file descriptor usage).
         *
         *     Then a new semaphore object under the same name will
         *     be created. Users that intend to open the old object
         *     by name will then get the new object instead.
         **/
        REMOVE_IF_EXISTS,
        /**
         * \brief
         *     Attach to the existing IPC object and resize the
         *     object to the given size

         *    Like REMOVE_IF_EXISTS this strategy only works on
         *    POSIX systems. It behaves like ATTACH_IF_EXISTS but
         *    additionaly changes the IPC object in its size to the
         *    size desired.
         *
         *    This can be dangerous if there are still users of the
         *    IPC object that aren't informed of that situation,
         *    especially if the existing object is reduced in size.
         *    Any already mapped memory areas may cause pagefaults
         *    for that users in the future (in the case of shared
         *    memory).
         **/
        RESIZE_IF_EXISTS
    }; // end enum

}; // end struct

} // end ns

#endif
