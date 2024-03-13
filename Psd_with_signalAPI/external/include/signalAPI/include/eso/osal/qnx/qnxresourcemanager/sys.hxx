#ifndef OSAL_QNXRESOURCEMANAGER_SYS_HXX
#define OSAL_QNXRESOURCEMANAGER_SYS_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Matthias Gerstner
    $Id$
*/

#include <ipl_config.h>

#ifndef IPL_OS_QNX
#    error "This is system specific code for QNX. You cannot compile it for other systems."
#endif

/**
 * \file
 * \brief
 *    Include this instead of directly including sys/iofunc.h and
 *    sys/dispatch.h

 *    QNX has mechanisms in its header files to enable extending its
 *    internal data structures. This is done by setting some \#defines
 *    before including sys/iofunc.h and sys/dispatch.h. So in order
 *    to avoid inconsistent definitions in different places, nobody is
 *    allowed to include the headers directly, but everybody must
 *    include this file instead, which does The Right Thing centrally.
 **/

namespace osal
{
    namespace qnxresourcemanager
    {
        class Attr;
        class Ocb;
    }
}

/*
 * we want to extend the dispatch context for the thread pool
 *
 * we want to extend the Attr structure and the Ocb structure
 */

#define THREAD_POOL_PARAM_T dispatch_context_t
#define THREAD_POOL_HANDLE_T dispatch_t
#define IOFUNC_ATTR_T osal::qnxresourcemanager::Attr
#define IOFUNC_OCB_T osal::qnxresourcemanager::Ocb

#include <sys/iofunc.h>
#include <sys/dispatch.h>
// ND_LOCAL_NODE define comes from here for example
#include <sys/netmgr.h>

#endif // inc. guard
