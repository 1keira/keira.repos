/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_IPERSISTENCEB_SERVICE_HXX_
#define PERSISTENCE_IPERSISTENCEB_SERVICE_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/IPersistenceBS.hxx>
#include <persistence/EventQueue.hxx>
#include <persistence/Core.hxx>
#include <persistence/Manager.hxx>

#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <comm/SingleThreadedActiveObjectFactory.hxx>
#include <comm/Lifecycle.hxx>

/*****************************************************************************/

IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_SERVICE_IPERSISTENCEB);

/*****************************************************************************/

namespace persistence {
    class PersistenceService;
}

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class IPersistenceBService: public IPersistenceBS, public comm::LifecycleListener {

    public:
        
        struct Config;
        
        IPersistenceBService(Core &core, application::ConnectionListener &manager,
                             PersistenceService &service,
                             const Config &config) IPL_NOEXCEPT;
        //! \brief Convenience c'tor calling setup() for you
        IPersistenceBService(comm::ActiveObjectFactoryPtr aoFactory,
                             Core &core, application::ConnectionListener &manager,
                             PersistenceService &service,
                             const Config &config) IPL_NOEXCEPT:
            IPersistenceBService(core, manager, service, config) {
            setup(aoFactory);
        }
        ~IPersistenceBService() IPL_NOEXCEPT override {
            teardown();
        }

        /*!
            \brief Setup the service-implementation, register the interface
            \return    true on error, false on success
        */
        bool setup(const comm::ActiveObjectFactoryPtr &aofactory) IPL_NOEXCEPT;

        /*!
        \brief
            teardown the service-implementation
            - unregister the interface
        */
        void teardown() IPL_NOEXCEPT;

        uint32_t instanceid() IPL_NOEXCEPT;
        virtual void alive(comm::Lifecycle *lifecycle, const comm::ServiceEvent &event) IPL_NOEXCEPT;
        virtual void dead(comm::Lifecycle *lifecycle, const comm::ServiceEvent &event) IPL_NOEXCEPT;


        /* connection tracking ***********************************************/
        virtual void clientConnected(uint32_t count,
                                     IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void clientDisconnected(uint32_t count,
                                        IPersistenceBProxyReply &reply) IPL_NOEXCEPT;

        /* IPersistenceBS ****************************************************/
        virtual void open(const CIPtr<CIString> &name,
                          const CIPtr<CIString> &version,
                          IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void close(const CIPtr<PartitionHandle> &handle,
                           IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void version(const CIPtr<CIString> &name,
                             IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void purge(const CIPtr<CIString> &name,
                           IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void flush(const CIPtr<persistence::PartitionHandle> &handle,
                           IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void remove(const CIPtr<PartitionHandle> &partition,
                            const CIPtr<CIString>& key, IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void exists(const CIPtr<PartitionHandle> &partition,
                            const CIPtr<CIString>& key, IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void setBlob(const CIPtr<PartitionHandle> &partition,
                             const CIPtr<CIString>& key, const CIPtr<CIUInt8Array> &val,
                             IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void getBlob(const CIPtr<PartitionHandle> &partition,
                             const CIPtr<CIString>& key, const int32_t timeout,
                             IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void getBlob(const CIPtr<PartitionHandle> &partition,
                             const CIPtr<CIString>& key,
                             IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void getAllKeys(const CIPtr<PartitionHandle> &handle,
                                IPersistenceBProxyReply &reply) IPL_NOEXCEPT;
        virtual void removeAll( const CIPtr< persistence::PartitionHandle >& handle,
                                IPersistenceBProxyReply& reply ) IPL_NOEXCEPT;
    private:
        osal::Mutex                      m_mutex;
        osal::Condition                  m_condition;
        uint32_t                         m_instanceId;
        Core                            &m_core;
        application::ConnectionListener &m_manager;
        PersistenceService              &m_service;

        bool m_is_setup;
    };

/*****************************************************************************/

    struct IPersistenceBService::Config {

        // part of the interface, hence without m_
        int32_t instanceId;

        Config() IPL_NOEXCEPT: instanceId(1) {}
        Config(int32_t instanceId) IPL_NOEXCEPT: instanceId(instanceId) {}
        Config(const util::config::Value &config_root) IPL_NOEXCEPT: Config() {
            load(config_root);
        }

        void load(const util::config::Value &config_root) IPL_NOEXCEPT;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
