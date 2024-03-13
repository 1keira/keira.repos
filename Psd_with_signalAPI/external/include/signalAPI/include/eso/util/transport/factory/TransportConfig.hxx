/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_TRANSPORTCONFIG_HXX
#define UTIL_TRANSPORT_TRANSPORTCONFIG_HXX

#include <ipl_config.h>

#include <util/util_dso.h>

#include <common/Singleton.hxx>
#include <osal/Mutex.hxx>
#include <osal/TCPSocket.hxx>

#include <util/config/FrameworkProvider.hxx>

#include <string>
#include <map>
#include <vector>
#include <utility>

#include <util/transport/factory/FactoryErrors.hxx>

namespace util
{
namespace transport
{

/**
 * \brief
 *     Common access to the transport configuration
 *
 *     This is a common transport configuration handling facility used
 *     by the various transport factories.
 *
 *     It manages the basic access to the
 *     util::config::FrameworkProvider and returns ready to use
 *     parameters for transport settings
 *
 *     The configuration file format is described in the framework
 *     userguide
**/
class UTIL_EXPORT TransportConfig
{
    // this is a singleton such that it may cache any values queried
    // during lifetime
    IPL_DECLARE_SINGLETON(TransportConfig)

public:

    //! kind of possible serializer
    enum SerializerType
    {
        //! undefined serialzer type
        SERIALIZER_NONE,
        //! little endian serializer type
        SERIALIZER_LE,
        //! big endian serializer type
        SERIALIZER_BE
    };

    //! transport protocol type
    enum class TransportFraming {
        TRANSPORT_FRAMING_CLASSIC     //!< classic length first transport protocol
        ,TRANSPORT_FRAMING_ETF        //!< transport protocol with ETF header
        ,TRANSPORT_FRAMING_SEQPACKET  //!< no framing, SOCK_SEQPACKET socket
    };

    //! ETF header features as bitmask
    enum class TransportETFHType : uint32_t {
        TRANSPORT_ETFH_TYPE_NONE            = 0        // ETF header with no additional featured
        ,TRANSPORT_ETFH_TYPE_PI             = 1<<0     // ETF header with peer info token
        ,TRANSPORT_ETFH_TYPE_DOWNGRADABLE   = 1<<1     // ETF header allows downgrade
    };


    struct TransportProtocol {
        TransportFraming    framing;
        uint32_t            header;       // at max currently 32 different features
        size_t              packetsize{0};  // TRANSPORT_FRAMING_SEQPACKET only

        // default: classic
        TransportProtocol()
        : framing(TransportFraming::TRANSPORT_FRAMING_CLASSIC)
        , header((uint32_t)TransportETFHType::TRANSPORT_ETFH_TYPE_NONE)
        {
        }

        // converting from framing type with default header features
        TransportProtocol( TransportFraming fr
                        , uint32_t features=(uint32_t)TransportETFHType::TRANSPORT_ETFH_TYPE_NONE)
        : framing(fr)
        , header(features)
        {
        }

        bool hasFeature(TransportETFHType f) const {
            return (header & (uint32_t)f) == (uint32_t)f;
        }

        void setFeature(TransportETFHType f) {
            if ( f == TransportETFHType::TRANSPORT_ETFH_TYPE_NONE ) {
                header = 0u;
            } else {
                header |= (uint32_t)f;
            }
        }
    };

    /**
     * Contains common parameter used in several transports
     */
    struct UTIL_EXPORT CommonParameter
    {
        CommonParameter() = default;
        explicit CommonParameter(TransportFraming framing) IPL_NOEXCEPT
        :tp{framing}
        {}
        void setHeaderFeature(const std::string& feature) IPL_NOEXCEPT;
        //! rx buffer size
        unsigned rx_buffer{0};
        //! tx buffer size
        unsigned tx_buffer{0};
        ipl::optional<TransportProtocol> tp;
        size_t packetsize{0};
        //! async trasnport
        bool is_async{false};
    };

    /**
     * Contains parameter pertaining to ssl.
     */
    struct SSLParameter
    {
        SSLParameter() IPL_NOEXCEPT : valid(false) {}
        //! \brief parameter valid?
        bool        valid;
        //! path to the ssl certificate file
        ipl::string cert;
        //! path to the private key file
        ipl::string key;
        //! path to ca file
        ipl::string ca;
        //! ssl cipher list
        ipl::string ciphers;
        //! ssl elliptic curve name
        ipl::string ec_name;
    };

    /**
     * Contains parameters for TCP keepalive settings
     *
     *  \link2req{satisfies,req~FW_UTIL_TCP_KEEPALIVE_DEFAULT_SETTING~1}
     */
    struct UTIL_EXPORT KeepaliveParameter: public osal::TCPSocket::KeepaliveSettings {
        // default config is not enabled, as per req~FW_UTIL_TCP_KEEPALIVE_DEFAULT_SETTING~1
        KeepaliveParameter() : osal::TCPSocket::KeepaliveSettings{false} {}
        explicit KeepaliveParameter(bool enabled) : osal::TCPSocket::KeepaliveSettings{enabled} {}
    };

    /**
     * Contains all TCP parameters
     *
     *  \link2req{satisfies,req~FW_UTIL_SO_LINGER_DEFAULT_SETTING~1}
     */
    struct UTIL_EXPORT TcpParameter  {
        TcpParameter() = default;

        TcpParameter(const std::string& address, uint16_t port)
        : address{address}
        , port{port}
        {
        }

        std::string         address;
        uint16_t            port{0};
        bool                enable_nodelay{true};
        std::string         family;
        KeepaliveParameter  keepalive{false};
        uint32_t            user_timeout{0};        // value of 0 indicates to not apply a user timeout
                                                    // when the socket is created in the transport
        bool                enable_linger{false};   // use the linger_time member to set the SO_LINGER socket option
                                                    // is off by default as per req~FW_UTIL_SO_LINGER_DEFAULT_SETTING~1
        unsigned            linger_time{0};         // the timeout value for SO_LINGER
    };


    /*!
    \brief
        Initialize object with the own process name
    \return
        false on success, true on error
    \errors
        ipl::CommonError with ID INVALID_USAGE if the TransportConfig is invalid.
    */
    bool init(const std::string& process) IPL_NOEXCEPT;

    //! whether singleton is valid
    bool isValid() const IPL_NOEXCEPT
    { return m_valid; }

    /*!
      \brief Getter for the name of the process we're running in

      \return Name of the process we're running in
     */
    const std::string& getProcessName() const IPL_NOEXCEPT
    {
        return m_process;
    }

    /*!
      \brief Getter for the name of the node we're running on

      \return Name of the process we're running on
     */
    const std::string& getNodeName() const IPL_NOEXCEPT
    {
        return m_node;
    }

    /*! Extended transport configuration.
     *
     * Consists of a string describing the configuration suitable for Descriptor
     * and a bool with value true indicating that astra is configured.
     */
    struct ExtConfig : public std::pair<std::string, bool> {
        using std::pair<std::string, bool>::pair;   // delegate constructors
        bool is_astra() const {
            return second;
        }
        const std::string& config() const {
            return first;
        }
    };

    /*!
    \brief
        get the transport settings for the specific service the current process can support.
        The information is read from the configuration

    \param[in] service
        the service, which is supported on the transport connection (e.g. comm, tracing)
    \param[out] connections
        a vector to store all found settings into. Each element of the vector contains the setting
        for one connection. The vector is not cleared, entries are only added if an identical
        configuration is not found in the vector
    \return
        -1 in case of an error
        0  in case of success but no entry found
        1  in case of success and one or more entries found
    */
    int16_t getSpawnConnectionConfigs (const std::string& service
                                        ,std::vector< std::string >& spawn_configs) IPL_NOEXCEPT;

    /*!
    \brief
        like getSpawnConnectionConfigs (const std::string& service, std::vector<std::string>& connections)
        but process and node is given

    \param[in] node
        is the node the process is running on
    \param[in] process
        is the process which shall support the transport
    \param[in] service
        the service, which is supported on the transport connection (e.g. comm, tracing)
    \param[out] cfgs
        a vector to store all found settings into. Each element of the vector contains the setting
        for one connection. The vector is not cleared, entries are only added if an identical
        configuration is not found in the vector
    \return
        -1 in case of an error
        0  in case of success but no entry found
        1  in case of success and one or more entries found
    \errorindicator
        on < 0 return an error occured.
    \errors
        util::transport::FactoryErrors
    */

    int16_t getSpawnConnectionConfigs (const std::string& node, const std::string& process
                                        ,const std::string& service
                                        ,std::vector< std::string >& cfgs) IPL_NOEXCEPT;

    int16_t getExtSpawnConnectionConfigs (const std::string& node
                                        ,const std::string& process
                                        ,const std::string& protocol
                                        ,std::vector< ExtConfig >& spawn_configs) IPL_NOEXCEPT;
    /*!
    \brief
        get the transport settings for a process necessary to connect to another process via a given service
        The information is read from the configuration
    \param[in] src_process
        is the process who wants to connect
    \param[in] dest_process
        is the process the src_process wants to connect to
    \param[in] service
        the service, which is supported on the transport connection (e.g. comm, tracing)
    \param[in] connection
        is the instance the found connection information is stored at
    \return
        -1 in case of an error
        0  in case of success but no settings found
        1  in case of success and settings found
    \errorindicator
        on < 0 return an error occured.
    \errors
        util::transport::FactoryErrors
    */
    int16_t getSingleConnectionConfig (const std::string& src_process
                                        ,const std::string& dest_process, const std::string& service
                                        ,std::string& cfg) IPL_NOEXCEPT;

    /*!
    \brief
        like getSingleConnectionConfig (const std::string& src_process, const std::string& dest_process, const std::string& service, std::string& connection)
        but the current process is used as src_process
    \return
        -1 in case of an error
        0  in case of success but no settings found
        1  in case of success and settings found
    \errorindicator
        on < 0 return an error occured.
    \errors
        util::transport::FactoryErrors
    */
    int16_t getSingleConnectionConfig (const std::string& dest_process, const std::string& service
                                        ,std::string& cfg) IPL_NOEXCEPT;

    /*!
    \brief
        Gets the extended transport configuration for a connection from \a src_process to \a dest_process for a given \a protocol.
    \param[out] config
        is a pair of config string suitable for Descriptor and a bool indicating with value true that astra is configured.
    \return
        -1 in case of an error
        0  in case of success but no settings found
        1  in case of success and settings found
    \errorindicator
        on < 0 return an error occured.
    \errors
        util::transport::FactoryErrors
    */
    int16_t getExtSingleConnectionConfig (const std::string& src_process
                                        ,const std::string& dest_process, const std::string& protocol
                                        ,ExtConfig& config) IPL_NOEXCEPT;

    /*!
    \brief
        retrieve the serializer definition for a connection from one process to another
    \param[in] src_process
        is the process who wants to connect
    \param[in] dest_process
        is the process the src_process wants to connect to
    \param[in] service
        the service, which is supported on the transport connection (e.g. comm, tracing)
    \param[out] type
        is the value the found serializer type is stored into
    \return
        false in case of success, true on error
    \errorindicator
        return value
    \errors
        util::transport::FactoryErrors
    \
    */
    bool getSerializer(const std::string& src_process, const std::string& dest_process, const std::string& service, SerializerType& type) IPL_NOEXCEPT;

    /*!
    \brief
        retrieve the serializer definition the current process shall support for a specific service
    \param[in] service
        the service, which is supported on the transport connection (e.g. comm, tracing)
    \param[out] type
        is the value the found serializer type is stored into
    \return
        false in case of success, true on error
    \errorindicator
        return value
    \errors
        util::transport::FactoryErrors
    \
    */
    bool getSerializer(const std::string& service, SerializerType& type) IPL_NOEXCEPT;

    static bool getAstraConfig(const util::config::Value& d) IPL_NOEXCEPT;

private: // methods
    /*!
    \brief
        retrieve the process settings from the configuration
    \param[in] process
        it's the name of the requested process
    \return
        pointer to the config value of the process-settings of an util::config::Value::getUndefined()
    */
    const util::config::Value* getProcessSettings (const std::string& process ) IPL_NOEXCEPT;

    /*!
    \brief
        retrieve the serializer settings for a given node configuration and a given service
        It checks for
        - serializer defined for each node-settings within the node::service block
        - all serializer definitions are equal
    \param[in] node_cfg
        is the configuration for the requested node
    \param[in] service
        is the requested service
    \param[out] type
        is the found serialzer type
    \return
        false on success, true on error
        An error is reported if
        -    a serializer setting is missing
        -    serialzer settings are not equal
    */
    bool getSerializerConfig (const util::config::Value& node_cfg, const std::string& service, SerializerType& type) IPL_NOEXCEPT;


protected: // protected members
    //! ID for the name of the node we're running on
    std::string m_node;

    //! ID for the name of the process we're running in
    std::string m_process;

    //! reference to the config provider singleton
    const util::config::Provider& m_cp;

    //! Whether the TransportConfig was correctly initialized
    bool m_valid;

    //! type for a cache of pointers to util::config::Value instance pointers
    typedef std::map< std::string, const util::config::Value* > ValueCache;

    //! protects parallel access to m_process_cache
    osal::Mutex m_cache_lock;

    //! cache for config settings for a process
    ValueCache m_process_cache;

public:
    //! key for the serializer entry of the configuration
    static const char* KEY_SERIALIZER_ENTRY;
    //! key for the timeout entry of the configuration
    static const char* KEY_TIMEOUT_MS_ENTRY;
    //! key for the transport entry of the configuration
    static const char* KEY_TRANSPORT_ENTRY;
    //! key for the nodes dictionary entry of the configuration
    static const char* KEY_NODES_ENTRY;

    //! key for a node entry of the configuration
    static const char* KEY_NODE_ENTRY;
    //! key for a transport mode entry of the configuration
    static const char* KEY_MODE_ENTRY;
    //! key for a default entry of the configuration
    static const char* KEY_DEFAULT_ENTRY;
    //! key for a transport resourcemanager settings entry of the configuration
    static const char* KEY_RESMAN_ENTRY;
    //! key for a transport tcpip settings entry of the configuration
    static const char* KEY_TCPIP_ENTRY;
    //! key for a transport transportserver settings entry of the configuration
    static const char* KEY_TS_ENTRY;
    //! key for a transport tcpip address settings entry of the configuration
    static const char* KEY_TCPIP_ADDRESS_ENTRY;
    //! key for a transport tcpip port settings entry of the configuration
    static const char* KEY_TCPIP_PORT_ENTRY;
    //! key for tcpip specific nodelay option
    static const char* KEY_TCPIP_NO_DELAY_ENTRY;
    //! key for a transport ip address ifamily settings entry of the configuration
    static const char* KEY_IP_ADDRESS_FAMILY_ENTRY;
    //! key for a transport resourcemanager path settings entry of the configuration
    static const char* KEY_RESMAN_PATH_ENTRY;
    //! key for a transport resourcemanager rootpath settings entry of the configuration
    static const char* KEY_RESMAN_ROOT_ENTRY;
    //! value of the transport type resourcemanager
    static const char* VALUE_RESMAN_TRANSPORT;
    //! value of the transport type tcpip
    static const char* VALUE_TCPIP_TRANSPORT;
    //! value of the serializer type big-endian
    static const char* VALUE_SERIALIZER_BE;
    //! value of the serializer type little-endian
    static const char* VALUE_SERIALIZER_LE;
    //! key the file entry in a transport server configuration
    static const char* KEY_TS_FILE_ENTRY;
    //! key for the mountpoint entry in a transportserver configuration
    static const char* KEY_TS_MOUNTPOINT_ENTRY;
    //! value of the transport type transportserver
    static const char* VALUE_TS_TRANSPORT;
    //! value of the transport type ssl
    static const char* VALUE_SSL_TRANSPORT;
    //! key for the ssl config entry
    static const char* KEY_SSL_ENTRY;
    //! key for a server entry
    static const char* KEY_SERVER_ENTRY;
    //! key for a client entry
    static const char* KEY_CLIENT_ENTRY;
    //! begin od batract paths with astra
    static const char  ABSTRACT_PATH_MARKER;

    //! key for a tx buffer size
    static const char* KEY_TX_BUFFER_ENTRY;
    //! key for a rx buffer size
    static const char* KEY_RX_BUFFER_ENTRY;
    //! 'enable no delay' parameter
    static const char* PARAMETER_NODELAY_OFF;

    //! transport server spawn directory
    static const char* VALUE_TS_SPAWN_DIR;
    //! transport server connect directory
    static const char* VALUE_TS_CONNECT_DIR;
    //! key for the ssl certificate authority entry
    static const char* KEY_SSL_CA_ENTRY;
    //! key for the ssl certificate entry
    static const char* KEY_SSL_CERT_ENTRY;
    //! key for the ssl private key entry
    static const char* KEY_SSL_KEY_ENTRY;
    //! key for the ssl cipher list entry
    static const char* KEY_SSL_CIPHERS_ENTRY;
    //! key for the ssl elliptic curve name entry
    static const char* KEY_SSL_EC_NAME_ENTRY;
    //! local transport key and mode name
    static const char* KEY_LOCAL_ENTRY;
    //! local transport: use abstract namespace
    static const char* KEY_LOCAL_ABSTRACT_ENTRY;
    //! msg transport key and mode name
    static const char* KEY_MSG_ENTRY;
    //! msg transport name by whicht to find the mapper process
    static const char* KEY_MSG_MAPPER_NAME_ENTRY;
    //! ghs connection transport key and mode name
    static const char* KEY_GHSCONN_ENTRY;
    //! transport framing key name
    static const char* KEY_FRAMING_ENTRY;
    // ! transport framing value "classic"
    static const char* VALUE_FRAMING_CLASSIC;
    // ! transport framing value "etf"
    static const char* VALUE_FRAMING_ETF;
    // ! transport framing value "seqpacket" for use with SOCK_SEQPACKET sockets
    static const char* VALUE_FRAMING_SEQPACKET;
    // ! transport packetsize for use with SOCK_SEQPACKET sockets
    static const char* KEY_PACKETSIZE_ENTRY;
    //! transport framing etf header type key name
    static const char* KEY_FRAMING_ETFHEADER;
    // ! transport framing etf header peerinfo value
    static const char* VALUE_FRAMING_ETFHEADER_PI;
    //! transport framing downgrade key
    static const char* KEY_FRAMING_DOWNGRADE_ENTRY;
    //! transport framing downgrade parameter for url
    static const char* VALUE_FRAMING_DOWNGRADABLE;
    //! protocol key
    static const char* KEY_PROTOCOL;
    //! etf without peerinfo
    static const char* VALUE_FRAMING_ETF_NO_PEERINFO;

    //! tcp keepalive parameters
    static const char* KEY_KEEPALIVE_ENTRY;
    //! tcp keepalive enable switch
    static const char* KEY_KEEPALIVE_ENABLED;
    //! key for idle_time for tcp keepalive settings
    static const char* KEY_KEEPALIVE_IDLETIME_ENTRY;
    //! key for probe_count for tcp keepalive settings
    static const char* KEY_KEEPALIVE_PROBECOUNT_ENTRY;
    //! key for probe_interval for tcp keepalive settings
    static const char* KEY_KEEPALIVE_PROBEINTERVAL_ENTRY;
    // corresponding values used in Descriptor
    //! idle_time for tcp keepalive settings
    static const char* DESC_KEEPALIVE_IDLETIME_ENTRY;
    //! probe_count for tcp keepalive settings
    static const char* DESC_KEEPALIVE_PROBECOUNT_ENTRY;
    //! probe_interval for tcp keepalive settings
    static const char* DESC_KEEPALIVE_PROBEINTERVAL_ENTRY;
    //! name of the keepalive enabled option in the transport description
    static const char* DESC_KEEPALIVE_ENABLED;

    //! tcp user timeout parameter
    static const char* KEY_TCP_USER_TIMEOUT;

    //! SO_LINGER for tcp transports
    static const char* KEY_TCP_LINGER;

    //! astra config key
    static const char* KEY_ASTRA;
    //! astra config key for service (listener fro many)
    static const char* KEY_ASTRA_SERVICE;

    //! transport ip family v4
    static const char* VALUE_IP_ADDRESS_FAMILY_V4;
    //! transport ip family v6
    static const char* VALUE_IP_ADDRESS_FAMILY_V6;
    //! tcp transport url scheme
    static const char* SCHEME_TCP;
    //! file transport url scheme
    static const char* SCHEME_FILE;
    //! resman transport url scheme
    static const char* SCHEME_RESMAN;
    //! ts transport url scheme
    static const char* SCHEME_TS;
    //! msg transport url scheme
    static const char* SCHEME_MSG;
    //! ssl transport url scheme
    static const char* SCHEME_SSL;
    //! local transport url scheme
    static const char* SCHEME_LOCAL;
    //! local transport url scheme in astra
    static const char* SCHEME_LOCAL_ASTRA;
    //! ghsconn transport url scheme
    static const char* SCHEME_GHSCONN;

    //! transport parameter for parametrization of this process' endpoint
    static const char* KEY_TRANSPORT_MY_END;

    // wraps an ExtConfig vector
    // Its add() only pushes if the same config isn't already there
    // Since we usually only have low single digit numbers of configurations
    // using a map or set isn't worth it.
    struct ExtConfigContainer {
        explicit ExtConfigContainer(std::vector<ExtConfig>& configs) : configs{configs} {}
        ExtConfigContainer(const ExtConfigContainer&) = delete;
        ExtConfigContainer(ExtConfigContainer&&) = delete;
        ExtConfigContainer& operator=(const ExtConfigContainer&) = delete;
        ExtConfigContainer& operator=(ExtConfigContainer&&) = delete;

        void add(ExtConfig&& config) IPL_NOEXCEPT;

        std::vector<ExtConfig>& configs;
    };

    // Merges process-,process-default,node- and node-default configurations into one dictionary
    // contained within
    class MergedConfig {
        public:
        MergedConfig(const std::string& protcocol
                    ,const util::config::Value& proc
                    ,const util::config::Value& proc_default
                    ,const util::config::Value& node
                    ,const util::config::Value& node_default
                    ,const util::config::Value& process_override
                    ) IPL_NOEXCEPT;

        // make a description of the configured transport for process.
        // This will either be one for SpawnFactory/SimpleFactory
        // or for astra depending on the configuration found.
        // The description is either for an incoming transport of process
        // if is_incoming is true or for a connection to process from a client
        // if is_incoming is false.
        std::string toDescription(const std::string& process
                          ,bool is_incoming ) IPL_NOEXCEPT;

        // is astra configured?
        bool getAstraConfig() IPL_NOEXCEPT;

        const util::config::Dictionary& merged() const IPL_NOEXCEPT { return m_merged; }
        private:
            // merges src into target
            static void merge(util::config::Dictionary* target, const util::config::Value& source) IPL_NOEXCEPT;

            // Gets the transport type/mode ("mode" key in json) and
            // translates that into a scheme for transport descriptions.
            //
            // The mode is either set in the dictionary or inferred.
            // E.g. a dictionary with "mode" looks like this:
            // { "mode" : "tcpip", "tcpip" : {<tcp parameters>} }
            //
            // One with no "mode" :
            // { "tcpip" : {<tcp parameters>} }
            // The inferred mode here is "tcpip".
            //
            // If the merged config doesn't have a "mode" key, we try to guess
            // in the process-config first, then process-default config
            // If no mode can be infered the scheme is set to the empty string
            void detectModeAndScheme(const util::config::Value& proc_config
                                    ,const util::config::Value& proc_default) IPL_NOEXCEPT;

            void getCommonParameter(CommonParameter& cp) IPL_NOEXCEPT;

            std::string                 m_scheme;
            std::string                 m_mode;
            util::config::Dictionary    m_merged;
            std::string                 m_protocol;
    };

}; // class TransportConfig

} // end namespace transport
} // end namespace util

#endif /* UTIL_TRANSPORT_TRANSPORTCONFIG_HXX */
