#ifndef SERVMNGT_ERRORS_HXX
#define SERVMNGT_ERRORS_HXX

/*
  	Copyright e.solutions GmbH
	All rights reserved
	Authors:
		Martin Ruff
	$Id: SmErrors.hxx 11218 2010-01-26 12:22:08Z martin.ruff $
*/

#include <common/error/Error.hxx>
#include <servmngt/servmngt_dso.h>

namespace servmngt {
	
namespace error {


enum Errors {
	//! The object is not initialized or was not constructed successfully
	OBJECT_NOT_VALID = 0,
	//! The application is not part of the configuration
	APP_NOT_CONFIGURED,
	//! The application was already added to the bundle
	APP_ALREADY_ADDED,
	//! The bundle loader commandline is invalid
	BUNDLE_LOADER_COMMAND_LINE_ERR,
	//! no process name given
	BUNDLE_LOADER_MISSING_PROC_NAME,
	//! no application name given
	BUNDLE_LOADER_MISSING_APPLICATION_NAME,
	//! process name not found in the configuration
	BUNDLE_LOADER_UNKOWN_PROC_NAME,
	//! application instance not given
	BUNDLE_LOADER_APPINSTANCE_MISSING,
	//! basic initialisation failed
	BUNDLE_LOADER_INIT_FAILED,
	//! A bundle was not valid after construction
	CANNOT_INSTANTIATE_BUNDLE,
	//! error on creating dictionary
	DICTIONARY_INVALID,
	//! call into the servmngt::core without initializiing before
	CORE_NOT_INITIALIZED,
	//! the handle to a configuration command block is unknown
	UNDEFINED_CONFIGCOMMANDBLOCK_HANDLE,
	//! a given config command block can't be executed
	CANT_EXECUTED_CONFIGCOMMANDBLOCK,
	//! command can't be performed because of wrong system state
	WRONG_SYSTEM_STATE,
    //! service.json not found or not loadable
    SERVMNGT_JSON_NOT_FOUND,
    //! some timeout occured
    EXECUTION_TIMEOUT
	};

}


/**
\brief	This class defines an error type for the service management module.
*/
SERVMNGT_EXPORT extern ipl::ErrorType Error;

}

#endif

