/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLYS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLYS_CSTYLE_HXX
#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructDatasetParameter.hxx>
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
    class DiagnosticDatasetsReplyS
    {
    public:
        // List of reply methods
            /**
            \brief
            reply for the attribute DatasetParameters
            updateDatasetParameters Method ID: 7
            **/
        virtual bool updateDatasetParameters (
            const ipl::vector< asi::connectivity::diagnostic::cstyle::DatasetParameter >* DatasetParameters,
            const bool isValid
        ) = 0;


        virtual ~DiagnosticDatasetsReplyS() {}
    protected:
        friend class DiagnosticDatasetsProxyReply;
    };

} // namespace cstyle
}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLYS_CSTYLE_HXX
