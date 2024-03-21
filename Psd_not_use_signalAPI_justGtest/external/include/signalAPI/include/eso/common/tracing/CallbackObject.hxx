/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_CALLBACKOBJECT_HXX
#define TRACING_CALLBACKOBJECT_HXX

#include <ipl_config.h>
#include <common/stdint.h>
#include <stddef.h>

namespace tracing
{

/*!
 *    \brief
 *        An interface class to implement callbacks.

 *        Please have a look at the user-guide for documenation
 *        regarding implementing trace callbacks.
 */
class CallbackObject
{
public:
    //! \brief Virtual destructor.
    virtual ~CallbackObject() IPL_NOEXCEPT {/* nop */};

    /*!
     *    \brief
     *        Actual implementation of the callback.
     *    \param
     *        cbid The callback's entity ID as returned from the trace
     *        frontend upon registration.
     *    \param
     *        data The data received by the requestee.
     *    \param
     *        len Size of data in number of bytes.
     */
    virtual void execute(int32_t cbid, void * const data, size_t len) IPL_NOEXCEPT = 0;

    //! \brief Shall return true if the callback object should be deleted after
    //!        unregistering the callback, false if you want to delete it yourself.
    virtual bool deleteAtUnregister() const IPL_NOEXCEPT = 0;
};

} // end of namespace tracing

#endif /* TRACING_CALLBACKOBJECT_HXX */

