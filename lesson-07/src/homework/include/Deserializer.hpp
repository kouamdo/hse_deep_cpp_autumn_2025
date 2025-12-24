#ifndef DESERIALIZER_HPP
#define DESERIALIZER_HPP

#include "../include/Serializer.hpp"
#include <cstdint>
#include <stdexcept>
#include <iostream>

#pragma once

class Deserializer
{
    static constexpr char Separator = ' ';

    private:
    // process использует variadic templates
        std::istream& in_ ;

        template <class T, class... Args>
        Error process(T& val, Args&... args)
        {
            Error err = load(val);
            if (err != Error::NoError)
                return err;
            return process(args...);
        }

        Error process() { return Error::NoError; }
        

    public:
        explicit Deserializer(std::istream& in) : in_(in)
        {

        }

        template <class T>
        Error load(T& object)
        {
            return object.serialize(*this);
        }

        template <class... ArgsT>
        Error operator()(ArgsT&... args)
        {
            return process(args...);
        }

        Error load() ;
        Error load(bool& value);
        Error load(uint64_t &arg);      
};

#endif

