/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_BYTEBUFFER_HXX
#define UTIL_BYTEBUFFER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <cstring>
#include <common/inttypes.h>
#include <common/buffers.hxx>
#include <util/transport/IMsgWriter.hxx>

#include <vector>

namespace util {

/*!  \brief a data sink that buffers all data in memory
 *
 *   \details The in-memory buffer is a vector of fix-sized chunks.
 *   The last chunk may be half-filled.
 */
class UTIL_EXPORT ByteBufferWriter : public util::transport::IMsgWriter {
    public:

        class Cursor {
        public:
            Cursor() : m_chunk_index{0}, m_write_pos_in_current_chunk{0} {};
        private:
            friend class ByteBufferWriter;
            size_t     m_chunk_index;
            size_t     m_write_pos_in_current_chunk;
        };

        static const size_t DEFAULT_INITIAL_CHUNK_SIZE = 1024;

        ByteBufferWriter(size_t chunk_size=DEFAULT_INITIAL_CHUNK_SIZE) IPL_NOEXCEPT;

        virtual ~ByteBufferWriter() IPL_NOEXCEPT;

        ByteBufferWriter(const ByteBufferWriter &)=delete;
        ByteBufferWriter &operator = (const ByteBufferWriter &)=delete;

        size_t size() const IPL_NOEXCEPT;

        /*! get the beginning of the buffer
         * \return
         *  pointer to the first chunk
         */
        uint8_t*  data() const IPL_NOEXCEPT;

        /*! retrieve the full content as a copy
         * \return
         *  number of retrieved bytes
        */
        size_t retrieve(uint8_t* destination, size_t max) const IPL_NOEXCEPT;

        bool put(uint8_t data) IPL_NOEXCEPT;
        bool put(const uint8_t* data, size_t num) IPL_NOEXCEPT;

        Cursor getCurrentCursor() const IPL_NOEXCEPT;
        bool setCursor(const Cursor& cursor) IPL_NOEXCEPT;

        void reset() IPL_NOEXCEPT;

        /*! \brief implement IMsgWriter interface
         */
        bool write(const util::transport::Writeable &w) override;

        /*! \brief writes itself into an ipl::buf
         */
        bool write(ipl::Buf& to) IPL_NOEXCEPT;

        static ByteBufferWriter* getLocalByteBuffer();

    private:

        size_t      m_chunk_size;
        uint8_t*    m_current_ptr;
        Cursor      m_cursor;

        std::vector<uint8_t*>   m_chunks;
};

class UTIL_EXPORT ByteBufferReader {
    public:

        ByteBufferReader(const uint8_t* data, size_t num, bool copyData=false) IPL_NOEXCEPT;

        ByteBufferReader(const ByteBufferWriter&)  IPL_NOEXCEPT;

        ~ByteBufferReader() IPL_NOEXCEPT;

        ByteBufferReader(const ByteBufferReader &)=delete;
        ByteBufferReader &operator = (const ByteBufferReader &)=delete;

        size_t size() const IPL_NOEXCEPT { return m_size; };

        size_t bytesLeft() const IPL_NOEXCEPT;

        const uint8_t* current() const IPL_NOEXCEPT { return m_data_ptr; }

        bool setCursor(const uint8_t* to) IPL_NOEXCEPT;

        uint8_t look() const IPL_NOEXCEPT { return *m_data_ptr; }

        bool skip(size_t num) IPL_NOEXCEPT;

        bool get(uint8_t& data) IPL_NOEXCEPT;
        bool get(uint8_t* data, size_t num) IPL_NOEXCEPT;

    private:

        size_t            m_read_pos;
        size_t            m_size;
        uint8_t*          m_data;
        const uint8_t*    m_data_ptr;

        bool        m_copy_data;

};

}    /* namespace */

#endif /* UTIL_BYTEBUFFER_HXX */

