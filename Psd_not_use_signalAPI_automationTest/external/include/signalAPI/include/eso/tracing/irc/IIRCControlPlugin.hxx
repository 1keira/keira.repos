/*
   Copyright 2023 e.solutions GmbH
   All rights reserved
*/

#ifndef TRACING_IRCBACKEND_IIRCCONTROLPLUGIN_HXX
#define TRACING_IRCBACKEND_IIRCCONTROLPLUGIN_HXX

#include <comm/commtypes.hxx>
#include <tracing/irc/IIRCPlugin.hxx>

namespace tracing
{

class IIRCControlPlugin : public IIRCPlugin
{
public:
    ~IIRCControlPlugin() override = default;

    virtual void sendStartDone() = 0;
    virtual void sendStopDone(const void * context) = 0;
    virtual void sendSyncDone(const void * context) = 0;
};

} // end of namespace tracing

#endif /* TRACING_IRCBACKEND_IIRCCONTROLPLUGIN_HXX*/
