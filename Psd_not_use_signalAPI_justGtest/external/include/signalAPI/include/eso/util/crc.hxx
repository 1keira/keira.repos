/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef UTIL_CRC_HXX
#define UTIL_CRC_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include "util_dso.h"
#include <common/types/vector.hxx>
#include <stdlib.h>

/*****************************************************************************/
/*!
    \page crc-page CRCs

    CRC is a family of checksum algorithms over a stream of bits.
    We provide a variety of CRC engines that calculate CRCs of different
    width over a sequence of bytes.

    \section Crc-using-page Using a readymade CRC engine

    All concrete CRC engines ultimately inherit the
    \ref util::Crc "generic CRC engine",
    so refer there for interface documentation.
    The main idea is that you create an object of one of the engine classes
    and call it (i.e. invoke its standard operator).
    Creating the engine is a bit expensive, as it creates lookup tables,
    so you should avoid creating a new engine for each checksum.
    Rather create an engine once and reuse it.

    The result of calculating a CRC is a sequence of bytes (of suitable width).
    This allows you to easily concatenate the checksum to a data buffer.
    If you need to interpret the checksum as single integer number
    for whatever reason, consider the first byte to be the most significant one,
    i.e. Big Endian or Network Byte Order.

    If you only need a specific CRC width but no specific algorithm,
    check out util::Crc8, util::Crc16, util::Crc24, util::Crc32, util::Crc40
    and util::Crc64.
    If you do need a specific algorithm, look for classes in \ref util
    beginning with "Crc" or for children of util::Crc.

    \subsection crc-buffer-page Checksumming a buffer

    A buffer is represented as a pointer and a size (number of bytes).
    The easiest way to calculate a CRC over a buffer is this:
    \code
    util::Crc32 engine;
    util::Crc32::Bytes crc=engine(buf, len);
    \endcode
    util::Crc32::Bytes is a vector of bytes, which means it is easy to use
    but not optimally efficient to kick around.

    So if you care a bit more for efficiency, use a preallocated buffer:
    \code
    util::Crc32 engine;
    unsigned char crc[engine.WIDTH];  // Crc32's width is 4 of course
    engine(buf, len, crc);
    \endcode

    \subsection crc-stream-page Checksumming a stream

    If you need to calculate a CRC incrementally, you can use the
    \ref util::Crc::process "process()" method,
    but you need to call \ref util::Crc::precondition "precondition()"
    before and \ref util::Crc::postcondition "postcondition()" after:
    \code
    util::Crc32 engine;
    unsigned char crc[engine.WIDTH];
    engine.precondition(crc);           // initialize the crc buffer
    for(whatever)
        engine.process(buf, len, crc);  // eat a chunk of data
    engine.postcondition(crc);          // apply final magic to the crc buffer
    \endcode

    \section crc-generic-page Using the generic CRC engine

    When you just need some CRC, you will be happy with Crc32 and friends.
    If you need a specific CRC algorithm,
    chances are that it is already provided.
    But if it isn't, you can still use the generic CRC engine util::Crc.

    The generic engine follows the Rocksoft<sup>TM</sup> Model CRC Algorithm
    as described in http://www.ross.net/crc/download/crc_v3.txt
    and uses the same parameters -- almost.
    The important difference is that the \c width according to the model
    would be in bits,
    while util::Crc's width is in \e bytes -- we do not support CRCs
    not divisible by eight.
    I.e. no Crc12 for you!

    A whole lot of different CRC algorithms are described in the
    <em>Catalogue of parametrised CRC algorithms</em> at
    http://reveng.sourceforge.net/crc-catalogue.
    The parameters are directly usable with util::Crc, except that the
    hex numbers need to be converted into byte arrays in network byte order.
    I.e. a \c poly of \c 0x04c11db7 becomes
    <code>{0x04, 0xc1, 0x1d, 0xb7}</code>.

    Have a look at the definitions of the predefined Crc classes
    (like util::Crc32) to see how it is done.

    \subsection crc-residuum-page Checking a message by residuum

    You already know everything you need to calculate a data buffer's CRC
    and compare that with a CRC that came with the data,
    so you need not read this.

    There is the custom of appending a CRC checksum to a message
    so that the CRC of the \e whole \e thing results in some constant residue.
    This implementation does not support this mode of residual checking,
    as it would require a calculation mode without appending zeros
    (if you don't know what I'm talking about, you need not know).
    While you can easily feed the whole message through the CRC engine,
    the result will be funnily distorted with respect to the residual value
    you would expect from an appropriate calculation,
    so it is up to you to know the value and byte orderto check against.

    And be aware that this method won't probably work as expected with
    \c REFOUT=true anyway.
    In short: Don't do it.
*/
/*****************************************************************************/

namespace util {

/*****************************************************************************/

    /*!
        \brief Generic CRC engine

        A CRC engine has no internal state, so it is safe to reuse it
        or even use it from different threads simultaneously.

        This engine needs to be parameterized to implement a specific
        CRC algorithm.
        This is black art, so you do not want to do this.
        You want to use readymade engines instead,
        i.e. one of the classes inheriting this.

        \see \ref crc-page %for an overview
    */
    class UTIL_EXPORT Crc {

    public:

        typedef ipl::vector<unsigned char> Bytes;

        /*!
            Note that this constructor is somewhat expensive,
            as it calculates a lookup table.
            Therefore if you need to calculate multiple CRCs,
            you should create only \e one engine and reuse it.

            The parameters follow the Rocksoft<sup>TM</sup> Model CRC Algorithm
            (http://www.ross.net/crc/download/crc_v3.txt),
            like those in the Catalogue of parametrised CRC algorithms
            (http://reveng.sourceforge.net/crc-catalogue).
            Only difference is that the \a width_in_bytes is in bytes (duh!),
            not bits.
        */
        Crc(unsigned width_in_bytes, const void *polynomial, const void *init,
            bool reflect_input, bool reflect_output, const void *xor_output) IPL_NOEXCEPT;

        /*!
            \brief Dirt-simple way to calculate a CRC

            Call the engine, hand it a pointer to the \a data to process
            along with the number of \a bytes,
            and you get back a vector with the checksum:
            \code
            util::CrcWhatever engine;
            ipl::vector<unsigned char> crc=engine(buf, len);
            \endcode
            The first byte is usually considered the most significant one
            (big endian, network byte order).

            \see operator()(const void*, size_t, void*) for a more
            efficient way wasting less time copying vectors around

            \see \ref crc-page for an overview
        */
        ipl::vector<unsigned char> operator()(const void *data, size_t bytes) IPL_NOEXCEPT {
            ipl::vector<unsigned char> crc(width);
            operator()(data, bytes, &crc[0]);
            return crc;
        }

        /*!
            \brief Normal way to calculate a CRC

            Call the engine, hand it a pointer to the \a data to process
            along with the number of \a bytes and a pointer where to store
            the \a crc.
            The number of bytes written at \a crc is the width as specified
            in the constructor, i.e. 4 for a Crc32, 2 for a Crc16 etc.

            The first byte of the checksum is usually considered the
            most significant one (big endian, network byte order).
        */
        void operator()(const void *data, size_t bytes, void *crc) IPL_NOEXCEPT {
            precondition(crc);
            process(data, bytes, crc);
            postcondition(crc);
        }

        /*!
            \name Advanced methods for incremental calculation

            When you need to calculate a CRC of some data that is
            never available as one single buffer,
            you cannot use the simple operator().
            Instead you have to manually invoke the three steps:
            \code
            unsigned char checksum[WIDTH];
            engine.precondition(checksum);
            engine.process(chunk1, size1, checksum);
            engine.process(chunk2, size2, checksum);
            engine.process(chunk3, size3, checksum);
            ...
            engine.postcondition(checksum);
            // now checksum contains the CRC of all the chunks
            \endcode

            \{
        */
        //! \brief Initialize \a *crc for calculation
        //!
        //! Internally this sets it to INIT.
        void precondition(void *crc) IPL_NOEXCEPT;
        //! \brief Process data, calculating \a *crc
        //!
        //! This can be called multiple times, e.g. for streamed data.
        //!
        //! Internally this leaves in \a *crc the CRC of the yet processed
        //! byte sequence (including the implicit suffix of zeros) as calculated
        //! by shifting in the (possibly reversed) bytes from the low end.
        void process(const void *data, size_t bytes, void *crc) IPL_NOEXCEPT;
        //! \brief Finalize \a *crc so the value can be used
        //!
        //! Internally this applies any REFOUT and XOROUT parameters to \a *crc.
        void postcondition(void *crc) IPL_NOEXCEPT;
        //!\}

    private:
        //! \brief Access the poly stored in the bytes
        unsigned char *poly()             { return &bytes[width*0]; }
        //! \brief Access a byte of the poly stored in the bytes
        unsigned char &poly(unsigned i)   { return poly()[i]; }
        //! \brief Access a byte of the initial register stored in the bytes
        unsigned char &init(unsigned i)   { return bytes[width*1+i]; }
        //! \brief Access a byte of the postcondition mask stored in the bytes
        unsigned char &xorout(unsigned i) { return bytes[width*2+i]; }
        //! \brief Access an entry of the lookup table stored in the bytes
        unsigned char *table(unsigned i)  { return &bytes[width*(3+i)]; }
        //! \brief Access a byte of the lookup table stored in the bytes
        unsigned char &table(unsigned i, unsigned j) { return table(i)[j]; }

        //! \brief Flip the bits of one byte back-to-front
        unsigned char reflect(unsigned char c) {
            return (unsigned char) ((c & 0x01u) << 7) |
                   (unsigned char) ((c & 0x02u) << 5) |
                   (unsigned char) ((c & 0x04u) << 3) |
                   (unsigned char) ((c & 0x08u) << 1) |
                   (unsigned char) ((c & 0x10u) >> 1) |
                   (unsigned char) ((c & 0x20u) >> 3) |
                   (unsigned char) ((c & 0x40u) >> 5) |
                   (unsigned char) ((c & 0x80u) >> 7) ;
        }
        //! \brief Flip a bitstream of width bytes back-to-front
        void reflect(void *here) {
            for(unsigned i=0; i<width/2; i++) {
                unsigned char c=((unsigned char *)here)[i];
                ((unsigned char *)here)[i]=reflect(((unsigned char *)here)[width-1-i]);
                ((unsigned char *)here)[width-1-i]=reflect(c);
            }
            if(width%2)  // middle of odd number
                ((unsigned char *)here)[width/2]=reflect(((unsigned char *)here)[width/2]);
        }
        //! \brief Xor a \a mask into width bytes
        void flip_bits(unsigned char *here, unsigned char *mask) {
            for(unsigned i=0; i<width; i++)
                here[i]^=mask[i];
        }
        //! \brief Shift a bitstream of width bytes one bit to the left
        //! (i.e. towards the MSB and towards byte 0)
        bool lshift(unsigned char *here) {
            unsigned char carry=0;
            for(unsigned i=width; i>0; i--) {
                unsigned char c=here[i-1]&0x80;
                here[i-1]=(unsigned char)(((unsigned)here[i-1])<<1)|(unsigned)carry;
                carry=c? 1 : 0;
            }
            return carry;
        }

        const unsigned width;
        const bool refin;
        const bool refout;

        //! \brief Storage for poly, init, xorout and table,
        //! unified to cut down heap allocation
        Bytes bytes;
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for an 8 bit CRC
    */
    class UTIL_EXPORT Crc8Itu: public Crc {

    public:
        static const unsigned      WIDTH=1;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc8Itu() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 16 bit crc
    */
    class UTIL_EXPORT Crc16Ansi: public Crc {

    public:
        static const unsigned      WIDTH=2;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc16Ansi() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 16 bit CRC as implemented in the Kermit protocol
    */
    class UTIL_EXPORT Crc16Kermit: public Crc {

    public:
        static const unsigned      WIDTH=2;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc16Kermit() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 16 bit CRC as implemented in the XModem protocol
    */
    class UTIL_EXPORT Crc16Xmodem: public Crc {

    public:
        static const unsigned      WIDTH=2;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc16Xmodem() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 24 bit CRC as used by OpenPGP
    */
    class UTIL_EXPORT Crc24OpenPgp: public Crc {

    public:
        static const unsigned      WIDTH=3;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc24OpenPgp() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for \b the 32 bit CRC as used in ZIP files,
        Ethernet and just about everywhere
    */
    class UTIL_EXPORT Crc32Ieee802: public Crc {

    public:
        static const unsigned      WIDTH=4;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc32Ieee802() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 32 bit CRC as used in bzip2
    */
    class UTIL_EXPORT Crc32Bzip2: public Crc {

    public:
        static const unsigned      WIDTH=4;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc32Bzip2() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for yet another 32 bit CRC
    */
    class UTIL_EXPORT Crc32Castagnoli: public Crc {

    public:
        static const unsigned      WIDTH=4;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc32Castagnoli() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 32 bit CRC as used in MPEG2
    */
    class UTIL_EXPORT Crc32Mpeg2: public Crc {

    public:
        static const unsigned      WIDTH=4;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc32Mpeg2() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 32 bit CRC as used in POSIX chksum
    */
    class UTIL_EXPORT Crc32Posix: public Crc {

    public:
        static const unsigned      WIDTH=4;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc32Posix() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 40 bit CRC (used in cell phones?)
    */
    class UTIL_EXPORT Crc40Gsm: public Crc {

    public:
        static const unsigned      WIDTH=5;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc40Gsm() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \brief CRC engine for a 64 bit CRC as used on DLT-1 backup tapes
    */
    class UTIL_EXPORT Crc64Ecma182: public Crc {

    public:
        static const unsigned      WIDTH=8;
        typedef unsigned char      CRC[WIDTH];

        static const unsigned char POLY[];
        static const unsigned char INIT[];
        static const bool          REFIN;
        static const bool          REFOUT;
        static const unsigned char XOROUT[];
        static const unsigned char CHECK[];

        Crc64Ecma182() IPL_NOEXCEPT: Crc(WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) {}
    };

/*****************************************************************************/

    /*!
        \name Default engines for CRCs of various length

        \{
    */
    typedef Crc8Itu         Crc8;
    typedef Crc16Ansi       Crc16;
    typedef Crc24OpenPgp    Crc24;
    typedef Crc32Ieee802    Crc32;  //!< \brief \b The CRC
    typedef Crc40Gsm        Crc40;
    typedef Crc64Ecma182    Crc64;
    //! \}

    typedef Crc32Ieee802    Crc32Zip;
    typedef Crc32Castagnoli Crc32Rfc3720;

/*****************************************************************************/

}  // end of namespace util

/*****************************************************************************/
#endif
