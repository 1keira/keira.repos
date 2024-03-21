/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_FILEINFODEFS_HXX
#define OSAL_POSIX_FILEINFODEFS_HXX

#include <sys/stat.h>

namespace osal {

    //! Handle to file status entries
    typedef struct stat FileInfoHandle;

    //! Handle to uniquely identify file systems in the system
    typedef dev_t FileSysID;

    //! is zero an invalid dev_t from POSIX POV?!
    const FileSysID INVALID_FILESYSID = 0;

    // from stat we get the inode and device number that should suffice for unique identification of
    // files
    //! identifier for a file system object on POSIX
    typedef struct FileID_s
    {
        // inode number
        ino_t ino;
        // device id
        FileSysID dev;

        FileID_s(FileSysID fsi = INVALID_FILESYSID, ino_t it = 0) : ino(it), dev(fsi)
        { }

        bool operator==(const FileID_s &o) const
        { return ino == o.ino && dev == o.dev; }

        bool operator!=(const FileID_s &o) const
        { return !operator==(o); }

        bool operator<(const FileID_s &o) const
        {
            if( ino < o.ino )
                return true;
            else if( ino == o.ino )
                return dev < o.dev;

            return false;
        }
    } FileID;

    //! Default ctor already sets invalid pars
    const FileID INVALID_FILEID;

    //! OS-independent type that is able to store a filesystem timestamp
    typedef time_t FileTime;

}  // end of namespace osal

#endif
