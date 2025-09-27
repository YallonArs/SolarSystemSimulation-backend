#pragma once

#include <utility>

class Vector;

class Point {
protected:
	double _x, _y;

public:
	// constructors
	Point();
	Point(double x, double y);

	// getters
	double x() const;
	double y() const;
	
	// operations
	Point operator-() const;
	Point operator+(const Point& other) const;
	Point operator+(const Vector& vector) const;
	Point operator-(const Point& other) const;
	Point operator-(const Vector& vector) const;

	Point& operator+=(const Point& other);
	Point& operator+=(const Vector& vector);
	Point& operator-=(const Point& other);
	Point& operator-=(const Vector& vector);

	Point operator*(double scalar) const;
	Point operator/(double scalar) const;

	bool operator==(const Point& other) const;
	bool operator!=(const Point& other) const;
};
