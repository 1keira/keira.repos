/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline osal::Thread::Priority osal::Thread::getCallerPriority()
    {
        int scheduler;
        struct ::sched_param params;
        ::pthread_getschedparam(pthread_self(), &scheduler,
            &params);

        return params.sched_priority;
    }

}  // end of namespace osal
