/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_ATTRIBUTES_HXX
#define COMM_ATTRIBUTES_HXX

// eso framework header files
#include <map>
#include <vector>
#include <cstdint>

#include <common/UUID.hxx>
#include <threadsafe/Mutex.hxx>
#include <comm/commidltypes.hxx>
#include <comm/Proxy.hxx>
#include <comm/comm_dso.h>

namespace comm {

/*!
    \brief
        base class for IDL based COMM services implementing attributes

        it contains
        - the notification matrix which manages a collection of reply-proxies to clients
          that have subscribed (called setNotification()) to an attribute..
        - the mechanism to detect that a connection to the interface has closed. In this
          case the notifications for this reply proxy can be removed
*/
class COMM_EXPORT AttributeNotificationContainer {


public:
    /*!
    \brief constructor

    \param[in] reply_uuid
        is the UUID of the related reply interface
    */
    explicit AttributeNotificationContainer(const ipl::UUID reply_uuid)
    : m_reply_tracker(*this, reply_uuid)
    {}

    /*!
    \brief
        check whether there is someone notified on the attribute with the given id

    \param[in] attr_id
        id of the attribute the information is requested for

    \param[out] proxies
        list of all reply proxies, where a notification for the given id is available. This
        vector is filled by the method. It's cleared in before

    \return
        true if one or more clients are notified on the attribute, otherwise false
    */
    bool getNotifiedProxies(const uint32_t attr_id, ipl::vector<comm::Proxy>& proxies);

    /*!
      Applies callable OP to every reply proxy for which a client has subscribed
      (called setNotification()) to attribute \p attr_id.
      OP is called with const comm::Proxy&.

      While apply runs a lock for the AttributeNotificationContainer is held.
      Processing of new clients that called setNotification() will thus be
      blocked while apply() runs.
    */
    template <typename OP>
    void apply (uint32_t attr_id, OP op) {
        threadsafe::Mutex::Guard g (m_mtx);
        auto it = m_subscriptions.find(attr_id);
        if ( it != m_subscriptions.end() ) {
            for (const comm::Proxy& p: it->second ) {
                op(p);
            }
        }
    }

    /*!
    \brief
        add the notification for the given attribute to the notification matrix
    \param[in] attr_id
        id of the attribute a notificaiton shall be added
    \param[in] proxy
        the proxy the notification shall be added

        if an entry for the given proxy already exists, the id is added to the existing
        ids, otherwise a new entry for the proxy is created ẃith the id as first element
    */
    void addNotification (comm::Proxy& proxy, const uint32_t attr_id);

    /*!
    \brief
        remove all notifications for the given proxy
    \param[in] proxy
        the proxy the notification shall be removed
    */
    void removeNotification (const comm::Proxy& proxy);

    /*!
    \brief
        remove the notifications for the given attribute
    \param[in] attr_id
        id of the attribute a notificaiton shall be remove
    \param[in] proxy
        the proxy the notification shall be removed
    */
    void removeNotification (const comm::Proxy& proxy, uint32_t attr_id);

    /*!
    \brief
        remove all notifications for the given proxy
    \param[in] instance_id
        the instance_id of the related proxy
    */
    void removeNotification (const comm::InstanceID& instance_id);

private:
    /*!
        \brief
        interface tracker for the reply-interfaces of the service IDL.

        It's used to detect the disconnection of a client. In this case the notification entry for
        this client can be removed
    */
    class ReplyInterfaceTracker  : public comm::LifecycleListener {
    public:
        ReplyInterfaceTracker(AttributeNotificationContainer& parent, const ipl::UUID& reply_uuid);
        ~ReplyInterfaceTracker();
    private:
        //! the interface went alive -> not used
        void alive( comm::Lifecycle* l, const comm::ServiceEvent& e) override {
            // this tracker only reacts to clients going away; this alive
            // is intentionally empty.
        }
        //! the interface went dead -> notifications can be removed
        void dead( comm::Lifecycle* l, const comm::ServiceEvent& e) override;

        AttributeNotificationContainer& m_parent;
        //! related UUID to the reply interface
        const ipl::UUID                 m_reply_uuid;
    };

    //! mutex to guard access to m_subscriptions
    threadsafe::Mutex                   m_mtx;

    using NotificationMap = std::map<uint32_t, std::vector<comm::Proxy> >;
    NotificationMap                     m_subscriptions;

    //! the tracker for detection of lost connections
    ReplyInterfaceTracker               m_reply_tracker;

};

} // namespace comm

#endif
