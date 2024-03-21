/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADDATASERVICESC_HXX
#define ASI_CONNECTIVITY_AL_NADDATASERVICESC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructDataConnectionInfo.hxx>
#include <asi/connectivity/al/StructSimDataConfig.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief The al::NadDataServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class NadDataServicesC
    {
    public:
        // List of request methods
        /**
            *
         * Request a data connection.
         * @param dataConnectionId the identifier of the data connection the action is performed for.
         * @param active "true" if a data connection must be is active, else "false".
         * @param ecmId the identifier of the ecm driver that should be used for the data connection
         *       (currently can be 0 –ecm0 or 1 –ecm1 ).
         *
         
            requestDataConnection Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool requestDataConnection(
            const int32_t dataConnectionId,
            const int32_t ecmId,
            const bool active
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Confirm DataConnection.
         * @param dataConnectionId the identifier of the data connection the action is performed for.
         * @param ecmId the identifier of the ecm driver that should be used for the data connection
         *
         * @brief this is called after routing has been set up or dataCall/routing has been started externally
         * @note please treat a disconnection of the ASI in the same way as DataConnectionState::DISCONNECTED
	 
            updateConfirmDataConnection Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool updateConfirmDataConnection(
            const int32_t dataConnectionId,
            const int32_t ecmId,
            const asi::connectivity::al::DataConnectionState state
        ) const IPL_NOEXCEPT = 0;

        /**
            bipRouteResponse Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool bipRouteResponse(
            const asi::connectivity::al::BipRouteResult result
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Set a configuration parameter e.g. APN, login or password for data connections.
         * @param request reqId  request identifier
         * @param request config  configuration, could be for multi apns
         * @param reply reqId  request identifier received by the request
         * @param reply result  the cme error code that was obtained as response for the set at command, -1 if timeout or nad is switched off or 0, in case of success.
         
            setConfiguration Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setConfiguration(
            const int32_t reqId,
            const CIPtr< asi::connectivity::al::SimDataConfig >& config
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Ask NAD to deattach and re-attach to Packet Domain service.
         * @param reply result holds the outcome of the request to de-attach/re-attach.
         
            requestPSReattach Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool requestPSReattach(
            
        ) const IPL_NOEXCEPT = 0;

        NadDataServicesC()  {}
        virtual ~NadDataServicesC() {}
    protected:
        friend class NadDataServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_NADDATASERVICESC_HXX
