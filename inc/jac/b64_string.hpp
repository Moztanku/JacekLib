#pragma once

#include <string>

#include "jac/type_defs.hpp"

namespace jac {
    class B64String
    {
        public:
            B64String() = default;
            ~B64String() = default;

            B64String(const std::string& str)
            {

            }
        private:
            size_t m_capacity;
            size_t m_size;
    };
}   // namespace jac