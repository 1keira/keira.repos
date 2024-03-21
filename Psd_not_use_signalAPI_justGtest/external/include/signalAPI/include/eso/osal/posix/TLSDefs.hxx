/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_TLSDEFS_HXX
#define OSAL_POSIX_TLSDEFS_HXX

#include <pthread.h>

namespace osal
{

typedef pthread_key_t TLSHandle;

} // end ns osal

#endif // inc. guard
