/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_ENVIRONMENTDEFS_HXX
#define OSAL_POSIX_ENVIRONMENTDEFS_HXX

namespace osal {

    //! \brief Pointer to start and end of environment
    typedef struct {
        const char **start;
        const char **end;
    } EnvironmentHandle;

    typedef const char **EnvironmentIteratorHandle;

}  // end of namespace osal

#endif
