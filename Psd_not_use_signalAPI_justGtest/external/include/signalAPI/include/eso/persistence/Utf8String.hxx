/*****************************************************************************/
/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
    $Id$
*/
/*****************************************************************************/
#ifndef PERSISTENCE_UTF8STRING_HXX
#define PERSISTENCE_UTF8STRING_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <util/UnicodeString8.hxx>
#include <util/UnicodeString16.hxx>
#include <common/types/string.hxx>
#include <common/types/vector.hxx> // for ugly hack vector

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/
    /*!
        \brief Convenient \ref util::UnicodeString "UnicodeString"
        locked to UTF8

        In order to interface framework code based on transparent unicode
        strings, SQLite (or other) code based on char-strings and
        source code needing to state string literals, a fixed common encoding
        of utf8 comes in handy.
        The framework can use the smart string, the simpler code can use
        the encoded rendition, and the programmer just needs to remember
        to encode funny characters by hand.

        \b WARNING: There are still bugs lurking that damage strings when
        passing them by value (incorrect copy).
        Keep that in mind and prefer passing by reference.

        \todo Fix the copy problem!
    */
    class Utf8String: public util::UnicodeString8 {

        //! \brief Convenient shortcut to parallel UnicodeString8
        typedef util::UnicodeString16 UnicodeString16;

    public:
        Utf8String() IPL_NOEXCEPT: UnicodeString8() {}
        /*!
            \brief Construct a string from an already utf8 encoded
            sequence of chars
        */
        Utf8String(const char *utf8) IPL_NOEXCEPT: UnicodeString8(utf8, UTF8) {}
        /*!
            \brief Construct a string from an already utf8 encoded
            sequence of chars
        */
        Utf8String(const ipl::string &utf8) IPL_NOEXCEPT: UnicodeString8(utf8.c_str(), UTF8) {}

        Utf8String(const Utf8String &other) IPL_NOEXCEPT: UnicodeString8(other) {}
        Utf8String(const UnicodeString8 &other) IPL_NOEXCEPT: UnicodeString8(other) {}
        Utf8String(const UnicodeString16 &other) IPL_NOEXCEPT: UnicodeString8(other) {}

        operator const char *() const IPL_NOEXCEPT {
            m_hack.resize(size()+1);
            memcpy(&m_hack[0], char_str(), size());
            m_hack[size()]=0;
            return &m_hack[0];
        }

        // needed to avoid implicit definition
        Utf8String &operator = (const Utf8String &other) IPL_NOEXCEPT {
            UnicodeString8::operator = (other);
            return *this;
        }
        Utf8String &operator = (const util::UnicodeString8 &other) IPL_NOEXCEPT {
            UnicodeString8::operator = (other);
            return *this;
        }
        Utf8String &operator = (const util::UnicodeString16 &other) IPL_NOEXCEPT {
            UnicodeString8::operator = (other);
            return *this;
        }

        //! \brief This shouldn't be necessary at all, but seemingly not
        bool operator == (const UnicodeString8 &other) const IPL_NOEXCEPT {
//            ipl::cerr << "\"" << *this
//                      << "\".operator == (UnicodeString8::\" << other << "\") = "
//                      << (const_cast<Utf8String *>(this)->UnicodeString8::operator == (
//                              const_cast<UnicodeString8 &>(other)
//                         )? "true" : "false")
//                      << ipl::endl;
//             // Ugly workaround for missin constness in ipl::DataBuffer:
//             return const_cast<Utf8String *>(this)->UnicodeString8::operator == (
//                 const_cast<UnicodeString8 &>(other)
//             );
            return UnicodeString8::operator == (other);
        }
        bool operator != (const UnicodeString8 &other) const IPL_NOEXCEPT {
            return !operator == (other);
        }
        //! \brief This shouldn't be necessary at all, but seemingly not
        bool operator == (const UnicodeString16 &other) const IPL_NOEXCEPT {
//            ipl::cerr << "\"" << *this
//                      << "\".operator == (UnicodeString8::\" << other << "\") = "
//                      << (const_cast<Utf8String *>(this)->UnicodeString8::operator == (
//                              const_cast<UnicodeString16 &>(other)
//                         )? "true" : "false")
//                      << ipl::endl;
//             // Ugly workaround for missin constness in ipl::DataBuffer:
//             return const_cast<Utf8String *>(this)->UnicodeString8::operator == (
//                 const_cast<UnicodeString16 &>(other)
//             );
            return UnicodeString8::operator == ((UnicodeString8)other);
        }
        bool operator != (const UnicodeString16 &other) const IPL_NOEXCEPT {
            return !operator == (other);
        }

        bool operator < (const UnicodeString8 &other) const IPL_NOEXCEPT {
            // Ugly workaround for missin constness in ipl::DataBuffer:
            return const_cast<Utf8String *>(this)->UnicodeString8::operator < (
                const_cast<UnicodeString8 &>(other)
            );
        }
        bool operator <= (const UnicodeString8 &other) const IPL_NOEXCEPT { return *this<other || *this==other; }
        bool operator >  (const UnicodeString8 &other) const IPL_NOEXCEPT { return !(*this<=other); }
        bool operator >= (const UnicodeString8 &other) const IPL_NOEXCEPT { return !(*this<other); }

        bool operator < (const UnicodeString16 &other) const IPL_NOEXCEPT {
//             // Ugly workaround for missin constness in ipl::DataBuffer:
//             return const_cast<Utf8String *>(this)->UnicodeString8::operator == (
//                 const_cast<UnicodeString16 &>(other)
//             );
            return UnicodeString8::operator < ((UnicodeString8)other);
        }
        bool operator <= (const UnicodeString16 &other) const IPL_NOEXCEPT { return *this<other || *this==other; }
        bool operator >  (const UnicodeString16 &other) const IPL_NOEXCEPT { return !(*this<=other); }
        bool operator >= (const UnicodeString16 &other) const IPL_NOEXCEPT { return !(*this<other); }

        bool operator < (const DataBuffer& db) const IPL_NOEXCEPT {
            return util::DataBuffer<util::STRING_LOCAL_BUFFER_SIZE>::operator<(db);
        }

        Utf8String &operator += (const char *other) IPL_NOEXCEPT {
            return operator += (Utf8String(other));
        }
        Utf8String &operator += (const ipl::string &other) IPL_NOEXCEPT {
            return operator += (Utf8String(other));
        }
        Utf8String &operator += (const UnicodeString8 &other) IPL_NOEXCEPT {
            UnicodeString8::operator = (operator + (other));
            return *this;
        }
        Utf8String &operator += (const UnicodeString16 &other) IPL_NOEXCEPT {
            UnicodeString8::operator = (operator + ((UnicodeString8)other));
            return *this;
        }

    protected:
        //! \brief Ugly workaround for missing zero termination in UnicodeString8
        mutable ipl::vector<char> m_hack;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
