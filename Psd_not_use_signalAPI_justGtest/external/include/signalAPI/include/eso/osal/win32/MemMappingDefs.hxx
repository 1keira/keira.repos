#ifndef OSAL_WIN32_MEMMAPPINGDEFS_HXX
#define OSAL_WIN32_MEMMAPPINGDEFS_HXX

namespace osal
{

struct MemMappingHandle
{
    void *addr;
    // the handle from CreateFileMapping
    HANDLE mapping;
    bool ringbuffer;

    MemMappingHandle()
    {
        invalidate();
    }

    void invalidate()
    {
        addr = NULL;
        mapping = INVALID_HANDLE_VALUE;
        ringbuffer = false;
    }

    bool haveMapping() const
    {
        return mapping != INVALID_HANDLE_VALUE;
    }
};

} // end ns osal

#endif
