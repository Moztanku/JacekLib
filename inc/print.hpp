#pragma once

#include <source_location>
#include <string>


namespace jac {
    constexpr void print(const std::string& message, 
        const std::source_location& location = std::source_location::current());

    constexpr void print_error(const std::string& message, 
        const std::source_location& location = std::source_location::current());

    constexpr void print_warning(const std::string& message, 
        const std::source_location& location = std::source_location::current());

    constexpr void print_info(const std::string& message,
        const std::source_location& location = std::source_location::current());

    constexpr void print_debug(
        [[maybe_unused]] const std::string& message,
        [[maybe_unused]] const std::source_location& location = std::source_location::current());
}   // namespace jac