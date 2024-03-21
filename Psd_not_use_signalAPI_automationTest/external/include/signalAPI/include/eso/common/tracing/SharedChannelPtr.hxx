/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_SHAREDCHANNELPTR_HXX
#define TRACING_SHAREDCHANNELPTR_HXX

#include <ipl_config.h>
#include <common/iplcommon_dso.h>
#include <common/tracing/Levels.hxx>

namespace tracing
{

class Channel;

/*!
 *    \brief
 *        Trace channels are the high-level representation of channel entities.

 *        When creating trace messages one usually wants to associate a context
 *        with them, e.g. some name where they originate from. Furthermore, it
 *        should be possible to filter messages by some kind of priority.
 *        The Channel class provides this feature. It is used to declare trace
 *        entities of type 'channel' within the trace core, it must be given a
 *        unique name and it always holds a filter level. When creating a new
 *        trace message you always reference a specific channel object thus
 *        providing the context where your message comes from.
 *    \note
 *        Maybe you want to use the macros provided in tracing.hxx. This would
 *        allow compiling away all references to a channel and their associated
 *        trace messages for production builds.
 */
class IPLCOMMON_EXPORT SharedChannelPtr
{
public:
    /*!
     *    \brief
     *        Creates a new shared channel ptr object.

     *        This will lookup the channel path and create the channel if
     *        its not already existing.
     *    \param
     *        path The unique name of the channel.
     */
    explicit SharedChannelPtr(const ipl::string & path) IPL_NOEXCEPT;

    /*!
     * Shutdown channel pointer
     */
    ~SharedChannelPtr() IPL_NOEXCEPT;

    /*!
     * Get the referenced channel
     */
    Channel * getChannel() IPL_NOEXCEPT { return m_channel; }

protected:
    //! the referenced channel
    Channel * m_channel;
    //! store path name
    ipl::string m_path;
};

}

#endif /* TRACING_SHAREDCHANNELPTR_HXX */

