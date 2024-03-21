/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_LEXICALCAST_HXX
#define IPL_LEXICALCAST_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/iplcommon_dso.h>

#include <common/streams/sstream.hxx>
#include <common/types/string.hxx>

namespace IPL_NAMESPACE
{

/**
 *    \brief
 *        Perform casts from non-integral types to other types

 *        The lexical_cast is an idiom also present in boost. It can be used very similar to
 *        the internal cast operators. It's use is typically to easily do formatted conversion
 *        operations from and to strings.
 *
 *        This generic template doesn't do anything. All the work is performed in the
 *        specializations. Currently the only operations available are string to integer and
 *        integer to string conversions.
 *
 *        This is a very simple, experimental implementation of lexical_cast.
 **/
template<typename TO>
class lexical_cast
{
};

template<>
//! Allows casting integers to their string representation
class lexical_cast<ipl::string>
{
public:
    lexical_cast(int num) IPL_NOEXCEPT :
        m_num(num)
    { }

    operator ipl::string() const IPL_NOEXCEPT
    {
        ipl::stringstream s;
        s << m_num;
        return s.str();
    }
private:
    int m_num;
};

template<>
//! Allows casting strings to their integer representation
class lexical_cast<int>
{
public:
    lexical_cast(const ipl::string &s) IPL_NOEXCEPT :
        m_num(0)
    {
        ipl::stringstream ss(s);

        ss >> m_num;
    }

    lexical_cast(const char *s) IPL_NOEXCEPT  :
        m_num(0)
    {
        ipl::stringstream ss(s);

        ss >> m_num;
    }
public:
    operator int() const IPL_NOEXCEPT
    {
        return m_num;
    }
private:
    int m_num;
};

} // end namespace ipl

#endif /* IPL_LEXICALCAST_HXX */
