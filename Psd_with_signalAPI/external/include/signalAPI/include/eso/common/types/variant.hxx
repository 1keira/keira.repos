/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_TYPES_VARIANT_H
#define COMMON_TYPES_VARIANT_H

#include <common/types/utility.hxx>
#include <ipl_config.h>

#if defined(HAVE_ARA_CORE_VARIANT) && defined(USE_ARA_CORE_VARIANT)
#define IPL_VARIANT_NAMESPACE ara::core
#include <ara/core/variant.h>

#elif defined(HAVE_STD_VARIANT) && __cplusplus >= 201703L
#define IPL_VARIANT_NAMESPACE std
#include <variant>

#else
#define IPL_VARIANT_NAMESPACE mpark
#include <mpark/variant.hpp>
#endif

namespace IPL_NAMESPACE {
#if defined(HAVE_ARA_CORE_VARIANT) && defined(USE_ARA_CORE_VARIANT)
        using IPL_VARIANT_NAMESPACE::Variant;
        template <typename...U>
        using variant = IPL_VARIANT_NAMESPACE::Variant<U...>;
#else
        using IPL_VARIANT_NAMESPACE::variant;
#endif
        // Non member functions;
        using IPL_VARIANT_NAMESPACE::visit;
        using IPL_VARIANT_NAMESPACE::holds_alternative;
        using IPL_VARIANT_NAMESPACE::get;
        using IPL_VARIANT_NAMESPACE::get_if;
        using IPL_VARIANT_NAMESPACE::operator==;
        using IPL_VARIANT_NAMESPACE::operator!=;
        using IPL_VARIANT_NAMESPACE::operator<;
        using IPL_VARIANT_NAMESPACE::operator<=;
        using IPL_VARIANT_NAMESPACE::operator>;
        using IPL_VARIANT_NAMESPACE::operator>=;

        using IPL_VARIANT_NAMESPACE::swap;

        using IPL_VARIANT_NAMESPACE::monostate;
        using IPL_VARIANT_NAMESPACE::bad_variant_access;
        using IPL_VARIANT_NAMESPACE::variant_size;
        using IPL_VARIANT_NAMESPACE::variant_size_v;
        using IPL_VARIANT_NAMESPACE::variant_alternative;
        using IPL_VARIANT_NAMESPACE::variant_alternative_t;

        using IPL_VARIANT_NAMESPACE::in_place_index_t;
        using IPL_VARIANT_NAMESPACE::in_place_type_t;

} //namespace IPL_NAMESPACE

#endif //COMMON_TYPES_VARIANT_H
