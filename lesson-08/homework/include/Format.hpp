#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <cstdint>
#include <stdexcept>
#include <iostream>

#pragma once

template<typename... Args>
class Format
{
    private:
        /* data */
        std::string format_str;
        std::tuple<Args...> args;
        std::stringstream result_stream;

    public:

        
        Format(const std::string& fmt, Args&&... arguments)
        : format_str(fmt),
          args(std::forward<Args>(arguments)...) {}

        Format();

        void parse();

        std::string str();

        ~Format();
};

#endif