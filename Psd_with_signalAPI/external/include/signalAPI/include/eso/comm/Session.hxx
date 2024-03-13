/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_SESSION_HXX
#define COMM_SESSION_HXX


#include <ipl_config.h>
#include <comm/comm_dso.h>
#include <util/UInt32Tag.hxx>
#include <comm/commtypes.hxx>
#include <comm/commtracing.hxx>


namespace tracing {
    class Channel;
}

namespace comm {
    /*
        This interface is used by the generated code.
    */

    /*! low level meta info about a comm session  */
    struct COMM_EXPORT Session;

    /*! low level interface to get the serializer tag from a session */
    COMM_EXPORT util::UInt32Tag get_serializer_tag(const Session&) IPL_NOEXCEPT;

    /*! low level comm tracing setup for a session */
    COMM_EXPORT void setup_comm_tracing(Session&
                                      ,tracing::Channel*
                                      ,comm::CommTracingContent
                                      ,bool is_request
                                      ) IPL_NOEXCEPT;

}

#endif // COMM_SESSION_HXX
