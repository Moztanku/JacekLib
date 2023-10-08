#pragma once

#include <format>
#include <initializer_list>
#include <string_view>
#include <cstring>

namespace jac {
    struct ANSI_EC {
        static constexpr auto reset = "\033[0m";

        static inline auto concat(const char* l) noexcept {
            return std::format("{}", l);
        }

        template<typename... Args>
        static inline auto concat(const char* l, Args... args) noexcept {
            return std::format("{}{}", l, concat(args...));
        }

        struct Style {
            static constexpr auto bold = "\033[1m";
            static constexpr auto dim = "\033[2m";
            static constexpr auto italic = "\033[3m";
            static constexpr auto underline = "\033[4m";
            static constexpr auto blink = "\033[5m";
            static constexpr auto reverse = "\033[7m";
            static constexpr auto hidden = "\033[8m";
        };

        struct FG {
            // 4-bit colors
            static constexpr auto black = "\033[30m";
            static constexpr auto red = "\033[31m";
            static constexpr auto green = "\033[32m";
            static constexpr auto yellow = "\033[33m";
            static constexpr auto blue = "\033[34m";
            static constexpr auto magenta = "\033[35m";
            static constexpr auto cyan = "\033[36m";
            static constexpr auto white = "\033[37m";
            // 4-bit colors (bright)
            struct bright {
                static constexpr auto black = "\033[90m";
                static constexpr auto red = "\033[91m";
                static constexpr auto green = "\033[92m";
                static constexpr auto yellow = "\033[93m";
                static constexpr auto blue = "\033[94m";
                static constexpr auto magenta = "\033[95m";
                static constexpr auto cyan = "\033[96m";
                static constexpr auto white = "\033[97m";
            };
            // 8-bit colors
            struct high_intensity {
                static constexpr auto black = "\033[38;5;8m";
                static constexpr auto red = "\033[38;5;9m";
                static constexpr auto green = "\033[38;5;10m";
                static constexpr auto yellow = "\033[38;5;11m";
                static constexpr auto blue = "\033[38;5;12m";
                static constexpr auto magenta = "\033[38;5;13m";
                static constexpr auto cyan = "\033[38;5;14m";
                static constexpr auto white = "\033[38;5;15m";
            };
            struct additional {
                static constexpr auto orange = "\033[38;5;208m";
                static constexpr auto purple = "\033[38;5;129m";
                static constexpr auto pink = "\033[38;5;205m";
                static constexpr auto brown = "\033[38;5;130m";
                static constexpr auto gray = "\033[38;5;240m";
                static constexpr auto lime = "\033[38;5;118m";
                static constexpr auto teal = "\033[38;5;30m";
                static constexpr auto olive = "\033[38;5;142m";
                static constexpr auto navy = "\033[38;5;18m";
                static constexpr auto maroon = "\033[38;5;52m";
                static constexpr auto gold = "\033[38;5;214m";
                static constexpr auto silver = "\033[38;5;188m";
            };

            static constexpr auto rgb(u_char r, u_char g, u_char b) noexcept {
                return std::format("\033[38;2;{};{};{}m", r, g, b);
            }
        };

        struct BG {
            // 4-bit colors
            static constexpr auto black = "\033[40m";
            static constexpr auto red = "\033[41m";
            static constexpr auto green = "\033[42m";
            static constexpr auto yellow = "\033[43m";
            static constexpr auto blue = "\033[44m";
            static constexpr auto magenta = "\033[45m";
            static constexpr auto cyan = "\033[46m";
            static constexpr auto white = "\033[47m";
            // 4-bit colors (bright)
            struct bright {
                static constexpr auto black = "\033[100m";
                static constexpr auto red = "\033[101m";
                static constexpr auto green = "\033[102m";
                static constexpr auto yellow = "\033[103m";
                static constexpr auto blue = "\033[104m";
                static constexpr auto magenta = "\033[105m";
                static constexpr auto cyan = "\033[106m";
                static constexpr auto white = "\033[107m";
            };
            // 8-bit colors
            struct high_intensity {
                static constexpr auto black = "\033[48;5;8m";
                static constexpr auto red = "\033[48;5;9m";
                static constexpr auto green = "\033[48;5;10m";
                static constexpr auto yellow = "\033[48;5;11m";
                static constexpr auto blue = "\033[48;5;12m";
                static constexpr auto magenta = "\033[48;5;13m";
                static constexpr auto cyan = "\033[48;5;14m";
                static constexpr auto white = "\033[48;5;15m";
            };
            struct additional {
                static constexpr auto orange = "\033[48;5;208m";
                static constexpr auto purple = "\033[48;5;129m";
                static constexpr auto pink = "\033[48;5;205m";
                static constexpr auto brown = "\033[48;5;130m";
                static constexpr auto gray = "\033[48;5;240m";
                static constexpr auto lime = "\033[48;5;118m";
                static constexpr auto teal = "\033[48;5;30m";
                static constexpr auto olive = "\033[48;5;142m";
                static constexpr auto navy = "\033[48;5;18m";
                static constexpr auto maroon = "\033[48;5;52m";
                static constexpr auto gold = "\033[48;5;214m";
                static constexpr auto silver = "\033[48;5;188m";
            };

            static constexpr auto rgb(u_char r, u_char g, u_char b) noexcept {
                return std::format("\033[48;2;{};{};{}m", r, g, b);
            }
        };
    };
}   // namespace jac