/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <string.h>

namespace osal {

    inline osal::UnicodeString Environment::getVariable(const osal::UnicodeString &ucs)
    {
        const char *var = osal::Environment::getVariable(ucs.data());

        osal::UnicodeString ret(var, ::strlen(var),
            osal::UnicodeString::SHARED);

        return ret;
    }

    template<typename STRING>
    typename Environment::const_iterator_base<STRING>&
    Environment::const_iterator_base<STRING>::operator++()
    {
        m_handle++;

        return *this;
    }

    template<typename STRING>
    typename Environment::const_iterator_base<STRING>
    Environment::const_iterator_base<STRING>::operator++(int)
    {
        const_iterator_base<STRING> ret = *this;

        m_handle++;

        return ret;
    }

    template<>
    const osal::UnicodeString
    inline Environment::const_iterator_base<const osal::UnicodeString>::operator*() const
    {
        if (m_handle && *m_handle)
            return osal::UnicodeString(*m_handle,
                ::strlen(*m_handle) + 1,
                osal::UnicodeString::SHARED);
        return {};
    }

    template<typename STRING>
    inline STRING
    Environment::const_iterator_base<STRING>::operator*() const
    {
        return *m_handle;
    }

}  // end of namespace osal
