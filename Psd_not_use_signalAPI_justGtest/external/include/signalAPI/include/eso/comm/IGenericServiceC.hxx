/*
      Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/
#ifndef COMM_IGENERICSERVICEC_HXX
#define COMM_IGENERICSERVICEC_HXX

#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>
#include <util/transport/Readable.hxx>
#include <util/transport/IMsgWriter.hxx>

namespace comm {

    /**
      \brief The client side view of the generice service interface
     **/
    class COMM_EXPORT IGenericServiceC {
        public:
            IGenericServiceC () {}
            virtual ~IGenericServiceC () {}

            /*!
              Generic method call with serialized call data.

              \param mid The method id
              \param payload a MsgWriter with the payload
              */
            virtual bool handleCallMethod(MethodID mid
                                ,const util::transport::Readable& payload) = 0;

            /*!
              Generic method call with a MsgWriter for call data.

              \param mid The method id
              \param size size of the payload
              \param payload_writer a IMsgWriter that can write the payload
              */
            virtual bool handleCallMethod(MethodID mid
                                ,size_t size
                                ,util::transport::IMsgWriter& payload_writer ) = 0;

    };

}
#endif // COMM_IGENERICSERVICEC_HXX

