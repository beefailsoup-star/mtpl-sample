#include "matrix_multiply.h"
#include <iostream>
#include <random>

template <typename T>
static Matrix<T> make_random(size_t r, size_t c) {
    Matrix<T> m(r, c);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(T(-10), T(10));
    for (size_t i = 0; i < r; ++i)
        for (size_t j = 0; j < c; ++j)
            m(i, j) = dist(gen);
    return m;
}

template <typename T>
static void print_matrix(const Matrix<T>& m) {
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j)
            std::cout << m(i, j) << "\t";
        std::cout << "\n";
    }
}

int main() {
    auto a = make_random<double>(3, 3);
    auto b = make_random<double>(3, 3);
    auto c = a * b;
    std::cout << "Matrix A:\n"; print_matrix(a);
    std::cout << "Matrix B:\n"; print_matrix(b);
    std::cout << "A * B:\n"; print_matrix(c);
    return 0;
}
