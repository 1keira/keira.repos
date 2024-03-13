/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_TYPES_STRING_HXX
#define COMMON_TYPES_STRING_HXX

#include <common/ipl_namespace.hxx>
#include <string>



#if defined(_MSC_VER) && (_MSC_VER >= 1600) && (_MSC_VER < 1916)
const std::string::size_type std::string::npos = (std::string::size_type) - 1;
const std::wstring::size_type std::wstring::npos = (std::wstring::size_type) - 1;
#endif


namespace IPL_NAMESPACE {

    using std::char_traits;
    using std::basic_string;
    using std::string;
    using std::wstring;
    using std::hash;
    using std::getline;

    using std::stoi;
    using std::stol;
    using std::stoll;

}

#endif  //  COMMON_TYPES_STRING_HXX
