/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <common/CommonError.hxx>
#include <osal/SysError.hxx>
#include "WinPath.hxx"

namespace osal {

    inline Directory::Directory(const ipl::string &path, const bool need_file_info):
        m_is_valid(false),
        m_at_end(true)
    {
        WinPath wcs_path(path.c_str(), path.size());
        osal::Directory tmp(static_cast<osal::UnicodeString>(wcs_path), need_file_info );
        *this = tmp;
    }

    inline const char* Directory::curEntry() const
    {
        /*
            getting the ASCII string now that we rely on unicode
            everywhere is a bit ugly. We need to hold a deep copy of
            the ASCII representation of the current entry in case it
            is accessed

            exactly this happens now. WinPath helps us converting
            the utf16 cur entry into a plain ipl::string which is
            able to provide a const char* that is valid until the
            next curEntry() call occurs.
        */
        WinPath ret_utf16(m_handle.cur_entry.cFileName);

        m_handle.cur_entry_ascii = ret_utf16.getAscii();

        return m_handle.cur_entry_ascii.c_str();
    }

    inline void Directory::curEntry(osal::UnicodeString &ucs) const
    {
        // there seems to be no way of getting to know the length of
        // cFileName beforehand, thus we need to restort to wcslen().
        ucs = osal::UnicodeString((char*)m_handle.cur_entry.cFileName,
                                  (::wcslen(m_handle.cur_entry.cFileName)+1)
                                  *sizeof(native_utf),
                                  osal::UnicodeString::SHARED);
    }

    inline osal::FileInfo Directory::curInfo(const bool resolve_links) const
    {
        if( atEnd() )
        {
            ipl_raise( ipl::CommonError, ipl::INVALID_USAGE,
                "curInfo() called on directory with atEnd() == true" );
            return osal::FileInfo();
        }

        WinPath new_path( m_handle.path );
        new_path += L"\\";
        osal::UnicodeString ucs;
        this->curEntry(ucs);
        new_path += ucs;

        osal::FileInfo ret(static_cast<osal::UnicodeString>(new_path), resolve_links );
//         if( !ret.isValid() )
//         {
//             IPL_ABORT("invalid info");
//         }
        return ret;
    }

    inline osal::Directory Directory::curDir(const bool need_file_info) const
    {
        if( atEnd() )
        {
            ipl_raise( ipl::CommonError, ipl::INVALID_USAGE,
                "curDir() called on directory with atEnd() == true" );
            osal::Directory d;
            return d;
        }

        WinPath new_path( m_handle.path );
        new_path += L"\\";
        osal::UnicodeString ucs;
        this->curEntry(ucs);
        new_path += ucs;

        osal::Directory ret(
            static_cast<osal::UnicodeString>(new_path),
            need_file_info );

        if( ! ret.isValid() )
        {
            //IPL_ABORT("invalid dir");
        }

        return ret;
    }

    inline osal::Directory Directory::curDir( const bool resolve_links, const bool need_file_info ) const
    {
        /* ignore the resolve_links because windows is just a testing environment */
        (void)resolve_links;

        return this->curDir( need_file_info );
    }

}  // end of namespace osal
