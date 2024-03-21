/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IENTITY_HXX
#define TRACING_IENTITY_HXX

#include <tracing/tracing_dso.h>
#include <common/types/string.hxx>

namespace tracing
{

class EntityURI;

/*!
 *  \brief
 *      Interface class for Entities.
 */
class TRACINGIMPL_EXPORT IEntity
{
public:
    //! \brief Virtual destructor.
    virtual ~IEntity() = 0;
    //! \sa Entity::getName()
    virtual const char * getName() const = 0;
    //! \sa Entity::getURI()
    virtual const EntityURI & getURI() const = 0;
    //! \sa Entity::getFilterLevel()
    virtual int16_t getFilterLevel() const = 0;
    //! \sa Entity::getBackendLevel()
    virtual int16_t getBackendLevel(int16_t bid) const = 0;
    //! \sa Entity::isEnabled()
    virtual bool isEnabled() const = 0;
    //! \sa Entity::getParent()
    virtual const IEntity * getParent() const = 0;
    //! \sa Entity::getParentURI()
    virtual const EntityURI & getParentURI() const = 0;
    //! \sa Entity::getEpoch()
    virtual int32_t getEpoch() const = 0;
    //! \sa Entity::clone()
    virtual IEntity * clone() const = 0;
    //! \sa Entity::toString()
    virtual ipl::string toString() const = 0;
};

inline IEntity::~IEntity() {/* nop */}

}

#endif /* TRACING_IENTITY_HXX */

