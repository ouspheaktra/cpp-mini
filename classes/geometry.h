#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <windows.h>
#include <math.h>

#define PI 3.14159265358979323846
#define toRadian(degree) (double)(degree*PI / 180)
#define toDegree(radian) (float)(radian*180 / PI)

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
	Point operator * (int number) const;
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

#endif