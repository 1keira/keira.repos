/*
   Copyright 2023 e.solutions GmbH
   All rights reserved
*/

#ifndef TRACING_IRCBACKEND_IIRCPRIVACYPLUGIN_HXX
#define TRACING_IRCBACKEND_IIRCPRIVACYPLUGIN_HXX

#include <tracing/irc/IIRCPlugin.hxx>

namespace tracing
{

class IIRCPrivacyPlugin : public IIRCPlugin
{
public:
    ~IIRCPrivacyPlugin() override = 0;
};

inline IIRCPrivacyPlugin::~IIRCPrivacyPlugin() { /* nop */ }

} // end of namespace tracing

#endif /* TRACING_IRCBACKEND_ILOGTRANSFERPLUGIN_HXX */
