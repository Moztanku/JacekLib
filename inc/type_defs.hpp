#pragma once

using uchar = unsigned char;

using uint = unsigned int;
using uint8 = __UINT8_TYPE__;   using int8 = __INT8_TYPE__;
using uint16 = __UINT16_TYPE__; using int16 = __INT16_TYPE__;
using uint32 = __UINT32_TYPE__; using int32 = __INT32_TYPE__;
using uint64 = __UINT64_TYPE__; using int64 = __INT64_TYPE__;
using uint128 = __uint128_t;    using int128 = __int128_t;

using czstring = const char*;   using cwstring = const wchar_t*;
using zstring = char*;          using wstring = wchar_t*;

using idx = size_t;

static constexpr uint8 UINT8_MAX = __UINT8_MAX__;
static constexpr uint16 UINT16_MAX = __UINT16_MAX__;
static constexpr uint32 UINT32_MAX = __UINT32_MAX__;
static constexpr uint64 UINT64_MAX = __UINT64_MAX__;
static constexpr uint128 UINT128_MAX = __uint128_t(-1);

static constexpr int8 INT8_MAX = __INT8_MAX__;
static constexpr int16 INT16_MAX = __INT16_MAX__;
static constexpr int32 INT32_MAX = __INT32_MAX__;
static constexpr int64 INT64_MAX = __INT64_MAX__;
static constexpr int128 INT128_MAX = UINT128_MAX >> 1;

static constexpr int8 INT8_MIN = -__INT8_MAX__ - 1;
static constexpr int16 INT16_MIN = -__INT16_MAX__ - 1;
static constexpr int32 INT32_MIN = -__INT32_MAX__ - 1;
static constexpr int64 INT64_MIN = -__INT64_MAX__ - 1;
static constexpr int128 INT128_MIN = -INT128_MAX - 1;

// static constexpr int8 INT8_MIN = ;