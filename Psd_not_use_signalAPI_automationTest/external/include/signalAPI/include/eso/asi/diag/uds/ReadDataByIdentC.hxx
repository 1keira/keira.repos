/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_DIAG_UDS_READDATABYIDENTC_HXX
#define ASI_DIAG_UDS_READDATABYIDENTC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/diag/uds/Definitions.hxx>

namespace asi
{
namespace diag
{
namespace uds
{

    /**
    \brief The uds::ReadDataByIdent interface on the client side.
    \details
            A proxy implements this interface.
        * Diagnosis service interface for read by identifier in uds service (0x22, e.g. measurement).
     * Client sends data to the Service as a response 
     * based on request specified by the Identifier.
     * For example this is used to Read the values of Coding or
     * or HW version or SW Version requested by Service. 
     * And these Coding or HW Version or SW Version will be identified by 2-Byte Identifier
     * Detailed list of use cases can be found in the specifications for the corresponding node,    
     * e.g. measurements for 0x8125: "HCP3_0x8125_Messwerte_Bs42.0_03 - Austausch (EXERPT) - HCP3.reqifz"
     *
     * Every diagnosis node on system and android partition registers its own service instance of this interface.   
     * Every instance ID handles exactly the identifiers which are defined for that node.
     * The instance IDs of all nodes are defined in diag_common.idl.
    **/
    class ReadDataByIdentC
    {
    public:
        // List of request methods
        /**
            
         * Register a read data by identifier handler
         * The Client should register the identifier/identifiers for which it is responsible for.
         * 
         * @param identifier identifier of a Read data by ident that this application handles
         
            registerHandler Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool registerHandler(
            const uint16_t identifier
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * Register multiple read by identifier handlers
         * With this method Client can register for multiple Identifiers with a single call.
         * 
         * @param identifiers identifiers of Read data by idents that this application handles
         
            registerHandler Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool registerHandler(
            const CIPtr< CIUInt16Array >& identifiers
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * The Client responds to the readValue Request from the 
         * service along with data values. 
         *
         * @param requestIdentifier identifier of the tester request, which was passed by readValue
         * @param identifier identifier of this value
         * @param value Read value for identifier
         
            readValueReply Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool readValueReply(
            const uint32_t requestIdentifier,
            const uint16_t identifier,
            const CIPtr< CIUInt8Array >& value
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * If Client can not process the readValue request then ErrorResponse to be sent
         * Only Following eServiceOpError codes can be sent.
         * service_condition_incorrect(0x22)
         *   - This error must be sent if the condition for identifier does not apply
         * service_failure_prevents_execution(0x26)
             - This error must be sent if e.g. a hardware error prevents processing the request
         * service_request_out_of_range(0x31)
         *   - This error must be sent if requested Identifier is not supported currently or
         *     Identifier is not supported in the current  configuration (e.g. coding or parameter set does not apply).
         *
         * @param requestIdentifier identifier of the tester request, which was passed by readValue
         * @param identifier  Requested identifier
         * @param eServiceOpError Reason for failure
         
            readValueErrorReply Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool readValueErrorReply(
            const uint32_t requestIdentifier,
            const uint16_t identifier,
            const asi::diag::uds::eServiceOpError error
        ) const IPL_NOEXCEPT = 0;

        ReadDataByIdentC()  {}
        virtual ~ReadDataByIdentC() {}
    protected:
        friend class ReadDataByIdentProxy;
    };

}//namespace asi
}//namespace diag
}//namespace uds
#endif// ASI_DIAG_UDS_READDATABYIDENTC_HXX
