/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IMESSAGEFORMATTER_HXX
#define TRACING_IMESSAGEFORMATTER_HXX

#include <tracing/tracing_dso.h>
#include <common/types/string.hxx>

namespace tracing
{

class IBackendListener;
class Message;

/*!
 *    \brief
 *        Interface class for a message formatter.
 *        A message formatter takes an instance of an Message class and
 *        creates a string containing a formatted representation of the
 *        supplied message. This string can then be used by a backend
 *        for printing it to a console or file.
 */
class TRACINGIMPL_EXPORT IMessageFormatter
{
public:
    //! \brief Virtual default destructor
    virtual ~IMessageFormatter() = default;

    /*!
     *    \brief
     *        Set initialization data for the formatter.
     *    \param
     *        bid The ID of the backend which is the owner of this formatter.
     *    \param
     *        listener A backend listener instance, which is the same as the
     *        owning backend's listener. The formatter may need this instance
     *        to be able to do ID lookups for channels, threads or other
     *        entities. \sa IBackendListener
     */
    virtual void setBackend(int16_t bid, IBackendListener * listener) = 0;

    /*!
     *    \brief
     *        Creates a formatted message.
     *    \param
     *        msg An instance of a Message that should be formatted.
     *    \return
     *        A formatted string.
     */
    virtual ipl::string formatMessage(const Message & msg) = 0;
};

}

#endif /* TRACING_IMESSAGEFORMATTER_HXX */

