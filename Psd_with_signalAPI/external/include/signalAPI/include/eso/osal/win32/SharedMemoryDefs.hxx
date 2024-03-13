/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_SHAREDMEMORYDEFS_HXX
#define OSAL_WIN32_SHAREDMEMORYDEFS_HXX

#include <osal/common/LazyInit.hxx>
#include <osal/ShmMutex.hxx>
#include <osal/SemaphoreCreator.hxx>

namespace osal {

    struct SharedMemoryHandle
    {
        //! just a handle to the SHM, is of a file handle like type
        HANDLE fd;
        size_t size;
        // the slot in SharedMemMipl we occupy
        size_t shm_list_slot;

        SharedMemoryHandle()
        {
            this->invalidate();
        }

        void invalidate()
        {
            fd = INVALID_HANDLE_VALUE;
            size = 0;
            shm_list_slot = 0;
        }

        bool isValid() const
        {
            return fd != INVALID_HANDLE_VALUE;
        }
    };

    struct SharedMemoryServerHandle
    {
        /*
        * we don't need anything here on WIN32 currently
        */
        SharedMemoryServerHandle(const bool doc)
        {
            (void)doc;
        }
    };

    const SharedMemoryHandle INVALID_SHARED_MEMORY_HANDLE = SharedMemoryHandle();

    // SHM impl. that cares for keeping track of SHM object sizes in the
    // system
    class SharedMemImpl
    {
    public: // types

        // the maximum length of an SHM object
        static const size_t SHM_LIST_MAX_ENTRY_LEN = 32;

    private: // types
        // the structure of a single list entry in SHM
        struct ShmListEntry
        {
            // users of this SHM object, if it hits zero then
            // invalidation occurs
            size_t users;
            // used length of the name field in characters w/o
            // terminator, if zero then the entry is unused
            size_t name_len;
            // size of the SHM object denoted by the name field
            size_t shm_size;
            // the name of the SHM object
            native_utf name[SHM_LIST_MAX_ENTRY_LEN];
        };

        // the structure kept in the private SHM
        struct ShmData
        {
            // the data portion for the shm lock
            osal::ShmMutex::Data lock;
            // the amount of ShmListEntries that still fit into the
            // SHM
            size_t free_entries;
            // the start of the SHM name->length mapping list
            ShmListEntry list;
        };

        static const size_t SHM_DATA_HEADER_SIZE =
            sizeof(osal::ShmMutex::Data) + sizeof(size_t);

    private: // data
        // shared memory handle
        HANDLE shm;
        // memory mapping pointer
        void *memory;
        // size of SHM in bytes
        size_t shm_size;

        // lock for safely accessing SHM data once it is initialized
        osal::ShmMutex shm_lock;
        // semaphore for safely initializing private SHM
        osal::SemaphoreCreator sem;

        // type-safe access to SHM data
        ShmData *shm_data;
        // ptr. to the start of the list in SHM
        ShmListEntry *list_start;
        // ptr. past the end of the list in SHM
        ShmListEntry *list_end;

    private: // functions
        /**
        * \brief
        *     Returns a pointer to the entry for \c name in the shm
        *     object

        *     If \a name is not present in the shm object then NULL is
        *     returned.
        **/
        ShmListEntry* findEntry(const native_utf *name);

        //! find the next free entry in the SHM list
        ShmListEntry *findFreeEntry();
    public:
        SharedMemImpl() :
            shm(INVALID_HANDLE_VALUE),
            memory(),
            shm_size(),
            shm_lock(),
            sem(),
            shm_data(),
            list_start(),
            list_end()
        { }

        // initialize private SHM
        bool init();
        // free private SHM
        void exit();

        // lookup the size of SHM object \c name and return it
        size_t getSizeOf(const native_utf *name, size_t &shm_list_slot);
        // set the size of SHM object \c name to \c size
        size_t setSizeOf(const native_utf *name, const size_t size);
        // removes an SHM entry from the private SHM again
        void removeRef(const size_t shm_list_slot);
    };

    // the one and only SHM impl.
    extern SharedMemImpl *g_shm_impl;

    // for lazy initialization of g_shm_impl
    class LazySHMInit :
        public osal::LazyInit
    {
        bool doInit();
    };

    extern LazySHMInit *g_lazy_shm_init;

}  // end of namespace osal

#endif
