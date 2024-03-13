//
// SHA1Engine.h
//
// Library: Foundation
// Package: Crypt
// Module:  SHA1Engine
//
// Definition of class SHA1Engine.
//
// Secure Hash Standard SHA-1 algorithm
// (FIPS 180-1, see http://www.itl.nist.gov/fipspubs/fip180-1.htm)
//
// Based on the public domain implementation by Peter C. Gutmann
// on 2 Sep 1992, modified by Carl Ellison to be SHA-1.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:    BSL-1.0
//

// Adapted for the e.solutions framework

#ifndef IPL_SHA1ENGINE_HXX
#define IPL_SHA1ENGINE_HXX


#include "DigestEngine.hxx"
#include <common/stdint.h>


namespace util {


class UTIL_EXPORT SHA1Engine: public DigestEngine
    /// This class implementes the SHA-1 message digest algorithm.
    /// (FIPS 180-1, see http://www.itl.nist.gov/fipspubs/fip180-1.htm)
{
public:
    enum
    {
        BLOCK_SIZE  = 64,
        DIGEST_SIZE = 20
    };

    SHA1Engine() IPL_NOEXCEPT;
    ~SHA1Engine() IPL_NOEXCEPT;

    std::size_t digestLength() const IPL_NOEXCEPT;
    void reset() IPL_NOEXCEPT;
    const DigestEngine::Digest& digest() IPL_NOEXCEPT;

protected:
    void updateImpl(const void* data, std::size_t length) IPL_NOEXCEPT;

private:
    void transform() IPL_NOEXCEPT;
    static void byteReverse(uint32_t* buffer, int byteCount) IPL_NOEXCEPT;

    typedef uint8_t BYTE;

    struct Context
    {
        uint32_t digest[5]; // Message digest
        uint32_t countLo;   // 64-bit bit count
        uint32_t countHi;
        uint32_t data[16];  // SHA data buffer
        uint32_t slop;      // # of bytes saved in data[]
    };

    Context _context;
    DigestEngine::Digest _digest;

    SHA1Engine(const SHA1Engine&);
    SHA1Engine& operator = (const SHA1Engine&);
};


} // namespace util


#endif // IPL_SHA1ENGINE_HXX
