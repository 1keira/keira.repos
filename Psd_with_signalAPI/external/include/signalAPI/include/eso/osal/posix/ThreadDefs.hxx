/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_THREADDEFS_HXX
#define OSAL_POSIX_THREADDEFS_HXX

#include <ipl_config.h>

#include <threadsafe/Mutex.hxx>
#include <sys/types.h>
#include <osal/sched.hxx>

#include <string.h>
#include <pthread.h>

namespace osal
{

//! OS handle to reference a posix thread
struct ThreadHandle
{
#ifdef HAVE_BROKEN_PTHREAD_CREATE
    // synchronizes pthread_create with actual thread start
    // so we can guarantee that thread is already initialized
    threadsafe::Mutex mutex;
#endif
    pthread_t thread;
    // scheduling attributes from constructor
    osal::sched::Attr sched_attr;
    // kernel-thread id for linux
    pid_t               tid;

    ThreadHandle(): tid(0) {
        ::memset( &thread, 0, sizeof(pthread_t) );
    }
};

//! definition of a thread ID, remember this could be any type
typedef pthread_t OSThreadId;

} // end ns osal

#endif // inc. guard
