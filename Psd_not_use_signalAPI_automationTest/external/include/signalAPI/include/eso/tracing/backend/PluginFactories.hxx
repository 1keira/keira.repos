/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_PLUGINFACTORIES_HXX
#define TRACING_PLUGINFACTORIES_HXX

#include <common/stdint.h>

namespace tracing
{

class IBackend;
class IMessageFormatter;
class IMessageDecoder;
class IMessageFilter;
class IFrontendListener;
class IPresetPlugin;
class IPowerStatePlugin;
class ISDCardMountPlugin;

typedef const char *    (*BackendName)();
typedef int32_t         (*BackendVersion)();
typedef IBackend *      (*BackendCreate)();
typedef void            (*BackendDestroy)(IBackend *);

//! \brief Struct containing static methods of an IBackend class. \sa BackendFactoryFct
struct BackendFactory
{
    BackendName backend_name;
    BackendVersion backend_version;
    BackendCreate backend_create;
    BackendDestroy backend_destroy;
};

typedef const char *        (*FormatterName)();
typedef int32_t             (*FormatterVersion)();
typedef IMessageFormatter * (*FormatterCreate)();
typedef void                (*FormatterDestroy)(IMessageFormatter *);

//! \brief Struct containing static methods of an IMessageFormatter class. \sa FormatterFactoryFct
struct FormatterFactory
{
    FormatterName formatter_name;
    FormatterVersion formatter_version;
    FormatterCreate formatter_create;
    FormatterDestroy formatter_destroy;
};

typedef const char *        (*DecoderName)();
typedef int32_t             (*DecoderVersion)();
typedef IMessageDecoder *   (*DecoderCreate)();
typedef void                (*DecoderDestroy)(IMessageDecoder *);

//! \brief Struct containing static methods of an IMessageDecoder class. \sa DecoderFactoryFct
struct DecoderFactory
{
    DecoderName decoder_name;
    DecoderVersion decoder_version;
    DecoderCreate decoder_create;
    DecoderDestroy decoder_destroy;
};

typedef const char *        (*FrontendListenerName)();
typedef int32_t             (*FrontendListenerVersion)();
typedef IFrontendListener * (*FrontendListenerCreate)();
typedef void                (*FrontendListenerDestroy)(IFrontendListener *);

//! \brief Struct containing static methods of an IFrontendListenerPlugin class. \sa FrontendListenerFactoryFct
struct FrontendListenerFactory
{
    FrontendListenerName listener_name;
    FrontendListenerVersion listener_version;
    FrontendListenerCreate listener_create;
    FrontendListenerDestroy listener_destroy;
};

typedef const char *        (*PresetPluginName)();
typedef int32_t             (*PresetPluginVersion)();
typedef IPresetPlugin *     (*PresetPluginCreate)();
typedef void                (*PresetPluginDestroy)(IPresetPlugin *);

//! \brief Struct containing static methods of an IPresetPlugin class. \sa PresetPluginFactoryFct
struct PresetPluginFactory
{
    PresetPluginName preset_plugin_name;
    PresetPluginVersion preset_plugin_version;
    PresetPluginCreate preset_plugin_create;
    PresetPluginDestroy preset_plugin_destroy;
};

typedef const char *        (*PowerStatePluginName)();
typedef int32_t             (*PowerStatePluginVersion)();
typedef IPowerStatePlugin * (*PowerStatePluginCreate)();
typedef void                (*PowerStatePluginDestroy)(IPowerStatePlugin *);

//! \brief Struct containing static methods of an IPowerStatePlugin class.
struct PowerStatePluginFactory
{
    PowerStatePluginName powerstate_plugin_name;
    PowerStatePluginVersion powerstate_plugin_version;
    PowerStatePluginCreate powerstate_plugin_create;
    PowerStatePluginDestroy powerstate_plugin_destroy;
};

typedef const char *        (*SDCardMountPluginName)();
typedef int32_t             (*SDCardMountPluginVersion)();
typedef ISDCardMountPlugin * (*SDCardMountPluginCreate)();
typedef void                (*SDCardMountPluginDestroy)(ISDCardMountPlugin *);

//! \brief Struct containing static methods of an ISDCardMountPlugin class.
struct SDCardMountPluginFactory
{
    SDCardMountPluginName sdcardmount_plugin_name;
    SDCardMountPluginVersion sdcardmount_plugin_version;
    SDCardMountPluginCreate sdcardmount_plugin_create;
    SDCardMountPluginDestroy sdcardmount_plugin_destroy;
};


typedef const char *      (*MessageFilterName)();
typedef int32_t           (*MessageFilterVersion)();
typedef IMessageFilter *  (*MessageFilterCreate)();
typedef void              (*MessageFilterDestroy)(IMessageFilter *);

//! \brief Struct containing static methods of an IMessageFilter class. \sa MessageFilterFactoryFct
struct MessageFilterFactory
{
    MessageFilterName        message_filter_name;
    MessageFilterVersion     message_filter_version;
    MessageFilterCreate      message_filter_create;
    MessageFilterDestroy     message_filter_destroy;
};

} // end of namespace tracing

extern "C"
{
    /*!
     *  \brief
     *      Typedef for a function returning a struct BackendFactory.

     *      Custom backend plugins should export a function with this
     *      signature and return a struct containing function pointers
     *      to the specified backend functions. These function pointers
     *      will be used by the tracing's plugin loader to create an
     *      instance of the custom backend.
     */
    typedef tracing::BackendFactory * (*BackendFactoryFct)();
    /*!
     *  \brief
     *      Typedef for a function returning a struct FormatterFactory.

     *      Custom formatter plugins should export a function with this
     *      signature and return a struct containing function pointers
     *      to the specified formatter functions. These function pointers
     *      will be used by the tracing's plugin loader to create an
     *      instance of the custom message formatter.
     */
    typedef tracing::FormatterFactory * (*FormatterFactoryFct)();
    /*!
     *  \brief
     *      Typedef for a function returning a struct DecoderFactory.

     *      Custom decoder plugins should export a function with this
     *      signature and return a struct containing function pointers
     *      to the specified decoder functions. These function pointers
     *      will be used by the tracing's plugin loader to create an
     *      instance of the custom message decoder.
     */
    typedef tracing::DecoderFactory * (*DecoderFactoryFct)();
    /*!
     *  \brief
     *      Typedef for a function returning a struct FrontendListenerFactory.

     *      Custom frontend plugins should export a function with this
     *      signature and return a struct containing function pointers
     *      to the specified frontend functions. These function pointers
     *      will be used by the tracing's plugin loader to create an
     *      instance of the custom frontend plugin.
     */
    typedef tracing::FrontendListenerFactory * (*FrontendListenerFactoryFct)();

    /*!
     *  \brief
     *      Typedef for a function returning a struct MessageFilterFactory.

     *      Custom message filters should export a function with this
     *      signature and return a struct containing function pointers
     *      to the specified message filter functions. These function pointers
     *      will be used by the tracing's plugin loader to create an
     *      instance of the custom message filter.
     */
    typedef tracing::MessageFilterFactory * (*MessageFilterFactoryFct)();

    /*!
     *  \brief
     *      Typedef for a function returning a struct PresetPluginFactory.

     *      Custom preset plugins should export a function with this
     *      signature and return a struct containing function pointers
     *      to the specified preset functions. These function pointers
     *      will be used by the tracing's plugin loader to create an
     *      instance of the custom frontend plugin.
     */
    typedef tracing::PresetPluginFactory * (*PresetPluginFactoryFct)();
}

#endif /* TRACING_PLUGINFACTORIES_HXX */

