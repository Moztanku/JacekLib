#include "jac/print.hpp"

#include <format>
#include <iostream>

#include "jac/ansi.hpp"
#include "jac/debug.hpp"

namespace jac {
    void print(const Message_List& messages, 
        const std::source_location& location) noexcept
    {
        std::cout << std::format(
            "{}{}@ {}:{}{}\n", messages.to_string(), ANSI_EC::Style::dim, location.file_name(), location.line(), ANSI_EC::reset
        );
    }

    void print_error(Message_List&& messages, 
        const std::source_location& location) noexcept
    {
        const std::string prefix = std::format("{}[ERROR]{}", ANSI_EC::FG::red, ANSI_EC::reset);
        messages.prepend(prefix);

        print(messages, location);
    }

    void print_warning(Message_List&& messages, 
        const std::source_location& location) noexcept
    {
        const std::string prefix = std::format("{}[WARNING]{}", ANSI_EC::FG::yellow, ANSI_EC::reset);
        messages.prepend(prefix);

        print(messages, location);
    }

    void print_info(Message_List&& messages,
        const std::source_location& location) noexcept
    {
        const std::string prefix = std::format("{}[INFO]{}", ANSI_EC::FG::cyan, ANSI_EC::reset);
        messages.prepend(prefix);

        print(std::move(messages), location);
    }

    void print_debug(Message_List&& messages,
        const std::source_location& location) noexcept
    {
        if constexpr(Debug == false)
            return;

        const std::string prefix = std::format("{}[DEBUG]{}", ANSI_EC::FG::magenta, ANSI_EC::reset);
        messages.prepend(prefix);

        print(std::move(messages), location);
    }

}   // namespace jac
