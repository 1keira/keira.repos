/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_ENTITYURI_HXX
#define TRACING_ENTITYURI_HXX

#include <tracing/tracing_dso.h>
#include <common/stdint.h>
#include <common/types/string.hxx>
#include <common/streams/iostream.hxx>
#include <tracing/entity/EntityType.hxx>

namespace tracing
{

/*!
 *    \brief
 *        The entity URI is used for uniquely referencing a certain type of entity.
 */
class TRACINGIMPL_EXPORT EntityURI
{
public:
    static EntityURI INVALID_URI;
    //! \brief Comparison operator.
    struct UriCompare
    {
        bool operator()(const EntityURI & l, const EntityURI & r) const
        {
            return l.getId() < r.getId();
        }
    };
public:
    /*!
     *    \brief
     *        Constructor.
     *
     *        This default ctor is used when default-constructing entities which
     *        can happen internally in the trace core. Usually you should never
     *        use this constructor, the trace core returns valid URIs after creating
     *        new entities by calling createEntity() or friends.
     *      The default parameters for type and id denote an invalid EntityURI.
     *    \param
     *        type The entity type, as specified in EntityType.hxx
     *    \param
     *        id A unique ID, assigned by the trace core's model.
     */
    EntityURI(int16_t type = -1, int32_t id = -1) :
        m_type(type),
        m_id(id)
    {
    }

    //! \brief Copy constructor.
    EntityURI(const EntityURI & uri) :
        m_type(uri.m_type),
        m_id(uri.m_id)
    {
    }

    //! \brief Assignment operator.
    EntityURI & operator=(const EntityURI & uri)
    {
        if (this != &uri) {
            m_type = uri.m_type;
            m_id = uri.m_id;
        }
        return *this;
    }

    //! \brief Comparison operator.
    bool operator==(const EntityURI & uri) const
    {
        return m_type == uri.m_type && m_id == uri.m_id;
    }

    //! \brief Less than operator
    bool operator<(const EntityURI & uri) const
    {
        return m_type < uri.m_type || (m_type == uri.m_type && m_id < uri.m_id);
    }

    //! \brief Gets the type stored in the URI.
    int16_t getType() const
    {
        return m_type;
    }

    //! \brief Gets the ID stored in the URI.
    int32_t getId() const
    {
        return m_id;
    }

    //! \brief Creates a string representation of the URI.
    ipl::string toString() const;

    //! \brief Output operator for the URI.
    ipl::ostream & operator<<(ipl::ostream & out) const
    {
        return out << toString();
    }

    //! \brief Check if the URI is valid.
    bool isValid() const
    {
        return m_type >= 0 && m_type < EntityType::LAST_ENTITY && m_id >= 0;
    }

protected:
    int16_t m_type;  //! The entity type as defined in EntityType.hxx
    int32_t m_id;    //! The unique entity ID.
};

}

#endif /* TRACING_ENTITYURI_HXX */

