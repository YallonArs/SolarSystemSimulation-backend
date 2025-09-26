#pragma once

#include <utility>

class Vector;

class Point {
private:
    double _x, _y;

public:
    Point();
    Point(std::pair<double, double> values);
    Point(double x, double y);

    double x() const;
    double y() const;
	
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

    double distanceTo(const Point& other) const;
};
