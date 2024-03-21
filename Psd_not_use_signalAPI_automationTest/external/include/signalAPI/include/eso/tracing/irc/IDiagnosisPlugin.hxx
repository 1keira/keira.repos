/*
   Copyright 2023 e.solutions GmbH
   All rights reserved
*/

#ifndef TRACING_IRCBACKEND_IDIAGNOSISPLUGIN_HXX
#define TRACING_IRCBACKEND_IDIAGNOSISPLUGIN_HXX

#include <tracing/irc/IIRCPlugin.hxx>

namespace tracing
{

class IDiagnosisPlugin : public IIRCPlugin
{
public:
    ~IDiagnosisPlugin() override = 0;
};

inline IDiagnosisPlugin::~IDiagnosisPlugin() { /* nop */ }

} // end of namespace tracing

#endif /* TRACING_IRCBACKEND_IDIAGNOSISPLUGIN_HXX */
