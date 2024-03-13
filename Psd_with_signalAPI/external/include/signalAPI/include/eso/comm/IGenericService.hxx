/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_IGENERICSERVICE_HXX
#define COMM_IGENERICSERVICE_HXX

#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>

namespace util {
namespace transport {
    class Readable;
}
}

namespace comm {

    class GenericProxy;

    /**
      \brief    The generice service interface
     **/
    class COMM_EXPORT IGenericService {
        public:
            IGenericService() {}
            virtual ~IGenericService() {}

            /*!
              Generic method call with serialized call data from remote peers.
              This method is called for every call a proxy makes to this service. The reply proxy instance
              may be invalid if either the service interface has no replies or the caller did not register
              an instance of the reply service.

              \param mid The method id
              \param payload the serialized call arguments and metadata
              \param reply a proxy to reply to the caller, may be not valid
              */
            virtual void handleCallMethod(MethodID mid, const util::transport::Readable& payload
                                            ,const GenericProxy& reply) = 0;

            /*!
              \brief Informs the service about a connected client
              \param count The number of connected clients
              \param reply a proxy to reply to the caller, may be not valid
              */
            virtual void clientConnected(uint32_t count, const GenericProxy& reply) {
                // default implementation is empty, classes that derive from this
                // don't need to implement clientConnected()
            }

            /*!
              \brief Informs the service that a client disconnected
              \param count the number of connected clients
              \param reply a proxy to reply to the caller, may be not valid
              */
            virtual void clientDisconnected(uint32_t count, const GenericProxy& reply) {
                // default implementation is empty, classes that derive from this
                // don't need to implement clientDisconnected()
            }


    };
}
#endif // COMM_IGENERICSERVICE_HXX

