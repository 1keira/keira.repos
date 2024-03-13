/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_MEMORYPOOL_HXX
#define COMMON_MEMORYPOOL_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <string.h>

#include <common/types/new.hxx>
#include <common/GlobalErrorHandler.hxx>
#include <common/Macros.hxx>
#include <common/NonCopyable.hxx>
#include <common/ScopeGuard.hxx>
#include <common/const_assert.hxx>
#include <common/stdint.h>
#include <common/types/vector.hxx>

namespace IPL_NAMESPACE
{

/*
 * The MemoryPool takes two additional template parameters that define
 * the types to use for thread synchronization (lock and condition).
 * This allows to use the same pool with and without thread
 * synchronization overhead.
 *
 * The following FakeLock and FakeCondition types are the ones used by
 * default that do no synchronization at all. Thus the default variant
 * of a MemoryPool will not be thread safe.
 *
 * On a level where you get your hands onto some actual locks and
 * conditions (e.g. the OSAL level) you can start using the pool with
 * real types and thus get a thread-safe pool.
 */

// fwd. declarations for default template arguments
struct FakeLock;
struct FakeCondition;
struct NullOnDepletion;

/**
 * \brief
 *     A generic, raw memory pool implementation

 *     This memory pool allows pre-allocation of a fixed number of
 *     items of a certain size. It is raw in that it doesn't handle
 *     actual types or objects but only raw chunks of memory.
 *
 *     The fixed pool allocation reduces runtime penalties due to use
 *     of dynamic memory and increases predictability of runtime
 *     behaviour in both time and memory requirements. Heap
 *     fragmentation is alleviated.
 *
 *     This pool does not allow to allocate an array of items. Only
 *     single items can be handled. This allows for a very simple
 *     implementations of the pool (resulting in very small performance
 *     overhead).
 *
 *     Using the default template parameters of the pool leaves the
 *     pool not thread safe i.e. an instance of this pool may not be
 *     accessed in parallel by different threads. If you need that
 *     then you need to pass suitable LOCK and CONDITION types to the
 *     template. LOCK and CONDITION need to fulfill an interface
 *     contract as shown in the FakeLock and FakeCondition classes.
 *
 *     The CONDITION type is only needed if you want to be able to wait
 *     for a ressource to become available once the pool is full (\see
 *     getItem(bool) ).
 *
 *     Further specialized pools can account for additional needs that
 *     are not covered by this basic implementation.

 *     \code
 *     // simple malloc/free like scheme
 *     MemoryPool<> default_pool;
 *     void* item = default_pool.getItem();
 *     default_pool.freeItem(item);
 *     \endcode
 **/
template <
    typename POLICY = NullOnDepletion,
    typename LOCK = FakeLock,
    typename CONDITION = FakeCondition>
class MemoryPool :
    // copying a pool would be unfortunate
    public ipl::NonCopyable
{
protected:
    //! simple LockGuard for template-LOCK usage (internal use)
    struct LockGuard :
        public ScopeGuard< const LOCK,
            bool(LOCK::*)(void) const >
    {
        LockGuard( const LOCK& l ) IPL_NOEXCEPT :
            ScopeGuard< const LOCK,
                bool(LOCK::*)(void) const >(
                    l, &LOCK::unlock)
        { this->m_valid = true; if(l.lock()) ipl::GlobalErrorHandler::doAbort(__FILE__, __LINE__, __FUNCTION__, "error locking"); } // BRANCH_COVERAGE_UNTESTABLE
    };

public:
    /**
     * \brief
     *    Creates a pool providing exactly \c item_count items of
     *    size \c item_size bytes

     *     The items will be immediatly allocated. When all items
     *     are in use then nothing can be done (to the pool) to get
     *     more items. This might be done via appropriate
     *     deplection policy template paremeters.
     * \param[in] p
     *     You can pass an object of type POLICY to construct the
     *     policy the pool uses from. By default the default
     *     constructor of it is applied.
     **/
    MemoryPool(
        const size_t item_size,
        const size_t item_count,
        POLICY p = POLICY() ) IPL_NOEXCEPT :
            m_item_size(item_size),
            m_item_count(item_count),
            // this allocates all items in a single block
            m_memblock_start( new(ipl::nothrow)
                uint8_t[item_size * item_count]),
            m_memblock_end( m_memblock_start +
                (item_count * item_size) ),
            m_depletion_policy(p),
            m_free(item_size, item_count, m_memblock_start)
    {
        IPL_ASSERT( m_memblock_start );
        // forward parameters to policy
        m_depletion_policy.setPars( item_size, item_count );

        // regarding aligment you may want to read BOOST
        // documentation:
        // http://www.boost.org/doc/libs/1_41_0/libs/pool/doc/implementation/alignment.html
        //
        // in principle it says: arrays may not introduce
        // additional padding (only types may do). Thus
        // sizeof(RESSOURCE) needs to return a size that is
        // suitable to setup an array of RESSOURCE without extra
        // padding between the items.
    }

    //! \brief
    //!    Assert that all items have been returned and free memory
    //!    block
    //! \note
    //!    Assertion does not cover items that have been possibly
    //!    acquired via the POLICY implementation.
    ~MemoryPool() IPL_NOEXCEPT
    {
//        IPL_ASSERT( ! m_free.used() );
        delete[] m_memblock_start;
    }

    //! \brief
    //! number of items left available in the pool (before the
    //! policy is called for help)
    size_t itemsLeft() const IPL_NOEXCEPT
    {
        LockGuard g( m_lock );
        return m_free.left() + m_depletion_policy.itemsLeft();
    }

    //! \brief
    //! number of items already in use (including any items obtained
    //! from the policy)
    size_t itemsUsed() const IPL_NOEXCEPT
    {
        LockGuard g( m_lock );
        return m_free.used() + m_depletion_policy.itemsUsed();
    }

    //! \brief
    //! returns whether \c item is an item that belongs to this pool
    //! (or its policy impl.)
    bool isFromHere(void *item) const IPL_NOEXCEPT
    {
        // maybe the depletion policy knows about it if not the
        // pool
        return this->isFromThisPool(item) ||
            m_depletion_policy.isThisYours(item);
    }

    //! \brief
    //! makes \c item available to the pool again, zero pointers
    //! allowed.
    void freeItem(void *item) IPL_NOEXCEPT
    {
        if( ! item )
            return;

        LockGuard g( m_lock );

        if( this->isFromThisPool( item ) )
        {
            m_free.push( (uint8_t*)item );

            // notify possible waiter
            const bool error = m_free_item.signal();
            IPL_ASSERT(!error);
            (void)error;
        }
        else
        {
            // assume it's from the depletion policy
            m_depletion_policy.thankYou(item);
        }
    }

    /**
     * \brief
     *     Returns an item from the pool for use by the caller.

     *     It tries to acquire a fixed allocated item, if that
     *     fails the depletion policy is called for help. What
     *     happens then depends on the policy.
     * \param[in] allow_wait
     *     If set to true then if currently the pool is depleted it
     *     will be waited for an item to be returned to the pool by
     *     another thread. This is only possible if suitable LOCK
     *     and CONDITION template types have been passed. Using the
     *     default LOCK and CONDITION will result in runtime
     *     errors.
     *     <br>
     *     Also note that the wait will be infinite if no other
     *     thread will ever return an item to the pool.
     *     <br>
     *     When using this option the depletion policy will *not*
     *     be called.
     * \return
     *     Pointer to the newly acquired item or NULL if it wasn't
     *     possible to acquire an item.
     **/
    void* getItem(const bool allow_wait = false) IPL_NOEXCEPT
    {
        LockGuard g( m_lock );

        // if no waiting is requested we either immediatly
        // return a new item or ask the policy for help
        if( ! allow_wait )
        {
            return m_free.left() ?
                m_free.pop() :
                m_depletion_policy.getHelp();
        }

        // if wait is requested then we never turn to the
        // depletion policy for help
        while( ! m_free.left() )
        {
            const bool error = m_free_item.wait( m_lock );
            IPL_ASSERT(! error);
            (void)error;
        }

        return m_free.pop();
    }

    //! \brief
    //! Returns the maximum size per pool item as given at
    //! construction time
    size_t itemSize() const IPL_NOEXCEPT
    { return m_item_size; }

protected:
    //! \brief
    //!    determine whether an item is exactly from this pool
    //!
    //!    But not from the associated depletion policy.
    bool isFromThisPool(void *item) const IPL_NOEXCEPT
    {
        if( ((uint8_t*)item >= m_memblock_start &&
            (uint8_t*)item < m_memblock_end) )
        {
            return true;
        }

        return false;
    }

    /**
     * \brief
     *     Lightweight stack of free items in the pool

     *     The stack keeps the number of free items in no
     *     particular order, putting returned items on top of the
     *     stack, returning items from the top of the stack.
     * \note
     *     This sort of free stack doesn't allow to return a
     *     continuous range of items (i.e. an array of items)
     **/
    class FreeStack
    {
    public:
        /**
         * \brief
         *     Create a stack for \c items items that will take
         *     it's addresses from the array of \c item items
         *     present at \c init.
         **/
        FreeStack(const size_t item_size,
            const size_t item_count,
            uint8_t *init) IPL_NOEXCEPT :
            m_left(item_count),
            m_size(item_count)
        {
            IPL_ASSERT(init);
            /*
             *    We simply allocate an array of pointers
             *    to the actual items. This introduces an
             *    overhead of one pointer per item i.e. if
             *    you use this with very small items (e.g.
             *    int's) then you have a memory overhead
             *    of 100 %).
             *
             *    It could be alleviated by using some
             *    kind block scheme that only handles
             *    tiles of items of a certain amount e.g.
             *    one entry per N items. The entry would
             *    consists of the pointer to the first
             *    item plus a bitfield of which of the N
             *    items is actually used or not.
             *
             *    But such modifications would complicate
             *    other things again (fragmentation,
             *    lookup issues)
             */
            IPL_NEW(m_stack,
                new(ipl::nothrow) uint8_t*[item_count],
                "need free stack");

            // initialize the stack with the actual items -
            // at the start all items are available i.e. the
            // stack is at maximum capacity.
            for( size_t item = 0;
                item < m_size;
                item++, init += item_size )
            {
                m_stack[item] = init;
            }
        }

        //! deletes the stack memory
        ~FreeStack() IPL_NOEXCEPT
        { delete[] m_stack; }

        //! number of items still available in the stack
        size_t left() const IPL_NOEXCEPT
        { return m_left; }

        //! number of items currently in use from the stack
        size_t used() const IPL_NOEXCEPT
        { return m_size - m_left; }

        //! return an item to the stack
        void push(uint8_t *item) IPL_NOEXCEPT
        {
            IPL_ASSERT( m_left < m_size );
            m_stack[m_left] = item;
            m_left++;
        }

        //! retrieve an item from the stack
        uint8_t* pop() IPL_NOEXCEPT
        {
            IPL_ASSERT( m_left != 0 );
            m_left--;
            return m_stack[m_left];
        }
    private:
        //! \brief
        //! an array of pointers to items, representing the
        //! stack
        uint8_t **m_stack;

        //! \brief
        //! the number of items left in the stack (the top item
        //! is m_stack[m_left-1])
        size_t m_left;

        //! complete size of the pool
        const size_t m_size;
    };

private: // members
    //! size of a single item
    const size_t m_item_size;
    //! number of fixed items managed by the pool
    const size_t m_item_count;

    //! the complete memory block allocated during construction time
    uint8_t * const m_memblock_start;
    //! pointer past the last item in the allocated memblock
    uint8_t * const m_memblock_end;

    //! for synchronization in case of multi-threaded access
    LOCK m_lock;

    //! to wait for new items in case the pool is depleted
    CONDITION m_free_item;

    //! helper in case of depletion
    POLICY m_depletion_policy;

    //! manages all free fixed-allocated items for the pool
    FreeStack m_free;
};

/**
 * \brief
 *     A derived pool that binds the MemoryPool base class to an object
 *     of type \c T

 *    The semantic of this pool are the same as of the base class
 *    MemoryPool except it operates on items of the specific type \c
 *    T. This knowledge makes it possible to construct and destroy the
 *    items for the client.
 **/
template <
    typename T,
    typename POLICY = NullOnDepletion,
    typename LOCK = FakeLock,
    typename CONDITION = FakeCondition>
class ObjectPool :
    public ipl::MemoryPool<POLICY, LOCK, CONDITION>
{
public:
    /**
     * \brief
     *    Construct the pool for \c item_count items of type \c T
     * \note
     *     Leaves out item_size as it is defined by T
     * \see
     *     MemoryPool(const size_t, const size_t, POLICY)
     **/
    ObjectPool(const size_t item_count, POLICY p = POLICY() ) IPL_NOEXCEPT :
        ipl::MemoryPool<POLICY, LOCK, CONDITION>(
            sizeof(T), item_count, p)
    { }

    /**
     * \brief
     *     Does the same as MemoryPool::getItem but additionally
     *     calls copy-constructor for \c T

     *     The provided parameter \c other will be passed to the
     *     copy constructor of \c T to construct the newly returned
     *     item. A correctly typed pointer will be returned.
     *
     *     If allocation failed then, of course, no construction is
     *     performed.
     *  \warning
     *     This costs a copy operation (note the name
     *     'copy-constructor')
     *     <br>
     *     Sadly there's no other obvious way of allowing arbitrary
     *     construction of T without using overloaded new which has
     *     it's very own problems again.
     **/
    T* getObj(const T &other = T(), const bool allow_wait = false) IPL_NOEXCEPT
    {
        T* ret = static_cast<T*>(
            ipl::MemoryPool<POLICY,
                LOCK,
                CONDITION>::getItem(allow_wait));

        if( ret )
        {
            new(ret) T(other);
        }

        return ret;
    }

    /**
     * \brief
     *     Construct an object of type T from default constructor
     * \see
     *     getObj(const T&, const bool)
     **/
    T* getDefObj(const bool allow_wait = false) IPL_NOEXCEPT
    {
        T* ret = static_cast<T*>(
            ipl::MemoryPool<POLICY,
                LOCK,
                CONDITION>::getItem(allow_wait));

        if( ret )
        {
            new(ret) T();
        }

        return ret;
    }

    //! \brief
    //!    Calls destructor for \c item, if not NULL. Then frees
    //!    the item as freeItem() does.
    void freeObj(T *item) IPL_NOEXCEPT
    {
        if( item )
            item->~T();

        this->freeItem(item);
    }
};

/**
 * \brief
 *     A class that feels like a lock but isn't actually one

 *     Fulfills the interface contract of a lock but doesn't actually
 *     lock anything.
 **/
struct FakeLock
{
    bool lock() const IPL_NOEXCEPT { return false; };

    bool unlock() const IPL_NOEXCEPT { return false; };
};

/**
 * \brief
 *     A class that feels like a condition but isn't actually one

 *     Fulfills the interface contract of a condition but doesn't
 *     actually do anything.
 **/
struct FakeCondition
{
    //! runtime error is raised if called.
    template<typename FAKELOCK>
    bool wait(FAKELOCK &lock) IPL_NOEXCEPT
    { IPL_ABORT("Attempt to wait on fake condition"); return true; }

    bool signal() IPL_NOEXCEPT
    { return false; }
};


/**
 * \brief
 *     Base class for depletion policy types

 *     A depletion policy type is used in conjunction with memory
 *     pools.
 *
 *     It determines what to do when a memory pool runs out of items.
 *     It is called in context of the getItem() and freeItem()
 *     functions. But only in case of the pool itself can't fullfil a
 *     request for an item any more due to depletion.
 *
 *     It depends on the depletion policy implementation what happens
 *     then. Generally there are the following options (some more
 *     exotic ones maybe tought of):
 *
 *     - abort program execution (maybe after doing some logging or
 *     similar)
 *     - satisfy the request for an item from some other source unknown
 *     to the original pool
 *
 *     This is merely the base class for actual policies to derive
 *     from. The functions aren't virtual to avoid runtime penalties.
 *     Instead this works via an interface contract. You need to
 *     implement the functions presented in this base class.
 *
 *     Thus if you don't want to use the base class you can avoid that.
 *     But deriving from the base class allows easy override of only
 *     some of the functions, keeping the others at default behaviour.
 *
 *     Also having the base class allows for clearer documentation of
 *     the required API.
 * \note
 *     A depletion policy does not need to worry about concurrent
 *     access. If the associated pool is constructed as a thread-safe
 *     pool then the calls to the policy will happen in a serialized
 *     way.
 */
struct IDepletionPolicy
{
    virtual ~IDepletionPolicy() {}

    /**
     * \brief
     *     Try to help the calling pool to satisfy a request for an
     *     item

     *     The base implementation returns a NULL pointer against
     *     the client of a pool can check (behaviour like
     *     malloc()/new(ipl::nothrow)
     * \return
     *     If the policy object returns then it should be either
     *     NULL or a pointer to a memory area of the correct size.
     **/
    virtual void* getHelp() IPL_NOEXCEPT
    { return NULL; }

    /**
     * \brief
     *     Takes back a pointer to an item previously returned from
     *     getHelp()

     *     The base implementation only honors NULL pointers,
     *     everything else raises a runtime error.
     * \param[in] ptr
     *     A pointer to an item that doesn't belong to the calling
     *     pool. Maybe NULL.  May also be not an item from the
     *     policy at all (if there is an error in pool client
     *     code).
     **/
    virtual void thankYou(void *ptr) IPL_NOEXCEPT
    { IPL_ASSERT( ! ptr ); }

    /**
     * \brief
     *     Returns the number of items that have been allocated
     *     with this policy object's help

     *     The base implementation doesn't provide any extra items
     *     thus here always zero is returned.
     **/
    virtual size_t itemsUsed() const IPL_NOEXCEPT
    { return 0; }

    /**
     * \brief
     *     Returns the number of items that the policy can provide
     *     without acquiring any dynamic ressources

     *     The base implementation doesn't provide any extra items
     *     thus here always zero is returned.
     **/
    virtual size_t itemsLeft() const IPL_NOEXCEPT
    { return 0; }

    /**
     * \brief
     *     Returns whether the given ptr originates from this
     *     policy object

     *     Base implementation doesn't own any ptrs. thus returns
     *     always false.
     **/
    virtual bool isThisYours(void *ptr) const IPL_NOEXCEPT
    { return false; }



    /**
     * \brief
     *     This function is called once upon pool construction to
     *     pass on the construction parameters to the policy.

     *     \a item_size gives the size of each item and pool_size
     *     gives the number of items the calling pools is
     *     providing. These data can be needed to fulfill the job
     *     of the policy but might also be ignored silently if not
     *     so.
     *
     *     Base implementation doesn't do anything with this.

     * \note
     *     \a item_size and \a pool_size aren't expected to change
     *     during the lifetime of a policy or until the pool calls
     *     setPars() again.
     **/
    virtual void setPars(const size_t item_size, const size_t pool_size) IPL_NOEXCEPT
    {}
};

//! \brief
//! keeps the defaults of the base class thus returning NULL on
//! depletion
struct NullOnDepletion :
    public IDepletionPolicy
{ };

/**
 * \brief
 *     This policy sets up more pools in case the current one is
 *     depleted
 *     The size of the pools that are constructed grow exponentially in
 *     size to avoid having too much pools as allocation grows.
 *
 *     When enough items are freed again such that a pool in the
 *     chain becomes empty again then that pool will be freed.
 **/
struct UsePoolOnDepletion :
    public IDepletionPolicy
{
    //! You need to specify the size of the pool to be allocated
    UsePoolOnDepletion() IPL_NOEXCEPT :
        m_pool_size(0),
        m_item_size(0),
        m_free_items(),
        m_free_pool(NULL)
    { }

    void setPars(const size_t item_size, const size_t pool_size) IPL_NOEXCEPT override
    {
        m_item_size = item_size;
        m_pool_size = pool_size;
    }

    void* getHelp() IPL_NOEXCEPT override
    {
        if( !m_free_pool || !m_free_pool->itemsLeft() )
        {
            void *ret;

            if( m_free_items )
            {
                for( size_t i = 0; i < m_pools.size(); i++ )
                {
                    if( (ret = m_pools[i]->getItem()) )
                    {
                        m_free_pool = m_pools[i];
                        m_free_items--;
                        return ret;
                    }
                }
            }

            ipl::MemoryPool<NullOnDepletion> *pool;

            m_pool_size <<= 1;

            // create a new pool
            IPL_NEW(pool, // BRANCH_COVERAGE_UNTESTABLE
                new(ipl::nothrow)
                    ipl::MemoryPool<NullOnDepletion>(
                    m_item_size, m_pool_size),
                "need another pool");

            m_pools.push_back(pool);
            m_free_pool = pool;
            m_free_items += m_pool_size - 1;

            return pool->getItem();
        }

        return m_free_pool->getItem();
    }

    void thankYou(void *ptr) IPL_NOEXCEPT override
    {
        for( size_t i = m_pools.size() - 1; i < m_pools.size(); i-- )
        {
            if( m_pools[i]->isFromHere(ptr) )
            {
                m_pools[i]->freeItem(ptr);
                m_free_items--;

                if( ! m_pools[i]->itemsUsed() )
                {
                    if( m_free_pool == m_pools[i] )
                        m_free_pool = NULL;

                    // free the pool
                    delete m_pools[i];
                    m_pools.erase( m_pools.begin() + (long)i );

                    m_pool_size >>= 1;
                }

                return;
            }
        }

        IPL_ABORT("item is not from here!");
    }

    bool isThisYours(void *ptr) const IPL_NOEXCEPT override
    {
        for( size_t i = 0; i < m_pools.size(); i++ )
        {
            if( m_pools[i]->isFromHere(ptr) )
                return true;
        }

        return false;
    }

    size_t itemsUsed() const IPL_NOEXCEPT override
    {
        if( m_pools.empty() )
            return 0;

        size_t ret = 0;

        for( size_t i = 0; i < m_pools.size(); i++ )
        {
            ret += m_pools[i]->itemsUsed();
        }

        return ret;
    }

    size_t itemsLeft() const IPL_NOEXCEPT override
    {
        return m_free_items;
    }
private:
    size_t m_pool_size;
    size_t m_item_size;
    size_t m_free_items;

    ipl::vector< ipl::MemoryPool<NullOnDepletion>* > m_pools;
    ipl::MemoryPool<NullOnDepletion> *m_free_pool;

};

//! overwrites getHelp such that execution will be aborted
struct AbortOnDepletion :
    public IDepletionPolicy
{
    void* getHelp() IPL_NOEXCEPT override
    {
        IPL_ABORT("Memory pool is depleted");
        return NULL;
    }
};


//! \brief
//! This policy implementation switches to heap-allocation in case a
//! pool is depleted
struct UseHeapOnDepletion :
    public IDepletionPolicy
{
    /**
     * \param[in] max_heap_items
     *     If set to non-zero then this determines an upper limit
     *     on the number of items allocated from the heap. If this
     *     many items are around then getHelp() will return NULL on
     *     further requests until some items have been freed from
     *     the heap.
     **/
    UseHeapOnDepletion(const size_t max_heap_items = 0) IPL_NOEXCEPT :
        m_item_size(0),
        m_heap_items(0),
        m_max_heap_items(max_heap_items)
    {}

    void setPars(const size_t item_size, const size_t pool_size) IPL_NOEXCEPT override
    { m_item_size = item_size; }

    void* getHelp() IPL_NOEXCEPT override
    {
        if( m_max_heap_items &&
            m_heap_items >= m_max_heap_items )
        {
            // limit has been reached
            return NULL;
        }

        // we allocate more than item_size. at the end of the
        // memory area we place a ptr to this object. This
        // allows to check whether a ptr. really is from us at
        // thankYou().  note, of course, that this wastes memory
        void *ret = ::malloc(m_item_size + sizeof(this) );

        if(ret) { // BRANCH_COVERAGE_UNTESTABLE
#ifdef IPL_DEBUG
            // if not done this way then valgrind complains about
            // unitialized values
            ::memset( (uint8_t*)ret + m_item_size, 0, sizeof(this) );
#endif

            UseHeapOnDepletion* p = this; // &this doesn't work
            ::memcpy( (uint8_t*)ret + m_item_size, &p, sizeof(p) );

            m_heap_items++;
        }

        return ret;
    }

    void thankYou(void *ptr) IPL_NOEXCEPT override
    {
        if(!ptr) return;

        // make sure this really is from us
        IPL_ASSERT( this->isThisYours(ptr) );

        ::free(ptr);

        m_heap_items--;
    }

    bool isThisYours(void *ptr) const IPL_NOEXCEPT override
    {
        const UseHeapOnDepletion* p = this; // &this doesn't work
        return ::memcmp( (uint8_t*)ptr + m_item_size, &p, sizeof(p) ) == 0;
    }

    size_t itemsUsed() const IPL_NOEXCEPT override
    { return m_heap_items; }
private:
    size_t m_item_size;

    //! number of heap items allocated by this policy object
    size_t m_heap_items;

    //! \brief
    //! maximum number of heap items to be allocated by this policy,
    //! zero if unlimited
    size_t m_max_heap_items;
};

/*
 *    A story on C++ memory management, by mage2618
 *    ---------------------------------------------
 *
 *    I've tried a number of approach for smartly replacing the
 *    default memory management of C++ for certains parts of code with
 *    memory pool allocation. The ideal requirements have been these:
 *
 *    1) Allow to replace the memory allocation for just a specific
 *    piece of code
 *    2) Allow to use the alternative memory allocation in an
 *    intuitive way with using overloaded new/delete operators
 *    3) Make it possible to easily tell an STL container object to
 *    use the alternative memory allocation instead of the default one
 *    (via template ALLOCATORs)
 *
 *     All three requirements cannot be met together. This is for the
 *     following reasons:
 *
 *     - You can't really overload operator new/delete. This means that
 *     you *can* overload the operators but not the keywords
 *     new/delete. Even more specific: You can overload the new keyword
 *     but not the delete keyword. Let me demonstrate:
 *
 *     class Obj;
 *    // allocates memory for Obj and calls the Obj constructor with 5
 *     Obj *o = new Obj(5);
 *
 *     // assume we have some overloaded version of operator new
 *     void* operator new(size_t, Obj) { ... }
 *
 *    // allocates memory for Obj but does _not_ call any Obj constructor
 *     Obj *o = (Obj*)operator new(sizeof(Obj));
 *
 *     // calls overloaded version of new with Obj(), assume it
 *     // allocates the memory, then the // compiler calls the Obj
 *     // constructor with 5
 *     Obj *o = new(Obj()) Obj(5);
 *
 *     // calls destructor ~Obj() for the object at location o. Frees
 *     // the memory at location o.
 *     delete o;
 *
 *     // assume we have some overloaded version of operator delete
 *     operator delete(void*, Obj) { ... }
 *
 *     // calls overloaded operator delete with Obj() which can then
 *     // free the memory at location o.  // The object is *not* destroyed
 *     // via ~Obj()!
 *     operator delete(o, Obj());
 *
 *     // invalid syntax. delete keyword cannot be called this way.
 *     delete(Obj()) o;
 *
 *     Thus as you can see there is no way to correctly overloaded
 *     new/delete to make a different allocation model possible in a
 *     transparent way. The overloaded operator delete is only used in
 *     one place (as can be read in "efficient c++" by scott meyers).
 *     This is when you have exceptions available (using real c++
 *     unlike us) and you have overloaded operator new/delete as above.
 *     Then if allocating memory from the overloaded new operator
 *     succeeds but construction of Obj() fails by throwing an
 *     exception the compiler will automatically call the matching
 *     overloaded operator delete to free the memory again before
 *     passing on the exception.
 *
 *     This effectively kills requirement 2)
 *
 *     Requirement 3) is killed, because STL containers require array
 *     allocation. If you need to write a memory pool that supports
 *     this then you end up in writing a fully fledged heap which gives
 *     away the simplicity and efficiency of the original pool concept.
 *
 *     Requirement 1) is killed, because the only possibility to
 *     transparently replace the c++ memory management model is by
 *     overwriting the global new/delete operators which causes the
 *     complete process to use this new model. This is unsuitable for a
 *     framework and worse different parts of application models might
 *     try to replace new/delete concurrently.
 *
 *     For all these reason we resorted to this simple MemoryPool
 *     applying only to raw items in a malloc/free like way. The
 *     ObjectPool then adds a type-binding on top of it. Arbitrary
 *     construction there is only possible via a copy-constructor that
 *     requires a copy operation.
 */

} // end namespace ipl

#endif // include guard
