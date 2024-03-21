/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_SHAREDCHANNELMAP_HXX
#define TRACING_SHAREDCHANNELMAP_HXX

#include <ipl_config.h>
#include <common/iplcommon_dso.h>
#include <common/stdint.h>
#include <common/types/map.hxx>
#include <common/types/string.hxx>

namespace tracing
{

class Channel;

/*!
 *    \brief
 *        This singleton maps channel path names of shared channel ptrs to
 *        the allocated channel object
 */
class IPLCOMMON_EXPORT SharedChannelMap
{
public:
    //! \brief Non-virtual destructor.
    ~SharedChannelMap() IPL_NOEXCEPT;

    //! \brief Returns the single instance of the channel list.
    static SharedChannelMap & getInstance() IPL_NOEXCEPT;

    //! \brief Create a channel for the given path
    Channel * mapChannel(const ipl::string &path) IPL_NOEXCEPT;

    //! \brief Release a channel for the given path
    void unmapChannel(const ipl::string &path) IPL_NOEXCEPT;

private:
    //! value of channel map: usage count and channel object
    typedef ipl::pair<uint32_t,Channel *> Value;

    //! type of channel list
    typedef ipl::map<ipl::string,Value> Map;

    //! channel map
    Map m_map;

    //! \brief  Hidden constructor
    SharedChannelMap() IPL_NOEXCEPT;

    SharedChannelMap(const SharedChannelMap &) = delete;
    SharedChannelMap(SharedChannelMap &&) = delete;
    SharedChannelMap & operator=(const SharedChannelMap &) = delete;
    SharedChannelMap & operator=(SharedChannelMap &&) = delete;
};

}

#endif /* TRACING_SHAREDCHANNELMAP_HXX */

