#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <cmath>
#include <cassert>

template <typename T>
class Vector2 {
public:
    T x, y;
    Vector2() : x(0), y(0) {}
    Vector2(T x, T y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& v) const { return {x + v.x, y + v.y}; }
    Vector2 operator-(const Vector2& v) const { return {x - v.x, y - v.y}; }
    Vector2 operator*(T s) const { return {x * s, y * s}; }
    Vector2 operator/(T s) const { return {x / s, y / s}; }
    Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
    Vector2& operator*=(T s) { x *= s; y *= s; return *this; }
    Vector2& operator/=(T s) { x /= s; y /= s; return *this; }

    T dot(const Vector2& v) const { return x * v.x + y * v.y; }
    T length() const { return std::sqrt(length_sq()); }
    T length_sq() const { return x * x + y * y; }
    Vector2 normalized() const { auto l = length(); return l > 0 ? Vector2(x / l, y / l) : Vector2(); }
    void normalize() { auto l = length(); if (l > 0) { x /= l; y /= l; } }
    T distance(const Vector2& v) const { return (*this - v).length(); }
};

template <typename T>
class Vector3 {
public:
    T x, y, z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vector3 operator-(const Vector3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vector3 operator*(T s) const { return {x * s, y * s, z * s}; }
    Vector3 operator/(T s) const { return {x / s, y / s, z / s}; }
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3& operator*=(T s) { x *= s; y *= s; z *= s; return *this; }
    Vector3& operator/=(T s) { x /= s; y /= s; z /= s; return *this; }

    T dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vector3 cross(const Vector3& v) const {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }
    T length() const { return std::sqrt(length_sq()); }
    T length_sq() const { return x * x + y * y + z * z; }
    Vector3 normalized() const { auto l = length(); return l > 0 ? Vector3(x / l, y / l, z / l) : Vector3(); }
    void normalize() { auto l = length(); if (l > 0) { x /= l; y /= l; z /= l; } }
    T distance(const Vector3& v) const { return (*this - v).length(); }
};

using Vec2f = Vector2<float>;
using Vec2d = Vector2<double>;
using Vec3f = Vector3<float>;
using Vec3d = Vector3<double>;

#endif
