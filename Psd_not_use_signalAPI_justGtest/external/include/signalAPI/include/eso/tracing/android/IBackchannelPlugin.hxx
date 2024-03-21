/*
    Copyright 2023 e.solutions GmbH
    All rights reserved
 */
#ifndef TRACING_IBACKCHANNEL_PLUGIN_HXX_
#define TRACING_IBACKCHANNEL_PLUGIN_HXX_

#include <string>

namespace tracing {

/**
 * \brief
 *    Interface which is used for running the Android AOSP backchannel services.
 *
 *    Android AOSP backchannel client and server need to implement this interface.
 *    Tracecore will start thread with related threadloop.
 **/
class IBackchannelPlugin
{
public:
    /**
     * \brief
     *    These static functions need to be present in a plugin to be able to
     *    load and use it. The addresses of these need to be stored in a
     *    struct PresetPluginFactory which must be accessible via a function
     *    named getPresetPluginFactory().
     **/

    //! \brief Get the name of the preset plugin.
    static const char * getName() { return nullptr; }
    //! \brief Get the version number of the plugin.
    static int32_t getVersion() { return 0; }
    //! \brief Create a new instance of the preset plugin.
    static IBackchannelPlugin* create() { return nullptr; }
    //! \brief Destroy the instance previously created.
    static void destroy(IBackchannelPlugin* plugin) { delete plugin; }

    /*!
     * \brief
     *        Virtual destructor.
     *
     *        When unloading the plugin the custom destroy() function will be
     *        called. This virtual destructor merely saves a plugin implementor
     *        from casting inside the destroy() function. The destructor is
     *        never called directly from the plugin loader itself.
     */
    virtual ~IBackchannelPlugin() = default;

    /**
     * \brief
     *     Will be started by tracecore to run AOSP server or client backchannel service.
     *
     * \param[in] caller  A shared pointer to IBackchannelServer or IBackchannelClient
     *                    which allows the AOSP side to emit callbacks towards the tracecore.
     **/
    virtual void threadloop(void* caller) = 0;

    /**
     * \brief
     *     Indication by tracecore towards AOSP backchannel service to stop services.
     **/
    virtual void shutdown() = 0;
};

typedef const char*         (*BackchannelName)();
typedef int32_t             (*BackchannelVersion)();
typedef IBackchannelPlugin* (*BackchannelCreate)(const std::string& /*fwk client name*/);
typedef void                (*BackchannelDestroy)(IBackchannelPlugin*);

//! \brief Struct containing static methods of an IBackchannelPlugin.
struct BackchannelPluginFactory
{
    BackchannelName    backchannel_plugin_name;
    BackchannelVersion backchannel_plugin_version;
    BackchannelCreate  backchannel_plugin_create;
    BackchannelDestroy backchannel_plugin_destroy;
};

extern "C"
{
    /*!
     *  \brief
     *      Typedef for a function returning a struct BackchannelPluginFactory.

     *      Custom Android AOSP backchannel plugins should export a function with
     *      this signature and return a struct containing function pointers
     *      to the specified backchannel functions. These function pointers
     *      will be used by the tracing's plugin loader to create an
     *      instance of the Android backchannel plugin.
     */
    typedef tracing::BackchannelPluginFactory * (*BackchannelPluginFactoryFct)();
}

} /*  namespace tracing */

#endif /* TRACING_IBACKCHANNEL_PLUGIN_HXX_ */
