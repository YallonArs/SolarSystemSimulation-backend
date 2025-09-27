#include <cmath>

#include "math/MathUtils.h"

double MathUtils::distance(Point p1, Point p2) {
	return std::sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
}
