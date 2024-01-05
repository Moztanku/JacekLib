#include "jac/print.hpp"

#include <format>
#include <iostream>

#include "jac/ansi.hpp"
#include "jac/debug.hpp"

namespace jac {
    void print(const std::string& message, 
        const std::source_location& location) noexcept
    {
        std::cout << std::format(
            "{} {}@ {}:{}{}\n", message, ANSI_EC::Style::dim, location.file_name(), location.line(), ANSI_EC::reset
        );
    }

    void print_error(const std::string& message, 
        const std::source_location& location) noexcept
    {
        print(
            std::format("{}[ERROR]{} {}", ANSI_EC::FG::red, ANSI_EC::reset, message),
            location
        );
    }

    void print_warning(const std::string& message, 
        const std::source_location& location) noexcept
    {
        print(
            std::format("{}[WARNING]{} {}", ANSI_EC::FG::additional::orange, ANSI_EC::reset, message),
            location
        );
    }

    void print_info(const std::string& message,
        const std::source_location& location) noexcept
    {
        print(
            std::format("{}[INFO]{} {}", ANSI_EC::FG::cyan, ANSI_EC::reset, message),
            location
        );
    }

    void print_debug(const std::string& message,
        const std::source_location& location) noexcept
    {
        if(Debug)
            print(
                std::format("{}[DEBUG]{} {}", ANSI_EC::FG::magenta, ANSI_EC::reset, message),
                location
            );
    }

}   // namespace jac