/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_FILEDEFS_HXX
#define OSAL_WIN32_FILEDEFS_HXX

#include <ipl_config.h>
#include <iplbase/win32.h>
#include <string.h>

namespace osal {

    //! \brief File handle for Win32
    struct FileHandle
    {
        FileHandle( HANDLE h = INVALID_HANDLE_VALUE ) :
            handle(h)
        {
    #if !defined(IPL_OS_WINCE) // pedu2501: Drive letters are not supported in WinCE
            ::memset( drive, 0, sizeof(drive));
    #endif    
        }

        HANDLE handle;

    #if !defined(IPL_OS_WINCE) // pedu2501: Drive letters are not supported in WinCE
        // this is needed to determine the cluster size in case FileInfo objects is requested at
        // BinFileBase
        char drive[3];
    #endif

        bool operator==(const FileHandle &o) const
        {
            return handle == o.handle;
        }

        bool operator!=(const FileHandle &o) const
        {
            return !operator==(o);
        }

        void invalidate()
        {
            handle = INVALID_HANDLE_VALUE;
        }

        bool isValid()
        {
            return handle != INVALID_HANDLE_VALUE;
        }

        HANDLE get()
        {
            return handle;
        }
    };

    const FileHandle OSAL_INVALID_FILE_HANDLE = FileHandle();

}  // end of namespace osal

#endif
