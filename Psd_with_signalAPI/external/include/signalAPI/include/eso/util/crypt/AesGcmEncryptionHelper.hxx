/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CRYPT_AESGCMENCRYPTIONHELPER_HXX
#define UTIL_CRYPT_AESGCMENCRYPTIONHELPER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <common/error/Error.hxx>
#include <common/unicode.hxx>
#include <common/buffers.hxx>
#include <util/crypt/AesGcmEncryption.hxx>

#include <string>
#include <cstdint>

namespace util {
namespace crypt {


    //! \brief Convenience class for one-line encryption with AES/GCM.
    //!
    //! This uses AesGcmEncryption with
    //! - 96 bit long random-bit-genereated initialization vector
    //! - 128 bit long authentication tag
    //!
    //! Both the encryptString() and encryptBuffer() combine the created
    //! ciphertext, authentication tag and initialization vector into one
    //! output.
    //!
    //! encryptString() provides the output as a std::string that consists of
    //! base64-encoded parts with some decoration.
    //! This output format is interoperable with the Java implementation in
    //! package ``de.esolutions.extfw.persistence.encryption``
    //!
    //! For interopreability's sake the encryptString() call accepts only
    //! 256 bit sized keys.
    //! The input unicode string is converted to UTF-8 before encryption.
    //!
    //! Use AesGcmDecryptionHelper::decryptString() to decrypt.
    //!
    //! encryptBuffer() concatenates all three parts into the output buffer.
    //!
    //! Use AesGcmDecryptionHelper::decryptBuffer() to decrypt.
    //!
    //! \see AesGcmDecryptionHelper
    //! \see \ref util_crypt_aes_gcm
    class UTIL_EXPORT AesGcmEncryptionHelper {
        public:
            AesGcmEncryptionHelper() IPL_NOEXCEPT = default;
            ~AesGcmEncryptionHelper() IPL_NOEXCEPT = default;

            AesGcmEncryptionHelper(const AesGcmEncryptionHelper&) = delete;
            AesGcmEncryptionHelper& operator=(const AesGcmEncryptionHelper&) = delete;

            AesGcmEncryptionHelper(AesGcmEncryptionHelper&&) = default;
            AesGcmEncryptionHelper& operator=(AesGcmEncryptionHelper&&) = default;

            //! \brief Encrypts the input string and returns the the output as a string.
            //!
            //! The input is first encoded as a sequence of UTF-8 bytes and then
            //! encrypted.
            //! The \a output contains the encrypted input, the authentication tag and
            //! the IV.
            //!
            //! The output is formatted in a way that is interoperable with a Java implementation.
            //! To be interoperable with Java only keys of size 32 byte/256 bit are allowed here.
            //!
            //! Returns an empty string and raises in case of errors.
            //! If the input is an empty string, the output is also an
            //! empty string and no error is raised.
            std::string encryptString(const uint8_t* key_data, size_t key_size,
                                const ipl::unicode::String& input) IPL_NOEXCEPT;

            //! \brief Encrypts the input buffer and returns the the output buffer.
            //!
            //! The output buffer contains ciphertext, authentication tag and
            //! initialization vector concatenated in that order.
            //!
            //! Returns an empty buffer and raises in case of errors.
            //! If the input is an empty buffer, the output is also an
            //! empty buffer and no error is raised.
            ipl::SharedBuf encryptBuffer(const uint8_t* key_data, size_t key_size,
                                const uint8_t* cleartext, size_t cleartext_size ) IPL_NOEXCEPT;

            bool hasError() const IPL_NOEXCEPT { return m_encrypt.hasError(); }
        private:
            AesGcmEncryption    m_encrypt;
    };
}
}

#endif // UTIL_CRYPT_AESGCMENCRYPTIONHELPER_HXX
