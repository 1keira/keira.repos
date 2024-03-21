/*****************************************************************************/
/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
    $Id$
*/
/*****************************************************************************/
#ifndef PERSISTENCE_SERIALIZATION_HXX
#define PERSISTENCE_SERIALIZATION_HXX
/*****************************************************************************/

#include <ipl_config.h>

#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
#include <util/serializer/serializer.hxx>
#include <util/serializer/SerializerErrors.hxx>
#include <util/transport/Writeable.hxx>
#include <util/UnicodeString.hxx>
#include <comm/commtypes.hxx>
#include <comm/Error.hxx>
#else
#include <util/serializer/DefaultSerializerBE.hxx>
#include <util/serializer/DefaultDeserializerBE.hxx>
#include <comm/commidltypes.hxx>
#endif

#include "Blob.hxx"

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/
    /*!
        \brief Convenient \ref Blob "Buffer"/\ref util::serializer::IStreamSerializer "Serializer"/\ref util::serializer::IStreamDeserializer "Deserializer"

        It is not completely trivial to use the
        \ref util::serializer "serialization subsystem",
        but persistence users (as well as the persistence implementation itself)
        need simple means to serialize their data into a blob
        (and getting it back, of course).
        Therefore we provide a simple buffer that supports simple and naive use
        as well as more sophisticated, more efficient use.

        There are two modes how this class can be used to serialize your data.
        In \b naive \b mode you simply pipe in your data:
        \code
        persistence::Serialization buf;
        buf << foo
            << bar
            << thud;
        persistence.put("grunt", buf);
        \endcode
        This is simple and easy, but the downside is that the buffer might
        need to be resized internally, which is expensive,
        the more expensive the more data you put in.

        If your data is large you should serialize in two passes,
        one for size calculation and one for actual serialization into an
        appropriately-sized buffer:
        \code
        persistence::Serialization buf;
        buf.beginSizeCalc();
        buf << foo
            << bar
            << thud;
        buf.endSizeCalc();  // automagically resizes the internal buffer
        buf << foo
            << bar
            << thud;
        persistence.put("grunt", buf);
        \endcode
        Note that this differs a bit from the underlying
        \ref util::serializer::IStreamSerializer "IStreamSerializer" in that
        the buffer is handled internally for you.

        Deserialization works just as you'd expect:
        \code
        persistence::Serialization buf;
        persistence.get("grunt", buf);
        buf >> foo
            >> bar
            >> thud;
        \endcode

        \b Warning: This class behaves quite magicly!
        Do not expect serializing to work accross any other calls
        (like deserializing, casting to \ref Blob etc.).

        \b Implementation \b Note: The magic involves that Serialization's
        internal state must change even upon Blob's const methods,
        therefore the members must be mutable. Bummer.
    */
    class Serialization: public Blob {

    public:
        Serialization(size_t initial_size=0) IPL_NOEXCEPT:
            m_read_ok(true),
            m_write_ok(true),
            m_clean(false),
            m_buffer(initial_size) {

#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
            m_dryrun=false;
            m_cursor=0;
#else
            m_serializer.attachBuffer(m_buffer);
            m_deserializer.attachBuffer(m_buffer.getReadable());
#endif
        }

        Serialization(const Blob &other) IPL_NOEXCEPT:
            m_read_ok(true),
            m_write_ok(true),
            m_clean(false),
            m_buffer(Writeable(other)) {

#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
            m_dryrun=false;
            m_cursor=0;
#else
            m_serializer.attachBuffer(m_buffer);
            m_deserializer.attachBuffer(m_buffer.getReadable());
#endif
        }

        virtual ~Serialization() IPL_NOEXCEPT;

        virtual operator Readable () const IPL_NOEXCEPT;
        virtual Blob &operator = (const Readable &other) IPL_NOEXCEPT;
        virtual void setData(size_t bytes, const void *data) IPL_NOEXCEPT;

//    protected:
        virtual size_t size() const IPL_NOEXCEPT;
        virtual const void *data() const IPL_NOEXCEPT;

    public:
#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
        void beginSizeCalc() IPL_NOEXCEPT {
            IPL_ASSERT(!m_dryrun);
            m_dryrun=true;
        }
        void endSizeCalc() IPL_NOEXCEPT {
            IPL_ASSERT(m_dryrun);
            m_dryrun=false;
            m_buffer.resize(m_cursor);
            m_cursor=0;
        }
#else
        void beginSizeCalc() IPL_NOEXCEPT {
            m_serializer.detachBuffer();
            m_serializer.beginSizeCalc();
        }
        void endSizeCalc() IPL_NOEXCEPT {
            m_buffer.resize(m_serializer.endSizeCalc());
            m_serializer.attachBuffer(m_buffer);
        }
#endif

        inline Serialization &operator << (bool value) IPL_NOEXCEPT;
        inline Serialization &operator << (int8_t value) IPL_NOEXCEPT;
        inline Serialization &operator << (uint8_t value) IPL_NOEXCEPT;
        inline Serialization &operator << (int16_t value) IPL_NOEXCEPT;
        inline Serialization &operator << (uint16_t value) IPL_NOEXCEPT;
        inline Serialization &operator << (int32_t value) IPL_NOEXCEPT;
        inline Serialization &operator << (uint32_t value) IPL_NOEXCEPT;
        inline Serialization &operator << (int64_t value) IPL_NOEXCEPT;
        inline Serialization &operator << (uint64_t value) IPL_NOEXCEPT;
        inline Serialization &operator << (float value) IPL_NOEXCEPT;
        inline Serialization &operator << (double value) IPL_NOEXCEPT;
        inline Serialization &operator << (const util::UnicodeString8 &value) IPL_NOEXCEPT;
        inline Serialization &operator << (const util::UnicodeString16 &value) IPL_NOEXCEPT;

        inline Serialization &operator >> (bool &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (int8_t &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (uint8_t &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (int16_t &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (uint16_t &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (int32_t &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (uint32_t &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (int64_t &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (uint64_t &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (float &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (double &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (util::UnicodeString8 &value) IPL_NOEXCEPT;
        inline Serialization &operator >> (util::UnicodeString16 &value) IPL_NOEXCEPT;

        bool isValid() IPL_NOEXCEPT { return m_read_ok && m_write_ok; }

    protected:

        typedef util::transport::Writeable Writeable;

        void ensure_clean() const /* mutable! */ IPL_NOEXCEPT {
            if(!m_clean) {
#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
#else
                m_serializer.detachBuffer();
                m_deserializer.detachBuffer();
#endif
                m_buffer.commitBuffer();
                m_clean=true;
#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
                m_cursor=0;
#else
                m_serializer.attachBuffer(m_buffer);
                m_deserializer.attachBuffer(m_buffer.getReadable());
#endif
                m_read_ok=true;
                m_write_ok=true;
            }
        }

        typedef util::transport::Writeable Buffer;

#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
#else
        class Serializer:
            public util::serializer::DefaultSerializerBE {

        protected:
            //! \brief Autoresize
            virtual bool handle_overflow(size_t actual, unsigned requested) IPL_NOEXCEPT;
        };

        typedef util::serializer::DefaultDeserializerBE Deserializer;
#endif

        mutable bool m_read_ok;
        mutable bool m_write_ok;
        mutable bool m_clean;
        mutable Buffer m_buffer;
#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
        mutable bool m_dryrun;
        mutable size_t m_cursor;
#else
        mutable Serializer m_serializer;
        mutable Deserializer m_deserializer;
#endif


#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION
        //! \brief coping with strict aliasing
        //!
        //! \see http://cellperformance.beyond3d.com/articles/2006/06/understanding-strict-aliasing.html
        //! \{
        union float2uint32_t {
            float    f;
            uint32_t u;
            char     b[sizeof(float)];  //!< \brief Formally required
        };
        union double2uint64_t {
            double   d;
            uint64_t u;
            char     b[sizeof(double)];  //!< \brief Formally required
        };
        //! \}
#endif
    };

/*****************************************************************************/

#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION

    inline Serialization &Serialization::operator << (bool value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+1) m_buffer.resize(m_cursor+1);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value? 0xff : 0x00;
        }

        m_cursor+=1;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (int8_t value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+1) m_buffer.resize(m_cursor+1);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value>>0;
        }

        m_cursor+=1;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (uint8_t value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+1) m_buffer.resize(m_cursor+1);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value>>0;
        }

        m_cursor+=1;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (int16_t value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+2) m_buffer.resize(m_cursor+2);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value>>8;
            m_buffer[m_cursor+1]=value>>0;
        }

        m_cursor+=2;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (uint16_t value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+2) m_buffer.resize(m_cursor+2);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value>>8;
            m_buffer[m_cursor+1]=value>>0;
        }

        m_cursor+=2;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (int32_t value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+4) m_buffer.resize(m_cursor+4);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value>>24;
            m_buffer[m_cursor+1]=value>>16;
            m_buffer[m_cursor+2]=value>> 8;
            m_buffer[m_cursor+3]=value>> 0;
        }

        m_cursor+=4;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (uint32_t value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+4) m_buffer.resize(m_cursor+4);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value>>24;
            m_buffer[m_cursor+1]=value>>16;
            m_buffer[m_cursor+2]=value>> 8;
            m_buffer[m_cursor+3]=value>> 0;
        }

        m_cursor+=4;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (int64_t value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+8) m_buffer.resize(m_cursor+8);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value>>56;
            m_buffer[m_cursor+1]=value>>48;
            m_buffer[m_cursor+2]=value>>40;
            m_buffer[m_cursor+3]=value>>32;
            m_buffer[m_cursor+4]=value>>24;
            m_buffer[m_cursor+5]=value>>16;
            m_buffer[m_cursor+6]=value>> 8;
            m_buffer[m_cursor+7]=value>> 0;
        }

        m_cursor+=8;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (uint64_t value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+8) m_buffer.resize(m_cursor+8);

        if(!m_dryrun) {
            m_buffer[m_cursor+0]=value>>56;
            m_buffer[m_cursor+1]=value>>48;
            m_buffer[m_cursor+2]=value>>40;
            m_buffer[m_cursor+3]=value>>32;
            m_buffer[m_cursor+4]=value>>24;
            m_buffer[m_cursor+5]=value>>16;
            m_buffer[m_cursor+6]=value>> 8;
            m_buffer[m_cursor+7]=value>> 0;
        }

        m_cursor+=8;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (float value) IPL_NOEXCEPT {
        IPL_CONST_ASSERT(sizeof(float)==4);

        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+4) m_buffer.resize(m_cursor+4);

        if(!m_dryrun) {
            /* This assumes that the machine uses IEEE format natively */
            union {
                uint32_t u;
                float v;
            } CastUnion;
            CastUnion.v = value;
            //uint32_t &v=*(uint32_t *)(void * /* work around anal gcc warning */)&value;
            uint32_t &v=CastUnion.u;
            m_buffer[m_cursor+0]=v>>24;
            m_buffer[m_cursor+1]=v>>16;
            m_buffer[m_cursor+2]=v>> 8;
            m_buffer[m_cursor+3]=v>> 0;
        }

        m_cursor+=4;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (double value) IPL_NOEXCEPT {
        IPL_CONST_ASSERT(sizeof(double)==8);

        if(!m_write_ok) return *this;
        if(m_buffer.size()<m_cursor+8) m_buffer.resize(m_cursor+8);

        if(!m_dryrun) {
            /* This assumes that the machine uses IEEE format natively */
            union {
                uint64_t u;
                double v;
            } CastUnion;
            CastUnion.v = value;
            //uint64_t &v=*(uint64_t *)(void * /* work around anal gcc warning */)&value;
            uint64_t &v=CastUnion.u;
            m_buffer[m_cursor+0]=v>>56;
            m_buffer[m_cursor+1]=v>>48;
            m_buffer[m_cursor+2]=v>>40;
            m_buffer[m_cursor+3]=v>>32;
            m_buffer[m_cursor+4]=v>>24;
            m_buffer[m_cursor+5]=v>>16;
            m_buffer[m_cursor+6]=v>> 8;
            m_buffer[m_cursor+7]=v>> 0;
        }

        m_cursor+=8;
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (const util::UnicodeString8 &value) IPL_NOEXCEPT {
        if(!m_write_ok) return *this;
        size_t header_size = 1; // encoding byte
        size_t num_chars = value.size();
        if (num_chars > INT16_MAX) {
            header_size += sizeof(uint32_t);   // 32bit string size
        } else {
            header_size += sizeof(uint16_t);   // 16bit string size
        }
        if(m_buffer.size()<m_cursor+header_size+num_chars) m_buffer.resize(m_cursor+header_size+num_chars);
        uint8_t encoding=0;  // STREAM_STRING_ENCODING_UTF8
        const unsigned char *chars=value.retrieveData();
        operator << (encoding);
        if (value.size() > INT16_MAX) {
            // new style: large values stored as negative number in high/low short
            // 1. negate size
            uint32_t length = -value.size();
            // 2. split in high/low short
            uint16_t top = (uint16_t)(length >> 16);
            uint16_t bot = (uint16_t)(length & 0xffff);
            // 3. first put high then low short
            // Note: put both as signed to keep all 16 bits of short
            operator << (top);
            operator << (bot);
        } else {
            uint16_t len=(uint16_t)num_chars;
            operator << (len);
        }
        if(!m_dryrun) {
            for(size_t i=0; i<num_chars; i++)
                m_buffer[m_cursor+i]=chars[i];
        }

        m_cursor+=num_chars;
        return *this;
    }

    inline Serialization &Serialization::operator << (const util::UnicodeString16 &value) IPL_NOEXCEPT {
        util::UnicodeString8 s(value);
        return operator << (s);
    }

#else

    inline Serialization &Serialization::operator << (bool value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (int8_t value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (uint8_t value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (int16_t value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (uint16_t value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (int32_t value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (uint32_t value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (int64_t value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (uint64_t value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (float value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (double value) IPL_NOEXCEPT {
        m_serializer << value;
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (const util::UnicodeString8 &value) IPL_NOEXCEPT {
        serialize(m_serializer, util::UnicodeString(value));
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

    inline Serialization &Serialization::operator << (const util::UnicodeString16 &value) IPL_NOEXCEPT {
        serialize(m_serializer, util::UnicodeString(value));
        if(m_serializer.hasError()) {
            ipl_error.ack();
            m_write_ok=false;
        }
        m_clean=false;
        return *this;
    }

#endif

/*****************************************************************************/

#ifdef PERSISTENCE_USE_INTERNAL_SERIALIZATION

    inline Serialization &Serialization::operator >> (bool &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+1) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 1);
            m_read_ok=false;
            return *this;
        }

        value=m_buffer.getReadable()[m_cursor+0];

        m_cursor+=1;
        return *this;
    }

    inline Serialization &Serialization::operator >> (int8_t &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+1) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 1);
            m_read_ok=false;
            return *this;
        }

        value=m_buffer.getReadable()[m_cursor+0];

        m_cursor+=1;
        return *this;
    }

    inline Serialization &Serialization::operator >> (uint8_t &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+1) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 1);
            m_read_ok=false;
            return *this;
        }

        value=m_buffer.getReadable()[m_cursor+0];

        m_cursor+=1;
        return *this;
    }

    inline Serialization &Serialization::operator >> (int16_t &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+2) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 2);
            m_read_ok=false;
            return *this;
        }

        value =m_buffer.getReadable()[m_cursor+0];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+1];

        m_cursor+=2;
        return *this;
    }

    inline Serialization &Serialization::operator >> (uint16_t &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+2) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 2);
            m_read_ok=false;
            return *this;
        }

        value =m_buffer.getReadable()[m_cursor+0];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+1];

        m_cursor+=2;
        return *this;
    }

    inline Serialization &Serialization::operator >> (int32_t &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+4) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 4);
            m_read_ok=false;
            return *this;
        }

        value =m_buffer.getReadable()[m_cursor+0];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+1];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+2];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+3];

        m_cursor+=4;
        return *this;
    }

    inline Serialization &Serialization::operator >> (uint32_t &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+4) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 4);
            m_read_ok=false;
            return *this;
        }

        value =m_buffer.getReadable()[m_cursor+0];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+1];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+2];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+3];

        m_cursor+=4;
        return *this;
    }

    inline Serialization &Serialization::operator >> (int64_t &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+8) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 8);
            m_read_ok=false;
            return *this;
        }

        value =m_buffer.getReadable()[m_cursor+0];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+1];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+2];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+3];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+4];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+5];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+6];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+7];

        m_cursor+=8;
        return *this;
    }

    inline Serialization &Serialization::operator >> (uint64_t &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+8) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 8);
            m_read_ok=false;
            return *this;
        }

        value =m_buffer.getReadable()[m_cursor+0];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+1];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+2];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+3];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+4];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+5];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+6];
        value<<=8;
        value|=m_buffer.getReadable()[m_cursor+7];

        m_cursor+=8;
        return *this;
    }

    inline Serialization &Serialization::operator >> (float &value) IPL_NOEXCEPT {
        IPL_CONST_ASSERT(sizeof(float)==4);

        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+4) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 4);
            m_read_ok=false;
            return *this;
        }

        float2uint32_t v;
        v.u =m_buffer.getReadable()[m_cursor+0];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+1];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+2];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+3];
        value=v.f;

        m_cursor+=4;
        return *this;
    }

    inline Serialization &Serialization::operator >> (double &value) IPL_NOEXCEPT {
        IPL_CONST_ASSERT(sizeof(double)==8);

        ensure_clean();
        if(!m_read_ok) return *this;
        if(m_buffer.getReadable().size()<m_cursor+8) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, 8);
            m_read_ok=false;
            return *this;
        }

        double2uint64_t v;
        v.u =m_buffer.getReadable()[m_cursor+0];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+1];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+2];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+3];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+4];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+5];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+6];
        v.u<<=8;
        v.u|=m_buffer.getReadable()[m_cursor+7];
        value=v.d;

        m_cursor+=8;
        return *this;
    }

    inline Serialization &Serialization::operator >> (util::UnicodeString8 &value) IPL_NOEXCEPT {
        ensure_clean();
        if(!m_read_ok) return *this;
        size_t header_size = 3; // encoding byte + minimum (=16bit) string size
        if(m_buffer.getReadable().size()<m_cursor+header_size) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, header_size);
            m_read_ok=false;
            return *this;
        }

        uint8_t encoding = 0;
        operator >> (encoding);
        if(encoding!=0 /* STREAM_STRING_ENCODING_UTF8 */) {
            ipl_raise(comm::Error, comm::error::UNSUPPORTED_UNICODE_FORMAT);
            m_read_ok=false;
            return *this;
        }

        uint32_t string_length = 0;
        int16_t len = 0;
        operator >> (len);
        if (len < 0) {
            // negative values a the marker for 32bit string size,
            // the value is the high part of the size

            // we expect another 16 bit value
            // check if we have enough data for 2 more bytes
            if(m_buffer.getReadable().size()<m_cursor + 2) {
                ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                          m_buffer.getReadable().size()-m_cursor, 2);
                m_read_ok=false;
                return *this;
            }
            string_length = len;
            // Note: second one needs to be read as _unsigned_ to get all bits but no sign bit!! (avoid sign extension)
            // now read low short
            uint16_t lo = 0;
            operator >> (lo);
            // rebuild negative size from hi and low short
            string_length = (string_length << 16) | lo;
            // negate size
            string_length = -string_length;
        } else {
            // we have an 16bit sized string
            string_length = len;
        }
        if(m_buffer.getReadable().size()<m_cursor+string_length) {
            ipl_raise(util::serializer::Error, util::serializer::READABLE_UNDERFLOW,
                      m_buffer.getReadable().size()-m_cursor, string_length);
            m_read_ok=false;
            return *this;
        }
        if(string_length)
            value.setString((const char *)m_buffer.getReadable().data()+m_cursor,
                            util::UnicodeString::UTF8, string_length);
        else  // UnicodeString8::setString is Broken As Designed for len=0
            value.clear();

        m_cursor+=string_length;
        return *this;
    }

    inline Serialization &Serialization::operator >> (util::UnicodeString16 &value) IPL_NOEXCEPT {
        util::UnicodeString8 s;
        operator >> (s);
        value=s;
        return *this;
    }

#else

    inline Serialization &Serialization::operator >> (int8_t &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (bool &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (uint8_t &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (int16_t &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (uint16_t &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (int32_t &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (uint32_t &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (int64_t &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (uint64_t &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (float &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (double &value) IPL_NOEXCEPT {
        ensure_clean();
        m_deserializer >> value;
        if(m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        return *this;
    }

    inline Serialization &Serialization::operator >> (util::UnicodeString8 &value) IPL_NOEXCEPT {
        util::UnicodeString s;
        ensure_clean();
        if(deserialize(m_deserializer, s) || m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        value=s;
        return *this;
    }

    inline Serialization &Serialization::operator >> (util::UnicodeString16 &value) IPL_NOEXCEPT {
        util::UnicodeString s;
        ensure_clean();
        if(deserialize(m_deserializer, s) || m_deserializer.hasError()) {
            ipl_error.ack();
            m_read_ok=false;
        }
        value=s;
        return *this;
    }

#endif

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
