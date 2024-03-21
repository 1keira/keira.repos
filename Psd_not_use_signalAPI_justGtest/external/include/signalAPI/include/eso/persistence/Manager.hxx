/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_MANANGER_HXX
#define PERSISTENCE_MANANGER_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <common/types/vector.hxx>
#include <osal/osal.hxx>
#include <util/util.hxx>
#include <util/config/Provider.hxx>
#include <comm/AgentStarter.hxx>
#include <persistence/Core.hxx>
#include <persistence/EngineSwitch.hxx>

// TODO: proper filename (Manager? application?)

/*****************************************************************************/

namespace persistence {
    namespace application {

/*****************************************************************************/

        class ConnectionListener {
            
        public:
            //! \brief Just to keep the compiler happy...
            virtual ~ConnectionListener() IPL_NOEXCEPT;
            //! \brief Report that a new client has connected to the frontend
            virtual void clientConnected() IPL_NOEXCEPT;
            //! \brief Report that a client has disconnected to the frontend
            virtual void clientDisconnected() IPL_NOEXCEPT;
        };

/*****************************************************************************/

        class Manager: public ConnectionListener {

        public:
            Manager(const ipl::string &name) IPL_NOEXCEPT;

            /*!
                \brief    start the business. It returns after the complete business was done
                \return
                true on error, false on success
                \todo What's "the complete business"?
                \todo rename to run?
            */
            virtual bool start() IPL_NOEXCEPT=0;

            Core &getCore() IPL_NOEXCEPT { return m_core; }

            Engine &getEngine() IPL_NOEXCEPT { return m_engine_switch;}
            void loadEngineConfig() IPL_NOEXCEPT {
                m_engine_switch_config.load(m_core, config);
                m_engine_switch.setDefaultEngine (m_engine_switch_config);
            }
            void addEngineType(const ipl::string &name, Engine::Factory *factory) IPL_NOEXCEPT {
                m_engine_switch_config.sign_on(factory, name);
            }
            void removeEngineType(Engine::Factory *factory) IPL_NOEXCEPT {
                m_engine_switch_config.sign_off(factory);
            }

            unsigned flushPersistence() IPL_NOEXCEPT { return m_engine_switch.flushAll(m_core); }

            virtual void clientConnected() IPL_NOEXCEPT;
            virtual void clientDisconnected() IPL_NOEXCEPT;

            const util::config::Provider config;  // part of the interface, hence public and without m_

        protected:
            // TODO: semantics???
            bool startup() IPL_NOEXCEPT;
            void teardown() IPL_NOEXCEPT;

            ipl::string  m_name;
            Core::Config m_core_config;
            Core         m_core;
            persistence::EngineSwitch::Config m_engine_switch_config;
            persistence::EngineSwitch         m_engine_switch;

            volatile int16_t m_connected_clients;
            osal::Mutex      m_mutex;
            osal::Condition  m_condition;
        };

/*****************************************************************************/

    }  // end of namespace application
}  // end of namespace persistence

/*****************************************************************************/
#endif
