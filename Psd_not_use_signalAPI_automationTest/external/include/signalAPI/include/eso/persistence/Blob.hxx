/*****************************************************************************/
/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
    $Id:$
*/
/*****************************************************************************/
#ifndef PERSISTENCE_BLOB_HXX
#define PERSISTENCE_BLOB_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <util/transport/Readable.hxx>

#include <stddef.h>
#include <string.h>

/*****************************************************************************/

namespace util {
    namespace transport {
        //class Readable;
        class DefaultBuffer;
    }
}

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/
    /*!
        \brief Bunch of bytes to be stored in persistence
    */
    class Blob {

    public://protected:
        typedef util::transport::Readable Readable;

    public:
        Blob()=default;
        Blob(const Blob &)=default;
        virtual ~Blob();  //!< \brief Just to make the compiler happy...
        Blob &operator = (const Blob &)=delete;

        virtual operator Readable () const IPL_NOEXCEPT=0;
        virtual Blob &operator = (const Readable &other) IPL_NOEXCEPT=0;
        virtual void setData(size_t bytes, const void *data) IPL_NOEXCEPT=0;

        bool operator == (const Blob &other) const IPL_NOEXCEPT {
            if(size()!=other.size()) return false;
            return memcmp(data(), other.data(), size())==0;
        }
        bool operator != (const Blob &other) const IPL_NOEXCEPT { return !operator == (other); }

    //protected:
        virtual size_t size() const IPL_NOEXCEPT=0;
        virtual const void *data() const IPL_NOEXCEPT=0;
    };

/*****************************************************************************/
    /*!
        \brief \ref util::transport::Readable "Readable" based implementation
    */
    // TODO: put where it belongs
    class ReadableBlob: public Blob {

    public:
        ReadableBlob() IPL_NOEXCEPT;
        ReadableBlob(const Readable &readable) IPL_NOEXCEPT;
        ReadableBlob(size_t bytes, const void *data) IPL_NOEXCEPT;

        virtual operator Readable () const IPL_NOEXCEPT;
        virtual Blob &operator = (const Readable &other) IPL_NOEXCEPT;
        virtual void setData(size_t bytes, const void *data) IPL_NOEXCEPT;

        const Readable &readable() const IPL_NOEXCEPT { return m_readable; }

//    protected:
        typedef util::transport::DefaultBuffer Buffer;

        virtual size_t size() const IPL_NOEXCEPT;
        virtual const void *data() const IPL_NOEXCEPT;

    protected:
        Readable m_readable;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
