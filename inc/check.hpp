#pragma once

#include <source_location>
#include <format>

#include <ansi.hpp>
#include <print.hpp>
#include <debug.hpp>
#include <types.hpp>

namespace jac {

    template<typename T>
    void CHECK_IMPL(T condition_value,
        const char* condition_text,
        const std::source_location& location) noexcept
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);
        if (DEBUG && !static_cast<bool>(condition_value)) {
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

        if (DEBUG && lhs != rhs) {
            print_warning(
                std::format("CheckEQ \"{}{}{}\" == \"{}{}{}\" failed", style, lhs_text, ANSI_EC::reset, style, rhs_text, ANSI_EC::reset),
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
                "CheckEQ \"{}{}{}\" == \"{}{}{}\" failed, different types {} and {}", 
                style, lhs_text, ANSI_EC::reset,
                style, rhs_text, ANSI_EC::reset, 
                jac::type_name<T>(), jac::type_name<U>()
            ), location
        );
    };

}   // namespace jac

#define CHECK(condition) \
    jac::CHECK_IMPL(condition, #condition, std::source_location::current())

#define CHECK_EQ(lhs, rhs) \
    jac::CHECK_EQ_IMPL(lhs, rhs, #lhs, #rhs, std::source_location::current())

