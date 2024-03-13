/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_TRANSPORTSERRORS_HXX
#define UTIL_TRANSPORT_TRANSPORTSERRORS_HXX

#include <util/util_dso.h>
#include <common/error/Error.hxx>

namespace util
{

namespace transport
{

enum TransportErrors
{
    //! \brief
    //! Operation on a message buffer couldn't be performed as the
    //! message size was too big
    MESSAGE_TOO_BIG = 0,
    //! \brief
    //!  An operation on a message buffer was performed, but only
    //!  part of the message was ! processed as the message was too
    //!  large
    MESSAGE_TRUNCATED,
    //! \brief
    //!  A previously established connection to the peer was lost
    //! (un)expectedly
    CONNECTION_LOST,
    //! \brief
    //! Can be many different things that make it impossible to
    //! perform an operation on the ! transport. It ranges from
    //! logical errors to adressing problems and others.
    COMMUNICATION_ERROR,
    //! \brief
    //! The supposed peer of the transport is rejecting the
    //! connection or simply not available.
    NO_PEER,
    //! \brief
    //! The requested feature is not supported by the transport
    //! implementation
    NOT_SUPPORTED,
    //! unable to open the transport
    OPEN_ERROR,
    //! \brief
    //! Message header could not be validated (crc check fail)
    MESSAGE_CORRUPTED,
    //! \brief
    //! error during ETF init phase that may trigger a downgrade
    ETFH_DOWNGRADABLE_ERROR,
    //! \brief
    //! Message exceeds configured limit
    MESSAGE_EXCEEDS_LIMIT
};

const ipl::ErrorID TRANSPORT_ERROR_TABLE[] =
{
    { MESSAGE_TOO_BIG, "Message of size %d bytes is too big."
        " Maximum is %d bytes", 2 },
    { MESSAGE_TRUNCATED, "Only %d bytes from message of size %d"
        " bytes could be processed", 2 },
    { CONNECTION_LOST, "Connection to peer was lost (un)expectedly",
        0 },
    { COMMUNICATION_ERROR, "A communication error occured and the"
        " operation could not be performed", 0 },
    { NO_PEER, "No peer available or peer rejected connection", 0 },
    { NOT_SUPPORTED, "Operation is not supported by transport", 0 },
    { OPEN_ERROR, "failed to open %s", 1 },
    { MESSAGE_CORRUPTED, "Message is corrupted: %s", 1 },
    { ETFH_DOWNGRADABLE_ERROR, "Downgradable error in ETF init phase", 0 },
    { MESSAGE_EXCEEDS_LIMIT, "Packet size exceeds hard limit: %zu Bytes (limit: %zu)", 2 },
};

UTIL_EXPORT extern ipl::ErrorType Error;

} // end namespace transport
} // end namespace util

#endif
