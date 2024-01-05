#pragma once

#include <source_location>
#include <format>

#include <ansi.hpp>
#include <print.hpp>
#include <debug.hpp>
#include <utils.hpp>

namespace jac {
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

    template<typename T>
    void REQUIRE_EQ_IMPL(const T& lhs, const T& rhs,
        const char* lhs_text, const char* rhs_text,
        const std::source_location& location)
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);
        if (lhs != rhs) {
            print_error(
                std::format("RequireEQ \"{0}{2}{1}\" == \"{0}{3}{1}\" failed", style, ANSI_EC::reset, lhs_text, rhs_text),
                location
            );
            throw std::runtime_error("Require failed!");
        }
    }

    template<typename T, typename U>
    void REQUIRE_EQ_IMPL(const T& lhs, const U& rhs,
        const char* lhs_text, const char* rhs_text,
        const std::source_location& location)
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);
        if (lhs != rhs) {
            print_error(
                std::format("RequireEQ \"{0}{2}{1}\" == \"{0}{3}{1}\" failed, different types {4} and {5}",
                style, ANSI_EC::reset, lhs_text,  rhs_text, jac::type_name<T>(), jac::type_name<U>()),
                location
            );
            throw std::runtime_error("Require failed!");
        }
    }
}   // namespace jac

#define JAC_REQUIRE(condition) \
    jac::REQUIRE_IMPL(condition, #condition, std::source_location::current())


#define JAC_REQUIRE_EQ(lhs, rhs) \
    REQUIRE_EQ_IMPL(lhs, rhs, #lhs, #rhs, std::source_location::current())