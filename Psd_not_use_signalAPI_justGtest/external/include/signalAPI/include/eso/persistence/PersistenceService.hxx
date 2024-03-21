/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_PERSISTENCESERVICE_HXX
#define PERSISTENCE_PERSISTENCESERVICE_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/Engine.hxx>
#include <persistence/Manager.hxx>  // TODO
#include <persistence/IPersistenceAService.hxx>
#include <persistence/IPersistenceBService.hxx>
#include <util/SharedPtr.hxx>

/*****************************************************************************/

namespace persistence {
    class Engine;

    namespace IPersistenceA {
        class SubscriptionAnchorJob;
    }
}

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    /*!
        \brief Module implementing an IPersistenceA interface and its logic
    */
    class PersistenceService {

    public:

        typedef uint32_t Index;  // TODO: --> Service?

        class Client;

        PersistenceService(Engine &engine,
                           Core &core) IPL_NOEXCEPT;

        //! \brief Convenient abstraction of PartitionHandle interna
        static CIPtr<PartitionHandle> createPartitionHandle(Index index) IPL_NOEXCEPT {
            CIPtr<PartitionHandle> handle=
                CIFactory<PartitionHandle>::createObject();
            handle->index=index;
            return handle;
        }

        //! \brief Convenient abstraction of PartitionHandle interna
        static CIPtr<PartitionHandle> invalidHandle() IPL_NOEXCEPT {
            static CIPtr<PartitionHandle> handle=
                CIFactory<PartitionHandle>::createObject();
            handle->index=(uint32_t)-1;
            return handle;
        }

        //! \brief Convenient abstraction of PartitionHandle interna
        static bool invalid(Index index) IPL_NOEXCEPT {
            return index==(uint32_t)-1;
        }
        //! \brief Convenient abstraction of PartitionHandle interna
        static bool invalid(const PartitionHandle &handle) IPL_NOEXCEPT {
            return invalid(handle.index);
        }
        //! \brief Convenient abstraction of PartitionHandle interna
        static bool invalid(const CIPtr<PartitionHandle> &handle) IPL_NOEXCEPT {
            return invalid(*handle);
        }

        Engine &engine;  // Part of the interface, thus public and without m_

        //! \brief Get access to Client structure
        util::SharedPtr<Client> client(const comm::InstanceID &instance) IPL_NOEXCEPT {
            return m_clients[instance];
        }
        //! \brief Discard Client structure
        void removeClient(const comm::InstanceID &instance) IPL_NOEXCEPT {
            m_clients.erase(instance);
        }
        //! \brief add Client structure
        void addClient(const comm::InstanceID &instance, Client* client) IPL_NOEXCEPT {
            util::SharedPtr<Client>c (client);
            m_clients[instance] = c;
        }
        
    protected:

        typedef ipl::map<comm::InstanceID, util::SharedPtr<Client> > Clients;
        Clients m_clients;
    };


/*****************************************************************************/

    /*!
        \brief One IPersistenceA client's worth of information
    */
    class PersistenceService::Client {

    public:

        struct Partition;

        Client() IPL_NOEXCEPT {}

        Partition *add(util::SharedPtr<Engine::Partition> partition,
                       const Engine::Name &name) IPL_NOEXCEPT;
        bool erase(Index index) IPL_NOEXCEPT;
        util::SharedPtr<Partition> partition(Index index) const IPL_NOEXCEPT;

    protected:

        typedef ipl::vector<util::SharedPtr<Partition> > Partitions;
        Partitions m_partitions;
    };


/*****************************************************************************/

    /*!
        \brief Per-partition information for one client
    */
    struct PersistenceService::Client::Partition {

        util::SharedPtr<Engine::Partition> partition;  // TODO: SharedPtr, sharedFromThis()
        Index index;
        Engine::Name name;
        IPersistenceA::SubscriptionAnchorJob *anchor;
        unsigned hold_count;

        Partition(const util::SharedPtr<Engine::Partition> &partition,
                  Index index, const Engine::Name &name) IPL_NOEXCEPT:
            partition(partition), index(index), name(name), anchor(NULL),
            hold_count(0) {}
        ~Partition() IPL_NOEXCEPT;

        //! \brief Update subscriptions, arrange for initial notifications
        Core::Seqnum subscribe(Core &core, const ipl::vector<uint32_t> &keys,
                               int timeout, IPersistenceAProxyReply &reply) IPL_NOEXCEPT;
        //! \brief Update subscriptions, possibly clean up
        Core::Seqnum unsubscribe(Core &core, ipl::vector<uint32_t> &keys) IPL_NOEXCEPT;
        //! \brief Update all subscriptions, clean up
        Core::Seqnum unsubscribe(Core &core) IPL_NOEXCEPT;

        //! \brief Make subscription anchor send (initial) update on end()
        void noValue(Engine::Key key, RequestStatus status) IPL_NOEXCEPT;
        //! \brief Make subscription anchor send (initial) update on end()
        void value(Engine::Key key, Engine::Int value) IPL_NOEXCEPT;
        //! \brief Make subscription anchor send (initial) update on end()
        void value(Engine::Key key, const Engine::String &value) IPL_NOEXCEPT;
        //! \brief Make subscription anchor send (initial) update on end()
        void value(Engine::Key key, const Engine::Blob &value) IPL_NOEXCEPT;
        //! \brief Make subscription anchor send (initial) update now
        void end() IPL_NOEXCEPT;

        //! \brief Stop sending updates, queue instead
        void hold_updates() IPL_NOEXCEPT;
        //! \brief Resume sending updates (queued ones first)
        void release_updates() IPL_NOEXCEPT;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
