/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAC_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAC_HXX

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
    \brief The diagnostic::ViDiagData interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class ViDiagDataC
    {
    public:
        // List of request methods
        /**
            subscribeIds Method ID: 5
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool subscribeIds(
            const CIPtr< CIUInt32Array >& ids
        ) const IPL_NOEXCEPT = 0;

        /**
            unsubscribeIds Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unsubscribeIds(
            const CIPtr< CIUInt32Array >& ids
        ) const IPL_NOEXCEPT = 0;

        /**
            getDiagData Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getDiagData(
            const CIPtr< CIUInt32Array >& diagDataIds
        ) const IPL_NOEXCEPT = 0;

        /**
            getDiagDataMetadata Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getDiagDataMetadata(
            const CIPtr< CIUInt32Array >& diagDataIds
        ) const IPL_NOEXCEPT = 0;

        /**
            writeDiagData Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool writeDiagData(
            const uint32_t id,
            const CIPtr< CIUInt8Array >& data
        ) const IPL_NOEXCEPT = 0;

        ViDiagDataC()  {}
        virtual ~ViDiagDataC() {}
    protected:
        friend class ViDiagDataProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDIAGDATAC_HXX
