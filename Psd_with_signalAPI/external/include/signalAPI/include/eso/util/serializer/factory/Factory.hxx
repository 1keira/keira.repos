/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_FACTORY_HXX
#define UTIL_SERIALIZER_FACTORY_HXX

#include <util/util_dso.h>

#include <common/types/string.hxx>
#include <util/serializer/serializer.hxx>
#include <util/serializer/IStreamSerializer.hxx>
#include <util/serializer/IStreamDeserializer.hxx>
#include <util/transport/factory/TransportConfig.hxx>

namespace util
{
namespace serializer
{

/**
 *     \brief
 *         Construct a suitable serializer/deserializer pair for a given transport
 *         configuration.

 *         To not have compile time decisions about how (de)serialization is done on a certain
 *         communication link, the serializer facility uses the transport configuration
 *         facility to obtain (de)serializer instances in an abstract way.
 *
 *         The (de)serializers are currently configured via an additional attribute of
 *         transport service specifications in the configuration files. Thus there is a dependency
 *         of the serializer to the transport facility. This is okay, though as the
 *         (de)serializer uses infrastructure from there anyway (Readable, Writeable).
**/
class UTIL_EXPORT Factory
{
public: // subclasses / fwd. decl. / types

public: // methods
    /**
     *    \brief
     *        Construct a factory for the given set of transport identifiers, acting as
     *        client side.
     *    \param[in] src_proc
     *        the name of the process, which want't to connect
     *    \param[in] dest_proc
     *        The name of the process to which we want to connect
     *    \param[in] service
     *        The name of the service to use (e.g. comm, tracing)
     *    \errorindicator
     *        via isValid()
     *    \errors
     *        FactoryError from util::transport::TransportConfig::getSerializer
     **/
    Factory(const ipl::string &src_proc, const ipl::string &dest_proc, const ipl::string &service);

    /**
     *    \brief
     *        Construct a factory for the given set of transport identifiers, acting as
     *        server side.

     *        Does the same as Factory(const ipl::string&,const ipl::string&,const
     *        ipl::string&) but acts as server side. That is why no process parameter is
     *        required as it will be the name of the current process.
     **/
    Factory(const ipl::string &service);

    //! \brief
    //!    In debug mode asserts that no (de)serializer constructed by this factory is left out
    //!    there
    ~Factory();

    /**
     *    \brief
     *        Create a new serializer according to construction time specifications.

     *        Returns a ready to user serializer suitable to be used on the transport
     *        specified at construction time.
     *
     *        After the client is finished with using the serializer, it has to be
     *        returned to the factory via returnSerializer(). Multiple serializers may be
     *        acquired from the factory, if neccessary. Every one needs then to be
     *        returned.
     *    \return
     *        A reference to a new stream serializer instance.
     **/
    IStreamSerializer& createSerializer(Sanity &sanity=insanity);

    /**
     *    \brief
     *        Create a new deserializer according to construction time specification.s

     *        The same rules apply as to createSerializer(). Obtained instances need to be
     *        returned via returnDeserializer().
     *    \return
     *        A reference to a new stream deserializer instance.
     **/
    IStreamDeserializer& createDeserializer(Sanity &sanity=insanity);

    /**
     *    \brief
     *        Return a serializer previously acquired via createSerializer().

     *        Only a serializer acquired at the same factory instance may be returned
     *        here.
     *    \param[in] s
     *        Reference to a serializer instance previously acquired via createSerializer()
     *    \errors
     *        On mismatch program execution is aborted
     **/
    void returnSerializer(IStreamSerializer &s);

    /**
     *    \brief
     *        Return a deserializer previously acquired via createDeserializer().

     *        Only a deserializer acquired at the same factory insance may be returned
     *        here.
     *    \param[in] d
     *        Reference to a deserializer instance previously acquired via
     *        createDeserializer()
     *    \errors
     *        On mismatch program execution is aborted
     **/
    void returnDeserializer(IStreamDeserializer &d);

    bool isValid() const
    { return m_is_valid; }
protected: // members
    bool m_is_valid;
    //! the abstract serializers constructed by this factory
    ipl::set<IStreamSerializer*> m_sers;
    //! the abstract deserializers constructed by this factory
    ipl::set<IStreamDeserializer*> m_desers;

    //! The different (de)serializer types the factory supports
    //! The (de)serializer type this factory is constructing
    util::transport::TransportConfig::SerializerType m_type;
}; // class Factory

} // end namespace serializer
} // end namespace util

#endif
