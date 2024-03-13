/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_ASTRA_FACTORY_HXX
#define UTIL_ASTRA_FACTORY_HXX
/*****************************************************************************/

/*!
    \page util_astra_factory_page Transport Factories

    The factories for new-style Transports are a bunch of functions
    located in astra/factory.hxx.
    
    There is \ref util::astra::create_transport() which creates a
    \ref util::astra::Transport "Transport" and
    \ref util::astra::create_listener() which, you guessed it, creates a
    \ref util::astra::Listener.
    Both take a \ref util::Descriptor "Descriptor" that describes the
    type of %Transport / %Listener you want as well as its parameters.
    
    There is also an \ref util::astra::is_listener() "is_listener()"
    function that you can use to decide whether a given Descriptor describes
    a Listener or not (which will probably mean it describes a Transport).
    
    Concrete %Transport / %Listener types implement their own concrete versions
    of these functions and register them together with their URI schema,
    so the generic factory knows about and can dispatch to them.
    
    \see \ref util_astra_descriptor_page, \ref util_astra_page
*/

/****************************************************************************/

#include "Transport.hxx"
#include "Listener.hxx"
#include <util/Descriptor.hxx>
#include <string>
#include <memory>
#include <functional>

#include <util/util_dso.h>

/****************************************************************************/

namespace util {
    namespace astra {

/****************************************************************************/

        extern UTIL_EXPORT ipl::ErrorType factory_error;

/****************************************************************************/

        /*!
            \brief Does the \p descriptor describe a Listener?
            
            Check whether this descriptor describes a Listener or rather
            a Transport, i.e. whether you can use it with create_listener()
            or rather create_transport().
            
            \see \ref util_astra_factory_page
        */
        UTIL_EXPORT bool is_listener(const Descriptor &descriptor);
        
        /*!
            \brief Create a Transport from a descriptor for which is_listener()
            returned \c false
            
            In case of an error \c nullptr is returned
            and a factory_error is raised.
            
            \see \ref util_astra_factory_page
        */
        UTIL_EXPORT std::unique_ptr<Transport> create_transport(
            const Descriptor &descriptor
        );
        
        /*!
            \brief Create a Listener from a descriptor for which is_listener()
            returns \c true
            
            In case of an error \c nullptr is returned and a factory_error is raised.
            
            \see \ref util_astra_factory_page
        */
        UTIL_EXPORT std::unique_ptr<Listener> create_listener(
            const Descriptor &descriptor
        );
        
        /*!
            \brief Register factory functions for \p scheme
            
            If something else is already registered for \p scheme it will
            silently be overwritten.
            
            \see \ref util_astra_factory_page
            
            \{
        */
        UTIL_EXPORT void sign_on(const std::string &scheme,
                                 std::function<bool (const util::Descriptor &)> &&is_listener,
                                 std::function<std::unique_ptr<Transport>(const Descriptor &)> &&create_transport,
                                 std::function<std::unique_ptr<Listener>(const Descriptor &)> &&create_listener);
        template <typename T> inline void sign_on() {
            sign_on(T::scheme, T::is_listener, T::create_transport, T::create_listener);
        }
        /*! \} */
        
        /*!
            \brief Unregister any factory functions for \p scheme
            
            If nothing is currently registered for \p scheme, that fact will
            mercifully be ignored.
            
            \see \ref util_astra_factory_page
            
            \{
        */
        UTIL_EXPORT void sign_off(const std::string &scheme);
        template <typename T> inline void sign_off() {
            sign_off(T::scheme);
        }
        /*! \} */

/****************************************************************************/

//         template <typename T> class SignOn;
// 
//         template <> class SignOn {
//             
//         public:
//             SignOn(const std::string &scheme,
//                    std::function<bool (const Descriptor &)> is_listener,
//                    std::function<Transport *(const Descriptor &)> create_transport,
//                    std::function<Listener *(const Descriptor &)> create_listener):
//                 scheme(scheme) {
//                 sign_on(scheme, is_listener, create_transport, create_listener);
//             }
//             
//             ~SignOn() {
//                 sign_off(scheme);
//             }
//             
//         protected:
//             std::string scheme;
//         };
//         
//         template <typename T> class SignOn: public SignOn<> {
//             
//         public:
//             SignOn(): SignOn<>(T::scheme, T::is_listener, T::create_transport, T::create_listener) {}
//         };

/****************************************************************************/

    }  // end of namespace astra
}  // end of namespace util

/****************************************************************************/
#endif
