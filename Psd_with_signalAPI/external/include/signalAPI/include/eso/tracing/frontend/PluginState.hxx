/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_PLUGINSTATE_HXX
#define TRACING_PLUGINSTATE_HXX

#include <cstddef>
#include <tracing/tracing_dso.h>

namespace tracing
{

class IFrontendListener;
class AttachmentPool;

/*!
 *  \brief
 *      Class handling the state and attributes of a frontend plugin.
 */
class TRACINGIMPL_EXPORT PluginState final
{
public:
    /*!
     *    \brief
     *        Constructor.
     *
     *    \param
     *        id The plugin's ID.
     *    \param
     *        plugin The frontend listener plugin instance.
     */
    PluginState(int16_t id = -1, IFrontendListener * plugin = nullptr);

    /*!
     *    \brief
     *        Register plugin for usage of entity attachments.
     *    \param
     *        size The entity pool size.
     *    \return
     *        true if attachments can be used.
     */
    bool registerAttachments(size_t size);

    /*!
     *    \brief
     *        Unregister plugin for usage of entity attachments.
     *
     *        This will invalidate the stored pointers for this plugin. Further
     *        calls to getAttachment() will return nullptr only.
     */
    void unregisterAttachments();

    /*!
     *    \brief
     *        Store a pointer referencing an entity.
     *    \param
     *        id The entity id which shall be used for storing the attachment.
     *    \param
     *        attachment The pointer that shall be stored.
     */
    void setAttachment(int32_t id, void * attachment);

    /*!
     *    \brief
     *        Retrieve a previously stored attachment.
     *    \param
     *        id The entity id which was used for storing the attachment.
     *    \return
     *        The stored pointer or nullptr if not set.
     */
    void * getAttachment(int32_t id) const;
protected:
    IFrontendListener * m_plugin;
    AttachmentPool * m_attachments;
    int16_t m_id;
};

} // end of namespace tracing

#endif /* TRACING_PLUGINSTATE_HXX */

