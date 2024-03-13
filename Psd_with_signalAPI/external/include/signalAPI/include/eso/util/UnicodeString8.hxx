/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_UNICODESTRING8_HXX
#define UTIL_UNICODESTRING8_HXX

#include <ipl_config.h>

#include <common/stdint.h>
#include <common/align.hxx>
#include <common/unicode.hxx>
#include <common/streams/iostream.hxx>
#include <common/types/algorithm.hxx>
#include <common/unicode.hxx>

#include <osal/UnicodeString.hxx>  // backwards compatibility
#include <osal/Path.hxx>  // backwards compatibility

#include <util/UnicodeString_common.hxx>
#include <util/util_dso.h>
#include <util/DataBuffer.hxx>
// #include <util/UCSWrapper.hxx>

namespace util{
    class UnicodeString16;

    /**
            \brief unicode string class

            this class uses the data buffer to store UTF-8 coded unicode strings
            \author v0.1 Marco Staginski (marco.staginski@elektrobit.com)
            \version v0.1
            \date 2007-7-13
            \author v0.2 Marco Staginski (marco.staginski@elektrobit.com)
            \version v0.2
            \date 2007-10-12

        \b Warning! util::UnicodeString, util::UnicodeString8 and
        util::UnicodeString16 may not work as expected when the string
        contains a 0 character somewhere in the middle.
    **/

    class UTIL_EXPORT UnicodeString8:
        public UnicodeString_common,
        public util::DataBuffer<STRING_LOCAL_BUFFER_SIZE> {

    public:
        /**
            \brief embedded iterator class for unicode strings

            embedded iterator class for unicode strings
            \author v0.1 Marco Staginski (marco.staginski@elektrobit.com)
            \version v0.1
            \date 2007-7-13
        **/

        class UTIL_EXPORT iterator{
            friend class UnicodeString8;
        public:
            /**
                \brief constructor
            **/
            iterator(const uint8_t* data, const uint8_t* begin, const uint8_t* end) IPL_NOEXCEPT;
            /**
                \brief gets the current unicode character
            **/
            UnicodeChar operator*() const IPL_NOEXCEPT;
            /**
                \brief advances the iterator and returns the advanced one
            **/
            iterator& operator++() IPL_NOEXCEPT;
            /**
                \brief decreases the iterator and returns the decreased one
            **/
            iterator& operator--() IPL_NOEXCEPT;
            /**
                \brief advances the iterator and returns the previous one
            **/
            iterator operator++(int) IPL_NOEXCEPT;
            //! \brief Guess!
            iterator operator--(int) IPL_NOEXCEPT;
            /**
                \brief tests for inequality
            **/
            bool operator!=(const iterator& iter) const IPL_NOEXCEPT;
            /**
                \brief tests for equality
            **/
            bool operator==(const iterator& iter) const IPL_NOEXCEPT;
            /**
                \brief gets the number of bytes between two iterators
            **/
            int32_t operator-(const iterator& iter) const IPL_NOEXCEPT;
            /**
                \brief sets the iterator further away
            **/
            void operator+=(uint32_t offset) IPL_NOEXCEPT;
            /**
                \brief sets the iterator nearer
            **/
            void operator-=(uint32_t offset) IPL_NOEXCEPT;
            /**
                \brief sets the iterator further away
            **/
            iterator operator+(uint32_t offset) IPL_NOEXCEPT;
            /**
                \brief sets the iterator nearer
            **/
            iterator operator-(uint32_t offset) IPL_NOEXCEPT;
            /**
                \brief checks whether there is an error
            **/
            bool hasError() IPL_NOEXCEPT {return m_has_error;}

        private:
            //! The pointer to the current string position
            const uint8_t* m_current;
            //! If the iterator has encountered an error
            bool m_has_error;
            //! The pointer to the string start position
            const uint8_t* m_start;
            //! The pointer to the string end position
            const uint8_t* m_end;
        };
        friend class iterator;

        /**
            \brief Constructor
            \errors
                none
        **/
        UnicodeString8() IPL_NOEXCEPT;

        UnicodeString8(const ipl::unicode::String &other) IPL_NOEXCEPT;
        /**
            \brief Constructor that takes string data
            \errors
                see setString
            \errorindicator
                hasError()
        **/
        explicit UnicodeString8(char const * string, Encoding enc, uint32_t strlength=0, bool terminateAtZero=false, uint32_t* num_bytes_read=reinterpret_cast<uint32_t*>(NULL)) IPL_NOEXCEPT;
        /**
            \brief Constructor that takes an input stream
            \errors
                see setString
            \errorindicator
                hasError()
        **/
        UnicodeString8(ipl::istream& in, Encoding enc) IPL_NOEXCEPT;

        /**
        * \brief
        *     Construct from an osal::UnicodeString
        **/
        UnicodeString8(const osal::UnicodeString &ucs) IPL_NOEXCEPT;

        // Compatibility hacks, remove ASAP
        UnicodeString8(const osal::BasicPath<char> &path) IPL_NOEXCEPT;
        UnicodeString8(const osal::BasicPath<wchar_t> &path) IPL_NOEXCEPT;

        /**
            \brief Converts a data buffer into a unicode string
            \errors
                see setString
            \errorindicator
                hasError()
        **/
        template<int storage>
        UnicodeString8(util::DataBuffer<storage> const & db, Encoding enc) IPL_NOEXCEPT
        {
            if (db.size() > 0)
            {
                setString(reinterpret_cast<const char*>(db.retrieveData()), enc, db.size());
            }
        }
        
        /**
            \brief Inits the string with a unicode codepoint \p cp repeated \p num_repeat times
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
            \note Behavior for invalid unicode codepoint is undefined
        **/
        UnicodeString8(uint32_t num_repeat, UnicodeChar const & cp) IPL_NOEXCEPT;

        /**
            \brief Inits the string with a number using \%u printf format

            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        explicit UnicodeString8(uint32_t num) IPL_NOEXCEPT {appendNum(num);}
        
        /**
            \brief Inits the string with a number using \%i printf format

            the number->string conversion is not locale dependent - see notes on append
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        explicit UnicodeString8(int32_t num) IPL_NOEXCEPT {appendNum(num);}
        
        /**
            \brief Inits the string with a number using \%llu printf format

            the number->string conversion is not locale dependent - see notes on append
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        explicit UnicodeString8(uint64_t num) IPL_NOEXCEPT {appendNum(num);}
        
        /**
            \brief Inits the string with a number using \%lli printf format

            the number->string conversion is not locale dependent - see notes on append
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        explicit UnicodeString8(int64_t num) IPL_NOEXCEPT {appendNum(num);}
        
        /**
            \brief Inits the string with a number using \%lf printf format

            the decimal separator is locale dependent, see also notes on append
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        explicit UnicodeString8(double num) IPL_NOEXCEPT {appendNum(num);}
        
        /**
            \brief Copy constructor
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8(UnicodeString8 const & s) IPL_NOEXCEPT;
        
        /**
            \brief Copy constructor
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8(UnicodeString16 const & s) IPL_NOEXCEPT;
        
        /**
            \brief Destructor
            \errors
                none
        **/
        virtual ~UnicodeString8() IPL_NOEXCEPT;
        
        /**
            \brief get the start iterator

            the iterator points at the position before the first character
            \errors
                none
        **/
        iterator begin() const IPL_NOEXCEPT;
        /**
        *     \brief
        *         A separate method for setting the UnicodeString by providing an external
        *         c-style string pointer.
        *  \param p_str_ptr the pointer containing the string data. NULL can be used to create an empty string
        *  \param p_str_enc the encoding of the string data in p_str_ptr
        *  \param p_str_length the length of the string data in bytes. Can be 0 if the string data is zero-terminated according to its encoding
        *  \param terminateAtZero if true the parsing of the string data is stopped on encountering a zero-termination even if p_str_length is bigger
        *  \return the number of bytes read
        *  \errors
        *        ipl::CommonError with ID OUT_OF_MEMORY
        *      util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
        *  \errorindicator
        *        hasError()
        **/
        uint32_t setString(char const * p_str_ptr, Encoding p_str_enc, uint32_t p_str_length=0, bool terminateAtZero=false) IPL_NOEXCEPT;
        /**
            \brief get the end iterator

            the iterator points at the position after the last character
            \errors
                none
        **/
        iterator end() const IPL_NOEXCEPT;
        /**
                \brief get the number of code points (unicode characters) in the string
                \errors
                    util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
                \errorindicator
                    hasError()
        **/
        uint32_t length() const IPL_NOEXCEPT;
        /**
                \brief insert a code point into the string
                \param position an iterator to the position after which the unicode character should be inserted
                \param codepoint the unicode character to be inserted
                \errors
                    ipl::CommonError with ID OUT_OF_MEMORY
                \errorindicator
                    hasError()
        **/
        iterator& insert(iterator& position, UnicodeChar codepoint) IPL_NOEXCEPT;
        /**
                \brief insert another string into the string
                \param position an iterator to the position after which the unicode string should be inserted
                \param str the unicode string to be inserted
                \errors
                    ipl::CommonError with ID OUT_OF_MEMORY
                \errorindicator
                    hasError()
        **/
        iterator& insert(iterator& position, UnicodeString8 const& str) IPL_NOEXCEPT;
        iterator &insert(iterator &position, const UnicodeString16 &str) IPL_NOEXCEPT {
            return insert(position, UnicodeString8(str));
        }
        /**
                \brief erases parts of a string
                \param start the iterator to the first character that should be erased
                \param ending the iterator to the last character that should be erased
                \errors
                    none
        **/
        iterator erase(iterator& start, iterator& ending) IPL_NOEXCEPT;
        /**
        \brief insert a code point into the string
        \param position an iterator to the position after which the unicode character should be inserted
        \param codepoint the unicode character to be inserted
        \errors
            ipl::CommonError with ID OUT_OF_MEMORY
        \errorindicator
            hasError()
        **/
        iterator insert(const iterator& position, UnicodeChar codepoint) IPL_NOEXCEPT;
        /**
        \brief insert another string into the string
        \param position an iterator to the position after which the unicode string should be inserted
        \param str the unicode string to be inserted
        \errors
            ipl::CommonError with ID OUT_OF_MEMORY
        \errorindicator
            hasError()
        **/
        iterator insert(const iterator& position, UnicodeString8 const& str) IPL_NOEXCEPT;
        iterator insert(const iterator &position, const UnicodeString16 &str) IPL_NOEXCEPT {
            return insert(position, UnicodeString8(str));
        }
        /**
        \brief erases parts of a string
        \param start the iterator to the first character that should be erased
        \param ending the iterator to the last character that should be erased
        \errors
            none
        **/
        iterator erase(const iterator& start, const iterator& ending) IPL_NOEXCEPT;
        /**
                \brief erases the first character of a string
                \errors
                    ipl::CommonError with ID INVALID_USAGE
                \errorindicator
                    hasError()
        **/
        void popFront() IPL_NOEXCEPT;
        /**
            \brief insert a code point into the string
            \param codepoint the unicode character to be inserted
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& append(UnicodeChar codepoint) IPL_NOEXCEPT;
        /**
            \brief appends a string to the string
            \param str the unicode string to be appended
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& append(const UnicodeString8& str) IPL_NOEXCEPT {insert(end(), str); return *this;}
        UnicodeString8 &append(const UnicodeString16 &str) IPL_NOEXCEPT {insert(end(), str); return *this;}

        /**
        \brief Return a utf-8 coded version of the string

        If \a max_bytes is not 0, the returned buffer contains at most
        \a max_bytes bytes. It is still guaranteed to be correctly encoded
        (i.e. no incomplete multi-byte code at the end) but might not be
        null terminated.

        \errors see setString()
        \errorindicator hasError()
        **/
        util::DataBuffer<util::STRING_LOCAL_BUFFER_SIZE> utf8(uint32_t max_bytes=0) const IPL_NOEXCEPT;
        /**
        \brief Return a utf-16 coded version of the string

        If \a max_bytes is not 0, the returned buffer contains at most
        \a max_bytes bytes. It is still guaranteed to be correctly encoded
        (i.e. no incomplete multi-byte code at the end) but might not be
        null terminated.

        \errors see setString()
        \errorindicator hasError()
        **/
        util::DataBuffer<util::STRING_LOCAL_BUFFER_SIZE> utf16(uint32_t max_bytes=0) const IPL_NOEXCEPT;
        /**
        \brief Return a utf-32 coded version of the string

        If \a max_bytes is not 0, the returned buffer contains at most
        \a max_bytes bytes. It is still guaranteed to be correctly encoded
        (i.e. no incomplete multi-byte code at the end) but might not be
        null terminated.

        \errors see setString()
        \errorindicator hasError()
        **/
        util::DataBuffer<util::STRING_LOCAL_BUFFER_SIZE> utf32(uint32_t max_bytes=0) const IPL_NOEXCEPT;
        /**
        \brief Return an ascii version of the string

        If \a max_bytes is not 0, the returned buffer contains at most
        \a max_bytes bytes. It is still guaranteed to be correctly encoded
        (i.e. no incomplete multi-byte code at the end) but might not be
        null terminated.

        Since only a few characters of unicode can be represented as ascii,
        the string is likely to contain unknown characters (?).

        \errors see setString()
        \errorindicator hasError()
        **/
        util::DataBuffer<util::STRING_LOCAL_BUFFER_SIZE> ascii(uint32_t max_bytes=0) const IPL_NOEXCEPT;
        /**
        \brief BROKEN AS DESIGNED, DO NOT USE!
        **/
        util::DataBuffer<util::STRING_LOCAL_BUFFER_SIZE> ucs(uint32_t max_bytes=0) const IPL_NOEXCEPT;

        using DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator +;
        /**
            \brief appends a unicode string to another one
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        util::UnicodeString8 operator+(const UnicodeString8& us) const IPL_NOEXCEPT;
        UnicodeString8 operator + (const UnicodeString16 &other) const IPL_NOEXCEPT {
            return operator + (UnicodeString8(other));
        }
        /**
            \brief appends a unicode string to another one
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        inline util::UnicodeString8& operator+=(const UnicodeString8& us) IPL_NOEXCEPT {return append(us);}
        inline util::UnicodeString8 &operator += (const UnicodeString16 &other) IPL_NOEXCEPT {
            return append(other);
        }
        /**
            \brief swap two characters in a string, invalidates \p a and \p b
            \errors
                util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
            \errorindicator
                hasError()
        **/
        void swap(iterator& a, iterator& b) IPL_NOEXCEPT;
        /**
            \brief assignment operator
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& operator=(UnicodeString8 const& us) IPL_NOEXCEPT;
        /**
            \brief assignment operator
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& operator=(UnicodeString16 const& us) IPL_NOEXCEPT;

        UnicodeString8 &operator = (const ipl::unicode::String &other) IPL_NOEXCEPT;

        using DataBuffer<STRING_LOCAL_BUFFER_SIZE>::compare;
        /**
            \brief compares two unicode strings
            \errors
                none
        **/
// #ifdef __clang__
// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Woverloaded-virtual"
// #endif
        int32_t compare(UnicodeString8 const & str) const IPL_NOEXCEPT {
            return util::DataBuffer<STRING_LOCAL_BUFFER_SIZE>::compare(str);
        }
        int32_t compare(const UnicodeString16 &other) const IPL_NOEXCEPT {
            return util::DataBuffer<STRING_LOCAL_BUFFER_SIZE>::compare(UnicodeString8(other));
        }
// #ifdef __clang__
// #pragma clang diagnostic pop
// #endif

        /**
            \brief direct access to the character

            this is just a convenience function that uses iterators to reach the desired location.
            \errors
                util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
            \errorindicator
                hasError()
        **/
        UnicodeChar get(uint32_t position) const IPL_NOEXCEPT;
        /**
            \brief search the position of a substring
            \return an iterator to the position of the first character of the matching string or end(), if the string is not present,
                    or begin() if \p str is empty
            \errors
                util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
            \errorindicator
                hasError()
        **/
        iterator findOccurrenceOf(UnicodeString8 const& str) const IPL_NOEXCEPT;
        iterator findOccurrenceOf(const UnicodeString16 &str) const IPL_NOEXCEPT {
            return findOccurrenceOf(UnicodeString8(str));
        }
        /**
            \brief search the position of a substring
            \return an iterator to the position of the first character of the matching string or end(), if the string is not present or empty
            \errors
                util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
            \errorindicator
                hasError()
        **/
        iterator findLastOccurrenceOf(UnicodeString8 const& str) const IPL_NOEXCEPT;
        iterator findLastOccurrenceOf(const UnicodeString16 &str) const IPL_NOEXCEPT {
            return findLastOccurrenceOf(UnicodeString8(str));
        }
        /**
            \brief search the position of a character
            \return an iterator to the position of the character of the matching string or end(), if the string is not present
            \errors
                util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
            \errorindicator
                hasError()
        **/
        iterator findOccurrenceOf(UnicodeChar const& ch) const IPL_NOEXCEPT;
        /**
            \brief search the position of a character
            \return an iterator to the position of the character of the matching string or end(), if the string is not present
            \errors
                util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
            \errorindicator
                hasError()
        **/
        iterator findLastOccurrenceOf(UnicodeChar const& str) const IPL_NOEXCEPT;
        /**
            \brief count the number of occurrences
            \return UINT32_MAX, if \p str is empty\n
                    the number of occurrences, otherwise
            \errors
                util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
            \errorindicator
                hasError()
        **/
        uint32_t countOccurrenceOf(UnicodeString8 const& str) const IPL_NOEXCEPT;
        uint32_t countOccurrenceOf(const UnicodeString16 &str) const IPL_NOEXCEPT {
            return countOccurrenceOf(UnicodeString8(str));
        }
        /**
            \brief returns a substring of that string
            \errors
                see setString
            \errorindicator
                errorindicator of returned string
        **/
        UnicodeString8 substring(iterator const& from, iterator const& to) const IPL_NOEXCEPT;
        /**
            \brief allows to replace a \<number> token through another string
            \errors
                see setString
            \errorindicator
                errorindicator of returned string
        **/
        UnicodeString8 argument(UnicodeString8 const& arg) IPL_NOEXCEPT;
        UnicodeString8 argument(const UnicodeString16 &arg) IPL_NOEXCEPT {
            return argument(UnicodeString8(arg));
        }
        /**
            \brief splits up a unicode string into several string parts
            \param token the token at which the string should be broken up
            \param result the splitted string parts are written into that parameter. The user must make sure that enough memory is given to store the strings in the array. If result is NULL, nothing is written and only the value is returned
            \param max_splits the maximum number of splits allowed.
            \param keep_empty_strings determines if empty substrings should be kept or discarded
            \return the number of splitted strings
            \errors
                see setString
            \errorindicator
                errorindicator of returned strings
        **/
        uint32_t split(UnicodeChar token, UnicodeString8** result, uint32_t max_splits, bool keep_empty_strings=false) const IPL_NOEXCEPT;
        /**
            \brief get internal storage format
            \errors
                none
        **/
        static Encoding getInternalFormat() IPL_NOEXCEPT {return UTF8;}
        /**
            \brief check validity of string data
        **/
        bool isStringDataValid() const IPL_NOEXCEPT;
        /**
            \brief checks if the current string ends with \p str
            \return true, if the current string ends with \p str or \p str is empty\n
                    false, otherwise
        **/
        bool endsWith(const util::UnicodeString8& str) const IPL_NOEXCEPT;
        bool endsWith(const UnicodeString16 &str) const IPL_NOEXCEPT {
            return endsWith(UnicodeString8(str));
        }
        /**
            \brief checks if the current string begins with str
            \return true, if the current string begins with \p str or \p str is empty \n
                    false, otherwise
        **/
        bool beginsWith(const util::UnicodeString8& str) const IPL_NOEXCEPT;
        bool beginsWith(const UnicodeString16 &str) const IPL_NOEXCEPT {
            return beginsWith(UnicodeString8(str));
        }
        /**
            \brief checks if the current string ends with ch
        **/
        bool endsWith(const util::UnicodeChar& ch) const IPL_NOEXCEPT;
        /**
            \brief checks if the current string begins with ch
        **/
        bool beginsWith(const util::UnicodeChar& ch) const IPL_NOEXCEPT;
        /**
            \brief empties a string
        **/
        inline void clear() IPL_NOEXCEPT {erase(begin(), end());}
        /**
            \brief checks if the current string contains \p str
            \return true , if current string contains \p str or \p str is empty\n
                    false, otherwise
        **/
        inline bool contains(const util::UnicodeString8& str) const IPL_NOEXCEPT
        {
            if (this->size() == 0 && this->operator==(str))
            {
                return true;
            }
            return findOccurrenceOf(str) != end();
        }
        inline bool contains(const UnicodeString16 &str) const IPL_NOEXCEPT
        {
            if (this->size() == 0 && this->operator==(str))
            {
                return true;
            }
            return findOccurrenceOf(str) != end();
        }
        /**
            \brief checks if the current string contains ch
        **/
        inline bool contains(const util::UnicodeChar& ch) const IPL_NOEXCEPT {return findOccurrenceOf(ch) != end();}
        /**
            \brief removes whitespaces at the beginning of the string
        **/
        void ltrim() IPL_NOEXCEPT;
        /**
            \brief removes whitespaces at the end of the string
        **/
        void rtrim() IPL_NOEXCEPT;
        /**
            \brief removes whitespaces at the beginning and end of the string
        **/
        void trim() IPL_NOEXCEPT;
        /**
            \brief appends an integer to the string
            \param num the number to be appended

            this function does NOT consider locales when converting numbers to strings.
                See class UnicodeTransformer if you need Locale-dependent conversion
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& appendNum(int32_t num) IPL_NOEXCEPT;
        /**
            \brief appends an integer to the string
            \param num the number to be appended

            this function does NOT consider locales when converting numbers to strings.
                See class UnicodeTransformer if you need Locale-dependent conversion
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& appendNum(double num) IPL_NOEXCEPT;
        /**
            \brief appends an integer to the string
            \param num the number to be appended

            this function does NOT consider locales when converting numbers to strings.
                See class UnicodeTransformer if you need Locale-dependent conversion
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& appendNum(uint32_t num) IPL_NOEXCEPT;
        /**
            \brief appends an integer to the string
            \param num the number to be appended

            this function does NOT consider locales when converting numbers to strings.
                See class UnicodeTransformer if you need Locale-dependent conversion
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& appendNum(int64_t num) IPL_NOEXCEPT;
        /**
            \brief appends an integer to the string
            \param num the number to be appended

            this function does NOT consider locales when converting numbers to strings.
                See class UnicodeTransformer if you need Locale-dependent conversion
            \errors
                ipl::CommonError with ID OUT_OF_MEMORY
            \errorindicator
                hasError()
        **/
        UnicodeString8& appendNum(uint64_t num) IPL_NOEXCEPT;
    //     /**
    //         \brief converts the string to uppercase
    //
    //         just a convenience function, see UnicodeTransformer for details
    //     **/
    //     UnicodeString8 toUpper() const IPL_NOEXCEPT;
    //     /**
    //         \brief converts the string to lowercase
    //
    //         just a convenience function, see UnicodeTransformer for details
    //     **/
    //     UnicodeString8 toLower() const IPL_NOEXCEPT;

//         operator UCSWrapper<UnicodeString8>() const IPL_NOEXCEPT
//         {
//             return UCSWrapper<UnicodeString8>(*this);
//         }

        operator ipl::unicode::String () const IPL_NOEXCEPT {
            return ipl::unicode::String(ipl::SharedBuf(retrieveData(), size()), ipl::unicode::UTF8);
        }

        operator osal::UnicodeString () const IPL_NOEXCEPT {
            return operator ipl::unicode::String ();
        }

        using DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator <;
        /**
            \brief compares two strings byte-wise, for advanced string comparison see Collation class
        **/
        bool operator<(const UnicodeString8& str) const IPL_NOEXCEPT {
            return ((DataBuffer<STRING_LOCAL_BUFFER_SIZE>*)this)->operator<((DataBuffer<STRING_LOCAL_BUFFER_SIZE>&)str);
        }
        /*!
            \b Warning! Not dual to UnicodeString16::operator > (const UnicodeString8 &)!
         */
        bool operator < (const UnicodeString16 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator < (UnicodeString8(other));
        }

        /**
            \brief compares two strings byte-wise, for advanced string comparison see Collation class
        **/
        bool operator==(const UnicodeString8& str) const IPL_NOEXCEPT {
            return ((DataBuffer<STRING_LOCAL_BUFFER_SIZE>*)this)->operator==((DataBuffer<STRING_LOCAL_BUFFER_SIZE>&)str);
        }
        bool operator == (const UnicodeString16 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator == (UnicodeString8(other));
        }

        bool operator != (const UnicodeString8 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator != (other);
        }
        bool operator != (const UnicodeString16 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator != (UnicodeString8(other));
        }
        bool operator <= (const UnicodeString8 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator <= (other);
        }
        bool operator <= (const UnicodeString16 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator <= (UnicodeString8(other));
        }
        bool operator > (const UnicodeString8 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator > (other);
        }
        bool operator > (const UnicodeString16 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator > (UnicodeString8(other));
        }
        bool operator >= (const UnicodeString8 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator >= (other);
        }
        bool operator >= (const UnicodeString16 &other) const IPL_NOEXCEPT {
            return DataBuffer<STRING_LOCAL_BUFFER_SIZE>::operator >= (UnicodeString8(other));
        }

        /**
            \brief replaces all occurrences of the string \p find with the string \p replaceWith
            \return a copy of this, if \p find is empty,\n
                    the string with the replacements, otherwise
        **/
        UnicodeString8 replace(UnicodeString8 const& find, UnicodeString8 const& replaceWith) IPL_NOEXCEPT;
        UnicodeString8 replace(const UnicodeString8 &find, const UnicodeString16 &replaceWith) IPL_NOEXCEPT {
            return replace(find, UnicodeString8(replaceWith));
        }
        UnicodeString8 replace(const UnicodeString16 &find, const UnicodeString8 &replaceWith) IPL_NOEXCEPT {
            return replace(UnicodeString8(find), replaceWith);
        }
        UnicodeString8 replace(const UnicodeString16 &find, const UnicodeString16 &replaceWith) IPL_NOEXCEPT {
            return replace(UnicodeString8(find), UnicodeString8(replaceWith));
        }

    protected:
        /** determine the length of a code point sequence
            \brief get the number of code units a code point consists of
            \errors
                util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
            \errorindicator
                return true
        **/
        static bool sequenceLength(uint8_t const * const lead_sequence, uint8_t& length, int32_t stoplength) IPL_NOEXCEPT;
        /**
            \brief convert a code point to utf-8
            \param codepoint the coidepoint to convert
            \param buffer the output buffer for the utf-8 coded sequence
            \return the number of code units needed to store the codepoint in utf8
            \errors
                none
        **/
        static uint8_t cpToUtf8(UnicodeChar codepoint, uint8_t buffer[4]) IPL_NOEXCEPT;
        /**
            \brief
                Get a char pointer of the data.

                Be aware that this function does not guarantee zero-termination of the data.
                Therefore it is protected here. See usage notes in UnicodeString.hxx
            \return const char pointer to the data.
            \note Behavior for invalid unicode codepoint is undefined
        **/
        char const* char_str() const IPL_NOEXCEPT {return (char const*)retrieveData();}

        /**
            \brief
                Get a wchar pointer of the data.

                Be aware that this function does not guarantee zero-termination of the data.
                Therefore it is protected here. See usage notes in UnicodeString.hxx
            \return const wchar_t pointer to the data.
        **/
        wchar_t const* wchar_str() const IPL_NOEXCEPT {return ipl::cast_without_warning<wchar_t const*>(retrieveData());}

    };

}  // end of namespace util

/**
    \brief global stream operator that takes a unicode string
    \errors
        util::UnicodeError with ID UNICODESTRING_INVALID_ENCODING
    \errorindicator
        errorindicator of UnicodeString us
**/
UTIL_EXPORT ipl::ostream& operator<<(ipl::ostream& out, const util::UnicodeString8& us) IPL_NOEXCEPT;

#endif
