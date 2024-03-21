/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

#ifndef COMM_UTIL_HXX
#define COMM_UTIL_HXX

// delegate old COMM_LOCK/UNLOCK etc to osal
#define COMM_LOCK(mutex) IPL_MUTEX_LOCK_OR_ABORT(mutex)
#define COMM_UNLOCK(mutex) IPL_MUTEX_UNLOCK_OR_ABORT(mutex)
#define COMM_SIGNAL(condvar) IPL_CONDITION_SIGNAL_OR_ABORT(condvar)

#ifndef COMM_HERE
#define COMM_HERE __FILE__,__LINE__
#endif

#endif // COMM_UTIL_HXX


