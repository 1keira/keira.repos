/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_OSAL_HXX
#define OSAL_OSAL_HXX

/*
    OS abstraction for some os-specific - free functions and for
    generic OSAL types, global OSAL type definitions / constants
    etc.

    Actually is just one of that famous "misc" functionality files.
*/

#include <ipl_config.h>
#include <common/stdint.h>

#ifdef USE_THREADSAFE_IN_OSAL
#include <iplbase/time.hxx>
#endif

#if (defined IPL_OS_POSIX) || (defined IPL_OS_INTEGRITY)
#    include "posix/SystemInfoDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/SystemInfoDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal {

    //! An abstract type for time values of any kind
    //! which happens not to be abstract at all
    typedef int64_t TimeT;

}

#include <common/streams/iostream.hxx>
#include <common/error/Error.hxx>
#include <common/Macros.hxx>
#include <osal/AtomicCounter.hxx>
#include <osal/osal_dso.h>
#include <osal/sched.hxx>

namespace osal {

    /**
    * \brief
    *    OSAL initialization class
    * \note
    *    on Error the constructor aborts

    *    Before accessing any other OSAL functionality an instance of
    *    this class needs to be created. The lifetime of this object
    *    defines also the lifetime of OSAL initialization. When the
    *    object is destructed OSAL cannot be used any longer.
    *
    *    Typically you will want to define an instance of this class in
    *    your main function before doing anything else. The motivation of
    *    this requirement follows.
    *
    *    Like many general-purpose libraries OSAL needs to be initialized
    *    before first being used. This is the case as various services
    *    inside the library need to setup their runtime. This may be the
    *    need to starting up threads. Also runtime checks on the
    *    operating environment can be part of this initialization. Or
    *    allocation of global data structures, OS ressources, etc.
    *
    *    Where there is initialization there also needs to be
    *    deinitialization, of course. The latter cleans up any of the
    *    ressources and facilities created during initialization.
    *
    *    This process of initialization and cleanup could in principle be
    *    done via implicit machanisms like definition of static
    *    initializers, shared library startup code or something alike. As
    *    OSAL is intended to be platform-independent any
    *    platform-specific feature to achieve this is hard to use,
    *    because of the resulting configuration management and different
    *    behaviour between platforms.
    *
    *    The simple use of static objects that are defined inside the
    *    OSAL library is also not suitable, because the behaviour of
    *    static initialization is not defined by the C++ standard.
    *    Especially on win32 platforms strange behaviour can result
    *    during deinitialization when using system calls. Also the order
    *    of static initialization is not well-defined.
    *
    *    Another solution would have been to do all initialization needs
    *    on-the-fly at the time the client requires certain
    *    functionality. This has a number of drawbacks, however:
    *
    *    - If an OSAL facility is not working correctly then it will only
    *    be detected at a stage in the program when the facility is
    *    actually accessed
    *
    *    - The runtime behaviour will loose predictability when the time
    *    and order of initialization is dynamic
    *
    *    - There might a a runtime performance penalty as individual code
    *    sections need to repeatedly check if initialization has already
    *    been done or not
    *
    *    On the downside the approach of explicit initialization and
    *    cleanup can decrease startup times (as everything needs to be
    *    setup in advance before being able to continue with application
    *    logic) and increase ressource consumption (as everything is
    *    initialized regardless of whether it is required by the
    *    application)
    *
    *     Therefore OSAL requires you to setup this initialization object.
    *     But the object can be configured to either realize lazy startup
    *     or bulk startup. This way both behaviours can be realized.
    **/
    class OSAL_EXPORT Osal
    {
    public: // types
        //! global OSAL errors that aren't SysErrors
        enum OsalErrors
        {
            INIT_ERROR
        };

        //! the one and only OSAL error
        static ipl::ErrorType Error;

        /**
        * \brief
        * Contains basic system information inquired during Osal
        * initialization
        **/
        struct SystemInfo
        {
            SystemInfo();

            //! returns the pagesize of the running system
            inline size_t getPagesize() const;

            //! returns the number of CPUs in the running system
            inline size_t getNumCPUs() const;

            const SystemInfoHandle& getHandle() const
            { return m_handle; }
        private:
            SystemInfoHandle m_handle;
        };

    public: // functions
        /**
        * \brief
        *     Constructor performs OSAL initialization
        * \param[in] lazy
        *     If set to \c true then ressources will be allocated and
        *     setup up on an as needed basis, where appropriate. E.g.
        *     if you never setup a ProcessTNG object then the
        *     associated ressources will never be setup. This may
        *     improve startup performance, however it may also
        *     introduce unexpected delays as ressources need to be
        *     setup as soon as the first user of a certain facility
        *     appears. It's thus less deterministic.
        * \param[in] shutdown_handler_enabled
        *     enable_shutdown_handler If set to \c true then you will
        *     be able to deal with shutdown requests sent from the
        *     system to the current process.
        *
        *     To register an actual shutdown handler please refer to
        *     registerShutdownHandler(IShutdownHandler*)
        **/
        Osal(const bool lazy = true,
            const bool shutdown_handler_enabled = false);

        inline ~Osal();

        /**
        * \brief
        *     Returns the SystemInfo for the current system
        **/
        static SystemInfo getSystemInfo()
        { return s_sys_info; }

        /**
         * \brief
         *     Assigns the framework config directory default.
         *     Returns the value of the framework config directory default from before
         *     the assignment.
         *     The initial value after construction is the empty string.
         *     Must be called before the Util constructor to have any effect.
         **/
        ipl::string setDefaultConfigDir(const ipl::string& path);


    protected: // functions
        //! performs cleanup of all OSAL components
        void cleanupAll();


        // allows the Console to initialize its services
        friend class Console;

        /**
        * \brief
        *    initializes basic platform-dependent stuff before
        *    anything else is initialized
        **/
        bool preInit();

        /**
        * \brief
        *    Initializes platform-dependent stuff after after
        *    everything else has been initialized
        **/
        bool postInit();

    private:
        //! if initialization was successful
        static bool s_initialized;

        //! Whether OSAL was ever initialized
        static bool s_ever_initialized;

        //! number of initializations currently done
        static osal::AtomicCounter s_init_count;

        //! basic system-wide information
        static SystemInfo s_sys_info;

        //! whether lazy initialization was requested
        const bool m_lazy;

        friend class Thread;
        static osal::sched::Attr s_osal_ctor_sched_attrs;

    };

    /**
    * \brief
    *    count the number of characters in the provided string.

    *    this safe type of strlen from ANSI C is unfortunately not
    *    standardised. Thus we have to abstract it.
    * \note
    *    this function counts the numbers of characters in str until the
    *    null character is hit. If the first max_length characters don't
    *    contain a null character then max_length is returned.
    * \param
    *    str which number of characters should be counted.
    * \param max_length
    *    maximum number of characters to count.
    * \return
    *    number of characters found in str or max_length.
    * \deprecated since 2018-11-16:
    *     This function is deprecated. Replacements functions for strnlen
    *     are now provided elsewhere.
    **/
    IPL_DEPRECATED ( "use other function",
    OSAL_EXPORT uint32_t strnlen(
        const char* const str,
        const uint32_t max_length)
    )  /* end IPL_DEPRECATED */
    ;

    /**
    * \see
    *    strnlen
    * \note
    *    wide character variant of strnlen
    * \deprecated since 2018-11-16:
    *     This function is deprecated. Replacements functions for wcsnlen
    *     are now provided elsewhere.
    **/
    IPL_DEPRECATED ( "use other function",
    OSAL_EXPORT uint32_t wcsnlen(
        const wchar_t* const str,
        const uint32_t max_length)
    )  /* end IPL_DEPRECATED */
    ;

    OSAL_EXPORT void getMainFwArgs(int* argc, char*** argv);
}  // end of namespace osal

#if (defined IPL_OS_POSIX) || (defined IPL_OS_INTEGRITY)
#    include "posix/osal.inl"
#elif defined (IPL_OS_WINPC)
#    include "win32/osal.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
