#include <iostream>
#include "Point.h"
#include "Vector.h"

int main() {
	Point p1(1.0, 2.0);
	Point p2(3.0, 4.0);
	Vector v1(p1, p2);

	std::cout << "Point 1: (" << p1.x() << ", " << p1.y() << ")\n";
	std::cout << "Point 2: (" << p2.x() << ", " << p2.y() << ")\n";
	std::cout << "Vector from Point 1 to Point 2: (" << v1.x() << ", " << v1.y() << ")\n";
}
