/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_VEHICLE_TESTREPLY_HXX
#define ASI_VEHICLE_TESTREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/vehicle/StructKlemmenStatus01Struct.hxx>
#include <asi/vehicle/Definitions.hxx>

namespace asi
{
namespace vehicle
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class TestReply {

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
        virtual void updateKlemmen_Status_01(
            const CIPtr< asi::vehicle::KlemmenStatus01Struct >& Klemmen_Status_01,
            const bool isValid
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count) {}

        // call ids
        void
        updateKlemmen_Status_01CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<TestReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }


        virtual ~TestReply() {}
    };

}//namespace asi
}//namespace vehicle

#endif// ASI_VEHICLE_TESTREPLY_HXX
