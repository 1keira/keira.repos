/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

#ifndef COMM_COREPUBLICAPI_HXX
#define COMM_COREPUBLICAPI_HXX

#include <ipl_config.h>
#include <comm/comm_dso.h>
#include <comm/Agent.hxx>

namespace comm {
    // for backward compatibility only. Use comm::Agent
    class COMM_EXPORT CoreApi {
        public:
            CoreApi();
            ~CoreApi();
            static comm::CoreApi& getInstance() IPL_NOEXCEPT;

            void trackServices(const comm::InterfaceID& id, comm::LifecycleListener& ll) IPL_NOEXCEPT {
                Agent::getAgent().trackServices(id, ll);
            }

            void untrackServices( const comm::InterfaceID& id, comm::LifecycleListener& ll) IPL_NOEXCEPT {
                Agent::getAgent().untrackServices(id, ll);
            }

    };
}

#endif // COMM_COREPUBLICAPI_HXX
// vim: ts=4 sw=4:
