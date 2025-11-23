#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstdint>
#include <stdexcept>
#include <iostream>

#pragma once

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;
};

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';

    private:
    // process использует variadic templates
        std::ostream& out_ ;

    public:
        explicit Serializer(std::ostream& out) : out_(out)
        {

        }

        template <class T>
        Error save(T& object)
        {
            return object.serialize(*this);
        }

        template <class... ArgsT>
        Error operator()(ArgsT... args)
        {
            return process(args...);
        }

        Error process(bool &&arg);
        Error process(uint64_t &&arg);
};

#endif
