/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_DIAG_UDS_READDATABYIDENT_REPLYS_HXX
#define ASI_DIAG_UDS_READDATABYIDENT_REPLYS_HXX
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
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
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
    class ReadDataByIdentReplyS
    {
    public:
        // List of reply methods
            /**
            
         * Service sends request for data to the particular Client
         * based on prior Registration using registerHandler method.
         * 
         * @param requestIdentifier identifier of the tester request. shall not be evaluated by client
         * @param identifier requesting value of this identifier
         * @param dfcc dfcc, if request is triggered by a dtc (use case: reading measurement value assigned to dtc).
         *  If dtc request is not triggered by a dtc, constant dfcc_no_dtc is sent.
         *  In case of dfcc_no_dtc or if values are not dtc specific, dfcc shall not be evaluated by client.
         
            readValue Method ID: 0
            **/
        virtual bool readValue (
            const uint32_t requestIdentifier,
            const uint16_t identifier,
            const uint32_t dfcc
        ) IPL_NOEXCEPT = 0;

        virtual ~ReadDataByIdentReplyS() {}
    };

}// namespace asi
}// namespace diag
}// namespace uds


#endif// ASI_DIAG_UDS_READDATABYIDENT_REPLYS_HXX
