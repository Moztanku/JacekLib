#pragma once

#include <source_location>
#include <format>

namespace jac {

    #define REQUIRE(condition) \
        REQUIRE_IMPL(condition, #condition, std::source_location::current())

    constexpr void REQUIRE_IMPL(bool condition_value, 
        const char* condition_text,
        const std::source_location& location);

}   // namespace jac