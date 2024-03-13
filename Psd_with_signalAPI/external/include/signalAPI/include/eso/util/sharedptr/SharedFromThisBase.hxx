/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SHAREDPTR_SHAREDFROMTHISBASE_HXX
#define UTIL_SHAREDPTR_SHAREDFROMTHISBASE_HXX

#include <iplbase/exceptions.hxx>

#include <memory>

namespace util {

    template <class T> class SharedPtr;

    template <typename T>
    class SharedFromThisBase {

    public:

        /**
        * \brief
        *     Returns a SharedPtr object pointing to the current
        *     object
        *
        * \b WARNING: If there is no SharedPtr pointing to the object (yet) and
        * the class derives from SharedFromThisBase in some non-downcastable way,
        * the resulting pointer will point to the wrong address.
        **/
        SharedPtr<T> sharedFromThis() IPL_NOEXCEPT {
            std::shared_ptr<T> p{m_weak_this.lock()};
            if(!p) {
                p.reset((T *)this);
                m_weak_this=p;
            }
            return p;
        }

        /**
        * \brief
        *     Returns a SharedPtr object pointing to the const version
        *     of the current object
        *
        * \b WARNING: If there is no SharedPtr pointing to the object (yet) and
        * the class derives from SharedFromThisBase in some non-downcastable way,
        * the resulting pointer will point to the wrong address.
        **/
        SharedPtr<const T> sharedFromThis() const IPL_NOEXCEPT {
            std::shared_ptr<T> p{m_weak_this.lock()};
            if(!p) {
                p.reset((T *)this);
            }
            return std::const_pointer_cast<const T>(p);
        }

    private:

        template <typename SHAREDPTR_TYPE>
        friend class ::util::SharedPtr;

        //! \brief The weak reference to ourselves
        //!
        //! Note that this gets initialized not in a constructor (to avoid
        //! shared object overhead while not needed) and as that might pose
        //! casting problems. Instead the first shared pointer owning this
        //! initializes, introducing a race condition.
        mutable std::weak_ptr<T> m_weak_this;
    };

}

#endif
