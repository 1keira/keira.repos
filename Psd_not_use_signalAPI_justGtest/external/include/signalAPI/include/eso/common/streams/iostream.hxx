/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef IPL_IOSTREAM_HXX
#define IPL_IOSTREAM_HXX

#include <common/ipl_namespace.hxx>
#include <iostream>

#include <common/streams/ios.hxx>
#include <common/streams/streambuf.hxx>
#include <common/streams/istream.hxx>
#include <common/streams/ostream.hxx>

namespace IPL_NAMESPACE {
    using std::cin;
    using std::wcin;
    using std::cout;
    using std::wcout;
    using std::cerr;
    using std::wcerr;
    using std::clog;
    using std::wclog;
}
#endif
