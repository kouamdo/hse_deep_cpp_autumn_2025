#ifndef TOKENPARSER_HPP
#define TOKENPARSER_HPP

#include <string>
#include <functional>
#include <cstdint>

class TokenParser
{
    private:

        bool isAllDigits(const std::string& token);
        std::function<void()> startCallback_;
        std::function<void()> endCallback_;
        std::function<void(uint64_t)> digitTokenCallback_;
        std::function<void(const std::string&)> stringTokenCallback_;

    public:
        TokenParser() = default;
        void Parse(const std::string& line);
        void SetStartCallback(std::function<void()> cb) { startCallback_ = std::move(cb); }
        void SetEndCallback(std::function<void()> cb) { endCallback_ = std::move(cb); }
        void SetDigitTokenCallback(std::function<void(uint64_t)> cb) { digitTokenCallback_ = std::move(cb); }
        void SetStringTokenCallback(std::function<void(const std::string&)> cb) { stringTokenCallback_ = std::move(cb); }

        ~TokenParser();
};

TokenParser::~TokenParser(){}
#endif