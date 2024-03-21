/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

// #include <string.h>

namespace osal {

    inline osal::UnicodeString Environment::getVariable(const osal::UnicodeString &ucs)
    {
        return UnicodeString();
//         const char *var = osal::Environment::getVariable(ucs.data());
// 
//         osal::UnicodeString ret(var, ::strlen(var),
//             osal::UnicodeString::SHARED);
// 
//         return ret;
    }

    template<typename STRING>
    typename Environment::const_iterator_base<STRING>&
    Environment::const_iterator_base<STRING>::operator++()
    {
//         m_handle++;
// 
        return *this;
    }

    template<typename STRING>
    typename Environment::const_iterator_base<STRING>
    Environment::const_iterator_base<STRING>::operator++(int)
    {
        const_iterator_base<STRING> ret = *this;

//         m_handle++;
// 
        return ret;
    }

    template<>
    const osal::UnicodeString
    inline Environment::const_iterator_base<const osal::UnicodeString>::operator*() const
    {
        return osal::UnicodeString();
//         osal::UnicodeString ret(*m_handle,
//             ::strlen(*m_handle) + 1,
//             osal::UnicodeString::SHARED);
//         return ret;
    }

    template<typename STRING>
    inline STRING
    Environment::const_iterator_base<STRING>::operator*() const
    {
        return STRING();
//         return *m_handle;
    }

}  // end of namespace osal
