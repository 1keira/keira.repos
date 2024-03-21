/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_UNICODESTRING_COMMON_HXX
#define UTIL_UNICODESTRING_COMMON_HXX

#include <ipl_config.h>

#include <common/stdint.h>
#include <util/util_dso.h>

namespace util{

const uint8_t STRING_LOCAL_BUFFER_SIZE = 16;

typedef uint32_t UnicodeChar;

const UnicodeChar BOM = 0xFEFF;

/*!
    \brief Common stuff for UnicodeString8 and UnicodeString16

    In order to be able to have interfaces that accept both UnicodeString8
    and UnicodeString16 it is necessary that the two share some base class
    which contains all common aspects.
    This needn't be an interface (i.e. virtual methods) and probably shouldn't,
    for efficiency's sake.

*/
class UnicodeString_common {

public:
    enum Encoding {
        ASCII_7bit,
        ASCII_ESCAPED,
        ASCII,
        UTF8,
        UTF16,
        UTF32,
        WCHAR_UTF
    };

    static bool is_whitespace(UnicodeChar codepoint) {
        // http://en.wikipedia.org/wiki/Whitespace_character#Unicode
        return codepoint==0x0009 ||  // HT
               codepoint==0x000a ||  // LF
               codepoint==0x000b ||  // VT
               codepoint==0x000c ||  // FF
               codepoint==0x000d ||  // CR
               codepoint==0x0020 ||  // space
               codepoint==0x0085 ||  // NEL
               codepoint==0x00a0 ||  // non-breakable space
               codepoint==0x1680 ||  // ogham space
               codepoint==0x2000 ||  // en quad
               codepoint==0x2001 ||  // em quad
               codepoint==0x2002 ||  // en space
               codepoint==0x2003 ||  // em space
               codepoint==0x2004 ||  // 3 per em space
               codepoint==0x2005 ||  // 4 per em space
               codepoint==0x2006 ||  // 6 per em space
               codepoint==0x2007 ||  // figure space
               codepoint==0x2008 ||  // punctuation space
               codepoint==0x2009 ||  // thin space
               codepoint==0x200a ||  // hair space
               codepoint==0x2028 ||  // line separator
               codepoint==0x2029 ||  // paragraph separator
               codepoint==0x202f ||  // narrow non-breakable space
               codepoint==0x205f ||  // medium math space
               codepoint==0x3000;    // ideographic space
    }

protected:
    //! A customized strnlen function
    static uint32_t strnlen(char const* data, uint32_t max_length, uint8_t charsize, uint8_t& zero_length) IPL_NOEXCEPT;
};

}

#endif // UTIL_UNICODESTRING_COMMON_HXX
