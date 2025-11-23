#include "../include/Serializer.hpp"
#include "../include/Deserializer.hpp"
#include <string>
#include <sstream>

template <class T, class... Args>
Error Deserializer::process(T& val, Args&... args)
{
    Error err = load(val);
    if (err != Error::NoError)
        return err;
    return process(args...);
}

Error Deserializer::process()
{
    return Error::NoError;
}

Error Deserializer::load() {
    return Error::NoError;
}

Error Deserializer::load(bool& value)
{
    std::string text;
    in_ >> text;

    if (text == "true")
        value = true;
    else if (text == "false")
        value = false;
    else
        return Error::CorruptedArchive;

    return Error::NoError;
}

Error Deserializer::load(uint64_t &&arg)
{
    std::string text;
    in_ >> text;

    if (text.empty()) 
        return Error::CorruptedArchive;

    try {
        size_t pos;
        uint64_t num = std::stoull(text, &pos);
        if (pos != text.size())
            return Error::CorruptedArchive;
        arg = num;
    }
    catch (...) {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}