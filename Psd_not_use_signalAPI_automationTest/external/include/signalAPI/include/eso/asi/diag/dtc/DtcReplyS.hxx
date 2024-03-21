/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_DIAG_DTC_DTC_REPLYS_HXX
#define ASI_DIAG_DTC_DTC_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/diag/dtc/Definitions.hxx>
namespace asi
{
namespace diag
{
namespace dtc
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    * Diagnosis service interface to test and report DTCs based on 3 Byte Diagnostic Fault Check Codes (DFCC).
     *
     * Every diagnosis node on system and android partition registers its own service instance of this interface.   
     * Every instance ID handles exactly the DTCs which are defined for that node.
     * The instance IDs of all nodes are defined in diag_common.idl.
    **/
    class DtcReplyS
    {
    public:
        // List of reply methods
            /**
            
         *  publishes dtc related events e.g. dtc storage cleared
         *
         *  @param event the occured event
         
            publishEvent Method ID: 1
            **/
        virtual bool publishEvent (
            const asi::diag::dtc::eDtcEvent event
        ) IPL_NOEXCEPT = 0;

        virtual ~DtcReplyS() {}
    };

}// namespace asi
}// namespace diag
}// namespace dtc


#endif// ASI_DIAG_DTC_DTC_REPLYS_HXX
