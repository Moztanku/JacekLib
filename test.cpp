
#include <check.hpp>

#include <sstream>
#include <iostream>
#include <string>

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

int main() {
    int x = 1;
    int& refX = x;
    int y = 1;

    CHECK_EQ(x, refX);
    CHECK_EQ(x, y);
    CHECK_EQ(refX, y);
    CHECK_EQ(x, 1);
    CHECK_EQ(x, 1u);

    StreamCapturer capturer;

    // std::string output;
    // CHECK(true);

    // if(capturer.read() != "")
    //     std::cerr << "Warning printed" << std::endl;

    // CHECK(false);
    // if(!capturer.read().contains("[WARNING]"))
    //     std::cerr << "Warning not printed" << std::endl;

    // CHECK_EQ_TYPE(NULL, nullptr);
    // if(!capturer.read().contains("[WARNING]"))
    //     std::cerr << "Warning not printed" << std::endl;

    return 0;
}