/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_BINARYMESSAGE_HXX
#define UTIL_BINARYMESSAGE_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <iplcompiler.h>
#include <common/types/vector.hxx>
#include <ostream>

// forward delcaration of BinaryMessage
namespace util
{
    /**
     * \brief
     *    This enum is used for operator<< to allow the user to do
     *    more complex operations on the BinaryMessage object
     * \note
     *    Unfortunately we cannot keep this inside BinaryMessage
     *    as the global output operators need it and the
     *    friendship delcarations inside BinaryMessage need the
     *    global output operator declarations and so on ...
     **/
    enum MessageOperations
    {
        //! Causes the message data to be set to zero length
        CLEAR,
        //! \brief
        //! Causes the last message byte to be removed from the
        //! message data
        CHOP
    };


    template <typename HEADER_T>
    class BinaryMessage;
}

// global operators for the following class declaration of
// BinaryMessage. These have to be declared here such that BinaryMessage
// can perform friend declarations on them. Be aware that these
// declaration must not be in a namespace as these are global operators.
// The reader may skip on to the class declaration of BinaryMessage and
// return later. Thank you.

// these global output operators have to be global such that classes
// that derive from BinaryMessage overload these operators still can
// access the base classes operators easily. This can only be assured by
// making the affected operators global.

/**
 * \brief
 *    global output operator for the BinaryMessage class

 *    a global output operator that allows to easily print
 *    BinaryMessage content for testing / tracing / logging purposes.
 *    The custom message content will be printed byte-wise as
 *    hexadecimal numbers. The header will be printed using its own
 *    output operator - i.e. you have to define an output operator the
 *    header.
 * \param
 *    p_out Output stream that is printed to
 * \param
 *    p_msg The BinaryMessage to be printed
 * \return
 *    The output stream is returned such that it can be used in
 *    operator chains
 **/
template <typename HT>
inline ipl::ostream& operator<<(
    ipl::ostream& p_out, const util::BinaryMessage<HT>& p_msg) IPL_NOEXCEPT;

/*
 * \brief
 *    read one byte from the current parsing position of the message
 * \warning
 *    this operator still modifies the parsing position regardless of the
 *    const modifier
 * \return
 *    A reference to the own object
 * */
template <typename HT>
inline const util::BinaryMessage<HT>& operator>>(
    const util::BinaryMessage<HT> &p_message, uint8_t* p_out_byte) IPL_NOEXCEPT;

template <typename HT>
inline const util::BinaryMessage<HT>& operator>>(
    const util::BinaryMessage<HT> &p_message, int8_t* p_out_byte) IPL_NOEXCEPT;

/*
 * \brief
 *     read one word from the current parsing position of the message
 * \note
 *     The value will be retrieved in host byte order!
 * \warning
 *     this operator still modifies the parsing position regardless of
 *     the const modifier
 * \return
 *     A reference to the own object
 * */
template <typename HT>
inline const util::BinaryMessage<HT>& operator>>(
    const util::BinaryMessage<HT> &p_message, uint16_t* p_out_word) IPL_NOEXCEPT;

template <typename HT>
inline const util::BinaryMessage<HT>& operator>>(
    const util::BinaryMessage<HT> &p_message, int16_t* p_out_word) IPL_NOEXCEPT;

/*
 * \brief
 *     read one long from the current parsing position of the message
 * \note
 *     The value will be retrieved in host byte order!
 * \warning
 *     this operator still modifies the parsing position regardless of
 *     the const modifier
 * \return
 *     A reference to the own object
 **/
template <typename HT>
inline const util::BinaryMessage<HT>& operator>>(
    const util::BinaryMessage<HT> &p_message, uint32_t* p_out_long) IPL_NOEXCEPT;

template <typename HT>
inline const util::BinaryMessage<HT>& operator>>(
    const util::BinaryMessage<HT> &p_message, int32_t* p_out_long) IPL_NOEXCEPT;

/**
 * \brief
 *     This operator allows to add a byte value of data to the custom
 *     message data
 * \param
 *     p_byte A pointer to the byte that should be added to the
 *     BinaryMessage data
 * \note
 *     The pointer versions of this operator are used because
 *     non-pointer versions of uint8_t, uint16_t and uint32_t would be
 *     ambigous to the compiler
 * \return
 *     A reference to the own object
 **/
template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message, const uint8_t* const p_byte) IPL_NOEXCEPT;

template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message, const int8_t* const p_byte) IPL_NOEXCEPT;

/**
 * \brief
 *     This operator allows to add a word value of data to the custom
 *     message data
 * \param
 *     p_word A pointer to the word that should be added to the
 *     BinaryMessage<HT> data
 * \note
 *     The value will be added to the message in network byte order!
 * \return
 *     A reference to the own object
 **/
template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message,
    const uint16_t* const p_word) IPL_NOEXCEPT;

template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message,
    const int16_t* const p_word) IPL_NOEXCEPT;

/**
 * \brief
 *     This operator allows to add a long value of data to the custom
 *     message data
 * \param
 *     p_long A pointer to the long value that should be added to the
 *     util::BinaryMessage<HT>
 * \note
 *     The value will be added to the message in network byte order!
 * \return
 *     A reference to the own object
 **/
template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message,
    const uint32_t* const p_long) IPL_NOEXCEPT;

template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message,
    const int32_t* const p_long) IPL_NOEXCEPT;


/**
 * \brief
 *     Operators as above, just taking not pointers but stack copies of
 *     the values
 **/
template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message, const uint8_t p_byte) IPL_NOEXCEPT;

template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message, const uint16_t p_word) IPL_NOEXCEPT;

template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message, const uint32_t p_long) IPL_NOEXCEPT;

/*
 * \brief
 *     This operator adds the content of p_append_message to the
 *     content of the own object.
 * \note
 *     This will only append the custom message part of
 *     p_append_message to this message. The header data will not be
 *     appended.
 * \param
 *     p_append_message The message whose content will be appended.
 * \return
 *     A reference to the own object
 **/
template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT>& p_target_message,
    const util::BinaryMessage<HT>& p_append_message) IPL_NOEXCEPT;

/**
 * \brief
 *     This operator allows to perform special operations on the
 *     util::BinaryMessage
 * \param
 *     p_operation The kind of operation that should be performed on
 *     the util::BinaryMessage
 * \return
 *     A reference to the own object
 **/
template <typename HT>
inline util::BinaryMessage<HT>& operator<<(
    util::BinaryMessage<HT> &p_message,
    const typename util::MessageOperations p_operation) IPL_NOEXCEPT;


/******************************
 * start of class declaration *
 ******************************/

namespace util
{

template <typename HEADER_T>
/**
 * \brief
 *    General binary message for communication on networks or between
 *    processes etc.

 *    This binary message object is intended for comfortable and fast
 *    handling of a custom message object that consists of some
 *    unspecified binary data.
 * \tparam
 *    HEADER_T is a struct type that is used for accessing the
 *    constant header data of the BinaryMessage. The size of this data
 *    type is used for reserving the apropriate space at the beginning
 *    of the first message data block
**/
class BinaryMessage
{
// friendships

    // declare global output operators as friends - this is a
    // one-to-one template friendship declaration.  Well ... there
    // seems to be no simple kind of friendship in life
    friend ipl::ostream& ::operator<< <HEADER_T>(
        ipl::ostream&, const BinaryMessage<HEADER_T>&) IPL_NOEXCEPT;
    friend const BinaryMessage<HEADER_T>&
        ::operator>> <HEADER_T>(const BinaryMessage<HEADER_T>&,
        uint8_t*) IPL_NOEXCEPT;
    friend const BinaryMessage<HEADER_T>&
        ::operator>> <HEADER_T>(const BinaryMessage<HEADER_T>&,
        uint16_t*) IPL_NOEXCEPT;
    friend const BinaryMessage<HEADER_T>&
        ::operator>> <HEADER_T>(const BinaryMessage<HEADER_T>&,
        uint32_t*) IPL_NOEXCEPT;
    friend BinaryMessage<HEADER_T>&
        ::operator<< <HEADER_T>(BinaryMessage<HEADER_T>&,
        const BinaryMessage<HEADER_T>&) IPL_NOEXCEPT;
    friend BinaryMessage<HEADER_T>&
        ::operator<< <HEADER_T>(BinaryMessage<HEADER_T>&,
        const uint8_t* const) IPL_NOEXCEPT;
    friend BinaryMessage<HEADER_T>&
        ::operator<< <HEADER_T>(BinaryMessage<HEADER_T>&,
        const uint16_t* const) IPL_NOEXCEPT;
    friend BinaryMessage<HEADER_T>&
        ::operator<< <HEADER_T>(BinaryMessage<HEADER_T>&,
        const uint32_t* const) IPL_NOEXCEPT;
    friend BinaryMessage<HEADER_T>&
        ::operator<< <HEADER_T>(BinaryMessage<HEADER_T>&,
        const util::MessageOperations) IPL_NOEXCEPT;
    friend BinaryMessage<HEADER_T>&
        ::operator<< <HEADER_T>(BinaryMessage<HEADER_T>&,
        uint8_t) IPL_NOEXCEPT;
    friend BinaryMessage<HEADER_T>&
        ::operator<< <HEADER_T>(BinaryMessage<HEADER_T>&,
        uint16_t) IPL_NOEXCEPT;
    friend BinaryMessage<HEADER_T>&
        ::operator<< <HEADER_T>(BinaryMessage<HEADER_T>&,
        uint32_t) IPL_NOEXCEPT;

public: // types
    /**
     * \brief
     *     This is just a helper construct that avoids ambigous
     *     overloads of the BinaryMessage constructor or unwanted
     *     implicit message construction from numbers.
     **/
    class blocksize
    {
        friend class BinaryMessage;
    public:
        blocksize(const uint16_t p_blocksize) IPL_NOEXCEPT
        {
            m_blocksize = p_blocksize;
        }
    private:
        uint16_t m_blocksize;
    };

public: // non-static functions
    /**
     * \brief
     *    Default constructor for BinaryMessage object, performs
     *    initialization with sane default values
     * \param[in]
     *    p_block_size Determines the size of data blocks that are
     *    allocated as the message size grows.
     * \param[in]
     *    p_network_byte_order Determines wheter the binary data
     *    in the object should be kept in network byte order / is
     *    expected to be in network byte order. If set to true
     *    then all datainsertion and extractions operations
     *    performed at the BinaryMessage interface will do
     *    automatic conversion between network byte order and host
     *    byte order.

     *    At first only one block of p_block_size bytes will be
     *    allocated that contains the header data as well as a
     *    certain amount of custom binary data. This block will
     *    always be present. Once the data amount exceeds the
     *    p_block_size another data block is used for storing it.
     *    If the message to be expected is known in advance then
     *    the block size can be set accordingly. If the expected
     *    data size is unknown than a sane value should be chosen
     *    that allows typical messages to fit in the first block
     *    but doesn't waste too much unused memory.
     *    <br>
     *    If the message data fits in one block then the message
     *    can be sent over COMM interfaces without the need to
     *    copy the message data into another buffer.
     * \note
     *    The p_block_size may not be smaller then the size of the
     *    HEADER_T in bytes.  Also the block size may be increased
     *    in such cases to fit the header data in and to match
     *    alignment boundaries.
    **/
    BinaryMessage(const blocksize p_block_size,
        const bool p_network_byte_order) IPL_NOEXCEPT;

    /**
     * \brief
     *     copy constructor that performs deep copy of binary data
     * \param
     *     p_src_obj The object from with this object should be
     *     constructed.
     **/
    BinaryMessage(const BinaryMessage& p_src_obj) IPL_NOEXCEPT;

    /**
     * \brief
     *     Destructor for BinaryMessage object, performs any
     *     cleanup tasks that might be needed (so far nothing
     *     special)
    **/
    ~BinaryMessage() IPL_NOEXCEPT;

    /**
     * \brief
     *    Set the message data. A data buffer of a at least
     *    p_data_length bytes has to be provided. Data length
     *    cannot be set separately.
     * \note
     *    The data provided in p_data is copied and the p_data
     *    pointer not kept in the object.
     * \param
     *    p_data A pointer to the custom message data to be used
     *    for the BinaryMessage
     * \param
     *    p_data_length The amount of bytes valid in p_data. May
     *    not be bigger than the actual amount of bytes available
     *    in p_data.
     * \note
     *    The header data will not be overwritten by use of this
     *    method.
     * \return
     *     \c true on error, \c false otherwise
     * \errors
     *     ipl::CommonError with OUT_OF_MEMORY
    **/
    bool setData(uint8_t const * const p_data,
        const uint16_t p_data_length) IPL_NOEXCEPT;

    /**
     * \brief
     *    Does the same as setData(uint8_t const* const, const
     *    uint16_t) but also sets a new blocksize that is applied
     *    before copying over the new data.

     *    The new setting of the blocksize is useful when e.g.
     *    varying sizes of data are frequently set via setData. In
     *    this case a constant blocksize would be contra
     *    productive. The blocksize should adapt to the new
     *    message size.
     *
     *    For example if you want to construct a read-only message
     *    object via setData that is not increased in size
     *    afterwards then it is a good idea to set the blocksize
     *    to the data size such that only one block will be
     *    existing without waste of memory.
     *
     *    If your newly set binary message object is going to grow
     *    a little in size afterwards then you should choose a
     *    smaller blocksize, however. This prevents the allocation
     *    of a second big block of memory.
     * \param[in]
     *    p_new_blocksize The new blocksize to be set into effect
     *    before setting the new data. The same restrictions apply
     *    as to the blocksize specified at construction time.
     * \return
     *     \c false on success, \c true on error
     * \errors
     *     ipl::CommonError with OUT_OF_MEMORY or INVALID_USAGE
     **/
    bool setData(uint8_t const * const p_data,
        const uint16_t p_data_length,
        const blocksize p_new_blocksize) IPL_NOEXCEPT;

    /**
     * \brief
     *    Set the complete message data (i.e. even the header
     *    data) by providing a pointer to binary data.
     * \note
     *    The data provided in p_data is copied and the p_data
     *    pointer not kept in the object.
     * \param
     *    p_data A pointer to data containing valid header
     *    information and custom message data.
     * \param
     *    p_data_length The number of bytes available in p_data.
     *    Must be at least sizeof(m_header) to fill the header
     *    data completely.
     * \note
     *    Just like with retrieveMessagePtr a 32 bit message
     *    length is needed here as the message length along with
     *    the header length may exceed 64 K.
     * \warning
     *    Any data present in the message before calling
     *    setRawData will be overwritten and thus lost.
     * \return
     *     \c false on success, \c true on error
     * \errors
     *    ipl::CommonError with reason INVALID_USAGE. This happens
     *    when the provided buffer and buffer length indicate an
     *    error. E.g. a NULL p_data pointer or a p_data length is
     *    less then sizeof(m_header).  If this error is raised
     *    then the object is left unaltered.
     **/
    bool setRawData(uint8_t const * const p_data,
        const uint32_t p_data_length) IPL_NOEXCEPT;

    /**
     * \brief
     *    Does the same as setRawData(uint8_t const* const, const
     *    uint32_t) but also sets a new blocksize that is applied
     *    before copying over new data.

     *    The semantics of the new blocksize setting is the same
     *    as with setData(.,., const blocksize).
     * \param[in]
     *    p_new_blocksize The new blocksize to be set into effect
     *    before setting the new data. The same restrictions apply
     *    as to the blocksize specified at construction time.
     * \return
     *     \c false on success, \c true on error
     **/
    bool setRawData(uint8_t const * const p_data,
        const uint32_t p_data_length,
        const blocksize p_new_blocksize) IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns a const pointer to the header data part of the
     *    message
     **/
    const HEADER_T* getHeaderData() const IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns the message data. The provided buffer p_buffer
     *    must provide at least enough space for the amount of
     *    bytes returned from getDataLength()
     * \return
     *    16 bit message size, number of bytes valid in p_buffer
     * \exception
     *    IplException with IPL_INTEGRITY_ERROR. This is raised
     *    when the copied data doesn't have the excepted length.
     *    The failure doesn't leave the object in an
     *    unconsistent state by design but the reason for the
     *    failure indicates an integrity error nonetheless and
     *    this points to some bug in the class implementation or
     *    memory corruption. Continuing the program to work at
     *    this point is discouraged.
    **/
    int_fast16_t getData(uint8_t* const p_buffer,
        const uint16_t p_buffer_length) const IPL_NOEXCEPT;

    /**
     * \brief
     *    This method allows to add data to the custom message
     *    data part of the message. It also cares about the
     *    correct handling of message data blocks while adding the
     *    data.
     * \param[in]
     *    p_data A pointer to the message data to be added.
     * \param[in]
     *    p_bytes The number of bytes available in p_data.
     **/
    void addData(const uint8_t* const p_data,
        const uint16_t p_bytes) IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns a raw pointer to the message data, starting at
     *    the header data of the message or optionally at the
     *    custom message data. This should only be used in special
     *    cases e.g. when wanting to get a buffer valid for
     *    sending the message over a communication line.

     *    The retrieved pointer is constant as it should not be
     *    used to manipulate the message data from outside the
     *    BinaryMessage object. Also the pointer has to be
     *    returned to the object by usage of returnMessagePtr to
     *    avoid memory leaks.
     *    <br>
     *    The retrieved pointer may or may not be a copy of the
     *    actual message data.  This depends upon wheter the
     *    message currently fits into a single data block or not.
     *    If it fits into a single data block then a pointer to
     *    the real data is returned. Otherwise a pointer to a copy
     *    of the complete message is retrieved. No assumptions
     *    should be made, though, about the type of pointer
     *    returned.
     * \warning
     *    The pointer returned by this function should only be
     *    used for a specific purpose and not be stored for any
     *    longer time or be used when concurrent access may
     *    happen.  Danger of memory corruption is very high when
     *    the BinaryMessage object is manipulated and the
     *    previously returned pointer looses its validity.
     *    <br>
     *    Also the object may not be altered by any means before
     *    the pointer has been returned by calling
     *    retrieveMessagePtr.
     * \param[out]
     *    p_length In this variable the number of bytes valid in
     *    the returned pointer is written to. It is important not
     *    to access the returned pointer beyond this boundary.
     * \param[in]
     *    p_with_header If set to true then the pointer returned
     *    includes the header data of the object. Otherwise only
     *    the custom message data is returned.
     * \return
     *    A pointer to the message data (starting at the header
     *    data if p_with_header is true!), NULL on error
     * \errors
     *     ipl::CommonError with ID OUT_OF_MEMORY if no memory was
     *     available for allocating the ptr.
     **/
    const uint8_t* retrieveMessagePtr(uint32_t& p_length,
        const bool p_with_header = true) const IPL_NOEXCEPT;


    /**
     * \brief
     *    Return a pointer retrieved by retrieveMessagePtr to the
     *    object. Only pointers that have been retrieved there may
     *    be provided as argument to this method. Also the pointer
     *    may be returned only once.
     * \post
     *    After the pointer has been returned it is no longer
     *    valid and may not be stored or used any more.
     * \param
     *    p_ptr The pointer that has been previously retrieved by
     *    retrieveMessagePtr
     **/
    void returnMessagePtr(const uint8_t* const p_ptr) const IPL_NOEXCEPT;

    /**
     * \brief
     *    Allows to set the header data part of the message to new values.
     * \param
     *    p_new_header A constant pointer to the new header data to be set.
     **/
    void setHeaderData(const HEADER_T* const p_new_header) IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns the number of valid bytes in the message data
     * \return
     *    16 bit message size
    **/
    inline uint16_t getDataLength() const IPL_NOEXCEPT;

    /**
     * \brief
     *    assignment operator that performs deep copy
     * \param
     *    p_other The object to assign to this object
     * \return
     *    A reference to the own object
     **/
    inline BinaryMessage& operator=(
        const BinaryMessage& p_other) IPL_NOEXCEPT;

    /**
     * \brief
     *    equality operator that checks wheter p_other contains
     *    the same data as this object. Header data and custom
     *    data is checked.

     *    Not checked is the parse position and the block size.
     * \param
     *    p_other The object that is to be compared against this
     *    object.
     * \return
     *    true if equal, false otherwise
     **/
    inline bool operator==(const BinaryMessage& p_other) const IPL_NOEXCEPT;

    /**
     * \brief
     *    not equal operator that checks wheter p_other contains
     *    different data than this object. Header data and custom
     *    data is checked.

     *    The same restrictions count here as for operator==
     * \return
     *    true is not equal, false otherwise
     **/
    inline bool operator!=(const BinaryMessage& p_other) const IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns the specified byte from the custom message data.
     *    This is only intended for easy and quick access to the
     *    data.
     * \param
     *    p_index The byte position in the custom message data
     *    which should be returned. [0] returns the first custom
     *    message data byte. The header data can not be retrieved
     *    by this functionality.
     * \return
     *    The byte at the specified index position of the message
     *    data
     **/
    inline uint8_t operator[](const uint16_t p_index) const IPL_NOEXCEPT;

    /**
     * \brief
     *    This method allows to retrieve a 16 bit value from the
     *    specified message byte position in host byte order.
     *    Counting starts at 0, where 0 is the first custom
     *    message data byte.
     * \param
     *    p_start_byte The byte position where the data extraction
     *    should start
     * \return
     *    The 16 bit value extracted from the given message position
     * \note
     *    The value will already be in host byte order!
     * \code
     *    // to get a 16 bit value that resides at byte 11 of the
     *    // custom message data:
     *
     *     BinaryMessage<SomeHeader> my_msg;
     *    uint16_t retrieved_value;
     *    retrieved_value = my_msg.getInt16(11);
     *    // now be happy with the retrieved_value
     * \endcode
     **/
    inline uint16_t getUint16(uint16_t p_start_byte) const IPL_NOEXCEPT;

    /**
     * \brief
     *    This method allows to retrieve a 32 bit value from the
     *    specified message byte position in host byte order.
     *    Counting starts at 0, where 0 is the first custom
     *    message data byte.
     * \param
     *    p_start_byte The byte position where the data extraction
     *    should start
     * \return
     *    The 32 bit value extracted from the given message position
     * \note
     *    The value will already be in host byte order
     * \code
     *    // To get a 32 bit value that resides at byte 11 of the
     *    // custom message data:
     *
     *     BinaryMessage<SomeHeader> my_msg;
     *    uint32_t retrieved_value;
     *    retrieved_value = my_msg.getInt32(11);
     *    // now be happy with the retrieved_value
     * \endcode
     **/
    inline uint32_t getUint32(uint16_t p_start_byte) const IPL_NOEXCEPT;

    /**
     * \brief
     *    Sets the current parsing position in bytes.

     *    For knowing where the parsing of a BinaryMessage has
     *    stopped this position marker is used.
     * \param
     *    p_pos The byte position where parsing has stopped. The
     *    byte this is refering to should not yet have been
     *    parsed. Byte 0 refers to the first byte in the custom
     *    message data part.
     * \warning
     *    this method still alters the parse position although it
     *    has a const modifier. This is as the parse position is a
     *    mutable class member
     **/
    inline void setParsePosition(const uint16_t p_pos) const IPL_NOEXCEPT;

    /**
     * \brief
     *    Get the current parsing position in bytes.

     *    For knowing where the parsing of a BinaryMessage has
     *    stopped this position marker is used. Parsing of the
     *    message starts at the first byte in the custom message
     *    data part of the message.
     * \return
     *    The byte position where the parsing of the message has
     *    been stopped the last time. The byte this is refering to
     *    should not yet have been parsed.
     **/
    inline uint16_t getParsePosition() const IPL_NOEXCEPT;

    /**
     * \brief
     *    Get the number of bytes left for parsing in the message.

     *    This allows to check wheter enough unparsed bytes exist
     *    to perform a certain operation.
     * \return
     *    getDataLength() - getParsePosition()
     **/
    inline uint16_t bytesLeft() const IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns wheter the parse position reached the end of the
     *    message
     * \return
     *    Returns true if getParsePosition() == getDataLength(),
     *    false otherwise
     **/
    inline bool parsingCompleted() const IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns wheter data is kept in network byte order.

     *    This is a construction time parameter. See the
     *    constructor for more information.
     * \return
     *    true if data is stored in network byte order
     **/
    inline bool isNetworkByteOrder() const IPL_NOEXCEPT;

private: // private non-static members
    /**
     * \brief
     *    This method deletes all dynamically allocated data.
     *    Should only be called in the destructor or when new data
     *    is setup.
     * \param
     *    p_keep_header_data If this flag is set to true then the
     *    first message data block will not be deleted, the header
     *    data will not be touched, but the m_data_length is set
     *    to 0. If set to false then all data will be freed and
     *    thus invalidated.
     * \errors
     *     ipl::CommonError with ID INVALID_USAGE.
     *    This is raised when the data was attempted to be double
     *    freed or some logical inconsistency occured. The error
     *    doesn't leave the object in an unconsistent state by
     *    design but the reason for the error indicates an
     *    integrity error nonetheless and this points to some bug
     *    in the class implementation or memory corruption.
     *    Continuing the program to work at this point is
     *    discouraged.
     * \return
     *     \c true on error, \c false otherwise
     **/
    bool freeData(const bool p_keep_header_data = false);

    /**
     * \brief
     *    Sets up the initial data block and the static message
     *    header data ready for use. Should only be used in the
     *    constructor or when new data is setup.
     * \return
     *     \c true on error, \c false otherwise
     * \errors
     *     ipl::CommonError with reason OUT_OF_MEMORY if data
     *     couldn't be allocated.
     *
     *    The error is also indicated when the function is called
     *    more than once without cleaning up or when some
     *    corruption has occured.
     **/
    bool initData();

    /**
     * \brief
     *    Removes any custom message data and optionally header
     *    data. Then all data blocks are freed and the first data
     *    block is created with a new blocksize in effect.

     *    The new blocksize will be set effective for the message
     *    object after return from the function call.
     * \param[in]
     *    p_new_blocksize The new blocksize that should be used
     *    for the object.
     * \param[in]
     *    p_keep_header Wheter the header data should be kept i.e.
     *    copied over to the new first data block after
     *    reallocation to the new blocksize.
     * \return
     *     \c false on success, \c true on error
     * \errors
     *     see \c initData()
     **/
    bool freeDataAndChangeBlocksize(const uint16_t p_new_blocksize,
        const bool p_keep_header);

    /**
     * \brief
     *    Checks the blocksize currently set in m_data_block_size
     *    and adjusts it to fit the purpose of our message object,
     *    if needed.

     *    The blocksize set differs from the found blocksize on
     *    the following conditions:
     *
     *    - if the blocksize is smaller than the HEADER_SIZE then
     *    it will be set to HEADER_SIZE
     *    - if the blocksize is not a multiple of 8 then it will
     *    be increased to be so.
     **/
    void normalizeBlocksize();

    /**
     * \brief
     *     Returns whether currently valid data is present in the
     *     object
     **/
    bool isValid()
    {
        return !m_data.empty();
    }

protected: // members
    //! \brief
    //! this is a pointer to the header data (located at the start
    //! of m_data[0])
    HEADER_T* m_header;

private: // members
    /**
     * Contains the overall number of valid bytes in the data
     * blocks. E.g. if m_data_length is 60 while the
     * m_data_block_size is 32 then the first block would contain
     * only valid bytes while the second block would contain 28
     * valid bytes.
     **/
    uint16_t m_data_length;

    //! \brief
    //! the data blocks used for this MostMessage - contains the
    //! actual data
    ipl::vector<uint8_t*> m_data;

    //! \brief
    //!    The block-size to be used for the m_data blocks.
    uint16_t m_data_block_size;

    //! \brief
    //!    Wheter the data stored is in network byte order
    bool m_network_byte_order;

    /**
     * \brief
     *    byte position where parsing of an incoming BinaryMessage
     *    has last stopped
     * \warning
     *    counting of parse positions starts at the first custom
     *    message byte, not at the first header byte!
     * \note
     *    this is a muteable member variable. The problem is that
     *    parsing a message object is in principle a const
     *    operation as while reading in parts from the message for
     *    parsing reasons is a read-only operation. But we want to
     *    have a current    parsing position and the only place
     *    where this makes sense is inside the message object
     *    itself. Thus we have to use mutable here to sustain the
     *    constness of the code while gaining flexibility by using
     *    this parsing position marker
     **/
    mutable uint16_t m_parse_position;

    //! the size of the header data in the first message data block
    static const uint_fast16_t HEADER_SIZE = sizeof(HEADER_T);
};


} // end namespace

// we need to include the function implementations in the header,
// because template functions aren't included in the shared library
// otherwise
#include <util/BinaryMessage.inl>

#endif
