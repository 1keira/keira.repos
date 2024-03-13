/*
  	Copyright e.solutions GmbH
	All rights reserved
	Authors:
		Stefan Bittner
*/
#ifndef COMM_DSO_H
#define COMM_DSO_H

#include <ipl_config.h>
#include <iplbase/dso_macros.h>
/*
	Defines the export/import macros for the comm shared object.

	On Windows platforms export and import of symbols with regards to shared
	objects have to be specified explicitely.

	The macro definitione herein allow to do this.
	Classes should be decorated in their header files in the following way:

	class COMM_EXPORT ClassName : public SomeClass {
		// class definition
	};

	Functions use:

	COMM_EXPORT returnType Function1(arg list);
*/

// the iplcommon code may be compiled into different libraries as of now iplcommon hence the
// expansion of the COMM_EXPORT needs to be triggered by either of them
#if defined (comm_EXPORTS)
    #define COMM_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS)
    #define COMM_EXPORT IPL_STATICLINK_MARKER
#else
    #define COMM_EXPORT IPL_IMPORT_MARKER
#endif

#endif
