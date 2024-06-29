#pragma once

#include <source_location>
#include <vector>
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

    struct Message_List {
        template <typename... Args>
        Message_List(const Args... args) {
            messages = {to_message(args)...};
        }

        void prepend(const Message& message) {
            messages.insert(messages.begin(), message);
        }

        std::string to_string() const {
            std::string str;
            for(const auto& message : messages) {
                str += message + " ";
            }
            return str;
        }

        std::vector<Message> messages;
    };

    void print(const Message_List& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_error(Message_List&& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_warning(Message_List&& message, 
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_info(Message_List&& message,
        const std::source_location& location = std::source_location::current()) noexcept;

    void print_debug(Message_List&& message,
        const std::source_location& location = std::source_location::current()) noexcept;
}   // namespace jac
