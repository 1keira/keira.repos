/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_INTEGRITY_SHAREDMEMORYDEFS_HXX
#define OSAL_INTEGRITY_SHAREDMEMORYDEFS_HXX

namespace osal {


    struct SharedMemoryHandle
    {
         //! \brief
         //! just a file descriptor, not all operations may be allowed on
         //! it like on e.g. select on socket fds
           int fd;

        SharedMemoryHandle()
        {
            invalidate();
        }

        bool isValid() const
        {
             return fd != -1;
        }

        void invalidate()
        {
             fd   = -1;
        }
    };

    struct SharedMemoryServerHandle
    {
        //! the IPC identifier of the shared memory
        char identifier[NAME_MAX + 1];
        const bool del_on_close;

        SharedMemoryServerHandle(const bool doc) :
            del_on_close(doc)
        {
            invalidate();
        }

        void invalidate()
        {
            identifier[0] = '\0';
        }

        bool isValid() const
        {
            return identifier[0] != '\0';
        }
    };

}  // end of osal

#endif
