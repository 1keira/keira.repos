/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_FILEDEFS_HXX
#define OSAL_POSIX_FILEDEFS_HXX

#include "FileInfoDefs.hxx"

namespace osal {

    typedef int FileHandle;

    const FileHandle OSAL_INVALID_FILE_HANDLE = -1;

    struct FileOps {
        
        /*!
            \brief Common open error handling code
            
            \param[in] p The offending path
            \return \c true on interrupt error, \c false otherwise
        */
        static bool handleOpenError(int error, const char *p);

        static bool getFileInfoHandle(const FileHandle &handle,
            FileInfoHandle *out);
    };

}  // end of namespace osal

#endif
