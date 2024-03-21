/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ISTREAMDESERIALIZER_HXX
#define UTIL_SERIALIZER_ISTREAMDESERIALIZER_HXX

#include <util/util_dso.h>
#include <util/serializer/serializer.hxx>
#include <util/transport/Readable.hxx>
#include <common/types/vector.hxx>

namespace util
{
namespace serializer
{

/**
 *     \brief
 *         Abstract interface for stream based deserializers

 *         This interface is implemented by every stream based deserializer implementation.
 *
 *         It consists for three major parts:
 *
 *         - operators for deserialization of primitive data types from an associated Readable
 *         object from util::transport
 *
 *         - (De)Serializer pair matching function canHandleSerializer() that gets passed a
 *         serializer ID from IStreamSerializer::getSerializerID() to check whether the
 *         deserializer can understand the binary data from the serializer.
**/
class UTIL_EXPORT IStreamDeserializer
{
public: // methods
    IStreamDeserializer() IPL_NOEXCEPT : m_has_error(false) { }

    //! to have implementors destructor always called
    virtual ~IStreamDeserializer() IPL_NOEXCEPT { };

    /**
     *    \brief
     *        Return an identification token for the serializer instance.

     *        The returned identification token is to be considered opaque to the user. It
     *        is exactly one byte in size and can be passed to
     *        IStreamDeserializer::canHandleSerializer() for compatibility checking.
     **/
    virtual uint8_t getSerializerID() IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Return whether the deserializer instance is compatible with the given
     *        serializer ID.
     *    \return
     *        true if the given serializer ID is compatible with the current deserializer
     *        instance, false otherwise.
     **/
    virtual bool canHandleSerializer(const uint8_t id) IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Attach a new Readable buffer to the deserializer.

     *        This associates a new Readable buffer with the deserializer to be used for
     *        subsequent deserialization operations.
     *
     *        The deserialization has to be completed by calling detachBuffer().
     *    \param[in] r
     *        Readable buffer where data will be read from for deserialization. Data may
     *        be read during this function call, during calls to deserialization operators
     *        and during calls to detachBuffer().
     **/
    virtual void attachBuffer(util::transport::Readable r) IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Finish the deserialization operation on the currently attached Readable
     *        buffer.

     *        After all data has been read from the deserializer the deserialization
     *        operation needs to be finished via this function.
     *
     *        After return of the function the Readable attached via attachBuffer() will
     *        no longer be associated with this deserializer. The deserializer can then
     *        be attached a new buffer.
     *    \return
     *        Amount of data in bytes that has been parsed from the associated Readable.
     *        If this is less then the readables size then some data was not deserialized
     *        by the user.
     **/
    virtual size_t detachBuffer() IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Deserialize the given primitive data type from the stream
     *    \return
     *        A reference to the current object.
     **/
    virtual IStreamDeserializer& operator>>(bool &val) IPL_NOEXCEPT = 0;

    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(int8_t &val) IPL_NOEXCEPT = 0;
    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(uint8_t &val) IPL_NOEXCEPT = 0;

    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(int16_t &val) IPL_NOEXCEPT = 0;
    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(uint16_t &val) IPL_NOEXCEPT = 0;

    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(int32_t &val) IPL_NOEXCEPT = 0;
    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(uint32_t &val) IPL_NOEXCEPT = 0;

    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(int64_t &val) IPL_NOEXCEPT = 0;
    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(uint64_t &val) IPL_NOEXCEPT = 0;

    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(float &val) IPL_NOEXCEPT = 0;
    //! \see operator>>(bool)
    virtual IStreamDeserializer& operator>>(double &val) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Serialize the given flags object onto the stream
     * \note
     *     The Flags object needs to be set to the correct number of bits for deserialization
     *     to work correctly.
     * \see
     *     operator>>(bool)
     **/
    virtual IStreamDeserializer& operator>>(util::serializer::Flags &f) IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Deserialize an array sequence of the given primitive type from the stream
     *  \b WARNING: Do not use for vector<bool>,
     *   use operator >> (ipl::vector<bool>) instead!
     *    \return
     *        A reference to the current object.
     **/
    virtual IStreamDeserializer& operator>>(serializer::Array<bool> &a) IPL_NOEXCEPT = 0;
    /**
     *    \brief
     *        Deserialize a bool vector which is not stored as an array of bools
     *    \return
     *        A reference to the current object.
     **/
    virtual IStreamDeserializer& operator>>(ipl::vector<bool> &v) IPL_NOEXCEPT = 0;

    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<int8_t> &a) IPL_NOEXCEPT = 0;
    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<uint8_t> &a) IPL_NOEXCEPT = 0;

    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<int16_t> &a) IPL_NOEXCEPT = 0;
    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<uint16_t> &a) IPL_NOEXCEPT = 0;

    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<int32_t> &a) IPL_NOEXCEPT = 0;
    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<uint32_t> &a) IPL_NOEXCEPT = 0;

    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<int64_t> &a) IPL_NOEXCEPT = 0;
    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<uint64_t> &a) IPL_NOEXCEPT = 0;

    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<float> &a) IPL_NOEXCEPT = 0;
    //! \see operator>>(serializer::Array<bool>)
    virtual IStreamDeserializer& operator>>(serializer::Array<double> &a) IPL_NOEXCEPT = 0;

    //! returns true if the last operation failed, false otherwise
    bool hasError() const IPL_NOEXCEPT
    { return m_has_error; }
protected:
    //! set error indication
    void setError() const IPL_NOEXCEPT
    { m_has_error = true; }

    //! unset error indication
    void resetError() const IPL_NOEXCEPT
    { m_has_error = false; }
private:
    mutable bool m_has_error;
}; // class IStreamDeserializer

} // end namespace serializer
} // end namespace util

#endif
