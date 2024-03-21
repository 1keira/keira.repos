/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_SERIALIZER_HXX
#define UTIL_SERIALIZER_SERIALIZER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <common/types/utility.hxx>
#include <common/Macros.hxx>
#include <common/stdint.h>
#include <common/UUID.hxx>

#include <stdlib.h> // for size_t

#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
namespace serializer
{

//! shared ID for DefaultSerializerLE and DefaultDeserializerLE
static const uint8_t LE_SERIALIZER_ID = 0;
//! shared ID for DefaultSerializerBE and DefaultDeserializerBE
static const uint8_t BE_SERIALIZER_ID = 1;

/**
 * \brief
 *     Wrapper for an ipl::pair to represent primitive arrays

 *     Wraps an ipl::pair consisting of an array pointer of a certain
 *     type and a size specification. The size gives the number of
 *     valid elements in the array.
 **/
template <typename T>
class Array :
    public ipl::pair< size_t, T* >
{
public:

    // container compatibility
    using value_type             = T;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using const_iterator         = const value_type* ;
    using iterator               = value_type*;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;


    //! Default constructor constructs zero size array at NULL
    Array() IPL_NOEXCEPT :
        ipl::pair< size_t, T*>( 0, NULL )
    { }

    //! Construct array from size specification and primitive array ptr.
    Array(const size_t size, T* ptr) IPL_NOEXCEPT :
        ipl::pair< size_t, T*>( size, ptr )
    { }

    //! set a new pair of array size and array ptr
    void set(const size_t size, T* ptr) IPL_NOEXCEPT
    {
        this->first = size;
        this->second = ptr;
    }

    //! return the size of the array
    size_type size() const IPL_NOEXCEPT { return this->first; }
    //! return a const pointer to the first element of the array
    const T* data() const IPL_NOEXCEPT { return this->second; }
    //! return a non-const pointer to the first element of the array
    T* data() IPL_NOEXCEPT { return this->second; }

    //  iterator support
    constexpr iterator begin() const noexcept {return iterator(data());};
    constexpr iterator end() const noexcept {return iterator(data() + size());}
    constexpr const_iterator cbegin() const noexcept {return data();};
    constexpr const_iterator cend() const noexcept {return data() + size();}

    constexpr reverse_iterator rbegin() const noexcept {
        return reverse_iterator(data() + size());
    };
    constexpr reverse_iterator rend() const noexcept {
        return reverse_iterator(data());
    }
    constexpr const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(data() + size());
    }
    constexpr const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(data());
    }

    //! Return a non-const reference to the given element in the array
    T& operator[](const size_t which) IPL_NOEXCEPT
    { return this->second[which]; }

    //! Return a const reference to the given element in the array
    const T& operator[](const size_t which) const IPL_NOEXCEPT
    { return this->second[which]; }

    //! \brief
    //!    comparison of array content. equality is given if size
    //!    of arrays and content of arrays is equal
    bool operator==(const Array &other) const IPL_NOEXCEPT
    {
        if( this->size() != other.size() )
            return false;

        for( size_t elem = 0; elem < this->size(); elem++ )
        {
            if( (*this)[elem] != other[elem] )
                return false;
        }

        return true;
    }

    bool operator!=(const Array &other) const IPL_NOEXCEPT
    { return ! operator==(other); }
};

/**
 * \brief
 *     Represents bit-flags

 *     Consists of an integer value and a bit amount. The bit amount
 *     states a number of bits that is used for keeping flag
 *     information in the integer value.
 *
 *     This flag information can be efficiently processed by
 *     serializers.
 **/
class Flags
{
public:
    /**
     * \brief
     *     Create a new flag representation with the given bit
     *     amount and initial value
     * \param[in] bit_amount
     *     Number of bits to use for flags representation in value. Valid ranges from
     *     [0, 32].
     * \param[in] value
     *     The initial value to apply for any flags.
     **/
    Flags(size_t bit_amount = 0, uint32_t value = 0) IPL_NOEXCEPT
    { setBitAmount(bit_amount); setValue(value); }

    //! \brief
    //! Returns the currently set amount of bits to use for flags
    //! representation
    size_t getBitAmount() const IPL_NOEXCEPT
    { return m_bits; }

    /**
     * \brief
     *     Set a new number of bits to use for flag representation

     *     If any bits at higher positions then the given amount
     *     are set in the flags value then they will be ignored
     *     during serialization.
     * \param[in] amount
     *     Number of bits to use. Valid range is 0 <= amount <= 32.
     **/
    void setBitAmount(const size_t amount) IPL_NOEXCEPT
    {
        IPL_ASSERT( amount <= 32 );
        m_bits = amount;
    }

    /**
     * \brief
     *     Returns the current flags value

     *     Any bits higher then the currently set bit amount will
     *     be ignored
     **/
    uint32_t getValue() const IPL_NOEXCEPT
    { return m_val; }

    /**
     * \brief
     *     Sets a new flags value

     *     Any bits higher then the currently set bit amount will
     *     be discarded from value.
     **/
    void setValue(uint32_t value) IPL_NOEXCEPT
    {
        const size_t unused_bits = 32 - m_bits;
        value <<= unused_bits;
        value >>= unused_bits;
        m_val = value;
    }

    /**
     * \brief
     *     Get the bit currently set at position pos

     *     Counting of bit positions starts at zero.
     * \param[in] pos
     *     The position of the bit to retrieve. Valid range is 0 <=
     *     pos < getBitAmount().
     **/
    bool getBit(const size_t pos) const IPL_NOEXCEPT
    {
        IPL_ASSERT( pos < m_bits );

        uint32_t tmp = m_val;
        tmp <<= (31 - pos);
        tmp >>= 31;

        return tmp != 0;
    }

    /**
     * \brief
     *     Set the bit of the flags value at position pos

     *     Counting of bit positions starts at zero.
     * \param[in] pos
     *     Bit position to set. Valid range is 0 <= pos <
     *     getBitAmount().
     **/
    void setBit(const size_t pos, const bool val = true) IPL_NOEXCEPT
    {
        IPL_ASSERT( pos < m_bits );

        // get an integer with the pos. bit position set to one
        uint32_t bit = 1;
        bit <<= pos;

        // if we have to enable the bit, simply use bitwise or
        if(val)
        {
            m_val |= bit;
        }
        // for disable we need to 'and' the complement
        else
        {
            // now all bits set expecpt the pos. bit
            bit = ~bit;

            // the pos. bit will now be disabled in m_val, too
            m_val &= bit;
        }
    }

    //! \see setValue()
    Flags& operator=(const uint32_t val) IPL_NOEXCEPT
    { setValue(val); return *this; }

    //! \see getBit()
    bool operator[](const size_t pos) const IPL_NOEXCEPT
    { return getBit(pos); }

    bool operator==(const Flags &other) const IPL_NOEXCEPT
    { return m_bits == other.m_bits && m_val == other.m_val;}

    bool operator!=(const Flags &other) const IPL_NOEXCEPT
    { return !operator==(other); }
protected:
    //! number of bits valid in m_val (starting from the lowest)
    size_t m_bits;
    uint32_t m_val;
};


/*!
    \brief Callback interface for serializer sanity checks
*/
class UTIL_EXPORT Sanity {

public:
    Sanity(size_t dont_warn_below_bytes) IPL_NOEXCEPT:
        dont_warn_below_bytes(dont_warn_below_bytes) {}
    virtual ~Sanity() IPL_NOEXCEPT;  //!< Just to keep the compiler happy...

    //! \brief Report suspect block size, return whether this is an error
    virtual bool block_size(size_t bytes)=0;

    //! \brief Minimum block size to call block_size() for
    const size_t dont_warn_below_bytes;
};

//! \brief Convenient NOP implementation of sanity checks
class Insanity: public Sanity {

public:
    Insanity() IPL_NOEXCEPT : Sanity((size_t)-1) {}
    virtual bool block_size(size_t bytes) IPL_NOEXCEPT;
};

extern UTIL_EXPORT Insanity insanity;


} // end namespace serializer
} // end namespace util

#endif
