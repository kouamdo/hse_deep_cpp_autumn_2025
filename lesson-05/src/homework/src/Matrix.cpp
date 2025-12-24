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

const int32_t& Matrix::ProxyRow::operator[](size_t j) const
{
    if (j >= cols_)
        throw std::out_of_range("Column index out of range");
    return data_[j];
}

// Normal constructor
Matrix::Matrix(size_t r, size_t c) : data_(nullptr), rows_(r), cols_(c), rows_data_(nullptr)
{
    if (rows_ == 0 || cols_ == 0)
        throw std::invalid_argument("rows and cols must be > 0");

    data_ = new int32_t*[rows_];
    for (size_t i = 0; i < rows_; i++) {
        data_[i] = new int32_t[cols_]();
    }

    rows_data_ = new Matrix::ProxyRow[rows_];
    for (size_t j = 0; j < rows_; j++)
        rows_data_[j] = ProxyRow(data_[j], cols_);
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
    : data_(nullptr), rows_(other.rows_), cols_(other.cols_), rows_data_(nullptr)
{
    data_ = new int32_t*[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        data_[i] = new int32_t[cols_];
        for (size_t j = 0; j < cols_; ++j)
            data_[i][j] = other.data_[i][j];
    }
    rows_data_ = new Matrix::ProxyRow[rows_];
    for (size_t i = 0; i < rows_; ++i)
        rows_data_[i] = ProxyRow(data_[i], cols_);
}

// Move constructor
Matrix::Matrix(Matrix&& other) noexcept
    : data_(other.data_), rows_(other.rows_), cols_(other.cols_), rows_data_(other.rows_data_)
{
    other.data_ = nullptr;
    other.rows_data_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

// Copy assignment
Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other) return *this;

    // free current
    if (data_) {
        for (size_t i = 0; i < rows_; ++i) delete[] data_[i];
        delete[] data_;
    }
    delete[] rows_data_;

    rows_ = other.rows_;
    cols_ = other.cols_;

    data_ = new int32_t*[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        data_[i] = new int32_t[cols_];
        for (size_t j = 0; j < cols_; ++j)
            data_[i][j] = other.data_[i][j];
    }
    rows_data_ = new Matrix::ProxyRow[rows_];
    for (size_t i = 0; i < rows_; ++i)
        rows_data_[i] = ProxyRow(data_[i], cols_);

    return *this;
}

// Move assignment
Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    if (this == &other) return *this;

    if (data_) {
        for (size_t i = 0; i < rows_; ++i) delete[] data_[i];
        delete[] data_;
    }
    delete[] rows_data_;

    data_ = other.data_;
    rows_data_ = other.rows_data_;
    rows_ = other.rows_;
    cols_ = other.cols_;

    other.data_ = nullptr;
    other.rows_data_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;

    return *this;
}
size_t Matrix::getRows() const { return rows_; }

size_t Matrix::getColumns() const { return cols_; }

Matrix::~Matrix()
{
    if (data_) {
        for (size_t i = 0; i < rows_; i++)
            delete[] data_[i];
        delete[] data_;
    }
    delete[] rows_data_;
}

int32_t& Matrix::at(size_t i, size_t j)
{
    if (i >= rows_ || j >= cols_)
        throw std::out_of_range("Matrix indice out of range");
    return data_[i][j];
}

const int32_t& Matrix::at(size_t i, size_t j) const
{
    if (i >= rows_ || j >= cols_)
        throw std::out_of_range("Matrix indice out of range");
    return data_[i][j];
}

Matrix& Matrix::operator*=(int32_t val)
{
    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < cols_; j++)
            data_[i][j] *= val;
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (other.rows_ == rows_ && other.cols_ == cols_)
    {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; i++)
            for (size_t j = 0; j < cols_; j++)
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
        return result;
    }
    else
        throw std::invalid_argument("Matrices sizes do not match");
}

bool Matrix::operator==(const Matrix& other) const
{
    if (other.rows_ != rows_ || other.cols_ != cols_)
        return false;

    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < cols_; j++)
            if (data_[i][j] != other.data_[i][j])
                return false;

    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

Matrix::ProxyRow& Matrix::operator[](size_t i)
{
    if (i >= rows_)
        throw std::out_of_range("Row index out of range");
    return rows_data_[i];
}

const Matrix::ProxyRow Matrix::operator[](size_t i) const
{
    if (i >= rows_)
        throw std::out_of_range("Row index out of range");
    return rows_data_[i];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (size_t i = 0; i < m.rows_; i++)
    {
        for (size_t j = 0; j < m.cols_; j++)
            os << m.data_[i][j] << ' ';
        os << '\n';
    }
    return os;
}
