#pragma once

#include <sstream>
#include <string_view>
#include <iostream>

#define TO_STRING(x) #x

namespace jac {
    // Author: https://stackoverflow.com/users/11638718/康桓瑋
    // Source: https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
    template <typename T>
    constexpr auto type_name() {
      std::string_view name, prefix, suffix;
    #ifdef __clang__
      name = __PRETTY_FUNCTION__;
      prefix = "auto jac::type_name() [T = ";
      suffix = "]";
    #elif defined(__GNUC__)
      name = __PRETTY_FUNCTION__;
      prefix = "constexpr auto jac::type_name() [with T = ";
      suffix = "]";
    #elif defined(_MSC_VER)
      name = __FUNCSIG__;
      prefix = "auto __cdecl jac::type_name<";
      suffix = ">(void)";
    #endif
      name.remove_prefix(prefix.size());
      name.remove_suffix(suffix.size());
      return name;
    }

    template<typename T>
    constexpr auto type_name(const T& /*unused*/) {
        return type_name<T>();
    }

    template <std::ostream& stream = std::cout>
    class StreamCapturer {
        public:
            ~StreamCapturer(){
                stream.rdbuf(old);
            }

            std::string read(){
                std::string output = ss.str();
                ss.str(std::string());

                return output;
            }

            std::string readLine(){
                std::string output;
                std::getline(ss, output);

                return output;
            }

        private:
            std::stringstream ss;
            std::streambuf* old = stream.rdbuf(ss.rdbuf());
    };
}   // namespace jac
