/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_SCOPEGUARD_HXX
#define IPL_SCOPEGUARD_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/Macros.hxx>

namespace IPL_NAMESPACE
{

/**
 * \brief
 *    Scope guard implementation that calls a specified function in
 *    its destructor

 *    The Scope guard is used to perform a rollback in case multiple
 *    operations that can fail need to be performed in an
 *    all-or-nothing manner.

 *    Example:
 *    \code
 *    typedef void(File::*filefunc(void);
 *    typedef void(Buffer::*bufferfunc(void);
 *    typedef void(Codec::*codecfunc(void);
 *
 *    // [...]
 *    // open may fail
 *    if( mediaFile.open() )
 *        return;
 *
 *    ScopeGuard<File, filefunc> fileGuard(mediaFile, &File::close);
 *
 *    // allocate may fail
 *    if( mediaBuffer.allocate() )
 *        return;
 *    ScopeGuard<Buffer, bufferfunc> bufferGuard(mediaBuffer,
 *        &Buffer::free);
 *
 *    // get may fail
 *    if( mediaCodec.get() )
 *        return;
 *    ScopeGuard<Codec, codecfunc> codecGuard(mediaCodec,
 *        &Codec::release);
 *
 *    // if everything is OK we dismiss the ScopeGuards...
 *    fileGuard.dismiss();
 *    bufferGuard.dismiss();
 *    codecGuard.dismiss();
 *
 *    // otherwise, ScopeGuards destructors are doing the clean up
 *    // work.
 *    \endcode
 **/
/*
 * Default functor for converting the release function's return value to bool.
 * Does nothing.
 */
struct NoopResultConv {
    bool operator() (bool arg) IPL_NOEXCEPT {
        return arg;
    }
};

template<class T, class FUNC = bool (T::*)(void), class RESULTCONV = NoopResultConv >
class ScopeGuard
{
    T& m_obj; /**< the external mutex (or other locking object) */
    FUNC m_release_func; /**< the actual release function for the
        external mutex */

    /**
     * \brief
     *    private CTOR, only CTOR with params usable
    **/
    ScopeGuard(const ScopeGuard&) IPL_NOEXCEPT;
    /**
     * \brief
     *    private copy operator to protect object form beeing
     *    copied
    **/
    ScopeGuard& operator=(const ScopeGuard&) IPL_NOEXCEPT;

    bool m_dismissed;
public:
    /**
       \brief
        CTOR to create the guard with corresponding object and
        release method.

        See usage for more information.
       \param obj Object on which the release method will be called.
       \param release_func Release method to call in destructor if
        dismiss is not called on the ScopeGuard.
       \errors
        implementation defined
    **/
    ScopeGuard( T& obj, FUNC release_func, const bool valid = false ) IPL_NOEXCEPT :
        m_obj(obj),
        m_release_func(release_func),
        m_dismissed(false),
        m_valid(valid)
    {}

    /**
     * \brief
     *     Releases the associated ressource in case it has not
     *     been explicitly dismiss()ed already.
     * \errors
     *     In case of release error assertion or abortion is
     *     caused. Error cannot be sensibly dispatched to the
     *     client.
    **/
    virtual ~ScopeGuard() IPL_NOEXCEPT
    {
        if (!m_dismissed && m_valid)
        {
            RESULTCONV resultconv;
            const bool release_failed = resultconv(
                (m_obj.*m_release_func)());
            IPL_ASSERT( ! release_failed );
        }
    }

    void dismiss() IPL_NOEXCEPT
    { m_dismissed = true; }

    /**
     * \brief
     *    Default dereference operator
    **/
    T& operator*() IPL_NOEXCEPT
    { return *m_obj; }

    /**
     * \brief
     *    Access operator for internal object.
    **/
    T* operator->() IPL_NOEXCEPT
    { return &m_obj; }

    operator bool() const IPL_NOEXCEPT
    {
        return m_valid;
    }
protected:
    bool m_valid;
};

/**
 * \brief
 *    Object encapsulating a scope guard for ease of usage
 *
 *    see article: multi threaded programmers best friend
 *    (drdobsjournal) the scoped object guard is a wrapper around an
 *    object, to ensure that the access to the object is safe in a
 *    thread/process-wide context
 *
 *    Example:
 *    \code
 *    struct Mutex
 *    {
 *        void lock(){ //locking the mutex }
 *        void unlock(void){ //assume we do some real cleanup }
 *    };
 *
 *    osal::Mutex m;
 *    ObjectToGuard guardedInstance;
 *    {
 *        ScopedObjectGuard<ObjectToGuard, Mutex>
 *            theGuard( guardedInstance, m );
 *        theGuard->doSomeRealwork();
 *    }//impicit release of the resource
 *    \endcode
**/
template<typename TGuardedObject, typename TMutex>
class ScopedObjectGuard
{
private:
    //! The guarded object member
    TGuardedObject* m_pObj;
    //! osal::Mutex to lock object
    ScopeGuard<TMutex> m_ResourceGuard;
    //! private CTOR to prevent implicit copy
    ScopedObjectGuard(const ScopedObjectGuard&);
    //! private operator= to prevent explicit copy
    ScopedObjectGuard& operator=(const ScopedObjectGuard&);
public:
    /**
     * \brief
     *     CTOR to create the guard with corresponding protected
     *     object and mutex

     *    See usage for more information, remember that the mutex
     *    must be created separately.
    **/
    ScopedObjectGuard(volatile TGuardedObject& obj, TMutex& mx) IPL_NOEXCEPT
        : m_pObj(const_cast<TGuardedObject*>(&obj))
        , m_ResourceGuard(mx, &TMutex::unlock )
    {
        mx.lock();
    }

    /**
     * \brief
     *    Default dereference operator
    **/
    TGuardedObject& operator*() IPL_NOEXCEPT { return *m_pObj; }

    /**
     * \brief
     *     Access operator for member access (lock and guarded
     *     object)
    **/
    TGuardedObject* operator->() IPL_NOEXCEPT { return m_pObj; }
};

} // end namespace

#endif // IPL_SCOPEGUARD_HXX
