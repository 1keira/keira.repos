/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_DIRECTORYDEFS_HXX
#define OSAL_POSIX_DIRECTORYDEFS_HXX

#include <dirent.h>
#include <unistd.h>

#if _POSIX_VERSION+0<200809
#    include <common/types/string.hxx>
#endif

namespace osal {

    //! position values returned from telldir and used at seekdir
    typedef long DirectoryPos;

    //! handle for open directory entries
    typedef struct
    {
        // file descriptor for the current directory
        int fd;
        // for readdir operation the DIR handle
        DIR *dir;
        // for readdir operation the a ptr to the currently selected entry
        struct dirent *cur_entry;
    #if _POSIX_VERSION+0<200809
        // for curDir() and curInfo() we need the full path if no *at() functions are available
        ipl::string path;
    #endif
        // for readdir_r operation the OSAL allocated dirent structure
        //struct dirent *mem;
    } DirectoryHandle;

}  // end of namespace osal

#endif
