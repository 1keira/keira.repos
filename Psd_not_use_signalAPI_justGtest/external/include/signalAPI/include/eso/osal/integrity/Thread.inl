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
		Value prio;
        ::GetTaskPriority (CurrentTask (), &prio);
		return prio;
    }

}  // end of namespace osal
