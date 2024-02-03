#pragma once

#include <source_location>
#include <string>

namespace jac {
    typedef std::string Message;

    template <typename T>
    Message to_message(const T& t)
    {
        if constexpr (std::is_same<T, Message>::value)
            return t;
        else if constexpr (std::is_same<T, char>::value)
            return std::string(1, t);
        else if constexpr (std::is_arithmetic<T>::value)
            return std::to_string(t);
        else
            return std::string(t);
    }
    
    template <typename ...Arg>
    Message make_message(const Arg& ...args)
    {
        return (Message{} + ... + to_message(args));
    }

    void print(const Message& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_error(const Message& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_warning(const Message& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_info(const Message& message,
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_debug(const Message& message,
        const std::source_location& location = std::source_location::current()) noexcept;
}   // namespace jac
