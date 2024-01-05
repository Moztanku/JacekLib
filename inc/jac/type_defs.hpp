#pragma once

#include <memory>
#include <cstdint>

#ifndef JAC_NO_NUMERIC_ALIASES
// integer types

using uchar = unsigned char;

using uint = unsigned int;
using uint8 = __UINT8_TYPE__;   using int8 = __INT8_TYPE__;
using uint16 = __UINT16_TYPE__; using int16 = __INT16_TYPE__;
using uint32 = __UINT32_TYPE__; using int32 = __INT32_TYPE__;
using uint64 = __UINT64_TYPE__; using int64 = __INT64_TYPE__;
using uint128 = __uint128_t;    using int128 = __int128_t;

using idx = size_t;
using boolean = bool;

// floating point types

using float32 = _Float32;
using float64 = _Float64;

// numeric_limits
// Some are already defined in <limits.h> and <stdint.h>

// static constexpr uint8 UINT8_MAX = __UINT8_MAX__;
// static constexpr uint16 UINT16_MAX = __UINT16_MAX__;
// static constexpr uint32 UINT32_MAX = __UINT32_MAX__;
// static constexpr uint64 UINT64_MAX = __UINT64_MAX__;
static constexpr uint128 UINT128_MAX = __uint128_t(-1);

// static constexpr int8 INT8_MAX = __INT8_MAX__;
// static constexpr int16 INT16_MAX = __INT16_MAX__;
// static constexpr int32 INT32_MAX = __INT32_MAX__;
// static constexpr int64 INT64_MAX = __INT64_MAX__;
static constexpr int128 INT128_MAX = UINT128_MAX >> 1;

// static constexpr int8 INT8_MIN = -__INT8_MAX__ - 1;
// static constexpr int16 INT16_MIN = -__INT16_MAX__ - 1;
// static constexpr int32 INT32_MIN = -__INT32_MAX__ - 1;
// static constexpr int64 INT64_MIN = -__INT64_MAX__ - 1;
static constexpr int128 INT128_MIN = -INT128_MAX - 1;

static constexpr idx IDX_MAX = __SIZE_MAX__;
#endif  // JAC_NO_NUMERIC_ALIASES

#ifndef JAC_NO_PTR_ALIASES
// pointer types

using czstring = const char*;   using cwstring = const wchar_t*;
using zstring = char*;          using wstring = wchar_t*;

using c_string = czstring;      using c_wstring = cwstring;


template<class T> using ptr = T*;
template<typename ...T> using uptr = std::unique_ptr<T...>;
template<typename ...T> using sptr = std::shared_ptr<T...>;
template<typename ...T> using wptr = std::weak_ptr<T...>;

template<typename... T>
constexpr inline auto mk_uptr(T&&... args) -> decltype(std::make_unique<T...>(std::forward<T>(args)...))
{
    return std::make_unique<T...>(std::forward<T>(args)...);
}

template<typename... T>
constexpr inline auto mk_sptr(T&&... args) -> decltype(std::make_shared<T...>(std::forward<T>(args)...))
{
    return std::make_shared<T...>(std::forward<T>(args)...);
}

using void_ptr = void*;

template<class T> using ref = T&;
#endif  // JAC_NO_PTR_ALIASES

#ifndef JAC_NO_STD_ALIASES
// aliases for std

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using std::make_unique;
using std::make_shared;
using std::move;
using std::forward;

#endif  // JAC_NO_STD_ALIASES
