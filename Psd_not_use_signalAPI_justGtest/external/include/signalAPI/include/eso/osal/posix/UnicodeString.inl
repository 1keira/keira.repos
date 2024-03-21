/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <common/buffers.hxx>

namespace osal {

    inline UnicodeString::UnicodeString(const ipl::string &s):
        m_data(s.data()),
        m_bytes(s.size()+1),
        m_mode( MAKE_COPY )
    {
        // on POSIX ASCII and UTF8 are compatible. Take over the given
        // data plainly.
        checkStorage();
    }
    
    inline UnicodeString::UnicodeString(const char *s):
        m_data(s),
        m_bytes(strlen(s)+1),
        m_mode( MAKE_COPY )
    {
        // on POSIX ASCII and UTF8 are compatible. Take over the given
        // data plainly.
        checkStorage();
    }
    
    inline UnicodeString::operator ipl::unicode::String() const
    {
        return ipl::unicode::String(ipl::SharedBuf(data(), size()), ipl::unicode::UTF8);
    }

    inline UnicodeString::operator ipl::string() const
    {
        // nothing much to do
        return ipl::string(m_data);
    }

}  // end of namespace osal
