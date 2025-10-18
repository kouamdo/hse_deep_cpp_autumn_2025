#include <iostream>

class IDevice
{
public:
    virtual void print(const std::string& message)
    {
        std::cout << "Device: [" << message << "]" << std::endl;
    }
    virtual void open() = 0;
    virtual void close() = 0;
};

class Printer : public IDevice
{
public:
    void print(const std::string& message) override
    {
        std::cout << "Printer: [" << message << "]" << std::endl;
    }

    void open() override {}
    void close() override {}

    ~Printer()
    {
        std::cout << "~Printer()" << std::endl;
    }
};

class Console : public IDevice
{
public:
    void print(const std::string& message) override
    {
        std::cout << "Console: [" << message << "]" << std::endl;
    }

    void open() override {}
    void close() override {}

    ~Console()
    {
        std::cout << "~Console()" << std::endl;
        delete fd;
    }
    int* fd;
};

IDevice* GetDevice(const std::string device_name)
{
    if (device_name == "printer") {
        return new Printer{};
    } else if (device_name == "console") {
        return new Console{};
    }
    return nullptr;
}

void process(IDevice* device)
{
    device->open();
    //...
    device->print("Hello, kitty");
    //...
    device->close();
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " [console|printer]" << std::endl;
        return 1;
    }
    std::string device_name{argv[1]};
    IDevice* device = GetDevice(device_name);
    process(device);
    delete device;
}
