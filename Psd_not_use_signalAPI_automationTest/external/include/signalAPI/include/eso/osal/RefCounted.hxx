/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_REFCOUNTED_HXX
#define OSAL_REFCOUNTED_HXX

#include <common/MemoryPool.hxx>
#include <osal/osal_dso.h>
#include <osal/AtomicCounter.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>

namespace osal {

    /**
    * \brief
    *    OSAL-internal base class for objects that need to be reference
    *    counted.

    *    Users need to derive from this class, implement the pure virtual
    *    destroy() member function (here the code should go that cleans
    *    up as soon as the reference count hits zero) and in the
    *    destructor of the derived class RefCounted::decrement() needs to
    *    be called.
    **/
    class OSAL_EXPORT RefCounted
    {
    public:
        /**
        * \brief
        *    Creates a new object that's not shared.
        **/
        RefCounted() :
            m_counter()
        {
            checkInit();

            //! get a new counter from the counter pool
            m_counter = s_counter_pool->getObj( osal::AtomicCounter(1) );
        }

        /**
        * \brief
        *    Does reference counting and closes the associated system
        *    object and ressources.
        **/
        virtual ~RefCounted() { }

        RefCounted(const RefCounted &other) :
            m_counter(NULL)
        { operator=(other); }

        RefCounted& operator=(const RefCounted &other)
        {
            if( this == &other )
                return *this;

            // when called from copy-ctor, then m_counter is invalid
            if( m_counter )
                decrement();

            m_counter = other.m_counter;

            if( m_counter )
                m_counter->increment();
            return *this;
        }

    protected: // functions
        friend class osal::Osal;

        virtual void destroy() = 0;

        void decrement()
        {
            if( m_counter->decrement() == 1 )
            {
                destroy();
                s_counter_pool->freeObj( m_counter );
                m_counter = NULL;
            }
        }

        // NOTE: see util/sharedptr/RefCounted.hxx for some comments on checkInit(), doInit(), doExit()
        static void doInit()
        {
            IPL_NEW( s_counter_pool,
                (new ipl::ObjectPool< osal::AtomicCounter,
                    ipl::UsePoolOnDepletion,
                    osal::Mutex >( 1024UL )),
                "need counter pool" );
        }

        static void doExit()
        {
        }

        static void checkInit()
        {
            IPL_MUTEX_LOCK_OR_ABORT( s_init_lock );
            if ( 0 == s_init_counter.exchangeIf(1, 0) ) {
                doInit();
            }
            IPL_MUTEX_UNLOCK_OR_ABORT( s_init_lock );
        }
    private:
        //! \brief
        //! We do some reference counting for allowing flat copy of
        //! Directory objects.
        osal::AtomicCounter *m_counter;

        //! \brief
        //! a big, static pool that for counters that works in a
        //! block-allocation-scheme manner
        static ipl::ObjectPool
            < osal::AtomicCounter, ipl::UsePoolOnDepletion,
                osal::Mutex >
            *s_counter_pool;

        static osal::AtomicCounter
            s_init_counter;

        static osal::Mutex
            s_init_lock;
    };

}  // end of namespace osal

#endif
