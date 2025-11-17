#include "../include/Matrix.hpp"

// ProxyRow

Matrix::ProxyRow::ProxyRow() : data_(nullptr), cols_(0) {}

Matrix::ProxyRow::ProxyRow(int32_t* row_data, size_t cols) : data_(row_data), cols_(cols) {}

int32_t& Matrix::ProxyRow::operator[](size_t j)
{
    if (j >= cols_)
        throw std::out_of_range("Column index out of range");
    return data_[j];
}

// Matrix

Matrix::Matrix(size_t r, size_t c) : rows(r), cols(c)
{
    data = new int32_t*[rows];
    for (size_t i = 0; i < rows; i++)
        data[i] = new int32_t[cols]();

    rows_data = new Matrix::ProxyRow[rows];
    for (size_t j = 0; j < rows; j++)
        rows_data[j] = ProxyRow(data[j], cols);
}

size_t Matrix::getRows() const { return rows; }

size_t Matrix::getColumns() const { return cols; }

Matrix::~Matrix()
{
    for (size_t i = 0; i < rows; i++)
        delete[] data[i];
    delete[] data;
    delete[] rows_data;
}

int32_t& Matrix::at(size_t i, size_t j)
{
    if (i >= rows || j >= cols)
        throw std::out_of_range("Matrix indice out of range");
    return data[i][j];
}

Matrix& Matrix::operator*=(int32_t val)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            data[i][j] *= val;
    return *this;
}

Matrix Matrix::operator+(Matrix& other) const
{
    if (other.rows == rows && other.cols == cols)
    {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }
    else
        throw std::invalid_argument("Matrices sizes do not match");
}

bool Matrix::operator==(Matrix& other) const
{
    if (other.rows == rows && other.cols == cols)
    {
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                if (data[i][j] != other.data[i][j])
                    return false;

        return true;
    }
    else
        throw std::invalid_argument("Matrices sizes do not match");
}

bool Matrix::operator!=(Matrix& other) const
{
    return !(*this == other);
}

Matrix::ProxyRow& Matrix::operator[](size_t i)
{
    if (i >= rows)
        throw std::out_of_range("Row index out of range");
    return rows_data[i];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (size_t i = 0; i < m.rows; i++)
    {
        for (size_t j = 0; j < m.cols; j++)
            os << m.data[i][j] << ' ';
        os << '\n';
    }
    return os;
}
