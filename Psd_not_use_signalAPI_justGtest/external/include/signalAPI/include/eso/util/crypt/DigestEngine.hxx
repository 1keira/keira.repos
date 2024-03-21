//
// DigestEngine.h
//
// Library: Foundation
// Package: Crypt
// Module:  DigestEngine
//
// Definition of class DigestEngine.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:    BSL-1.0
//

// Adapted for the e.solutions framework

#ifndef IPL_DIGESTENGINE_HXX
#define IPL_DIGESTENGINE_HXX


#include <util/util_dso.h>
#include <iplbase/exceptions.hxx>

#include <cstddef>
#include <string>
#include <vector>


namespace util {


class UTIL_EXPORT DigestEngine
    /// This class is an abstract base class
    /// for all classes implementing a message
    /// digest algorithm, like MD5Engine
    /// and SHA1Engine.
    /// Call update() repeatedly with data to
    /// compute the digest from. When done,
    /// call digest() to obtain the message
    /// digest.
{
public:
    typedef std::vector<unsigned char> Digest;

    DigestEngine() IPL_NOEXCEPT;
    virtual ~DigestEngine() IPL_NOEXCEPT;

    void update(const void* data, std::size_t length) IPL_NOEXCEPT;
    void update(char data) IPL_NOEXCEPT;
    void update(const std::string& data) IPL_NOEXCEPT;
        /// Updates the digest with the given data.

    virtual std::size_t digestLength() const IPL_NOEXCEPT = 0;
        /// Returns the length of the digest in bytes.

    virtual void reset() IPL_NOEXCEPT = 0;
        /// Resets the engine so that a new
        /// digest can be computed.

    virtual const Digest& digest() IPL_NOEXCEPT = 0;
        /// Finishes the computation of the digest and
        /// returns the message digest. Resets the engine
        /// and can thus only be called once for every digest.
        /// The returned reference is valid until the next
        /// time digest() is called, or the engine object is destroyed.

    static std::string digestToHex(const Digest& bytes) IPL_NOEXCEPT;
        /// Converts a message digest into a string of hexadecimal numbers.

    //! \brief Contrary to Poco this returns an empty Digest on error
    static Digest digestFromHex(const std::string& digest) IPL_NOEXCEPT;
        /// Converts a string created by digestToHex back to its Digest presentation

    static bool constantTimeEquals(const Digest& d1, const Digest& d2) IPL_NOEXCEPT;
        /// Compares two Digest values using a constant-time comparison
        /// algorithm. This can be used to prevent timing attacks
        /// (as discussed in <https://codahale.com/a-lesson-in-timing-attacks/>).

protected:
    virtual void updateImpl(const void* data, std::size_t length) IPL_NOEXCEPT = 0;
        /// Updates the digest with the given data. Must be implemented
        /// by subclasses.

private:
    DigestEngine(const DigestEngine&);
    DigestEngine& operator = (const DigestEngine&);
};


//
// inlines
//


inline void DigestEngine::update(const void* data, std::size_t length) IPL_NOEXCEPT
{
    updateImpl(data, length);
}


inline void DigestEngine::update(char data) IPL_NOEXCEPT
{
    updateImpl(&data, 1);
}


inline void DigestEngine::update(const std::string& data) IPL_NOEXCEPT
{
    updateImpl(data.data(), data.size());
}


} // namespace util


#endif // IPL_DIGESTENGINE_HXX
