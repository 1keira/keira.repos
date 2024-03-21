/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_IRUNNABLE_HXX
#define UTIL_IRUNNABLE_HXX

#include <ipl_config.h>

#include <util/util_dso.h>

namespace util
{

/**
 * \brief
 *    This interface is used by the util::PlainThread as entry point
 *    for new threads.

 *    Any class that wants to implement its own thread can derive from
 *    this interface to have a thread run in the threadLoop()
 *    interface function. The use of this interface provides some
 *    safety and comfort in contrast to plain C callback functions.
 *
 *    Also the interface makes it possible to handle a big amount of
 *    threads in an abstract way e.g. for functionality like
 *    util::ThreadPool and alike.
 *
 *    This interface has an additional template parameter that denotes
 *    the type of the parameter passed to the threadLoop() function.
 *    If you don't need to pass a parameter then you can simply choose
 *    void* as a parameter type and pass NULL as a value.
 **/
template <typename PAR>
struct IRunnableT
{
    /**
     * \brief
     *    virtual destructor to get derived class' destructor
     *    always called.
     **/
    virtual ~IRunnableT(){ };

    /**
     * \brief
     *    The entry function for the thread. Here any custom
     *    thread code can be executed.

     *    To use this interface you have to derive your class from
     *    it and use the interface pointer for registration at a
     *    util::PlainThread object.
     * \param[in]
     *     p The parameter that is passed to your thread. What this
     *     is depends on your template parameter choice.
     * \note
     *    No return value is currently provided here.  This
     *    functionality can usually be realised by using
     *    appropriate shared class member variables and alike.
     **/
    virtual void threadLoop(PAR p) = 0;
}; // end class

} // end namespace

#endif
