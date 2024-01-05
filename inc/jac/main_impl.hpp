#pragma once

#include <map>
#include <string>

namespace jac {
    class Arguments {
            using const_iterator = std::map<std::string_view, std::string_view>::const_iterator;
        public:
            Arguments() = delete;
            Arguments(const Arguments&) = delete;
            Arguments(Arguments&&) = delete;
            ~Arguments() = delete;

            Arguments operator=(const Arguments&) = delete;
            Arguments operator=(Arguments&&) = delete;

            const std::string_view& operator[](const std::string& key) const;

            const_iterator begin() const;
            const_iterator end() const;
            size_t size() const;
        private:
            std::map<std::string_view, std::string_view> args;
    };

    int main(int argc, char** argv, char** envp);
} // namespace jac

int run(jac::Arguments&, jac::Arguments&);
