#include "../include/Serializer.hpp"
#include <string>
#include <sstream>

Error Serializer::process(bool &&arg)
{
    this->out_ << ((arg == true) ? "true " : "false ") 
        << Serializer::Separator ;

    return Error::NoError ;
}

Error Serializer::process(uint64_t &&arg)
{
    this->out_ << arg << Serializer::Separator ;

    return Error::NoError;
}