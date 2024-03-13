/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SHAREDPTR_SHAREDPTR_HXX
#define UTIL_SHAREDPTR_SHAREDPTR_HXX

#include <iplbase/exceptions.hxx>
#include <util/sharedptr/SharedFromThisBase.hxx>

#include <memory>
#include <type_traits>
#include <cstddef>

namespace util {

    template < typename T > class WeakPtr;

    template <class T>
    class SharedPtr {

    public:

        struct IsArrayTag {};
        typedef IsArrayTag isArray;

        // custom deleter
        typedef void (*DelFunc)(void*, void*);

        SharedPtr() IPL_NOEXCEPT {}
        SharedPtr(const SharedPtr<T> &other) IPL_NOEXCEPT=default;

        template <typename U>
        SharedPtr(const std::shared_ptr<U> &p) IPL_NOEXCEPT:
            m_ptr(p) { setTargetsWeakThis(p.get()); }
        SharedPtr(T *p) IPL_NOEXCEPT: m_ptr(p) { setTargetsWeakThis(p); }

        explicit SharedPtr(T *p, const IsArrayTag &) IPL_NOEXCEPT:
            m_ptr(p, [](T *p) { IPLBASE_ABORT_ON_EXCEPTION( delete [] p; ) }) {}

        // with custom deleter
        // DelFunc is called with: void *ptr, void *ctx
        SharedPtr(T *p, DelFunc df, void *ctx=nullptr) IPL_NOEXCEPT:
            m_ptr(p, [ctx, df](T *p) { IPLBASE_ABORT_ON_EXCEPTION( df(p, ctx); ) }) {
            setTargetsWeakThis(p);
        }

        template <typename U> operator std::shared_ptr<U> () const IPL_NOEXCEPT { return m_ptr; }
        template <typename U> operator std::weak_ptr<U> () const IPL_NOEXCEPT { return m_ptr; }

        template <typename U> SharedPtr(U *p) IPL_NOEXCEPT: m_ptr(p) { setTargetsWeakThis(p); }

        template <typename U> SharedPtr(const SharedPtr<U> &other) IPL_NOEXCEPT:
            m_ptr(std::static_pointer_cast<T>(other.m_ptr)) {}

        template <typename U>
        SharedPtr(const WeakPtr<U> &other) IPL_NOEXCEPT:
            m_ptr(std::static_pointer_cast<T>(other.m_ptr.lock())) {}

        template <typename U>
        SharedPtr(const std::weak_ptr<U> &other) IPL_NOEXCEPT:
            m_ptr(std::static_pointer_cast<T>(other.lock())) {}

        SharedPtr<T> &operator = (const SharedPtr<T> &other) IPL_NOEXCEPT {
            m_ptr = other.m_ptr;
            return *this;
        }

        SharedPtr<T> &operator = (T *p) IPL_NOEXCEPT {
            if(p)
                m_ptr.reset(p);
            else
                m_ptr.reset();
            setTargetsWeakThis(p);
            return *this;
        }

        bool valid() const IPL_NOEXCEPT     { return m_ptr.operator bool(); }
        bool unique() const IPL_NOEXCEPT    { return m_ptr.use_count() == 1; }
        T* retrieve() const IPL_NOEXCEPT    { return m_ptr.get(); }
        T& dereference() const IPL_NOEXCEPT { return *m_ptr.get(); }
        void reset() IPL_NOEXCEPT           { m_ptr.reset(); }

        uint_fast32_t getRefCount() const IPL_NOEXCEPT {
            return (uint_fast32_t)m_ptr.use_count();
        }

        void setSharedPointer(T *other) IPL_NOEXCEPT { operator = (other); }

        T &operator * () const IPL_NOEXCEPT          { return m_ptr.operator * (); }
        T *operator -> () const IPL_NOEXCEPT         { return m_ptr.operator -> (); }
        explicit operator bool () const IPL_NOEXCEPT { return m_ptr.operator bool (); }

        template < class U, class V >
        friend bool operator == (const SharedPtr<U> &, const SharedPtr<V> &) IPL_NOEXCEPT;
        template < class U, class V >
        friend bool operator < (const SharedPtr<U> &, const SharedPtr<V> &) IPL_NOEXCEPT;

    protected:
        template <typename Target>
        void setTargetsWeakThis(SharedFromThisBase<Target> *target) {
            if(target) {
                target->m_weak_this=std::static_pointer_cast<Target>(m_ptr);
            }
        }

        void setTargetsWeakThis(... /* accepts any type */) {
            /* nothing to do for non-SharedFromThisBase */
        }

        template <typename U>
        int cmp(const SharedPtr<U> &other) const IPL_NOEXCEPT {
            if(m_ptr==other.m_ptr)
                return 0;
            if(m_ptr.owner_before(other.m_ptr))
                return -1;
            return 1;
        }

        template <typename U> friend class SharedPtr;
        template <typename U> friend class WeakPtr;
        std::shared_ptr<T> m_ptr;

    };

    // this makes the operators unoveridable (don’t know why we need this,
    // but it’s the same as in the "impl" implementation)
    template < class T, class U >
    inline bool operator == (const SharedPtr<T> &lhs, const SharedPtr<U> &rhs) IPL_NOEXCEPT {
        return lhs.m_ptr==rhs.m_ptr;
    }

    template < class T, class U >
    inline bool operator != (const SharedPtr<T> &lhs, const SharedPtr<U> &rhs) IPL_NOEXCEPT {
        return !(lhs==rhs);
    }

    template < class T, class U >
    inline bool operator < (const SharedPtr<T> &lhs, const SharedPtr<U> &rhs) IPL_NOEXCEPT {
        return lhs.m_ptr.owner_before(rhs.m_ptr);
    }

    template < class T, class U >
    inline bool operator <= (const SharedPtr<T> &lhs, const SharedPtr<U> &rhs) IPL_NOEXCEPT {
        return lhs<rhs || lhs==rhs;
    }

    template < class T, class U >
    inline bool operator > (const SharedPtr<T> &lhs, const SharedPtr<U> &rhs) IPL_NOEXCEPT {
        return !(lhs<=rhs);
    }

    template < class T, class U >
    inline bool operator >= (const SharedPtr<T> &lhs, const SharedPtr<U> &rhs) IPL_NOEXCEPT {
        return !(lhs<rhs);
    }

    template < class T >
    inline bool operator == (const SharedPtr<T> &lhs, std::nullptr_t) IPL_NOEXCEPT {
        return lhs==SharedPtr<T>();
    }

    template < class T >
    inline bool operator == (std::nullptr_t, const SharedPtr<T> &rhs) IPL_NOEXCEPT {
        return SharedPtr<T>()==rhs;
    }

    template < class T >
    inline bool operator != (const SharedPtr<T> &lhs, std::nullptr_t) IPL_NOEXCEPT {
        return lhs!=SharedPtr<T>();
    }

    template < class T >
    inline bool operator != (std::nullptr_t, const SharedPtr<T> &rhs) IPL_NOEXCEPT {
        return SharedPtr<T>()!=rhs;
    }

    template < class T >
    inline bool operator < (const SharedPtr<T> &lhs, std::nullptr_t) IPL_NOEXCEPT {
        return lhs<SharedPtr<T>();
    }

    template < class T >
    inline bool operator < (std::nullptr_t, const SharedPtr<T> &rhs) IPL_NOEXCEPT {
        return SharedPtr<T>()<rhs;
    }

    template < class T >
    inline bool operator <= (const SharedPtr<T> &lhs, std::nullptr_t) IPL_NOEXCEPT {
        return lhs<=SharedPtr<T>();
    }

    template < class T >
    inline bool operator <= (std::nullptr_t, const SharedPtr<T> &rhs) IPL_NOEXCEPT {
        return SharedPtr<T>()<=rhs;
    }

    template < class T >
    inline bool operator > (const SharedPtr<T> &lhs, std::nullptr_t) IPL_NOEXCEPT {
        return lhs>SharedPtr<T>();
    }

    template < class T >
    inline bool operator > (std::nullptr_t, const SharedPtr<T> &rhs) IPL_NOEXCEPT {
        return SharedPtr<T>()>rhs;
    }

    template < class T >
    inline bool operator >= (const SharedPtr<T> &lhs, std::nullptr_t) IPL_NOEXCEPT {
        return lhs>=SharedPtr<T>();
    }

    template < class T >
    inline bool operator >= (std::nullptr_t, const SharedPtr<T> &rhs) IPL_NOEXCEPT {
        return SharedPtr<T>()>=rhs;
    }

}
#endif
