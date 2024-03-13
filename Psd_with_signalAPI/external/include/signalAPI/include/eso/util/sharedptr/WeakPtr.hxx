/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SHAREDPTR_WEAKPTR_HXX
#define UTIL_SHAREDPTR_WEAKPTR_HXX

#include <memory>

namespace util {

    template < typename T > class SharedPtr;

    template <typename T>
    class WeakPtr {

    public:
        WeakPtr() IPL_NOEXCEPT: m_valid(false) {}

        template <typename U>
        WeakPtr(const util::SharedPtr<U> &p) IPL_NOEXCEPT:
            m_ptr(p.m_ptr), m_valid(p) {}

        template <typename U>
        WeakPtr(const util::WeakPtr<U> &p) IPL_NOEXCEPT:
            m_ptr(p.m_ptr), m_valid(p.m_valid) {}

        template <typename U>
        WeakPtr(const std::shared_ptr<U> &p) IPL_NOEXCEPT:
            m_ptr(p), m_valid(true) {}
        template <typename U>
        WeakPtr(const std::weak_ptr<U> &p) IPL_NOEXCEPT:
            m_ptr(p), m_valid(true) {}

        template <typename U>
        WeakPtr<T> &operator = (const WeakPtr<U> &other) IPL_NOEXCEPT {
            m_ptr = other.m_ptr;
            m_valid=other.m_valid;
            return *this;
        }

        template <typename U> operator std::weak_ptr<U> () const IPL_NOEXCEPT { return m_ptr; }
        template <typename U> operator std::shared_ptr<U> () const IPL_NOEXCEPT { return m_ptr.lock(); }

        bool dead() const IPL_NOEXCEPT { return m_ptr.expired(); }

        void release() IPL_NOEXCEPT {
            m_ptr.reset();
            m_valid=false;
        }
        bool valid() const IPL_NOEXCEPT { return m_valid; }

        SharedPtr<T> shared() const IPL_NOEXCEPT {
            return SharedPtr<T>(m_ptr.lock());
        }

        bool operator < (const WeakPtr<T> &other) const IPL_NOEXCEPT {
            /* invalid < valid */
            if(m_valid)
                if(other.m_valid)
                    return m_ptr.owner_before(other.m_ptr);
                else
                    return false;
            else
                return other.m_valid;
        }

    protected:

        template <typename O> friend class WeakPtr;
        template <typename O> friend class SharedPtr;

        std::weak_ptr<T> m_ptr;
        //! This is only needed to implement valid() in a way compatible
        //! to the old implementation.
        bool m_valid;

    };
}

#endif
