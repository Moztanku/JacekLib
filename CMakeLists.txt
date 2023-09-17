cmake_minimum_required(VERSION 3.27.5)

set(CMAKE_CXX_STANDARD 23)

project(JacekLib)

add_library(JacekLib)
target_include_directories(JacekLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc/")

file(GLOB_RECURSE JacekLib_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
target_sources(JacekLib PRIVATE ${JacekLib_SOURCES})
