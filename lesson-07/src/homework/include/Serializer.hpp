#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstdint>
#include <stdexcept>
#include <iostream>

#pragma once

enum class Error
{
    NoError,
    CorruptedArchive
};

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class SerializerT>
    Error serialize(SerializerT& serializer)
    {
        return serializer(a, b, c);
    }
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
            return process(std::forward<ArgsT>(args)...);
        }

        // variadic dispatcher implemented in-header
        Error process() { return Error::NoError; }

        template <class T, class... Args>
        Error process(T&& val, Args&&... args)
        {
            Error err = process(std::forward<T>(val));
            if (err != Error::NoError)
                return err;
            return process(std::forward<Args>(args)...);
        }

        // overloads for supported types
        Error process(bool arg);
        Error process(uint64_t arg);
};

#endif
