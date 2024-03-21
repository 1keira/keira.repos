/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_TYPES_UTILITY_H
#define COMMON_TYPES_UTILITY_H

#include <iterator>
#include <utility>
#include <common/ipl_namespace.hxx>


namespace IPL_NAMESPACE {

using std::swap;
using std::make_pair;
using std::pair;

#if __cplusplus >= 201703L

using std::data;
using std::size;
using std::empty;

#else

///\brief Return a pointer to the block of memory that contains the elements of a container
///\tparam Container a type with a data() methoed
///\param c (in) an instance of Container
///\return  a pointer to the first element of the container
template <typename Container>
constexpr auto data (Container &c) -> decltype(c.data())
{
    return c.data();
}

///\brief Return a const pointer to the block of memory that contains the elements of a container
///\tparam Container a type with a data() methoed
///\param c (in) an instance of Container
///\return  a pointer to the first element of the container
template <typename Container>
constexpr auto data (Container const &c) -> decltype(c.data())
{
    return c.data();
}
///@brief return a pointer to the block of memory that contains the elements of a raw array
template <typename T, std::size_t N>
constexpr T* data(T (&array)[N]) noexcept
{
    return array;
}

/// @brief Return a pointer to the block of memory that contains the elements of a std::initializer_list
template <typename E>
constexpr E const* data(std::initializer_list<E> il) noexcept
{
    return il.begin();
}

///@brief Return the size of a container.
template <typename Container>
constexpr auto size (Container const &c) -> decltype(c.size())
{
    return c.size();
}

///@brief Return the size of a raw array
template <typename T, std::size_t N>
constexpr std::size_t size (T const (&array)[N]) noexcept
{
    return N;
}


///@brief Return whether the given container is empty
template <typename Container>
constexpr auto empty (Container const &c) -> decltype(c.empty())
{
    return c.empty();
}

///@brief Return whether the given raw array is empty.
///As raw arrays cannot have zero elements in C++, this function always returns false.
template <typename T, std::size_t N>
constexpr bool empty (T const (&array)[N]) noexcept
{
    return false;
}

///@brief Return whether the given std::initializer_list is empty.
template <typename E>
constexpr bool empty (std::initializer_list< E > il) noexcept
{
    return il.size() == 0;
}

#endif

} // namespace IPL_NAMESPACE

#endif
