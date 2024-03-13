/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <common/CommonError.hxx>
#include <osal/SysError.hxx>
#include <osal/win32/TimeDefs.hxx>

namespace osal {

    inline FileInfo::~FileInfo()
    {
#ifdef IPL_DEBUG
        m_valid = false;

        ::memset( &m_handle, 0, sizeof(FileInfoHandle) );
#endif
    }

    inline FileTime FileInfo::getModTime() const
    {
        if( ! m_valid )
            return 0;

        // m_handle.info.ftLastWriteTime now contains two 32-bit parts, the higher and lower bits of
        // the actual 64-bit timestamp. MSDN recommends to merge those two parts using the
        // ULARGE_INTEGER union which has an alternative view as a ULONGLONG 64-bit value onto the
        // timestamp. This saves us at least some bit shifting trouble.
        ULARGE_INTEGER ret;
        ret.LowPart = m_handle.info.ftLastWriteTime.dwLowDateTime;
        ret.HighPart = m_handle.info.ftLastWriteTime.dwHighDateTime;

        return ret.QuadPart;
    }

    inline uint64_t FileInfo::getSize() const
    {
        // directories have no sizes
        if( ! m_valid )
            return 0;

        // lets try the same stuff as with getModeTime() above
        ULARGE_INTEGER ret;

        ret.LowPart = m_handle.info.nFileSizeLow;
        ret.HighPart = m_handle.info.nFileSizeHigh;

        return ret.QuadPart;
    }

    inline uint64_t FileInfo::getBlocks() const
    {
        if( ! m_valid )
            return 0;

        const uint64_t netsize = this->getSize();
        uint64_t ret = netsize / m_handle.cluster_size;

        // partial block required, too
        if ( netsize % m_handle.cluster_size )
            ret++;

        return ret;
    }

    inline uint_fast32_t FileInfo::IOBlockSize() const
    {
        if( ! m_valid )
            return 0;

        // we need to assume that the cluster size obtained from GetDiskFreeSpace() is also the
        // optimum I/O size. Otherwise I fear that Win32 doesn't have a notion of that.
        return m_handle.cluster_size;
    }

    inline FileSysID FileInfo::getFsId() const
    {
        if( ! m_valid )
            return INVALID_FILESYSID;

        // now the GetFileInformationByHandle stuff pays off, it delivers the volume id...
        return m_handle.info.dwVolumeSerialNumber;
    }

    inline uint_fast32_t FileInfo::getBlockSize() const
    {
        // the same
        return this->IOBlockSize();
    }

    inline FileID FileInfo::getFileID() const
    {
        if( ! m_valid )
            return INVALID_FILEID;

/* pedu2501: On WinCE nFileIndexLow and nFileIndexHigh are not available.
            So lets use the unique Object Id instead.
*/
#if defined(IPL_OS_WINCE)
        return m_handle.info.dwOID;
#else
        FileID ret;

        ret.file_sys = this->getFsId();

        ret.file_index.LowPart = m_handle.info.nFileIndexLow;
        ret.file_index.HighPart = m_handle.info.nFileIndexHigh;

        return ret;
#endif
    }

    inline osal::TimeT FileInfo::convertFileTime(const osal::FileTime &osal_ft)
    {
        FILETIME ft;
        ft.dwHighDateTime = (DWORD)(osal_ft >> 32);
        ft.dwLowDateTime = (DWORD)osal_ft;

        return convertFileTimeToOsalTime(ft);
    }

    inline osal::FileTime FileInfo::getFileTime(const osal::TimeT &t)
    {
        /*
            FILETIME in in windows epoch. see osal::getTime for win32 to know more about
            changing UNIX timestamp into win-stamp and vice-versa
        */

        // we use that struct thingy to better work with the high and low words
        ULARGE_INTEGER write_time;

        // first we assign the UNIX epoch in msec.
        write_time.QuadPart = t;

        // add the windows epoch difference such that we get the windows epoch in milliseconds
        write_time.QuadPart += OSAL_DELTA_EPOCH_IN_MSEC;

        // from msec to 100 nano-sec periods
        write_time.QuadPart = write_time.QuadPart * 10 * 1000;

        return write_time.QuadPart;
    }

    inline FileInfo::EntryType FileInfo::getType() const
    {
        if( ! m_valid )
            return INVALID_ENTRY_TYPE;

        if( m_handle.info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            return DIRECTORY;
        // MSDN says "reserverd for system use" here
        else if(
#ifdef IPL_OS_WINPC
            m_handle.info.dwFileAttributes & FILE_ATTRIBUTE_DEVICE ||
#endif
            m_handle.info.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT )
                return SPECIAL;

        // nothing else can be said, it seems to be regular.
        return REGULAR;
    }

    inline FileAccess FileInfo::getAccess() const
    {
        // ignore anything. security descriptor stuff is really spooky.
        // The real thing to do is described in https://technet.microsoft.com/en-us/library/bb463216.aspx
        return FileAccess::all;
    }

    inline User FileInfo::getOwner() const
    {
        // TODO
        return User(User::BAD_ID);
    }

    inline Group FileInfo::getGroup() const
    {
        // ignore anything. security descriptor stuff is really spooky.
        return Group(Group::BAD_ID);
    }

}  // end of namespace osal
