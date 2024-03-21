/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTTC_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTTC_HXX

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
    \brief The diagnostic::DiagnosticDatasetsVtt interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class DiagnosticDatasetsVttC
    {
    public:
        // List of request methods
        DiagnosticDatasetsVttC()  {}
        virtual ~DiagnosticDatasetsVttC() {}
    protected:
        friend class DiagnosticDatasetsVttProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSVTTC_HXX
