#ifndef SERVMNGT_HXX
#define SERVMNGT_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Martin Stein
*/

#include <ipl_config.h>
#include <servmngt/Application.hxx>
#include <servmngt/servmngt_dso.h>

namespace servmngt{

    /**
        \brief Initialize the service management framework. 

        This function must be called in the main function of each process that 
        uses the service management library. In particular it must be called in 
        the main function of a single application process. If it is not called, 
        service management functions will fail and abort.

        You <b>must not</b> call this function in a method or the constructor of
        an application derived from the class Application, when you plan to add
        the application to a bundle, because in this case the bundle loader of
        the process will initialize the framework.
        
        This call create an osal and an util instance and also a
        comm::AgentStarter
        
        \param[in]    argc is the unchanged argc parameter from  main
        \param[in]    argv is the unchanged argv parameter from  main
        \return    
            true on error, false on success. In case of failure, an error is raised
    **/
    SERVMNGT_EXPORT bool init(int argc, const char** argv) IPL_NOEXCEPT;

    /**
        \brief Initialize the service management framework. 
        
        like void init(int argc, const char** argv) but
        - the processname has to be given
        - osal, util and agentstarter may be create outside

        \param[in]    process_name
            is the name of the process as configured in the framework.json
        \param[in]    init_osal_util
            tells, whether an osal and an util instance shall be created (value=true) or not (value=false)
        \param[in]    setup_comm
            tells, whether a comm::AgentStarter shall be created (value=true) or not (value=false)
        \return    
            true on error, false on success. In case of failure, an error is raised
    **/
    SERVMNGT_EXPORT bool init(const char* process_name, bool init_osal_util, bool setup_comm) IPL_NOEXCEPT;

    /*!
        \brief    cleanup everything done in init()
                It need not to be called by the user-applications
    */
    SERVMNGT_EXPORT void dispose() IPL_NOEXCEPT;


    /**
        \brief Register an application in a single application process.

        This function registers an application at the bundle loader and gives the
        control to the framework library. The function does not return until either 
        service the management unloads the application or a fatal error occurred.

        This function makes the application visible to the service management, so that
        the service management can initialize and run the application. However, this
        does not happen by default. The application is only initialized/run when the
        service management encounters a trigger to start the application (e.g. a 
        corresponding command in the configuration of the static startup).

        Note that the function needs the unmodified command line parameters of the 
        process, because the service management uses command line parameters as 
        initial input to the bundle loader, which is embedded in every service 
        management process. Therefore it is not possible to use user defined command
        line parameters in single application processes.

        \param argc The argc of the main function.
        \param argv The argv of the main function.
        \param app A pointer to the servmngt::IApplicationInit interface, which 
            initializes your application.
        \param name The name of the application. This must be exactly the same
            name as used in the system configuration.

        \return false if the application exits regularly, true if an error occurred.
    **/
    SERVMNGT_EXPORT bool startApp(int argc, const char** argv, Application* app, const ipl::string& name) IPL_NOEXCEPT;

    //! retrieve the processname given via the commandline
    SERVMNGT_EXPORT ipl::string getProcessName() IPL_NOEXCEPT;

    //! retrieve the process id given via the commandline
    SERVMNGT_EXPORT uint32_t getProcessID() IPL_NOEXCEPT;

    //! retrieve the number of restarts given by the commandline
    SERVMNGT_EXPORT uint32_t getNumberRestarts() IPL_NOEXCEPT;

    //! retrieve the arguments from the commandline which are not related to the servicemanage trigger startup
    SERVMNGT_EXPORT ipl::vector<ipl::string> getUserArguments() IPL_NOEXCEPT;

    //! retrieve the information whether the commandline is valid or not
    SERVMNGT_EXPORT bool commandlineValid() IPL_NOEXCEPT;
    
    /*!
     \brief
     parse the commandline paramater and check
     whether they belong to a startup done by the
     servicemanager

    \return false in case of not-started by the servicemanager otherwise true
    */
    SERVMNGT_EXPORT bool checkCommandline(int argc, const char** argv) IPL_NOEXCEPT;
}


// have to put the doxygen comment for servmngt namespace somewhere...
/**
    \namespace servmngt
    \brief The service management namespace.
**/

#endif

