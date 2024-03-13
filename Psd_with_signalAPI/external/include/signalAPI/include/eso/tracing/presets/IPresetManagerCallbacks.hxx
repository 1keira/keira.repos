/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IPRESETMANAGERCALLBACKS_HXX
#define TRACING_IPRESETMANAGERCALLBACKS_HXX

#include <common/types/string.hxx>

namespace tracing
{

/*!
 * \brief
 *        Provides an interface for PresetManager plugins.
 *
 *        This interface is implemented by the PresetManager plugin and can be
 *        used by implementors of IPresetPlugin for activating presets, querying
 *        status etc.
 */
class IPresetManagerCallbacks
{
public:
    //! Virtual destructor.
    virtual ~IPresetManagerCallbacks() {/* nop */}

    /*!
     * \brief
     *        Activate a preset.
     * \param
     *        name The name of the preset that should be activated. Preset names
     *        usually follow this pattern: \<json prest file basename>::\<preset>,
     *        e.g. 'persistence::default' for a preset named 'default' in a file
     *        named 'persistence.json'.
     * \return
     *        True if activation succeeded, false otherwise.
     */
    virtual bool enablePreset(const ipl::string & name) = 0;

    /*!
     * \brief
     *        Add externally provided presets.
     *
     *        This can be used to add additional presets which are not found on
     *        the system at startup time, e.g. by inserting an SD card or some
     *        other external medium.
     * \param
     *        path Absolute path to a preset file in Json format.
     * \param[out]
     *        result The list of presets found in the provided file which were
     *        successfully added to the internal list of available presets.
     * \note
     *        If conflicts exist, i.e. a preset should be added which is alreay
     *        present on the system it will be ignored and thus missing in the
     *        result vector.
     * \note
     *        The plugin's IPresetPlugin::addPreset() method will not be called
     *        in this case.
     */
    virtual void addPresetFile(const ipl::string & path,
            ipl::vector<ipl::string> & result) = 0;

    /*!
     * \brief
     *        Reset channel settings to defaults.
     *
     *        This will revert all changes that were made to channel and thread
     *        levels since startup. This means if a preset was persisted on the
     *        system, its level settings will be restored. If the system started
     *        with default trace settings, the values from the tracing
     *        configuration file will be used instead.
     */
    virtual void resetToDefault() = 0;

    /*!
     * \brief
     *        Save the current channel and thread level changes for future
     *        system startups.
     *
     *        This will create a file on the filesystem, usually named
     *        'savedpreset.json' which will contain level settings that are used
     *        for initializing levels instead of the levels specified in tracing
     *        configuration file.
     */
    virtual void saveCurrentSettings() = 0;

    /*!
     * \brief
     *        Remove the persisted channel settings created by
     *        saveCurrentSettings().
     */
    virtual void removeCurrentSettings() = 0;

    /*!
     * \brief
     *        Get some statistical information.
     * \param
     *        msgs Total number of trace messages created will be stored here.
     * \param
     *        drops Total number of trace messages dropped will be stored here.
     * \return
     *        True if stored values are valid, false in case of errors. msgs and
     *        drops may be invalid in this case.
     */
    virtual bool getMessageAndDropCount(size_t & msgs,
            size_t & drops) const = 0;

    /*!
     * \brief
     *        Config query functionality for preset plugins.
     * \param
     *        key The key whose value should be queried in the tracing
     *        configuration file.
     * \param
     *        default_value The value which will be returned, if 'key' is not
     *        found in the configuration.
     * \return
     *        The string value which is associated with 'key'.
     */
    virtual ipl::string getConfigString(const ipl::string & key,
            const ipl::string & default_value = "") = 0;

    /*!
     * \brief
     *        Config query functionality for preset plugins.
     * \param
     *        key The key whose value should be queried in the tracing
     *        configuration file.
     * \param
     *        default_value The value which will be returned, if 'key' is not
     *        found in the configuration.
     * \return
     *        The integer value which is associated with 'key'.
     */
    virtual int32_t getConfigInteger(const ipl::string & key,
            int32_t default_value = 0) = 0;

    /*!
     * \brief
     *        Config query functionality for preset plugins.
     * \param
     *        key The key whose value should be queried in the tracing
     *        configuration file.
     * \param
     *        default_value The value which will be returned, if 'key' is not
     *        found in the configuration.
     * \return
     *        The bool value which is associated with 'key'.
     */
    virtual bool getConfigBool(const ipl::string & key,
            bool default_value = false) = 0;
};

} // end of namespace tracing

#endif /* TRACING_IPRESETMANAGERCALLBACKS_HXX */

