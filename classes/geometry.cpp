#include "geometry.h"
#include <windef.h>
#include <math.h>

double DegreeToRadian(int degree) {
	return degree*M_PI/180;
}

Circle::Circle() {
	SetValue(0, 0, 0);
}
Circle::Circle(int x, int y, int radius) {
	SetValue(x, y, radius);
}
void Circle::SetValue(int x, int y, int radius) {
	this->x = x;
	this->y = y;
	this->radius = radius;
}
POINT Circle::GetPointAtDegree(int degree) {
	return (POINT){
		x + radius*cos( DegreeToRadian(degree) ),
		y + radius*sin( DegreeToRadian(degree) )
	};
}
