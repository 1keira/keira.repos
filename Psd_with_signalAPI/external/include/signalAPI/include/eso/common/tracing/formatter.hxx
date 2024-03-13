/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#pragma once

#include <fmt/format.h>

namespace ipl {
    class UUID;
    namespace unicode {
        class String;
    }
}
namespace util { class UnicodeString8; }

namespace fmt {

    //! \brief fmt formatter for UUID
    template <>
    struct formatter< ::ipl::UUID >
    {
        constexpr auto * parse(format_parse_context& ctx)
        {
            return ctx.begin();
        }

        template <typename T, typename FormatContext>
        auto format(T msg, FormatContext& ctx)
        {
            return ::fmt::format_to(ctx.out(), msg.toString());
        }
    };
    //! \brief fmt formatter for unicode string
    template <>
    struct formatter< ::ipl::unicode::String >
    {
        constexpr auto * parse(format_parse_context& ctx)
        {
            return ctx.begin();
        }

        template <typename T, typename FormatContext>
        auto format(T msg, FormatContext& ctx)
        {
            return ::fmt::format_to(ctx.out(), msg.str().c_str());
        }
    };
    //! \brief fmt formatter for UnicodeString8
    template <>
    struct formatter< ::util::UnicodeString8 >
    {
        constexpr auto * parse(format_parse_context& ctx)
        {
            return ctx.begin();
        }

        template <typename T, typename FormatContext>
        auto format(T msg, FormatContext& ctx)
        {
            return ::fmt::format_to(ctx.out(), msg.utf8().char_str());
        }
    };

}   // fmt

