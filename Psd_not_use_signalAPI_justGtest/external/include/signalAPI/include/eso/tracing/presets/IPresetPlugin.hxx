/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IPRESETPLUGIN_HXX
#define TRACING_IPRESETPLUGIN_HXX

#include <common/types/string.hxx>
#include <tracing/presets/IPresetManagerCallbacks.hxx>

namespace tracing
{

class IPresetPlugin
{
public:
    // These static functions need to be present in a plugin to be able to
    // load and use it. The addresses of these need to be stored in a
    // struct PresetPluginFactory which must be accessible via a function
    // named getPresetPluginFactory().

    //! \brief Get the name of the preset plugin.
    static const char * getName() { return nullptr; }
    //! \brief Get the version number of the plugin.
    static int32_t getVersion() { return 0; }
    //! \brief Create a new instance of the preset plugin.
    static IPresetPlugin * create() { return nullptr; }
    //! \brief Destroy the instance previously created.
    static void destroy(IPresetPlugin * plugin) { delete plugin; }

    /*!
     * \brief
     *        Virtual destructor.
     *
     *        When unloading the plugin the custom destroy() function will be
     *        called. This virtual destructor merely saves a plugin implementor
     *        from casting inside the destroy() function. The destructor is
     *        never called directly from the plugin loader itself.
     */
    virtual ~IPresetPlugin() {/* nop */}

    /*!
     * \brief
     *        Initialize the plugin.
     * \param
     *        manager The interface which can be used for interacting with the
     *        PresetManager plugin which loads a preset plugin.
     * \return
     *        Return true, if plugin initialization succeeded, false otherwise.
     */
    virtual bool init(IPresetManagerCallbacks * manager) = 0;

    /*!
     * \brief
     *        Called by the PresetManager plugin before shutdown.
     *
     *        Do any cleanup work in the implementation of this method. The
     *        PresetManager plugin will call no other methods of the loaded
     *        plugin after this point. Furthermore, it may unload the plugin
     *        library anytime after this returns.
     */
    virtual void exit() = 0;

    /*!
     * \brief
     *        Notification about available presets.
     *
     *        This will be called once for any preset that is found on the
     *        system. Calls may happen anytime during the lifetime of the plugin.
     * \param
     *        preset_name The name of the preset.
     */
    virtual void addPreset(const ipl::string & preset_name) = 0;

    /*!
     * \brief
     *        Notification that all presets have been removed.
     * \note
     *        There is no remove method for single presets. Instead if presets
     *        disappear during runtime this method is called and followed by
     *        calls to addPreset() for any preset that remains.
     */
    virtual void removePresets() = 0;
};

} // end of namespace tracing

#endif /* TRACING_IPRESETPLUGIN_HXX */

