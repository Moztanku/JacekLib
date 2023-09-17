#include <print.hpp>

#include <iostream>
#include <format>
#include <source_location>
#include <string>

#include <debug.hpp>
#include <ansi.hpp>

namespace jac {
    constexpr void print(const std::string& message, 
        const std::source_location& location)
    {
        std::cout << std::format(
            "{} {}@ {}:{}{}\n", message, ANSI_EC::Style::dim, location.file_name(), location.line(), ANSI_EC::reset
        );
    }

    constexpr void print_error(const std::string& message, 
        const std::source_location& location) 
    {
        print(
            std::format("{}[ERROR]{} {}", ANSI_EC::FG::red, ANSI_EC::reset, message),
            location
        );
    }

    constexpr void print_warning(const std::string& message, 
        const std::source_location& location) 
    {
        print(
            std::format("{}[WARNING]{} {}", ANSI_EC::FG::orange, ANSI_EC::reset, message),
            location
        );
    }

    constexpr void print_info(const std::string& message,
        const std::source_location& location)
    {
        print(
            std::format("{}[INFO]{} {}", ANSI_EC::FG::cyan, ANSI_EC::reset, message),
            location
        );
    }

    constexpr void print_debug(
        [[maybe_unused]] const std::string& message,
        [[maybe_unused]] const std::source_location& location) 
    {
        if(DEBUG)
            print(
                std::format("{}[DEBUG]{} {}", ANSI_EC::FG::magenta, ANSI_EC::reset, message),
                location
            );
    }
}   // namespace jac