/*
    Copyright 2020, 2022 e.solutions GmbH
    All rights reserved
*/


#ifndef TRACING_OBJECTNODE_HXX
#define TRACING_OBJECTNODE_HXX

#include <ipl_config.h>

#include <common/UUID.hxx>
#include <common/types/map.hxx>
#include <common/types/vector.hxx>
#include <common/types/variant.hxx>
#include <common/types/optional.hxx>
#include <common/Singleton.hxx>

#include <memory>   //std::unique_ptr support

#ifdef HAVE_ARA_CORE_STRING
#include <ara/core/string.h>
#endif /* HAVE_ARA_CORE_STRING */

/*****************************************************************************/
namespace tracing {
   /*****************************************************************************/
    /* Forward declaration of Composite classes*/
    class BaseNode;
    class ArrayNode;
    class ObjectNode;
    class ScalarNode;
    class NullNode;

    /*****************************************************************************/

    /*!
     * \brief
     *   A visitor interface for traverse over Nodes
     *
     *  This class implements visitor design pattern and allows to define classes
     *  that operate on elements of Tags and traverses inside Tree over elements
     *  and children without the need to modify the source
     */
    class INodeVisitor {
    public:
        //! \brief Default constructor.
        INodeVisitor() = default;
        //! \brief Virtual default destructor.
        virtual ~INodeVisitor() = default;

        //! \brief Visit and operate on a \sa ScalarNode.
        virtual void visit(const ScalarNode &node) = 0;
        //! \brief Visit and operate on a \sa ArrayNode.
        virtual void visit(const ArrayNode &node) = 0;
        //! \brief Visit and operate on a \sa ObjectNode.
        virtual void visit(const ObjectNode &node) = 0;
        //! \brief Visit and operate on a \sa NullNode.
        virtual void visit(const NullNode &node) = 0;
    };

    /*!
     * \brief
     *   Base Node declaration of composite pattern
     */
    class BaseNode {
    public:
        //! \brief Default constructor.
        BaseNode() = default;
        //! \brief Virtual default destructor.
        virtual ~BaseNode() = default;

        //! \brief Let a visitor operate on the Node.
        virtual void accept(INodeVisitor &visitor) = 0;

        //! \brief Clones a BaseNode instance.
        virtual std::unique_ptr<BaseNode> clone() const = 0;
    };

    using BaseNodePtr = std::unique_ptr<BaseNode>;

    /*****************************************************************************/

    /*!
     * \brief
     *   Null Node type - declares an object inside composite tree that has no value
     */

    class NullNode : public BaseNode {
    public:
        //! \brief Default constructor.
        NullNode() = default;
        //! \brief Virtual default destructor.
        ~NullNode() override = default;

        //! \brief Let a visitor operate on the NullNode.
        void accept(INodeVisitor &visitor) override {
            visitor.visit(*this);
        }

        //! \brief Clones the NullNode.
        std::unique_ptr<BaseNode> clone() const override {
            std::unique_ptr<NullNode> newelem(new NullNode);
            return newelem;
        }
    };

    using NullNodePtr = std::unique_ptr<NullNode>;

    /*****************************************************************************/

    /*!
     * \brief
     *   This class declares an object that contains a scalar value
     */
    class ScalarNode : public BaseNode {
    public:
        //! \brief Supported ScalarNode variant types.
        using ScalarNodeVariant
                = ipl::variant < std::string, uint8_t, uint16_t, uint32_t, uint64_t,
                int8_t, int16_t, int32_t, int64_t, bool
#ifdef HAVE_ARA_CORE_STRING
                , ara::core::String
#endif /* HAVE_ARA_CORE_STRING */
                >;

    private:
        ScalarNodeVariant m_value;

    public:
        //! \brief Constructor.
        explicit ScalarNode(const ScalarNodeVariant & value) : m_value(value) {/* nop */}
        //! \brief Virtual default destructor.
        ~ScalarNode() override = default;

        //! \brief Get the ScalarNode variant value.
        const ScalarNodeVariant& getValue() const {return m_value;}
        //! \brief Set the ScalarNode variant value.
        void setValue(const ScalarNodeVariant &value)  {m_value = value;}

        //! \brief Let a visitor operate on the ScalarNode.
        void accept(INodeVisitor &visitor) override {
            visitor.visit(*this);
        }

        //! \brief Clones the ScalarNode.
        std::unique_ptr<BaseNode>clone() const override {
            std::unique_ptr<ScalarNode> newelem(new ScalarNode(m_value));
            return newelem;
        }
    };
    using ScalarNodePtr = std::unique_ptr<ScalarNode>;

    /*****************************************************************************/

    /*!
     * \brief
     *   This class declares an object that contains a map (key->value Node)
     */
    class ObjectNode : public BaseNode {
    public:
        using ObjectNodeMap = ipl::map<std::string, BaseNodePtr>;
    private:
        ObjectNodeMap m_map;
    public:
        //! \brief Default constructor.
        ObjectNode() = default;
        //! \brief Virtual default destructor.
        ~ObjectNode() override = default;

        //! \brief Get the map of \sa BaseNodes.
        const ObjectNodeMap& getValues() const {return m_map;}

        //! \brief Add a \sa BaseNode with its key to the ObjectNode.
        void add(const std::string & key, BaseNodePtr value) {m_map[key] = std::move(value);}

        //! \brief Let a visitor operate on the ObjectNode.
        void accept(INodeVisitor &visitor) override {
            visitor.visit(*this);
        }

        //! \brief Clones the ObjectNode.
        std::unique_ptr<BaseNode> clone() const override {
            std::unique_ptr<ObjectNode> newelem(new ObjectNode);
            for (auto it = m_map.begin(); it != m_map.end(); it++)
            {
                newelem->add((*it).first, (*it).second->clone());
            }
            return newelem;
        }

    };
    using ObjectNodePtr = std::unique_ptr<ObjectNode>;

    /*****************************************************************************/

    /*!
     * \brief
     *   This class declares an object that contains an array of other Nodes
     */
    class ArrayNode : public BaseNode {
    public:
        using ArrayNodeVector = ipl::vector<BaseNodePtr>;
    private:
        ArrayNodeVector m_array;
    public:
        //! \brief Default constructor.
        ArrayNode() = default;
        //! \brief Virtual default destructor.
        ~ArrayNode() override = default;

        //! \brief Get the vector of \sa BaseNode pointers.
        const ArrayNodeVector& getValues() const {return m_array;}

        //! \brief Add a \sa BaseNode pointer to the ArrayNode.
        void add(BaseNodePtr newElem) {m_array.push_back(std::move(newElem));}

        //! \brief Let a visitor operate on the ArrayNode.
        void accept(INodeVisitor &visitor) override {
            visitor.visit(*this);
        }

        //! \brief Clones the ArrayNode.
        std::unique_ptr<BaseNode> clone() const override {
            std::unique_ptr<ArrayNode> newelem(new ArrayNode);
            for (auto it = m_array.begin(); it != m_array.end(); it++)
            {
                newelem->add((*it)->clone());
            }
            return newelem;
        }
    };

    using ArrayNodePtr = std::unique_ptr<ArrayNode>;

    /*****************************************************************************/
}
/*****************************************************************************/
#endif /*  TRACING_OBJECTNODE_HXX */

