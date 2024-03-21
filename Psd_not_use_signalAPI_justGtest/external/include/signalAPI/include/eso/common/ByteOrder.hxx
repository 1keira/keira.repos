/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_BYTEORDER_HXX
#define IPL_BYTEORDER_HXX

// definition of byte order conversion macros and other byte handling specific macros

#include <ipl_config.h>

//! Create 16 bit word from two 8 bit input values
#define IPL_MAKE_UINT16(hiByte,loByte)    ((uint16_t)((((uint16_t)(hiByte))<<8)| \
                    ((uint16_t)(loByte))))

//! Create 32 bit double-word from four 8 bit input values
#define IPL_MAKE_UINT32(hiHiByte,hiLoByte,loHiByte,loLoByte) \
                    ((uint32_t)((((uint32_t)(hiHiByte))<<24)| \
                    (((uint32_t)(hiLoByte))<<16)| \
                    (((uint32_t)(loHiByte))<<8) | \
                    ((uint32_t)(loLoByte))))

//! Return high byte from 16 bit value
#define IPL_GETHIBYTE_16(data)        ((uint8_t)(((uint16_t)(data))>>8))

//! Return lowest byte from > 8 bit value
#define IPL_GETLOWESTBYTE(data)        ((uint8_t)(data))

//! Return highest 8 bit from 32 bit value
#define IPL_GETHIBYTEHI_32(data)        ((uint8_t)(((uint32_t)(data))>>24))

//! Return high 8 bit from lower word of 32 bit value
#define IPL_GETHIBYTELO_32(data)        ((uint8_t)(((uint32_t)(data))>>8))

//! Return lower 8 bit from upper word of 32 bit value
#define IPL_GETLOBYTEHI_32(data)        ((uint8_t)(((uint32_t)(data))>>16))

//! Unconditionally invert byte order of uint16
#define SWITCH_BYTEORDER_UINT16(A) ((uint16_t)(((uint16_t)(A) & 0xff00) >> 8) | \
    (uint16_t)(((uint16_t)(A) & 0x00ff) << 8))

//! Unconditionally invert byte order of uint32
#define SWITCH_BYTEORDER_UINT32(A) ((((uint32_t)(A) & 0xff000000) >> 24) | \
    (((uint32_t)(A) & 0x00ff0000) >> 8) | \
    (((uint32_t)(A) & 0x0000ff00) << 8) | \
    (((uint32_t)(A) & 0x000000ff) << 24))

//! Unconditionally invert byte order of uint16
#define SWITCH_BYTEORDER_UINT64(A) ((((uint64_t)(A) & 0xff00000000000000ULL) >> 56) | \
    (((uint64_t)(A) & 0x00ff000000000000ULL) >> 40) | \
    (((uint64_t)(A) & 0x0000ff0000000000ULL) >> 24) | \
    (((uint64_t)(A) & 0x000000ff00000000ULL) >> 8) | \
    (((uint64_t)(A) & 0x00000000ff000000ULL) << 8) | \
    (((uint64_t)(A) & 0x0000000000ff0000ULL) << 24) | \
    (((uint64_t)(A) & 0x000000000000ff00ULL) << 40) | \
    (((uint64_t)(A) & 0x00000000000000ffULL) << 56))


#if defined (IPL_FW_BIG_ENDIAN) && !defined(IPL_FW_LITTLE_ENDIAN)
    //! host to network translation of an unsigned int16_t (on big endian)
#    define IPL_HTON_UINT16(A) (A)
    //! host to network translation of an unsigned int32_t (on big endian)
#    define IPL_HTON_UINT32(A) (A)
    //! host to network translation of an unsigned int64_t (on big endian)
#    define IPL_HTON_UINT64(A) (A)
    //! network to host translation of an unsigned int16_t (on big endian)
#    define IPL_NTOH_UINT16(A) (A)
    //! network to host translation of an unsigned int32_t (on big endian)
#    define IPL_NTOH_UINT32(A) (A)
    //! network to host translation of an unsigned int64_t (on big endian)
#    define IPL_NTOH_UINT64(A) (A)

    //! convert to little-endian uint16
#    define IPL_TO_LE_UINT16 SWITCH_BYTEORDER_UINT16
    //! convert to little-endian uint32
#    define IPL_TO_LE_UINT32 SWITCH_BYTEORDER_UINT32
    //! convert to little-endian uint64
#    define IPL_TO_LE_UINT64 SWITCH_BYTEORDER_UINT64
    //! convert to big-endian uint16
#    define IPL_TO_BE_UINT16(A) A
    //! convert to big-endian uint32
#    define IPL_TO_BE_UINT32(A) A
    //! convert to big-endian uint64
#    define IPL_TO_BE_UINT64(A) A

#elif defined (IPL_FW_LITTLE_ENDIAN) && !defined (IPL_FW_BIG_ENDIAN)
    //! host to network translation of an unsigned int16_t (on little endian)
#    define IPL_HTON_UINT16 SWITCH_BYTEORDER_UINT16

//! host to network translation of an unsigned int32_t (on little endian)
#    define IPL_HTON_UINT32 SWITCH_BYTEORDER_UINT32
    //! host to network translation of an unsigned int64_t (on little endian)
#    define IPL_HTON_UINT64 SWITCH_BYTEORDER_UINT64
    //! network to host translation of an unsigned int16_t (on little endian)
#    define IPL_NTOH_UINT16 IPL_HTON_UINT16

    //! network to host translation of an unsigned int32_t (on little endian)
#    define IPL_NTOH_UINT32 IPL_HTON_UINT32

    //! network to host translation of an unsigned int64_t (on little endian)
#    define IPL_NTOH_UINT64 IPL_HTON_UINT64

    //! convert to little-endian uint16
#    define IPL_TO_BE_UINT16 SWITCH_BYTEORDER_UINT16
    //! convert to little-endian uint32
#    define IPL_TO_BE_UINT32 SWITCH_BYTEORDER_UINT32
    //! convert to little-endian uint64
#    define IPL_TO_BE_UINT64 SWITCH_BYTEORDER_UINT64
    //! convert to big-endian uint16
#    define IPL_TO_LE_UINT16(A) A
    //! convert to big-endian uint32
#    define IPL_TO_LE_UINT32(A) A
    //! convert to big-endian uint64
#    define IPL_TO_LE_UINT64(A) A

#else

#error Inconsistent IPL_FW_*_ENDIAN defines

#endif //ENDIANESS

#endif
