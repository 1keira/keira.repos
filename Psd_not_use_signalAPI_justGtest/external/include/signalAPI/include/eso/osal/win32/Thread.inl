/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal {

    inline osal::Thread::Priority osal::Thread::getCallerPriority()
    {
        return ::GetThreadPriority( ::GetCurrentThread() );
    }

} // end ns osal
