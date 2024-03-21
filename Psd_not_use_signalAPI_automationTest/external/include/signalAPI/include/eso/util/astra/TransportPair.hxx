/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_ASTRA_TRANSPORT_PAIR_HXX
#define UTIL_ASTRA_TRANSPORT_PAIR_HXX
/****************************************************************************/

#include "Transport.hxx"
#include <util/util_dso.h>
#include <memory>

/****************************************************************************/

namespace util {
    namespace astra {

/****************************************************************************/

        /*!
            \brief Pair of connected Transports within the same process
            
            What is sent into one Transport is received by the other
            and vice versa. Like socketpair().
            
            The other Transport can be accessed as member \ref other.
            
            Use it as a drop-in replacement when you need to recycle
            Transport using code in a local context. Do \b not use it
            if there is no need for actual Transports, call the RawCallbacks
            instead or, even better, directly call what's needed.
        */
        class UTIL_EXPORT TransportPair: public Transport {
            
        public:
            /*!
                \brief Create \e two Transports that are connected to
                each other
            */
            TransportPair() IPL_NOEXCEPT:
                other(*new(std::nothrow) TransportPair(this)),
                delete_other(true) {}
            ~TransportPair() IPL_NOEXCEPT override;
            TransportPair(const TransportPair&) = delete;
            TransportPair& operator=(const TransportPair&) = delete;
            
            bool isValid() const IPL_NOEXCEPT override;
            bool send(const ipl::Buf &data) IPL_NOEXCEPT override;
            void retry() IPL_NOEXCEPT override;
            
            //! \brief The other Transport we're connected to
            //
            // This is a reference for interface's sake, internally
            // it is used like a pointer, i.e. with new and delete.
            TransportPair &other;
            
        protected:
            explicit TransportPair(TransportPair *other) IPL_NOEXCEPT:
                other(*other), delete_other(false) {}
                
            void enable() IPL_NOEXCEPT override;
                
            bool delete_other;
        };

/****************************************************************************/

    }  // end of namespace astra
}  // end of namespace util

/****************************************************************************/
#endif
