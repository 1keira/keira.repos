/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef IPLBASE_NONCOPYABLE_HXX
#define IPLBASE_NONCOPYABLE_HXX
/*****************************************************************************/

namespace iplbase {

/*****************************************************************************/

    /*!
        \brief Mixin for copy inhibit

        An object inheriting from this cannot be assigned to.
        So when you have a class that should not allow copying an object,
        inherit from iplbase::NonCopyable,
        which clearly documents your intent and saves you dealing with
        technical details.
    */
    class NonCopyable {

    protected:
        NonCopyable() {}

    private:
        //! \brief Not implemented => non-copyable
        NonCopyable(const NonCopyable &other);
        //! \brief Not implemented => non-copyable
        NonCopyable &operator = (const NonCopyable &other);
    };

/*****************************************************************************/

}  // end of namespace iplbase

/*****************************************************************************/
#endif
