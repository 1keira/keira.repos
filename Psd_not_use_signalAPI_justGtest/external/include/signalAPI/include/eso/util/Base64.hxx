/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef UTIL_BASE64_HXX
#define UTIL_BASE64_HXX
/*****************************************************************************/

#include "util_dso.h"

#include <common/error/ErrorType.hxx>
#include <common/buffers.hxx>

#include <string>
#include <map>
#include <stdlib.h>

/*****************************************************************************/

namespace util {

/*****************************************************************************/

    //! \internal
    //! Internal base to Base64Encoder and Base64Decoder.
    class UTIL_EXPORT Base64 {

    public:
        static ipl::ErrorType error;

        // Cannot use an enum class here as that would be typesafe,
        // i.e. the values wouldn't be usable without explicitly
        // casting all the time.
        struct Reason {
            enum {
                out_of_output,  //!< \brief Not enough output buffer available
                out_of_input,   //!< \brief Truncated input
                invalid_input   //!< \brief Invalid character in input
            };
        };

    protected:
        static char hex(uint8_t byte, bool high_nybble);

        static ipl::ErrorID error_table[];
    };

/*****************************************************************************/

    /*!
        \brief Encoder to turn a blob into a string according to RFC4648

        Creates a contiguous base64 encoding (i.e. without line breaks) using
        the normal alphabet or optionally the "URL/file name safe" one.

        You create an encoder object and either stream data through it in
        portions (process(), finish()) or encode the whole data in one go
        (encode(), encodeInto()).

        As creating the encoder might be expensive, if you need to encode
        several buffers create one encoder only and reuse it.
        After stream-encoding one blob, successfully or unsuccessfully,
        call reset() and you are good to go again.
        One-step encoding with encode() or encodeInto()
        resets the encoder automatically.

        encode() might require additional copying in your code,
        encodeInto() and of course process()/finish() write directly
        into a buffer you provide.
        When you alloc a buffer for a whole message,
        determine the needed output buffer size via guessOutputSize().

        There are three ways to use the encoder:

        Dirt simple:
        \code
        util::Base64Encoder encoder;
        std::string result1=encoder.encode(buf1, len1);
        std::string result2=encoder.encode(buf2, len2);
        \endcode

        Still simple:
        \code
        util::Base64Encoder encoder;
        size_t output1_len=encoder.guessOutputSize(input1_len);
        char *output1=malloc(output1_len);  // or new or whatever
        if(encoder.encodeInto(input1_data, input1_len, output1, output1_len)) {
            whaa_error();
            ...
        } else
            do_something_with(output1, output1_len);

        encoder.reset();
        size_t output2_len=encoder.guessOutputSize(input2_len);
        char *output2=malloc(output2_len);  // or new or whatever
        if(encoder.encodeInto(input2_data, input2_len, output2, output2_len)) {
            whaa_error();
            ...
        } else
            do_something_with(output2, output2_len);
        \endcode

        Streaming:
        \code
        util::Base64Encoder encoder;
        size_t input_offset;
        size_t output_offset;

        uint8_t input[INPUT_BUFFER_SIZE];
        size_t input_len;
        char output[OUTPUT_BUFFER_SIZE];

        output_offset=0;
        while(whatever) {
            input_offset=0;
            input_len=gather_bytes_into(input, INPUT_BUFFER_SIZE);
            while(true) {
                encoder.process(input, input_len, input_offset,
                                output, OUTPUT_BUFFER_SIZE, output_offset);
                if(input_offset<input_len) {  // not all input processed, i.e. output full
                    do_something_with(output, output_offset);
                    output_offset=0;  // reset output
                } else  // need more input
                    break;
            }
        }
        do_something_with(output, output_offset);
        output_offset=0;  // reset output

        // end of input stream, process remaining buffered data
        if(encoder.finish(output, OUTPUT_BUFFER_SIZE, output_offset)) {
            whaa_error();
            ...
        } else
            do_something_with(output, output_offset);

        // rinse...
        encoder.reset();

        // ...repeat
        output_offset=0;
        while(whatever) {
            ...
        \endcode
    */
    class UTIL_EXPORT Base64Encoder: public Base64 {

    public:
        //! The normal alphabet is used by default.
        //! Chosing the "URL/file name safe" alphabet instead results in a
        //! different, incompatible encoding!
        Base64Encoder(bool use_url_safe_alphabet=false):
            use_url_safe_alphabet(use_url_safe_alphabet) {}

        //! \brief Return a buffer size guaranteed to be big enough to hold the
        //! encoding of \a input_size bytes
        //!
        //! If you allocate one char more, encodeInto() / finish() guarantees
        //! a terminating 0 char after the last character.
        static size_t guessOutputSize(size_t input_size);

        /*!
            \brief Encode some data as far as possible

            Writes into \a output the base64 encoding of \a input
            in groups of 3 bytes / 4 chars. Any incomplete group left over from
            a previous call will filled up first, any incomplete group left over
            at the end will be buffered for later.

            You can call this method multiple times to stream an arbitrary
            amount of data through the encoder. Remember to call finish()
            after all data has been processed, or the encoded text may be
            incomplete.

            Reading doesn't start at \a input but rather at
            \a input + \a input_offset, similar writing starts at
            \a output + \a output_offset.
            Both offsets will be mutated to refer to the position behind the
            last byte read / character written.
            This allows passing the same pointers and offset variables into
            subsequent calls, as long as parts of the same buffers are processed.

            If there is not enough output space available, encoding will stop
            before the input is exhausted. In that case \a input_offset will
            be less than input_size, reflecting where to proceed in a
            subsequent call.
            Note that \a output_offset may \em still \em be \em less \em than
            \a output_size in that case, as encoding stops when there is not
            enough room left for an output chunk of four chars.

            Remember to reset the corresponding offset to 0 when you acquire
            a new buffer of input / flush a buffer of output to some processing.
        */
        void process(const void *input, size_t input_size, size_t &input_offset,
                     char *output, size_t output_size, size_t &output_offset);

        /*!
            \brief Encode any incomplete group left over from process()

            Write out anything still buffered in the encoder, possibly creating
            padding chars.

            Call this at the end of every process() sequence or your result may
            be incomplete. The parameters \a output, \a output_size
            and \a output_offset are the same as in process(), except that not
            providing enough output space is an \em error.
            This might require up to 4 chars.

            If space permits, a 0 char is added after the encoding
            but \em not reflected in \a offset.
            This allows you to treat a complete encoding as a C string,
            provided that your output buffer is at least of size
            guessOutputSize(size_of_input)+1.

            Returns \c true and raises Error on error.
        */
        bool finish(char *output, size_t output_size, size_t &output_offset);

        /*!
            \brief Forget any internal state and prepare for a new stream

            Call this before reusing the encoder.
        */
        void reset() { accu_fill=0; }

        //! \brief Simple zero-copy way to base64-encode
        //!
        //! \a output_size or \a output.bytes will be set to the actual
        //! size of the encoded text afterwards.
        //!
        //! Returns \c true and raises Error on error.
        //! \{
        bool encodeInto(const void *input, size_t input_size,
                         char *output, size_t &output_size);

        bool encodeInto(const ipl::Buf &input,
                         char *output, size_t &output_size) {
            return encodeInto(input, input.bytes, output, output_size);
        }

        bool encodeInto(const void *input, size_t input_size,
                         ipl::Buf &output) {
            return encodeInto(input, input_size, output, output.bytes);
        }
        bool encodeInto(const ipl::Buf &input,
                         ipl::Buf &output) {
            return encodeInto(input, input.bytes, output, output.bytes);
        }
        //! \}

        //! \brief Dirt-simple way to base64-encode
        //! \{
        std::string encode(const void *input, size_t input_size);

        std::string encode(const ipl::Buf &input) {
            return encode((const void *)input, input.bytes);
        }
        //! \}

    protected:
        //! Encode three bytes (from \ref accu) into four chars
        void encodeChunk(char *output);

        bool use_url_safe_alphabet;

        //! One chunk of input to encodeChunk(), potentially accumulated
        //! over several calls to process().
        uint8_t accu[3];
        //! Number of bytes in \ref accu
        size_t accu_fill{0};
    };

    //! \brief Convenience Base64Encoder using the (incompatible) "URL/file name safe" alphabet
    //!
    //! If you do not know what that means, you do not want to use it!
    class UTIL_EXPORT Base64UrlSafeEncoder: public Base64Encoder {

    public:
        Base64UrlSafeEncoder(): Base64Encoder(true) {}
    };

/*****************************************************************************/

    /*!
        \brief Decoder to turn a string into a blob according to RFC4648

        Reads a contiguous base64 encoding (i.e. without line breaks, whitespace
        or other intervening junk) using the normal alphabet,
        optionally the "URL/file name safe" one or even both.

        You create a decoder object and either stream data through it in
        portions (process(), finish()) or decode the whole data in one go
        (decode(), decodeInto()).

        As creating the decoder might be expensive, if you need to decode
        several strings create one decoder only and reuse it.
        After stream-decoding one string, successfully or unsuccessfully,
        call reset() and you are good to go again.
        One-step decoding with decode() or decodeInto()
        resets the encoder automatically.

        decode() might require additional copying in your code,
        decodeInto() and of course process()/finish() write directly
        into a buffer you provide.
        When you alloc a buffer for a whole message,
        determine the needed output buffer size via guessOutputSize().

        The three ways to use the decoder, dirt simple, somewhat simple and streaming,
        are analog to the Base64Encoder'S ones. See there for examples.
    */
    class UTIL_EXPORT Base64Decoder: public Base64 {

    public:
        //! By default the decoder uses the normal alphabet.
        //! You can selectively disable it and enable the
        //! "URL/file name safe" alphabet if your input is encoded that way
        //! or you can enable both, so any mixture is recognized.
        //!
        //! In case of doubt use the default.
        Base64Decoder(bool use_base_64_alphabet=true, bool use_url_safe_alphabet=false);

        //! \brief Check whether some character is legal in base64
        //!
        //! If you need to decode some mangled base64, e.g. with line breaks,
        //! whitespaces or even random junk interspersed, you need to
        //! prefilter the input data.
        //! This method allows you to separate characters the decoder can
        //! understand from junk.
        bool isLegal(char);

        //! \brief Return a buffer size guaranteed to be big enough to hold the
        //! decoding of \a input_size chars
        //!
        //! The actually decoded data may be smaller due to padding.
        static size_t guessOutputSize(size_t input_size);

        /*!
            \brief Decode some text as far as possible

            Writes into \a output the base64 decoding of \a input
            in groups of 4 chars / 3 bytes. Any incomplete group left over from
            a previous call will filled up first, any incomplete group left over
            at the end will be buffered for later.

            You can call this method multiple times to stream an arbitrary
            amount of text through the decoder. Remember to call finish()
            after all text has been processed, or the decoded data may be
            incomplete.

            Note that any terminating 0 char is \em not part of the input,
            i.e. don't count it in \a input_size!

            Reading doesn't start at \a input but rather at
            \a input + \a input_offset, similar writing starts at
            \a output + \a output_offset.
            Both offsets will be mutated to refer to the position behind the
            last character read / byte written.
            This allows passing the same pointers and offset variables into
            subsequent calls, as long as parts of the same buffers are processed.

            If there is not enough output space available, decoding will stop
            before the input is exhausted. In that case \a input_offset will
            be less than input_size, reflecting where to proceed in a
            subsequent call.
            Note that \a output_offset may \em still \em be \em less \em than
            \a output_size in that case, as decoding stops when there is not
            enough room left for an output chunk of three bytes.

            Remember to reset the corresponding offset to 0 when you acquire
            a new buffer of input / flush a buffer of output to some processing.

            Returns \c true and raises Error on error.
        */
        bool process(const char *input, size_t input_size, size_t &input_offset,
                     void *output, size_t output_size, size_t &output_offset);

        /*!
            \brief Decode any incomplete group left over from process()

            Write out anything still buffered in the decoder.

            Call this at the end of every process() sequence or your result may
            be incomplete. The parameters \a output, \a output_size
            and \a output_offset are the same as in process(), except that not
            providing enough output space is an \em error.
            This might require up to 3 bytes.
        */
        bool finish(void *output, size_t output_size, size_t &output_offset);

        /*!
            \brief Forget any internal state and prepare for a new stream

            Call this before reusing the decoder.
        */
        void reset() { accu_fill=0; padding_seen=0; }

        //! \brief Simple zero-copy way to base64-decode
        //!
        //! \a output_size or \a output.bytes will be set to the actual
        //! size of the decoded data afterwards.
        //!
        //! Returns \c true and raises Error on error.
        //! \{
        bool decodeInto(const char *input, size_t input_size,
                         void *output, size_t &output_size);

        bool decodeInto(const ipl::Buf &input,
                         void *output, size_t &output_size) {
            return decodeInto(input, input.bytes, output, output_size);
        }

        bool decodeInto(const char *input, size_t input_size,
                         ipl::Buf &output) {
            return decodeInto(input, input_size, output, output.bytes);
        }

        bool decodeInto(const ipl::Buf &input,
                         ipl::Buf &output) {
            return decodeInto(input, input.bytes, output, output.bytes);
        }
        //! \}

        //! \brief Dirt-simple way to base64-decode
        //!
        //! In case of an error the returned buffer will be NULL
        //! (test with \code if(buf)\endcode).
        //!
        //! \{
        ipl::SharedBuf decode(const char *input, size_t input_size);

        ipl::SharedBuf decode(const std::string &input) {
            return decode(input.c_str(), input.size());
        }

        ipl::SharedBuf decode(const ipl::Buf &input) {
            return decode((const char *)input, input.bytes);
        }
        //! \}

    protected:
        //! Decode four characters (from \ref accu) into three bytes
        //! (or less in case of padding).
        //! Returns \c true and raises Error on error.
        bool decodeChunk(void *output, size_t output_size, size_t &output_offset);

        //! One chunk of input to decodeChunk(), potentially accumulated
        //! over several calls to process().
        uint8_t accu[4];
        //! Number of bytes in \ref accu
        size_t accu_fill{0};
        //! Have we already seen padding?
        //! This means that non-padding or even another chunk is illegal.
        bool padding_seen{false};

        typedef std::map<char, uint8_t> Alphabet;
        Alphabet alphabet;
    };

    //! \brief Convenience Base64Decoder using the (incompatible) "URL/file name safe" alphabet
    //!
    //! If you do not know what that means, you do not want to use it!
    class UTIL_EXPORT Base64UrlSafeDecoder: public Base64Decoder {

    public:
        Base64UrlSafeDecoder(): Base64Decoder(false, true) {}
    };

    //! \brief Convenience Base64Decoder using both the normal and the
    //! (incompatible) "URL/file name safe" alphabet simultaneously
    //!
    //! If you do not know what that means, you do not want to use it!
    class UTIL_EXPORT Base64UniversalDecoder: public Base64Decoder {

    public:
        Base64UniversalDecoder(): Base64Decoder(true, true) {}
    };

/*****************************************************************************/

}  // end of namespace util

/*****************************************************************************/
#endif
