/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CRYPT_AESGCMENCRYPTION_HXX
#define UTIL_CRYPT_AESGCMENCRYPTION_HXX

#include <util/crypt/AesGcmBase.hxx>

#include <cstdint>
#include <vector>

namespace util {
namespace crypt {

    /*!
        \brief Cipher that encrypts using AES in Galois Counter mode (GCM).

        \see \ref util_crypt_aes_gcm

        To encrypt with AesGcmEncryption:
        - create an instance
        - set the encryption key with setKey()
        - start the encryption with start() providing the initialization vector
        - call encrypt() as many times as necessary providing a chunk of data to encrypt
          and creating a chunk or ciphertext
        - call finish() to complete the encryption

        After finish() retrieve the authentication tag with getTag().

        This is the process necessary to encrypt one set of data.

        There is a helper class AesGcmEncryptionHelper that provides all of
        this in a single call.

        In decryption the initialization vector and authentication tag have
        to be provided together with the encrypted output.


        \see AesGcmDecryption, AesGcmEncryptionHelper, AesGcmDecryptionHelper
     */

/*****************************************************************************/

    class UTIL_EXPORT AesGcmEncryption final : public AesGcmBase {

        public:
            using Tag = AesGcmBase::Tag;

            //! \brief Initializes some context for cryptographic operations.
            //!
            //! Instances can't be copied, but moved.
            AesGcmEncryption() IPL_NOEXCEPT : AesGcmBase() {};
            ~AesGcmEncryption() IPL_NOEXCEPT = default;

            AesGcmEncryption(const AesGcmEncryption&) = delete;
            AesGcmEncryption& operator=(const AesGcmEncryption&) = delete;

            AesGcmEncryption(AesGcmEncryption&&) = default;
            AesGcmEncryption& operator=(AesGcmEncryption&&) = default;

            //! \brief Sets the key.
            //!
            //! Key data are copied. Allowed key sizes is in bytes are 16, 24 and 32
            //! for the AES standard key sizes of 128, 192, 256 bit.
            //! Returns \c true on error and raises.
            bool setKey(const  uint8_t* key_data, size_t key_size) IPL_NOEXCEPT;

            //! \brief Set up for encryption of a new set of data.
            //!
            //! A new initialization vector must be provided for each new set
            //! of data.
            //! Returns \c true on error and raises.
            bool start(const uint8_t* iv_data, size_t iv_size) IPL_NOEXCEPT;

            //! \brief Encrypts cleartext \a input of size \a input_size into \a output that has \a output_size space.
            //!
            //! The size of the generated ciphertext in \a output is the same as \a input_size.
            //! If output_size is less than input_size, the call will fail.
            //! This call can be repeated several times.
            //!
            //! Complete the encryption with finish().
            //! Returns \c true on error and raises.
            bool encrypt(const void* input, size_t input_size
                        ,uint8_t* output, size_t output_size) IPL_NOEXCEPT;

            //! \brief Completes the encryption.
            //!
            //! Does not create new output data. After finish() was called, the
            //! authentication tag can be retrieved with getTag().
            //! Returns true on error and raises.
            bool finish() IPL_NOEXCEPT;

            //! \brief Returns the authentication tag.
            //!
            //! This is a reference to internal data, which get overwritten with each
            //! finish() call.
            const Tag& getTag() const IPL_NOEXCEPT { return m_tag; }

        private:
            Tag                                     m_tag{};


    };
}
}

#endif // UTIL_CRYPT_AESGCMENCRYPTION_HXX
