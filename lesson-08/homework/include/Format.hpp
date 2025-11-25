#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <tuple>
#include <sstream>
#include <stdexcept>
#include <string>

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

        template<template T>
        std::string argToSrtring(const T& value) const
        {
            std::stringstream ss ; 

            ss << value ;

            return ss.str();
        }

        template<std::size_t Index>
        std::string getArgByIndex() const {
            if constexpr (Index >= sizeof...(Args))
                throw std::out_of_range("Indice argument hors limites");
            else
                return argToString(std::get<Index>(args));
        }

        std::string getArg(std::size_t index) const {
        // On doit dispatcher l’index à la bonne surcharge getArgByIndex
        // Comme std::get requiert un index en constexpr, ici une implémentation simple :
            switch (index) {
                #define CASE(i) case i: return getArgByIndex<i>();
                CASE(0)
                CASE(1)
                CASE(2)
                CASE(3)
                CASE(4)
                // Ajouter autant de cases que le nombre maximum d’arguments attendus
                #undef CASE
                default: throw std::out_of_range("Argument index hors limites");
            }
        }
        
        
        Format(const std::string& fmt, Args&&... arguments)
        : format_str(fmt),
          args(std::forward<Args>(arguments)...) {}

        Format();

        void parse();

        std::string str();

        ~Format();
};

#endif