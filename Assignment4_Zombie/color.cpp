#include <iostream>
#include <termcolor/termcolor.hpp>

int main(int /*argc*/, char** /*argv*/)
{
    std::cout << termcolor::red << "Hello, ";                   // 16 colors
    std::cout << termcolor::color<100> << "Colorful ";          // 256 colors
    std::cout << termcolor::color<211, 54, 130> << "World!";    // true colors
    std::cout << std::endl;
    return 0;
}