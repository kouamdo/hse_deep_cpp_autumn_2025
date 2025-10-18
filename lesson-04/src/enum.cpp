#include <iostream>
#include <string>
#include <vector>

enum class NodeColor
{
    RED,
    BLACK,
    UNKNOWN
};


namespace CatColor {
enum CatColor
{
    WHITE,
    BLACK,
    COFFEE,
    UNKNOWN
};
}

enum class HttpCode
{
    Ok = 200,
    NotFound = 404,
    InternalServerError = 500,
    ImTeaPot = 418
};

// Google Protobuf

union Jack
{
    double a;
    int b;
    bool c;
};

union RGB
{
    uint32_t code; // 0xFFBBCC00
    struct {
        //uint8_t r, g, b, a;
        uint8_t a;
        uint8_t g;
        uint8_t b;
        uint8_t r;
    } rgba;
};

int main()
{
    const std::vector<std::string> colors = {"red", "black", "purple"};
    std::string shlepa_color = colors[0];
    HttpCode code = HttpCode::ImTeaPot;
    NodeColor node_color = NodeColor::RED;
    CatColor::CatColor cat_color = CatColor::COFFEE;
    std::cout << static_cast<int32_t>(code) << std::endl;

    Jack tmp;
    tmp.b = 100500;
    std::cout << std::boolalpha << tmp.c << std::endl;
    tmp.a = 0;
    std::cout << std::boolalpha << tmp.c << std::endl;

    RGB c;
    c.code = 0xFFAA0900;
    std::cout << static_cast<int>(c.rgba.r) << " " << static_cast<int>(c.rgba.g) << " " << static_cast<int>(c.rgba.b) << " " << static_cast<int>(c.rgba.a) << std::endl;
}
