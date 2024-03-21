/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_LAZYINIT_HXX
#define OSAL_LAZYINIT_HXX

#include <common/Macros.hxx>

#include <osal/Mutex.hxx>
#include <osal/AtomicCounter.hxx>

namespace osal
{

/**
 * \brief
 *     Thread-safe, lazy initialization mechanism

 *     If you need to perform some initialization sequence (typically
 *     to allocate and prepare ressources) but don't want to use
 *     statically initialized objects or explicit initialization calls
 *     then you can use the LazyInit mechanism.
 *
 *     To use it you need to inherit from this class, implement the
 *     doInit() function to perform the initialization steps and call
 *     checkInit() whenever you need to make sure that the object is
 *     properly initialized.
 *
 *     The checkInit() function is thread-safe and ensures that
 *     doInit() will only we called once for initialization. Also, once
 *     the object is initialized the costs of checking for
 *     initialization are reduced to reading an atomic counter value.
 **/
template <class INIT_PAR>
class LazyInitBase
{
    //! \brief
    //! the initialization counter - if zero then initialization is
    //! attempted, otherwise nothing is done
    osal::AtomicCounter is_init;
    //! a lock to perform the actually initialization in a safe way
    osal::Mutex lock;
protected: // data
    INIT_PAR *m_par;
protected: // functions

    /**
     * \brief
     *     Implementation defined function that performs actual
     *     initialization

     *     Is called from checkInit() in case initialization is
     *     required. Is called at most once.
     * \return
     *     \c true on error, \c false on success
     **/
    virtual bool doInit() = 0;
public: // functions
    //! nothing special
    LazyInitBase() :
        is_init(0),
        m_par()
    { }

    virtual ~LazyInitBase() {}

    /**
     * \brief
     *     Returns validity of the lazy initializatino related
     *     members
     **/
    bool isValid()
    {
        return lock.isValid();
    }

    /**
     * \brief
     *     Checks if initialization is needed

     *     If initialization already occured then nothing is done
     *     and \c false is returned.
     *
     *     If initialization is still required then doInit() is
     *     called. The return value will then be the return value
     *     of doInit().
     *
     *     After return, if no errors occured in doInit(), the
     *     object will be initialized.
     * \param[in] p
     *     An optional pointer to a parameter that is to be used
     *     during initialization.
     **/
    bool checkInit(INIT_PAR *p = NULL)
    {
        if( is_init.getCurrentCount() )
        {
            // already done
            return false;
        }

        IPL_MUTEX_LOCK_OR_ABORT( lock );

        bool ret = false;

        // if this is not the case when a race occured and
        // somebody else did initialization already
        if( ! is_init.getCurrentCount() )
        {
            m_par = p;
            ret = doInit();
            is_init++;
        }

        IPL_MUTEX_UNLOCK_OR_ABORT( lock );

        return ret;
    }

    //! \brief
    //! reset the counter, assuming the object is deinitialized
    //! again
    void reset()
    {
        is_init = 0;
    }
};

typedef LazyInitBase<void*> LazyInit;

}; // end ns osal

#endif
