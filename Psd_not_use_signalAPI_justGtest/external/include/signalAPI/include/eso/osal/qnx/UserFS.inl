/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal {

    inline size_t UserFS::Entity::useCount() const
    {
        return m_attr.count;
    }

    inline void UserFS::Entity::setSize(const size_t size)
    {
        m_attr.nbytes = size;
    }

    inline size_t UserFS::Entity::getSize() const
    {
        return m_attr.nbytes;
    }

    inline size_t UserFS::Entity::getLinkCount() const
    {
        return m_attr.nlink;
    }

    inline void UserFS::Entity::setLinkCount(const size_t count)
    {
        m_attr.nlink = count;
    }

    inline osal::FileTime UserFS::Entity::getModTime() const
    {
        return m_attr.mtime;
    }

    inline void UserFS::Entity::setModTime(const osal::FileTime &ft)
    {
        m_attr.mtime = ft;
    }

    inline void UserFS::Entity::setType(const FileInfo::EntryType type)
    {
        // this unsets all type bits
        m_attr.mode &= ~(S_IFMT);

        switch( type )
        {
        default:
        case FileInfo::INVALID_ENTRY_TYPE:
        case FileInfo::REGULAR:
            m_attr.mode |= S_IFREG;
            break;
        case FileInfo::DIRECTORY:
            m_attr.mode |= S_IFDIR;
            break;
        case FileInfo::LINK:
            m_attr.mode |= S_IFLNK;
            break;
        }
    }

    inline FileInfo::EntryType UserFS::Entity::getType() const
    {
        if( S_ISREG(m_attr.mode) )
            return FileInfo::REGULAR;
        else if( S_ISDIR(m_attr.mode) )
            return FileInfo::DIRECTORY;
        else if( S_ISLNK(m_attr.mode) )
            return FileInfo::LINK;

        return FileInfo::INVALID_ENTRY_TYPE;
    }

    //! \todo Proper access bits
    inline void UserFS::Entity::setAccess(const FileAccess &access)
    {
        mode_t &mode = (this->m_attr).mode;

        // don't let group or world do anything by default
        mode &= ~(S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);

        // now for the user bits
        if( /*access.canRead()*/access&FileAccess::owner_read )
            mode |= S_IRUSR;
        else
            mode &= ~S_IRUSR;

        if( /*access.canWrite()*/access&FileAccess::owner_write )
            mode |= S_IWUSR;
        else
            mode &= ~S_IWUSR;

        if( /*access.canExecute()*/access&FileAccess::owner_exec )
            mode |= S_IXUSR;
        else
            mode &= ~S_IXUSR;
    }

    //! \todo Proper access bits
    inline FileAccess UserFS::Entity::getAccess() const
    {
//         return FileAccess(
//             m_attr.mode & S_IRUSR,
//             m_attr.mode & S_IWUSR,
//             m_attr.mode & S_IXUSR );
        FileAccess result=FileAccess::none;
        if(m_attr.mode & S_IRUSR) result|=FileAccess::owner_read|FileAccess::group_read;
        if(m_attr.mode & S_IWUSR) result|=FileAccess::owner_write|FileAccess::group_write;
        if(m_attr.mode & S_IXUSR) result|=FileAccess::owner_exec|FileAccess::group_exec;
        return result;
    }

    inline EntityID UserFS::Entity::getEntityID() const
    {
        return (this->m_attr).inode;
    }

    inline void UserFS::Entity::setEntityID(const EntityID &id)
    {
        (this->m_attr).inode = id;
    }

    inline size_t UserFS::DirFiller::left() const
    {
        return m_handle.left - sizeof(struct ::dirent);
    }

    inline size_t UserFS::DirFiller::used() const
    {
        return m_handle.size - m_handle.left;
    }

    inline size_t UserFS::DirFiller::offset() const
    {
        return m_handle.offset;
    }

} // end namespace
