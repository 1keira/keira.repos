/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef COMMON_BUFFERS_HXX
#define COMMON_BUFFERS_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <threadsafe/AtomicCounter.hxx>

#include "iplcommon_dso.h"
#include "ipl_namespace.hxx"
#include "PseudoBool.hxx"
#include "Macros.hxx"

#include <stddef.h>
#include <string.h>

// #include <common/streams/iostream.hxx>

/*****************************************************************************/

namespace IPL_NAMESPACE {

/*****************************************************************************/

    /*!
        Pointer-ish thing that knows how to free itself

        The Ptr is similar to a dumb pointer in that it points to
        some location in memory and doesn't attempt any
        smart lifecycle management.
        Contrary to a plain pointer, though, it retains information about
        how the memory has been allocated in the first place.

        This enables the user to deallocate the memory
        <em>regardless how the memory was allocated</em>
        by simply calling Ptr::free().
        Also a client requiring memory that has been allocated in a certain way
        (e.g. for DMA) can check that and either reject or copy "wrong" data.

        \a WARNING: This is preliminary code. Don't rely on it.
    */
    struct IPLCOMMON_EXPORT Ptr {

        class IPLCOMMON_EXPORT Allocator {
        public:
            virtual ~Allocator() IPL_NOEXCEPT=default;
        protected:
            //! \brief Free memory (any offset, NULL safe)
            //!
            //! If you override this, be aware that \a p.p may not point to
            //! the original address anymore.
            //! Use the information your malloc() has stored in p.context
            //! instead.
            virtual void free(const Ptr &p) const IPL_NOEXCEPT=0;
            void free(Ptr &ptr) const IPL_NOEXCEPT {  // helps debugging
                free((const Ptr)ptr);
                ptr.p=nullptr;
                ptr.context=nullptr;
            }
            friend struct Ptr;  // calls free
        };

        //! \brief The raw address we're pointing to
        //!
        //! Most of the time you will not need this,
        //! as casting to the needed pointer type is more convenient.
        void *p;
        //! \brief Semi-internal pointer to the Allocator responsible for the
        //! pointed-to buffer
        const Allocator *allocator;
        //! \brief Totally internal data the Allocator needs to free the buffer
        void *context;

        //! \brief Create an invalid (NULL) Ptr
        Ptr() IPL_NOEXCEPT: p(nullptr), allocator(nullptr), context(nullptr) {}
        Ptr(const Ptr &other) IPL_NOEXCEPT: p(other.p), allocator(other.allocator),
            context(other.context) {}
        //! \brief Usually you do not use this but acquire a Ptr
        //! from an Allocator instead
        Ptr(void *p, const Allocator *allocator, void *context) IPL_NOEXCEPT:
            p(p), allocator(allocator), context(context) {}

        //! \brief Deallocate the pointed-to buffer
        void free() const IPL_NOEXCEPT { if(allocator) allocator->free(*this); }

        //! \brief Access memory - not necessarily properly aligned
        template<typename T> operator T* () const IPL_NOEXCEPT {
            return reinterpret_cast<T *>(p);
        }

        Ptr& operator=(const Ptr& other) IPL_NOEXCEPT {
            if ( this != &other ) {
                p = other.p;
                allocator = other.allocator;
                context = other.context;
            }
            return *this;
        }

        //! \brief a.k.a. operator bool () const
        operator PseudoBool () const IPL_NOEXCEPT { return p? &PSEUDO_TRUE : PSEUDO_FALSE; }
        bool operator ! () const IPL_NOEXCEPT { return p==nullptr; }

        //! \brief Same address?
        bool operator == (const Ptr &other) const IPL_NOEXCEPT { return p==other.p; }
        //! \brief Different address?
        bool operator != (const Ptr &other) const IPL_NOEXCEPT { return p!=other.p; }

        //! \brief Add byte offset
        Ptr operator + (size_t offset) const IPL_NOEXCEPT {
            return Ptr(p? reinterpret_cast<unsigned char *>(p)+offset : nullptr,
                       allocator, context);
        }
        //! \brief Subtract byte offset
        Ptr operator - (size_t offset) const IPL_NOEXCEPT {
            return Ptr(p? reinterpret_cast<unsigned char *>(p)-offset : nullptr,
                       allocator, context);
        }

        //! \brief Add byte offset
        Ptr &operator += (size_t offset) IPL_NOEXCEPT {
            if(p) p=reinterpret_cast<unsigned char *>(p)+offset;
            return *this;
        }
        //! \brief Subtract byte offset
        Ptr &operator -= (size_t offset) IPL_NOEXCEPT {
            if(p) p=reinterpret_cast<unsigned char *>(p)-offset;
            return *this;
        }

        //! \brief A NULL-Ptr whose free() deletes us
        //!
        //! This is \b not a general null %Ptr, use Ptr() or {} instead.
        Ptr null() const IPL_NOEXCEPT { return Ptr(nullptr, allocator, context); }
    };

/*****************************************************************************/

    /*!
        \brief Ptr with size

        A Buf is a Ptr that knows the size of the pointed-to buffer.

    */
    struct IPLCOMMON_EXPORT Buf: public Ptr {

        //! \brief You can derive your own allocators from this
        class IPLCOMMON_EXPORT Allocator: public Ptr::Allocator {
        public:
            //! \brief Allocate at least \a bytes of memory
            //!
            //! If you override this, store the allocated buffer in \a p,
            //! yourself in \a allocator and any information free() needs
            //! in \a context.
            //! And make sure \a p is suitably aligned for any type.
            virtual Buf malloc(size_t bytes) const IPL_NOEXCEPT;
            //! \brief A newly allocated buffer with the same size and data
            //! but independent lifetime
            Buf copy(const Buf &buf) const IPL_NOEXCEPT {
                auto res{malloc(buf.bytes)};
                memcpy(res, buf, buf.bytes);
                return res;
            }
            using Ptr::Allocator::free;
            virtual void free(const Ptr &p) const IPL_NOEXCEPT;
        };
        
        //! \brief Wrapper around another Allocator preallocating
        //! header and footer space
        class IPLCOMMON_EXPORT PreAllocator: public Allocator {
        public:
            PreAllocator(
                size_t bytes_header, size_t bytes_footer=0,
                Allocator &underlying=DEFAULT_ALLOCATOR
            ): bytes_header(bytes_header), bytes_footer(bytes_footer),
            underlying(underlying) {}
            PreAllocator(size_t bytes_header, Allocator &underlying):
                PreAllocator(bytes_header, 0, underlying) {}

            //! The returned buffer is only suitably aligned if bytes_header is.
            Buf malloc(size_t bytes) const IPL_NOEXCEPT override;
            using Ptr::Allocator::free;
            void free(const Ptr &p) const IPL_NOEXCEPT override;

            //! \brief Check whether \p p was allocated by this PreAllocator
            //!
            //! header(), footer() and all() must only be called if this
            //! returns \c true.
            bool owns(const Ptr &p) { return p.allocator==this; }
            //! \brief Given a \p buf allocated by this PreAllocator,
            //! return the preallocated header in front of it
            //!
            //! Freeing this or the original buffer will delete both.
            Buf header(const Buf &buf) {
                IPL_ASSERT(owns(buf));
                return Buf(((const Info *)buf.context)->begin, this,
                           buf.context, bytes_header);
            }
            //! \brief Given a \p buf allocated by this PreAllocator,
            //! return the preallocated footer behind it
            //!
            //! Freeing this or the original buffer will delete both.
            Buf footer(const Buf &buf) {
                IPL_ASSERT(owns(buf));
                return Buf(((const Info *)buf.context)->footer, this,
                buf.context, bytes_footer);
            }
            //! \brief Given a \p buf allocated by this PreAllocator,
            //! return the whole of header, original buffer and footer
            //!
            //! Freeing this or the original buffer will delete both.
            Buf all(const Buf &buf) {
                IPL_ASSERT(owns(buf));
                return Buf(((const Info *)buf.context)->begin, this,
                           buf.context, bytes_header+buf.bytes+bytes_footer);
            }
            
            const size_t bytes_header;
            const size_t bytes_footer;
            Allocator &underlying;
            
        protected:
            struct Info {
                void *begin;
                void *footer;
                void *underlying_context;
            };
        };
        
        //! \brief This one uses malloc/free internally
        static Allocator DEFAULT_ALLOCATOR;

        //! \brief The size of the pointed-to buffer in bytes (duh!)
        size_t bytes;

        //! \brief Create an invalid (NULL) Buf
        Buf() IPL_NOEXCEPT: Ptr(), bytes(0) {}
        Buf(const Buf &other) IPL_NOEXCEPT: Ptr(other), bytes(other.bytes) {}
        //! \brief Add a size to a Ptr
        Buf(const Ptr &ptr, size_t bytes) IPL_NOEXCEPT: Ptr(ptr), bytes(bytes) {}
        //! \brief Allocate \a bytes bytes via \a allocator
        Buf(size_t bytes, const Allocator &allocator=DEFAULT_ALLOCATOR) IPL_NOEXCEPT;
        //! \brief Usually you don't use this but
        //! Buf(size_t, Allocator &) or Allocator::malloc()
        Buf(void *p, const Ptr::Allocator *allocator, void *context, size_t bytes) IPL_NOEXCEPT:
            Ptr(p, allocator, context), bytes(bytes) {}

        Buf& operator=(const Buf& other) IPL_NOEXCEPT {
            if (this != &other) {
                this->Ptr::operator=((const Ptr&)other);
                bytes = other.bytes;
            }
            return *this;
        }

        //! \brief Add byte offset, adjusting \ref bytes
        Buf operator + (size_t offset) const IPL_NOEXCEPT {
            return Buf(Ptr::operator + (offset), bytes-offset);
        }
        //! \brief Subtract byte offset, adjusting \ref bytes
        Buf operator - (size_t offset) const IPL_NOEXCEPT {
            return Buf(Ptr::operator - (offset), bytes+offset);
        }
        //! \brief Add byte offset, adjusting \ref bytes
        Buf &operator += (size_t offset) IPL_NOEXCEPT {
            Ptr::operator += (offset);
            bytes-=offset;
            return *this;
        }
        //! \brief Subtract byte offset, adjusting \ref bytes
        Buf &operator -= (size_t offset) IPL_NOEXCEPT {
            Ptr::operator -= (offset);
            bytes+=offset;
            return *this;
        }
        //! \brief Reduce official size
        //!
        //! If you try to shrink below 0 bytes, the result has 0 bytes.
        Buf shrink(size_t by_bytes) const IPL_NOEXCEPT {
            if(bytes>by_bytes)
                return Buf(p, allocator, context, bytes-by_bytes);
            else
                return Buf(p, allocator, context, 0);
        }

        //! \brief A NULL-Buf whose free() deletes us
        //!
        //! This is \b not a general null %Buf, use Buf() or {} instead.
        Buf null() const IPL_NOEXCEPT { return Buf(nullptr, allocator, context, 0); }
        
        //! \brief A newly allocated buffer with the same size and data
        //! but independent lifetime
        //!
        //! This is a convenience wrapper for Allocator::copy(Buf).
        Buf copy(const Allocator &allocator=DEFAULT_ALLOCATOR) const IPL_NOEXCEPT {
            return allocator.copy(*this);
        }
    };

/*****************************************************************************/

    /*!
        \brief Similar to Buf but with reference counting
    */
    class IPLCOMMON_EXPORT SharedBuf {

        struct Overhead {
            threadsafe::AtomicCounter refs;
        };
        static const size_t OVERHEAD=
            // compile time reimplementation of ipl::align() from align.hxx
            sizeof(Overhead)+IPL_MAX_ALIGNMENT-1
            -(sizeof(Overhead)+IPL_MAX_ALIGNMENT-1)%IPL_MAX_ALIGNMENT;

    public:
        //! \brief Allocate nothing, the buffer is \b invalid
        //!
        //! You can assign from and to and compare, but other operations
        //! will/might crash
        SharedBuf() IPL_NOEXCEPT: offset(0) {}
        //! \brief Allocate \a bytes of payload
        SharedBuf(size_t bytes, const Buf::Allocator &allocator=Buf::DEFAULT_ALLOCATOR) IPL_NOEXCEPT:
            buf(allocator.malloc(bytes+OVERHEAD)), offset(OVERHEAD) { initref(); }
        //! \brief Allocate and copy \a bytes of payload from \a data
        SharedBuf(const void *data, size_t bytes, const Buf::Allocator &allocator=Buf::DEFAULT_ALLOCATOR) IPL_NOEXCEPT:
            buf(allocator.malloc(bytes+OVERHEAD)), offset(OVERHEAD) {
            initref();
            memcpy(buf+OVERHEAD, data, bytes);
        }
        //! \brief Share allocated buffer with \a other
        SharedBuf(const SharedBuf &other) IPL_NOEXCEPT:
            buf(other.buf), offset(other.offset) { ref(); }

    protected:
        //! \internal
        //! \a buf must already begin with an initialized refcounter!
        SharedBuf(const Buf &buf, size_t offset) IPL_NOEXCEPT:
            buf(buf), offset(offset) { ref(); }

    public:
        ~SharedBuf() IPL_NOEXCEPT { unref(); }

        SharedBuf &operator = (const SharedBuf &other) IPL_NOEXCEPT {
            if (this != &other) {
                other.ref();
                unref();
                buf=other.buf;
                offset=other.offset;
            }
            return *this;
        }

        //! \brief Check for validity
        operator PseudoBool () const { return buf; }

        size_t bytes() const IPL_NOEXCEPT { return buf.bytes-offset; }

        operator Buf () const IPL_NOEXCEPT {
            if(buf)
                return Buf(((unsigned char *)buf.p)+offset, buf.allocator,
                        buf.context, bytes());
            else
                return Buf();
        }
        //! \brief Access memory ??? not necessarily properly aligned
        template<typename T> operator T* () const IPL_NOEXCEPT { return buf+offset; }

        //! \brief Same buffer and offset?
        bool operator == (const SharedBuf &other) const IPL_NOEXCEPT {
            return buf==other.buf && offset==other.offset;
        }
        //! \brief Different buffer or offset?
        bool operator != (const SharedBuf &other) const IPL_NOEXCEPT {
            return !operator == (other);
        }

        //! \brief Add byte offset, adjusting \ref bytes
        //!
        //! \b Warning: buffer must be valid!
        SharedBuf operator + (size_t offset_) const IPL_NOEXCEPT {
            IPL_ASSERT(buf);
            return SharedBuf(buf, this->offset+offset_);
        }
        //! \brief Add byte offset, adjusting \ref bytes
        //!
        //! \b Warning: buffer must be valid!
        SharedBuf &operator += (size_t offset_) IPL_NOEXCEPT {
            IPL_ASSERT(buf);
            this->offset+=offset_;
            return *this;
        }
        //! \brief Reduce official size
        //!
        //! \b Warning: buffer must be valid!
        //!
        //! If you try to shrink below 0 bytes, the result has 0 bytes.
        SharedBuf shrink(size_t by_bytes) const IPL_NOEXCEPT {
            IPL_ASSERT(buf);
            if(buf.bytes>by_bytes)
                return SharedBuf(Buf(
                    buf.p, buf.allocator, buf.context, buf.bytes-by_bytes
                ), offset);
            else
                return SharedBuf(Buf(
                    buf.p, buf.allocator, buf.context, 0
                ), offset);
        }

    protected:
        void initref() const IPL_NOEXCEPT {
            if(buf) {
                Overhead &overhead(*(Overhead *)buf);
                overhead.refs=1;
            }
        }
        void ref() const IPL_NOEXCEPT {
            if(buf) {
                Overhead &overhead(*(Overhead *)buf);
                overhead.refs++;
            }
        }
        void unref() const IPL_NOEXCEPT {
            if(buf) {
                Overhead &overhead(*(Overhead *)buf);
                if(--overhead.refs==0)
                    buf.free();
            }
        }

        Buf buf;
        size_t offset;
    };

/*****************************************************************************/

}  // end of namespace IPL_NAMESPACE

/*****************************************************************************/
#endif
