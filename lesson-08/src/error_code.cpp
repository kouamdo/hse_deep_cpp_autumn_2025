#include <iostream>
#include <system_error>

enum class HttpCode
{
    Ok = 200,
    NotFound = 404,
    InternalServerError = 500,
    Unknown = 0
};

class HttpCategory : public std::error_category
{
public:
    const char* name() const noexcept override
    {
        return "http";
    }

    std::string message(int code) const override
    {
        switch(code)
        {
            case 200:
                return "ok";
            case 404:
                return "not found";
            case 500:
                return "internal server error";
            default:
                return "unknown";
        }
    }
};

std::error_code make_error_code(HttpCode code)
{
    static const HttpCategory instance;
    return std::error_code(static_cast<int>(code), instance);
}

std::error_code fetch(const std::string& str)
{
    // Что-то делаем
    if (str == "yahoo.com")
    {
        return make_error_code( HttpCode::InternalServerError );
    }
    return make_error_code( HttpCode::Ok );
}

[[nodiscard]]
HttpCode download(const std::string& str)
{
    // Что-то делаем
    if (str == "yahoo.com")
    {
        return HttpCode::InternalServerError;
    }
    return HttpCode::Ok;
}

int main()
{
    {
        [[maybe_unused]] HttpCode vk_code = download("vk.com");
    }
    {
        HttpCode yahoo_code = download("yahoo.com");
        if (yahoo_code != HttpCode::Ok)
        {
            std::cerr << "Failed to download url" << std::endl;
        }
    }

    {
        auto code = fetch("yahoo.com");
        if (code)
        {
            std::cerr << code << std::endl;
            std::cerr << code.message() << std::endl;
        }
    }
    {
        auto code = fetch("vk.com");
        if (code)
        {
            std::cerr << code << std::endl;
            std::cerr << code.message() << std::endl;
        }
    }

    return 0;
}

