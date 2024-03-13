/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

//
// UUID.h
//
// Library: Foundation
// Package: UUID
// Module:  UUID
//
// Definition of the UUID class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:    BSL-1.0
//

// Adapted for the e.solutions framework

#ifndef IPL_UUID_HXX
#define IPL_UUID_HXX


#include <ipl_config.h>
#include <common/iplcommon_dso.h>
#include <common/ipl_namespace.hxx>
#include <common/Macros.hxx>
#include <common/types/utility.hxx>
#include <common/stdint.h>
#include <common/CommonError.hxx>
#include <string>

namespace IPL_NAMESPACE {



class IPLCOMMON_EXPORT UUID
    /// A UUID is an identifier that is unique across both space and time,
    /// with respect to the space of all UUIDs. Since a UUID is a fixed
    /// size and contains a time field, it is possible for values to
    /// rollover (around A.D. 3400, depending on the specific algorithm
    /// used). A UUID can be used for multiple purposes, from tagging
    /// objects with an extremely short lifetime, to reliably identifying
    /// very persistent objects across a network.
    ///
    /// This class implements a Universal Unique Identifier,
    /// as specified in Appendix A of the DCE 1.1 Remote Procedure
    /// Call Specification (http://www.opengroup.org/onlinepubs/9629399/),
    /// RFC 2518 (WebDAV), section 6.4.1 and the UUIDs and GUIDs internet
    /// draft by Leach/Salz from February, 1998
    /// (http://www.ics.uci.edu/~ejw/authoring/uuid-guid/draft-leach-uuids-guids-01.txt)
    /// and also http://tools.ietf.org/html/draft-mealling-uuid-urn-05
{
public:
    enum Errors { PARSE_ERROR };
    static ErrorType Error;

    enum Version
    {
        UUID_TIME_BASED      = 0x01,
        UUID_DCE_UID         = 0x02,
        UUID_NAME_BASED      = 0x03,
        UUID_RANDOM          = 0x04,
        UUID_NAME_BASED_SHA1 = 0x05,
        UUID_NON_STD_ESO_SEMVER = 0x06

    };

    static const size_t BYTE_LEN=16;

    UUID() IPL_NOEXCEPT;
        /// Creates a nil (all zero) UUID.

    UUID(const UUID& uuid) IPL_NOEXCEPT;
        /// Copy constructor.

    explicit UUID(const std::string& uuid) IPL_NOEXCEPT;
        /// Parses the UUID from a string.

    explicit UUID(const char* uuid) IPL_NOEXCEPT;
        /// Parses the UUID from a string.

    UUID(uint32_t timeLow, uint32_t timeMid,
         uint32_t timeHiAndVersion, uint16_t clockSeq,
         uint8_t node0, uint8_t node1,
         uint8_t node2, uint8_t node3,
         uint8_t node4, uint8_t node5) IPL_NOEXCEPT:
        m_parse_error(false),
        timeLow(timeLow),
        timeMid((uint16_t)timeMid),
        timeHiAndVersion((uint16_t)timeHiAndVersion),
        clockSeq(clockSeq) {
        node[0]=node0;
        node[1]=node1;
        node[2]=node2;
        node[3]=node3;
        node[4]=node4;
        node[5]=node5;
    }

    UUID(const uint8_t* bytes, Version version) IPL_NOEXCEPT;

    ~UUID() IPL_NOEXCEPT;
        /// Destroys the UUID.

    UUID& operator = (const UUID& uuid) IPL_NOEXCEPT;
        /// Assignment operator.

    void swap(UUID& uuid) IPL_NOEXCEPT;
        /// Swaps the UUID with another one.

    bool parse(const std::string& uuid) IPL_NOEXCEPT;
        /// Parses the UUID from its string representation.

    bool tryParse(const std::string& uuid) IPL_NOEXCEPT;
        /// Tries to interpret the given string as an UUID.
        /// If the UUID is syntactically valid, assigns the
        /// members and returns true. Otherwise leaves the
        /// object unchanged and returns false.

    std::string toString() const IPL_NOEXCEPT;
        /// Returns a string representation of the UUID consisting
        /// of groups of hexadecimal digits separated by hyphens.

    void copyFrom(const char* buffer) IPL_NOEXCEPT;
        /// Copies the UUID (16 bytes) from a buffer or byte array.
        /// The UUID fields are expected to be
        /// stored in network byte order.
        /// The buffer need not be aligned.

    void copyTo(char* buffer) const IPL_NOEXCEPT;
        /// Copies the UUID to the buffer. The fields
        /// are in network byte order.
        /// The buffer need not be aligned.
        /// There must have room for at least 16 bytes.

    Version version() const IPL_NOEXCEPT;
        /// Returns the version of the UUID.

    int variant() const IPL_NOEXCEPT;
        /// Returns the variant number of the UUID:
        ///   - 0 reserved for NCS backward compatibility
        ///   - 2 the Leach-Salz variant (used by this class)
        ///   - 6 reserved, Microsoft Corporation backward compatibility
        ///   - 7 reserved for future definition

    bool operator == (const UUID& uuid) const IPL_NOEXCEPT;
    bool operator != (const UUID& uuid) const IPL_NOEXCEPT;
    bool operator <  (const UUID& uuid) const IPL_NOEXCEPT;
    bool operator <= (const UUID& uuid) const IPL_NOEXCEPT;
    bool operator >  (const UUID& uuid) const IPL_NOEXCEPT;
    bool operator >= (const UUID& uuid) const IPL_NOEXCEPT;

    bool isNull() const IPL_NOEXCEPT;
        /// Returns true iff the UUID is nil (in other words,
        /// consists of all zeros).
//     IPL_DEPRECATED("use isNull() instead",
//                    bool isNil() const IPL_NOEXCEPT) { return isNull(); }
    IPL_DEPRECATED("use isNull() instead",
                   bool isNil() const IPL_NOEXCEPT) { return isNull(); }

    bool parseError() const IPL_NOEXCEPT { return m_parse_error; }

    static const UUID& null() IPL_NOEXCEPT;
        /// Returns a null/nil UUID.
    IPL_DEPRECATED("use null() instead",
                   static const UUID &nil() IPL_NOEXCEPT) { return null(); }

    static const UUID& dns() IPL_NOEXCEPT;
        /// Returns the namespace identifier for the DNS namespace.

    static const UUID& uri() IPL_NOEXCEPT;
        /// Returns the namespace identifier for the URI (former URL) namespace.

    static const UUID& oid() IPL_NOEXCEPT;
        /// Returns the namespace identifier for the OID namespace.

    static const UUID& x500() IPL_NOEXCEPT;
        /// Returns the namespace identifier for the X500 namespace.

protected:
    UUID(uint32_t timeLow, uint32_t timeMid, uint32_t timeHiAndVersion, uint16_t clockSeq, uint8_t node[]) IPL_NOEXCEPT;
//     UUID(const char* bytes, Version version) IPL_NOEXCEPT;
    int compare(const UUID& uuid) const IPL_NOEXCEPT;
    static void appendHex(std::string& str, uint8_t n) IPL_NOEXCEPT;
    static void appendHex(std::string& str, uint16_t n) IPL_NOEXCEPT;
    static void appendHex(std::string& str, uint32_t n) IPL_NOEXCEPT;
    static int16_t nibble(char hex) IPL_NOEXCEPT;
    void fromNetwork() IPL_NOEXCEPT;
    void toNetwork() IPL_NOEXCEPT;

    static const ErrorID ERROR_TABLE[];

    bool m_parse_error;

public:
    uint32_t timeLow;
    uint16_t timeMid;
    uint16_t timeHiAndVersion;
    uint16_t clockSeq;
    uint8_t  node[6];

};


//
// inlines
//
inline bool UUID::operator == (const UUID& uuid) const IPL_NOEXCEPT
{
    return compare(uuid) == 0;
}


inline bool UUID::operator != (const UUID& uuid) const IPL_NOEXCEPT
{
    return compare(uuid) != 0;
}


inline bool UUID::operator < (const UUID& uuid) const IPL_NOEXCEPT
{
    return compare(uuid) < 0;
}


inline bool UUID::operator <= (const UUID& uuid) const IPL_NOEXCEPT
{
    return compare(uuid) <= 0;
}


inline bool UUID::operator > (const UUID& uuid) const IPL_NOEXCEPT
{
    return compare(uuid) > 0;
}


inline bool UUID::operator >= (const UUID& uuid) const IPL_NOEXCEPT
{
    return compare(uuid) >= 0;
}


inline UUID::Version UUID::version() const IPL_NOEXCEPT
{
    return Version(timeHiAndVersion >> 12);
}


inline bool UUID::isNull() const IPL_NOEXCEPT
{
    return compare(null()) == 0;
}


inline void swap(UUID& u1, UUID& u2) IPL_NOEXCEPT
{
    u1.swap(u2);
}


} // namespace IPL_NAMESPACE


#endif // IPL_UUID_HXX
