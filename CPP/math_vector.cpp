#include "math_vector.h"
#include <iostream>
#include <cmath>

int main() {
    Vec3f a(1.0f, 2.0f, 3.0f);
    Vec3f b(4.0f, 5.0f, 6.0f);

    auto sum = a + b;
    auto diff = a - b;
    auto scaled = a * 2.0f;
    auto dot = a.dot(b);
    auto cross = a.cross(b);

    std::cout << "a = (" << a.x << ", " << a.y << ", " << a.z << ")\n";
    std::cout << "b = (" << b.x << ", " << b.y << ", " << b.z << ")\n";
    std::cout << "a + b = (" << sum.x << ", " << sum.y << ", " << sum.z << ")\n";
    std::cout << "a - b = (" << diff.x << ", " << diff.y << ", " << diff.z << ")\n";
    std::cout << "a * 2 = (" << scaled.x << ", " << scaled.y << ", " << scaled.z << ")\n";
    std::cout << "a dot b = " << dot << "\n";
    std::cout << "a cross b = (" << cross.x << ", " << cross.y << ", " << cross.z << ")\n";
    std::cout << "|a| = " << a.length() << "\n";
    std::cout << "a normalized = (" << a.normalized().x << ", " << a.normalized().y << ", " << a.normalized().z << ")\n";
    std::cout << "distance a-b = " << a.distance(b) << "\n";

    Vec2f p1(3.0f, 4.0f);
    std::cout << "|p1| = " << p1.length() << "\n";
    return 0;
}
