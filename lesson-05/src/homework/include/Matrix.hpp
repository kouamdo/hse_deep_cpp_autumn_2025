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
            const int32_t& operator[](size_t j) const;
        };

        int32_t** data_;
        size_t rows_;
        size_t cols_;
        ProxyRow* rows_data_;

    public:
        // ctors / assignment
        Matrix(size_t rows, size_t cols);
        Matrix(const Matrix& other);
        Matrix(Matrix&& other) noexcept;
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other) noexcept;
        ~Matrix();

        // access
        int32_t& at(size_t i, size_t j);
        const int32_t& at(size_t i, size_t j) const;

        size_t getColumns() const;
        size_t getRows() const;

        // arithmetic
        Matrix& operator*=(int32_t val);
        Matrix operator+(const Matrix& other) const;

        // comparisons
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

        // proxy access
        ProxyRow& operator[](size_t i);
        const ProxyRow operator[](size_t i) const;

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

#endif // MATRIX_HPP