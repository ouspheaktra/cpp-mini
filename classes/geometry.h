#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <windows.h>
#include "math.h"

class Point {
public:
	int x, y;
	Point();
	Point(int x);
	Point(int x, int y);
	void Set(int x, int y);
	Point & Offset(int x, int y);
	Point & Offset(Point point);
	double AngleFrom(Point point);
	double DistanceFrom(Point point);
	Point MidPointFrom(Point point);
	Point RotateAround(Point point, double angle);

	Point operator + (Point point) const;
	Point operator - (Point point) const;
	Point operator += (Point point);
	Point operator -= (Point point);
	operator bool();
};

class Circle {
	int x, y, radius;
public:
	Circle();
	Circle(Point point, int radius);
	Circle(int x, int y, int radius);
	void SetValue(int x, int y, int radius);
	Point GetPointAtAngle(double angle);
};

class Line {
	double slope;
	double yIntercept;
public:
	Line();
	Line(double slope, double yIntercept);
	Line(Point point1, Point point2);
	void Set(double slope, double yIntercept);
	void Set(Point point1, Point point2);
	Point GetPointAtX(int x);
	Point GetPointAtY(int y);
	Point GetPointAtDistanceFromPoint(double distance, Point point);
};

#endif