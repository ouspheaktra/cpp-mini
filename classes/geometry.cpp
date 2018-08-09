#include "geometry.h"

Circle::Circle() {
	SetValue(0, 0, 0);
}
Circle::Circle(Point point, int radius) {
	SetValue(point.x, point.y, radius);
}
Circle::Circle(int x, int y, int radius) {
	SetValue(x, y, radius);
}
void Circle::SetValue(int x, int y, int radius) {
	this->x = x;
	this->y = y;
	this->radius = radius;
}
Point Circle::GetPointAtAngle(double angle) {
	return {
		(int)(x + radius*cos(angle)),
		(int)(y + radius*sin(angle))
	};
}

Point::Point() {
	Set(0, 0);
}

Point::Point(int x) {
	Set(x, 0);
}

Point::Point(int x, int y) {
	Set(x, y);
}

void Point::Set(int x, int y) {
	this->x = x;
	this->y = y;
}

Point & Point::Offset(int x, int y) {
	this->x += x;
	this->y += y;
	return *this;
}

Point & Point::Offset(Point point) {
	return Offset(point.x, point.y);
}

double Point::AngleFrom(Point point){
	return atan2(this->y - point.y, this->x - point.x);
}

double Point::DistanceFrom(Point point) {
	return sqrt(pow(this->x - point.x, 2) + pow(this->y - point.y, 2));
}

Point Point::MidPointFrom(Point point) {
	return {
		(point.x + this->x) / 2,
		(point.y + this->y) / 2
	};
}

Point Point::RotateAround(Point point, double angle) {
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	Point newPoint = *this;
	newPoint -= point;

	// rotate point n translate back
	newPoint.Set(
		newPoint.x * c - newPoint.y * s + point.x,
		newPoint.x * s + newPoint.y * c + point.y
	);

	return newPoint;
}

Point Point::operator+ (Point point) const {
	return {
		this->x + point.x,
		this->y + point.y
	};
}

Point Point::operator-(Point point) const {
	return{
		this->x - point.x,
		this->y - point.y
	};
}

Point Point::operator* (int number) const {
	return {
		this->x * number,
		this->y * number
	};
}

Point Point::operator+=(Point point) {
	*this = *this + point;
	return *this;
}

Point Point::operator-=(Point point) {
	*this = *this - point;
	return *this;
}

Point::operator bool() {
	return !(x == 0 && y == 0);
}

Line::Line() : Line(0, 0) {}

Line::Line(double slope, double yIntercept) {
	Set(slope, yIntercept);
}

Line::Line(Point point1, Point point2) {
	Set(point1, point2);
}

void Line::Set(double slope, double yIntercept) {
	this->slope = slope;
	this->yIntercept = yIntercept;
}

void Line::Set(Point point1, Point point2) {
	slope = ((double)point2.y - (double)point1.y) / ((double)point2.x - (double)point1.x);
	yIntercept = point1.y - slope * point1.x;
}

Point Line::GetPointAtX(int x) {
	return {
		x,
		(int)(x * slope + yIntercept)
	};
}

Point Line::GetPointAtY(int y) {
	return {
		(int)((y - yIntercept) / slope),
		y
	};
}

Point Line::GetPointAtDistanceFromPoint(double distance, Point point) {
	return GetPointAtX(point.x + distance / sqrt(1 + slope * slope));
}
