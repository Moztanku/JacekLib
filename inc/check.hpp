#pragma once

#include <source_location>
#include <format>

namespace jac {

    #define CHECK(condition) \
        CHECK_IMPL(condition, #condition, std::source_location::current())

    constexpr void CHECK_IMPL(bool condition_value, const char* condition_text, const std::source_location& location) {
        if (DEBUG && !condition_value) {
            print_warning(
                std::format("Check \"{}{}{}\" failed", ANSI_EC::FG::yellow, condition_text, ANSI_EC::reset),
                location
            );
        }
    }

}   // namespace jac