/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CONFIG_FRAMEWORKPROVIDER_HXX
#define UTIL_CONFIG_FRAMEWORKPROVIDER_HXX

#include <osal/sched.hxx>
#include <ipl_config.h>

#include <util/config/Provider.hxx>
#include <common/types/vector.hxx>

namespace util {
namespace config {

/*!
\brief    This class is a container for keys from the json configuration files
*/
class UTIL_EXPORT FWKeys {
    public:
    //! key for the root process array
    static const char* DEFAULT_CONFIG_PATH;

    //! key for the root process array
    static const char* PROCARRAY;

    //! key for the root node dictionary
    static const char* NODEDICT;

    //! key for any id
    static const char* IDKEY;

    //! key for any name
    static const char* NAMEKEY;

    //! key for any file
    static const char* FILEKEY;

    //! key for any node
    static const char* NODEKEY;

    //! key for resource manager config
    static const char* TCPIPKEY;

    //! key for resource manager config
    static const char* RESMANKEY;

    //! key for resource manager root-path value
    static const char* RESMANROOT;

    //! key for resource manager process settings
    static const char* RESMANLOCALKEY;

    //! key for servicemanager settings node with a process
    static const char* SVCMGRKEY;

    //! default node name
    static const char* DEFAULT_NODE;

    static const char* COMM_SETTINGS;
    static const char* COMM_SETTINGS_CPP;
    static const char* COMM_SETTINGS_CPP_FACTORY_PATH;

    //! process name used by all agents wit dynamically allocated agent ids in the procs array
    static const char* DYNAMIC_PROCESS_NAME;

    //! generic transport settings
    static const char* TRANSPORT_SETTINGS;
    //! transport: path for loadable transport factories
    static const char* TRANSPORT_SETTINGS_TRANSPORT_PATH;
};

/*!
\brief    This class is gives access to the framework root configuration (framework.json) and
        contains a util::config::Provider instance
*/
class UTIL_EXPORT FrameworkProvider {
public:

    enum COMMInterfaceDirection {
        COMMInterfaceDirectionRequest,
        COMMInterfaceDirectionReply
    };

    //! get the instance to the singleton.
    static const Provider &getInstance() IPL_NOEXCEPT;

    /*! Creates a config provider from a given path.
    \param path path to a config file. The file must exist and be readable.
    \return true im case of error e.g. if an instance does already exists (getInstance() was called before)
            or an I/O error ocurred during processing, false otherwise.
    */
    static bool makeInstance(const ipl::string& path) IPL_NOEXCEPT;

    /*! Creates a config provider from json string.
    \param json the configuration as a json string
    \return true im case of error e.g. if an instance does already exists (getInstance() was called before)
            or error ocurred during parsing, false otherwise.
    */
    static bool makeInstanceFromJson(const ipl::string& json) IPL_NOEXCEPT;

    /*!
    \brief    retrieve the name of the node, the process is configured to be running on
    \param    processname [in]
                name of the process
    \param    nodename [out]
                string to store the result into
    \return    false if the process is found and the nodename is configured, true on error
    */
    static bool getNodenameForProcess (const ipl::string& processname, ipl::string& nodename) IPL_NOEXCEPT;

    /*!
    \brief    retrieve the value of the comm factory-path
            if the environment variable IPL_CONFIG_FACTORY_PATH is set, the value
            is retrieved from this, otherwise it's fetched from framework.json

            If neither IPL_CONFIG_FACTORY_PATH nor "comm_settings:factory_path" in
            framework.json is defined, the strings stays unchanged
    \param[out] path
            is the string-instance where the result is stored into
    \return    false in case of "value-found, otherwise true
    */
    static bool getCOMMFactoryPath (ipl::string& path) IPL_NOEXCEPT;

    /*!
    \brief  retrieve the thread-priority for all COMM AgentThreads from
            the framework.json configuration
    \param[out] priority
            is the value read from the configuration. If the priority
            isn't configured the value is unchanged
    \return false in case of "value-found", otherwise true
    */
    static bool getCOMMAgentThreadPrio (int32_t& priority) IPL_NOEXCEPT;

    /*!
    \brief  retrieve the thread-priority for a COMM DefaultActiveObject related to
            a given interface from the framework.json configuration
    \param[in] interface_name
            is the name of the interface as defined in the IDL
            (\<modulename>.\<interfacename>
    \param[in] direction
            defines whether the request or the reply direction is requested
    \param[out] priority
            is the value read from the configuration. If the priority
            isn't configured the value is unchanged
    \return false in case of "value-found", otherwise true
    */
    static bool getCOMMDefaultAOPrio (const char* interface_name,
                                      COMMInterfaceDirection direction,
                                      int32_t& priority) IPL_NOEXCEPT;

    /*!
    \brief  retrieve the scheduling configuration (policy and its parameter)
            of a COMM DefaultActiveObject for a given interface from the framework.json file.
    \param[in] interface_name
            is the name of the interface as defined in the IDL (<modulename>.<interfacename>[Reply])
    \param[in] direction
            defines whether the request or the reply direction is requested
    \param[out]    sched_attr
            the scheduling attributes value, if no scheduling is configured the policy is set to
            osal::sched::OSAL_SCHED_NOOP
    */
    static void getCOMMDefaultAOSched (const char* interface_name
                                    , COMMInterfaceDirection direction
                                    , osal::sched::Attr& sched_attr) IPL_NOEXCEPT;
    /*!
    \brief  Retrieves the scheduling configuration (policy and its parameter)
            of a COMM DefaultActiveObject for a given interface and process name
            from the framework.json file.

     If process name is empty the global configuration is used, if not the per-process configuration
     is used for the passed process name
     \par
     The lookups in the configuration are made starting from the more specific configuration to the more general.
     Thus more specific configuration settings in framework.json override more general ones.
     \par
     The lookup sequence as follows

     \li interface name and process name            (<em>finds per process configuration for a service's interface</em>)
     \li interface name                             (<em>finds global configuration for a service's interface</em>)

     \par
     As soon as a match is found the call returns.

    \param[in] process_name
            is the name of the process as used in framework.json, may be empty
    \param[in] interface_name
            is the name as generated from the IDL (<modulename>.<interfacename>[Reply])
    \param[out] sched_attr
            the scheduling attributes value, if no scheduling is configured the policy is set to
            osal::sched::OSAL_SCHED_NOOP
    */
    static void getCOMMDefaultAOSched (const std::string& process_name
                                    , const char* interface_name
                                    , osal::sched::Attr& sched_attr) IPL_NOEXCEPT;
    /*!
    \brief  Retrieves the agent id values for all statically configured agents from the procs array as integers.
    \param[out] agentIDs
            the vector of agent id values.
    */
    static void getConfiguredAgentIDs (ipl::vector<int32_t>& agentIDs) IPL_NOEXCEPT;

    /*!
    \brief  Retrieves the agent id values for all statically configured agents from the procs array as a range of first, last.
    \param[out] agentIDs
            the vector of agent id values.
    */
    struct AgentIDRange {
        uint16_t min{0};
        uint16_t max{0};
    };
    static AgentIDRange getConfiguredAgentIDRange () IPL_NOEXCEPT;

    /*!
    \brief    retrieve the value of the loadable tranport factory path
            if the environment variable IPL_CONFIG_TRANSPORT_PATH is set, the value
            is retrieved from this, otherwise it's fetched from framework.json

            If neither IPL_CONFIG_TRANSPORT_PATH nor "transport:loadable_path" in
            framework.json is defined, the strings stays unchanged
    \param[out] path
            is the string-instance where the result is stored into
    \return false in case of "value-found", otherwise true
    */
    static bool getLoadableTransportFactoryPath (ipl::string& path) IPL_NOEXCEPT;


    /*!
    \brief    Retrieves the scheduling values from a config dictionary.

    \details
            Reads policy and its parameter from a config value.
            <br>The config value can either be a single number or a dictionary.
            <br>If it is a number the policy is assumed to be "normal" and
            the number is returned in the relevant member (for this policy) in param.
            <br>If it is a dictionary it must contain a "policy" and a "param" key.
            <br>policy is a string with values "normal", "rr", "fifo" etc for scheduling
            policies.
            <param> is a single integer or an array of intergers. The meaning depends on
            the policy value.
            <br>e.g.  { "policy" : "normal", "param" : 1 }
            <br>If the passed config value is no dictionary or if it does not contain valid
            values the policy is set to osal::sched::OSAL_SCHED_NOOP and \p param is not
            changed.

    \param[in] cfg
            the config dictionary.
    \param[out] policy
            the configured policy value.
    \param[out] param
            the configured parameter to \p policy.
    */
    static void getConfiguredSched(const util::config::Value& cfg
                                        ,osal::sched::Policy& policy
                                        ,osal::sched::Param& param
                                        ) IPL_NOEXCEPT;

    /*!
    \brief Translates a string to a scheduling policy value.
    \details
    If the string is not valid osal::sched::OSAL_SCHED_NOOP is returned,
    \return the policy value represented by the passed string.
    */
    static osal::sched::Policy stringToPolicy(const ipl::string& stringValue) IPL_NOEXCEPT;

private:
    static void fatalInstanceError();
};

} // namespace config
} // namespace util

#endif // UTIL_CONFIG_FRAMEWORKPROVIDER_HXX
