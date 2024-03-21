/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_AGENT_MIB3_HXX
#define COMM_AGENT_MIB3_HXX

#if __cplusplus>=201103L // C+11
#include <cstdint>
#endif
#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>
#include <comm/Proxy.hxx>
#include <comm/ServiceRegistration.hxx>

namespace comm {

    class LifecycleListener;
    class AgentImpl;
    class AgentStarterEventReceiver;
    struct AgentExtraParam;

    struct StateArgs {
        StateArgs(const Proxy::IdentityArgs& iargs
                        ,FactoryGetterFct factory_getter
                        ,InterfaceStyle interfaceStyle
                        ,LifecycleListener* l
                        ,void* service=nullptr)
        : identity(iargs)
        , listener(l)
        , factory_getter(factory_getter)
        , interface_style(interfaceStyle)
        , active_object_factory(nullptr)
        , service(service)
        {
        }

        StateArgs(const Proxy::IdentityArgs& iargs
                        ,FactoryGetterFct factory_getter
                        ,const ActiveObjectFactoryPtr& aof
                        ,InterfaceStyle interfaceStyle
                        ,LifecycleListener* l
                        ,void* service=nullptr)
        : identity(iargs)
        , listener(l)
        , factory_getter(factory_getter)
        , interface_style(interfaceStyle)
        , active_object_factory(aof)
        , service(service)
        {
        }

        StateArgs(const Proxy::IdentityArgs& iargs
                        ,FactoryGetterFct factory_getter
                        ,const ServiceRegistration& replyReg
                        ,InterfaceStyle interfaceStyle
                        ,LifecycleListener* l)
        : identity(iargs)
        , listener(l)
        , factory_getter(factory_getter)
        , interface_style(interfaceStyle)
        , reply_registration(replyReg)
        , active_object_factory(nullptr)
        , service(nullptr)
        {
        }

        const Proxy::IdentityArgs&      identity;
        LifecycleListener*              listener;
        FactoryGetterFct                factory_getter;
        InterfaceStyle                  interface_style;
        ServiceRegistration             reply_registration;
        ActiveObjectFactoryPtr          active_object_factory;
        void*                           service;
    };

    /*!
     \brief comm agent API
    */
    typedef void (*TrackServicesFct)(const comm::InterfaceID& id, comm::LifecycleListener& ll);
    typedef void (*UntrackServicesFct)(const comm::InterfaceID& id, comm::LifecycleListener& ll);
    //XXX move semantik f args?
    typedef Proxy::StatePtr (*InitProxyStateFct)(const StateArgs& args);
    typedef void (*DeinitProxyStateFct)(ProxyState* state);
    typedef ServiceRegistration::StatePtr (*InitServiceStateFct)(const StateArgs& args);
    typedef void (*DeinitServiceStateFct)(ServiceState* state);
    typedef bool (*ConnectProxyFct)(const Proxy& proxy);
    typedef void (*DisconnectProxyFct)(const Proxy& proxy);
    typedef bool (*RegisterServiceFct)(const ServiceRegistration& registration);
    typedef void (*UnregisterServiceFct)(const ServiceRegistration& registration);
    typedef bool (*DisconnectAndNotifyFct)(const Proxy& proxy, ProxyReleasedFct cb, void* ctx);
    typedef void (*UnregisterAndNotifyFct)(const ServiceRegistration& reg, ServiceReleasedFct cb
                                                              ,void* ctx);
    typedef bool (*StartFct)(AgentStarterEventReceiver* cb, bool retry);
    typedef void (*WaitFct)();

    // return nullptr in case of success, an error string otherwise
    COMM_EXPORT const char* initialize(const char* v, comm::AgentID id, const std::string& name
                                        , const comm::AgentExtraParam* );
    COMM_EXPORT const char* deinitialize(void* res);

    struct Agent {
        Agent();
        ~Agent();
        AgentImpl*                      impl;
        AgentID                         agentID;
        StartFct                        start;
        WaitFct                         wait;
        TrackServicesFct                trackServices;
        UntrackServicesFct              untrackServices;
        InitProxyStateFct               initProxyState;
        DeinitProxyStateFct             deinitProxyState;
        ConnectProxyFct                 connectProxy;
        DisconnectProxyFct              disconnectProxy;
        InitServiceStateFct             initServiceState;
        DeinitServiceStateFct           deinitServiceState;
        RegisterServiceFct              registerService;
        UnregisterServiceFct            unregisterService;
        DisconnectAndNotifyFct          disconnectAndNotify;
        UnregisterAndNotifyFct          unregisterAndNotify;

        static COMM_EXPORT Agent& getAgent();
    };

}

#endif // COMM_AGENT_MIB3_HXX
// vim: ts=4 sw=4:
