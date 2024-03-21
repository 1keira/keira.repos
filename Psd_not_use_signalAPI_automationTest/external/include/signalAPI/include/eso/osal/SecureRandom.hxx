/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SECURERANDOM_HXX
#define OSAL_SECURERANDOM_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>
#include <common/streams/iostream.hxx>
#include <osal/StreamBinFileR.hxx>
#include <osal/osal.hxx>

#ifdef IPL_OS_WIN32
#include <iplbase/win32.h>  // instead of windows.h, see there
#endif

namespace osal
{

/**
 * \brief
 *     Provides access to secure random number generators.

 *     This class provides access to the system specific cryptographic
 *     random number generator. It can get single values and whole blocks
 *     of random data.
 **/

class OSAL_EXPORT SecureRandom:
        public ipl::NonCopyable
{
public:
    /**
     * \brief
     *     enum used for describing quality of random data being returned
     **/
    enum SecRandomQuality
    {
        SECRAND_QUALITY_SECURE,
        SECRAND_QUALITY_UNSAFE
    };

    /**
     * \brief
     *     Creates an SecureRandom object

     *     Opens a nonblocking random device by default
     * \param[in]
     *     canBlock use a blocking or nonblocking random device on posix systems,
     *     in blocking mode the getRand* calls can block an unspecified (very long)
     *     amount of time when waiting for new entropy data.
     * \errors
     *    The StreamBinFileR construction may fail
     * \errorindicator
     *    Via isValid()
    **/
    SecureRandom(bool canBlock = false);

    /**
     * \brief
     *    Frees the resources allocated during construction time
     **/
    ~SecureRandom();

    /**
     * \brief
     *     Returns true if construction of the SecureRandom object was
     *     successful, false otherwise
     **/
    bool isValid();

    /**
     * \brief
     *     Returns the quality of random data available on this system
     **/
    SecRandomQuality GetQuality();

    /**
     * \brief
     *    Read random data into buffer
     * \param[in]
     *    buf buffer to hold random data
     * \param[in]
     *    bufsize size of buf in bytes
     * \return
     *    true on error
     **/
    bool getRandData(uint8_t *buf, const uint32_t bufsize);

    /**
     * \brief
     *    Read byte of random data
     * \param[in]
     *    val variable to hold random data
     * \return
     *    true on error
     **/
    bool getRandByte(uint8_t& val);

    /**
     * \brief
     *    Read uint32 of random data
     * \param[in]
     *    val variable to hold random data
     * \return
     *    true on error
     **/
    bool getRandUInt32(uint32_t& val);

    /**
     * \brief
     *    Read uint32 of random data
     * \param[in]
     *    val variable to hold random data
     * \return
     *    true on error
     **/
    bool getRandUInt64(uint64_t& val);

    bool getRandUInt32_uniform(uint32_t& val, uint32_t upper_bound)
    {
        return getRand_uniform<uint32_t>(val, upper_bound);
    }
    bool getRandUInt64_uniform(uint64_t& val, uint64_t upper_bound)
    {
        return getRand_uniform<uint64_t>(val, upper_bound);
    }

private:

#ifdef IPL_OS_WIN32
    HCRYPTPROV m_hProvider;
#else
    StreamBinFileR m_randFile;
#endif
private:
    /*
     * Copyright (c) 2008, Damien Miller <djm@openbsd.org>
     *
     * Permission to use, copy, modify, and distribute this software for any
     * purpose with or without fee is hereby granted, provided that the above
     * copyright notice and this permission notice appear in all copies.
     *
     * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
     * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
     * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
     * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
     * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
     * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
     * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
     */

    /*
     * Calculate a uniformly distributed random number less than upper_bound
     * avoiding "modulo bias".
     *
     * Uniformity is achieved by generating new random numbers until the one
     * returned is outside the range [0, 2**32 % upper_bound).  This
     * guarantees the selected random number will be inside
     * [2**32 % upper_bound, 2**32) which maps back to [0, upper_bound)
     * after reduction modulo upper_bound.
     */
    template <typename T>
    bool getRand_uniform(T& val, T upper_bound)
    {
            T r, min;

            if (upper_bound < 2)
                    return true;

            /* 2**32 % x == (2**32 - x) % x */
            min = -upper_bound % upper_bound;

            /*
             * This could theoretically loop forever but each retry has
             * p > 0.5 (worst case, usually far better) of selecting a
             * number inside the range we need, so it should rarely need
             * to re-roll.
             */
            for (;;) {
                    if(getRandData((uint8_t*)&r, sizeof(T))) // BRANCH_COVERAGE_UNTESTABLE
                        return true;
                    if (r >= min) // BRANCH_COVERAGE_UNTESTABLE
                            break;
            }
            val = r % upper_bound;
            return false;
    }
}; // end class

} // end namespace

#endif // OSAL_SECURERANDOM_HXX
