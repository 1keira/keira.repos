/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_REPLYS_HXX
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
    class DiagnosticDatasetsVttReplyS
    {
    public:
        // List of reply methods
            /**
            updateDatasetParameters Method ID: 0
            **/
        virtual bool updateDatasetParameters (
            const uint16_t datasetId,
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::DatasetParameter > >& parameters
        ) IPL_NOEXCEPT = 0;

        virtual ~DiagnosticDatasetsVttReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTT_REPLYS_HXX
