/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_ISDCARDMOUNTPLUGIN_HXX
#define TRACING_ISDCARDMOUNTPLUGIN_HXX

#include <common/types/string.hxx>
#include <osal/Path.hxx>

namespace tracing
{

/*!
 *    \brief
 *        Interface class for a SDCard plugin listener which gets notified about
 *        the result of SDCard mount operations.
 */
class ISDCardPluginListener
{
public:
    //! \brief Virtual destructor.
    virtual ~ISDCardPluginListener() {/* nop */}
    //! \brief Indication of a mount SDCard result under the given path.
    virtual void mountSDResult(bool success, const osal::Path & path) = 0;
};

/*!
 *    \brief
 *        Interface class for a SDCard mount plugin which initiates SDCard
 *        mount operations.
 */
class ISDCardMountPlugin
{
public:
    //! \brief Returns the plugin name.
    static const char * getName() { return nullptr; }

    //! \brief Returns the version of the plugin.
    static int32_t getVersion() { return 0; }

    /*!
     *  \brief
     *      Creates a new SDCard mount plugin.
     *
     *  \return
     *      A pointer to the newly created plugin.
     */
    static ISDCardMountPlugin * create() { return nullptr; }

    /*!
     *  \brief
     *      Destroys the plugin.
     *
     *  \param
     *      plugin A pointer to the plugin.
     */
    static void destroy(ISDCardMountPlugin * plugin) { delete plugin; }

    //! \brief Virtual destructor.
    virtual ~ISDCardMountPlugin() {/* nop */}

    /*!
     *  \brief
     *      Initializes the SDCard mount plugin.
     *
     *  \param
     *      listener The valid instance of a SDCard plugin listeners.
     */
    virtual bool init(ISDCardPluginListener * listener) = 0;

    //! \brief Shut down the plugin.
    virtual void exit() = 0;

    /*!
     *  \brief
     *      Initites a mount SDCard operation.
     *
     *  \param
     *      path The system mount path.
     */
    virtual void mountSD(const osal::Path & path) = 0;

    //! \brief Initiates the unmount of a SDCard.
    virtual void unmountSD() = 0;
};

} // end of namespace tracing

#endif /* TRACING_ISDCARDMOUNTPLUGIN_HXX */

