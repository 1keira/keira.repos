/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_UTIL_HXX
#define UTIL_UTIL_HXX

/*
 *     common header for util  library
 */

#include <ipl_config.h>

#include <stdlib.h>

#include <common/types/new.hxx>
#include <common/Macros.hxx>

#include <osal/osal.hxx>
#include <osal/ProcessTNG.hxx>
#include <osal/SharedObj.hxx>

#include <util/util_dso.h>
#include <tracing/tracing.hxx>
#include <util/config/FrameworkProvider.hxx>

namespace util
{

/**
 *    \brief
 *        UTIL initialization class

 *        Before accessing any other UTIL functionality an instance of this class needs to be
 *        created. The lifetime of this object defines also the lifetime of UTIL
 *        initialization. When the object is destructed UTIL cannot be used any longer.
 *
 *        Typically you will want to define an instance of this class in your main function
 *        before doing anything else.
 *    \see
 *        osal::Osal
 **/
class UTIL_EXPORT Util
{
public:
    /**
     *    \brief
     *        Construct Util object and thus initialize the util library
     *    \param[in] osal
     *        This parameter is required to correctly express the dependency of the util
     *        library to the osal library.
     *    \param[in] with_tracing
     *        Specifies whether tracing should be initialized. If you pass false here
     *        but still want to use the tracing API, you need to explicitly initialize
     *        the tracing subsystem yourself, e.g. by calling IPL_TRACE_INIT().
     *    \param[in] with_probes
     *        deprecated
     *    \param[in] read_trace_config
     *        Specifies whether tracing.json should be parsed by tracing subsystem.
     **/
    Util(const osal::Osal &osal, const char* process_name = NULL,
        bool with_tracing = true, bool with_probes = false,
        bool read_trace_config = true, bool read_probes_config = false) IPL_NOEXCEPT
    {
        init(process_name, with_tracing, with_probes,
                read_trace_config, read_probes_config);
    }

    static void init(const char* process_name = NULL, bool with_tracing = true,
        bool with_probes = false, bool read_trace_config = true,
        bool read_probes_config = false) IPL_NOEXCEPT;

    ~Util() IPL_NOEXCEPT
    {
        IPL_ASSERT( s_initialized );

        if( (! --s_init_count) && s_initialized ) // BRANCH_COVERAGE_UNREACHABLE
        {
            cleanupAll();
        }
    }

protected:
    static void cleanupAll() IPL_NOEXCEPT;

    static void processExit() IPL_NOEXCEPT
    {
        if( s_initialized )
            cleanupAll();
    }

    //! initialize tracing subsystem
    static bool initTracing(const char* process_name = NULL, bool read_trace_config = true) IPL_NOEXCEPT;

    //! shutdown tracing subsystem
    static bool exitTracing() IPL_NOEXCEPT;

    /**
     * \brief
     *     Adds error handlers to ipl::GlobalErrorHandler that
     *     trace the errors
     **/
    static void setupTraceErrorHandlers() IPL_NOEXCEPT;

private:
    //! static boolean that tells whether currently UTIL is initialized or not
    static bool s_initialized;

    //! whether util has ever been initialized
    static bool s_ever_initialized;

    //! number of initializations at the time
    static osal::AtomicCounter s_init_count;

    //! static boolean that tells whether tracing was initialized together with UTIL
    static bool s_with_tracing;

    //! loads the tracing library if tracing is requested via Util() constructor
    static osal::SharedObj * s_lib_tracing;
};

} // end ns util

#endif
