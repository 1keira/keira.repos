/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <string.h>    // for memcpy

#include <common/ByteOrder.hxx>
#include <common/streams/iostream.hxx>
#include <common/streams/iomanip.hxx>
#include <common/error/ErrorHelper.hxx>
#include <common/Macros.hxx>

namespace util {

    template <typename HEADER_T>
    uint8_t BinaryMessage<HEADER_T>::operator[](const uint16_t p_index) const IPL_NOEXCEPT {
        IPL_ASSERT(p_index < m_data_length);

        const uint16_t real_pos = p_index + HEADER_SIZE;

        return m_data[real_pos/m_data_block_size][real_pos%m_data_block_size];
    }

    template <typename HEADER_T>
    uint16_t BinaryMessage<HEADER_T>::getDataLength() const IPL_NOEXCEPT
    {
        return m_data_length;
    }

    template <typename HEADER_T>
    BinaryMessage<HEADER_T>& BinaryMessage<HEADER_T>::operator=(const BinaryMessage& p_other) IPL_NOEXCEPT
    {
        if(!m_data.empty() && freeData() )
            return *this;

        m_network_byte_order = p_other.m_network_byte_order;
        m_data_block_size = p_other.m_data_block_size;

        if(initData())
            return *this;

        m_data_length = p_other.m_data_length;

        // now we have to copy over the header & custom data from p_other
        uint16_t block_count = p_other.m_data.size();
        for(uint16_t block_pos = 0; block_pos < block_count; block_pos++) {
            if(block_pos)
            {
                // for every block (except the first one) we have to allocate the memory
                m_data.push_back( new (ipl::nothrow) uint8_t[m_data_block_size] );
            }
            uint16_t amount = 0;
            // if this is the last block we copy over only a part of the block data
            if(block_pos == block_count-1)
                amount = (m_data_length + HEADER_SIZE) % m_data_block_size;
            if(!amount)
                amount = m_data_block_size;

            memcpy( m_data[block_pos], p_other.m_data[block_pos], amount );
        }
        return *this;
    }

    template <typename HEADER_T>
    uint16_t BinaryMessage<HEADER_T>::getUint16(uint16_t p_start_byte) const IPL_NOEXCEPT
    {
        IPL_ASSERT(p_start_byte+1 < m_data_length);

        const uint16_t real_pos = p_start_byte + HEADER_SIZE;
        // the block in which to search the word
        const uint16_t block_nr = real_pos / m_data_block_size;
        // the byte in the block in which to search the word
        const uint16_t byte_nr = real_pos % m_data_block_size;
        uint16_t ret;
        // first byte for the higher order bits
        ret = static_cast<uint16_t>( m_data[block_nr][byte_nr] ) << 8;
        // the second byte might be in the next data block - we have to cover that case
        if(byte_nr == m_data_block_size-1)
            ret |= static_cast<uint16_t>( m_data[block_nr+1][0] );
        else
            ret |= static_cast<uint16_t>( m_data[block_nr][byte_nr+1] );
        if( isNetworkByteOrder() )
            ret = IPL_NTOH_UINT16( ret );
        return ret;
    }

    template <typename HEADER_T>
    uint32_t BinaryMessage<HEADER_T>::getUint32(uint16_t p_start_byte) const IPL_NOEXCEPT
    {
        IPL_ASSERT(p_start_byte+3 < m_data_length);

        uint32_t ret = 0;
        const uint16_t real_pos = p_start_byte + HEADER_SIZE;
        // the block in which to search the word
        uint16_t block_nr = real_pos / m_data_block_size;
        // the byte in the block in which to search the word
        uint16_t byte_nr = real_pos % m_data_block_size;
        for( uint8_t shift_amount = 24; shift_amount <= 24; shift_amount -= 8 ) {
            ret |= static_cast<uint32_t>(m_data[block_nr][byte_nr]) << shift_amount;
            byte_nr++;
            if(byte_nr == m_data_block_size)
            {
                block_nr++;
                byte_nr = 0;
            }
        }
        if( isNetworkByteOrder() )
            ret = IPL_NTOH_UINT32( ret );
        return ret;
    }

    template <typename HEADER_T>
    void BinaryMessage<HEADER_T>::setParsePosition(const uint16_t p_pos) const IPL_NOEXCEPT
    {
        IPL_ASSERT(p_pos <= m_data_length);
        m_parse_position = p_pos;
    }

    template <typename HEADER_T>
    inline uint16_t BinaryMessage<HEADER_T>::getParsePosition() const IPL_NOEXCEPT
    {
        return m_parse_position;
    }

    template <typename HEADER_T>
    inline bool BinaryMessage<HEADER_T>::parsingCompleted() const IPL_NOEXCEPT
    {
        return m_parse_position == m_data_length;
    }

    template <typename HEADER_T>
    inline uint16_t BinaryMessage<HEADER_T>::bytesLeft() const IPL_NOEXCEPT
    {
        return m_data_length - m_parse_position;
    }

    template <typename HEADER_T>
    bool BinaryMessage<HEADER_T>::operator==(const BinaryMessage& p_other) const IPL_NOEXCEPT
    {
        if(this == &p_other) return true;
        if(m_data_length != p_other.m_data_length) return false;
        // check the header data byte for byte for equality
        for(uint8_t header_pos = 0; header_pos < sizeof(HEADER_T); header_pos++) {
            if(reinterpret_cast<const uint8_t* const>(m_header)[header_pos] !=
               reinterpret_cast<const uint8_t* const>(p_other.m_header)[header_pos])
                return false;
        }
        for(uint16_t data_pos = 0; data_pos < m_data_length; data_pos++)
            if((*this)[data_pos] != p_other[data_pos])
                return false;

        return true;
    }

    template <typename HEADER_T>
    inline bool BinaryMessage<HEADER_T>::operator!=(const BinaryMessage& p_other) const IPL_NOEXCEPT
    {
        return ! operator==(p_other);
    }

} // end namespace

// global operators follow

template <typename HT>
ipl::ostream& operator << (ipl::ostream& p_out,
                           const util::BinaryMessage<HT>& p_msg) IPL_NOEXCEPT
{
    p_out << *(p_msg.m_header);

    ipl::ios::fmtflags old_flags = p_out.flags();
    p_out.setf ( ipl::ios::hex, ipl::ios::basefield ); // set hex as the basefield
    p_out.fill('0');

    p_out << ipl::setw(4) << p_msg.getDataLength();
    if(p_msg.getDataLength())
        p_out << ": ";

    for(uint16_t bytenum = 0; bytenum < p_msg.getDataLength(); bytenum++) {
        if(bytenum%4 == 0)
            p_out << "   ";
        else
            p_out << " ";
        p_out << ipl::setw(2) << static_cast<uint32_t>(p_msg[bytenum]);
    }
    
    p_out << ipl::flush;
    p_out.flags ( old_flags );
    return p_out;
}

template <typename HT>
const util::BinaryMessage<HT>& operator >> (const util::BinaryMessage<HT> &p_message,
                                            uint8_t* p_out_byte) IPL_NOEXCEPT
{
    IPL_ASSERT(!p_message.parsingCompleted());

    *p_out_byte = p_message[p_message.m_parse_position];
    p_message.m_parse_position++;
    return p_message;
}

template <typename HT>
inline const util::BinaryMessage<HT>& operator >> (const util::BinaryMessage<HT> &p_message,
                                                   int8_t* p_out_byte) IPL_NOEXCEPT
{
    return p_message >> reinterpret_cast<uint8_t*>(p_out_byte);
}

template <typename HT>
const util::BinaryMessage<HT>& operator >> (const util::BinaryMessage<HT> &p_message,
                                            uint16_t* p_out_word) IPL_NOEXCEPT
{
    IPL_ASSERT(p_message.m_parse_position + 2 <= p_message.m_data_length);

    *p_out_word = p_message.getUint16(p_message.m_parse_position);
    p_message.m_parse_position += 2;
    return p_message;
}

template <typename HT>
inline const util::BinaryMessage<HT>& operator >> (const util::BinaryMessage<HT> &p_message,
                                                   int16_t* p_out_word) IPL_NOEXCEPT
{
    return p_message >> reinterpret_cast<uint16_t*>(p_out_word);
}

template <typename HT>
const util::BinaryMessage<HT>& operator >> (const util::BinaryMessage<HT> &p_message,
                                            uint32_t* p_out_long) IPL_NOEXCEPT
{
    IPL_ASSERT(p_message.m_parse_position + 4 <= p_message.m_data_length);

    *p_out_long = p_message.getUint32(p_message.m_parse_position);
    p_message.m_parse_position += 4;
    return p_message;
}

template <typename HT>
inline const util::BinaryMessage<HT>& operator >> (const util::BinaryMessage<HT> &p_message,
                                                   int32_t* p_out_long) IPL_NOEXCEPT
{
    return p_message >> reinterpret_cast<uint32_t*>(p_out_long);
}

template <typename HT>
util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                      const uint8_t* const p_byte) IPL_NOEXCEPT
{
    p_message.addData(p_byte, 1);
    return p_message;
}

template <typename HT>
inline util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                             const int8_t* const p_byte) IPL_NOEXCEPT
{
    return p_message << reinterpret_cast<const uint8_t* const>(p_byte);
}

template <typename HT>
util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                      const uint16_t* const p_word) IPL_NOEXCEPT
{
    if( p_message.isNetworkByteOrder() ) {
        uint16_t network_word = IPL_HTON_UINT16( *p_word );

        uint8_t half_word = static_cast<uint8_t>(network_word >> 8);
        p_message.addData(&half_word, 1);
        p_message.addData(&(half_word = static_cast<uint8_t>(network_word)), 1);
    } else {
        uint8_t half_word = static_cast<uint8_t>(*p_word >> 8);
        p_message.addData(&half_word, 1);
        p_message.addData(&(half_word = static_cast<uint8_t>(*p_word)), 1);
    }
    return p_message;
}

template <typename HT>
inline util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                             const int16_t* const p_word) IPL_NOEXCEPT
{
    return p_message << reinterpret_cast<const uint16_t* const>(p_word);
}

template <typename HT>
util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                      const uint32_t* const p_long) IPL_NOEXCEPT
{
    if( p_message.isNetworkByteOrder() ) {
        uint32_t network_long = IPL_HTON_UINT32( *p_long );
        uint8_t quarter_long = static_cast<uint8_t>(network_long >> 24);
        p_message.addData(&quarter_long, 1);
        p_message.addData(&(quarter_long = static_cast<uint8_t>(network_long>>16)), 1);
        p_message.addData(&(quarter_long = static_cast<uint8_t>(network_long>>8)), 1);
        p_message.addData(&(quarter_long = static_cast<uint8_t>(network_long)), 1);
    } else {
        uint8_t quarter_long = static_cast<uint8_t>(*p_long >> 24);
        p_message.addData(&quarter_long, 1);
        p_message.addData(&(quarter_long = static_cast<uint8_t>(*p_long>>16)), 1);
        p_message.addData(&(quarter_long = static_cast<uint8_t>(*p_long>>8)), 1);
        p_message.addData(&(quarter_long = static_cast<uint8_t>(*p_long)), 1);
    }
    return p_message;
}

template <typename HT>
inline util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                             const int32_t* const p_long) IPL_NOEXCEPT
{
    return p_message << reinterpret_cast<const uint32_t* const>(p_long);
}

template <typename HT>
inline util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                             const uint32_t p_long) IPL_NOEXCEPT
{
    return (p_message << &p_long);
}

template <typename HT>
inline util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                             const uint16_t p_word) IPL_NOEXCEPT
{
    p_message << &p_word;
    return p_message;
}

template <typename HT>
inline util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                             const uint8_t p_byte) IPL_NOEXCEPT
{
    return (p_message << &p_byte);
}

template <typename HT>
util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_message,
                                      const util::MessageOperations p_operation) IPL_NOEXCEPT
{
    if(p_operation == util::CLEAR) {
        
        if( p_message.freeData(true) ) {
            IPL_WARN("error freeing data");
            return p_message;
        }
        p_message.setParsePosition(0);
        
    } else if(p_operation == util::CHOP) {
        
        // simply reduce the data_length by one byte
        IPL_ASSERT(p_message.m_data_length);
        p_message.m_data_length--;
        // in case we freed a whole message block we have to remove it
        if( ((p_message.m_data_length+util::BinaryMessage<HT>::HEADER_SIZE) % p_message.m_data_block_size) == 0 )
        {
            delete[] p_message.m_data.back();
            p_message.m_data.pop_back();
        }
        
    } else {
        IPL_ASSERT(false);
    }

    return p_message;
}

template <typename HT>
util::BinaryMessage<HT>& operator << (util::BinaryMessage<HT> &p_target_message,
                                      const util::BinaryMessage<HT>& p_append_message) IPL_NOEXCEPT
{
    uint32_t append_size = p_append_message.getDataLength();

    // if there is no custom data than ignore that ...
    if(append_size) {
        uint32_t tmp;
        // retrieve a pointer to the message data _plus_ header
        const uint8_t* const temp_buffer = p_append_message.retrieveMessagePtr(tmp, false);
        p_target_message.addData(temp_buffer, append_size);
        // data length is already increased in addData !
        p_append_message.returnMessagePtr(temp_buffer);
    }
    return p_target_message;
}

// now starts the actual class implementation, thus we can use an encapsulating namespace
namespace util {

    template <typename HEADER_T>
    inline BinaryMessage<HEADER_T>::BinaryMessage(const blocksize p_block_size,
                                                  const bool p_network_byte_order) IPL_NOEXCEPT :
        m_network_byte_order(p_network_byte_order)
    {
        m_header = NULL;
        m_data_length = 0;
        m_data_block_size = p_block_size.m_blocksize;
        m_parse_position = 0;
        normalizeBlocksize();
        
        bool err = initData();
        (void)err;
    }

    template <typename HEADER_T>
    inline BinaryMessage<HEADER_T>::BinaryMessage(const BinaryMessage& p_src_obj) IPL_NOEXCEPT
    {
        m_header = NULL;
        m_data_length = 0;
        m_parse_position = 0;

        operator=(p_src_obj);
        return;
    }

    template <typename HEADER_T>
    inline BinaryMessage<HEADER_T>::~BinaryMessage() IPL_NOEXCEPT
    {
        if( freeData() )
            IPL_WARN("error freeing data");
    }

    template <typename HEADER_T>
    void BinaryMessage<HEADER_T>::normalizeBlocksize() IPL_NOEXCEPT
    {
        // if the requested block size is less then the static message header then we have to adjust
        // the block size.
        if(m_data_block_size < HEADER_SIZE)
            m_data_block_size = HEADER_SIZE;

        // set the block size to a sensible value, if needed
        //
        // if not a multiple of 8 then make it one
        if (m_data_block_size % 8) {
            if( UINT16_MAX - m_data_block_size < 8 )
                m_data_block_size = UINT16_MAX;
            else
                m_data_block_size += 8 - (m_data_block_size % 8 );
        }

        IPL_ASSERT( m_data_block_size );
    }

    template <typename HEADER_T>
    bool BinaryMessage<HEADER_T>::initData() IPL_NOEXCEPT
    {
        if( m_header || ! m_data.empty() || m_data_length )
        {
            return true;
        }
        m_data.push_back( new(ipl::raise_error) uint8_t[m_data_block_size] );
        if( ! m_data.back() )
        {
            m_data.clear();
            return true;
        }
        m_header = reinterpret_cast<HEADER_T*>(m_data[0]);
        return false;
    }

    template <typename HEADER_T>
    bool BinaryMessage<HEADER_T>::freeData(const bool p_keep_header_data) IPL_NOEXCEPT
    {
        if(!m_header || m_data.empty())
        {
            ipl_raise( ipl::CommonError, ipl::INVALID_USAGE,
                "no data to free");
            return true;
        }

        if(!p_keep_header_data)
            m_header = NULL;

        // free all message data blocks if we don't have to keep header
        // data
        while( (!p_keep_header_data && !m_data.empty()) )
        {
            uint8_t* to_delete = m_data.back();
            m_data.pop_back();
            delete[] to_delete;
        }

        // in this case free all but the first data block
        while ( (p_keep_header_data && m_data.size() > 1) )
        {
            uint8_t* to_delete = m_data.back();
            m_data.pop_back();
            delete[] to_delete;
        }

        m_data_length = 0;
        m_parse_position = 0;

        return false;
    }

    template <typename HEADER_T>
    bool BinaryMessage<HEADER_T>::freeDataAndChangeBlocksize(
        const uint16_t p_new_blocksize, const bool p_keep_header) IPL_NOEXCEPT
    {
        if( freeData( p_keep_header ) )
            return true;

        // remember the old first block, if needed
        uint8_t* const old_first_block = p_keep_header ? m_data.back() : NULL;
        const HEADER_T* const old_header = p_keep_header ? m_header : NULL;

        if( p_keep_header )
        {
            // remove the first block now, too
            m_data.pop_back();
        }

        IPL_ASSERT( m_data.empty() );

        m_header = NULL;
        m_data_block_size = p_new_blocksize;
        normalizeBlocksize();
        // with the new blocksize set we are able to reinitialize the
        // data of the object according to the new parameters.
        if( initData() )
            return true;

        if( p_keep_header )
        {
            // get our old header data back
            memcpy( m_header, old_header, HEADER_SIZE );
            // finally delete the old first block
            delete[] old_first_block;
        }

        return false;
    }

    template <typename HEADER_T>
    inline const HEADER_T* BinaryMessage<HEADER_T>::getHeaderData() const IPL_NOEXCEPT
    {
        return m_header;
    }


    template <typename HEADER_T>
    inline void BinaryMessage<HEADER_T>::setHeaderData(const HEADER_T* const p_header) IPL_NOEXCEPT
    {
        memcpy( m_header, p_header, sizeof(HEADER_T));
    }

    template <typename HEADER_T>
    bool BinaryMessage<HEADER_T>::setData(uint8_t const * const p_data,
                                          const uint16_t p_data_length) IPL_NOEXCEPT
    {
        if(!p_data && p_data_length)
        {
            ipl_raise( ipl::CommonError, ipl::INVALID_USAGE, "no valid data provided" );
            return true;
        }

        if( freeData(true) )
            return true;
        addData(p_data, p_data_length);
        return false;
    }

    template <typename HEADER_T>
    bool BinaryMessage<HEADER_T>::setData(uint8_t const * const p_data,
                                          const uint16_t p_data_length,
                                          const blocksize p_new_blocksize) IPL_NOEXCEPT
    {
        if(!p_data && p_data_length)
        {
            ipl_raise( ipl::CommonError, ipl::INVALID_USAGE,
                "no valid data provided" );
            return true;
        }
        if( freeDataAndChangeBlocksize(p_new_blocksize.m_blocksize, true) )
            return true;
        return setData(p_data, p_data_length);
    }

    template <typename HEADER_T>
    bool BinaryMessage<HEADER_T>::setRawData(uint8_t const * const p_data,
                                             const uint32_t p_data_length,
                                             const blocksize p_new_blocksize) IPL_NOEXCEPT
    {
        // there MUST be data available and it must be at least enough
        // data to fill the header (this check needs to be done here,
        // too to keep exception safety)
        if(!p_data || (p_data_length < HEADER_SIZE))
        {
            ipl_raise( ipl::CommonError,
                ipl::INVALID_USAGE,
                "no valid data provided" );
            return true;
        }

        if( freeDataAndChangeBlocksize(p_new_blocksize.m_blocksize, false) )
            return true;
        return setRawData(p_data, p_data_length);
    }

    template <typename HEADER_T>
    bool BinaryMessage<HEADER_T>::setRawData(uint8_t const * const p_data,
                                             const uint32_t p_data_length) IPL_NOEXCEPT
    {
        // there MUST be data available and it must be at least enough
        // data to fill the header
        if(!p_data || (p_data_length < HEADER_SIZE))
        {
            ipl_raise( ipl::CommonError,
                ipl::INVALID_USAGE,
                "no valid data provided" );
            return true;
        }

        if( freeData(true) )
            return true;
        memcpy( &m_data[0][0], p_data, HEADER_SIZE );
        addData(p_data+HEADER_SIZE, p_data_length-HEADER_SIZE);

        return false;
    }

    template <typename HEADER_T>
    void BinaryMessage<HEADER_T>::addData(uint8_t const * const p_data,
                                          const uint16_t p_bytes) IPL_NOEXCEPT
    {
        // it is important to add the header size to the data length to
        // obtain the real position in the message block we're starting at
        uint16_t block_pos = (m_data_length + HEADER_SIZE) % m_data_block_size;

        // In the case the current block is already full, we need to add a new one
        if (block_pos == 0) {
            m_data.push_back( new (ipl::nothrow) uint8_t[m_data_block_size] );
        }

        // how many bytes to copy
        uint16_t bytes_left = p_bytes;
        while(bytes_left)
        {
            bool new_block_needed = true;
            // how many bytes will be copied in this turn
            uint16_t free_bytes = m_data_block_size - block_pos; // maximum free space in this data block
            if(free_bytes >= bytes_left) {
                free_bytes = bytes_left;
                new_block_needed = false;
            }
            memcpy( m_data.back() + block_pos,
                    p_data + (p_bytes - bytes_left),
                    free_bytes );
            bytes_left -= free_bytes;
            m_data_length += free_bytes;

            if( new_block_needed ) {
                m_data.push_back( new (ipl::nothrow) uint8_t[m_data_block_size] );
                block_pos = 0;
            } else
                return;
        }
    }

    template <typename HEADER_T>
    int_fast16_t BinaryMessage<HEADER_T>::getData(uint8_t* const p_buffer,
                                                  const uint16_t p_buffer_length) const IPL_NOEXCEPT
    {
        if(!m_data_length) return 0;

        if(!p_buffer || p_buffer_length < m_data_length) {
            ipl_raise( ipl::CommonError,
                ipl::INVALID_USAGE, "no data available" );
            return -1;
        }

        uint16_t bytes_copied = 0;
        const uint32_t end_block = m_data.size() - 1;
        for(uint16_t block_nr = 0; block_nr <= end_block; block_nr++) {
            
            uint16_t start_byte = 0;
            uint16_t num_bytes = m_data_block_size;
            // if this is the first message data block then we have
            // to offset the header data
            if(block_nr == 0) {
                start_byte = HEADER_SIZE;
                num_bytes -= HEADER_SIZE;
            }
            // if this is the last message data block then we have
            // to correct the numbers of bytes to read
            if(block_nr == end_block) {
                bool full_block = (((m_data_length + HEADER_SIZE) % m_data_block_size) == 0);
                if (!full_block)
                    num_bytes -= m_data_block_size -
                                 ((m_data_length + HEADER_SIZE) % m_data_block_size);
            }

            memcpy(p_buffer + bytes_copied, m_data[block_nr] + start_byte, num_bytes);
            bytes_copied += num_bytes;
        }

        if( bytes_copied != m_data_length ) {
            return -1;
        }
        return bytes_copied;
    }

    template <typename HEADER_T>
    const uint8_t* BinaryMessage<HEADER_T>::retrieveMessagePtr(
        uint32_t& ptr_length, const bool with_header) const IPL_NOEXCEPT
    {
        ptr_length = m_data_length + (with_header ? HEADER_SIZE : 0);

        if(m_data.size() == 1)
            return m_data[0] + (with_header ? 0 : HEADER_SIZE);

        uint8_t* data_copy = new(ipl::raise_error)
            uint8_t[m_data_length + (with_header ? HEADER_SIZE : 0)];

        if( ! data_copy )
            return NULL;

        if( with_header )
            memcpy(data_copy, m_data[0], HEADER_SIZE);
        int_fast16_t res = getData(data_copy + (with_header ? HEADER_SIZE : 0),
                                   m_data_length);
        if( res < 0 )
        {
            delete[] data_copy;
            return NULL;
        }
        return data_copy;
    }

    template <typename HEADER_T>
    inline void BinaryMessage<HEADER_T>::returnMessagePtr(const uint8_t* const p_ptr) const IPL_NOEXCEPT
    {
        // we simply check the pointer against our first data block. If they aren't equal than this
        // is a copy of the message and has to be deleted.
        // => this of course means that the user may not retrieve a pointer, then play around with
        // the message object and finally return the pointer. This could cause memory corruption.
        if(p_ptr != m_data[0] && p_ptr != (m_data[0] + HEADER_SIZE))
            delete[] p_ptr;
    }

    template <typename HEADER_T>
    inline bool BinaryMessage<HEADER_T>::isNetworkByteOrder() const IPL_NOEXCEPT
    {
        return m_network_byte_order;
    }

} // end namespace
