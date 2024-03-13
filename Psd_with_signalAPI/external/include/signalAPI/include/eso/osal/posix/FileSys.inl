/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <osal/FileSys.hxx>

namespace osal {

    inline int_fast8_t FileSys::exists(const UnicodeString &ucs, const bool rl)
    {
        // on POSIX we can neatly reuse the ASCII version
        return FileSys::exists(ucs.data(), rl);
    }

    inline bool FileSys::createDir(const UnicodeString &ucs)
    {
        // neat!
        return FileSys::createDir(ucs.data());
    }

    inline bool FileSys::removeFile(const UnicodeString &ucs)
    {
        // you know...
        return FileSys::removeFile(ucs.data());
    }

    inline bool FileSys::removeDir(const UnicodeString &ucs)
    {
        // y. k.
        return FileSys::removeDir(ucs.data());
    }

    inline bool FileSys::move(const osal::UnicodeString &source,
                              const osal::UnicodeString &target)
    {
        return FileSys::move(source.data(), target.data());
    }

    inline bool FileSys::maxComponentLength(const osal::UnicodeString &path,
                                            uint_fast32_t &length)
    {
        return FileSys::maxComponentLength(path.data(), length);
    }

    inline bool FileSys::currentWD(osal::UnicodeString &wd)
    {
        // this is a tad inefficient. if necessary we can skip one copy
        // here
        ipl::string temp;

        const bool ret = FileSys::currentWD(temp);

        wd = osal::UnicodeString(temp.data(),
            temp.size()+1,
            osal::UnicodeString::MAKE_COPY);

        return ret;
    }

    inline bool FileSys::changeWD(const osal::UnicodeString &path)
    {
        return osal::FileSys::changeWD(path.data());
    }

    inline void FileSys::getTempPath(osal::UnicodeString &path)
    {
        const char *utf8 = getTempPath();

        path = osal::UnicodeString(utf8, ::strlen(utf8),
            osal::UnicodeString::SHARED);
    }

    inline void FileSys::getHomePath(osal::UnicodeString &path)
    {
        const char *utf8 = getHomePath();

        path = osal::UnicodeString(utf8, ::strlen(utf8),
            osal::UnicodeString::SHARED);
    }

    inline void FileSys::getMountPoints(ipl::list<osal::UnicodeString> &list)
    {
        // this means copying strings once more than necessary ... but
        // at least we save us some duplicate code.
        //
        // anybody who really wants to inspect mount points in unicode
        // will probably be able to bear with the performance loss in
        // this case
        ipl::list<ipl::string> mounts = osal::FileSys::getMountPoints();

        list.clear();

        while( ! mounts.empty() )
        {
            list.push_back(
                osal::UnicodeString(mounts.front().data(),
                    mounts.front().size()+1,
                    osal::UnicodeString::MAKE_COPY)
            );

            mounts.pop_front();
        }
    }
        
    inline bool FileSys::copy(const char *source, const char *target,
                              const size_t bufsize, void *buf)
    {
        // isn't that nice?
        return FileSys::copy(
            osal::UnicodeString(source, ::strlen(source) + 1, osal::UnicodeString::SHARED),
            osal::UnicodeString(target, ::strlen(target) + 1, osal::UnicodeString::SHARED),
            bufsize, buf);
    }
        
    inline bool FileSys::changeAccess(const osal::UnicodeString &ucs,
                                      const FileAccess &access)
    {
        return FileSys::changeAccess(ucs.nativeData(), access);
    }

}  // end of namespace osal
