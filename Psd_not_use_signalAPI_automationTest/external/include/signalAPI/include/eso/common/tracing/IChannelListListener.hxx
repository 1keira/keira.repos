/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
        
#ifndef TRACING_ICHANNELLISTLISTENER_HXX
#define TRACING_ICHANNELLISTLISTENER_HXX

#include <ipl_config.h>

#include <common/iplcommon_dso.h>
#include <common/types/vector.hxx>

namespace tracing
{

class Channel;

/*!
 *    \brief
 *        A callback interface used to get notified about channel list changes
 */
class IPLCOMMON_EXPORT IChannelListListener
{
public:
    //! \brief Virtual destructor.
    virtual ~IChannelListListener() IPL_NOEXCEPT {}

    //! \brief Notification about the registration of a new channel.
    virtual void registerChannel(Channel *channel) IPL_NOEXCEPT = 0;

    //! \brief Notification about the unregistration of a channel.
    virtual void unregisterChannel(Channel *channel) IPL_NOEXCEPT = 0;
};

}

#endif /* TRACING_ICHANNELLISTLISTENER_HXX */

