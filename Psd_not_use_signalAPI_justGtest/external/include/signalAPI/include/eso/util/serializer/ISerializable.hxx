/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ISERIALIZABLE_HXX
#define UTIL_SERIALIZER_ISERIALIZABLE_HXX

#include <util/util_dso.h>
#include <util/serializer/IStreamSerializer.hxx>
#include <util/serializer/IStreamSerializer.hxx>

namespace util
{
namespace serializer
{

/**
 *    \brief
 *        Abstract interface for serializable objects

 *        A class can implement this interface if it wants to be able to serialize itself into
 *        a util::serializer and also be able to deserialize itself from a util::serializer.
 **/
class ISerializable
{
public:

    virtual ~ISerializable() IPL_NOEXCEPT {}

    /**
     *    \brief
     *        Serialize the current object into serializer

     *        Any data required to reconstruct the current object at a later time should
     *        be serialized into serializer.
     *    \param[in,out] serializer
     *        The abstract serializer to write object data to
     *    \return
     *        Reference to the serializer object
     **/
    virtual IStreamSerializer& operator<<(IStreamSerializer &serializer) const IPL_NOEXCEPT = 0;

    /**
     *    \brief
     *        Assign the serialized object in deserializer to the current object

     *        The binary data present in deserializer is used to build up the current
     *        object from.
     *    \param[in,out] deserializer
     *        The abstract deserializer to read object data from
     *    \return
     *        Reference to the deserializer object
     **/
    virtual IStreamDeserializer& operator>>(IStreamDeserializer &deserializer) IPL_NOEXCEPT = 0;
};

/**
 *    \brief
 *        Global operator that allows streaming of ISerializable object into serializer

 *        This allows for:
 *        \code
 *        IStreamSerializer &my_serializer;
 *        ISerializable &my_serializable;
 *        my_serializer << my_serializable;
 *        \endcode
 *        It simply call the operator<< from the ISerializable interface with out as
 *        parameter.
 **/
inline IStreamSerializer& operator<<(IStreamSerializer& out, const ISerializable &s) IPL_NOEXCEPT
{
    return s << out;
}


/**
 *    \brief
 *        Global operator that allows streaming data into ISerializable object from deserializer

 *        This allows for:
 *        \code
 *        IStreamDeserializer &my_deserializer;
 *        ISerializable &my_serializable;
 *        my_deserializer >> my_serializable;
 *        \endcode
 *        It simply call the operator>> from the ISerializable interface with in as
 *        parameter.
 **/
inline IStreamDeserializer& operator>>(IStreamDeserializer& in, ISerializable &s) IPL_NOEXCEPT
{
    return s >> in;
}

} // end namespace serializer
} // end namespace util

#endif
