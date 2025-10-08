#pragma once

#include <cmath>

#include "geometry/Point.h"

struct PolarCoords {
	double r, theta;
};

class Vector {
protected:
	Point _point;

public:
	// constructors
	Vector();
	Vector(double x, double y);
	Vector(const Point &point);
	Vector(const Point &from, const Point &to);

	// getters
	double x() const;
	double y() const;
	Point point() const;

	// operations
	Vector operator+(const Vector &other) const;
	Vector operator-(const Vector &other) const;
	Vector operator*(double scalar) const;
	Vector operator/(double scalar) const;
	Vector operator-() const;

	Vector &operator+=(const Vector &other);
	Vector &operator-=(const Vector &other);
	Vector &operator*=(double scalar);
	Vector &operator/=(double scalar);

	Vector rotated(double angle) const;
	void rotate(double angle);

	PolarCoords toPolar() const;
	static Vector fromPolar(const PolarCoords &polar);

	// calculations
	Vector normalized() const;
	void normalize();
	double length() const;
	double dot(const Vector &other) const;
	double cross(const Vector &other) const;
	double angleTo(const Vector &other) const;
	bool isZero() const;
};
