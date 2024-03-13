/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CRYPT_AESGCMBASE_HXX
#define UTIL_CRYPT_AESGCMBASE_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <common/error/Error.hxx>

#include <cstdint>
#include <array>
#include <vector>
#include <string>

#if defined(HAVE_SSL) && defined(BUILD_UTIL_WITH_CRYPTO)
#include <openssl/evp.h>
#else
    struct EVP_CIPHER_CTX {};
    struct EVP_CIPHER {};
#endif

namespace util {
namespace crypt {

/*!
    \page util_crypt_aes_gcm Encryption with AES/GCM

    [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) (Advanced Encryption Standard) is a standardized encryption specification.

    It is a symmetric block cipher that uses keys of length 128, 192, 256 Bit.

    [GCM](https://en.wikipedia.org/wiki/Galois/Counter_Mode) (Galois/counter mode) is one of the modes AES can be used
    in.

    AES/GCM is an also an [authenticated encryption](https://en.wikipedia.org/wiki/Authenticated_encryption)
    algorithm that provides both authenticity (integrity) and confidentiality.

    When using AES/GCM to encrypt there are three inputs und two outputs:

    inputs:
    - key
    - cleartext
    - initialization vector (IV)

    outputs
    - ciphertext
    - authentication tag

    The initialization vector should be chosen such that a unique value
    is used for every encryption performed with the same key.
    Typical IV values are random-bit-generated with a size of 96 bit.

    The authentication tag can be used in decryption to verify that the ciphertext has
    not been tampered with.

    To decrypt a ciphertext the IV and authentication tag value have to also be provideded.

    Both IV and authentication tag are not secret. The IV has to be chosen such that it can
    not be guessed.

    AES/GCM does not require padding, the ciphertext has the same length as the cleartext.

    \see AesGcmEncryption, AesGcmDecryption, AesGcmDecryptionHelper, AesGcmDecryptionHelper
 */

    //! \internal
    //! Internal base to AES/GCM encryption and decryption classes
    class UTIL_EXPORT AesGcmBase {

        public:
            //! We always use the full authentication tag (16 byte, 128 bit)
            static constexpr size_t authentication_tag_size = 16;
            //! default IV is 12 byte, 96 bit long
            static constexpr size_t default_iv_size = 12;

            //! @name interoperable format special characters
            ///@{
            //! the start, separator and end characters of the interoperable format
            //! of AesGcmEncryptionHalper and AesGcmDecryptionHelper
            static constexpr char interop_start_char        = '{';
            static constexpr char interop_separator_char    = ',';
            static constexpr char interop_end_char          = '}';
            ///@}

            //! @name valid AES key length values in byte
            //! AES allows 128, 129, 256 bit sized keys.
            ///@{
            static constexpr size_t aes_key_128_bit_len = 16;
            static constexpr size_t aes_key_192_bit_len = 24;
            static constexpr size_t aes_key_256_bit_len = 32;
            ///@}

            using Tag = std::array<uint8_t, authentication_tag_size>;

            static ipl::ErrorType error;

            struct Reason {
                enum {
                    invalid_key_size,   //!< \brief Key size is not one the vaild AES key sizes
                    init_error,         //!< \brief error in cryptographic context initialisation
                    encrypt_error,      //!< \brief error in the encryption operation
                    decrypt_error,      //!< \brief error in the decryption operation
                    no_cipher_set,      //!< \brief cipher is not set
                    auth_tag_error,     //!< \brief error in the authentication tag step of encryption/decryption
                    iv_not_set,         //!< \brief no iv set for decryption
                    invalid_parameters, //!< \brief invalid parameters
                    base64_error,       //!< \brief error in base64 decoding
                };
            };


            //! \brief returns true if the constructor ha an error.
            bool hasError() const { return m_error; }

            //! \brief Fills the passed buffer with randomly generated bits usable as an initialization vector.
            //!
            //! returns true and raises on error
            static bool randomIv(uint8_t* iv_data, size_t size) IPL_NOEXCEPT;

        protected:
            //! \brief Initializes some context for cryptographic operations.
            //!
            //! Instances can't be copied, but moved.
            AesGcmBase() IPL_NOEXCEPT;
            ~AesGcmBase() IPL_NOEXCEPT;

            AesGcmBase(const AesGcmBase&) = delete;
            AesGcmBase& operator=(const AesGcmBase&) = delete;

            AesGcmBase(AesGcmBase&&) = default;
            AesGcmBase& operator=(AesGcmBase&&) = default;

            static ipl::ErrorID error_table[];

            EVP_CIPHER_CTX*                         m_ctx{nullptr};
            const EVP_CIPHER*                       m_cipher{nullptr};
            const char*                             m_cipher_name{nullptr};
            bool                                    m_error{false};

            std::vector<uint8_t>                    m_key{};

            // Copies the key data. Checks for valid sizes
            bool copyKey(const uint8_t* key_data, size_t key_size) IPL_NOEXCEPT;

            std::vector<uint8_t>                    m_iv;

            bool setIv(const uint8_t* key_data, size_t key_size) IPL_NOEXCEPT;

#if !defined(HAVE_SSL) || !defined(BUILD_UTIL_WITH_CRYPTO)
        protected:
            static bool raiseNoSslError();
#endif
    };
}
}

#endif  // UTIL_CRYPT_AESGCMBASE_HXX
