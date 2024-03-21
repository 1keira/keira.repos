/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

#ifndef COMM_ERROR_HXX
#define COMM_ERROR_HXX

/**
    \brief 	This class defines an error typr for the comm module.
**/

#include <common/error/Error.hxx>
#include <common/streams/sstream.hxx>
#include <osal/sched.hxx>
#include <comm/commtypes.hxx>
// for win32 DLL linkage
#include <comm/comm_dso.h>
#include <comm/util.hxx>

namespace comm {

    /** \brief comm error declarations and fatal error handling functions
    */
    namespace error {
        typedef Errors CommErrors;

        /** action to be taken in the comm module if a fatal error condition is encountered */
        COMM_EXPORT void fatal (const char* message, bool attach_reason=true);
        /** action to be taken in the comm module if a fatal error condition is encountered */
        COMM_EXPORT void fatal (const char* message, const char* file, int line, bool attach_reason=true);

        /** Warn about trouble when trying to set thread priorities.
         * message must be a printf format string containing a %d for priority
         * obsolete, deprecated
         */
        COMM_EXPORT void priority_warn (const char* message, const osal::sched::Attr& attr);

        /** Warn about trouble when trying to set thread priorities.
         * The resulting message will concatenate message and the stringified attr
         */
        COMM_EXPORT void priority_warn2 (const char* message, const osal::sched::Attr& attr);
        /** Traces an error  when trying to set thread priorities.
         */
        COMM_EXPORT void priority_error (const char* message);
    }

// macros for o-streaming messages
#define COMM_ERROR_FATAL(msg) \
        do { \
            ipl::ostringstream __comm_errr_fatal_tmp; \
            __comm_errr_fatal_tmp << msg; \
            ipl::ErrorIterator __comm_err_it = ipl_error.begin();\
            while ( __comm_err_it != ipl_error.end() ) {\
                __comm_errr_fatal_tmp <<": " << __comm_err_it->reason();\
                ++__comm_err_it;\
            }\
            comm::error::fatal(__comm_errr_fatal_tmp.str().c_str(), false); \
        } while (0)

#define COMM_ERROR_FATAL_HERE(msg) \
        do { \
            ipl::ostringstream __comm_errr_fatal_tmp; \
            __comm_errr_fatal_tmp << msg; \
            ipl::ErrorIterator __comm_err_it = ipl_error.begin();\
            while ( __comm_err_it != ipl_error.end() ) {\
                __comm_errr_fatal_tmp <<": "<< __comm_err_it->reason();\
                ++__comm_err_it;\
            }\
            comm::error::fatal(__comm_errr_fatal_tmp.str().c_str(), __FILE__, __LINE__, false); \
        } while (0)

    COMM_EXPORT extern ipl::ErrorType Error;

}

#endif /* COMM_ERROR_HXX */

