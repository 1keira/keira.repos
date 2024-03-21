/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCSC_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCSC_CSTYLE_HXX

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
    \brief The diagnostic::cstyle::DiagnosticDtcs interface on the client side.
    \detail
            A proxy implements this interface.
    **/
    class DiagnosticDtcsC
    {
    public:
        // List of request methods
        /**
            reportDtc Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool reportDtc(
            const uint32_t code,
            const asi::connectivity::diagnostic::cstyle::DtcErrorCondition errorCondition
        ) const = 0;

        /**
            \brief
            getter for the attribute Dtcs
            getDtcs Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getDtcs(
            
        ) const = 0;

        /**
            \brief
            setNotification for all notifiable attributes
            setNotification Method ID: 32767
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setNotification(
            
        ) const = 0;

        /**
            \brief
            setNotification for one specific attribute
            setNotification Method ID: 32765
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setNotification(
            const uint32_t attributeId
        ) const = 0;

        /**
            \brief
            setNotification for a list of attributes
            setNotification Method ID: 32766
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setNotification(
            const ipl::vector<uint32_t>* attributeId
        ) const = 0;

        /**
            \brief
            clearNotification for all notifiable attributes
            clearNotification Method ID: 32764
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool clearNotification(
            
        ) const = 0;

        /**
            \brief
            clearNotification for one specific attribute
            clearNotification Method ID: 32762
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool clearNotification(
            const uint32_t attributeId
        ) const = 0;

        /**
            \brief
            clearNotification for a list of attributes
            clearNotification Method ID: 32763
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool clearNotification(
            const ipl::vector<uint32_t>* attributeId
        ) const = 0;

        DiagnosticDtcsC()  {}
        virtual ~DiagnosticDtcsC() {}
    protected:
        friend class DiagnosticDtcsProxy;
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCSC_CSTYLE_HXX
