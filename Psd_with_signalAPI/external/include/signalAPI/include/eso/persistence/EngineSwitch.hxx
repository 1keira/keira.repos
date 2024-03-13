/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_ENGINESWITCH_HXX_
#define PERSISTENCE_ENGINESWITCH_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/Engine.hxx>
#include <persistence/tracing.hxx>

/*****************************************************************************/

IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_ENGINE);

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class EngineSwitch: public Engine {

    public:

        struct Config;

        typedef ipl::map<Int,    Engine *> EnginesByInt;
        typedef ipl::map<String, Engine *> EnginesByString;

        EngineSwitch(const Config &config) IPL_NOEXCEPT;

        /* Implementation of base class Engine *******************************/
        virtual Core::Seqnum requestPartition(Core &core,
                                              const Name &partition,
                                              const Version &version) IPL_NOEXCEPT;
        virtual Core::Seqnum requestConversion(Core &core,
                                               const Name &partition,
                                               const Version &from_version,
                                               const Version &to_version) IPL_NOEXCEPT;
        virtual Core::Seqnum purge(Core &core, const Name &partition) IPL_NOEXCEPT;
        virtual Core::Seqnum version(Core &core, const Name &partition) IPL_NOEXCEPT;

        virtual void fs_access(FsAccess access) IPL_NOEXCEPT;
        virtual unsigned flushAll(Core &core) IPL_NOEXCEPT;

        void setDefaultEngine(const Config& config) IPL_NOEXCEPT;

        /*********************************************************************/

    protected:

        typedef ipl::set<Engine *> AllEngines;
        AllEngines allEngines() const IPL_NOEXCEPT;

        Engine *getEngine(const Name &partition) const IPL_NOEXCEPT;

        const EnginesByInt        &m_enginesByInt;
        const EnginesByString     &m_enginesByString;
        Engine                  *m_default_engine;
    };

/*****************************************************************************/

    /*!
        \brief Convenient set of config options needed for a EngineSwitch

        This is separate from EngineSwitch construction to allow
        for maximum flexibility, i.e. you can use EngineSwitch
        with mixed configurations or with no configuration at all.
    */
    struct EngineSwitch::Config {

        Config() IPL_NOEXCEPT: defaultEngine(NULL) {}
        Config(Core &core, const util::config::Value &config_root) IPL_NOEXCEPT:
            defaultEngine(NULL) { load(core, config_root); }

        void sign_on(Engine::Factory *factory, const ipl::string &name) IPL_NOEXCEPT;
        void sign_off(Engine::Factory *factory) IPL_NOEXCEPT;

        EnginesByInt    enginesByInt;
        EnginesByString enginesByString;
        Engine         *defaultEngine;

        bool load(Core &core, const util::config::Value &config_root) IPL_NOEXCEPT;

    protected:
        typedef ipl::map<ipl::string, Engine::Factory *> BackendFactories;

        BackendFactories     m_backend_factories;
        //! all factory created engines
        ipl::vector<Engine *> m_all_engines;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif // PERSISTENCE_ENGINESWITCH_HXX_
