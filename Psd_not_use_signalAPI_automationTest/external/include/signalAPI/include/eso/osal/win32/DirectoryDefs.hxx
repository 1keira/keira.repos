/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_DIRECTORYDEFS_HXX
#define OSAL_WIN32_DIRECTORYDEFS_HXX

#include <iplbase/win32.h>
#include <common/types/string.hxx>

#include "WinPath.hxx"

    namespace osal {

    //! handle for open directory entries on Win32
    typedef struct DirectoryHandle_s
    {
        HANDLE dir;
        WIN32_FIND_DATAW cur_entry;
        // this is a suitable windows path for the directory
        WinPath path;
        // this is a possible ascii version cur_entry
        mutable ipl::string cur_entry_ascii;

        DirectoryHandle_s()
        { }

    } DirectoryHandle;

}  // end of namespace osal

#endif
