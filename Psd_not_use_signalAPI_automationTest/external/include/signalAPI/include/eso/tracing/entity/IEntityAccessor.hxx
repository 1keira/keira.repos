/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_IENTITY_ACCESSOR_HXX
#define TRACING_IENTITY_ACCESSOR_HXX

#include <common/tracing/Levels.hxx>
#include <tracing/tracing_dso.h>
#include <tracing/entity/IEntity.hxx>

namespace tracing
{

/*!
 *  \brief
 *      Interface accessor class for common access to entity methods.

 *      It is used in scope of message filter API.
 */
class IEntityAccessor
{
public:
    //! \brief Virtual destructor.
    virtual ~IEntityAccessor(){/* nop */}

    //! \brief Gets the filter level of an entity. \sa Levels.
    virtual int16_t getFilterLevel() const = 0;

    /*!
     *  \brief
     *      Gets the parents filter level of an entity.
     *  \param
     *      type The entity type. \sa EntityType.
     *  \return
     *      The parent's filter level. \sa Levels.
     */
    virtual int16_t getParentFilterLevel(const int16_t type) const {return Levels::LevelOFF;}

    /*!
     *  \brief
     *      Gets the privacy flags for the entity.
     *  \param
     *      filter_level The filter level for optionally available level
     *                   specific privacy flags. \sa Levels.
     *  \return
     *      The privacy flags. \sa LogTagTLRPrivacyFlag.
     */
    virtual uint32_t getPrivacyFlags(int16_t filter_level=Levels::LevelNONE) const = 0;

    /*!
     *  \brief
     *      Find the entity's parent of the given type.
     *  \param
     *      type The entity type. \sa EntityType.
     *  \return
     *      The parent entity or nullptr when not found.
     */
    virtual const IEntity * findParent(int16_t type) const {return nullptr;}
};

}

#endif /* TRACING_IENTITY_ACCESSOR_HXX */

