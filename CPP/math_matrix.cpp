#include "math_matrix.h"
#include <iostream>
#include <cmath>

int main() {
    Mat4f identity;
    std::cout << "Identity Matrix4:\n";
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c)
            std::cout << identity(r, c) << "\t";
        std::cout << "\n";
    }

    auto trans = Mat4f::translation(1.0f, 2.0f, 3.0f);
    Vec3f point(1.0f, 1.0f, 1.0f);
    auto transformed = trans.transform(point);
    std::cout << "Translated point: (" << transformed.x << ", "
              << transformed.y << ", " << transformed.z << ")\n";

    auto rot = Mat4f::rotation_z(3.14159f / 4.0f);
    auto scaled = Mat4f::scale(2.0f, 2.0f, 2.0f);
    auto combined = trans * rot * scaled;

    std::cout << "Combined matrix determinant: " << combined.determinant() << "\n";

    auto proj = Mat4f::perspective(3.14159f / 2.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    std::cout << "Perspective projection [2][2]: " << proj(2, 2) << "\n";
    return 0;
}
