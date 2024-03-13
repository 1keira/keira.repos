/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructViDiagData.hxx>
#include <asi/connectivity/diagnostic/StructViDiagDataMetadata.hxx>
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
    class ViDiagDataReplyS
    {
    public:
        // List of reply methods
            /**
            getDiagData Method ID: 1
            **/
        virtual bool getDiagData (
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::ViDiagData > >& data,
            const asi::connectivity::diagnostic::ViError error
        ) IPL_NOEXCEPT = 0;

            /**
            onDiagData Method ID: 4
            **/
        virtual bool onDiagData (
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::ViDiagData > >& data
        ) IPL_NOEXCEPT = 0;

            /**
            getDiagDataMetadata Method ID: 3
            **/
        virtual bool getDiagDataMetadata (
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::ViDiagDataMetadata > >& metadata,
            const asi::connectivity::diagnostic::ViError error
        ) IPL_NOEXCEPT = 0;

            /**
            writeDiagData Method ID: 7
            **/
        virtual bool writeDiagData (
            const asi::connectivity::diagnostic::ViError error
        ) IPL_NOEXCEPT = 0;

        virtual ~ViDiagDataReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATA_REPLYS_HXX
