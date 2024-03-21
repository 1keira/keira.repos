/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_MEMORYPOOL_HXX
#define UTIL_MEMORYPOOL_HXX

#include <ipl_config.h>
#include <common/MemoryPool.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <util/SharedPtr.hxx>

namespace util
{

/**
 * \brief
 *     thread-safe variant of ipl::ObjectPool that also can return
 *     SharedPtr objects

 *     This class derives from ipl::ObjectPool, specializing its LOCK
 *     and CONDITION parameters with the according OSAL objects. Thus
 *     this is a thread-safe pool.
 *
 *     Additionally the getSharedPtr function is provided that returns
 *     a SharedPtr to an object from the pool.
 **/
template< typename T, typename POLICY = ipl::NullOnDepletion >
class ObjectPool :
    public ipl::ObjectPool<T, POLICY, osal::Mutex, osal::Condition >
{
public:
    ObjectPool(const size_t item_count, POLICY p = POLICY() ) IPL_NOEXCEPT :
        ipl::ObjectPool<T, POLICY, osal::Mutex, osal::Condition>(item_count, p)
    { }

    //! \brief
    //!    Calls copy-constructor with given argument, returns correctly typed ptr.
    //! \warning
    //!    This costs a copy operation (note the name 'copy-constructor')
    T* getObj(const T &other = T(), const bool allow_wait = false) IPL_NOEXCEPT
    {
        // this function is repeated here to avoid users the lookup of the ipl::ObjectPool
        // just to see this functions documentation
        return ipl::ObjectPool<T, POLICY, osal::Mutex, osal::Condition>::getObj(other, allow_wait);
    }

    //! \brief
    //!    Does the same as getObj() but returns a SharedPtr to the new object
    //! \warning
    //!    The lifetime of a SharedPtr is not deterministic to clients. Still it needs to be
    //!    ensured that the pool instance this SharedPtr is retrieved from is valid as long as
    //!    the SharedPtr instance is around.
    util::SharedPtr<T> getSharedPtr(const T &other = T(), const bool allow_wait = false) IPL_NOEXCEPT
    {
        T* ret = this->getObj(other, allow_wait);

        return SharedPtr<T>(ret, &ObjectPool<T, POLICY>::deleteSharedItem, (void*)this);
    }

    //! \brief
    //!    Calls destructor for \c item, if not NULL. Then frees the item as freeItem() does.
    void freeObj(T *item) IPL_NOEXCEPT
    {
        // this function is repeated here to avoid users the lookup of the ipl::ObjectPool
        // just to see this functions documentation
        return ipl::ObjectPool<T, POLICY, osal::Mutex, osal::Condition>::freeObj(item);
    }

protected:
    //! internal use in combination with SharedPtr
    static void deleteSharedItem(void *item, void *context) IPL_NOEXCEPT
    {
        ObjectPool<T, POLICY> *pool = reinterpret_cast<ObjectPool<T, POLICY>*>(context);

        pool->freeObj( static_cast<T*>(item) );
    }
};

} // end namespace ipl

#endif
