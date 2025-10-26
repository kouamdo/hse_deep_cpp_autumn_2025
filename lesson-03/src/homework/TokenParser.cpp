#include <string>
#include <functional>
#include <iostream>
#include <charconv>
#include <sstream>
#include <cstdint>
#include <cctype>

class TokenParser
{
    public:

        TokenParser() = default;

        // Устанавливаем callback-функцию перед стартом парсинга.
        void SetStartCallback(std::function<void()> cb) { startCallback_ = std::move(cb); }

        // Устанавливаем callback-функцию после окончания парсинга.
        void SetEndCallback(std::function<void()> cb) { endCallback_ = std::move(cb); }

        // Устанавливаем callback-функцию для обработки чисел.
        void SetDigitTokenCallback(std::function<void(uint64_t)> cb) { digitTokenCallback_ = std::move(cb); }

        void SetStringTokenCallback(std::function<void(const std::string&)> cb) { stringTokenCallback_ = std::move(cb); }

        // Тут другие методы для установки callback-функций.
        //...
        void Parse(const std::string& line) {
            if (startCallback_) startCallback_();

            std::istringstream iss(line);
            std::string token;
            while (iss >> token) {
                if (isAllDigits(token)) {
                    uint64_t value = 0;
                    auto result = std::from_chars(token.data(), token.data() + token.size(), value);
                    if (result.ec == std::errc() && result.ptr == token.data() + token.size()) {
                        if (digitTokenCallback_) digitTokenCallback_(value);
                        continue;
                    }
                }
                if (stringTokenCallback_) stringTokenCallback_(token);
            }

            if (endCallback_) endCallback_();
        }

    private:

        bool isAllDigits(const std::string& token) {
            for (char c : token) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    return false;
                }
            }
            return !token.empty();
        }
    
        std::function<void()> startCallback_;
        std::function<void()> endCallback_;
        std::function<void(uint64_t)> digitTokenCallback_;
        std::function<void(const std::string&)> stringTokenCallback_;
};