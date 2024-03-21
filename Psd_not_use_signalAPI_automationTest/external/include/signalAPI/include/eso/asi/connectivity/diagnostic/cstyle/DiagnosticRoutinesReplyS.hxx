/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REPLYS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REPLYS_CSTYLE_HXX
#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructRoutineRequestInfo.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace cstyle {

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
            const asi::connectivity::diagnostic::cstyle::RoutineRequestInfo* RoutineRequest,
            const bool isValid
        ) = 0;


        virtual ~DiagnosticRoutinesReplyS() {}
    protected:
        friend class DiagnosticRoutinesProxyReply;
    };

} // namespace cstyle
}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_REPLYS_CSTYLE_HXX
