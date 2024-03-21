/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CRYPT_AESGCMDECRYPTIONHELPER_HXX
#define UTIL_CRYPT_AESGCMDECRYPTIONHELPER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <common/error/Error.hxx>
#include <common/unicode.hxx>
#include <common/buffers.hxx>
#include <util/crypt/AesGcmDecryption.hxx>

#include <string>

namespace util {
namespace crypt {


    //! \brief Convenience class for one-line decryption with AES/GCM.
    //!
    //! This class uses AesGcmDecryption to decrypt the output of AesGcmEncryptionHelper
    //! or the output of the interoperable Java implementation in package
    //! ``de.esolutions.extfw.persistence.encryption`` with decryptString().
    //!
    //! decryptString() returns the decrypted cleartext.
    //!
    //! decryptBuffer() decrypts the output of AesGcmDecryptionHelper::encryptBuffer().
    //!
    //! For decryptBuffer() the caller has to provide an appropriately sized buffer
    //! in the call in form of a uint8_t pointer, size pair, a std::vector, a std::array
    //! or an ipl::SharedBuf.
    //!
    //! Get the required output buffer size for decryptBuffer() with getOutputBufferSize().
    //!
    //! Both calls verify the authentication tag contained in the input.
    //!
    //! \see AesGcmEncryptionHelper
    //! \see \ref util_crypt_aes_gcm
    class UTIL_EXPORT AesGcmDecryptionHelper {
        public:
            AesGcmDecryptionHelper() IPL_NOEXCEPT = default;
            ~AesGcmDecryptionHelper() IPL_NOEXCEPT = default;

            AesGcmDecryptionHelper(const AesGcmDecryptionHelper&) = delete;
            AesGcmDecryptionHelper& operator=(const AesGcmDecryptionHelper&) = delete;

            AesGcmDecryptionHelper(AesGcmDecryptionHelper&&) = default;
            AesGcmDecryptionHelper& operator=(AesGcmDecryptionHelper&&) = default;

            //! \brief Decrypts the input string and returns the the output as a string.
            //!
            //! The input must be a string that contains ciphertext, authentication tag and
            //! iv as produced by AesGcmEncryptionHelper::encryptString() or the
            //! interoperable Java implementation.
            //!
            //! The \a output contains the decrypted input.
            //! The authentication tag contained in the input is verified.
            //!
            //! Returns an empty string and raises in case of errors.
            //! If the input is an empty string, the output is also an
            //! empty string and no error is raised.
            //! \see AesGcmEncryptionHelper::encryptString()
            ipl::unicode::String decryptString(const uint8_t* key_data, size_t key_size,
                                        const std::string& input) IPL_NOEXCEPT;


            //! \brief Decrypts the input buffer into the output buffer.
            //!
            //! The \a input must contain the result of a AesGcmEncryptionHelper::encryptBuffer().
            //!
            //! The necessary \a output size can be determined with getOutputBufferSize().
            //! The call fails if \a output_size is smaller than necessary to hold the
            //! decrypted buffer.
            //!
            //! Returns true and raises in case of errors.
            //! \see AesGcmEncryptionHelper::encryptBuffer(), getOutputBufferSize()
            bool decryptBuffer(const uint8_t* key_data, size_t key_size,
                                const uint8_t* input, size_t input_size,
                                uint8_t* output, size_t output_size) IPL_NOEXCEPT;

            bool decryptBuffer(const uint8_t* key_data, size_t key_size,
                                const uint8_t* input, size_t input_size,
                                std::vector<uint8_t>& output) IPL_NOEXCEPT {
                return decryptBuffer(key_data, key_size, input, input_size,
                                output.data(), output.size());
            }

            template<std::size_t N>
            bool decryptBuffer(const uint8_t* key_data, size_t key_size,
                                const uint8_t* input, size_t input_size,
                                std::array<uint8_t, N>& output) IPL_NOEXCEPT {
                return decryptBuffer(key_data, key_size, input, input_size,
                                output.data(), output.size());
            }

            bool decryptBuffer(const uint8_t* key_data, size_t key_size,
                                const uint8_t* input, size_t input_size,
                                ipl::Buf& output) IPL_NOEXCEPT {
                return decryptBuffer(key_data, key_size, input, input_size,
                                (uint8_t*)output, output.bytes);
            }

            //! \brief Returns true if the constructor failed.
            bool hasError() const IPL_NOEXCEPT { return m_decrypt.hasError(); }

            //! \brief Returns the necessary output buffer size for the cleartext from
            //!  the input size.
            //!
            //! Returns 0 if \a input_size is too small to contain the result of
            //! AesGcmEncryptionHelper::encryptBuffer()
            static size_t getOutputBufferSize(size_t input_size) {
                if ( input_size >
                        (AesGcmBase::default_iv_size + AesGcmBase::authentication_tag_size) ) {
                    return input_size - AesGcmBase::default_iv_size - AesGcmBase::authentication_tag_size;
                }
                return 0;
            }

        private:
            AesGcmDecryption    m_decrypt;
    };
}
}

#endif // UTIL_CRYPT_AESGCMDECRYPTIONHELPER_HXX
