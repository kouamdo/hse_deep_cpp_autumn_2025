#include <cstdint>
#include <stdexcept>
#include <iostream>

class Matrix
{
    private:

        int32_t* data;
        size_t rows;
        size_t cols;

    public:
        Matrix(size_t rows , size_t cols , int32_t* data);
        
        int32_t& at(size_t i , size_t j) {
            if (i >= rows || j >= cols) throw std::out_of_range("Matrix indice out of range");
            return data[i * cols + j];
        }
        ~Matrix();
};

Matrix::Matrix(size_t r , size_t c , int32_t* data) : rows(r) , cols(c) , data(data)
{
    data = new int32_t[rows * cols];
    
    for (size_t i = 0; i < rows * cols; ++i) data[i] = 0;
}

Matrix::~Matrix() { delete[] data; }