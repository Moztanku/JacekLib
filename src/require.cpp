#include <require.hpp>

#include <ansi.hpp>
#include <print.hpp>

namespace jac {
    constexpr void REQUIRE_IMPL(bool condition_value, 
        const char* condition_text, 
        const std::source_location& location)
    {
        if (!condition_value) {
            print_error(
                std::format("Require \"{}{}{}\" failed", ANSI_EC::FG::yellow, condition_text, ANSI_EC::reset),
                location
            );
            throw std::runtime_error("Require failed!");
        }
    }
}