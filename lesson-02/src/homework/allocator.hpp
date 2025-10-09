#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cstddef>

class Allocator
{
private:
    char *data;  //Указатель на начало выделенной памяти
    size_t max_size;   //малсимальный размер памяти
    size_t offset;  //  сбрасываем смещение

public:
    Allocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};

#endif // ALLOCATOR_HPP