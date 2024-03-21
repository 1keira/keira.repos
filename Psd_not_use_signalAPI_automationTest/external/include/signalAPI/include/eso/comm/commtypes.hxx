/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef COMM_COMMTYPES_HXX
#define COMM_COMMTYPES_HXX

#include <stdio.h>

#include <common/UUID.hxx>

#include <common/streams/ostream.hxx>
#include <comm/comm_dso.h>
#include <comm/CallContext.hxx>
#include <comm/ICallPayload.hxx>

namespace util {
    namespace transport {
        class Readable;
    }
}

namespace comm {

    /*! A type that identifies an interface uniquely, supports operator \< */
    typedef ipl::UUID     InterfaceID;

    /*! The interface key is a version 5 uuid and supports operator \< */
    typedef ipl::UUID    InterfaceKey;

    /*! Marker value for the handle in an instance id
         When this value is set in the handle at service registration, the handle will be replaced by a dynamically
        genereated one by the agent.
        All reply service instance handles have this set.
    */
    const uint32_t GENERATE_HANDLE = 0x80000000;
    /*! comm private handle value */
    const uint32_t ANY_HANDLE = 0xffffffff;

    // max length of the strings ":0xffffffff"/":4294967295" (uint32_t max) + trailing \0
    const short HANDLE_STR_LEN = 12;

    /*! \brief A type that identifies an instance of an interface uniquely within the system.
     *
        This identification is done via an InterfaceID and an additional unsigned 32bit handle value as identifier.
        The permitted value range for the handle is 0-0x7fffffff.
        All handle values with the most significant bit set to 1 (0x80000000-0xffffffff) are reserved in COMM.
        There is on excpetion to that rule: If a service is registered with the handle value 0x80000000 (See the constant comm::GENERAT_HANDLE)
        the registration has has the added semantics 'have comm generate a unique handle value for me'.
        The handle value of GENERATE_HANDLE is the replaced with a unique value when the service is registered.
    */
    struct InstanceID {
        /*! Default Constructor, set everything to zero, which is an invalid instanceID*/
        InstanceID(): m_handle(0) {}

        /*! Constructor with concrete InterfaceID and instance-number */
        InstanceID( const InterfaceID& _intID, uint32_t _instCt=0 )
        : m_interface(_intID), m_handle(_instCt) {}

        /*! Copy-Constructor */
        InstanceID( const InstanceID& rhs )
        : m_interface(rhs.m_interface), m_handle(rhs.m_handle)
        {}

        /*! Assignment Operator */
        InstanceID& operator=(    const InstanceID& rhs ) {
            if ( this == &rhs )
                return *this;
            m_interface = rhs.m_interface;
            m_handle = rhs.m_handle;
            return *this;
        }

        ~InstanceID() = default;
        InstanceID( InstanceID&& ) = default;
        InstanceID& operator=(InstanceID&&) = default;

        /*! operator equals to */
        bool operator==( const InstanceID& rhs ) const {
            if ( &rhs == this ) {
                return true;
            }
            return (m_interface == rhs.m_interface) && (m_handle == rhs.m_handle);
        }

        /*! operator not equal to */
        bool operator!=( const InstanceID& rhs ) const {
            return !operator==(rhs);
        }

        /*! check whether the instance is invalid (return true) or not (return false) */
        bool isInvalid() const { return m_interface.isNull(); }

        /*! return the interfaceID part of this instanceID */
        const InterfaceID&     getInterfaceID() const    {return m_interface;}

        /*! return the additional part of this instanceID */
        uint32_t                getHandle() const        {return m_handle;}

        /*! answers if the handle value is the marker value for generating a handle value */
        bool isHandleMarked() const                        { return m_handle == GENERATE_HANDLE; }

        /*! answers if the handle value is in the dynamically generated value range */
        bool isHandleGenerated() const                     { return m_handle & GENERATE_HANDLE; }

        /*! returns a human readable representation */
        COMM_EXPORT operator ipl::string () const;

        ipl::string str() const {
            return (ipl::string)(*this);
        }

        bool operator<(const InstanceID &other) const {
            if( m_interface != other.m_interface) return  m_interface < other.m_interface;
            return m_handle < other.m_handle;
        }

        /*! the interfaceID */
        InterfaceID        m_interface;

        /*! the additional identifier */
        typedef uint32_t Handle_t;
        Handle_t            m_handle;
    };

    COMM_EXPORT ipl::ostream& operator<<(ipl::ostream& stream, const comm::InstanceID& iid);

    /** \brief Sort functor for InstanceID. */
    class  InstanceIDSort {
        public:
            bool operator() (const InstanceID& i1, const InstanceID& i2) const {
                if ( i1 == i2 )
                    return false;
                return (i1.m_interface<i2.m_interface)
                    || ((i1.m_interface==i2.m_interface)&& (i1.m_handle<i2.m_handle));
            }
    };

    /*! define to create an instanceID object out of a uuid + the additional identifier */
    #define IPL_INSTANCEID(iid, handle) comm::InstanceID(comm::InterfaceID(ipl::string(iid)), handle)

    /*! \brief Sort functor for InterfaceID. */
    class InterfaceIDSort {
        public:
        bool operator() (const InterfaceID& a1, const InterfaceID& a2) const {
            return (a1<a2);
        }
    };


    /*! byte order */
    enum ByteOrder {
                    /*! value for unknown endianness */
                    ENDIAN_UNKNOWN
                    /*! value for little-endianness */
                    ,ENDIAN_LITTLE
                    /*! value for big-endianness */
                    ,ENDIAN_BIG
                    /*! value for don't care (leave as is) */
                    ,ENDIAN_NATIVE
                    };

    static const ByteOrder HOST_BYTE_ORDER =
#if defined(IPL_FW_LITTLE_ENDIAN)
    ENDIAN_LITTLE
#else
    ENDIAN_BIG
#endif
    ;

    /*! ID of an agent */
    struct AgentID {
        typedef uint16_t primitive_type;
        static const primitive_type INVALID = 0u;        // reserved invalid value
        static const primitive_type MIN = INVALID+1u;    // first good value
        static const primitive_type MAX = 0x7fffu;       // last good value
        static const primitive_type DYNAMIC_ID_REQUEST = 0x8000u;    // request for a dynamically
                                                                    // assigned id
        AgentID (): m_id(INVALID) {}
        AgentID (primitive_type id): m_id(id) {}

        operator primitive_type () const            { return m_id; }
        AgentID& operator=(primitive_type other)    { m_id = other; return *this; }

        // comparison is done by builtins for primitive types. Defining operators
        // makes the choice ambigous

        bool valid() const                          { return (m_id >= MIN) && (m_id <= MAX);}
        int toInt() const                           { return static_cast<int>((static_cast<unsigned>(m_id) & 0x0ffffu)); }
        explicit operator bool() const IPL_NOEXCEPT { return valid(); }

        bool isDynamicIDRequest() {
            return (static_cast<unsigned>(m_id) & static_cast<unsigned>(DYNAMIC_ID_REQUEST)) != 0;
        }

        static AgentID makeDynamicIDRequest(comm::AgentID id=AgentID()) {
            unsigned int tmp = static_cast<unsigned>(id.toInt());
            tmp |= static_cast<unsigned>(DYNAMIC_ID_REQUEST);
            return AgentID((primitive_type)tmp);
        }

        static AgentID stripDynamicIDRequest(comm::AgentID id) {
            unsigned int tmp = static_cast<unsigned>(id.toInt());
            tmp &= ~static_cast<unsigned>(DYNAMIC_ID_REQUEST);
            return AgentID((primitive_type)tmp);
        }

        primitive_type m_id;
    };

    /* Epoch of an Agent
     * see 'COMM v4 with Agent Epoch'
     * in the wiki: knowledge > framework > mib > comm > agentepoch
     */
    struct COMM_EXPORT AgentEpoch {
        typedef uint16_t primitive_type;
        // reserved initial value: no epoch known/assigned
        static const primitive_type NOEPOCH;        // 0
        // reserved initial value
        static const primitive_type FIRSTVALID;     // NOEPOCH+1
        static const primitive_type MAXEPOCH;       // static_cast <uint16_t> (NOEPOCH-1)
        AgentEpoch(): m_epoch(NOEPOCH) {}
        AgentEpoch(primitive_type epoch): m_epoch(epoch) {}

        // pre increment
        AgentEpoch& operator++()                                { ++m_epoch; return *this; }
        // post increment
        AgentEpoch operator++(int)                                { return m_epoch++; }
        operator AgentEpoch::primitive_type () const            { return m_epoch; }
        AgentEpoch& operator=(AgentEpoch::primitive_type epoch)    { m_epoch = epoch; return *this; }

        // comparison is done by builtins for primitive types. Defining operators
        // makes the choice ambigous
        bool valid() const                                        { return m_epoch != NOEPOCH; }
        int toInt() const                                        { return m_epoch & 0x0ffff; }
        primitive_type    m_epoch;
    };

    class StubID;
    /*! ID of a proxy */
    class ProxyID {
        public:
            typedef uint16_t PrimitiveType;
            static const PrimitiveType INVALID0 = 0;       // reserved invalid value 0
            static const PrimitiveType INVALID = 0xffff;   // reserved invalid value 1
            ProxyID (): m_id(INVALID0) {}
            ProxyID (PrimitiveType id): m_id(id) {}

            operator PrimitiveType () const                { return m_id; }
            ProxyID& operator=(PrimitiveType other)        { m_id = other; return *this; }
            bool valid() const {
                return (m_id != INVALID) && (m_id != INVALID0);
            }
            PrimitiveType m_id;
        private:
            // make the compiler fail on ProxyID/StubID mixup
            ProxyID& operator=(const StubID&);
            ProxyID (const StubID&);
    };

    COMM_EXPORT ipl::ostream& operator<<(ipl::ostream& stream, const comm::ProxyID& id);

    /*! ID of a stub */
    class StubID {
        public:
            typedef uint16_t PrimitiveType;
            static const PrimitiveType INVALID0 = 0;       // reserved invalid value 0
            static const PrimitiveType INVALID = 0xffff;   // reserved invalid value 1
            StubID (): m_id(INVALID0) {}
            StubID (PrimitiveType id): m_id(id) {}

            operator PrimitiveType () const                 { return m_id; }
            StubID& operator=(PrimitiveType other)          { m_id = other; return *this; }
            bool valid() const {
                return (m_id != INVALID) && (m_id != INVALID0);
            }
            PrimitiveType m_id;
        private:
            // make the compiler fail on ProxyID/StubID mixup
            StubID& operator=(const ProxyID&);
            StubID (const ProxyID&);
    };

    COMM_EXPORT ipl::ostream& operator<<(ipl::ostream& stream, const comm::StubID& id);

    #define COMM_LIB_VERSION "ESO_COMM_V_1.0.0"

    /*! ID of a method */
    typedef uint16_t V5MethodID;        // method id until comm v5
    typedef uint32_t V7MethodID;        // method id starting with comm v7
    typedef V7MethodID MethodID;        // method id type in comm

    /*! the kind of interface implementation of the client and service side
    */
    enum InterfaceStyle {
        UndefinedStyle = -1,
        /*! complex types as CIPtr */
        CIPtrStyle = 0,
        /*! complex types as c-style */
        CStyle = 1,
        /*! generic proxy/service api */
        GenericStyle = 2,
        /*!  types as cpp-style */
        CppStyle = 3
    };

    struct Distance {
        enum DistanceValue {
            RemoteDistance = 0    // via some network transport, possible different byte order, alignment etc.
            ,LocalDistance        // same process
            ,LastDistance = LocalDistance    // keep last
        };
        DistanceValue m_dist;

        Distance(DistanceValue val)
        : m_dist(val)
        {
        }

        Distance(AgentID a1, AgentID a2)
        : m_dist((a1==a2)?LocalDistance:RemoteDistance)
        {
        }

        bool isLocal() const { return m_dist == LocalDistance; }
        bool isRemote() const { return m_dist == RemoteDistance; }

        operator int () const {
            return (int)m_dist;
        }
    };

    namespace error {
        enum Errors {
            /*! no error */
            COMM_OK
            /*! a service with this instance id was already registered */
            ,DUPLICATE_INSTANCEID
            /*! the instance id is not valid */
            ,INVALID_INSTANCEID
            /*! connection was lost */
            ,CONNECTION_LOST
            /*! interface key did not match */
            ,INTERFACE_KEY_MISMATCH
            /*! a heap allocation failed */
            ,OOM
            /*! the service is not available any more (or not yet)*/
            ,SERVICE_NOT_AVAILABLE
            /*! the proxy/stub factory for the interface was not found */
            ,FACTORY_NOT_FOUND
            /*! An id pool is exhausted */
            ,ID_POOL_EXHAUSTED
            /*! call on a dead proxy */
            ,OBJECT_IS_DEAD
            /*! a call can not be made because a proxy is not in ALIVE */
            ,PROXY_IS_INVALID
            /*! invalid agent ID has an invalid value */
            ,INVALID_AGENT_ID
            /*! agent is shutting down */
            ,AGENT_IN_SHUTDOWN
            /*! last value that maps directly to comm::broker::ServiceReason/comm::ServiceEvent::Reason */
            ,LAST_DIRECTLY_MAPPABLE=AGENT_IN_SHUTDOWN
            /*! a message size is wrong */
            ,WRONG_MSG_SIZE
            /*! a messag type is wrong, we know what we expected */
            ,WRONG_MSG_TYPE
            /*! unexpected message type without indicating the expected */
            ,UNEXPECTED_MSG_TYPE
            /*! the protocol revision is wrong */
            ,WRONG_PROT_REV
            /*! Unsupported Unicode String Format */
            ,UNSUPPORTED_UNICODE_FORMAT
            /*! General comm error, use for reraising with some comm specific error message */
            ,COMM_ERROR
            /*! The handle value in an instance id has the 'GENERATE_HANDLE' bit set, but does not equal GENERATE_HANDLE
              -> if a handle has the value GENERATE_HANDLE, comm generates a uinque handle
              other than for that one case, the upper bit in the uint32_t handle must not be set.
              */
            ,HANDLE_VALUE_INVALID
            /*! An agent's call on the broker proxy returned with an error */
            ,CANT_TALK_TO_BROKER
            /*! This instance is already registered (registerSelf service error) */
            ,SELF_ALREADY_REGISTERED
            /*! The process name was not found in the configuration */
            ,CONFIG_PROCESS_NOT_FOUND
            /*! The process with a given id was not found in the configuration */
            ,CONFIG_PROCESS_ID_NOT_FOUND
            /*! uncompatible serializer id */
            ,INCOMPAT_SER_ID
            /*! transport setup error */
            ,TRANSPORT_ERROR
            /*! error in size calculation for a message */
            ,SIZE_CALC_ERROR
            /*! an error in the test support features */
            ,TEST_SUPPORT_ERROR
            /*! A necessary factory function pointer was 0 */
            ,FACTORY_FUNCTION_NOT_FOUND
            /*! string size > 32K in serializer found */
            ,STRING_TOO_LONG_FOR_SERIALIZATION
            /*! Method id is unknown */
            ,UNKNOWN_METHOD_ID
            /*! Error setting up connection handler */
            ,CANT_SETUP_CH
        };
    }

    /** \brief Events issued by the Broker with regard to service registration or deregistration */
    struct ServiceEvent {
        /*! The action taken */
        enum Action { NONE, SERVICE_REGISTERED, SERVICE_UNREGISTERED };
        /*! The reason of the event */
        enum Reason {
            NORMAL_OPERATION=comm::error::COMM_OK
            ,DUPLICATE_INSTANCEID=comm::error::DUPLICATE_INSTANCEID
            ,INVALID_INSTANCEID=comm::error::INVALID_INSTANCEID
            ,CONNECTION_LOST=comm::error::CONNECTION_LOST
            ,INTERFACE_KEY_MISMATCH=comm::error::INTERFACE_KEY_MISMATCH
            ,OOM=comm::error::OOM
            ,SERVICE_NOT_AVAILABLE=comm::error::SERVICE_NOT_AVAILABLE
            ,FACTORY_NOT_FOUND=comm::error::FACTORY_NOT_FOUND
            ,ID_POOL_EXHAUSTED=comm::error::ID_POOL_EXHAUSTED
            ,OBJECT_IS_DEAD=comm::error::OBJECT_IS_DEAD
            ,PROXY_IS_INVALID=comm::error::PROXY_IS_INVALID
            ,INVALID_AGENT_ID=comm::error::INVALID_AGENT_ID
            ,AGENT_IN_SHUTDOWN=comm::error::AGENT_IN_SHUTDOWN
            ,INTERNAL_ERROR
            ,PERMISSION_DENIED
            ,NO_SERIALIZER_AVAILABLE
        };

        /*!
        \brief Constructor
        \param    _a is the action
        \param    _r is the reason
        \param    id is the address, which has cause the event
        */
        ServiceEvent( Action _a, Reason _r, const InstanceID& id) : m_action(_a), m_reason(_r), m_id(id) {}
        /*!
        \brief Constructor without reason. Reason is set to the default-value NORMAL_OPERARTION
        \param    _a is the action
        \param    id is the address, to which the event is dispatched
        */
        ServiceEvent( Action _a, const InstanceID& id)
            : m_action(_a), m_reason(NORMAL_OPERATION), m_id(id) {}

        /*! action to perform */
        Action                m_action;
        /*! reason for the action to perform */
        Reason                m_reason;
        /** the instance id of the service that caused the event */
        const InstanceID&    m_id;
    };

    /** \brief some unspecified way to identify methods in comm idl interfaces
        \internal
    */
    typedef MethodID OpaqueMethodID;

    /** \brief A pair of ids relevant for a proxy-stub session
        \internal
    */
    struct ProxyStubID {
        ProxyStubID() {}
        ProxyStubID(ProxyID pid, StubID sid)
        : pid(pid)
        , sid(sid)
        {}

        ProxyID    pid;
        StubID    sid;
    };
}


#endif // COMM_COMMTYPES_HXX
// vim: ts=4 sw=4:

