/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructRoutineRequestInfo.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class DiagnosticRoutinesReplyS
    {
    public:
        // List of reply methods
            /**
            \brief
            reply for the attribute RoutineRequest
            updateRoutineRequest Method ID: 8
            **/
        virtual bool updateRoutineRequest (
            const CIPtr< asi::connectivity::diagnostic::RoutineRequestInfo >& RoutineRequest,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

        virtual ~DiagnosticRoutinesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REPLYS_HXX
