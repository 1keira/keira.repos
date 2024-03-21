/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_NOOPPTR_HXX
#define UTIL_NOOPPTR_HXX

#include <ipl_config.h>
#include <util/SharedPtr.hxx>

namespace util
{

inline void noop(void *, void *)
{}

/**
 *    \brief
 *        This is a shortcut class that instantiates a SharedPtr that doesn't to deletions
 *        when the reference count hits zero.
 **/
template <class TYPE>
class NoOpPtr :
    public SharedPtr<TYPE>
{
public:
    /**
     *    \brief
     *        Same as SharedPtr(TYPE*, const bool) but with a custom deletion function.

     *        Instead of calling delete or delete[] call the given custom deletion
     *        function upon reference count hitting zero.
     **/
    inline NoOpPtr(TYPE *p_object_ptr) IPL_NOEXCEPT :
        SharedPtr<TYPE>(p_object_ptr, &noop)
    { }
}; // end class NoOpPtr

} // end namespace

#endif
