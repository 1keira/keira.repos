/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_TYPES_OPTIONAL_H
#define COMMON_TYPES_OPTIONAL_H

#include <common/types/utility.hxx>

#if defined(HAVE_STD_OPTIONAL) && __cplusplus >= 201703L
    #define IPL_OPTIONAL_NAMESPACE std
    #include <optional>
#else
    #define IPL_OPTIONAL_NAMESPACE std::experimental
    #include <akrzemi1/Optional/optional.hpp>
#endif


namespace IPL_NAMESPACE {

    using IPL_OPTIONAL_NAMESPACE::nullopt_t;
    using IPL_OPTIONAL_NAMESPACE::in_place_t;
    using IPL_OPTIONAL_NAMESPACE::bad_optional_access;
    using IPL_OPTIONAL_NAMESPACE::nullopt;
    using IPL_OPTIONAL_NAMESPACE::make_optional;
    using IPL_OPTIONAL_NAMESPACE::operator==;
    using IPL_OPTIONAL_NAMESPACE::operator!=;
    using IPL_OPTIONAL_NAMESPACE::operator<;
    using IPL_OPTIONAL_NAMESPACE::operator<=;
    using IPL_OPTIONAL_NAMESPACE::operator>;
    using IPL_OPTIONAL_NAMESPACE::operator>=;
    using IPL_OPTIONAL_NAMESPACE::swap;
    using IPL_OPTIONAL_NAMESPACE::optional;
    using IPL_OPTIONAL_NAMESPACE::in_place_t;

#if defined(HAVE_STD_OPTIONAL) && __cplusplus >= 201703L
    using IPL_OPTIONAL_NAMESPACE::in_place;
#else
    ///@brief The singleton instance of in_place_t
    constexpr in_place_t  in_place{};
#endif

} //namespace IPL_NAMESPACE

#endif //COMMON_TYPES_OPTIONAL_H
