/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef IPL_ISTREAM_HXX
#define IPL_ISTREAM_HXX

#include <common/ipl_namespace.hxx>
#include <istream>

namespace IPL_NAMESPACE {

using std::basic_istream;

using istream = basic_istream<char>;
using wistream = basic_istream<wchar_t>;

using std::basic_iostream;
using iostream = basic_iostream<char>;
using wiostream = basic_iostream<wchar_t>;


}

#endif
