/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_LOGTAGFACTORY_HXX
#define TRACING_LOGTAGFACTORY_HXX

#include <ipl_config.h>
#include <tracing/tracing_dso.h>
#include <common/Singleton.hxx>
#include <common/tracing/ObjectNode.hxx>
#include <common/tracing/LogTag.hxx>

/*****************************************************************************/
namespace tracing {

/*!
 * \brief
 *   A Factory class implementation used to handle tags registration
 *
 * Use shall use LogTagFactory (singleton) instance to register own defined tags
 */
class TRACINGIMPL_EXPORT LogTagFactory
{
    IPL_DECLARE_SINGLETON(LogTagFactory)
public:
    //! \brief Factory uses function pointers to create tags
    using CreateMethod = std::unique_ptr<LogTagBase>(*)(const ipl::string &);
    //! \brief Factory keeps the rules how to create each tags
    using CreatorsList = ipl::map<ipl::string, CreateMethod>;
    //! \brief The map between tag name and tag type
    using TagTypesMap = ipl::map<ipl::string, LogTagType>;

    /*!
    *    \brief
    *        Registers a new tag.
    *
    *    \param
    *        name The tag name.
    *    \param
    *        type The tag type \sa LogTagType.
    *    \param
    *        funcCreate The creation method \sa CreateMethod
    *    \return
    *        true when successful, otherwise false.
    */
    bool Register(const ipl::string & name, LogTagType type, CreateMethod funcCreate)
    {
        auto it = m_allTags.find(name);
        if (it == m_allTags.end())
        {
            m_allTags[name] = funcCreate;
            m_knownTags[name] = type;
            return true;
        }
        return false;
    }

    /*!
    *    \brief
    *        Creates a new tag.
    *
    *    \param
    *        name The tag name.
    *    \param
    *        strValue A string being used for the registered creation method.
    *    \return
    *        unique pointer to \sa LogTagBase when successful, otherwise NULL.
    */
    std::unique_ptr<LogTagBase> Create(const ipl::string &name,
            const ipl::string &strValue)
    {
        auto it = m_allTags.find(name);
        if (it != m_allTags.end())
        {
            return it->second(strValue);
        }
        return nullptr;
    }

    //! \brief Return the list of already registered and known tags in the system
    const CreatorsList& getRegisteredTags()
    {
        return m_allTags;
    }

    //! \brief Return the number of registered tags
    size_t getRegisteredTagsCount()
    {
        return m_allTags.size();
    }

    /*!
    *    \brief
    *        Searches tag by its name and provides its \sa LogTagType.
    *
    *    \param
    *        name The tag name.
    *    \param
    *        idx The updated \sa LogTagType when tag was found.
    *    \return
    *        true when found and idx was updated, otherwise false.
    */
    bool findTagType(const ipl::string &name, LogTagType &idx)
    {
        auto it = m_knownTags.find(name);
        if (it != m_knownTags.end())
        {
            idx = it->second;
            return true;
        }
        return false;
    }
private:
    CreatorsList m_allTags;
    TagTypesMap m_knownTags;
};

} //namespace tracing

/*****************************************************************************/
#endif /* TRACING_LOGTAGFACTORY_HXX */

