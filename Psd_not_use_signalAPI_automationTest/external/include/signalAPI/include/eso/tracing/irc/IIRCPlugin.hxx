/*
   Copyright 2023 e.solutions GmbH
   All rights reserved
*/

#ifndef TRACING_IRCBACKEND_IIRCPLUGIN_HXX
#define TRACING_IRCBACKEND_IIRCPLUGIN_HXX

namespace util
{
namespace config
{
class Value;
}
}

namespace tracing
{

class IIRCBackend;

class IIRCPlugin
{
public:
    virtual ~IIRCPlugin() = 0;

    static const char * const FACTORY_FUNCTION_SYMBOL /* = "getIrcPluginFactory" */;
};

inline IIRCPlugin::~IIRCPlugin() { /* nop */ }

typedef const char *    (*IRCPluginName)();
typedef int32_t         (*IRCPluginVersion)();
typedef IIRCPlugin *    (*IRCPluginCreate)(IIRCBackend *, const util::config::Value &);
typedef void            (*IRCPluginDestroy)(IIRCPlugin *);

struct IRCPluginFactory
{
    IRCPluginName       plugin_name;
    IRCPluginVersion    plugin_version;
    IRCPluginCreate     plugin_create;
    IRCPluginDestroy    plugin_destroy;
};

} // end of namespace tracing

extern "C"
{

typedef tracing::IRCPluginFactory * (*IRCPluginFactoryFunc)();

}

#endif /* TRACING_IRCBACKEND_IIRCPLUGIN_HXX */
