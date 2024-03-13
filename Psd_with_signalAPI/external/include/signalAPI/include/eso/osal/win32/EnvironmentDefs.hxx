/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_ENVIRONMENTDEFS_HXX
#define OSAL_WIN32_ENVIRONMENTDEFS_HXX

#include <osal/osal_dso.h>

namespace osal {

    //! \brief Handle for environment access
    typedef struct EHs {
        EHs(): start(NULL), end(NULL) {}

        //! \brief Pointer to a null-terminated list of null-terminated
        //! strings representing the environment
        const wchar_t *start;
        //! Pointer to the last, zero-sized string in the block
        const wchar_t *end;
    } EnvironmentHandle;

    struct EnvironmentIteratorHandle {
        const wchar_t *pos;
        // this is needed for being able to return ASCII variant of
        // environment variable
        mutable ipl::string cur_ascii;
        void OSAL_EXPORT update_ascii() const;
        
        EnvironmentIteratorHandle(const wchar_t *p = NULL): pos(p) {}

        bool operator==(const EnvironmentIteratorHandle &o) const
        {
            return pos == o.pos;
        }
    };

}  // end of namespace osal

#endif
