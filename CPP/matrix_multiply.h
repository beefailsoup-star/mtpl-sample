#ifndef MATRIX_MULTIPLY_H
#define MATRIX_MULTIPLY_H

#include <vector>
#include <cstddef>
#include <stdexcept>

template <typename T>
class Matrix {
public:
    Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data_(rows * cols) {}

    T& operator()(size_t r, size_t c) {
        if (r >= rows_ || c >= cols_) throw std::out_of_range("Matrix index out of range");
        return data_[r * cols_ + c];
    }

    const T& operator()(size_t r, size_t c) const {
        if (r >= rows_ || c >= cols_) throw std::out_of_range("Matrix index out of range");
        return data_[r * cols_ + c];
    }

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }

    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_)
            throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
        Matrix result(rows_, other.cols_);
        for (size_t i = 0; i < rows_; ++i)
            for (size_t j = 0; j < other.cols_; ++j) {
                T sum = T{};
                for (size_t k = 0; k < cols_; ++k)
                    sum += (*this)(i, k) * other(k, j);
                result(i, j) = sum;
            }
        return result;
    }

private:
    size_t rows_, cols_;
    std::vector<T> data_;
};

using Matrixf = Matrix<float>;
using Matrixd = Matrix<double>;

#endif
