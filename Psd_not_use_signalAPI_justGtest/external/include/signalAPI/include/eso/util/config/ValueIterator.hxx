/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CONFIG_VALUEITERATOR_HXX
#define UTIL_CONFIG_VALUEITERATOR_HXX

#include <common/types/iterator.hxx>
#include <common/types/map.hxx>

namespace util {
namespace config {

class Value;

template <typename ConcreteIterator>
class value_iterator
{
public: // types
    /// A type that represents the type of object stored as an element in a map.
    typedef typename ConcreteIterator::reference reference;
    typedef typename ConcreteIterator::pointer pointer;
    typedef typename ConcreteIterator::value_type value_type;

protected: // types

    typedef value_iterator<ConcreteIterator> Self;
    typedef ConcreteIterator concrete_iterator;

public: // data

    concrete_iterator it;

public: // functions
    value_iterator() = default;

    value_iterator(const ConcreteIterator &_it)
    : it(_it)
    {};

    value_iterator(const value_iterator<ipl::map<ipl::string, Value*>::iterator> & _it)
    {
        it = _it.it;
    };

    ~value_iterator() = default;

    value_iterator& operator=(const value_iterator&) = default;

    /// Iterate to the next element in the tree
    Self& operator++()
    {
        it++;
        return *this;
    }

    /// Iterate to the next element in the tree
    Self operator++(int)
    {
        Self tmp( *this );
        it++;
        return tmp;
    }

    /// Iterate to the previous element in the tree
    Self& operator--()
    {
        it--;
        return *this;
    }

    /// Iterate to the previous element in the tree
    Self operator--(int)
    {
        value_iterator tmp( *this );
        it--;
        return tmp;
    }

    /// Returns a reference to the element
    reference operator*() const
    {
        return *it;
    }

    pointer operator->() const
    {
        return &(*it);
    }

    /// Checks if both iterators were pointing to the same node
    bool operator==(value_iterator _it) const
    {
        return _it.it == it;
    }

    /// Checks if both iterators were pointing to different nodes
    bool operator!=(value_iterator _it) const
    {
        return !(_it.it == it);
    }
};

}
}

#endif // UTIL_CONFIG_VALUEITERATOR_HXX

