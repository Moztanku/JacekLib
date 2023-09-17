#pragma once

namespace jac {
    struct ANSI_EC {
        static constexpr auto reset = "\033[0m";
        
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
            // 8-bit colors
            static constexpr auto black = "\033[30m";
            static constexpr auto red = "\033[31m";
            static constexpr auto green = "\033[32m";
            static constexpr auto yellow = "\033[33m";
            static constexpr auto blue = "\033[34m";
            static constexpr auto magenta = "\033[35m";
            static constexpr auto cyan = "\033[36m";
            static constexpr auto white = "\033[37m";
            // additional colors
            static constexpr auto orange = "\033[38;5;208m";
        };

        struct BG {
            // 8-bit colors
            static constexpr auto black = "\033[40m";
            static constexpr auto red = "\033[41m";
            static constexpr auto green = "\033[42m";
            static constexpr auto yellow = "\033[43m";
            static constexpr auto blue = "\033[44m";
            static constexpr auto magenta = "\033[45m";
            static constexpr auto cyan = "\033[46m";
            static constexpr auto white = "\033[47m";
            // additional colors
            static constexpr auto orange = "\033[48;5;208m";
        };
    };
}   // namespace jac