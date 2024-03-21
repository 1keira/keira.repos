/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
/*!
    \file
    \brief Don't forget to bring your own ICU!

    This file provides util::IcuString,
    a bridge between the framework's util::UnicodeString
    and icu::UnicodeString.
    It \b does \b not magically make your program ICU capable.
    You have to do that yourself,
    i.e. provide ICU includes in your own include path and
    link to the appropriate ICU libs, at least \c icuuc.
*/
/*****************************************************************************/
#ifndef UTIL_FWUSTRING_HXX
#define UTIL_FWUSTRING_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <unicode/unistr.h>
#include "util/UnicodeString.hxx"

// these two are only present in newer versions of ICU
#ifndef UNISTR_FROM_CHAR_EXPLICIT
#define UNISTR_FROM_CHAR_EXPLICIT
#endif
#ifndef UNISTR_FROM_STRING_EXPLICIT
#define UNISTR_FROM_STRING_EXPLICIT
#endif

/*****************************************************************************/

namespace util {

/*****************************************************************************/

    /*!
        \brief Bridge between icu::UnicodeString and util::UnicodeString

        This is a icu::UnicodeString wrapping an eso framework string.
        Both ICU and framework use copy-on-write, so the data is shared
        as long as it isn't changed.

        So if you have a framework string but need an ICU string,
        you can simply do
        \code
        util::IcuString icus(some_util_UnicodeString);
        \endcode
        and use \a icus as if it was an <code>icu::UnicodeString</code>.

        The other way round is similarly easy. If you have an ICU string
        but need to convert it into a framework string, just do something like
        \code
        util::IcuString icus(some_icu_UnicodeString);
        some_function_taking_util_UnicodeString(icus);
        \endcode

        In short, you can use a util::IcuString just as you would use an
        icu::UnicodeString,
        plus you can can construct it from/cast it into a
        util::UnicodeString.

        \b Note:
        You need to bring your own ICU, i.e. it is \b your \b responsibility
        to provide ICU headers in the include path and to link against
        the appropriate ICU libs, at least \c icuuc.
    */
    class IcuString: public icu::UnicodeString {

    public:
        IcuString(const util::UnicodeString8  &s) IPL_NOEXCEPT { operator = (s); }
        IcuString(const util::UnicodeString16 &s) IPL_NOEXCEPT { operator = (s); }

        IcuString() IPL_NOEXCEPT {}
        IcuString(int32_t capacity, UChar32 c, int32_t count) IPL_NOEXCEPT:
            icu::UnicodeString(capacity, c, count) {}
        UNISTR_FROM_CHAR_EXPLICIT IcuString(UChar c) IPL_NOEXCEPT:
            icu::UnicodeString(c) {}
        UNISTR_FROM_CHAR_EXPLICIT IcuString(UChar32 c) IPL_NOEXCEPT:
            icu::UnicodeString(c) {}
        UNISTR_FROM_STRING_EXPLICIT IcuString(const UChar *text) IPL_NOEXCEPT:
            icu::UnicodeString(text) {}
        IcuString(const UChar *text, int32_t textLength) IPL_NOEXCEPT:
            icu::UnicodeString(text, textLength) {}
        IcuString(UBool isTerminated, const UChar *text, int32_t textLength) IPL_NOEXCEPT:
            icu::UnicodeString(isTerminated, text, textLength) {}
        IcuString(UChar *buffer, int32_t buffLength, int32_t buffCapacity) IPL_NOEXCEPT:
            icu::UnicodeString(buffer, buffLength, buffCapacity) {}
        UNISTR_FROM_STRING_EXPLICIT IcuString(const char *codepageData) IPL_NOEXCEPT:
            icu::UnicodeString(codepageData) {}
        IcuString(const char *codepageData, int32_t dataLength) IPL_NOEXCEPT:
            icu::UnicodeString(codepageData, dataLength) {}
        IcuString(const char *codepageData, const char *codepage) IPL_NOEXCEPT:
            icu::UnicodeString(codepageData, codepage) {}
        IcuString(const char *codepageData, int32_t dataLength, const char *codepage) IPL_NOEXCEPT:
            icu::UnicodeString(codepageData, dataLength, codepage) {}
        IcuString(const char *src, int32_t srcLength, UConverter *cnv, UErrorCode &errorCode) IPL_NOEXCEPT:
            icu::UnicodeString(src, srcLength, cnv, errorCode) {}
        IcuString(const char *src, int32_t length, enum EInvariant inv) IPL_NOEXCEPT:
            icu::UnicodeString(src, length, inv) {}
        IcuString(const UnicodeString &that) IPL_NOEXCEPT: icu::UnicodeString(that) {}
        IcuString(const UnicodeString &src, int32_t srcStart) IPL_NOEXCEPT:
            icu::UnicodeString(src, srcStart) {}
        IcuString(const UnicodeString &src, int32_t srcStart, int32_t srcLength) IPL_NOEXCEPT:
            icu::UnicodeString(src, srcStart, srcLength) {}

        IcuString &operator = (const util::UnicodeString8  &s) IPL_NOEXCEPT {
            fw_string16=s;
            IPL_ASSERT(sizeof(UChar)==U_SIZEOF_UCHAR);
            setTo((UBool)false,
                  (UChar *)fw_string16.retrieveData(), fw_string16.length());
            return *this;
        }
        IcuString &operator = (const util::UnicodeString16  &s) IPL_NOEXCEPT {
            fw_string16=s;
            IPL_ASSERT(sizeof(UChar)==U_SIZEOF_UCHAR);
            setTo((UBool)false,
                  (UChar *)fw_string16.retrieveData(), fw_string16.length());
            return *this;
        }
        using icu::UnicodeString::operator =;

        operator util::UnicodeString () IPL_NOEXCEPT {
            if((void *)icu::UnicodeString::getBuffer()==(void *)fw_string16.retrieveData())
                return fw_string16;
            else
                return util::UnicodeString((char *)icu::UnicodeString::getBuffer(),
                                           util::UnicodeString::UTF16,
                                           icu::UnicodeString::length()*2);
        }
        operator const util::UnicodeString () const IPL_NOEXCEPT {
            if((void *)icu::UnicodeString::getBuffer()==(void *)fw_string16.retrieveData())
                return fw_string16;
            else
                return util::UnicodeString((char *)icu::UnicodeString::getBuffer(),
                                           util::UnicodeString::UTF16,
                                           icu::UnicodeString::length()*2);
        }

    protected:
        util::UnicodeString16 fw_string16;
    };

/*****************************************************************************/

}  // end of namespace util

/*****************************************************************************/
#endif
