
#include <check.hpp>

#include <sstream>
#include <iostream>
#include <string>

#include <type_defs.hpp>

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

#define print_max(x) std::cout << #x << " max = " << std::hex << std::numeric_limits<x>::max() << std::endl;
#define print_min(x) std::cout << #x << " min = " << std::hex << std::numeric_limits<x>::min() << std::endl;

int main() {
    print_max(float16);
    print_max(float32);
    print_max(float64);
    // print_max(float128);

    return 0;
}