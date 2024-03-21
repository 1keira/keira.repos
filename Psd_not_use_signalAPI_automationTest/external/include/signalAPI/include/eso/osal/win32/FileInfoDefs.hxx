/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_FILEINFODEFS_HXX
#define OSAL_WIN32_FILEINFODEFS_HXX

#include <ipl_config.h>

// to prevent annoying warnings on WIN32
#include <iplcompiler.h>

#include <common/types/map.hxx>
#include <osal/RWLock.hxx>

namespace osal {

    // its to store a volume serial number
    typedef DWORD FileSysID;

    // XXX is this really suitable for "invalid" ?
    const FileSysID INVALID_FILESYSID = 0;

    //! to hold file information data
    struct OSAL_EXPORT FileInfoHandle
    {    
        // cluster size for the FS the file resides on
        DWORD cluster_size;
        // type information from getFileAttributes
        //DWORD type;
        // timestamps, file size, volume serial number, ...
        BY_HANDLE_FILE_INFORMATION info;

    protected:
        friend class FileInfo;
        friend class BinFileBase;

    #if !defined(IPL_OS_WINCE)
        // pedu25: In contrast to the WinPC implementation we do no
        // caching of the cluster size here because WinCE does not
        // support VolumeSerialNumbers because it has no Volume names.

        // stores the cluster size for each file system encountered
        static ipl::map< FileSysID, DWORD > fs_cluster_map;
    #endif

        // efficient thread safety for adding entries to fs_cluster_map
        static osal::RWLock fs_cluster_map_lock;

        //! sets the cluster size of the current object acc. to info
        //member and path
        template <typename STR>
        bool getClusterSize(STR *path)
        {
            cluster_size = getClusterSize(info, path);

            return cluster_size == 0;
        }

        template <typename STR>
        static DWORD getClusterSize(
            BY_HANDLE_FILE_INFORMATION &bhfi,
            STR path);
    };

    #ifndef OSAL_EXPORT_CONTEXT
    extern template DWORD FileInfoHandle::getClusterSize<const char*>(
        BY_HANDLE_FILE_INFORMATION &, const char*);
    extern template DWORD FileInfoHandle::getClusterSize<const wchar_t*>(
        BY_HANDLE_FILE_INFORMATION &, const wchar_t*);
    #endif

    // the information for this can be obtained from FileInfoHandle.info
    // identifier for a file system object on Win32
    typedef struct FileID_s
    {
        // the file system ID (volume UID)
        FileSysID file_sys;
        // the file index (high and low from BHFI struct)
        ULARGE_INTEGER file_index;

        FileID_s(FileSysID fsi = INVALID_FILESYSID, int64_t fi = 0) :
            file_sys(fsi) { file_index.QuadPart = fi; }

        bool operator==(const FileID_s &o) const
        {
            return file_sys == o.file_sys &&
                file_index.QuadPart == o.file_index.QuadPart;
        }

        bool operator!=(const FileID_s &o) const
        {
            return !operator==(o);
        }

        bool operator<(const FileID_s &o) const
        {
            if( file_sys < o.file_sys )
                return true;
            else if( file_sys == o.file_sys )
                return file_index.QuadPart < o.file_index.QuadPart;

            return false;
        }
    } FileID;

    // constructor already sets invalid pars
    const FileID INVALID_FILEID;

    //! OS-independent type that is able to store a filesystem timestamp
    typedef ULONGLONG FileTime;

}  // end of namespace osal

#endif
