#include "jac/main_impl.hpp"

#include <iostream>

#include "jac/type_defs.hpp"

namespace {
    constexpr std::string invalid = "";
    constexpr std::string executable = "program";
    constexpr std::string default_arg = "true";
}

namespace jac {
    const std::string_view Arguments::operator[](const std::string_view key) const
    {
        const auto it = args.find(key);

        if (it == args.end())
            return invalid;

        return it->second;
    }

    const std::string_view Arguments::operator[](const size_t index) const
    {
        if (index >= args.size())
            return invalid;

        auto it = args.begin();
        std::advance(it, index);

        return it->second;
    }

    Arguments::const_iterator Arguments::begin() const
    {
        return args.begin();
    }

    Arguments::const_iterator Arguments::end() const
    {
        return args.end();
    }

    size_t Arguments::size() const
    {
        return args.size();
    }

    int main(int argc, char** argv, char** envp)
    {
        std::map<std::string_view, std::string_view> arg;
        arg[executable] = argv[0];

        for (idx i = 1; i < argc; i++)
        {
            std::string_view argument = argv[i];

            if (argument.starts_with("--"))
            {
                argument.remove_prefix(2);
                auto pos = argument.find('=');

                if (pos == std::string_view::npos)
                {
                    std::cerr << "Missing '=' in argument " << argument << "\n";
                    continue;
                }

                std::string_view key = argument.substr(0, pos);
                std::string_view value = argument.substr(pos + 1);

                arg[key] = value;
            }
            else if (argument.starts_with("-"))
            {
                argument.remove_prefix(1);

                if (i + 1 >= argc || argv[i + 1][0] == '-')
                {
                    std::string_view key = argument;
                    std::string_view value = default_arg;

                    arg[key] = value;
                } else {
                    std::string_view key = argument;
                    std::string_view value = argv[i + 1];

                    arg[key] = value;
                    i++;
                }
            }
            else
            {
                std::cerr << "Only arguments of the form \"--arg=value\" or \"-a value\" are supported\n";
            }
        }

        std::map <std::string_view, std::string_view> env;

        for (idx i = 0; envp[i] != nullptr; i++)
        {
            std::string_view argument = envp[i];

            auto pos = argument.find('=');

            if (pos == std::string_view::npos)
            {
                std::cerr << "Missing '=' in argument " << argument << "\n";
                continue;
            }

            std::string_view key = argument.substr(0, pos);
            std::string_view value = argument.substr(pos + 1);

            env[key] = value;
        }

        return run(
            reinterpret_cast<Arguments&>(arg),
            reinterpret_cast<Arguments&>(env)
        );
    }
} // namespace jac
