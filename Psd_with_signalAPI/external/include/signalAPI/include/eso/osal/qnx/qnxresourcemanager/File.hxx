#ifndef OSAL_QNXRESOURCEMANAGER_FILE_HXX
#define OSAL_QNXRESOURCEMANAGER_FILE_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Matthias Gerstner
    $Id$
*/

#include "Mountpoint.hxx"

namespace osal
{

namespace qnxresourcemanager
{

/**
 * \brief
 *     Implementation of the Device flavour of a Resource Manager (see
 *     QNX programming docu)

 *     This binds itself into the file system as one file (as opposed
 *     to a directory).
 *
 *     Clients interact with it using open() and close() as if it was a
 *     file.
 *
 *     The class thus specializes Mountpoint for being a file
 **/
class File :
    public Mountpoint
{
public:
    File(
        Engine &engine,
        mode_t mode=0666) :
            Mountpoint(engine, false, mode)
    {}
};

} // end of namespace
} // end of namespace

#endif // inc. guard
