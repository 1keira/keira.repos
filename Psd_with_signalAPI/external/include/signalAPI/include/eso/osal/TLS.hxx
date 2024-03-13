/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_TLS_HXX
#define OSAL_TLS_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>

#ifdef USE_THREADSAFE_IN_OSAL
    #include <threadsafe/Tls.hxx>
#else
    #ifdef IPL_OS_POSIX
        #include "posix/TLSDefs.hxx"
    #elif defined (IPL_OS_WINPC)
        #include "win32/TLSDefs.hxx"
    #else
        #error "error undefined IPL_OS_ variant"
    #endif
#endif

#include <osal/osal.hxx>
#include <osal/osal_dso.h>

namespace osal
{

/**
 * \brief
 *    Thread Local Storage (TLS) access

 *    TLS makes it possible to have thread-unique data values that are
 *    globally accessible by each thread. In some rare, special cases this
 *    can be used to make life easier or more efficient.
 *
 *    If you don't know what TLS is then you don't need it.
 *    \deprecated since 2020-01-31: use thread_local keyword instead.
**/
class OSAL_EXPORT TLS;
class
IPL_DEPRECATED_PRE("use thread_local keyword instead.")
TLS
{
public:
    /**
     * \brief
     *    This subclass is used to represent a TLS (thread local
     *    storage) key in the system
     * \note
     *    This object can be used with the createKey and company member
     *    functions within the TLS class. It can be obtained from the
     *    static createKey() member function. It is only a
     *    representation for an OS handle and serves no other purpose.
     *    Nothing can be actively done with this thing.
     **/
    class OSAL_EXPORT Key :
        // should never be copied
        public ipl::NonCopyable
    {
        // Surrounding class may directly access the handle
        friend class TLS;
#ifdef USE_THREADSAFE_IN_OSAL
    public:
        bool isInitialized() const { return true; }

    private:
        threadsafe::Tls tls;
#else
    public:
        /**
         * \brief
         *    Simply create a new Key ready for usage
         **/
        Key();

        /**
         * \brief
         *    Destroys the storage key (and deletes it on OS basis)
         **/
        ~Key();

        //! returns whether this key is already initialized or not
        bool isInitialized() const
        { return m_init; }
    private:
        //! OS handle for a thread local storage identifier
        TLSHandle m_handle;
        //! wheter the m_handle has been initialised on OS level
        bool m_init;
#endif
    };

    /**
     * \brief
     *    Create a new TLS key identifier that can be used for setting
     *    per-thread data
     * \warning
     *    The Key object can only be initialised _once_. An attempt to
     *    use the same object more than once with this function will
     *    result in an error being raised.
     * \param[in,out]
     *    p_new_key A reference to the Key object that should be
     *    initialised.
     * \return
     *     true on error, false on success
     * \errorindicator
     *     via return code
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - INVALID_USAGE if \c p_new_key was already used before.
     *
     *     osal::SystemError with IDs:
     *
     *     - SYSTEM_RESSOURCES_EXHAUSTED if ressources other than memory
     *     are lacking for creation of another TLS key.
     *     - OUT_OF_MEMORY if insufficient memory is available for
     *     creation of another TLS key.
     *     - UNKNOWN_ERROR on other errors
     * \deprecated since 2020-01-31: use thread_local keyword instead.
     **/
    IPL_DEPRECATED ( "use thread_local keyword instead.",
	static bool createKey(Key &p_new_key)
	)  /* IPL_DEPRECATED */
	;

    /**
     * \brief
     *     Retrieve the currently set value associated with the given TLS
     *     key
     * \param[in]
     *     p_key The Key previously initialised by createTLSKey.
     * \param[out] p_val
     *     The value that is currently associated with \c p_key and the
     *     calling thread is returned here. If no value has been set for
     *     this thread yet then NULL is returned.
     * \return
     *     true on error, false on success
     * \errorindicator
     *     via return code
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - INVALID_USAGE if \c p_new_key was wasn't initialized via
     *     createKey().
     *
     *     osal::SystemError with IDs:
     *
     *     - UNKNOWN_ERROR on other errors
     * \deprecated since 2020-01-31: use thread_local keyword instead.
     **/
    IPL_DEPRECATED ( "use thread_local keyword instead.",
    static bool getValue( const Key &p_key, void *&p_val )
	)  /* IPL_DEPRECATED */
	;

    /**
     * \brief
     *     Set the value to be associated with the given TLS key
     * \param
     *     p_key The Key previously initialised by createTLSKey.
     * \param
     *     p_value The value to set for the given key and the calling
     *     thread.
     * \return
     *     true on error, false on success
     * \errorindicator
     *     via return code
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - INVALID_USAGE if \c p_key was wasn't initialized via
     *     createKey().
     *
     *     osal::SystemError with IDs:
     *
     *     - OUT_OF_MEMORY if insufficient memory is available for
     *     setting the TLS value
     *     - INTEGRITY_ERROR on severe internal errors like invalid \c
     *     p_key
     *     - UNKNOWN_ERROR on other occasions
     * \deprecated since 2020-01-31: use thread_local keyword instead.
     **/
    IPL_DEPRECATED ( "use thread_local keyword instead.",
    static bool setValue( const Key &p_key, void* p_value )
	)  /* IPL_DEPRECATED */
	;

}
IPL_DEPRECATED_POST("use thread_local keyword instead.")
;  // end class

#ifdef USE_THREADSAFE_IN_OSAL
    inline bool TLS::createKey(Key &p_new_key)
    {
        // The Key is already fully operable
        return false;
    }

    inline bool TLS::getValue(const Key &p_key, void *&p_val)
    {
        p_val=p_key.tls.get();
        return false;
    }

    inline bool TLS::setValue(const Key &p_key, void *p_value)
    {
        const_cast<Key &>(p_key)/* working around interface */.tls.set(p_value);
        return false;
    }
#endif

} // end namespace

#endif
