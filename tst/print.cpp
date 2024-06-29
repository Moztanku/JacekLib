#include <gtest/gtest.h>

#include "jac/print.hpp"
#include "jac/ansi.hpp"
#include "jac/utils.hpp"

#include <string>
#include <iostream>
#include <format>
#include <source_location>
#include <vector>
#include <type_traits>

auto string_contains(
    const std::string_view str,
    const std::vector<std::string_view>& expected) -> bool
{
    for(const auto& e : expected) {
        if(str.find(e) == std::string::npos)
            return false;
    }

    return true;
}

TEST(Print, expected_output)
{
    jac::StreamCapturer<std::cout> cout_capturer;
    std::string line;

    jac::print("Hello, World!");
    line = cout_capturer.readLine();
    EXPECT_TRUE(
        string_contains(
            line,
            {"Hello, World!"}));

    jac::print_error("Hello, World!");
    line = cout_capturer.readLine();
    EXPECT_TRUE(
        string_contains(
            line,
            {"Hello, World!", "[ERROR]", jac::ANSI_EC::FG::red}));

    jac::print_warning("Hello, World!");
    line = cout_capturer.readLine();
    EXPECT_TRUE(
        string_contains(
            line,
            {"Hello, World!", "[WARNING]", jac::ANSI_EC::FG::yellow}));

    jac::print_info("Hello, World!");
    line = cout_capturer.readLine();
    EXPECT_TRUE(
        string_contains(
            line,
            {"Hello, World!", "[INFO]", jac::ANSI_EC::FG::cyan}));

    jac::print_debug("Hello, World!");
    line = cout_capturer.readLine();
    EXPECT_TRUE(
        string_contains(
            line,
            {"Hello, World!", "[DEBUG]", jac::ANSI_EC::FG::magenta}));

    EXPECT_FALSE(
        string_contains(
            line,
            {"[INFO]"}));
}

TEST(Print, multiple_arguments)
{
    jac::StreamCapturer<std::cout> cout_capturer;
    std::string line;

    jac::print({"Hello", "World!", 42, 3.14});

    line = cout_capturer.readLine();
    EXPECT_TRUE(
        string_contains(
            line,
            {"Hello", "World!", "42", "3.14"}));
}

auto call_from_set_line() -> int
{
    std::source_location location = std::source_location::current();

    jac::print("Hello, World!");

    return location.line() + 2;
}

TEST(Print, source_location)
{
    jac::StreamCapturer<std::cout> cout_capturer;
    std::string line;

    int line_number = call_from_set_line();

    line = cout_capturer.readLine();
    EXPECT_TRUE(
        string_contains(
            line,
            {std::to_string(line_number), "print.cpp"}));
}