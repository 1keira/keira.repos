/*
   Copyright 2023 e.solutions GmbH
   All rights reserved
*/

#ifndef TRACING_IRCBACKEND_ISMSYSTEMEVENTSPLUGIN_HXX
#define TRACING_IRCBACKEND_ISMSYSTEMEVENTSPLUGIN_HXX

#include <tracing/irc/IIRCPlugin.hxx>

namespace tracing
{

class ISMSystemEventsPlugin : public IIRCPlugin
{
public:
    ~ISMSystemEventsPlugin() override = default;
    virtual void shutdownRequestedAck() = 0;
    virtual void shutdownCancelledAck() = 0;
};

} // end of namespace tracing

#endif /* TRACING_IRCBACKEND_ISMSYSTEMEVENTSPLUGIN_HXX */
