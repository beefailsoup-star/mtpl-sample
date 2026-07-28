#include "quaternion.h"
#include <iostream>
#include <cmath>

int main() {
    Quatf q1(1.0f, 0.0f, 1.0f, 0.0f);
    q1.normalize();
    std::cout << "q1: (" << q1.w << ", " << q1.x << ", " << q1.y << ", " << q1.z << ")\n";

    Vector3f axis(0.0f, 1.0f, 0.0f);
    auto q_rot = Quatf::from_axis_angle(axis, 3.14159f / 2.0f);
    std::cout << "90 deg around Y: (" << q_rot.w << ", " << q_rot.x << ", "
              << q_rot.y << ", " << q_rot.z << ")\n";

    Vector3f point(1.0f, 0.0f, 0.0f);
    auto rotated = q_rot.rotate(point);
    std::cout << "Rotated point: (" << rotated.x << ", " << rotated.y << ", "
              << rotated.z << ")\n";

    auto euler_q = Quatf::from_euler(0.0f, 0.0f, 3.14159f / 4.0f);
    std::cout << "From euler (45 deg roll): (" << euler_q.w << ", " << euler_q.x
              << ", " << euler_q.y << ", " << euler_q.z << ")\n";

    auto combined = q_rot * euler_q;
    std::cout << "Combined quat norm: " << combined.norm() << "\n";
    return 0;
}
