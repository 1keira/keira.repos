/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_PROXYSTUBFACTORY_HXX
#define COMM_PROXYSTUBFACTORY_HXX

#include <common/UUID.hxx>

#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>

#include <memory>
#include <new>

namespace comm {
    class StubBase;
    struct ProxyState;
    struct Session;
    class Connection;
    using ConnectionPtr = std::shared_ptr<Connection>;
}

    /** \brief The proxy factory for a given interface.
        \internal
    */

    template <typename T> class ProxyFactory {
        public:
            /* create a Proxy */
            static T* create(comm::Session& session) {
#if defined (__GNUC__) && defined (COMM_FACTORY_DEBUG)
                creationCount++;
#endif
                return new (std::nothrow) T(session);
            }
            static void destroy(T* t) {
#if defined (__GNUC__) && defined (COMM_FACTORY_DEBUG)
                creationCount--;
#endif
                delete t;
            }
#if defined (__GNUC__) && defined (COMM_FACTORY_DEBUG)
            static unsigned creationCount;
#endif
    };

    /** \brief The stub factory for a given interface.
        \internal
    */
    template <typename T> class StubFactory {
        public:
            /* create a stub (with reply instance id)*/
            static comm::StubBase* create( const comm::ConnectionPtr& conn, const comm::InstanceID& replyid
                                            ,const comm::InstanceID& iid
                                            ,const comm::ProxyStubID& psid) {
                return new (std::nothrow) T(conn, replyid, iid, psid);
            }
            /* create a stub (without  reply instance id)*/
            static comm::StubBase* create2( const comm::ConnectionPtr& conn, const comm::InstanceID&
                                            ,const comm::InstanceID& iid
                                            ,const comm::ProxyStubID& psid) {
                return new (std::nothrow) T(conn, iid, psid);
            }
            static void destroy(comm::StubBase* s) {
                delete (T*)s;
            }
    };

// factory functions for a Proxy/Stub
typedef void* (*ProxyCreator) (comm::Session&);
typedef void (*ProxyDeleter) (void*);

typedef comm::StubBase* (*StubCreator) (const comm::ConnectionPtr& conn, const comm::InstanceID& replyid
                ,const comm::InstanceID& iid, const comm::ProxyStubID& psid);
typedef void (*StubDeleter) (comm::StubBase*);

/**
    \brief Per comm interface data for creating proxies and stubs
    \internal
*/
struct ProxyStubFactory {
    comm::InterfaceID       interfaceID;    // interface id
    const char* module_version;             // version of the module
    const char* interface_version;          // version of the interface
    const char* interface_name;             // name of the interface
    ipl::UUID   interface_key;              // version 5 uuid of the interface (hash for verification)
    /** \brief Proxy/stub creator functions
        \internal
    */
    struct Factories {
        comm::Distance          type;           // the Distance we can create proxies and stubs for
        ProxyCreator            createProxy;    // proxy creator/deleter for the interface
        ProxyDeleter            deleteProxy;
        StubCreator             createStub;     // stub creator/deleter for the interface
        StubDeleter             deleteStub;
    };
    Factories   ciptrFactories [(unsigned)comm::Distance::LastDistance+1];
    Factories   cstyleFactories[(unsigned)comm::Distance::LastDistance+1];
    Factories   cppstyleFactories[(unsigned)comm::Distance::LastDistance+1];

    void*                       CIPtrUnbornProxy;
    void*                       CIPtrDeadProxy;
    void*                       CStyleUnbornProxy;
    void*                       CStyleDeadProxy;
    void*                       CppStyleUnbornProxy;
    void*                       CppStyleDeadProxy;
};

//! function type for retreiving a ProxyStubFactory
typedef const ProxyStubFactory* (*FactoryGetterFct)();

extern "C" {
    typedef ProxyStubFactory* (*FactoryFct) (int* count);
    COMM_EXPORT ProxyStubFactory* getFactory (int* count);
}

#endif // COMM_PROXYSTUBFACTORY_HXX

