#include "jac/type_defs.hpp"
#include "jac/utils.hpp"
#include "jac/main.hpp"
#include "jac/random.hpp"
#include "jac/print.hpp"
#include "jac/check.hpp"
#include "jac/require.hpp"
#include "jac/data_ptr.hpp"

#include <iostream>
#include <format>
#include <source_location>
#include <functional>

using PrintFun = std::function<void(const std::string&, const std::source_location&)>;

void TestPrintFun(PrintFun fun, const std::string& prefix, const std::string& message)
{
    std::string location_file = std::source_location::current().file_name();
    uint location_line;

    std::string actual = "";
    {
        jac::StreamCapturer<std::cout> capturer;

        fun(message, std::source_location::current());
        location_line = std::source_location::current().line() - 1;

        actual = capturer.read();
    }

    std::string expected =
        jac::make_message(
            prefix,
            message,
            " ",
            jac::ANSI_EC::Style::dim,
            "@ ",
            location_file,
            ":",
            location_line,
            jac::ANSI_EC::reset,
            '\n'
        );

    JAC_CHECK_EQ(actual, expected);
}

void TestPrint()
{
    std::array<std::pair<PrintFun, std::string>, 5> prefixes = {
        std::make_pair(jac::print, ""),
        std::make_pair(
            jac::print_error,
            std::format("{}[ERROR]{} ", jac::ANSI_EC::FG::red, jac::ANSI_EC::reset)
        ),
        std::make_pair(
            jac::print_warning,
            std::format("{}[WARNING]{} ", jac::ANSI_EC::FG::additional::orange, jac::ANSI_EC::reset)
        ),
        std::make_pair(
            jac::print_info,
            std::format("{}[INFO]{} ", jac::ANSI_EC::FG::cyan, jac::ANSI_EC::reset)
        ),
        std::make_pair(
            jac::print_debug,
            std::format("{}[DEBUG]{} ", jac::ANSI_EC::FG::magenta, jac::ANSI_EC::reset)
        )
    };

    for (size_t i = 0; i < 50; i++)
    {
        std::string message = jac::randomString(i);

        for (auto& [fun, prefix] : prefixes)
            TestPrintFun(fun, prefix, message);
    }
}

void printDataPtr(const uint64 ptr)
{
    for (idx i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
            std::cout << " ";
        std::cout << ((ptr >> (63 - i)) & 1);
    }
    std::cout << std::endl;
}

int run(jac::Arguments& args, jac::Arguments& env)
{
    const void* ptr = nullptr;
    uint32 data = 0u;
    jac::DataPtr data_ptr(ptr, data);

    // JAC_CHECK_EQ(data_ptr.getPtr(), ptr);
    // JAC_CHECK_EQ(data_ptr.getData(), data);

    ptr = malloc(0);
    data_ptr.setPtr(ptr);

    // JAC_CHECK_EQ(data_ptr.getPtr(), ptr);
    // JAC_CHECK_EQ(data_ptr.getData(), data);

    data = jac::random(0u, static_cast<uint32>(jac::DataPtr::max_data));
    data_ptr.setData(data);

    // JAC_CHECK_EQ(data_ptr.getPtr(), ptr);
    // JAC_CHECK_EQ(data_ptr.getData(), data);

    return 0;
}