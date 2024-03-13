/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_SERIALIZERSERRORS_HXX
#define UTIL_SERIALIZER_SERIALIZERSERRORS_HXX

#include <common/error/Error.hxx>
#include <util/util_dso.h>

namespace util
{

namespace serializer
{

enum SerializerErrors
{
    INVALID_MODE = 0,
    UNEXPECTED_PARAMETER_VALUE,
    WRITEABLE_OVERFLOW,
    READABLE_UNDERFLOW,
    FACTORY_MISMATCH,
    INSANE_SIZE,
    UNEXPECTED_EOS,
    UNEXPECTED_TOKEN,
    UNEXPECTED_TYPE,
    UNEXPECTED_KEY,
    UNEXPECTED_VALUE_1,
    UNEXPECTED_VALUE_2,
    NOT_A_NUMBER,
    NO_DATA_FOR_DESERIALIZATION,
    UNMATCHED_ENDTAG,
    WRONG_API_USAGE,
    LENGTH_SIZE_OVERFLOW,
    ARRAY_LIMIT_VIOLATION,
    UNSUPPORTED_UNICODE_FORMAT,
    INVALID_LENGTH_INDICATOR,
    MANDATORY_FIELD_MISSING,
    ILLEGAL_ENUM_VALUE,
    INVALID_UNICODE_STRING
};

const ipl::ErrorID SERIALIZER_ERROR_TABLE[] =
{
    { INVALID_MODE, "InvalidMode: Invalid function call order occured at (de)serializer.", 0 },
    { UNEXPECTED_PARAMETER_VALUE, "unexpected value for '%s'", 1},
    { WRITEABLE_OVERFLOW, "WriteableOverflow: Not enough Writeable buffer space to complete operation."
        " Capacity available: %d, capacity needed: %d", 2 },
    { READABLE_UNDERFLOW, "ReadableUnderflow: Not enough data in Readable to complete operation."
        " Capacity available: %d, capacity needed: %d", 2 },
    { FACTORY_MISMATCH, "FactoryMistmach: (De)Serializer does not belong to factory instance.", 0 },
    { INSANE_SIZE, "Insane size: Tried to (de)serialize %zu bytes, which seems to be insanely much", 1 },
    { UNEXPECTED_EOS, "unexpected end-of-stream", 0},
    { UNEXPECTED_TOKEN, "unexpected token '%c' found", 1},
    { UNEXPECTED_TYPE, "unexpected type '%s' found instead of type '%s'", 2},
    { UNEXPECTED_KEY, "unexpected key '%s' found", 1},
    { UNEXPECTED_VALUE_1, "unexpected value '%lld' for type '%s' found", 2},
    { UNEXPECTED_VALUE_2, "unexpected value '%s' for type '%s' found", 2},
    { NOT_A_NUMBER, "number expected but '%s' found", 1},
    { NO_DATA_FOR_DESERIALIZATION, "no data available for deserialization", 0},
    { UNMATCHED_ENDTAG, "unmatched endtag", 0},
    { WRONG_API_USAGE, "wrong (de) serializer API usage", 0},
    { LENGTH_SIZE_OVERFLOW, "length size overflow value '%ld' bit size ='%d'", 2},
    { ARRAY_LIMIT_VIOLATION, "array limit violation", 0},
    { UNSUPPORTED_UNICODE_FORMAT, "unsupported unicode format", 0},
    { INVALID_LENGTH_INDICATOR, "invalid length %ld during deserialization", 1},
    { MANDATORY_FIELD_MISSING, "mandatory field %s, id=%d missing", 2},
    { ILLEGAL_ENUM_VALUE, "Illegal enum value %ld for %s detected", 1},
    { INVALID_UNICODE_STRING, "Invalid Unicode codepoints detected", 0}
};

UTIL_EXPORT extern ipl::ErrorType Error;

} // end namespace serializer
} // end namespace util

#endif /* UTIL_SERIALIZER_SERIALIZERSERRORS_HXX */
