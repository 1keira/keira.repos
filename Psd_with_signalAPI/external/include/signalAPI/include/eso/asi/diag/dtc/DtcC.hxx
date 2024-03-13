/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_DIAG_DTC_DTCC_HXX
#define ASI_DIAG_DTC_DTCC_HXX

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
    \brief The dtc::Dtc interface on the client side.
    \details
            A proxy implements this interface.
        * Diagnosis service interface to test and report DTCs based on 3 Byte Diagnostic Fault Check Codes (DFCC).
     *
     * Every diagnosis node on system and android partition registers its own service instance of this interface.   
     * Every instance ID handles exactly the DTCs which are defined for that node.
     * The instance IDs of all nodes are defined in diag_common.idl.
    **/
    class DtcC
    {
    public:
        // List of request methods
        /**
            
         * report a single test result. service side handled the debouncing.
         * should only report a changed test result ((pre)failed -> (pre)passed and vice versa) except after the following events
         * - asi reconnect (due to disconnect from service and/or client side)
         * debouncing is then restarted on service side
         *
         * @param dfcc       The tested dtc
         * @param result     Test result of the test.
         
            reportTestResult Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool reportTestResult(
            const uint32_t dfcc,
            const asi::diag::dtc::eDtcTestResult result
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * signalize if enableConditions are fulfilled (see "Randbedingungen" in dtc specification).
         * Must be sent in case of any status change. enableConditions == false until true value is initially sent by client.
         * TestResults from client are ignored if enabledConditions == false. Must be set to true prior to reportTestResult.
         * 
         * @param dfcc Diagnostic Fault Check Code that this application handles
         * @param fulfilled if enableConditions are fulfilled. If true, a dtc detection is possible on client side.   
         
            enableConditionsFulfilled Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool enableConditionsFulfilled(
            const uint32_t dfcc,
            const bool fulfilled
        ) const IPL_NOEXCEPT = 0;

        DtcC()  {}
        virtual ~DtcC() {}
    protected:
        friend class DtcProxy;
    };

}//namespace asi
}//namespace diag
}//namespace dtc
#endif// ASI_DIAG_DTC_DTCC_HXX
