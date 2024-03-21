/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <string.h>
#include <iplbase/win32.h>

namespace osal {

    inline const char* Environment::getVariable(const char *name)
    {
        // no re-use of code in this case as otherwise we'd get problems
        // with memory management
        char *ret = ::getenv(name);
        return ret ? ret : "";
    }

    template <typename STRING>
    inline typename Environment::const_iterator_base<STRING>&
    Environment::const_iterator_base<STRING>::operator++()
    {
        while( *(m_handle.pos) != '\0' )
        {
            m_handle.pos++;
        }
        m_handle.pos++;
        return *this;
    }

    template <typename STRING>
    inline typename Environment::const_iterator_base<STRING>
    Environment::const_iterator_base<STRING>::operator++(int)
    {
        const_iterator_base<STRING> ret = *this;

        while( *(m_handle.pos) != '\0' )
        {
            m_handle.pos++;
        }
        m_handle.pos++;
        return ret;
    }

    template <typename STRING>
    inline STRING
    Environment::const_iterator_base<STRING>::operator*() const
    {
        m_handle.update_ascii();
        return m_handle.cur_ascii.c_str();
    }

    template<>
    inline const osal::UnicodeString
    Environment::const_iterator_base<const osal::UnicodeString>::operator*() const
    {
        return osal::UnicodeString( (const char*)m_handle.pos,
            ::wcslen(m_handle.pos),
            osal::UnicodeString::SHARED );
    }

}  // end of namespace osal
