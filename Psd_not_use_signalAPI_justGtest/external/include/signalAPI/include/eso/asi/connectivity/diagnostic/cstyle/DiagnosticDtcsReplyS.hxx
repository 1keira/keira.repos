/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_REPLYS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_REPLYS_CSTYLE_HXX
#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructDtc.hxx>
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
    class DiagnosticDtcsReplyS
    {
    public:
        // List of reply methods
            /**
            \brief
            reply for the attribute Dtcs
            updateDtcs Method ID: 8
            **/
        virtual bool updateDtcs (
            const ipl::vector< asi::connectivity::diagnostic::cstyle::Dtc >* Dtcs,
            const bool isValid
        ) = 0;


        virtual ~DiagnosticDtcsReplyS() {}
    protected:
        friend class DiagnosticDtcsProxyReply;
    };

} // namespace cstyle
}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCS_REPLYS_CSTYLE_HXX
