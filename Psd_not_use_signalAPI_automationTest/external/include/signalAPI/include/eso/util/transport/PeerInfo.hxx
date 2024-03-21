/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_PEERINFO_HXX
#define UTIL_TRANSPORT_PEERINFO_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <common/Tag.hxx>

#include <string>

// This should build without runtime dependencies to framework libs
// so that it can be used in jni without dragging all framewerk libs into
// the Java VM.
// so: careful with includes

namespace util {
namespace transport {
    class UTIL_EXPORT PeerInfo {
        public:
            virtual ~PeerInfo() IPL_NOEXCEPT = default;

            // let derived classes return their tag
            virtual const ipl::Tag& tag() const IPL_NOEXCEPT = 0;

            // cast to T if T::TYPE equals tag(), return null if not
            // all derived classes need a static TYPE tag which they return in tag()
            template <typename T>
            const T* as() const IPL_NOEXCEPT {
                if( T::TYPE == tag() ) {
                    return static_cast<const T*>(this);
                }
                return 0;
            }

            virtual std::string toString() const IPL_NOEXCEPT = 0;

    };

}
}
#endif


