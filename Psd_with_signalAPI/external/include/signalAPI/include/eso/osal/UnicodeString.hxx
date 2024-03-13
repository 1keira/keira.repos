/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_UNICODESTRING_HXX
#define OSAL_UNICODESTRING_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>
#include <common/unicode.hxx>

#if defined IPL_OS_POSIX
#    include "posix/PathDefs.hxx"
#elif defined (IPL_OS_WINPC)
#    include "win32/PathDefs.hxx"
#elif defined (IPL_OS_INTEGRITY)
#    include "integrity/PathDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif
#include <osal/osal_dso.h>

#include <osal/RefCounted.hxx>

#include <string.h>

namespace osal {

#if defined (IPL_OS_POSIX) || defined (IPL_OS_INTEGRITY)
    typedef char native_utf;
#elif defined (IPL_OS_WINPC)
    typedef wchar_t native_utf;
#else
#    error "error undefined IPL_OS_ variant"
#endif

    /*!
        \brief \b OBSOLETE! Do not use. Use ipl::unicode::String instead
        or maybe osal::Path
    */
    class OSAL_EXPORT UnicodeString :
        public osal::RefCounted
    {
    public: // constants

        //! possibly encoding variants
        enum Encoding
        {
            ASCII,
            UTF8,
            UTF16,
            UTF32
        };

        //! different modes of memory management
        enum StoreMode
        {
            //! take the data, don't copy it, don't delete it
            SHARED,
            //! \brief
            //! take the data, don't copy it, delete it when the
            //! last reference goes away
            TAKE_OWNERSHIP,
            //! make a copy of the data, delete it when the last
            //! reference goes away
            MAKE_COPY
        };

    public: // functions

        //! constructs an empty unicode string
        UnicodeString() :
            m_data(),
            m_bytes(),
            m_mode(SHARED)
        { }

        UnicodeString(const ipl::unicode::String &other): m_mode(MAKE_COPY) {
            ipl::SharedBuf buf(other.encode(ipl::unicode::NATIVE));
            m_data=buf;
            m_bytes=buf.bytes();
            checkStorage();
        }

        //! \brief
        //!    constructs a read-only unicode string from \c data which
        //!    is a sequence of \c bytes bytes.
        UnicodeString(const char *data, const size_t bytes, const StoreMode mode) :
            m_data(data), m_bytes(bytes), m_mode( mode )
        {
            checkStorage();
        }

        /**
        * \brief
        *     Create a UnicodeString object from the given ASCII
        *     string \c s

        *     The ASCII string \c s will be converted into native
        *     unicode encoding. For this operation always a copy needs
        *     to be made.
        **/
        explicit UnicodeString(const ipl::string &s);
        explicit UnicodeString(const char *s);
        explicit UnicodeString(const wchar_t *s);

        /**
        * \brief
        *     Create a UnicodeString object from the given wide
        *     character string \c s

        *     The wide-character string \c s will be converted into
        *     native unicode encoding. For this operation always a
        *     copy needs to be made.
        **/
        explicit UnicodeString(const ipl::wstring &s);

        //! \brief
        //! decrease reference count, possibly freeing the underlying
        //! data
        ~UnicodeString()
        {
            this->decrement();
        }

        inline operator ipl::unicode::String() const;

        /**
        * \brief
        *    The global OSAL encoding for UnicodeStrings
        **/
        static Encoding getSystemEncoding()
        {
            return s_encoding;
        }

        /**
        * \brief
        *    read-only access to the currently stored string data

        *    The returned ptr. may be NULL if the string is
        *    unset/empty.
        **/
        const char* data() const
        { return m_data; }

        /**
        * \brief
        *     same as data() but in native utf data type
        **/
        const native_utf* nativeData() const
        {
            return (const native_utf*)m_data;
        }

        //! number of valid bytes in the string
        size_t size() const
        { return m_bytes; }

        /**
        * \brief
        *     Convert the current UnicodeString into an ipl::string
        *     object

        *     The current UnicodeString will be converted into an
        *     ipl::string object in ASCII format. If any characters
        *     can't be represented in ASCII then an empty string will
        *     be returned.
        **/
        operator ipl::string() const;

        /**
        * \brief
        *     Convert the current UnicodeString into an ipl::wstring
        *     object

        *     The current UnicodeString will be converted into an
        *     ipl::wstring object in a platform-dependent unicode
        *     encoding.
        **/
        operator ipl::wstring() const;

    protected: // functions

        //! called by base class when reference count hits zero
        void destroy()
        {
            if( m_data && m_mode != SHARED )
            {
                delete[] m_data;
            }

            m_data = NULL;
            m_mode = SHARED;
        }

        //! \brief
        //!    request to make a deep copy of the current string, if it
        //!    isn't one already
        void checkStorage()
        {
            if( m_mode != MAKE_COPY )
                return;

            char *cpy = NULL;

            while( !cpy )
            {
                cpy = new(ipl::nothrow) char[m_bytes];
                if( ! cpy ) // BRANCH_COVERAGE_UNTESTABLE
                {
                    // die or smth.
                    IPL_OOM("cannot make UC copy");
                }
            }

            ::memcpy( cpy, m_data, m_bytes );

            m_data = cpy;
        }

        // should only be called from derived class constructor
        // otherwise if called more than once in the lifetime then
        // memory might be lost or refcounting is messed up
        void setData(const char *data, const size_t bytes,
            const StoreMode mode)
        {
            m_data = data;
            m_bytes = bytes;
            m_mode = mode;

            checkStorage();
        }

    private: // data
        //! the read-only string data
        const char *m_data;
        //! the number of valid bytes in \c m_data
        size_t m_bytes;
        //! encoding of the string data
        static const Encoding s_encoding;
        //! whether \c m_data was internally allocated
        StoreMode m_mode;
    };

}  // end of namespace osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/UnicodeString.inl"
#elif defined IPL_OS_WINPC
#    include "win32/UnicodeString.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
