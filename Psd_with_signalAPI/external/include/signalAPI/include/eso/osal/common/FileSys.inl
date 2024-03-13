/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <osal/Path.hxx>

namespace osal {

    inline bool FileSys::readLink(const ipl::string &path, ipl::string &target)
    {
        char p[osal::Path::MAX_PATH_LEN];
        size_t len = osal::Path::MAX_PATH_LEN;

        target.clear();

        if( FileSys::readLink(path.c_str(), p, len) )
            return true;

        target = p;

        return false;
    }

    inline bool FileSys::readLink(const osal::UnicodeString &path,
                                  osal::UnicodeString &target)
    {
        // for win32 we always get an error from ascii readLink()
        char p[osal::Path::MAX_PATH_LEN];
        size_t len = osal::Path::MAX_PATH_LEN;

        if( FileSys::readLink((const char*)path.nativeData(), p, len) )
        {
            target = osal::UnicodeString();
            return true;
        }

        target = osal::UnicodeString(p, (len+1)*sizeof(native_utf),
                                     osal::UnicodeString::MAKE_COPY);

        return false;
    }

}  // end of namespace osal
