/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_MESSAGETAGS_HXX
#define TRACING_MESSAGETAGS_HXX

/*!
 *    \brief
 *        Message attributes contains Tags and Nodes
 *
 *        User can enrich tracing by applying additional information
 *        within the tracing messages such as Tags and Nodes.
 *
 *        In addition, user can define and add own tags to the system, and also
 *        can apply own filtering rules to define which user specific tags shall
 *        be carried to the frontend or backend
 *
 */

#include <common/iplcommon_dso.h>
#include <common/stdint.h>

#include <common/streams/iostream.hxx>
#include <common/types/string.hxx>
#include <common/types/vector.hxx>

#include <memory>
#include <common/types/map.hxx>
#include <common/types/variant.hxx>
#include <common/types/optional.hxx>
#include <common/Singleton.hxx>

#include "ObjectNode.hxx"
#include "LogTag.hxx"

namespace tracing {

    /*!
     * \brief
     *   A container for MessageAttributes (Nodes and Tags) that can be attached
     *   to the message.
     */
    class MessageAttributes {
    public:

        using TagsMask = ipl::vector<bool>;

    private:
        TagsList     m_tags;
        TagsMask     m_tagsMask;
        BaseNodePtr  m_object;
    public:
        using LogTagType = uint32_t;

        //! \brief Default constructor.
        MessageAttributes() = default;
        //! \brief Default destructor.
        ~MessageAttributes() = default;
        //! \brief Copy Constructor, disabled.
        MessageAttributes(const MessageAttributes &) = delete;
        //! \brief Move Constructor, disabled.
        MessageAttributes(MessageAttributes &&) = delete;
        //! \brief Copy assignment operator, disabled.
        MessageAttributes & operator=(const MessageAttributes &) = delete;

        //! \brief Instead of copying tags, it is always preferable to use move semantic.
        MessageAttributes& operator=(MessageAttributes &&attr)
        {
            m_tags = std::move(attr.m_tags);
            m_tagsMask = std::move(attr.m_tagsMask);
            m_object = std::move(attr.m_object);

            return *this;
        }

        //! \brief returns true if message attribute contains tags.
        bool hasTags()
        {
            return !m_tags.empty();
        }

        //! \brief returns true if given tag is known.
        bool hasTag(LogTagType tag)
        {
            if (tag < m_tagsMask.size())
                return m_tagsMask[tag];
            return false;
        }

        //! \brief returns true if message attribute has an object.
        bool hasObject()
        {
            return (bool) m_object;
        }

        //! \brief when known returns raw pointer to the tag by it's type, otherwise nullptr.
        template <typename T>
        T* getTagRawPtr(size_t type)
        {
            T* ret;
            for (auto it = m_tags.begin(); it != m_tags.end(); ++it)
            {
                if ((ret = (T*) ((*it).get()->cast(type))) != nullptr)
                    return ret;
            }
            return nullptr;
        }

        //! \brief when existing returns base pointer to the object node, otherwise nullptr.
        BaseNodePtr getObject()
        {
            if (hasObject())
                return std::move(m_object);
            return nullptr;
        }

        //! \brief swaps the tags content within message attribute.
        void forwardTags(TagsList& newTags)
        {
            m_tags.clear();
            m_tags.swap(newTags);

            m_tagsMask.clear();

            if (!m_tags.empty())
            {
                //generate TagsMask
                LogTagType max_tag = m_tags[0].get()->type();
                for (auto it = m_tags.begin(); it != m_tags.end(); ++it)
                {
                    if ((*it)->type() > max_tag)
                        max_tag = (*it)->type();
                }

                m_tagsMask.resize(max_tag + 1);
                for (auto it = m_tags.begin(); it != m_tags.end(); ++it)
                {
                    m_tagsMask[(*it)->type()] = true;
                }

            }
        }

        //! \brief Allows to print all tags of tags list and returns number of tags.
        int print_tags(ipl::ostream &os)
        {
            for (auto& tag : m_tags)
            {
                tag->print(os);
            }
            return (int)m_tags.size();
        }

        //! \brief swaps the object node content within message attribute.
        void forwardObject(BaseNodePtr &&object)
        {
            m_object = std::move(object);
        }

        //! \brief returns all tags within MessageAttributes container.
        const TagsList& getTags() const {return m_tags;}

        //! \brief returns tags mask. True at position I indicated that tag of this type
        //!        is presented in message attribute.
        TagsMask& getTagsMask() {return m_tagsMask;}

    };
} //namespace tracing

#endif /* TRACING_MESSAGETAGS_HXX */
