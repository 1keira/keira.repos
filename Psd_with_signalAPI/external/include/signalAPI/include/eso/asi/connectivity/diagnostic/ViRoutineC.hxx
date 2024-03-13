/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINEC_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINEC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructRoutineRequest.hxx>
#include <asi/connectivity/diagnostic/StructRoutineResponse.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief The diagnostic::ViRoutine interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class ViRoutineC
    {
    public:
        // List of request methods
        /**
            routineResponse Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool routineResponse(
            const CIPtr< asi::connectivity::diagnostic::RoutineResponse >& response
        ) const IPL_NOEXCEPT = 0;

        /**
            subscribeIds Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool subscribeIds(
            const CIPtr< CIUInt32Array >& routineIds
        ) const IPL_NOEXCEPT = 0;

        /**
            unsubscribeIds Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unsubscribeIds(
            const CIPtr< CIUInt32Array >& routineIds
        ) const IPL_NOEXCEPT = 0;

        ViRoutineC()  {}
        virtual ~ViRoutineC() {}
    protected:
        friend class ViRoutineProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINEC_HXX
