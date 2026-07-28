#include "smart_ptr.h"
#include <iostream>

struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
    ~Point() { std::cout << "Point(" << x << "," << y << ") destroyed\n"; }
};

int main() {
    SharedPtr<Point> p1 = make_shared<Point>(3, 4);
    std::cout << "p1: (" << p1->x << ", " << p1->y << "), count: " << p1.use_count() << "\n";

    {
        SharedPtr<Point> p2 = p1;
        std::cout << "p2 created, count: " << p1.use_count() << "\n";
    }
    std::cout << "p2 out of scope, count: " << p1.use_count() << "\n";

    auto p3 = std::move(p1);
    std::cout << "moved to p3, p1 is null: " << (!p1 ? "true" : "false") << "\n";
    return 0;
}
