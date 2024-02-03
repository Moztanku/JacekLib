#pragma once

#include "jac/type_defs.hpp"

namespace jac {
    void seed(uint seed) noexcept;

    template <typename T>
    T random(T min, T max) noexcept;

    float randomFloat(float min, float max) noexcept;
    float randomFloat(float max) noexcept;
    float randomFloat() noexcept;

    double randomDouble(double min, double max) noexcept;
    double randomDouble(double max) noexcept;
    double randomDouble() noexcept;

    int randomInt(int min, int max) noexcept;
    int randomInt(int max) noexcept;
    int randomInt() noexcept;

    std::string randomString(size_t length) noexcept;
}   // namespace jac
