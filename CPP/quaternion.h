#ifndef QUATERNION_H
#define QUATERNION_H

#include "math_vector.h"
#include <cmath>

template <typename T>
class Quaternion {
public:
    T w, x, y, z;

    Quaternion() : w(1), x(0), y(0), z(0) {}
    Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

    static Quaternion identity() { return {T(1), T(0), T(0), T(0)}; }

    Quaternion conjugated() const { return {w, -x, -y, -z}; }
    Quaternion inverse() const {
        T n = norm_sq();
        if (n == 0) return identity();
        auto conj = conjugated();
        return {conj.w / n, conj.x / n, conj.y / n, conj.z / n};
    }

    Quaternion operator*(const Quaternion& q) const {
        return {
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        };
    }

    Quaternion& operator*=(const Quaternion& q) {
        *this = *this * q;
        return *this;
    }

    T norm_sq() const { return w * w + x * x + y * y + z * z; }
    T norm() const { return std::sqrt(norm_sq()); }

    Quaternion normalized() const {
        T n = norm();
        if (n == 0) return identity();
        return {w / n, x / n, y / n, z / n};
    }

    void normalize() {
        T n = norm();
        if (n > 0) { w /= n; x /= n; y /= n; z /= n; }
    }

    static Quaternion from_axis_angle(const Vector3<T>& axis, T angle) {
        T half = angle / T(2);
        T s = std::sin(half);
        return {std::cos(half), axis.x * s, axis.y * s, axis.z * s};
    }

    static Quaternion from_euler(T pitch, T yaw, T roll) {
        T cp = std::cos(pitch / 2), sp = std::sin(pitch / 2);
        T cy = std::cos(yaw / 2), sy = std::sin(yaw / 2);
        T cr = std::cos(roll / 2), sr = std::sin(roll / 2);
        return {
            cp * cy * cr + sp * sy * sr,
            sp * cy * cr - cp * sy * sr,
            cp * sy * cr + sp * cy * sr,
            cp * cy * sr - sp * sy * cr
        };
    }

    Vector3<T> rotate(const Vector3<T>& v) const {
        Quaternion p(0, v.x, v.y, v.z);
        auto q = (*this) * p * this->inverse();
        return {q.x, q.y, q.z};
    }

    Matrix4<T> to_matrix() const {
        Matrix4<T> m;
        T xx = x * x, yy = y * y, zz = z * z;
        T xy = x * y, xz = x * z, yz = y * z;
        T wx = w * x, wy = w * y, wz = w * z;

        m(0, 0) = T(1) - T(2) * (yy + zz);
        m(0, 1) = T(2) * (xy - wz);
        m(0, 2) = T(2) * (xz + wy);
        m(1, 0) = T(2) * (xy + wz);
        m(1, 1) = T(1) - T(2) * (xx + zz);
        m(1, 2) = T(2) * (yz - wx);
        m(2, 0) = T(2) * (xz - wy);
        m(2, 1) = T(2) * (yz + wx);
        m(2, 2) = T(1) - T(2) * (xx + yy);
        return m;
    }
};

using Quatf = Quaternion<float>;
using Quatd = Quaternion<double>;

#endif
