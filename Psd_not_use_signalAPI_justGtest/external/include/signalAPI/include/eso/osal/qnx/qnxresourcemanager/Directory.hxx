#ifndef OSAL_QNXRESOURCEMANAGER_DIRECTORY_HXX
#define OSAL_QNXRESOURCEMANAGER_DIRECTORY_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
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
 *     Implementation of the directory flavour of a Resource Manager

 *     This binds itself into the file system as a directory with a
 *     file system hierarchy below it, managed by this process.
 *
 *     Clients use mkdir, rmdir, unlink, write, read, symlink etc. to
 *     deal with the file system contents.
 *
 *     The class thus specializes Mountpoint for being a directory
 **/
class Directory :
    public Mountpoint
{
public:
    Directory(
        Engine &engine,
        mode_t mode=0666) :
            Mountpoint(engine, true, mode)
    {}
};

} // end of namespace
} // end of namespace

#endif // inc. guard
