/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SYS_ERROR_HXX
#define OSAL_SYS_ERROR_HXX

#include <common/error/Error.hxx>

#include <osal/osal_dso.h>
#include <osal/SystemError.hxx>

namespace osal
{

/**
 *    \brief
 *        General system call errors used across OSAL

 *        Further specialized error types maybe declared per OSAL class
 **/
enum SysErrors
{
    SYSTEM_RESSOURCES_EXHAUSTED = 0,
    OUT_OF_MEMORY,
    INVALID_PATH,
    NO_DIRECTORY,
    PATH_TOO_LONG,
    INTERRUPTED,
    NOT_IMPLEMENTED,
    PERMISSION_DENIED,
    INVALID_ARGUMENT,
    INVALID_ADDRESS,
    INTEGRITY_ERROR,
    IO_FAILURE,
    FILE_EXISTS,
    OBJECT_BUSY,
    DIR_NOT_EMPTY,
    FS_NO_SPACE,
    INVALID_DEVICE,
    QUERY_FAILED,
    NO_PROCESS,
    UNKNOWN_ERROR,
    POLL_ERROR
};

/**
 *    \brief
 *        General system call error descriptions plus OS dependant error strings
 **/
const ipl::ErrorID SYS_ERROR_TABLE[] =
{
    { SYSTEM_RESSOURCES_EXHAUSTED, "System ressources exhausted: %s", 1 },
    { OUT_OF_MEMORY, "System is out of memory: %s", 1 },
    { INVALID_PATH, "Invalid path specified: %s", 1 },
    { NO_DIRECTORY, "Given path is not a directory: %s", 1 },
    { PATH_TOO_LONG, "Given path exceeds system maximum: %s (%d chars encountered, only max %d chars allowed)", 2 },
    { INTERRUPTED, "System call has been interrupted: %s", 1 },
    { NOT_IMPLEMENTED, "Function not implemented: %s", 1 },
    { PERMISSION_DENIED, "Permission denied: %s", 1 },
    { INVALID_ARGUMENT, "Supplied parameter is invalid: %s", 1 },
    { INVALID_ADDRESS, "Supplied parameter has invalid address: %s", 1 },
    { INTEGRITY_ERROR, "Spoiled integrity: %s", 1 },
    { IO_FAILURE, "Input/Output error: %s", 1 },
    { FILE_EXISTS, "A file already exists: %s", 1 },
    { OBJECT_BUSY, "The operation cannot be performed, because the object is still in use: %s", 1 },
    { DIR_NOT_EMPTY, "The directory is not empty: %s", 1 },
    { FS_NO_SPACE, "Not enough space left on file system: %s", 1 },
    { INVALID_DEVICE, "Given device is not existing, not ready or does not support the operation: %s", 1 },
    { QUERY_FAILED, "Querying the requested system information failed: %s", 1 },
    { NO_PROCESS, "The given process does not exist", 1 },
    { UNKNOWN_ERROR, "Unclassified error occured: %s", 1 },
    { POLL_ERROR, "poll/epoll/select error: %s", 1 }
};

/**
 *    \brief
 *        The glocal SysError object used for raising them.
 **/
OSAL_EXPORT extern ipl::ErrorType SysError;

//! \brief
//!    helper function that raises OSAL system errors
//!
//!    the given error and error ID, retrieving the currently set system specific error
//!    string via a SystemError object
#define osal_raise(TYPE, ID) (ipl_raise( TYPE, ID, osal::SystemError().getString().c_str() ))

//! takes an error ID that is not errno
#define osal_raise_errnum(NUM, TYPE, ID) (ipl_raise( TYPE, ID, osal::SystemError(NUM).getString().c_str() ))

#define osal_reraise(TYPE, ID) (ipl_reraise( TYPE, ID, osal::SystemError().getString().c_str() ))

#define osal_reraise_errnum(NUM, TYPE, ID) (ipl_reraise( TYPE, ID, osal::SystemError(NUM).getString().c_str() ))

#define osal_try_reraise(TYPE, ID) (ipl_try_reraise( TYPE, ID, osal::SystemError().getString().c_str() ))

} // end namespace

#endif
