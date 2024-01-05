#pragma once

#ifndef Release
    constexpr bool Debug = true;
#else
    constexpr bool Debug = false;
#endif