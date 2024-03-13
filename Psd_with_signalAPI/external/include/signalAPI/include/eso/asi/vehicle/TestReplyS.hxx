/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_VEHICLE_TEST_REPLYS_HXX
#define ASI_VEHICLE_TEST_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/vehicle/StructKlemmenStatus01Struct.hxx>
#include <asi/vehicle/Definitions.hxx>
namespace asi
{
namespace vehicle
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class TestReplyS
    {
    public:
        // List of reply methods
            /**
            \brief
            reply for the attribute Klemmen_Status_01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ZAS_Kl_15:
         *   * E3_1_1_UNECE: Klemmen_Status_01.ZAS_Kl_15
         * > KlemmenStatus01Struct.ZAS_Kl_15 [uint64]:
         *   Based on:
         *     * ZAS_Kl_15: Klemme 15: Zuendung (SW-Kl.15)
         *   Used Constants:
         *     0: eZASKl15_Aus
         *     1: eZASKl15_Ein
         * > KlemmenStatus01Struct.pdustate [uint64]:
         *   Based on:
         *     ZAS_Kl_15 SignalState
         *   Used Constants:
         *     0: ePdustate_NotExisting
         *     1: ePdustate_Valid
         *     2: ePdustate_TempNotValid
         *     3: ePdustate_TimeoutNotValidNotFiltered
         *     4: ePdustate_NeverReceived
         *     5: ePdustate_TimeoutNotValidFiltered
         *     15: ePdustate_Invalid
         ***
            updateKlemmen_Status_01 Method ID: 7
            **/
        virtual bool updateKlemmen_Status_01 (
            const CIPtr< asi::vehicle::KlemmenStatus01Struct >& Klemmen_Status_01,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

        virtual ~TestReplyS() {}
    };

}// namespace asi
}// namespace vehicle


#endif// ASI_VEHICLE_TEST_REPLYS_HXX
