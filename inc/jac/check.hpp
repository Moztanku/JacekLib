#pragma once

#include <source_location>
#include <format>

#include "jac/ansi.hpp"
#include "jac/print.hpp"
#include "jac/debug.hpp"
#include "jac/utils.hpp"

namespace jac {
    template<typename T>
    void CHECK_IMPL(T condition_value,
        const char* condition_text,
        const std::source_location& location) noexcept
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);
        if (Debug && !static_cast<bool>(condition_value)) {
            print_warning(
                std::format("Check \"{}{}{}\" failed", style, condition_text, ANSI_EC::reset),
                location
            );
        }
    }

    template<typename T>
    void CHECK_EQ_IMPL(const T& lhs, const T& rhs,
        const char* lhs_text, const char* rhs_text,
        const std::source_location& location) noexcept
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);

        if (Debug && lhs != rhs) {
            print_warning(
                std::format("CheckEQ \"{0}{2}{1}\" == \"{0}{3}{1}\" failed", style, ANSI_EC::reset, lhs_text, rhs_text),
                location
            );

            print_warning(
                std::format("   Values: {0}{2}{1} != {0}{3}{1}", style, ANSI_EC::reset, lhs, rhs),
                location
            );
        }
    };

    template<typename T, typename U>
    void CHECK_EQ_IMPL(const T& lhs, const U& rhs,
        const char* lhs_text, const char* rhs_text,
        const std::source_location& location) noexcept
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);
        print_warning(
            std::format(
                "CheckEQ \"{0}{2}{1}\" == \"{0}{3}{1}\" failed", 
                style, ANSI_EC::reset, lhs_text, rhs_text
            ), location
        );

        print_warning(
            std::format(
                "   Types: {0}{2}{1} != {0}{3}{1}",
                style, ANSI_EC::reset,
                jac::type_name<T>(), jac::type_name<U>
            ), location
        );
    };
}   // namespace jac

#define JAC_CHECK(condition) \
    jac::CHECK_IMPL(condition, #condition, std::source_location::current())

#define JAC_CHECK_EQ(lhs, rhs) \
    jac::CHECK_EQ_IMPL(lhs, rhs, #lhs, #rhs, std::source_location::current())
