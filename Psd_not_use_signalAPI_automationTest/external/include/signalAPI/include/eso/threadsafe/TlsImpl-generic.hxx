/*****************************************************************************/
/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/*****************************************************************************/
#ifndef THREADSAFE_TLSIMPL_GENERIC_HXX
#define THREADSAFE_TLSIMPL_GENERIC_HXX

/*****************************************************************************/

#include "threadsafe_dso.h"
#include "Mutex.hxx"

#include <vector>
#include <memory>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Generic implementation of Tls functionality
    */
    class THREADSAFE_EXPORT TlsImpl {

    public:
        TlsImpl() IPL_NOEXCEPT;
        ~TlsImpl() IPL_NOEXCEPT;

        const char *set(void *p) IPL_NOEXCEPT;
        void *get() const IPL_NOEXCEPT;

    protected:

        //! \brief Same size as void * to not lose bits to padding
        typedef uintptr_t Generation;

        struct Item {
            Generation generation;
            void *value;
        };

        //! \brief Actual thread local values
        //!
        //! Every thread creates its own Store and puts a pointer to it into
        //! store, which is \c thread_local. Together with the actual payload
        //! Item::value a Item::generation is stored so reusing a storage
        //! location for a new Tls object can (virtually) reset the stored
        //! value to nullptr.
        typedef std::vector<Item> Store;

        //! \brief Count how many times the same index has already been used
        Generation generation;
        //! \brief Position in *store where the value lives
        Store::size_type index;

        static threadsafe::Mutex mutex;
        typedef std::vector<Generation> Allocated;
        //! \brief List of (un)allocated indexes
        //!
        //! An odd number means allocated, an even number means free. Any
        //! (de)allocation increments the number, so when reusing an index
        //! the generation differs. A maximum possible value is not incremented
        //! again, i.e. stays allocated even when not used anymore.
        static Allocated allocated;
        //! \brief The actual thread local thing, pointing to the per-thread
        //! Store, automatically getting deleted on thread exit
        static thread_local std::unique_ptr<Store> store;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
