cmake_minimum_required(VERSION 3.16.3)

project(JacekLib)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE JacekLib_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")

add_library(JacekLib STATIC ${JacekLib_SOURCES})
target_include_directories(JacekLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")

target_compile_options(JacekLib PRIVATE -Wall -Wextra -pedantic -Werror -O3 -Wno-unused-parameter -Wno-sign-compare)

file(GLOB_RECURSE JacekLibTest_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tst/**.cpp")
