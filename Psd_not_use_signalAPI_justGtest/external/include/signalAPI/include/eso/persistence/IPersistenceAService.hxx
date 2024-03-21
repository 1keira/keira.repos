/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_IPERSISTENCEA_SERVICE_HXX_
#define PERSISTENCE_IPERSISTENCEA_SERVICE_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/IPersistenceAS.hxx>
#include <persistence/EventQueue.hxx>
#include <persistence/Core.hxx>
#include <persistence/Manager.hxx>

#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <comm/SingleThreadedActiveObjectFactory.hxx>
#include <comm/Lifecycle.hxx>

/*****************************************************************************/

IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_SERVICE_IPERSISTENCEA);

/*****************************************************************************/

namespace persistence {
    class PersistenceService;
}

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class IPersistenceAService: public IPersistenceAS, public comm::LifecycleListener {

    public:
        
        struct Config;
        
        IPersistenceAService(Core &core, application::ConnectionListener &manager,
                             PersistenceService &service,
                             const Config &config) IPL_NOEXCEPT;
        //! \brief Convenience c'tor calling setup() for you
        IPersistenceAService(comm::ActiveObjectFactoryPtr aoFactory,
                             Core &core, application::ConnectionListener &manager,
                             PersistenceService &service,
                             const Config &config) IPL_NOEXCEPT:
            IPersistenceAService(core, manager, service, config) {
            setup(aoFactory);
        }
        ~IPersistenceAService() IPL_NOEXCEPT override {
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
                                     IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void clientDisconnected(uint32_t count,
                                        IPersistenceAProxyReply &reply) IPL_NOEXCEPT;

        /* IPersistenceAS ****************************************************/
        virtual void open(const uint32_t number,
                          const CIPtr<CIString> &version,
                          IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void open(const uint32_t number, const uint32_t profile,
                          const CIPtr<CIString> &version,
                          IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void open(const CIPtr<CIString> &name,
                          const CIPtr<CIString> &version,
                          IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void open(const CIPtr<CIString> &name, const uint32_t profile,
                          const CIPtr<CIString> &version,
                          IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void convert(const uint32_t number,
                             const CIPtr<CIString> &from_version,
                             const CIPtr<CIString> &to_version,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void convert(const uint32_t number, const uint32_t profile,
                             const CIPtr<CIString> &from_version,
                             const CIPtr<CIString> &to_version,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void convert(const CIPtr<CIString> &name,
                             const CIPtr<CIString> &from_version,
                             const CIPtr<CIString> &to_version,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void convert(const CIPtr<CIString> &name, const uint32_t profile,
                             const CIPtr<CIString> &from_version,
                             const CIPtr<CIString> &to_version,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void close(const CIPtr<PartitionHandle> &handle,
                           IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void version(const uint32_t number,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void version(const uint32_t number, const uint32_t profile,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void version(const CIPtr<CIString> &name,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void version(const CIPtr<CIString> &name, const uint32_t profile,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void purge(const uint32_t number,
                           IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void purge(const uint32_t number, const uint32_t profile,
                           IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void purge(const CIPtr<CIString> &name,
                           IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void purge(const CIPtr<CIString> &name, const uint32_t profile,
                           IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void copy(const CIPtr<PartitionHandle> &from_handle,
                          const uint32_t to_number,
                          IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void copy(const CIPtr<PartitionHandle> &from_handle,
                          const uint32_t to_number, const uint32_t to_profile,
                          IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void copy(const CIPtr<PartitionHandle> &from_handle,
                          const CIPtr<CIString> &to_name,
                          IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void copy(const CIPtr<PartitionHandle> &from_handle,
                          const CIPtr<CIString> &to_name, const uint32_t to_profile,
                          IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void beginTransaction(const CIPtr<PartitionHandle> &partition,
                                      IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void endTransaction(const CIPtr<PartitionHandle> &partition,
                                    const bool flush,
                                    IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void endTransaction(const CIPtr<PartitionHandle> &partition,
                                    IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void flush(const CIPtr<persistence::PartitionHandle> &handle,
                           IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void remove(const CIPtr<PartitionHandle> &partition,
                            const uint32_t key, IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void exists(const CIPtr<PartitionHandle> &partition,
                            const uint32_t key, IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void setInt(const CIPtr<PartitionHandle> &partition,
                            const uint32_t key, const uint32_t val,
                            IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getInt(const CIPtr<PartitionHandle> &partition,
                            const uint32_t key, const int32_t timeout,
                            IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getInt(const CIPtr<PartitionHandle> &partition,
                            const uint32_t key, IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getInts(const CIPtr<PartitionHandle> &partition,
                             const CIPtr<CIUInt32Array> &keys,
                             const int32_t timeout,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getInts(const CIPtr<PartitionHandle> &partition,
                             const CIPtr<CIUInt32Array> &keys,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void setString(const CIPtr<PartitionHandle> &partition,
                               const uint32_t key, const CIPtr<CIString> &val,
                               IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getString(const CIPtr<PartitionHandle> &partition,
                               const uint32_t key,
                               IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getString(const CIPtr<PartitionHandle> &partition,
                               const uint32_t key, const int32_t timeout,
                               IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getStrings(const CIPtr<PartitionHandle> &partition,
                                const CIPtr<CIUInt32Array> &keys,
                                const int32_t timeout,
                                IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getStrings(const CIPtr<PartitionHandle> &partition,
                                const CIPtr<CIUInt32Array> &keys,
                                IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void setBlob(const CIPtr<PartitionHandle> &partition,
                             const uint32_t key, const CIPtr<CIUInt8Array> &val,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getBlob(const CIPtr<PartitionHandle> &partition,
                             const uint32_t key, const int32_t timeout,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getBlob(const CIPtr<PartitionHandle> &partition,
                             const uint32_t key,
                             IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getBlobs(const CIPtr<PartitionHandle> &partition,
                              const CIPtr<CIUInt32Array> &keys,
                              const int32_t timeout,
                              IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void getBlobs(const CIPtr<PartitionHandle> &partition,
                              const CIPtr<CIUInt32Array> &keys,
                              IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void subscribe(const CIPtr<PartitionHandle> &partition,
                               const CIPtr<CIUInt32Array> &keys,
                               const int32_t timeout,
                               IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void subscribe(const CIPtr<PartitionHandle> &partition,
                               const CIPtr<CIUInt32Array> &keys,
                               IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void unsubscribe(const CIPtr<PartitionHandle> &partition,
                                 const CIPtr<CIUInt32Array> &keys,
                                 IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        virtual void unsubscribeAll(const CIPtr<PartitionHandle> &partition,
                                    IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
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

    struct IPersistenceAService::Config {

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
