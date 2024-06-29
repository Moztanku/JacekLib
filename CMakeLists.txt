cmake_minimum_required(VERSION 3.16.3)

project(JacekLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE JacekLib_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")

add_library(JacekLib STATIC ${JacekLib_SOURCES})

target_include_directories(JacekLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
target_compile_options(JacekLib PRIVATE -Wall -Wextra -pedantic -Werror -O3 -Wno-unused-parameter -Wno-sign-compare)

# Build tests if -DBUILD_TESTING=ON
if(BUILD_TESTING)
    message (STATUS "Building tests")

    # Set up Google Test
    include(FetchContent)
    enable_testing()

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP false)
    FetchContent_MakeAvailable(googletest)

    # Add test executable
    file(GLOB_RECURSE JacekLib_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tst/**.cpp")
    add_executable(JacekLibTests ${JacekLib_TEST_SOURCES})

    target_include_directories(JacekLibTests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc")
    target_link_libraries(JacekLibTests PRIVATE JacekLib gtest_main)

    include(GoogleTest)
    gtest_discover_tests(JacekLibTests)

    add_dependencies(JacekLibTests JacekLib)
endif()
