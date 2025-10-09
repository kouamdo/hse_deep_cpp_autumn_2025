#include <cstddef>

class Allocator
{
private:
    char *data = nullptr ;
    size_t max_size = 0 ;
    size_t offset = 0 ;

public:
    Allocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};

Allocator::Allocator(size_t maxSize)
{
    if(this->data != nullptr) delete[] this->data; //сли ранее память была выделена, её необходимо освободить

    this->data = new char [maxSize] ;

    this->max_size = maxSize ;

    this->offset = 0;
}

char * Allocator::alloc(size_t size){

    if (this->max_size - offset > size) {
        
        char *ptr = this->data + this->offset;

        this->offset+= size;

        return ptr ;
    }

    else return (char*) nullptr ;
}

void Allocator::reset() {this->offset = 0 ;}

Allocator::~Allocator()
{
    this->data = nullptr ;
    this->max_size = 0 ;
    this->offset = 0 ;

    delete[] this->data ;
}