/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef IPL_STREAMBUF_HXX
#define IPL_STREAMBUF_HXX

#include <common/ipl_namespace.hxx>
#include <streambuf>

namespace IPL_NAMESPACE
{

    //template <class charT, class traits = std::char_traits<charT>>
    //using basic_streambuf = std::basic_streambuf<charT, traits>;

    using std::basic_streambuf;

    using streambuf = std::streambuf;
    using wstreambuf = std::wstreambuf;

}
#endif
