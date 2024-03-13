/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <common/CommonError.hxx>
#include <common/Macros.hxx>
#include <osal/SysError.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>

#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>
#include <fcntl.h>

namespace osal {

    inline Directory::Directory(const UnicodeString &path, const bool need_file_info):
        m_is_valid(false),
        m_at_end(true)
    {
        // there's no suitable common ctor code and ctors are messed up
        // by ifdefs. try it this way thus.
        osal::Directory tmp( path.data(), need_file_info );

        *this = tmp;
    }

    inline const char* Directory::curEntry() const
    {
        if (m_handle.cur_entry)
            return m_handle.cur_entry->d_name;
        return "";
    }

    inline void Directory::curEntry(osal::UnicodeString &ucs) const
    {
#if defined IPL_OS_QNX
        // QNX ships a non-std record member that states the length of
        // the string
        const size_t cur_entry_len = m_handle.cur_entry->d_namelen;
#else
        // on Linux we don't have an obvious shortcut to get the length
        // of curEntry().
        //
        // Linus chose to use d_reclen which is always aligned correctly
        // from kernel POV. Thus d_reclen does not necessarily tell us
        // the right length of d_name.
        //
        // ::offsetof(struct dirent, d_name) might thus be bigger than
        // ::strlen(d_name). However is might still prove quite faster
        // to look at d_name + ::offsetof(struct dirent, d_name) -
        // SOME_CONSTANT) for the null terminator and calculate the
        // length this way.
        //
        // Question is what SOME_CONSTANT is. Probably something like
        // sizeof(int). I'm not doing that optimization now to avoid
        // additional complexity. Keep it in mind though...
        const size_t cur_entry_len = ::strlen(this->curEntry());
#endif
        ucs = osal::UnicodeString( this->curEntry(),
            cur_entry_len + 1,
            osal::UnicodeString::SHARED );
    }

}  // end of namespace osal
