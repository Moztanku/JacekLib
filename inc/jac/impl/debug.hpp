#pragma once

namespace jac::impl {

#ifndef Release
    constexpr bool Debug = true;
#else
    constexpr bool Debug = false;
#endif

}  // namespace jac::impl