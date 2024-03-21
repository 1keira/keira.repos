/*
   Copyright 2023 e.solutions GmbH
   All rights reserved
*/

#ifndef TRACING_IRCBACKEND_ILOGTRANSFERPLUGIN_HXX
#define TRACING_IRCBACKEND_ILOGTRANSFERPLUGIN_HXX

#include <tracing/irc/IIRCPlugin.hxx>

namespace tracing
{

class ILogTransferPlugin : public IIRCPlugin
{
public:
    ~ILogTransferPlugin() override = default;

    virtual bool isCanceled() = 0;
    virtual bool putLog(const void * const data, size_t len, const int8_t progress) = 0;
    virtual bool logComplete() = 0;
};

} // end of namespace tracing

#endif /* TRACING_IRCBACKEND_ILOGTRANSFERPLUGIN_HXX */

