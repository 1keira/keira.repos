/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructDatasetParameter.hxx>
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
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::DatasetParameter > >& DatasetParameters,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

        virtual ~DiagnosticDatasetsReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLYS_HXX
