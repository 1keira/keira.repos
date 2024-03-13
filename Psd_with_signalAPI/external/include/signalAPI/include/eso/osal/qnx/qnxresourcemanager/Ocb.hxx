#ifndef OSAL_QNXRESOURCEMANAGER_OCB_HXX
#define OSAL_QNXRESOURCEMANAGER_OCB_HXX

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

namespace osal
{
    namespace qnxresourcemanager
    {
        class Mountpoint;
        class Session;
    }
}

namespace osal
{

namespace qnxresourcemanager
{

/**
 * \brief
 *     Extended QNX OCB structure

 *     This is an extension of the QNX native iofunc_ocb_t data
 *     structure. This is a data structure that is associated with each
 *     individual connection to a file registered in the resource
 *     manager.
 *
 *     This data structure is passed to each i/o function callback like
 *     the read or write call. We need to extend it to add our relevant
 *     C++ structures to it.
 * \note
 *     This "inherits" iofunc_ocb_t the C way, i.e. contains one as
 *     first member
 *
 *     See chapter <em>Extending the POSIX-Layer Data Structures</em>
 *     in book <em>Writing a Resource Manager</em> from the <em>QNX
 *     Neutrino Realtime Operating System</em> bookset which e.g. lives
 *     in the Momentics online help.
 * \warning
 *     This struct must not have a vtable! see note.
**/
struct Ocb
{
    iofunc_ocb_t m_ocb; // must be first member!
    Mountpoint *mountpoint;
    Session *session;

    Ocb(Mountpoint *mtp, Session *sess) :
        mountpoint(mtp),
        session(sess)
    {}
};

} // end of namespace qnxresourcemanager
} // end of namespace osal

#endif // inc. guard
