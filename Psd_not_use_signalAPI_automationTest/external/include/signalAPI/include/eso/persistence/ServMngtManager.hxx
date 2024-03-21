/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_SERVMNGT_MANANGER_HXX_
#define PERSISTENCE_SERVMNGT_MANANGER_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <common/types/vector.hxx>
#include <osal/osal.hxx>
#include <util/util.hxx>
#include <util/config/Provider.hxx>
#include <comm/AgentStarter.hxx>
#include <servmngt/Application.hxx>
#include <persistence/Core.hxx>
#include <persistence/EngineSwitch.hxx>
#include <persistence/Manager.hxx>

/*****************************************************************************/

namespace persistence {
    namespace application {

        class ServMngtApplication;  // defined in ServMngtManager.cxx

    }
}

/*****************************************************************************/

namespace persistence {
    namespace application {

/*****************************************************************************/

        /*!
            \brief Manager which runs under service management
        */
        class ServMngtManager: public Manager {
            
        public:

            class UpdateAccessModeJob;
            
            ServMngtManager(const ipl::string &appname, int argc, char* argv[]) IPL_NOEXCEPT:
                Manager(appname), m_argc(argc), m_argv(argv), m_app(NULL) {}

            virtual bool start() IPL_NOEXCEPT;

            bool stop() IPL_NOEXCEPT { return false;}

            bool initManager() IPL_NOEXCEPT;
            bool activateManager() IPL_NOEXCEPT;
            bool stopManager() IPL_NOEXCEPT;
            void watchdogAliveRequest() IPL_NOEXCEPT;
            void persistenceFlushRequest() IPL_NOEXCEPT;
            void updateAccessMode() IPL_NOEXCEPT;

            void fs_access(Engine::FsAccess access) IPL_NOEXCEPT;

        private:
            int m_argc;
            char **m_argv;
            ServMngtApplication* m_app;
        };

/*****************************************************************************/

        class ServMngtManager::UpdateAccessModeJob: public Job {
        public:
            UpdateAccessModeJob(Core &core, ServMngtApplication &application) IPL_NOEXCEPT:
                Job(core, "updateAccessMode()"), m_application(application) {}

            // no JobType needed, as there are no events

            virtual void *cast(const JobType &type) IPL_NOEXCEPT;
            virtual bool abort() IPL_NOEXCEPT;
            virtual void start() IPL_NOEXCEPT;
            
        protected:
            ServMngtApplication &m_application;
        };
        
/*****************************************************************************/

    }  // end of namespace application
}  // end of namespace persistence

/*****************************************************************************/
#endif
