#include <iostream>
#include <sstream>
#include <string>
#include <charconv>
#include <system_error>
#include <cctype>
#include "include/TokenParser.hpp"

int main() {
    TokenParser parser;

    parser.SetStartCallback([]() {
        std::cout << "Start of parsing\n";
    });

    parser.SetEndCallback([]() {
        std::cout << "End of parsing\n";
    });

    parser.SetDigitTokenCallback([](uint64_t value) {
        std::cout << "Number detected : " << value << "\n";
    });

    parser.SetStringTokenCallback([](const std::string& token) {
        std::cout << "Word detected : " << token << "\n";
    });

    std::string ligne = "123 chat 999999999999999999999999 abc 456";
    parser.Parse(ligne);

    return 0;
}