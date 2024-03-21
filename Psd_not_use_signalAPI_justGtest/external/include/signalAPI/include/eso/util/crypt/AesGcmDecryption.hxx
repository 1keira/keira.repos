/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CRYPT_AESGCMDECRYPTION_HXX
#define UTIL_CRYPT_AESGCMDECRYPTION_HXX

#include <util/crypt/AesGcmBase.hxx>

#include <cstdint>
#include <vector>

namespace util {
namespace crypt {

/*****************************************************************************/

    /*!
        \brief Cipher that decrypts using AES in Galois Counter mode (GCM).

        \see \ref util_crypt_aes_gcm

        In decryption the initialization vector and authentication tag
        from the encryption have to be provided together with key and ciphertext.

        To decrypt with AesGcmDecryption:
        - create an instance
        - set the encryption key with setKey()
        - start the encryption with start() providing the initialization vector
        - call decrypt() as many times as necessary providing a chunk of data to decrypt
          and creating a chunk or cleartext
        - call finish() with the authentication tag to complete the encryption and
          verify that the encrypted data have not been tampered with.

        This is the process necessary to decrypt one set of data.

        There is a helper class AesGcmDecryptionHelper that provides all of
        this in a single call.

        \see AesGcmEncryption, AesGcmEncryptionHelper, AesGcmDecryptionHelper
     */

    class UTIL_EXPORT AesGcmDecryption final : public AesGcmBase {

        public:
            using Tag = AesGcmBase::Tag;

            //! \brief Initializes some context for cryptographic operations.
            //!
            //! Instances can't be copied, but moved.
            AesGcmDecryption() IPL_NOEXCEPT : AesGcmBase() {};
            ~AesGcmDecryption() IPL_NOEXCEPT = default;

            AesGcmDecryption(const AesGcmDecryption&) = delete;
            AesGcmDecryption& operator=(const AesGcmDecryption&) = delete;

            AesGcmDecryption(AesGcmDecryption&&) = default;
            AesGcmDecryption& operator=(AesGcmDecryption&&) = default;

            //! \brief Sets the key.
            //!
            //! Key data are copied. Allowed key sizes is in bytes are are 16, 24, 32
            //! for the AES standard key sizes in bits of 128, 192, 256.
            //! Returns \c true on error and raises.
            bool setKey(const  uint8_t* key_data, size_t key_size) IPL_NOEXCEPT;

            //! \brief Set up for decryption of a new set of data.
            //!
            //! The initialization vector that was used in encryption
            //! must be provided.
            //! Returns \c true on error and raises.
            bool start(const uint8_t* iv_data, size_t iv_size) IPL_NOEXCEPT;

            //! \brief Decrypts ciphertext \a input of size \a input_size into \a output that has \a output_size space.
            //!
            //! The size of the generated cleartext in \a output is the same as \a input_size.
            //! If output_size is less than input_size, the call will fail.
            //! This call can be repeated several times.
            //!
            //! Complete the decryption with finish().
            //! Returns \c true on error and raises.
            bool decrypt(const uint8_t* input, size_t input_size
                        ,void* output, size_t output_size) IPL_NOEXCEPT;

            //! \brief Completes the decryption.
            //!
            //! Does not create new output data. finish() verifies the passed
            //! authentication tag.
            //! You can pass nullptr as tag_data. This indicates that no authentication
            //! check is done. In this case AES/GCM looses its authentication feature -
            //! it looses the verification that the ciphertext has not been tampered with.
            //! Returns true on error and raises.
            bool finish(const uint8_t* tag_data, size_t tag_size) IPL_NOEXCEPT;
    };
}
}

#endif // UTIL_CRYPT_AESGCMENCRYPTION_HXX
