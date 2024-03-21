/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_COMMON_ERROR_HXX
#define IPL_COMMON_ERROR_HXX

#include <common/ipl_namespace.hxx>
#include <common/error/Error.hxx>
#include <common/iplcommon_dso.h>

/*
 *    standard error categories and tables for the most common situations
 */

namespace IPL_NAMESPACE
{

enum CommonErrors
{
    OUT_OF_MEMORY = 0,
    INVALID_USAGE,
    INT_OUT_OF_RANGE,
    PAR_OUT_OF_RANGE,
    INVALID_PATH,
    INVALID_PARAMETER,
    NOT_SUPPORTED,
    ITEM_OVERFLOW
};

const ErrorID COMMON_ERROR_TABLE[] =
{
    { OUT_OF_MEMORY, "Out of heap memory", 0 },
    { INVALID_USAGE, "Invalid usage/logic detected: %s", 1 },
    { INT_OUT_OF_RANGE, "Integer parameter out of range. Min = %d, Max = %d, Found = %d", 3 },
    { PAR_OUT_OF_RANGE, "Parameter out of range: %s", 1 },
    { INVALID_PATH, "Invalid path specified: %s", 1 },
    { INVALID_PARAMETER, "Invalid parameter: %s", 1 },
    { NOT_SUPPORTED, "Function not supported: %s", 1 },
    { ITEM_OVERFLOW, "Overflow of item count occured: %s", 1 },
};

IPLCOMMON_EXPORT extern ipl::ErrorType CommonError;

// reraise something as critical
enum CommonCriticalErrors
{
    COMMON_CRITICAL_ERROR
};

const ErrorID COMMON_CRITICAL_ERROR_TABLE[] =
{
    { COMMON_CRITICAL_ERROR, "Critical error %s", 1 }
};

IPLCOMMON_EXPORT extern ipl::ErrorType CommonCriticalError;

} // namespace ipl

#endif // IPL_COMMON_ERROR_HXX
