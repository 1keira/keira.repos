/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REPLYS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REPLYS_CSTYLE_HXX
#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructAdaptationValues.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructCodingValues.hxx>
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
            const asi::connectivity::diagnostic::cstyle::AdaptationValues* AdaptationValues,
            const bool isValid
        ) = 0;

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
            const asi::connectivity::diagnostic::cstyle::CodingValues* CodingValues,
            const bool isValid
        ) = 0;


        virtual ~DiagnosticCodingReplyS() {}
    protected:
        friend class DiagnosticCodingProxyReply;
    };

} // namespace cstyle
}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODING_REPLYS_CSTYLE_HXX
