/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef UTIL_TRANSPORT_FACTORY_IDISPOSABLE_HXX
#define UTIL_TRANSPORT_FACTORY_IDISPOSABLE_HXX
/*****************************************************************************/

#include <ipl_config.h>

/*****************************************************************************/

namespace util {
    namespace transport {

/*****************************************************************************/

        /*!
            \brief Can dispose of itself

            You should inherit this interface for all objects that are returned
            by a factory with potentially non-trivial internal memory management
            or lifecycle logic.

            This interface is a compromise.
            Theoretically the functionality to dispose of some object already
            has a standard interface, namely the (overridden) \c delete
            operator.
            On the other hand it would surprise the user if \c delete would not
            actually free the allocated memory but just decrement a reference
            counter or similar.
            Therefore I (S.M.) decided to go with the more complicated,
            more explicit, less standard conform and less surprising variant.

        */
        class UTIL_EXPORT IDisposable {

        public:
            virtual ~IDisposable() {}

            //! \brief Drop object ownership, possibly deleting it
            //!
            //! You may not call any of the object's methods (including
            //! operator delete and dispose) after calling this.
            //! You are either obliged or forbidden to call this at all,
            //! depending on how you got hold of the object, i.e.
            //! on whether you own it or not.
            virtual void dispose()=0;
        };

/*****************************************************************************/

    }  // end of namespace transport
}  // end of namespace util

/*****************************************************************************/
#endif
