/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <common/buffers.hxx>

namespace osal {

    inline UnicodeString::UnicodeString(const wchar_t *s):
        // already in the right format
        m_data((char*)s),
        m_bytes((wcslen(s) + 1) * sizeof(wchar_t)),
        m_mode( MAKE_COPY )
    {
        checkStorage();
    }

    inline UnicodeString::UnicodeString(const ipl::wstring &s):
        // already in the right format
        m_data((char*)s.data()),
        m_bytes((s.size() + 1) * sizeof(wchar_t)),
        m_mode( MAKE_COPY )
    {
        checkStorage();
    }

    inline UnicodeString::operator ipl::unicode::String() const
    {
        return ipl::unicode::String(ipl::SharedBuf(data(), size()), ipl::unicode::UTF16MACHINE);
    }

    inline UnicodeString::operator ipl::wstring() const
    {
        return ipl::wstring((wchar_t*)m_data);
    }

}  // end of namespace osal
