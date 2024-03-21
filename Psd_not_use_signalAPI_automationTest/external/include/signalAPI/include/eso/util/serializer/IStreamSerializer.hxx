/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ISTREAMSERIALIZER_HXX
#define UTIL_SERIALIZER_ISTREAMSERIALIZER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/transport/Writeable.hxx>
#include <util/serializer/serializer.hxx>
#include <common/types/vector.hxx>

namespace util
{
namespace serializer
{

/**
 *     \brief
 *         Abstract interface for stream based serializers

 *         This interface is implemented by every stream based serializer implementation.
 *
 *         It consists of the following major parts:
 *
 *         - operators for serialization of primitive data types into a Writeable object from
 *         util::transport
 *
 *         - (De)Serializer pair matching function getSerializerID() that can be fed to the
 *         IStreamDeserializer::canHandleSerializer() for compatibility checking.
 *
 *         - begin/end API for the size calculation pass. This pass does not actually serialize
 *         the data turned into the serializer but the serializer only calculates the size of
 *         the resulting binary representation of the complete serialized data structure.
 *
 *         - attach/detach API for associating the serializer with a Writeable from
 *         util::transport and actually do serialization.
**/
class UTIL_EXPORT IStreamSerializer
{
public: // methods
    IStreamSerializer() IPL_NOEXCEPT : m_has_error(false) { }

    //! to have implementors destructor always called
    virtual ~IStreamSerializer() IPL_NOEXCEPT { };

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
     *        Attach a new Writeable buffer to the serializer.

     *        This causes an implicit mode change into the serialization pass. Further
     *        calls to serialization operators will perform actual serialization
     *        operations and fill the buffer turned in here.
     *
     *        The serialization has to be completed by calling detachBuffer().
     *    \param[in,out] w
     *        Writeable buffer where serialized data will go to. Data may be written
     *        during this function call, during calls to serialization operators and
     *        during calls to detachBuffer().
     *    \errorindicator
     *        via hasError()
     *    \errors
     *        serializer::Error with IDs:
     *
     *        - INVALID_MODE if a previous beginSizeCalc()/attachBuffer() call has not
     *        been completed via endSizeCalc()/detachBuffer().
     **/
    virtual void attachBuffer(const util::transport::Writeable &w) IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Finish the serialization operation on the currently attached Writeable
     *        buffer.

     *        After all data has been streamed into the serializer the serialization
     *        operation needs to be finished via this function.
     *
     *        After return of the function the Writable attached via attachBuffer() will
     *        no longer be associated with this serializer and is ready for sending via a
     *        util::transport. The serializer can then be attached a new buffer or start a
     *        size calculation via beginSizeCalc().
     *    \return
     *        Amount of data in bytes that was written in the attached Writeable for the
     *        complete serialization operation since attachBuffer was called.
     *    \errorindicator
     *        via hasError()
     *    \errors
     *        serializer::Error with IDs:
     *
     *        - INVALID_MODE if the serializer is currently in size calculation mode (i.e.
     *        a beginSizeCalc() was not finished via endSizeCalc()) or if no buffer is
     *        currently attached to the serializer (via a call to attachBuffer()).
     **/
    virtual size_t detachBuffer() IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Start a size calculation pass on the serializer.

     *        This causes an implicit mode change into the size calculation pass. During
     *        a size calculation pass no Writeable is associated with the serializer and
     *        no serialization operations actually perform serialization but only the
     *        amount of serialized data that would be generated is calculated.
     *
     *        The user can perform all serialization steps as if he were really
     *        serializing. When finished, a call to endSizeCalc() returns the
     *        calculated amount of data that the serialization will take. This number can
     *        then be used for retrieving a suitably sized Writeable to be passed to
     *        attachBuffer().
     *    \errorindicator
     *        via hasError()
     *    \errors
     *        serializer::Error with IDs:
     *
     *        - INVALID_MODE if a previous beginSizeCalc()/attachBuffer() call has not
     *        been completed via endSizeCalc()/detachBuffer().
     **/
    virtual void beginSizeCalc() IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Finish a currently active size calculation operation.

     *        A size calculation pass previously started via beginSizeCalc() is
     *        finished via a call to this function. The serializer will then return the
     *        calculated amount of data in bytes, that the serialization operation would
     *        have consumed in the Writeable buffer.
     *
     *        After this function returns a new size calculation can be started via
     *        beginSizeCalc() or a Writeable may be attached via attachBuffer().
     *    \return
     *        Amount of data in bytes that the serialize operation would have consumed.
     *    \errorindicator
     *        via hasError()
     *    \errors
     *        serializer::Error with IDs:
     *
     *        - INVALID_MODE if the serializer has currently a Writeable attached (i.e. an
     *        attachBuffer() was not finished via detachBuffer()) or if no size
     *        calculation pass was initiated at the serializer (via a call to
     *        beginSizeCalc()).
     **/
    virtual size_t endSizeCalc() IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Serialize the given primitive data type onto the stream.
     *    \return
     *        A reference to the current object.
     *    \errorindicator
     *        via hasError()
     *    \errors
     *        serializer::Error with IDs:
     *
     *        - INVALID_MODE if neither a buffer is attached to the serializer nor size
     *        calculation mode is active
     *        - WRITEABLE_OVERFLOW if the associated Writeable buffer is full
     **/
    virtual IStreamSerializer& operator<<(bool val) IPL_NOEXCEPT = 0;

    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(int8_t val) IPL_NOEXCEPT = 0;
    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(uint8_t val) IPL_NOEXCEPT = 0;

    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(int16_t val) IPL_NOEXCEPT = 0;
    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(uint16_t val) IPL_NOEXCEPT = 0;

    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(int32_t val) IPL_NOEXCEPT = 0;
    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(uint32_t val) IPL_NOEXCEPT = 0;

    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(int64_t val) IPL_NOEXCEPT = 0;
    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(uint64_t val) IPL_NOEXCEPT = 0;

    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(float val) IPL_NOEXCEPT = 0;
    //! \see operator<<(bool)
    virtual IStreamSerializer& operator<<(double val) IPL_NOEXCEPT = 0;

    //! serialize the given flags object onto the stream
    virtual IStreamSerializer& operator<<(const serializer::Flags &f) IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Serialize an array sequence of the given primitive type onto the stream
     *  \b WARNING: Do not use for vector<bool>,
     *   use operator << (ipl::vector<bool>) instead!
     *    \return
     *        A reference to the current object.
     *    \errorindicator
     *        via hasError()
     *    \errors
     *        serializer::Error with IDs:
     *
     *        - INVALID_MODE if neither a buffer is attached to the serializer nor size
     *        calculation mode is active
     *        - WRITEABLE_OVERFLOW if the associated Writeable buffer is full
     **/
    virtual IStreamSerializer& operator<<(const serializer::Array<bool> &a) IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Serialize a bool vector which is not stored as an array of bools
     *    \return
     *        A reference to the current object.
     **/
    virtual IStreamSerializer& operator<<(const ipl::vector<bool> &v) IPL_NOEXCEPT = 0;

    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<int8_t> &a) IPL_NOEXCEPT = 0;
    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<uint8_t> &a) IPL_NOEXCEPT = 0;

    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<int16_t> &a) IPL_NOEXCEPT = 0;
    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<uint16_t> &a) IPL_NOEXCEPT = 0;

    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<int32_t> &a) IPL_NOEXCEPT = 0;
    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<uint32_t> &a) IPL_NOEXCEPT = 0;

    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<int64_t> &a) IPL_NOEXCEPT = 0;
    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<uint64_t> &a) IPL_NOEXCEPT = 0;

    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<float> &a) IPL_NOEXCEPT = 0;
    //! \see operator<<(const serializer::Array<bool>)
    virtual IStreamSerializer& operator<<(const serializer::Array<double> &a) IPL_NOEXCEPT = 0;

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
}; // class IStreamSerializer

} // end namespace serializer
} // end namespace util

#endif
