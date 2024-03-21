/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef COMMON_UNICODE_HXX
#define COMMON_UNICODE_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include "iplcommon_dso.h"
#include "ipl_namespace.hxx"

#include "PseudoBool.hxx"
#include "buffers.hxx"
#include "stdint.h"
#include "types/string.hxx"
#include "streams/istream.hxx"  // for >>

#include <stddef.h>

#include <common/streams/iostream.hxx>
#include <common/types/iterator.hxx> // for forward_iterator_tag

/*****************************************************************************/

namespace IPL_NAMESPACE {
    namespace unicode {

/*****************************************************************************/

        //! \brief A Unicode "character"
        typedef uint32_t Codepoint;

        //! \brief The Unicode Replacement Character U+fffd
        extern IPLCOMMON_EXPORT const Codepoint REPLACEMENT_CHAR;
        //! \brief The Unicode Byte Order Mark Character U+feff
        extern IPLCOMMON_EXPORT const Codepoint BOM;
        //! \brief The Unicode Not A Character (BOM in wrong byte order) U+fffe
        extern IPLCOMMON_EXPORT const Codepoint MOB;

/*****************************************************************************/

        /*!
            \brief Interface for Unicode codecs to be used with
            ipl::unicode::String

            If you need to implement your own codec, inherit this class,
            implement your stuff, create one static instance and use only that.
            The reason is that certain optimizations (e.g. converting between
            identical codecs) compare codec object address,
            not dynamic codec type.

            You will need to implement the abstract methods, obviously.
            Only overwrite the non-abstract at() method if your implementation
            is more efficient than the default of stepping through the data
            with read_forward(), e.g. because your encoding is fixed-length.
        */
        class IPLCOMMON_EXPORT Codec {

        public:
            /*!
                \internal
                \brief Pointer to a codepoint in a String and the byte(s)
                representing it in the underlying Buf
            */
            struct Index {
                size_t codepoint;
                size_t byte;

                Index(size_t codepoint=0, size_t byte=0) IPL_NOEXCEPT:
                    codepoint(codepoint), byte(byte) {}

                // needed for IPL_ASSERT_EQUALS
                bool operator == (const Index &other) const IPL_NOEXCEPT {
                    return codepoint==other.codepoint && byte==other.byte;
                }
                bool operator != (const Index &other) const IPL_NOEXCEPT {
                    return !operator == (other);
                }
            };

            virtual ~Codec() IPL_NOEXCEPT;

            virtual Codepoint read(const unsigned char *p, size_t bytes,
                                   const Index &index) const IPL_NOEXCEPT=0;
            Codepoint read(const SharedBuf &buf, const Index &index) const IPL_NOEXCEPT {
                return read(buf, buf.bytes(), index);
            }
            //! \brief Increment \a index by \a steps codepoints,
            //! store the last Codepoint skipped in \a result,
            //! return whether successful
            //!
            //! I.e. for \a step=1 Codepoint pointed to by \a index
            //! before the call is read,
            //! for \a step=2 the current position is skipped and the
            //! next one read.
            //! If \a step=0 or out of bounds, the method returns \c false
            //! and \a result may or may not be changed.
            //! In any case incrementing \a index stops at the end of the buffer.
            //!
            //! \{
            virtual bool read_forward(const unsigned char *p, size_t bytes,
                                      Index &index, size_t steps,
                                      Codepoint &result) const IPL_NOEXCEPT=0;
            bool read_forward(const SharedBuf &buf, Index &index, size_t steps,
                              Codepoint &result) const IPL_NOEXCEPT {
                return read_forward(buf, buf.bytes(), index, steps, result);
            }
            //! \}

            //! \brief Put \a codepoint at \a p at \a index, increment \a index,
            //! return whether successful
            //!
            //! \{
            virtual bool write_forward(unsigned char *p, size_t bytes, Index &index,
                                       Codepoint codepoint) const IPL_NOEXCEPT=0;
            bool write_forward(const SharedBuf &buf, Index &index,
                               Codepoint codepoint) const IPL_NOEXCEPT {
                return write_forward(buf, buf.bytes(), index, codepoint);
            }
            //! \}

            //! \brief How many bytes does it take to encode \a codepoint?
            //! 0 means error.
            virtual size_t encoded_bytes(Codepoint codepoint) const IPL_NOEXCEPT=0;

            //! \brief Create Index to the \a codepoint_index'th codepoint at \a p
            //! but not more than \a bytes after \a p
            //!
            //! The default implementation simply traverses the buffer from the
            //! beginning. Override with a more efficient implementation if
            //! your encoding allows.
            virtual Index at(const unsigned char *p, size_t bytes,
                             size_t codepoint_index=0) const IPL_NOEXCEPT;
            //! \brief Create Index to the \a codepoint_index'th codepoint in \a buf
            //! but not more than \a buf.bytes() into \a buf
            Index at(const SharedBuf &buf, size_t codepoint_index=0) const IPL_NOEXCEPT {
                return at(buf, buf.bytes(), codepoint_index);
            }
            //! \brief Convert \a p into \a encoding -- always transcodes
            SharedBuf to(const Codec &encoding,
                         const unsigned char *p, size_t bytes,
                         bool zero_terminate,
                         size_t max_bytes/*=(size_t)-1*/) const IPL_NOEXCEPT;
            //! \brief Convert \a p into \a encoding, just returning \a buf if possible
            SharedBuf to(const Codec &encoding, const SharedBuf &buf,
                         bool zero_terminated, bool zero_terminate,
                         size_t max_bytes/*=(size_t)-1*/) const IPL_NOEXCEPT {
                if(this==&encoding && buf.bytes()<=max_bytes) {
                    if(zero_terminated==zero_terminate)
                        return buf;
                    else if(zero_terminated)
                        return buf.shrink(encoded_bytes(0));
                    else {
                        SharedBuf b(buf.bytes()+encoded_bytes(0));
                        memcpy(b, buf, buf.bytes());
                        Index i;
                        write_forward(b+buf.bytes(), i, 0);
                        return b;
                    }
                } else
                    if(zero_terminated) {
                        SharedBuf b(buf.shrink(encoded_bytes(0)));
                        return to(encoding, (const unsigned char *)b, b.bytes(),
                                  zero_terminate, max_bytes);
                    } else
                        return to(encoding, (const unsigned char *)buf, buf.bytes(),
                                  zero_terminate, max_bytes);
            }
        };

/*****************************************************************************/

        /*!
            \brief Description of a string encoding comprising a Codec and more

            We need to completely describe a String's memory format but
            want to do so in a compact manner (i.e. using a single constant).
            Trouble is that this format includes whether the data is
            zero-terminated, which is very much uninteresting for the
            actual Codec engine, even the fact whether two encodings are
            memory-compatible is only partly affected by it.
            Hence zero-termination should \e not be part of the actual codec.

            This implies that specifying an encoding and specifying a codec
            is not the same thing and we need this Encoding structure as type
            for the encoding constants.
        */
        struct Encoding {

            const Codec *codec;
            bool zero_terminated;

            Encoding(const Codec &codec, const bool zero_terminated) IPL_NOEXCEPT:
                codec(&codec), zero_terminated(zero_terminated) {}
            //! \brief For silently converting a Codec into an Encoding
            Encoding(const Codec &codec) IPL_NOEXCEPT:
                codec(&codec), zero_terminated(false) {}
            Encoding(const Encoding &other) IPL_NOEXCEPT
            : codec(other.codec)
            , zero_terminated(other.zero_terminated)
            {}

            Encoding &operator = (const Encoding &other) IPL_NOEXCEPT {
                if (this != &other) {
                    codec=other.codec;
                    zero_terminated=other.zero_terminated;
                }
                return *this;
            }
        };

/*****************************************************************************/

        /*!
            \internal
            \brief Do not instanciate this class,
            use the existing ipl::unicode::UTF8 instead
        */
        class IPLCOMMON_EXPORT Utf8: public Codec {

        public:
            virtual Codepoint read(const unsigned char *p, size_t bytes,
                                   const Index &index) const IPL_NOEXCEPT;
            virtual bool read_forward(const unsigned char *p, size_t bytes,
                                      Index &index, size_t steps,
                                      Codepoint &result) const IPL_NOEXCEPT;
            virtual bool write_forward(unsigned char *p, size_t bytes,
                                       Index &index, Codepoint codepoint) const IPL_NOEXCEPT;
            virtual size_t encoded_bytes(Codepoint codepoint) const IPL_NOEXCEPT;

            //! \brief Is \a byte a follow-up byte (0),
            //! a start byte of a sequence of \e n bytes (n) or
            //! illegal in UTF-8 (-1)?
            static int type(unsigned char byte) IPL_NOEXCEPT {
                if(byte & 0x80)
                    if(byte & 0x40)
                        if(byte & 0x20)
                            if(byte & 0x10)
                                if(byte & 0x08)
                                    if(byte & 0x04)
                                        if(byte & 0x02)
                                            return -1;  // 1111111x start of illegal sequence >31 bits payload
                                        else
                                            return 6;  // 1111110x start of non-unicode 6 byte sequence
                                    else
                                        return 5;  // 111110xx start of non-unicode 5 byte sequence
                                else
                                    return 4;  // 11110xxx start of 4 byte sequence
                            else
                                return 3;  // 1110xxxx start of 3 byte sequence
                        else
                            return 2;  // 110xxxxx start of 2 byte sequence
                    else
                        return 0;  // 10xxxxxx follow-up byte
                else
                    return 1;  // 0xxxxxxx start of a 1 byte sequence = single ASCII byte
            }
        };

        //! \brief \b The (not zero terminated) utf-8 encoding
        //!
        //! As UTF-8 is a variable-length encoding, random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding UTF8;
        //! \brief \b The zero-terminated utf-8 encoding
        //!
        //! As UTF-8 is a variable-length encoding, random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding UTF8Z;

/*****************************************************************************/

        /*!
            \internal
            \brief Do not instanciate this class, use the existing
            ipl::unicode::UTF16LE or ipl::unicode::UTF16BE instead
        */
        class IPLCOMMON_EXPORT Utf16: public Codec {

        public:
            Utf16(bool big_endian) IPL_NOEXCEPT:
                big_endian(big_endian)
            {}

            virtual Codepoint read(const unsigned char *p, size_t bytes,
                                   const Index &index) const IPL_NOEXCEPT;
            virtual bool read_forward(const unsigned char *p, size_t bytes,
                                      Index &index, size_t steps,
                                      Codepoint &result) const IPL_NOEXCEPT;
            virtual bool write_forward(unsigned char *p, size_t bytes,
                                       Index &index, Codepoint codepoint) const IPL_NOEXCEPT;
            virtual size_t encoded_bytes(Codepoint codepoint) const IPL_NOEXCEPT;

        protected:
            uint16_t read_uint16_t(const unsigned char *p) const IPL_NOEXCEPT {
                if(big_endian)
                    return (uint16_t)((((unsigned)p[0])<<8) | (unsigned)p[1]);
                else
                    return (uint16_t)((unsigned)p[0] | (((unsigned)p[1])<<8));
            }
            void write_uint16_t(uint16_t value, unsigned char *p) const {
                if(big_endian) {
                    p[0]=(unsigned char)(value>>8);
                    p[1]=(unsigned char)(value&0xff);
                } else {
                    p[0]=(unsigned char)(value&0xff);
                    p[1]=(unsigned char)(value>>8);
                }
            }
            uint16_t fix_endian(uint16_t x) const {
#ifdef IPL_FW_BIG_ENDIAN
                if(big_endian)
                    return x;
                else
                    return (uint16_t)((((unsigned)x)>>8) | (((unsigned)x)<<8));
#else
                if(big_endian)
                    return (uint16_t)((((unsigned)x)>>8) | (((unsigned)x)<<8));
                else
                    return x;
#endif
            }

            const bool big_endian;
        };

        //! \brief \b The (not zero terminated) utf-16 little endian encoding
        //!
        //! As UTF-16 is a variable-length encoding, random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding UTF16LE;
        //! \brief \b The zero terminated utf-16 little endian encoding
        //!
        //! As UTF-16 is a variable-length encoding, random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding UTF16LEZ;
        //! \brief \b The (not zero terminated) utf-16 big endian encoding
        //!
        //! As UTF-16 is a variable-length encoding, random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding UTF16BE;
        //! \brief \b The zero terminated utf-16 big endian encoding
        //!
        //! As UTF-16 is a variable-length encoding, random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding UTF16BEZ;
        //! \brief The (not zero terminated) utf-16 encoding matching the machine's native endianess
        //!
        //! As UTF-16 is a variable-length encoding, random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding &UTF16MACHINE;
        //! \brief The zero terminated utf-16 encoding matching the machine's native endianess
        //!
        //! As UTF-16 is a variable-length encoding, random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding &UTF16MACHINEZ;

/*****************************************************************************/

        /*!
            \internal
            \brief Do not instanciate this class,
            use the existing ipl::unicode::UCS4 instead
        */
        class IPLCOMMON_EXPORT Ucs4: public Codec {

        public:
            virtual Codepoint read(const unsigned char *p, size_t bytes,
                                   const Index &index) const IPL_NOEXCEPT;
            virtual bool read_forward(const unsigned char *p, size_t bytes,
                                      Index &index, size_t steps,
                                      Codepoint &result) const IPL_NOEXCEPT;
            virtual bool write_forward(unsigned char *p, size_t bytes,
                                       Index &index, Codepoint codepoint) const IPL_NOEXCEPT;
            virtual size_t encoded_bytes(Codepoint codepoint) const IPL_NOEXCEPT;
            virtual Index at(const unsigned char *p, size_t bytes,
                             size_t codepoint_index) const IPL_NOEXCEPT;
        };

        //! \brief \b The (not zero terminated) ucs4 encoding
        //! (=plain 32 bit codepoint number in machine byte order)
        //!
        //! This is a fixed-size encoding (4 bytes per codepoint) which makes for
        //! efficient random access.
        extern IPLCOMMON_EXPORT Encoding UCS4;
        //! \brief \b The zero-terminated ucs4 encoding
        //! (=plain 32 bit codepoint number in machine byte order)
        //!
        //! This is a fixed-size encoding (4 bytes per codepoint) which makes for
        //! efficient random access.
        extern IPLCOMMON_EXPORT Encoding UCS4Z;

/*****************************************************************************/

        //! \brief Alias for the system's native encoding, zero-terminated
        //!
        //! This is what the OS calls take, either UTF8Z or UTF16MACHINEZ.
        //! Hence random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding &NATIVE;

/*****************************************************************************/

        //! \brief Alias for std::wstring's internal encoding ??? deprecated, avoid wstring!
        //!
        //! Technically the encoding of std::wstring is locale dependent,
        //! so there is no such thing as \e the wstring encoding.
        //! In practice it seems to be either UCS4 or UTF16MACHINE, so defining
        //! a wstring codec alias sort of works.
        //! Under Windows (and possibly on other misguided systems)
        //! random access is inefficient.
        extern IPLCOMMON_EXPORT Encoding &WSTRING;

/*****************************************************************************/

        /*!
            \brief A sequence of Codepoints
        */
        class IPLCOMMON_EXPORT String {

        public:

            class Iterator;
            friend class Iterator;

            class Spliterator;

        protected:

            /*!
                \brief Temporary buffer that you can get a const char * to

                String::str() cannot return a const char * to the Strings
                (suitably encoded) content as there is nowhere it could point
                to. Instead it needs to return some kind of temporary buffer.
                Now it would be nice if this buffer object could cast implicitly
                into a const char * for your convenience, but unfortunatly this
                is impossible in the argument of a variadic function
                (i.e. printf), and that is the only use for String::str().

                Therefore String::str() returns a String::Str, containing the
                temporary buffer, and you need to call c_str() on it to get
                the actual pointer. Inconvenient but unavoidable.
            */
            class Str {

            public:
                Str(const SharedBuf &data) IPL_NOEXCEPT: data(data) {}
                /*!
                    \brief Retrieve a \b temporary const char * to the contained
                    data
                */
                const char *c_str() const IPL_NOEXCEPT { return data; }

            protected:
                SharedBuf data;
            };

        public:

            // Not inlining the c'tors guarantees that the Encoding constants
            // and the Codec instances are already initialized
            //
            //! \brief Constructors that keep internal encoding flexible
            //! -- use for known good data
            //!
            //! These constructors assume that the provided buffer contains
            //! valid data in the respective encoding -- efficient but
            //! potentially dangerous.
            //! \{
            String() IPL_NOEXCEPT;
            String(Codepoint codepoint) IPL_NOEXCEPT;
            String(const char *utf8text) IPL_NOEXCEPT;
            String(const ipl::string &utf8text) IPL_NOEXCEPT;
            String(const wchar_t *text) IPL_NOEXCEPT;       //!< \brief Deprecated ??? avoid wchar_t!
            String(const ipl::wstring &text) IPL_NOEXCEPT;  //!< \brief Deprecated ??? avoid wstring!
            String(const SharedBuf &buffer, const Encoding &encoding) IPL_NOEXCEPT;
            String(const String &other) IPL_NOEXCEPT;
            //! \}
            //! \brief Constructors that force the internal encoding
            //! -- \b do \b not \b use unless you positively know what you're doing
            //! \{
            String(const Encoding &internal_encoding) IPL_NOEXCEPT;
            String(const Encoding &internal_encoding, Codepoint codepoint) IPL_NOEXCEPT;
            String(const Encoding &internal_encoding, const char *utf8text) IPL_NOEXCEPT;
            String(const Encoding &internal_encoding, const ipl::string &utf8text) IPL_NOEXCEPT;
            String(const Encoding &internal_encoding, const wchar_t *text) IPL_NOEXCEPT;       //!< \brief Deprecated  avoid wchar_t!
            String(const Encoding &internal_encoding, const ipl::wstring &text) IPL_NOEXCEPT;  //!< \brief Deprecated  avoid wstring!
            String(const Encoding &internal_encoding, const SharedBuf &buffer, const Encoding &encoding) IPL_NOEXCEPT;
            String(const Encoding &internal_encoding, const String &other) IPL_NOEXCEPT;
            //! \}
            //! \brief Sanitizing factories -- use for untrusted data
            //!
            //! These make sure to only copy correctly encoded data.
            //! Everything invalid gets replaced with a REPLACEMENT_CHAR.
            //! \{
            static String sanitize(const SharedBuf &buffer,
                                   const Encoding &encoding) IPL_NOEXCEPT;
            //! \brief Also works with \c std::string etc.
            static String sanitize(const String &other) IPL_NOEXCEPT {
                return sanitize(other.buf, other.encoding);
            }
            //! \}

        protected:
            //! \internal
            String(const SharedBuf &buf, size_t size, const Encoding &encoding) IPL_NOEXCEPT:
                encoding(encoding), buf(buf), len(size) {}

        public:
            String& operator=(const String& other) IPL_NOEXCEPT;
            //! \brief UTF-8 encoding in narrow string form
            operator ipl::string () const  IPL_NOEXCEPT{
                SharedBuf converted(encoding.codec->to(*UTF8.codec, buf,
                                                       encoding.zero_terminated,
                                                       UTF8.zero_terminated,
                                                       (size_t)-1));
                return ipl::string(converted, converted.bytes());
            }
            //! \brief Deprecated ??? avoid wstring
            operator ipl::wstring () const  IPL_NOEXCEPT{
                SharedBuf converted(encoding.codec->to(*WSTRING.codec, buf,
                                                       encoding.zero_terminated,
                                                       WSTRING.zero_terminated,
                                                       (size_t)-1));
                return ipl::wstring(converted, converted.bytes()/sizeof(wchar_t));
            }
            //! \brief Yield String's content encoded as \a encoding in a new
            //! buffer
            //!
            //! If you specify \a max_bytes, the encoded data will be truncated
            //! but still be in valid format.
            //! If \a encoding recquires zero-termination, the result is guaranteed
            //! to be zero-terminated except when \a max_bytes is smaller than
            //! the size of a single encoded zero.
            SharedBuf encode(const Encoding &enc,
                             size_t max_bytes=(size_t)-1) const IPL_NOEXCEPT {
                return this->encoding.codec->to(*enc.codec, buf,
                                                this->encoding.zero_terminated,
                                                enc.zero_terminated,
                                                max_bytes);
            }

            // ****************************************************************
            float encode(const Encoding &enc, bool dummy, ...) const { return 0; }
            // ****************************************************************

            /*!
                \brief Get zero-terminated, UTF-8 encoded version of the string
                that you can turn into a const char * for use in printf-style
                functions

                Use like this:
                <code>
                printf("I really should have used ipl::cout to print \"%s\"\n",
                       some_unicode_string.str().c_str());
                </code>

                The combination str().c_str() yields a const char * to some
                \b temporary buffer containing the string in zero-terminated
                UTF-8. The pointer returned by Str::c_str() is valid as long as
                the temporary Str object returned by str() exists, i.e.
                you must not keep it around.

                The name str() was chosen to mimic std::istringstreams ideom
                of stream.str().c_str(), but String::str() doesn't return a
                std::string to avoid an unnecessary copy whenever the String
                already is in the right encoding.

                When you really need to turn a String into an std::string, use
                the cast operator instead.
            */
            Str str() const IPL_NOEXCEPT { return encode(UTF8Z); }

            //! \brief Number of Codepoints in the String
            size_t size() const IPL_NOEXCEPT { return len; }
            bool empty() const IPL_NOEXCEPT { return size()==0; }
            //! \brief Equivalent to \c !empty()
            operator PseudoBool () const IPL_NOEXCEPT { return empty()? PSEUDO_FALSE : &PSEUDO_TRUE; }

            //! \brief Normal STL-like iterators
            //!
            //! Note that instead of checking <code>iterator==string.end()</code>
            //! you can alternatively use <code>iterator.isend()</code>
            //! or <code>!iterator</code>.
            //!
            //! \{
            inline Iterator begin() const IPL_NOEXCEPT;
            inline Iterator end() const IPL_NOEXCEPT;
            //! \}

            //! \brief Read-only access \a i'th codepoint
            //!
            //! \a i must be less than size() and mustn't be negative.
            Codepoint operator [] (ptrdiff_t i) const IPL_NOEXCEPT {
                SharedBuf z=zero_corrected_buf();
                Codec::Index j=encoding.codec->at(z, normalize_index(i));
                return encoding.codec->read(z, j);
            }
            //! \brief Read-only access \a i'th codepoint
            //!
            //! \a i>=size() yields a REPLACEMENT CHAR U+FFFD
            Codepoint at(size_t i) const IPL_NOEXCEPT;
            //! \brief Substring from position \a begin
            //! up to but not including position \a end
            //!
            //! Note that both \a begin and \a end can be negative.
            //! In that case -1 means the last position, -2 the position before
            //! and so on.
            //! Non-negative numbers start with 0 at the first position,
            //! just as you expected.
            //! Leaving out \a end means "up to and including the String's end".
            //!
            //! It is safe to denote a position outside the string.
            //! It will be clamped to the actual string length
            //! (i.e. <code>ipl::unicode::String("abc").substr(-1000, 1000)</code>
            //! yields the original string while
            //! <code>ipl::unicode::String("abc").substr(1000, -1000)</code>
            //! is empty).
            //!
            //! substr() doesn't copy the original string's data,
            //! but the effort of finding the actual address of
            //! \a begin and \a end is equivalent to operator [].
            //!
            //! As substr does random access, its efficiency will depend on the
            //! encoding in use. Variable-size encodings as UTF8 and UTF16 have
            //! inefficient random access.
            //! \{
            String substr(const Iterator &begin, const Iterator &end) const IPL_NOEXCEPT;
            String substr(ptrdiff_t begin, ptrdiff_t end) const IPL_NOEXCEPT;
            String substr(const Iterator &begin) const IPL_NOEXCEPT;
            String substr(ptrdiff_t begin) const IPL_NOEXCEPT;
            //! \}

            //! \brief Concatenate String with \a other, using the right side's encoding
            const String operator + (const String &other) const IPL_NOEXCEPT;
            //! \brief Append \a other (inefficiently, i.e. with reallocating and copying)
            const String &operator += (const String &other) IPL_NOEXCEPT { *this=*this+other; return *this; }
            //! \brief Append the same String to itself, \a multiplicator times in total
            const String operator * (size_t multiplicator) const IPL_NOEXCEPT;
            //! \brief Append String to itself, \a multiplicator times in total
            //! (inefficiently, i.e. with reallocating and copying)
            const String &operator *= (size_t multiplicator) IPL_NOEXCEPT { *this=*this*multiplicator; return *this; }

            bool operator == (const String &other) const IPL_NOEXCEPT;
            bool operator != (const String &other) const IPL_NOEXCEPT { return !operator == (other); }
            //! \brief String ordering operators compare by Codepoint only
            //!
            //! No fancy-schmancy normalization or locale-dependent collation
            //! are performed.
            //! \c "a" is less than \c "aa" is less than \c "b".
            //! \{
            bool operator < (const String &other) const IPL_NOEXCEPT;
            bool operator >= (const String &other) const IPL_NOEXCEPT { return !operator < (other); }
            bool operator > (const String &other) const IPL_NOEXCEPT;
            bool operator <= (const String &other) const IPL_NOEXCEPT { return !operator > (other); }
            //! \}

            Iterator find(const String &needle, const Iterator &from) const IPL_NOEXCEPT;
            Iterator find(const String &needle, ptrdiff_t from) const IPL_NOEXCEPT;
            inline Iterator find(const String &needle) const IPL_NOEXCEPT;
            Iterator rfind(const String &needle, const Iterator &before) const IPL_NOEXCEPT;
            Iterator rfind(const String &needle, ptrdiff_t before) const IPL_NOEXCEPT;
            inline Iterator rfind(const String &needle) const IPL_NOEXCEPT;

            Iterator find_first_of(const String &needles, const Iterator &from) const IPL_NOEXCEPT;
            Iterator find_first_of(const String &needles, ptrdiff_t from) const IPL_NOEXCEPT;
            inline Iterator find_first_of(const String &needles) const IPL_NOEXCEPT;
            Iterator find_first_not_of(const String &non_needles, const Iterator &from) const IPL_NOEXCEPT;
            Iterator find_first_not_of(const String &non_needles, ptrdiff_t from) const IPL_NOEXCEPT;
            inline Iterator find_first_not_of(const String &non_needles) const IPL_NOEXCEPT;
            Iterator find_last_of(const String &needles, const Iterator &before) const IPL_NOEXCEPT;
            Iterator find_last_of(const String &needles, ptrdiff_t before) const IPL_NOEXCEPT;
            inline Iterator find_last_of(const String &needles) const IPL_NOEXCEPT;
            Iterator find_last_not_of(const String &non_needles, const Iterator &before) const IPL_NOEXCEPT;
            Iterator find_last_not_of(const String &non_needles, ptrdiff_t before) const IPL_NOEXCEPT;
            inline Iterator find_last_not_of(const String &non_needles) const IPL_NOEXCEPT;

            //! \brief Split the String at \a delimiter into a sequence of parts
            //!
            //! Use as \code
            //!     String stuff("foo, bar, baz");
            //!     ipl::vector list_of_stuff(stuff.split_begin(", "), stuff.split_end());
            //!     // list_of_stuff now contains String("foo"), String("bar") and String("baz").
            //! \endcode
            inline Spliterator split_begin(const String &delimiter) const IPL_NOEXCEPT;
            static inline Spliterator split_end() IPL_NOEXCEPT;
            //! \brief Put this string between each of \a *begin to \a *end
            //! and concatenate all of it
            //!
            //! E.g. \code
            //!    const char *stuff[]={"foo", "bar", "baz"};
            //!    String s=String(", ").join(stuff, stuff+sizeof(stuff));
            //!    // s is String("foo, bar, baz")
            //! \endcode
            template <typename ConstIter>
            String join(const ConstIter &begin, const ConstIter &end) const IPL_NOEXCEPT {
                String result;
                for(ConstIter i=begin; i!=end; i++) {
                    if(i!=begin)
                        result+=*this;
                    result+=*i;
                }
                return result;
            }

            //! \brief Return a new String where each instance of \a begone
            //! has been replaced by \a arise
            String replace(const String &begone, const String &arise) const IPL_NOEXCEPT;

            //! \brief Return a new string where each character from \a begone
            //! are removed from the beginning (default: spaces U+0020)
            inline String lstrip(const String &begone=" ") const IPL_NOEXCEPT;
            //! \brief Return a new string where each character from \a begone
            //! are removed from the end (default: spaces U+0020)
            inline String rstrip(const String &begone=" ") const IPL_NOEXCEPT;
            //! \brief Return a new string where each character from \a begone
            //! are removed from both ends (default: spaces U+0020)
            inline String strip(const String &begone=" ") const IPL_NOEXCEPT;

        protected:
            //! \internal
            //! \brief Make signed index non-negative and clamp to length
            size_t normalize_index(ptrdiff_t index) const IPL_NOEXCEPT {
                if(        index<0)      index+=(ptrdiff_t)size();  // normalize negative index
                if(        index<0)      index=0;                   // clamp to actual index space
                if((size_t)index>size()) index=(ptrdiff_t)size();   // clamp to actual index space
                return (size_t)index;
            }
            //! \internal
            //! \brief Count codepoints
            size_t count() const IPL_NOEXCEPT;
            //! \internal
            //! \brief Remove a possible zero termination from buf
            SharedBuf zero_corrected_buf() const IPL_NOEXCEPT {
                if(encoding.zero_terminated)
                    return buf.shrink(encoding.codec->encoded_bytes(0));
                else
                    return buf;
            }
            //! \internal
            //! \brief Subtract possible zero termination from buf.bytes()
            size_t zero_corrected_bytes() const IPL_NOEXCEPT {
                if(encoding.zero_terminated)
                    return buf.bytes()-encoding.codec->encoded_bytes(0);
                else
                    return buf.bytes();
            }

            Encoding encoding;
            SharedBuf buf;
            size_t len;
        };

/*****************************************************************************/

        /*!
            \brief const forward iterator over String
        */
        class IPLCOMMON_EXPORT String::Iterator {

        public:

            typedef size_t distance_type;
            typedef ptrdiff_t difference_type;
            typedef Codepoint value_type;
            typedef const value_type *pointer;
            typedef const value_type &reference;
            typedef ipl::forward_iterator_tag iterator_category;

            //! \brief Create an \b unusable iterator
            Iterator() IPL_NOEXCEPT: string(NULL) {}

            /* Forward iterator **********************************************/
            Codepoint operator * () const IPL_NOEXCEPT {
                if(string)
                    return string->encoding.codec->read(string->zero_corrected_buf(), index);
                return REPLACEMENT_CHAR;
            }
            // Codepoint *operator -> () const omitted

            Iterator &operator += (ptrdiff_t n) IPL_NOEXCEPT {
                Codepoint ignore;
                if(string)
                    string->encoding.codec->read_forward(string->zero_corrected_buf(),
                                                         index, (size_t)n, ignore);
                return *this;
            }
            Iterator &operator ++ () IPL_NOEXCEPT { return operator += (1); }
            Iterator operator ++ (int) IPL_NOEXCEPT {
                Iterator result(*this);
                operator ++ ();
                return result;
            }
            Iterator operator + (ptrdiff_t n) const IPL_NOEXCEPT {
                Iterator result(*this);
                result+=n;
                return result;
            }

            ptrdiff_t operator - (const Iterator &other) const IPL_NOEXCEPT {
                return (ptrdiff_t)(index.codepoint-other.index.codepoint);
            }

            Codepoint operator [] (size_t i) const IPL_NOEXCEPT {
                return *operator + ((ptrdiff_t)i);
            }

            //! \brief Always \c false for iterators pointing into different
            //! buffers
            bool operator < (const Iterator &other) const IPL_NOEXCEPT {
                if(string && other.string)
                    return (void *)string->buf==(void *)other.string->buf
                        && operator - (other)<0;
                return false;
            }

            /* Extensions ***************************************************/
            //! \brief Always \c false for iterators pointing into different
            //! buffers
            bool operator == (const Iterator &other) const IPL_NOEXCEPT {
                if(string)
                    if(other.string)
                        return (void *)string->buf==(void *)other.string->buf
                            && operator - (other)==0;
                    else
                        return false;
                else
                    if(other.string)
                        return false;
                    else
                        return true;
            }
            //! \brief Always \c false for iterators pointing into different
            //! buffers
            bool operator != (const Iterator &other) const IPL_NOEXCEPT {
                if(string)
                    if(other.string)
                        return (void *)string->buf==(void *)other.string->buf
                            && operator - (other)!=0;
                    else
                        return false;
                else
                    if(other.string)
                        return false;
                    else
                        return true;
            }
            //! \brief Always \c false for iterators pointing into different
            //! buffers
            bool operator <= (const Iterator &other) const IPL_NOEXCEPT {
                return operator < (other) || operator == (other);
            }
            //! \brief Always \c false for iterators pointing into different
            //! buffers
            bool operator > (const Iterator &other) const IPL_NOEXCEPT {
                if(string && other.string)
                    return (void *)string->buf==(void *)other.string->buf
                        && operator - (other)>0;
                return false;
            }
            //! \brief Always \c false for iterators pointing into different
            //! buffers
            bool operator >= (const Iterator &other) const IPL_NOEXCEPT {
                return operator > (other) || operator == (other);
            }

            //! \brief Compare with the original string's end() without the need to know the string
            bool isend() const IPL_NOEXCEPT { return *this==string->end(); }

            //! \brief Does the iterator point within the String,
            //! i.e. is it not end?
            //!
            //! You can use this for constructs like
            //! \code
            //!    while(it)
            //!        do_something_with(it++);
            //! \endcode
            operator PseudoBool () const IPL_NOEXCEPT {
                return (!isend() /*&& !isrend()*/)? &PSEUDO_TRUE : PSEUDO_FALSE;
            }
            bool operator ! () const IPL_NOEXCEPT { return !operator PseudoBool(); }

        protected:

            friend class String;

            Iterator(const String &string, size_t codepoint, size_t byte) IPL_NOEXCEPT:
                string(&string), index(codepoint, byte) {}

            const String *string;
            Codec::Index index;
        };

/*****************************************************************************/

        /*!
            \brief Input Iterator over String::split() results

            Obtain your Spliterators from String::split_begin() and
            String::split_end().
        */
        class IPLCOMMON_EXPORT String::Spliterator {

        public:

            typedef size_t distance_type;
            typedef ptrdiff_t difference_type;
            typedef String value_type;
            typedef const value_type *pointer;
            typedef const value_type &reference;
            typedef ipl::input_iterator_tag iterator_category;

            Spliterator() IPL_NOEXCEPT: end(true) {}
            Spliterator(const String &haystack, const String &needle) IPL_NOEXCEPT:
                haystack(haystack), needle(needle),
                position(haystack.begin()), next(haystack.find(needle)),
                end(false) {
                // special case: empty needle should yield all characters
                // one by one without leading or trailing empty strings
                if(needle.empty()) {
                    if(haystack.empty())
                        end=true;
                    else
                        next++;
                }
            }

            /* Input iterator **********************************************/
            String operator * () const IPL_NOEXCEPT {
                return haystack.substr(position, next);
            }

            Spliterator &operator ++ () IPL_NOEXCEPT {
                if(next) {
                    position=next+(ptrdiff_t)needle.size();
                    if(position)
                        // special case: empty needle should yield all characters
                        // one by one without leading or trailing empty strings
                        if(needle.empty())
                            next++;
                        else
                            next=haystack.find(needle, position);
                    else
                        next=haystack.end();  // not yet end=true!
                } else {
                    position=haystack.end();
                    next=haystack.end();
                    end=true;
                }
                return *this;
            }
            Spliterator operator ++ (int) IPL_NOEXCEPT {
                Spliterator result(*this);
                operator ++ ();
                return result;
            }
            bool operator == (const Spliterator &other) const IPL_NOEXCEPT {
                if(end)
                    return other.end;
                else
                    if(other.end)
                        return false;
                    else
                        return haystack.buf==other.haystack.buf
                            && needle.buf==other.needle.buf
                            && position==other.position
                            && next==other.next;
            }
            bool operator != (const Spliterator &other) const IPL_NOEXCEPT {
                return !operator == (other);
            }

            //! \brief Compare with the original string's end() without the need to know the string
            bool isend() const IPL_NOEXCEPT { return end; }

            //! \brief Does the iterator point within the part sequence,
            //! i.e. is it not end?
            //!
            //! You can use this for constructs like
            //! \code
            //!    while(it)
            //!        do_something_with(it++);
            //! \endcode
            operator PseudoBool () const IPL_NOEXCEPT {
                return !isend()? &PSEUDO_TRUE : PSEUDO_FALSE;
            }
            bool operator ! () const IPL_NOEXCEPT { return !operator PseudoBool(); }

        public:
            const String haystack;
            const String needle;  // copy needed as parameter can be deleted right away
            Iterator position;
            Iterator next;
            bool end;
        };

/*****************************************************************************/

        String::Iterator String::begin() const IPL_NOEXCEPT  { return Iterator(*this, 0, 0); }
        String::Iterator String::end() const IPL_NOEXCEPT    { return Iterator(*this, len, zero_corrected_bytes()); }

        String::Iterator String::find(const String &needle) const IPL_NOEXCEPT  { return find(needle, begin()); }
        String::Iterator String::rfind(const String &needle) const IPL_NOEXCEPT { return rfind(needle, end()); }

        String::Iterator String::find_first_of(const String &needles) const IPL_NOEXCEPT  { return find_first_of(needles, begin()); }
        String::Iterator String::find_first_not_of(const String &non_needles) const IPL_NOEXCEPT  { return find_first_not_of(non_needles, begin()); }
        String::Iterator String::find_last_of(const String &needles) const IPL_NOEXCEPT  { return find_last_of(needles, end()); }
        String::Iterator String::find_last_not_of(const String &non_needles) const IPL_NOEXCEPT  { return find_last_not_of(non_needles, end()); }

        String::Spliterator String::split_begin(const String &delimiter) const IPL_NOEXCEPT { return Spliterator(*this, delimiter); }
        String::Spliterator String::split_end() IPL_NOEXCEPT { return Spliterator(); }

        String String::lstrip(const String &begone) const IPL_NOEXCEPT { return substr(find_first_not_of(begone), end()); }
        String String::rstrip(const String &begone) const IPL_NOEXCEPT { return substr(begin(), find_last_not_of(begone)+1); }
        String String::strip(const String &begone) const IPL_NOEXCEPT { return substr(find_first_not_of(begone), find_last_not_of(begone)+1); }

/*****************************************************************************/

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator + ()
        inline String operator + (const String &left, const ipl::string &right) IPL_NOEXCEPT
        {
            return left+String(right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator + ()
        inline String operator + (const String &left, const char *right) IPL_NOEXCEPT
        {
            return left+String(right);
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator + ()
        inline String operator + (const ipl::string &left, const String &right) IPL_NOEXCEPT
        {
            return String(left)+right;
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator + ()
        inline String operator + (const char *left, const String &right) IPL_NOEXCEPT
        {
            return String(left)+right;
        }

        inline String operator + (const String &left, Codepoint right) IPL_NOEXCEPT
        {
            return left+String(right);
        }

        inline String operator + (Codepoint left, const String &right) IPL_NOEXCEPT
        {
            return String(left)+right;
        }

/*****************************************************************************/

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator == ()
        inline bool operator == (const String &left, const ipl::string &right) IPL_NOEXCEPT
        {
            return left==String(right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator != ()
        inline bool operator != (const String &left, const ipl::string &right) IPL_NOEXCEPT
        {
            return !(left==right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator == ()
        inline bool operator == (const String &left, const char *right) IPL_NOEXCEPT
        {
            return left==String(right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator != ()
        inline bool operator != (const String &left, const char *right) IPL_NOEXCEPT
        {
            return !(left==right);
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator == ()
        inline bool operator == (const ipl::string &left, const String &right) IPL_NOEXCEPT
        {
            return String(left)==right;
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator != ()
        inline bool operator != (const ipl::string &left, const String &right) IPL_NOEXCEPT
        {
            return !(left==right);
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator == ()
        inline bool operator == (const char *left, const String &right) IPL_NOEXCEPT
        {
            return String(left)==right;
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator != ()
        inline bool operator != (const char *left, const String &right) IPL_NOEXCEPT
        {
            return !(left==right);
        }

/*****************************************************************************/

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator < ()
        inline bool operator < (const String &left, const ipl::string &right) IPL_NOEXCEPT
        {
            return left<String(right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator >= ()
        inline bool operator >= (const String &left, const ipl::string &right) IPL_NOEXCEPT
        {
            return !(left<right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator < ()
        inline bool operator < (const String &left, const char *right) IPL_NOEXCEPT
        {
            return left<String(right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator >= ()
        inline bool operator >= (const String &left, const char *right) IPL_NOEXCEPT
        {
            return !(left<right);
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator < ()
        inline bool operator < (const ipl::string &left, const String &right) IPL_NOEXCEPT
        {
            return String(left)<right;
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator >= ()
        inline bool operator >= (const ipl::string &left, const String &right) IPL_NOEXCEPT
        {
            return !(left<right);
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator < ()
        inline bool operator < (const char *left, const String &right) IPL_NOEXCEPT
        {
            return String(left)<right;
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator >= ()
        inline bool operator >= (const char *left, const String &right) IPL_NOEXCEPT
        {
            return !(left<right);
        }

/*****************************************************************************/

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator > ()
        inline bool operator > (const String &left, const ipl::string &right) IPL_NOEXCEPT
        {
            return left>String(right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator <= ()
        inline bool operator <= (const String &left, const ipl::string &right) IPL_NOEXCEPT
        {
            return !(left>right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator > ()
        inline bool operator > (const String &left, const char *right) IPL_NOEXCEPT
        {
            return left>String(right);
        }

        //! \brief \a right is decoded as UTF-8
        //! \see ipl::unicode::String::operator <= ()
        inline bool operator <= (const String &left, const char *right) IPL_NOEXCEPT
        {
            return !(left>right);
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator > ()
        inline bool operator > (const ipl::string &left, const String &right) IPL_NOEXCEPT
        {
            return String(left)>right;
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator <= ()
        inline bool operator <= (const ipl::string &left, const String &right) IPL_NOEXCEPT
        {
            return !(left>right);
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator > ()
        inline bool operator > (const char *left, const String &right) IPL_NOEXCEPT
        {
            return String(left)>right;
        }

        //! \brief \a left is decoded as UTF-8
        //! \see ipl::unicode::String::operator <= ()
        inline bool operator <= (const char *left, const String &right) IPL_NOEXCEPT
        {
            return !(left>right);
        }

/*****************************************************************************/

        //! \brief Encode String as UTF-8 and push that into \a stream
        inline ipl::ostream &operator << (ipl::ostream &stream, const String &string) IPL_NOEXCEPT
        {
            ipl::string s(string);
            return stream << s;
        }

/*****************************************************************************/

        //! \brief Pull ipl::string from \a stream and put that into String
        inline ipl::istream &operator >> (ipl::istream &stream, String &string) IPL_NOEXCEPT
        {
            ipl::string s;
            ipl::istream &res=stream >> s;
            string=s;
            return res;
        }

/*****************************************************************************/

    }  // end of namespace unicode
}  // end of namespace IPL_NAMESPACE

/*****************************************************************************/
#endif
