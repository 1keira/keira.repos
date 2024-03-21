/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_FILE_ACCESS_ERROR_HXX
#define OSAL_FILE_ACCESS_ERROR_HXX

#include <common/error/Error.hxx>

#include <osal/osal_dso.h>
#include <osal/SystemError.hxx>

namespace osal
{

/**
 * \brief
 *    Specialized error for open/access operations of file system
 *    objects

 *    A FileAccessError is usually a more abstract osal::SysError. It
 *    is usually attached onto an osal::SysError.
 *
 *    Notably a FileAccessError is passed an additional file system
 *    path that caused the error. This is not the case with
 *    osal::SysError.
 **/
enum FileAccessErrors
{
    //! used if a path could not be found
    BAD_PATH = 0,
    //! used if a path was expected to be a directory but isn't
    NO_DIR,
    //! used if a path wasn't expected to be a directory but is
    IS_DIR,
    //! \brief
    //! used if all or part of a path exists but cannot be accessed
    //! due to lack of access rights
    NO_ACCESS,
    //! \brief
    //! a file system object already exists which is considered an
    //! error
    ALREADY_EXISTS,
    //! \brief
    //! a file system object exists and is in use by somebody which
    //! is considered an error
    FILE_BUSY,
    //! \brief
    //! another file cannot be accessed as too many files are
    //! currently opened by the current process or the whole system
    TOO_MANY_OPEN_FILES,
    //! \brief
    //! an operation on the file system cannot be performed due to
    //! lack of file system space
    NOT_ENOUGH_SPACE,
    //! \brief
    //! an operation on a file cannot be performed due to file
    //! system or hardware failure
    DEVICE_FAILURE,
    //! some other, unclassified error during accessing a file
    //! occured
    UNKNOWN_OPEN_ERROR,
    //! same as UNKNOWN_OPEN_ERROR
    UNKNOWN_ACCESS_ERROR = UNKNOWN_OPEN_ERROR
};

//! for backward compatibility. was formerly called OpenError
typedef FileAccessErrors OpenErrors;

/**
 * \brief
 *    General system call error descriptions plus OS dependant error
 *    strings
 **/
const ipl::ErrorID FILE_ACCESS_ERROR_TABLE[] =
{
    { BAD_PATH, "Bad path '%s'", 1 },
    { NO_DIR, "Path '%s' is not a directory", 1 },
    { IS_DIR, "Path '%s' is a directory", 1 },
    { NO_ACCESS, "Access to path '%s' denied", 1 },
    { ALREADY_EXISTS, "'%s' is already existing", 1 },
    { FILE_BUSY, "Path '%s' is busy", 1 },
    { TOO_MANY_OPEN_FILES, "Can't get file descriptor for path '%s'", 1 },
    { NOT_ENOUGH_SPACE, "Not enough space to create '%s'", 1 },
    { DEVICE_FAILURE, "Given device '%s' is not existing or not ready", 1 },
    { UNKNOWN_OPEN_ERROR, "Unclassified open/access error occured for path '%s'", 1 }
};

/**
 * \brief
 *    The glocal SysError object used for raising them.
 **/
OSAL_EXPORT extern ipl::ErrorType FileAccessError;

//! for backward compatibility. was formerly called OpenError
OSAL_EXPORT extern ipl::ErrorType &OpenError;

} // end namespace

#endif
