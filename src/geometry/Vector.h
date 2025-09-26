#pragma once

#include <cmath>

#include "Point.h"

class Vector {
protected:
	Point _point;

public:
    Vector();
    Vector(double x, double y);
	Vector(const Point& point);
    Vector(const Point& from, const Point& to);

	double x() const { return _point.x(); }
	double y() const { return _point.y(); }
	Point point() const { return _point; }

    // Vector operations
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;
    Vector operator-() const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(double scalar);
    Vector& operator/=(double scalar);

    Vector normalized() const;
    void normalize();
	double length() const;
    double dot(const Vector& other) const;
    double cross(const Vector& other) const;
    double angleTo(const Vector& other) const;
    bool isZero() const;
};
