/*
    Copyright 2022 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CRYPT_KEYSTORE2_HXX
#define UTIL_CRYPT_KEYSTORE2_HXX

#include <util/util_dso.h>
#include <ipl_config.h>

#include <common/error/ErrorType.hxx>
#include <common/buffers.hxx>
#include <osal/userinfo.hxx>

#include <cstdint>
#include <string>

namespace util {
namespace crypt {

    /**
     * \brief Keystore2 is a repository of cryprographic keys based on the keystore2 library.
     *
     * This class allows to create, retreive and remove cryptographic
     * keys from the key repository.
     *
     * In this repository keys are identified by a name and a group id.
     *
     * The repository implements access control.
     * To be able to access keys users have to
     * - be in group "tee" and
     * - be in the group that is used to identify the key
     *
     * The same key can by accessed by different applications if they fullfill
     * the access requirements.
     */

    class UTIL_EXPORT KeyStore2 {
        public:
            KeyStore2() IPL_NOEXCEPT = default;
            ~KeyStore2() IPL_NOEXCEPT = default;

            //! \brief Returns the name of this store.
            std::string getName() const IPL_NOEXCEPT;

            //! \brief A buffer with key data.
            struct Key {
                Key() IPL_NOEXCEPT = default;

                explicit Key(const ipl::SharedBuf& buf) IPL_NOEXCEPT : key_buffer{buf} {}
                explicit Key(ipl::SharedBuf&& buf) IPL_NOEXCEPT : key_buffer{buf} {}

                ipl::SharedBuf key_buffer;

                const uint8_t* data() const {
                    return (const uint8_t*) key_buffer;
                }

                size_t size() const {
                    return key_buffer.bytes();
                }

                bool empty() const {
                    return !(bool)key_buffer || (key_buffer.bytes()) == 0;
                }
            };

            using GroupId = osal::Group::Id;

            //! \brief creates and returns a key.
            //!
            //! The key is created with \a key_size bytes length and populated with random values.
            //!
            //! Returns an empty key and raises on error.
            Key create(const std::string& name, GroupId gid, size_t key_size) IPL_NOEXCEPT;

            //! \brief Returns an existing key.
            //!
            //! If a \a key_size of 0 is passed, the call will try to guess an adequate
            //! buffer size for the key data. This may lead to several allocations.
            //!
            //! Returns an empty key and raises on error.
            Key get(const std::string& name, GroupId gid, size_t key_size=0) const IPL_NOEXCEPT;


            //! \brief Removes an existing key.
            //!
            //! Returns true and raises on error.
            bool remove(const std::string& name, GroupId gid) IPL_NOEXCEPT;


            static ipl::ErrorType error;

            // this instead of enum struct avoids having to cast to int in each
            // ipl_raise call.
            struct Reason {
                enum {
                    library_error,      //!< \brief error returned from the keystore2 library
                    buffer_alloc_error, //!< \brief error allocating the key buffer
                    not_supported       //!< \brief keystore2 is not available
                };
            };

        protected:
            static ipl::ErrorID error_table[];


    };

}
}
#endif  // UTIL_CRYPT_KEYSTORE2_HXX
