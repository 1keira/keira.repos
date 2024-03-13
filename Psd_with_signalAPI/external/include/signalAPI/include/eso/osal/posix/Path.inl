/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


// for _MAX constants
#include <limits.h>

#include <osal/SysError.hxx>

namespace osal {

template <typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>    
BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>
BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::getEntryPoint() const
{
    const value_type root[2] = { SEPARATOR,
        traits_type::to_char_type(0) };

    return isAbsolute() ? root : BasicPath();
}

template <typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>    
bool
BasicPath<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::isAbsolute() const
{
    return !this->empty() &&
        *(this->begin()) == SEPARATOR;
}

inline Path Path::findEntryPoint() const
{
    const char root[3] = { SEPARATOR, '/', '\0' };
    return root;
}

inline WidePath WidePath::findEntryPoint() const
{
    const wchar_t root[3] = { SEPARATOR, L'/', '\0' };
    return root;
}

} // end namespace
