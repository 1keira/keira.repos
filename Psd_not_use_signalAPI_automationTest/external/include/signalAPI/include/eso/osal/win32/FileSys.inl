/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <iplbase/win32.h>

#include <osal/FileSys.hxx>
#include "WinPath.hxx"

namespace osal {

    inline int_fast8_t FileSys::exists(const char *p, const bool rl)
    {
        WinPath wp(p);

        return FileSys::exists(
            static_cast<osal::UnicodeString>(wp), rl);
    }

    inline bool FileSys::createDir(const char *path)
    {
        WinPath wp(path);

        return FileSys::createDir(
            static_cast<osal::UnicodeString>(wp));
    }

    inline bool FileSys::removeFile(const char *path)
    {
        WinPath wp(path);

        return FileSys::removeFile(
            static_cast<osal::UnicodeString>(wp));
    }

    inline bool FileSys::removeDir(const char *path)
    {
        WinPath wp(path);

        return FileSys::removeDir(
            static_cast<osal::UnicodeString>(wp));
    }

    inline bool FileSys::move(const char *source, const char *target)
    {
        WinPath src(source), tgt(target);

        return FileSys::move(
            static_cast<osal::UnicodeString>(src),
            static_cast<osal::UnicodeString>(tgt));
    }

    inline bool FileSys::maxComponentLength(const char *path, uint_fast32_t &length)
    {
        WinPath wp(path);

        return FileSys::maxComponentLength(
            static_cast<osal::UnicodeString>(wp), length);
    }

    inline bool FileSys::currentWD(ipl::string &wd)
    {
        wd.clear();

        osal::UnicodeString ucs;

        const bool err = FileSys::currentWD(ucs);

        if( err )
            return true;

        WinPath wp(ucs.nativeData(), ucs.size());

        wd = wp.getAscii();

        return false;
    }

    inline bool FileSys::changeWD(const char *path)
    {
        WinPath wp(path);

        return FileSys::changeWD(
            static_cast<osal::UnicodeString>(wp));
    }

    inline ipl::list<ipl::string> FileSys::getMountPoints()
    {
        ipl::list<osal::UnicodeString> utf16_list;
        ipl::list<ipl::string> ret;

        osal::FileSys::getMountPoints(utf16_list);

        while( ! utf16_list.empty() )
        {
            WinPath wp(utf16_list.front());
            ret.push_back( wp.getAscii() );
            utf16_list.pop_front();
        }

        return ret;
    }

    inline bool FileSys::copy(const char *source, const char *target,
                              const size_t bufsize, void *buf)
    {
        WinPath src(source), tgt(target);

        return FileSys::copy(
            static_cast<osal::UnicodeString>(src),
            static_cast<osal::UnicodeString>(tgt),
            bufsize, buf);
    }

    inline bool FileSys::changeAccess(const char *path, const FileAccess &access)
    {
        return false;
    }


    inline bool FileSys::changeAccess(const UnicodeString &ucs,
        const FileAccess &access)
    {
        return false;
    }
    
    inline bool FileSys::changeOwnerGroup(const UnicodeString &filename,
                                          const User &user, const Group &group)
    {
        return false;
    }
    
}  // end of namespace osal
