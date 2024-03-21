/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef COMMON_SHARED_HXX
#define COMMON_SHARED_HXX
/*****************************************************************************/

#include <ipl_config.h>
#include <common/iplcommon_dso.h>
#include <iplbase/NonCopyable.hxx>
#include <threadsafe/AtomicCounter.hxx>
#include <threadsafe/Mutex.hxx>
#include <common/ipl_namespace.hxx>
#include <common/Macros.hxx>
#include <common/align.hxx>

#include <new>  // working around an IntegrityOS bug

/*****************************************************************************/

namespace IPL_NAMESPACE {

/*****************************************************************************/

    template <typename T> class Shared;

/*****************************************************************************/

    /*!
        usage of IPLCOMMON_EXPORT is not needed because
        of only inline code defined
    */
    class SharedBase: public iplbase::NonCopyable {

        class PtrBase;

    public:

        template <typename T> class Ptr;

        virtual ~SharedBase() IPL_NOEXCEPT {}
        //! \internal
        virtual void new_object() IPL_NOEXCEPT=0;
        //! \internal
        virtual void delete_object() IPL_NOEXCEPT=0;

    protected:

        threadsafe::AtomicCounter refcount;
        threadsafe::Mutex         mutex;

        friend class PtrBase;  // may access fields
    };

/*****************************************************************************/

    class SharedBase::PtrBase {

    protected:
        PtrBase(SharedBase *shared, void *pointer) IPL_NOEXCEPT:
            shared(shared), pointer(pointer) {
            if(shared) {
                threadsafe::Mutex::Guard lock(shared->mutex);
                if(shared->refcount++==0)
                    shared->new_object();
                IPL_ASSERT(shared->refcount!=0);
            }
        }

    public:
        ~PtrBase() IPL_NOEXCEPT {
            if(shared) {
                threadsafe::Mutex::Guard lock(shared->mutex);
                IPL_ASSERT(shared->refcount!=0);
                if(--shared->refcount==0)
                    shared->delete_object();
            }
        }

        void reset() IPL_NOEXCEPT {
            if(shared) {
                threadsafe::Mutex::Guard lock(shared->mutex);
                if(--shared->refcount==0)
                    shared->delete_object();
            }
            shared=NULL;
            pointer=NULL;
        }

        explicit operator bool () const IPL_NOEXCEPT { return pointer; }

    protected:
        //! \brief Simplifies friendology
        threadsafe::AtomicCounter &shared_refcount() const IPL_NOEXCEPT { return shared->refcount; }
        //! \brief Simplifies friendology
        threadsafe::Mutex &shared_mutex() const IPL_NOEXCEPT { return shared->mutex; }

        SharedBase *shared;
        void       *pointer;
    };

/*****************************************************************************/

    /*!
        \brief Some minimal std::shared_ptr lookalike

        This can either point to a \e managed object,
        i.e. something that gets cleaned up when the last reference goes away,
        or an \e unmanaged object, i.e. something you have to delete yourself
        eventually.
        This allows for Ptr using code that works with both.

        \b Note: Use Shared<T>::Ptr instead where possible!
        SharedBase::Ptr<T> exists only to allow shared pointers to
        incomplete types.
    */
    template <typename T> class SharedBase::Ptr: public PtrBase {

    public:

        Ptr() IPL_NOEXCEPT: PtrBase(NULL, NULL) {}

        //! \brief Magic happens here
        //!
        //! When you assign a Shared<T> to a Ptr, the shared object
        //! is magically instantiated if needed.
        template <typename U> Ptr(Shared<U> &shared) IPL_NOEXCEPT:
            PtrBase(&shared,
                    static_cast<T*>(cast_without_warning<U*>(&shared.object))) {}

        // No, this is not redundant. A non-const reference doesn't match
        // above template.
        template <typename U> Ptr(typename Shared<U>::Ptr &other) IPL_NOEXCEPT:
            PtrBase(other.shared,
                    static_cast<T*>(reinterpret_cast<U*>(other.pointer))) {}
        // Aaargh!
        // No, this is not redundant either. Above templates come in
        // function lookup AFTER the implicit copy constructor,
        // so we need to define one explicitly. Grmbl.
        Ptr(const Ptr &other) IPL_NOEXCEPT:
            PtrBase(other.shared, other.pointer) {}

        //! \brief Have the Ptr point to some \e unmanaged object,
        //! i.e. ownership stays with the caller
        template <typename U> Ptr(U *other) IPL_NOEXCEPT:
            PtrBase(NULL, static_cast<T*>(other)) {}

        T &operator *  () const IPL_NOEXCEPT { return *reinterpret_cast<T *>(pointer); }
        T *operator -> () const IPL_NOEXCEPT { return  reinterpret_cast<T *>(pointer); }
        operator T *   () const IPL_NOEXCEPT { return  reinterpret_cast<T *>(pointer); }

        template <typename U> Ptr &
        operator = (const typename Shared<U>::Ptr &other) IPL_NOEXCEPT {
            if(shared && shared==other.shared)
                return *this;

            if(other.shared) {
                threadsafe::Mutex::Guard lock(other.shared_mutex());
                other.shared_refcount()++;
            }
            if(shared) {
                threadsafe::Mutex::Guard lock(shared_mutex());
                if(--shared_refcount()==0) shared->delete_object();
            }
            shared=other.shared;
            // the static cast may change the address a bit
            pointer=other.pointer?
                static_cast<T*>(reinterpret_cast<U*>(other.pointer)) :
                NULL;
            return *this;
        }
        template <typename U> Ptr &
        operator = (typename Shared<U>::Ptr &other) IPL_NOEXCEPT {
            return *this=(const typename Shared<U>::Ptr &)other;
        }

        Ptr &operator = (const Ptr &other) IPL_NOEXCEPT {
            if(shared && shared==other.shared)
                return *this;

            if(other.shared) {
                threadsafe::Mutex::Guard lock(other.shared_mutex());
                other.shared_refcount()++;
            }
            if(shared) {
                threadsafe::Mutex::Guard lock(shared_mutex());
                if(--shared_refcount()==0) shared->delete_object();
            }
            shared=other.shared;
            // the static cast may change the address a bit
            pointer=other.pointer;
            return *this;
        }
        Ptr &operator = (Ptr &other) IPL_NOEXCEPT { return *this=(const Ptr &)other; }

        //! \brief Have the Ptr point to some \e unmanaged object,
        //! i.e. ownership stays with the caller
        template <typename U> Ptr &
        operator = (U *other) IPL_NOEXCEPT {
            if(shared) {
                threadsafe::Mutex::Guard lock(shared_mutex());
                if(--shared_refcount()==0) shared->delete_object();
            }
            shared=NULL;
            // the static cast may change the address a bit
            pointer=static_cast<T*>(other);
            return *this;
        }

        //! \brief Magic happens here
        //!
        //! When you assign a Shared<T> to a Ptr, the shared object
        //! is magically instantiated if needed.
        Ptr &operator = (Shared<T> &shared) IPL_NOEXCEPT {
            *this=Ptr(shared);
            return *this;
        }
    };

/*****************************************************************************/

    /*!
        \brief %Shared object with automatic lifecycle management

        For any type T with a default constructor,
        a Shared\<T> behaves like a shared pointer to an instance of T that gets
        initialized, finalized and reinitialized (if necessary) on demand,
        i.e. first access initializes (lazily),
        last pointer vanishing destroys,
        new access initializes again.
        The underlying instance is allocated within the Shared\<T> object,
        saving heap overhead.

        \note Due to MSVC failing to implement the C++ standard properly,
        \e every class you put between the angle brackets must have a
        standard constructor.
        If yours hasn't, add a dummy one in an <code>\#ifdef IPL_OS_WIN32</code>
        block.

        \see util::Shared which does the same, supports util::SharedPtr and
        is unavailable on osal and below.
    */
    template <typename T> class Shared: public SharedBase {

    public:

        typedef Ptr<T> Ptr;

        virtual void new_object() IPL_NOEXCEPT;
        virtual void delete_object() IPL_NOEXCEPT;

        operator Ptr () IPL_NOEXCEPT { return Ptr(*this); }

        //! \brief \b BEWARE that this drops its reference \b immediately!
        Ptr operator -> () IPL_NOEXCEPT { return *this; }

#if defined _MSC_VER && _MSC_VER==1900
        // Visual Studio 2015 doesn't understand below
        // friend declaration, hence we cannot use protected here
#else
    protected:
#endif

#ifdef HAVE_ALIGNAS
        alignas(T) unsigned char object[sizeof(T)];
#else
        union {
            long long     alignment_dummy;  // hope for the best
            unsigned char object[sizeof(T)];
        };
#endif
#if defined _MSC_VER && _MSC_VER==1900
        // Visual Studio 2015 doesn't understand this
        // friend declaration, hence we do not use protected above
#else
        template <typename U> friend class SharedBase::Ptr;
#endif
    };

/*****************************************************************************/

    template <typename T> void Shared<T>::new_object() IPL_NOEXCEPT
    {
        new(object) T;
    }

/*****************************************************************************/

    template <typename T> void Shared<T>::delete_object() IPL_NOEXCEPT
    {
        T *p=cast_without_warning<T *>(&object);  // avoid strict aliasing warning
        p->~T();
    }

/*****************************************************************************/

}  // end of namespace IPL_NAMESPACE

/*****************************************************************************/
#endif
