/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
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
    class ViMeasurementReplyS
    {
    public:
        // List of reply methods
            /**
            getMeasurementValues Method ID: 0
            **/
        virtual bool getMeasurementValues (
            const uint32_t measurementId
        ) IPL_NOEXCEPT = 0;

        virtual ~ViMeasurementReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIMEASUREMENT_REPLYS_HXX
