/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_FACTORYERRORS_HXX
#define UTIL_TRANSPORT_FACTORYERRORS_HXX

#include <util/util_dso.h>
#include <common/error/Error.hxx>
#include <common/lexical_cast.hxx>

namespace util
{
namespace transport
{

enum FactoryErrors
{
    //! A transport link configuration could not be found
    LINK_NOT_FOUND = 0,
    //! A mapping error occured (string(s) couldn't be mapped to ID(s)
    MAP_ERROR,
    //! A transport link configuration is unsupported by factory
    UNSUPPORTED_TRANSPORT,
    //! A transport link configuration is logically incompatible with a factory type
    INCOMPATIBLE_TRANSPORT,
    //! A transport configuration is erroneous of missing information
    INVALID_CONFIG,
    //! A transport was tried to be created according to configuration but the operation failed
    CREATION_ERROR,
    //! Another transport cannot be created by a factory as one is still active
    TRANSPORT_IN_USE,
    //! A transport does not belong to a given factory
    TRANSPORT_MISMATCH,
    //! A transport is in the wrong state to perform an operation
    INVALID_TRANSPORT_STATE,
    //! A blocking call was canceled by client interaction
    BLOCKING_CALL_CANCELED,
    //! process settings in config not found
    PROCESS_NOT_FOUND,
    //! configuration for the process is invalid
    PROCESS_CONFIG_INVALID,
    //! node declaration for process in config not found
    PROCESS_NODE_NOT_FOUND,
    //! can't find transport configuration for a node for a service
    NODE_TRANSPORT_CONFIG_NOT_FOUND,
    //! transport config for the node is invalid
    NODE_TRANSPORT_CONFIG_INVALID,
    //! can't find the configuration for my transport settings
    TRANSPORT_CONFIG_NOT_FOUND,
    //! no serializer entry found in config
    NODE_SEARIALILZER_CONFIG_MISSING,
    //! invalid  serializer entry found in config
    NODE_SEARIALILZER_CONFIG_INVALID,
    //! can't find mode for the requested transport
    TRANSPORT_MODE_NOT_DEFINED,
    //! settings for a transport for a specific mode are invalid
    TRANSPORT_MODE_SETTINGS_INVALID,
    //! settings for a single transport from one process to another process for a service invalid
    TRANSPORT_SINGLE_SETTINGS_INVALID,
    //! no loadable shared object found for the transport
    LOADABLE_TRANSPORT_NOT_FOUND,
    //! the loadable transport factory does not contain any factory
    LOADABLE_TRANSPORT_EMPTY,
    //! the loadable transport factory does not contain the requested factory
    LOADABLE_TRANSPORT_MISSING_FACTORY,
    //! Can't create a channel (qnx message passing)
    CANT_CREATE_CHANNEL
};

const ipl::ErrorID FACTORY_ERROR_TABLE[] =
{
    { LINK_NOT_FOUND, "FactoryError: Couldn't find transport link from '%s' to '%s' via service '%s'", 3 },
    { MAP_ERROR, "FactoryError: Failed to map '%s' to an identifier", 1 },
    { UNSUPPORTED_TRANSPORT, "FactoryError: Transport type '%s' isn't supported by factory", 1 },
    { INCOMPATIBLE_TRANSPORT, "FactoryError: Transport type '%s' in mode '%s' isn't supported by factory", 2 },
    { INVALID_CONFIG, "FactoryError: Missing or invalid entry '%s' in transport configuration", 1 },
    { CREATION_ERROR, "FactoryError: Unable to create the configured transport '%s'", 1 },
    { TRANSPORT_IN_USE, "FactoryError: Can't create another transport as there is still one in use", 0 },
    { TRANSPORT_MISMATCH, "FactoryError: The given transport was no created by this factory", 0 },
    { INVALID_TRANSPORT_STATE,"FactoryError: The given transport has got an invalid state to perform the desired operation",  0 },
    { BLOCKING_CALL_CANCELED, "FactoryError: A blocking call has been canceled by client request", 0 },
    { PROCESS_NOT_FOUND, "FactoryError in %s: configuration for process '%s' not found", 2 },
    { PROCESS_CONFIG_INVALID, "FactoryError in %s: transport configuration for process '%s' not found", 2 },
    { NODE_TRANSPORT_CONFIG_INVALID, "FactoryError in %s: transport configuration for node '%s' for service '%s' invalid", 3 },
    { PROCESS_NODE_NOT_FOUND, "FactoryError in %s: 'node' for process '%s' not defined", 2 },
    { NODE_TRANSPORT_CONFIG_NOT_FOUND, "FactoryError in %s: can't find transport to '%s' for service '%s'", 3 },
    { TRANSPORT_CONFIG_NOT_FOUND, "FactoryError in %s: can't find transport config from node '%s' to node '%s' for service %s", 4 },
    { NODE_SEARIALILZER_CONFIG_MISSING, "FactoryError in %s: can't find serializer in '%s':'%s':'%s'", 4 },
    { NODE_SEARIALILZER_CONFIG_INVALID, "FactoryError in %s: serializer entry in '%s':'%s':'%s' is invalid", 4 },
    { TRANSPORT_MODE_NOT_DEFINED, "FactoryError in %s: can't find transport 'mode' for process '%s' on node '%s' for service '%s'", 4 },
    { TRANSPORT_MODE_SETTINGS_INVALID, "FactoryError in %s: invalid transport settings for process '%s' on node '%s' for service '%s' for mode '%s'", 5 },
    { TRANSPORT_SINGLE_SETTINGS_INVALID, "FactoryError in %s: invalid transport settings for process '%s' to process '%s' for service '%s' ", 4 },
    { LOADABLE_TRANSPORT_NOT_FOUND, "FactoryError: no loadable transport factory found for transport '%s', tried '%s'", 2 },
    { LOADABLE_TRANSPORT_EMPTY, "FactoryError: the loadable transport factory '%s' is empty (missing '%s')", 2 },
    { LOADABLE_TRANSPORT_MISSING_FACTORY, "FactoryError: the loadable transport factory for transport '%s' is missing '%s' ", 2 },
    { CANT_CREATE_CHANNEL, "FactoryError: Can't create channel: %s ", 1 }
};

UTIL_EXPORT extern ipl::ErrorType FactoryError;

#define IPL_RERAISE_TCPIP_CREATION_ERROR(ipaddr) {\
ipl::string tmp(ipaddr.address); \
tmp += ":"; \
tmp += ipl::lexical_cast<ipl::string>(ipaddr.port); \
ipl_reraise( FactoryError, CREATION_ERROR,tmp.c_str() ); \
}

#define FACTORYERRORS_RERAISE_RESMAN_CREATION_ERROR(path) {\
ipl::string tmp("resman "); \
tmp += path; \
ipl_reraise( FactoryError, CREATION_ERROR,tmp.c_str() ); \
}

#define FACTORYERRORS_RERAISE_SHM_CREATION_ERROR(identifier) {\
ipl::string tmp("shm id \""); \
tmp += identifier; \
tmp += "\""; \
ipl_reraise( FactoryError, CREATION_ERROR, tmp.c_str() ); \
}

} // end namespace transport
} // end namespace util

#endif
