/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICEC_HXX
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICEC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructAntennaInfo.hxx>
#include <asi/connectivity/al/StructDataConnectionInfo.hxx>
#include <asi/connectivity/al/StructDataConnectionStartResult.hxx>
#include <asi/connectivity/al/StructNadDeviceInformation.hxx>
#include <asi/connectivity/al/StructNetworkInfo.hxx>
#include <asi/connectivity/al/StructNetworkRejectInformation.hxx>
#include <asi/connectivity/al/StructSimDataConfig.hxx>
#include <asi/connectivity/al/StructSimDataInfo.hxx>
#include <asi/connectivity/al/StructTemperatureInfo.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief The al::NadInformationService interface on the client side.
    \details
            A proxy implements this interface.
        *
    * Clients, which are registered with the NadInformationService,
    * will receive updates of NAD related information.
    * All information will be cached and is read-only from a client perspective.
    **/
    class NadInformationServiceC
    {
    public:
        // List of request methods
        /**
            \brief
            getter for the attribute AntennaInfo
            getAntennaInfo Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getAntennaInfo(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute DataConnectionInfo
            getDataConnectionInfo Method ID: 5
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getDataConnectionInfo(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute SimDataConfig
            getSimDataConfig Method ID: 13
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getSimDataConfig(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute DataConnectionStartResult
            getDataConnectionStartResult Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getDataConnectionStartResult(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute NadDeviceInformation
            getNadDeviceInformation Method ID: 9
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getNadDeviceInformation(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute NetworkRejectInformation
            getNetworkRejectInformation Method ID: 12
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getNetworkRejectInformation(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute SimDataInfo
            getSimDataInfo Method ID: 14
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getSimDataInfo(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute TemperatureInfo
            getTemperatureInfo Method ID: 15
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getTemperatureInfo(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute NetworkInfo
            getNetworkInfo Method ID: 11
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getNetworkInfo(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute AirplaneMode
            getAirplaneMode Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getAirplaneMode(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute NadState
            getNadState Method ID: 10
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getNadState(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute JammingState
            getJammingState Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getJammingState(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            \brief
            getter for the attribute DormantMode
            getDormantMode Method ID: 7
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getDormantMode(
            
        ) const IPL_NOEXCEPT = 0;

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
            
        ) const IPL_NOEXCEPT = 0;

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
        ) const IPL_NOEXCEPT = 0;

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
            const CIPtr< CIUInt32Array >& attributeId
        ) const IPL_NOEXCEPT = 0;

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
            
        ) const IPL_NOEXCEPT = 0;

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
        ) const IPL_NOEXCEPT = 0;

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
            const CIPtr< CIUInt32Array >& attributeId
        ) const IPL_NOEXCEPT = 0;

        NadInformationServiceC()  {}
        virtual ~NadInformationServiceC() {}
    protected:
        friend class NadInformationServiceProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICEC_HXX
