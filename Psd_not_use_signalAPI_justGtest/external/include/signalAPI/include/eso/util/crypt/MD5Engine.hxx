//
// MD5Engine.h
//
// Library: Foundation
// Package: Crypt
// Module:  MD5Engine
//
// Definition of class MD5Engine.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:    BSL-1.0
//
//
// MD5 (RFC 1321) algorithm:
// Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
// rights reserved.
//
// License to copy and use this software is granted provided that it
// is identified as the "RSA Data Security, Inc. MD5 Message-Digest
// Algorithm" in all material mentioning or referencing this software
// or this function.
//
// License is also granted to make and use derivative works provided
// that such works are identified as "derived from the RSA Data
// Security, Inc. MD5 Message-Digest Algorithm" in all material
// mentioning or referencing the derived work.
//
// RSA Data Security, Inc. makes no representations concerning either
// the merchantability of this software or the suitability of this
// software for any particular purpose. It is provided "as is"
// without express or implied warranty of any kind.
//
// These notices must be retained in any copies of any part of this
// documentation and/or software.
//

// Adapted for the e.solutions framework


#ifndef IPL_MD5ENGINE_HXX
#define IPL_MD5ENGINE_HXX


#include "DigestEngine.hxx"
#include <common/stdint.h>


namespace util {


class UTIL_EXPORT MD5Engine: public DigestEngine
    /// This class implementes the MD5 message digest algorithm,
    /// described in RFC 1321.
{
public:
    enum
    {
        BLOCK_SIZE  = 64,
        DIGEST_SIZE = 16
    };

    MD5Engine() IPL_NOEXCEPT;
    ~MD5Engine() IPL_NOEXCEPT;

    std::size_t digestLength() const IPL_NOEXCEPT;
    void reset() IPL_NOEXCEPT;
    const DigestEngine::Digest& digest() IPL_NOEXCEPT;

protected:
    void updateImpl(const void* data, std::size_t length) IPL_NOEXCEPT;

private:
    static void transform(uint32_t state[4], const unsigned char block[64]) IPL_NOEXCEPT;
    static void encode(unsigned char* output, const uint32_t* input, std::size_t len) IPL_NOEXCEPT;
    static void decode(uint32_t* output, const unsigned char* input, std::size_t len) IPL_NOEXCEPT;

    struct Context
    {
        uint32_t state[4];          // state (ABCD)
        uint32_t count[2];          // number of bits, modulo 2^64 (lsb first)
        unsigned char buffer[64]; // input buffer
    };

    Context _context;
    DigestEngine::Digest _digest;

    MD5Engine(const MD5Engine&);
    MD5Engine& operator = (const MD5Engine&);
};


} // namespace util


#endif // IPL_MD5ENGINE_HXX
