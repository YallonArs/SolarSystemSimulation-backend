#include <limits>
#include <cmath>

#include "utils/Constants.h"
#include "geometry/Point.h"
#include "geometry/Vector.h"

Point::Point() : _x(0.0), _y(0.0) {}
Point::Point(double x, double y) : _x(x), _y(y) {}

double Point::x() const { return _x; }
double Point::y() const { return _y; }

Point Point::operator-() const {
	return Point(-_x, -_y);
}

Point Point::operator+(const Point& other) const {
	return Point(_x + other._x, _y + other._y);
}

Point Point::operator+(const Vector& vector) const {
	return *this + vector.point();
}

Point Point::operator-(const Point& other) const {
	return *this + (-other);
}

Point Point::operator-(const Vector& vector) const {
	return *this + (-vector);
}

Point& Point::operator+=(const Point& other) {
	*this = *this + other;

	return *this;
}

Point& Point::operator+=(const Vector& vector) {
	*this = *this + vector;
	return *this;
}

Point& Point::operator-=(const Point& other) {
	*this = *this - other;

	return *this;
}

Point& Point::operator-=(const Vector& vector) {
	*this = *this - vector;
	return *this;
}

Point Point::operator*(double scalar) const {
	return Point(_x * scalar, _y * scalar);
}

Point Point::operator/(double scalar) const {
	return *this * (1.0 / scalar);
}

bool Point::operator==(const Point& other) const {
	return std::abs(_x - other._x) <= Constants::EPSILON &&
		std::abs(_y - other._y) <= Constants::EPSILON;
}

bool Point::operator!=(const Point& other) const {
	return !(*this == other);
}
