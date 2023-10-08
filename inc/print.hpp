#pragma once

#include <source_location>
#include <string>

namespace jac {

    void print(const std::string& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_error(const std::string& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_warning(const std::string& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_info(const std::string& message,
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_debug(const std::string& message,
        const std::source_location& location = std::source_location::current()) noexcept;

}   // namespace jac