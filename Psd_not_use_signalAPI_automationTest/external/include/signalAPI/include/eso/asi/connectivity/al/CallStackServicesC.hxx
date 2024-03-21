/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLSTACKSERVICESC_HXX
#define ASI_CONNECTIVITY_AL_CALLSTACKSERVICESC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructCallStackEntry.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief The al::CallStackServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class CallStackServicesC
    {
    public:
        // List of request methods
        /**
            startCallStackDownload Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool startCallStackDownload(
            const int64_t btAddress,
            const asi::connectivity::al::CallStackType type,
            const CIPtr< CIString >& stored_version
        ) const IPL_NOEXCEPT = 0;

        /**
            resetMissedCallCounter Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool resetMissedCallCounter(
            const int64_t btAddress
        ) const IPL_NOEXCEPT = 0;

        CallStackServicesC()  {}
        virtual ~CallStackServicesC() {}
    protected:
        friend class CallStackServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_CALLSTACKSERVICESC_HXX
