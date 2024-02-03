#include "jac/random.hpp"

#include <random>
#include <algorithm>
#include <type_traits>

namespace {
    std::random_device rd;
    std::mt19937 gen(rd());
}   // namespace

namespace jac {
    void seed(uint seed) noexcept
    {
        gen.seed(seed);
    }

    template <typename T>
    T random(T min, T max) noexcept
    {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

        if constexpr (std::is_floating_point<T>::value)
        {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(gen);
        }
        else if constexpr (std::is_integral<T>::value)
        {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(gen);
        }

        return T{};
    }

    float randomFloat(float min, float max) noexcept
    {
        return random(min, max);
    }

    float randomFloat(float max) noexcept
    {
        return random(0.0f, max);
    }

    float randomFloat() noexcept
    {
        return random(0.0f, 1.0f);
    }

    double randomDouble(double min, double max) noexcept
    {
        return random(min, max);
    }

    double randomDouble(double max) noexcept
    {
        return random(0.0, max);
    }

    double randomDouble() noexcept
    {
        return random(0.0, 1.0);
    }

    int randomInt(int min, int max) noexcept
    {
        return random(min, max);
    }

    int randomInt(int max) noexcept
    {
        return random(0, max);
    }

    int randomInt() noexcept
    {
        return random(0, std::numeric_limits<int>::max());
    }

    std::string randomString(size_t length) noexcept
    {
        std::string str;
        str.reserve(length);

        constexpr char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        constexpr size_t charset_size = sizeof(charset) - 1;

        for (size_t _ = 0; _ < length; _++)
            str += charset[randomInt(charset_size)];

        return str;
    }
}   // namespace jac

template float32 jac::random<float32>(float32, float32) noexcept;
template float64 jac::random<float64>(float64, float64) noexcept;

template int8 jac::random<int8>(int8, int8) noexcept;
template int16 jac::random<int16>(int16, int16) noexcept;
template int32 jac::random<int32>(int32, int32) noexcept;
template int64 jac::random<int64>(int64, int64) noexcept;
template int128 jac::random<int128>(int128, int128) noexcept;

template uint8 jac::random<uint8>(uint8, uint8) noexcept;
template uint16 jac::random<uint16>(uint16, uint16) noexcept;
template uint32 jac::random<uint32>(uint32, uint32) noexcept;
template uint64 jac::random<uint64>(uint64, uint64) noexcept;
template uint128 jac::random<uint128>(uint128, uint128) noexcept;

// template bool jac::random<bool>(bool, bool) noexcept;
