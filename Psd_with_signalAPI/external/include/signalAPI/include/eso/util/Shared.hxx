/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef UTIL_SHARED_HXX
#define UTIL_SHARED_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <osal/Mutex.hxx>
#include <util/SharedPtr.hxx>

/*****************************************************************************/

namespace util {

/*****************************************************************************/

    /*!
        \brief Shared object with automatic lifecycle management

        For any type T with a default constructor,
        a Shared<T> behaves like a SharedPtr to an instance of T that gets
        initialized, finalized and reinitialized (if necessary) on demand,
        i.e. first access initializes (lazily),
        last pointer vanishing destroys,
        new access initializes again.
        The underlying instance is allocated within the Shared<T> object,
        saving heap overhead.

    */
    template <typename T> class Shared {

    public:
        operator SharedPtr<T> () IPL_NOEXCEPT;
        operator bool() IPL_NOEXCEPT;

    protected:
        static void release(void *pointer, void *context) IPL_NOEXCEPT;

        osal::Mutex   m_mutex;
        unsigned      m_refcount;
        union {
            long long m_alignment_dummy;
            unsigned char m_object[sizeof(T)];
        };
    };

/*****************************************************************************/

    template <typename T> Shared<T>::operator SharedPtr<T> () IPL_NOEXCEPT
    {
        m_mutex.lock();
        if(m_refcount++==0) new(m_object) T;
        IPL_ASSERT(m_refcount!=0);  // overflow
        SharedPtr<T> p(reinterpret_cast<T *>(&m_object), release, this);
        m_mutex.unlock();
        return p;
    }

/*****************************************************************************/

    template <typename T> Shared<T>::operator bool ()  IPL_NOEXCEPT
    {
        util::MutexGuard lock(m_mutex);
        return m_refcount;
    }

/*****************************************************************************/

    template <typename T> void Shared<T>::release(void *pointer, void *context) IPL_NOEXCEPT
    {
        Shared<T> &self=*reinterpret_cast<Shared<T> *>(context);

        IPL_ASSERT(pointer==&self.m_object);

        self.m_mutex.lock();
        if(--self.m_refcount==0) {
            T * tmp = reinterpret_cast<T *>(&self.m_object);
            tmp->~T();
        }
        self.m_mutex.unlock();
    }

/*****************************************************************************/

}  // end of namespace transportserver

/*****************************************************************************/
#endif
