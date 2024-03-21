/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_RPC_STUBBASE_HXX
#define COMM_RPC_STUBBASE_HXX

#include <ipl_config.h>
#include <comm/comm_dso.h>
#include <comm/StubBase.hxx>

namespace comm {

    /**
      \brief    baseclass for a remote stub in the comm-framework.
     **/
    class COMM_EXPORT RPCStubBase : public StubBase {
        public:

            RPCStubBase ( const comm::ConnectionPtr& conn
                        ,comm::InstanceID::Handle_t reply_handle
                        ,const comm::ProxyStubID& psid
                        ) IPL_NOEXCEPT;

            ~RPCStubBase () IPL_NOEXCEPT override;

    };

}

#endif // COMM_RPC_STUBBASE_HXX

