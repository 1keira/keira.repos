/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceC_hxx.tmpl
*/
#ifndef ASI_VEHICLE_TESTC_CSTYLE_HXX
#define ASI_VEHICLE_TESTC_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <asi/vehicle/cstyle/StructKlemmenStatus01Struct.hxx>
#include <asi/vehicle/cstyle/Definitions.hxx>

namespace asi
{
namespace vehicle
{
namespace cstyle {

    /**
    \brief The vehicle::cstyle::Test interface on the client side.
    \detail
            A proxy implements this interface.
    **/
    class TestC
    {
    public:
        // List of request methods
        /**
            \brief
            getter for the attribute Klemmen_Status_01
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
            getKlemmen_Status_01 Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getKlemmen_Status_01(
            
        ) const = 0;

        /**
            \brief
            setNotification for all notifiable attributes
            setNotification Method ID: 32767
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setNotification(
            
        ) const = 0;

        /**
            \brief
            setNotification for one specific attribute
            setNotification Method ID: 32765
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setNotification(
            const uint32_t attributeId
        ) const = 0;

        /**
            \brief
            setNotification for a list of attributes
            setNotification Method ID: 32766
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setNotification(
            const ipl::vector<uint32_t>* attributeId
        ) const = 0;

        /**
            \brief
            clearNotification for all notifiable attributes
            clearNotification Method ID: 32764
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool clearNotification(
            
        ) const = 0;

        /**
            \brief
            clearNotification for one specific attribute
            clearNotification Method ID: 32762
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool clearNotification(
            const uint32_t attributeId
        ) const = 0;

        /**
            \brief
            clearNotification for a list of attributes
            clearNotification Method ID: 32763
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool clearNotification(
            const ipl::vector<uint32_t>* attributeId
        ) const = 0;

        TestC()  {}
        virtual ~TestC() {}
    protected:
        friend class TestProxy;
    };

} // cstyle
}//namespace asi
}//namespace vehicle
#endif// ASI_VEHICLE_TESTC_CSTYLE_HXX
