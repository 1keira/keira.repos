#ifndef OSAL_WIN32_MEMFILEDEFS_HXX
#define OSAL_WIN32_MEMFILEDEFS_HXX

#include <common/types/map.hxx>
#include "BinFileDefs.hxx"

namespace osal {

    struct MemFileHandle {
        //! \brief Any registered memory mappings
        ipl::map< const void*, MemMapping > mappings;

        MemFileHandle() {}
    };

}  // end of namespace osal

#endif
