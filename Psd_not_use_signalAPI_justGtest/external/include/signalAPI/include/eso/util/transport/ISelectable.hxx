#ifndef UTIL_TRANSPORT_ISELECTABLE_HXX
#define UTIL_TRANSPORT_ISELECTABLE_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/
#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/UInt32Tag.hxx>
#include <common/types/variant.hxx>
#include <osal/Socket.hxx>

namespace util
{
namespace transport
{

/**
 * \brief
 *     An interface that supports i/o multiplexing using an i/o resource
**/
    class UTIL_EXPORT ISelectable {
        public:


            constexpr static const size_t SOCKET_INDEX=0;     // index into SelectableResource variant
                                                        // for sockets

            // the variant index maps to one of the possible alternatives
            struct SocketPair
            {
                osal::SocketHandle::socket_type rxfd;
                osal::SocketHandle::socket_type txfd;
            };
            using SelectableResource = ipl::variant< SocketPair// sockets at index 0
                                                    /* , some other slectable io resources ? */
                                                    >;


            ISelectable() IPL_NOEXCEPT = default;

            virtual ~ISelectable() IPL_NOEXCEPT = default;

            /**
             * \brief Answers if this instance can be used by an i/o multiplexer with the passed index.
             *
             **/
            virtual bool isSelectableBy (size_t index) const IPL_NOEXCEPT {
                return false;
            }

            /**
             * \brief Returns the i/o ressource used to multiplex.
             *
             **/
            virtual SelectableResource getResource() const IPL_NOEXCEPT {
                return SelectableResource(SocketPair{osal::SocketHandle().rxfd, osal::SocketHandle().txfd});
            }
    };

}
}

#endif /* UTIL_TRANSPORT_ISELECTABLE_HXX */
