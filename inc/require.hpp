#pragma once

#include <source_location>
#include <format>

#include <ansi.hpp>
#include <print.hpp>
#include <debug.hpp>

namespace jac {

    #define REQUIRE(condition) \
        REQUIRE_IMPL(condition, #condition, std::source_location::current())

    void REQUIRE_IMPL(bool condition_value, 
        const char* condition_text,
        const std::source_location& location)
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);
        if (!condition_value) {
            print_error(
                std::format("Require \"{}{}{}\" failed", style, condition_text, ANSI_EC::reset),
                location
            );
            throw std::runtime_error("Require failed!");
        }
    }

    #define REQUIRE_EQ(lhs, rhs) \
        REQUIRE_EQ_IMPL(lhs, rhs, #lhs, #rhs, std::source_location::current())

    template<typename T, typename U>
    void REQUIRE_EQ_IMPL(const T& lhs, const U& rhs,
        const char* lhs_text, const char* rhs_text,
        const std::source_location& location)
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);
        if (lhs != rhs) {
            print_error(
                std::format("RequireEQ \"{}{}{}\" == \"{}{}{}\" failed", style, lhs_text, ANSI_EC::reset, style, rhs_text, ANSI_EC::reset),
                location
            );
            throw std::runtime_error("Require failed!");
        }
    }

}   // namespace jac