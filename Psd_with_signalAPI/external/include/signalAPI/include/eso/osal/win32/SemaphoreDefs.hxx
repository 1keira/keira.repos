/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_POSIX_SEMAPHOREDEFS_HXX
#define OSAL_POSIX_SEMAPHOREDEFS_HXX

namespace osal {

    struct SemaphoreHandle
    {
        //! \brief
        //! just a file descriptor, not all operations may be allowed on
        //! it like on e.g. select on socket fds
        HANDLE sem;

        SemaphoreHandle()
        {
            invalidate();
        }

        bool isValid() const
        {
            return sem != INVALID_HANDLE_VALUE;
        }

        void invalidate()
        {
            sem = INVALID_HANDLE_VALUE;
        }
    };

    struct SemaphoreCreatorHandle
    {
        SemaphoreCreatorHandle(const bool doc)
        {
            (void)doc;
            // currently nothing needed on WIN32
        }
    };

}  // end of namespace osal

#endif
