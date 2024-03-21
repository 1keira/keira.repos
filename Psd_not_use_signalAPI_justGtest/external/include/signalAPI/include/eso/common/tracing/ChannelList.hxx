/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_CHANNELLIST_HXX
#define TRACING_CHANNELLIST_HXX

#include <ipl_config.h>
#include <stdlib.h>
#include <common/iplcommon_dso.h>
#include <common/types/list.hxx>
#include <common/tracing/IChannelListListener.hxx>

namespace tracing
{

class Channel;

/*!
 *    \brief
 *        A class for helping static construction of channel entities.
 *    \note
 *        You don't need this. Use the macros provided in tracing.hxx
 *        for static declaration of channels or the interface in
 *        Client.hxx for dynamic entities.
 */
class IPLCOMMON_EXPORT ChannelList
{
public:
    //! type of channel list
    typedef ipl::list<Channel *> ChannelVector;

    //! \brief Non-virtual destructor.
    ~ChannelList() IPL_NOEXCEPT {/* nop */}

    //! \brief Returns the single instance of the channel list.
    static ChannelList & getInstance() IPL_NOEXCEPT;

    //! \brief Adds a new channel declaration to the channel list.
    void registerChannel(Channel *channel) IPL_NOEXCEPT;

    //! \brief Removes a channel declaration from the channel list
    void unregisterChannel(Channel *channel) IPL_NOEXCEPT;

    //! \brief Retrieve a list of all registered channels
    const ChannelVector &getChannels() IPL_NOEXCEPT;

    //! \brief Set a listener
    void setListener(IChannelListListener *listener) IPL_NOEXCEPT;

protected:
    //! \brief Default constructor.
    ChannelList() IPL_NOEXCEPT : m_listener(nullptr) {/* nop */}

    //! vector with all registered channels
    ChannelVector m_channels;

    //! the channel list listener
    IChannelListListener *m_listener;

private:
    //! \brief Copy Constructor, disabled.
    ChannelList(const ChannelList &) = delete;
    //! \brief Move Constructor, disabled.
    ChannelList(ChannelList &&) = delete;
    //! \brief Assignment operator, disabled.
    ChannelList & operator=(const ChannelList &) = delete;
    //! \brief Move assignment operator, disabled.
    ChannelList & operator=(ChannelList &&) = delete;
};

}

#endif /* TRACING_CHANNELLIST_HXX */

