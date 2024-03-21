/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_PLAINTHREAD_HXX
#define UTIL_PLAINTHREAD_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <iplbase/exceptions.hxx>
#include <common/Macros.hxx>
#include <osal/Thread.hxx>
#include <util/IRunnable.hxx>

namespace util
{

/**
 * \brief
 *     Specalization of osal::Thread that is able to call into c++
 *     interfaces of type IRunnable

 *     This thread is plain in that is doesn't add any extra semantics
 *     about thread communication and synchronization. It is merely an
 *     OSAL thread that adds the possibility of calling IRunnable
 *     interface for thread entry points.
 *
 *     The template parameter \a PAR is used to specialize the
 *     IRunnableT type to determine its parameter type. An instance of
 *     this type can be passed to the newly created thread as a
 *     parameter.
 **/
template<typename PAR>
class PlainThread :
    public osal::Thread
{
public: // types

    //! \brief
    //! A shorthand for the specialization of our IRunnableT
    //! template with the provided parameter type
    typedef IRunnableT<PAR> Runnable;

public: // member functions

    /**
     * \brief
     *    Creates a new thread with \a entry as the entry point
     *
     *    See osal::Thread(osal::ThreadFct, void*).
     *    <br>Instead of a C function one passes an
     *    IRunnableT<PAR> instance.
     * \note
     *    \a entry must not be NULL.
     **/
    PlainThread( IRunnableT<PAR> * const entry, PAR argument) IPL_NOEXCEPT
    : osal::Thread( &threadWrapper, reinterpret_cast<void*>(this))
    , m_entry(entry)
    , m_par(argument)
    {
        IPL_ASSERT( entry );
    }

    /**
     * \brief
     *    Creates a new thread with \a entry as the entry point
     *
     *    See osal::Thread(osal::ThreadFct, void*, const char* const).
     *    <br>Instead of a C function one passes an
     *    IRunnableT<PAR> instance.
     * \note
     *    \a entry must not be NULL.
     **/
    PlainThread( IRunnableT<PAR> * const entry, PAR argument
                ,const char* const name) IPL_NOEXCEPT
    : osal::Thread( &threadWrapper, reinterpret_cast<void*>(this)
                    ,name)
    , m_entry(entry)
    , m_par(argument)
    {
        IPL_ASSERT( entry );
    }

    /**
     * \brief
     *    Creates a new thread with \a entry as the entry point
     *
     *    See osal::Thread(osal::ThreadFct, void*, const char* const, const bool, const osal::Priority, const uint32_t, const bool).
     *    <br>Instead of a C function one passes an
     *    IRunnableT<PAR> instance.
     * \note
     *    \a entry must not be NULL.
     **/
    PlainThread( IRunnableT<PAR> * const entry, PAR argument
                ,const char* const name
                ,const bool set_priority
                ,const osal::Thread::Priority priority = 0
                ,const uint32_t stacksize = 0
                ,const bool detached = false) IPL_NOEXCEPT
    : osal::Thread( &threadWrapper, reinterpret_cast<void*>(this)
                    ,name, set_priority, priority, stacksize, detached)
    , m_entry(entry)
    , m_par(argument)
    {
        IPL_ASSERT( entry );
    }

    /**
     * \brief
     *    Creates a new thread with \a entry as the entry point
     *
     *    See osal::Thread(osal::ThreadFct, void*, const char* const, const osal::sched::Policy, const osal::sched::Param, const bool).
     *    <br>Instead of a C function one passes an
     *    IRunnableT<PAR> instance.
     * \note
     *    \p entry must not be NULL.
     **/
    PlainThread( IRunnableT<PAR> * const entry, PAR argument
                ,const char* const name
                ,const osal::sched::Attr& sched_attr
                ,const bool detached = false) IPL_NOEXCEPT
    : osal::Thread( &threadWrapper, reinterpret_cast<void*>(this)
                    ,name, sched_attr, detached)
    , m_entry(entry)
    , m_par(argument)
    {
        IPL_ASSERT( entry );
    }

protected: // member functions

    /**
     * \brief
     *     C entry point for base class osal::Thread
     *
     *     This wrapper performs the necessary actions to call the
     *     C++ entry point specified at construction time from the
     *     new thread.
     **/
    static void threadWrapper(void *arg) IPL_NOEXCEPT
    {
        IPL_ASSERT( arg );

        // reference to our controlling object
        PlainThread<PAR> &self = *( reinterpret_cast<util::PlainThread<PAR>*>(arg) );

        IPLBASE_ABORT_ON_EXCEPTION(
            // do the run loop
            self.m_entry->threadLoop(self.m_par);
        )
    }
protected: // data
    //! The C++ entry point specified at ctor. time
    Runnable* const m_entry;
    //! \brief
    //! The parameter to be passed to m_entry as specified at
    //! construction time
    PAR m_par;
};

} // end namespace

#endif
