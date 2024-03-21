#error Not needed, posix version seems to be good enough
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

// #include <common/CommonError.hxx>
// #include <common/Macros.hxx>
// #include <osal/SysError.hxx>
// #include <osal/Mutex.hxx>
// #include <osal/Condition.hxx>
// 
// #include <sys/types.h>
// #include <dirent.h>
// #include <stddef.h>
// #include <fcntl.h>

namespace osal {

    inline Directory::Directory(const UnicodeString &path, const bool need_file_info):
        m_is_valid(false),
        m_at_end(true)
    {
//         // there's no suitable common ctor code and ctors are messed up
//         // by ifdefs. try it this way thus.
//         osal::Directory tmp( path.data(), need_file_info );
// 
//         *this = tmp;
    }

    inline const char* Directory::curEntry() const
    {
        return 0;  // TODO
//         return m_handle.cur_entry->d_name;
    }

    inline void Directory::curEntry(osal::UnicodeString &ucs) const
    {
//         ucs = osal::UnicodeString( this->curEntry(),
//             cur_entry_len + 1,
//             osal::UnicodeString::SHARED );
    }

}  // end of namespace osal
