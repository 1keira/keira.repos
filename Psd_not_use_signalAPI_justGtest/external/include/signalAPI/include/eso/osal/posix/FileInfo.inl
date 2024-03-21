/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include <common/CommonError.hxx>
#include <osal/SysError.hxx>
#include <osal/FileAccessError.hxx>

namespace osal {

    inline FileInfo::~FileInfo()
    {
#ifdef IPL_DEBUG
        m_valid = false;
        ::memset( &m_handle, 0, sizeof(struct stat) );
#endif
    }

    inline FileInfo::EntryType FileInfo::getType() const
    {
        if( ! m_valid )
            return INVALID_ENTRY_TYPE;

        if( S_ISREG(m_handle.st_mode) )
            return REGULAR;
        else if( S_ISDIR(m_handle.st_mode) )
            return DIRECTORY;
        else if( S_ISLNK(m_handle.st_mode) )
            return LINK;

        // anything else is special
        return SPECIAL;
    }

    inline FileTime FileInfo::getModTime() const
    {
        if( ! m_valid )
            return 0;

        return m_handle.st_mtime;
    }

    inline uint64_t FileInfo::getSize() const
    {
        if( m_valid && (S_ISREG(m_handle.st_mode) ||
            S_ISLNK(m_handle.st_mode)
#ifdef HAVE_SYS_STAT_TYPEISSHM
            || S_TYPEISSHM(&m_handle)
#endif
        ))
        {
            return (uint64_t)m_handle.st_size;
        }

        return 0;
    }

    inline uint64_t FileInfo::getBlocks() const
    {
        if( ! m_valid )
            return 0;

        return (uint64_t)m_handle.st_blocks;
    }

    inline uint_fast32_t FileInfo::IOBlockSize() const
    {
        if( ! m_valid )
            return 0;

        return (uint_fast32_t)m_handle.st_blksize;
    }

    inline FileSysID FileInfo::getFsId() const
    {
        if( ! m_valid )
            return INVALID_FILESYSID;

        return m_handle.st_dev;
    }

    inline FileID FileInfo::getFileID() const
    {
        FileID ret;

        if( m_valid )
        {
            ret.ino = m_handle.st_ino;
            ret.dev = this->getFsId();
        }

        return ret;
    }


    inline uint_fast32_t FileInfo::getBlockSize() const
    {
        /*
            This block size information is a pretty gray area in
            POSIX.
        
            According to POSIX it is completely implementation
            defined what the unit of st_blocks is. An implementation
            may or may not define a constant for that.
        
            It seems that most if not all UNIX systems out there use
            a block size of 512 bytes here - without providing an
            actual constant. Note that this has nothing to do with
            the actual block sizes used by the file system. It's
            simply a multiplier for st_size.
        */
        return 512;
    }

    inline FileTime FileInfo::getFileTime(const osal::TimeT &t)
    {
        // on POSIX Filetime and unix-timestamp are the same only
        // unix-timestamp on OSAL level is in ms. and unix file
        // timestamp is in s.
        return t / 1000;
    }

    inline osal::TimeT FileInfo::convertFileTime(const osal::FileTime &ft)
    {
        // see getFileTime() impl.
        return (osal::TimeT)ft * 1000;
    }
        
}  // end of namespace osal
