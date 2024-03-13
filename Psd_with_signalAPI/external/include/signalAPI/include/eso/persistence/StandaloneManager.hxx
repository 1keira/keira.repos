/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_STANDALONE_MANANGER_HXX_
#define PERSISTENCE_STANDALONE_MANANGER_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <common/types/vector.hxx>
#include <osal/osal.hxx>
#include <util/util.hxx>
#include <util/config/Provider.hxx>
#include <comm/AgentStarter.hxx>
#include <persistence/Core.hxx>
#include <persistence/EngineSwitch.hxx>
#include <persistence/Manager.hxx>

/*****************************************************************************/


namespace persistence {
    namespace application {


/*****************************************************************************/

    /*!
        \brief    Manager which runs standalone without service manager connection
    */
    class StandaloneManager: public Manager {
    public:
        StandaloneManager(const ipl::string &procname) IPL_NOEXCEPT:
            Manager(procname), m_agent(procname, "local")
        {
            // Nope, crashes, m_engine is not properly initialized, godammit!
            //m_engine_switch.fs_access(Engine::FS_READ_WRITE);
        }

        virtual bool start() IPL_NOEXCEPT;

        static osal::Osal*    m_osal;
        static util::Util*     m_util;
    private:
        StandaloneManager();
        comm::AgentStarter  m_agent;
    };

/*****************************************************************************/

    }  // end of namespace application
}  // end of namespace persistence

/*****************************************************************************/
#endif
