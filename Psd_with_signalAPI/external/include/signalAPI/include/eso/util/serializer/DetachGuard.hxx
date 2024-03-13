/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_DETACHGUARD_HXX
#define UTIL_SERIALIZER_DETACHGUARD_HXX

#include <common/ScopeGuard.hxx>
#include <util/serializer/IStreamDeserializer.hxx>

namespace util {
namespace serializer {

// detach prottotype that matches the Deaerializer's detachBuffer signature
typedef size_t(util::serializer::IStreamDeserializer::*d_detach_func)(void);

/** Functor for the scopeguard that always returns false */
struct ReturnFalseFunctor {
    bool operator() (size_t arg) {
        return false;
    }
};


/**
 * \brief
 *     This is a specialized ScopeGuard for deserializers that detaches
 *     the buffer when the scope is left.
 *
 *     Usage:
 *     It allows to code something like:
 *
 *  bool foo(Readable r) {
 *         SomeDeserializer deser;
 *         if ( deser.attachBuffer(r) ) {
 *             // handle error
 *             return true;
 *         }
 *         DetachGuard guard(deser);
 *         // do some deserializing ...
 *         // check error, leave early in case of error, buffer is detached by guard
 *         if ( deser.hasError() ) return true;
 *
 *        // some more ...
 *        // final return, buffer is detached by guard
 *        return deser.hasError();
 *     }
 * \see
 *     ipl::ScopeGuard
**/
class DetachGuard :
    public ipl::ScopeGuard< util::serializer::IStreamDeserializer
    ,d_detach_func
    ,ReturnFalseFunctor
    >
{
    public:
        /**
         * \brief
         *  Sets the guard up.
         *  Creates the base with the deserializer instance, release function.
         *  Makes the instance valid.
         *
         * \param
         *     deser A reference to a util::serializer::IStreamDeserializerobject that is to
         *     be detached on dertuction of this guard
         **/
        DetachGuard( util::serializer::IStreamDeserializer& deser) IPL_NOEXCEPT :
            ipl::ScopeGuard< util::serializer::IStreamDeserializer
                            ,d_detach_func
                            ,ReturnFalseFunctor >
                    (
                    deser
                    ,&util::serializer::IStreamDeserializer::detachBuffer
                    ,true
                    )
    {
    }

};

}
}

#endif // UTIL_SERIALIZER_DETACHGUARD_HXX


