#pragma once

#include <source_location>
#include <format>

#include "jac/ansi.hpp"
#include "jac/print.hpp"
#include "jac/debug.hpp"
#include "jac/utils.hpp"

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

            print_warning(
                std::format("   Values: {0}{2}{1} != {0}{3}{1}", style, ANSI_EC::reset, lhs, rhs),
                location
            );

            throw std::runtime_error("Require failed!");
        }
    }

    template<typename T, typename U>
    void REQUIRE_EQ_IMPL(const T& /*lhs*/, const U& /*rhs*/,
        const char* lhs_text, const char* rhs_text,
        const std::source_location& location)
    {
        const auto style = ANSI_EC::concat(ANSI_EC::FG::yellow, ANSI_EC::Style::bold);
        print_error(
            std::format(
                "RequireEQ \"{0}{2}{1}\" == \"{0}{3}{1}\" failed",
                style, ANSI_EC::reset, lhs_text,  rhs_text
            ), location
        );

        print_error(
            std::format(
                "   Types: {0}{2}{1} != {0}{3}{1}",
                style, ANSI_EC::reset,
                jac::type_name<T>(), jac::type_name<U>()
            ), location
        );

        throw std::runtime_error("Require failed!");
    }
}   // namespace jac

#define JAC_REQUIRE(condition) \
    jac::REQUIRE_IMPL(condition, #condition, std::source_location::current())


#define JAC_REQUIRE_EQ(lhs, rhs) \
    jac::REQUIRE_EQ_IMPL(lhs, rhs, #lhs, #rhs, std::source_location::current())
