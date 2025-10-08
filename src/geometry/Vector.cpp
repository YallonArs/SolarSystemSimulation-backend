#include <algorithm>
#include <limits>

#include "geometry/Vector.h"
#include "math/MathUtils.h"
#include "utils/Constants.h"

Vector::Vector() : _point(0, 0) {}
Vector::Vector(double x, double y) : _point(x, y) {}
Vector::Vector(const Point &point) : _point(point) {}
Vector::Vector(const Point &from, const Point &to) : _point(to - from) {}

double Vector::x() const { return _point.x(); }
double Vector::y() const { return _point.y(); }
Point Vector::point() const { return _point; }

Vector Vector::operator+(const Vector &other) const {
	return Vector(_point + other._point);
}

Vector Vector::operator-(const Vector &other) const {
	return *this + (-other);
}

Vector Vector::operator*(double scalar) const {
	return Vector(_point * scalar);
}

Vector Vector::operator/(double scalar) const {
	return *this * (1.0 / scalar);
}

Vector Vector::operator-() const {
	return Vector(-_point);
}

Vector &Vector::operator+=(const Vector &other) {
	this->_point += other._point;
	return *this;
}

Vector &Vector::operator-=(const Vector &other) {
	_point -= other._point;
	return *this;
}

Vector &Vector::operator*=(double scalar) {
	_point = _point * scalar;
	return *this;
}

Vector &Vector::operator/=(double scalar) {
	_point = _point / scalar;
	return *this;
}

Vector Vector::rotated(double angle) const {
	double cosA = std::cos(angle);
	double sinA = std::sin(angle);

	/*

	rotation matrix:
	| cosA -sinA |
	| sinA  cosA |

	*/

	return Vector(_point.x() * cosA - _point.y() * sinA,
				  _point.x() * sinA + _point.y() * cosA);
}

void Vector::rotate(double angle) {
	*this = rotated(angle);
}

PolarCoords Vector::toPolar() const {
	if (isZero()) return {0, 0};

	return PolarCoords{length(), std::atan2(_point.y(), _point.x())};
}

Vector Vector::fromPolar(const PolarCoords &polar) {
	return Vector(polar.r * std::cos(polar.theta), polar.r * std::sin(polar.theta));
}

Vector Vector::normalized() const {
	double len = length();
	if (len <= Constants::EPSILON) return *this;
	return *this / len;
}

void Vector::normalize() {
	*this = normalized();
}

double Vector::length() const {
	return MathUtils::distance(_point, Point(0, 0));
}

double Vector::dot(const Vector &other) const {
	return _point.x() * other._point.x() + _point.y() * other._point.y();
}

double Vector::cross(const Vector &other) const {
	return _point.x() * other._point.y() - _point.y() * other._point.x();
}

double Vector::angleTo(const Vector &other) const {
	double dotProduct = dot(other);
	double magnitudes = length() * other.length();
	if (magnitudes <= Constants::EPSILON) return 0.0;

	double c = std::clamp(dotProduct / magnitudes, -1.0, 1.0);
	return std::acos(c);
}

bool Vector::isZero() const {
	return length() <= Constants::EPSILON;
}
