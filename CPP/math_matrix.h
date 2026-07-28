#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include "math_vector.h"
#include <array>
#include <cstring>

template <typename T>
class Matrix4 {
public:
    std::array<T, 16> data;

    Matrix4() { identity(); }

    T& operator()(int r, int c) { return data[r * 4 + c]; }
    const T& operator()(int r, int c) const { return data[r * 4 + c]; }

    void identity() {
        data.fill(0);
        data[0] = data[5] = data[10] = data[15] = T(1);
    }

    Matrix4 operator*(const Matrix4& m) const {
        Matrix4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                T sum = 0;
                for (int k = 0; k < 4; ++k)
                    sum += (*this)(i, k) * m(k, j);
                r(i, j) = sum;
            }
        return r;
    }

    Vector3<T> transform(const Vector3<T>& v) const {
        T w = data[3] * v.x + data[7] * v.y + data[11] * v.z + data[15];
        if (w == 0) w = 1;
        return {
            (data[0] * v.x + data[4] * v.y + data[8] * v.z + data[12]) / w,
            (data[1] * v.x + data[5] * v.y + data[9] * v.z + data[13]) / w,
            (data[2] * v.x + data[6] * v.y + data[10] * v.z + data[14]) / w
        };
    }

    Matrix4 transpose() const {
        Matrix4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r(i, j) = (*this)(j, i);
        return r;
    }

    T determinant() const {
        auto a = [this](int i, int j) { return data[i * 4 + j]; };
        return a(0,3) * a(1,2) * a(2,1) * a(3,0) - a(0,2) * a(1,3) * a(2,1) * a(3,0)
             - a(0,3) * a(1,1) * a(2,2) * a(3,0) + a(0,1) * a(1,3) * a(2,2) * a(3,0)
             + a(0,2) * a(1,1) * a(2,3) * a(3,0) - a(0,1) * a(1,2) * a(2,3) * a(3,0)
             - a(0,3) * a(1,2) * a(2,0) * a(3,1) + a(0,2) * a(1,3) * a(2,0) * a(3,1)
             + a(0,3) * a(1,0) * a(2,2) * a(3,1) - a(0,0) * a(1,3) * a(2,2) * a(3,1)
             - a(0,2) * a(1,0) * a(2,3) * a(3,1) + a(0,0) * a(1,2) * a(2,3) * a(3,1)
             + a(0,3) * a(1,1) * a(2,0) * a(3,2) - a(0,1) * a(1,3) * a(2,0) * a(3,2)
             - a(0,3) * a(1,0) * a(2,1) * a(3,2) + a(0,0) * a(1,3) * a(2,1) * a(3,2)
             + a(0,1) * a(1,0) * a(2,3) * a(3,2) - a(0,0) * a(1,1) * a(2,3) * a(3,2)
             - a(0,2) * a(1,1) * a(2,0) * a(3,3) + a(0,1) * a(1,2) * a(2,0) * a(3,3)
             + a(0,2) * a(1,0) * a(2,1) * a(3,3) - a(0,0) * a(1,2) * a(2,1) * a(3,3)
             - a(0,1) * a(1,0) * a(2,2) * a(3,3) + a(0,0) * a(1,1) * a(2,2) * a(3,3);
    }

    static Matrix4 translation(T x, T y, T z) {
        Matrix4 m;
        m(0, 3) = x; m(1, 3) = y; m(2, 3) = z;
        return m;
    }

    static Matrix4 rotation_x(T angle) {
        Matrix4 m;
        T c = std::cos(angle), s = std::sin(angle);
        m(1, 1) = c; m(1, 2) = -s;
        m(2, 1) = s; m(2, 2) = c;
        return m;
    }

    static Matrix4 rotation_y(T angle) {
        Matrix4 m;
        T c = std::cos(angle), s = std::sin(angle);
        m(0, 0) = c; m(0, 2) = s;
        m(2, 0) = -s; m(2, 2) = c;
        return m;
    }

    static Matrix4 rotation_z(T angle) {
        Matrix4 m;
        T c = std::cos(angle), s = std::sin(angle);
        m(0, 0) = c; m(0, 1) = -s;
        m(1, 0) = s; m(1, 1) = c;
        return m;
    }

    static Matrix4 scale(T x, T y, T z) {
        Matrix4 m;
        m(0, 0) = x; m(1, 1) = y; m(2, 2) = z;
        return m;
    }

    static Matrix4 perspective(T fov, T aspect, T near, T far) {
        Matrix4 m;
        T f = T(1) / std::tan(fov / T(2));
        m(0, 0) = f / aspect;
        m(1, 1) = f;
        m(2, 2) = (far + near) / (near - far);
        m(2, 3) = (T(2) * far * near) / (near - far);
        m(3, 2) = T(-1);
        m(3, 3) = T(0);
        return m;
    }
};

using Mat4f = Matrix4<float>;
using Mat4d = Matrix4<double>;

#endif
