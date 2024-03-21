/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_SEMAPHOREDEFS_HXX
#define OSAL_POSIX_SEMAPHOREDEFS_HXX

#include <semaphore.h>
#include <limits.h>

namespace osal {

    struct SemaphoreHandle
    {
        // we actually get a ptr. back from sem_open but NULL is not
        // invalid, SEM_FAILED is!
        sem_t *sem;

        SemaphoreHandle()
        {
            this->invalidate();
        }

        bool isValid() const
        {
            return sem != SEM_FAILED;
        }

        void invalidate()
        {
            sem = SEM_FAILED;
        }
    };

    struct SemaphoreCreatorHandle
    {
        // mgr. additionally needs to keep the name
        char identifier[NAME_MAX + 1];
        const bool del_on_close;

        SemaphoreCreatorHandle(const bool doc) :
            del_on_close(doc)
        {
            invalidate();
        }

        bool isValid() const
        {
            return identifier[0] != '\0';
        }

        void invalidate()
        {
            identifier[0] = '\0';
        }
    };

}  // end of namespace osal

#endif
