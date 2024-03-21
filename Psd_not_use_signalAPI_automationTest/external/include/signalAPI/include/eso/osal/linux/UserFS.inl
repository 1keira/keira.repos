/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal
{

#ifdef HAVE_OSAL_USERFS

inline size_t UserFS::Entity::useCount() const
{
    return m_use_count;
}

inline void UserFS::Entity::setType(const FileInfo::EntryType type)
{
    // this unsets all type bits
    st_mode &= ~(S_IFMT);

    switch( type )
    {
    default:
    case FileInfo::INVALID_ENTRY_TYPE:
    case FileInfo::REGULAR:
        st_mode |= S_IFREG;
        break;
    case FileInfo::DIRECTORY:
        st_mode |= S_IFDIR;
        break;
    case FileInfo::LINK:
        st_mode |= S_IFLNK;
        break;
    }
}

inline FileInfo::EntryType UserFS::Entity::getType() const
{
    if( S_ISREG(st_mode) )
        return FileInfo::REGULAR;
    else if( S_ISDIR(st_mode) )
        return FileInfo::DIRECTORY;
    else if( S_ISLNK(st_mode) )
        return FileInfo::LINK;

    return FileInfo::INVALID_ENTRY_TYPE;
}

inline void UserFS::Entity::setAccess(const FileAccess &access)
{
    // don't let anybody do anything by default
    st_mode &= ~(S_IRWXU | S_IRWXG | S_IRWXO );

    // now for the user bits
    if( access.canRead() )
        st_mode |= S_IRUSR;

    if( access.canWrite() )
        st_mode |= S_IWUSR;

    if( access.canExecute() )
        st_mode |= S_IXUSR;
}

inline FileAccess UserFS::Entity::getAccess() const
{
    FileAccess result=FileAccess::none;
    if(st_mode & S_IRUSR) result|=FileAccess::owner_read|FileAccess::group_read;
    if(st_mode & S_IWUSR) result|=FileAccess::owner_write|FileAccess::group_write;
    if(st_mode & S_IXUSR) result|=FileAccess::owner_exec|FileAccess::group_exec;
    return result;
}

inline void UserFS::Entity::setSize(const size_t size)
{
    st_size = size;
}

inline size_t UserFS::Entity::getSize() const
{
    return st_size;
}

inline EntityID UserFS::Entity::getEntityID() const
{
    return st_ino;
}

inline void UserFS::Entity::setEntityID(const EntityID &id)
{
    st_ino = id;
}

inline size_t UserFS::Entity::getLinkCount() const
{
    return st_nlink;
}

inline void UserFS::Entity::setLinkCount(const size_t count)
{
    st_nlink = count;
}

inline osal::FileTime UserFS::Entity::getModTime() const
{
    return st_mtime;
}

inline void UserFS::Entity::setModTime(const osal::FileTime &ft)
{
    st_mtime = ft;
}
    
inline size_t UserFS::DirFiller::fill(const IFileSystem::DirEntry &e)
{
    m_handle.full = m_handle.filler(
        m_handle.buf,
        e.name,
        NULL,
        ++m_handle.offset);

    return left();
}

inline size_t UserFS::DirFiller::left() const
{
    return m_handle.full ? 0 : path_traits<char>::MAX_PATH_LEN;
}
    
inline size_t UserFS::DirFiller::used() const
{
    return path_traits<char>::MAX_PATH_LEN;
}

inline size_t UserFS::DirFiller::offset() const
{
    return m_handle.offset;
}

#else // HAVE_OSAL_USERFS

inline size_t UserFS::Entity::useCount() const
{
    return 0;
}

inline void UserFS::Entity::setType(const FileInfo::EntryType type)
{ }

inline FileInfo::EntryType UserFS::Entity::getType() const
{
    return FileInfo::INVALID_ENTRY_TYPE;
}

inline void UserFS::Entity::setAccess(const FileAccess &access)
{ } 

inline FileAccess UserFS::Entity::getAccess() const
{
//     return FileAccess(false, false, false);
    return FileAccess::none;
}

inline void UserFS::Entity::setSize(const size_t size)
{ }

inline size_t UserFS::Entity::getSize() const
{
    return 0;
}

inline EntityID UserFS::Entity::getEntityID() const
{
    return 0;
}

inline void UserFS::Entity::setEntityID(const EntityID &id)
{ }

inline size_t UserFS::Entity::getLinkCount() const
{
    return 0;
}

inline void UserFS::Entity::setLinkCount(const size_t count)
{ }
    
inline size_t UserFS::DirFiller::fill(const IFileSystem::DirEntry &e)
{
    return 0;
}

inline size_t UserFS::DirFiller::left() const
{
    return 0;
}
    
inline size_t UserFS::DirFiller::used() const
{
    return 0;
}

inline size_t UserFS::DirFiller::offset() const
{
    return 0;
}

inline osal::FileTime UserFS::Entity::getModTime() const
{
    return osal::FileTime();
}

inline void UserFS::Entity::setModTime(const osal::FileTime &ft)
{ }

#endif

} // end namespace
