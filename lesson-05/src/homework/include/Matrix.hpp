#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdint>
#include <stdexcept>
#include <iostream>

class Matrix
{
    private:
        class ProxyRow
        {
        private:
            int32_t* data_;
            size_t cols_;
        public:
            ProxyRow();
            ProxyRow(int32_t* row_data, size_t cols);
            int32_t& operator[](size_t j);
        };

        int32_t** data;
        size_t rows;
        size_t cols;
        ProxyRow* rows_data;

    public:
        Matrix(size_t rows, size_t cols);
        ~Matrix();

        int32_t& at(size_t i, size_t j);

        size_t getColumns() const {}
        size_t getRows() const {}
        Matrix& operator*=(int32_t val);
        Matrix operator+(Matrix& other) const;
        bool operator==(Matrix& other) const;
        bool operator!=(Matrix& other) const;

        ProxyRow& operator[](size_t i);

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

#endif // MATRIX_HPP