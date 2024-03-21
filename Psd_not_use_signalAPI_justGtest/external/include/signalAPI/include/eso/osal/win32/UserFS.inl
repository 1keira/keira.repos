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
//         return FileAccess(false, false, false);
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

} // end ns
