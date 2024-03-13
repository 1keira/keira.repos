#ifndef OSAL_QNXRESOURCEMANAGER_ATTR_HXX
#define OSAL_QNXRESOURCEMANAGER_ATTR_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Matthias Gerstner
    $Id$
*/

#ifndef IPL_OS_QNX
#    error "This is system specific code for QNX. You cannot compile it for other systems."
#endif

#include <common/Macros.hxx>

#include "Engine.hxx"

namespace osal
{
    namespace qnxresourcemanager
    {
        class Mountpoint;
    }
}

namespace osal
{

namespace qnxresourcemanager
{

/**
 * \brief
 *    Extended QNX device attribute structure

 *     This is an extension of the QNX native iofunc_attr_t data
 *     structure. This is a data structure that is associated with each
 *     registered file in resource manager. It is not associated with
 *     each open context of a file (that would be the OCB instead) but
 *     exists only once per file.
 *     
 *     This data structure is passed to each connect function callback
 *     like the open call. We need to extend it to add a referece to
 *     our C++ Mountpoint instance and thus make it available in the
 *     open calls.
 * \note
 *    This "inherits" iofunc_attr_t the C way, i.e. contains one as
 *    first member.
 *
 *    The attribute structure defines the basic attributes of a
 *    device/file on QNX like access rights and ownership.
 *
 *    This allows QNX to use it in place of an iofunc_attr_t while it
 *    allows us to add members.
 *
 *    See chapter <em>Extending the POSIX-Layer Data Structures</em>
 *    in book <em>Writing a Resource Manager</em> from the <em>QNX
 *    Neutrino Realtime Operating System</em> bookset which e.g. lives
 *    in the Momentics online help.
 * \warning
 *    This class must not have a vtable! see the note.
 **/
struct Attr
{
    iofunc_attr_t m_attr; // must be first member!
    Mountpoint *mountpoint;

    Attr(Mountpoint *mtp, mode_t mode)
    {
        initAttr(mode);
        setMountpoint(mtp);
    }

    Attr() : mountpoint()
    {
        initAttr(0);
    }

    void initAttr(mode_t mode)
    {
        Engine::initAttr(&m_attr, mode);
    }

    void setMountpoint(Mountpoint *mtp)
    {
        IPL_ASSERT(mtp != NULL);
        mountpoint = mtp;
    }
};

} // end of namespace qnxresourcemanager

} // end of namespace osal

#endif // inc. guard.
