/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_PACKETSIZE_LIMIT_HXX
#define UTIL_TRANSPORT_PACKETSIZE_LIMIT_HXX

#include <ipl_config.h>

#include <stddef.h> // size_t
#include <common/stdint.h>    // SIZE_MAX

namespace util
{

namespace transport
{

/**
 * \brief
 *     Packet size limit helper
**/

// desired effect:
//     A limit of SIZE_MAX will let all packets pass, a limit of 0 will let
//     no packets pass
//     when disabled all sizes should get passed

// we should present as the max possible size if we are disabled, as the set limit otherwise
// thus no other size can exceed is when disabled, which is what would be expected.
    class PacketSizeLimit {
        public:
            // starts out disabled
            PacketSizeLimit() IPL_NOEXCEPT : m_limit(SIZE_MAX) {}

            void enable(size_t limit) IPL_NOEXCEPT {
                m_limit = limit;
            }

            void disable() IPL_NOEXCEPT {
                m_limit = SIZE_MAX;
            }

            // setting SIZE_MAX as limit is the same as disabling
            bool enabled() const IPL_NOEXCEPT {
                return m_limit != SIZE_MAX;
            }

            operator size_t () const IPL_NOEXCEPT {
                return m_limit;
            }

            // compare with size_t
            bool operator <= (size_t size) const IPL_NOEXCEPT {
                return m_limit <= size;
            }
            bool operator < (size_t size) const IPL_NOEXCEPT {
                return m_limit < size;
            }
            bool operator == (size_t size) const IPL_NOEXCEPT {
                return m_limit == size;
            }
            bool operator >= (size_t size) const IPL_NOEXCEPT {
                return !operator < (size);
            }
            bool operator > (size_t size) const IPL_NOEXCEPT {
                return !operator <= (size);
            }
            bool operator != (size_t size) const IPL_NOEXCEPT {
                return !operator == (size);
            }

        private:
            size_t m_limit;
    };

}
}

#endif // UTIL_TRANSPORT_PACKETSIZE_LIMIT_HXX
