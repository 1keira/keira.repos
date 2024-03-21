/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructAdaptationValues.hxx>
#include <asi/connectivity/diagnostic/StructCodingValues.hxx>
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
    class DiagnosticCodingReplyS
    {
    public:
        // List of reply methods
            /**
            \brief
            reply for the attribute AdaptationValues
            updateAdaptationValues Method ID: 11
            **/
        virtual bool updateAdaptationValues (
            const CIPtr< asi::connectivity::diagnostic::AdaptationValues >& AdaptationValues,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute CodingValues
            \details
            *
         * Delivers coding values received from IOC (either on startup or when
         * a value has been changed)
         *
         * @param CodingValues - Contains values of all coding parameters
         
            updateCodingValues Method ID: 9
            **/
        virtual bool updateCodingValues (
            const CIPtr< asi::connectivity::diagnostic::CodingValues >& CodingValues,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

        virtual ~DiagnosticCodingReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REPLYS_HXX
