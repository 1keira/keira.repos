/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_UNICODE_ERROR_HXX
#define UTIL_UNICODE_ERROR_HXX

#include <common/error/Error.hxx>
#include <util/util_dso.h>

namespace util {

    enum UnicodeErrors {
        UNICODESTRING_INVALID_ENCODING = 0,
        STRING_ITERATOR_OUT_OF_BOUNDS,
        UNICODE_STREAM_READ_FAILED,
        UNICODE_STREAM_WRITE_FAILED,
        UNICODE_INVALID_CODEPOINT
    };

    const ipl::ErrorID UNICODE_ERROR_TABLE[] =
    {
        { UNICODESTRING_INVALID_ENCODING, "An invalid encoding was specified or the byte sequence is invalid for a given encoding", 0 },
        { STRING_ITERATOR_OUT_OF_BOUNDS, "The unicode string iterator is out of bounds", 0},
        { UNICODE_STREAM_READ_FAILED, "Could not read from stream.", 0},
        { UNICODE_STREAM_WRITE_FAILED, "Could not write to stream.", 0},
        { UNICODE_INVALID_CODEPOINT, "Cannot store codepoint U+%08x", 1}
    };

    UTIL_EXPORT extern ipl::ErrorType UnicodeError;

}  // end of namespace util

#endif
