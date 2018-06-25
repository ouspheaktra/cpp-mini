#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <windef.h>
#include <math.h>

double DegreeToRadian(int degree) {
	return degree*M_PI/180;
}

class Circle {
	int x, y, radius;
public:
	Circle() {
		SetValue(0, 0, 0);
	}
	Circle(int x, int y, int radius) {
		SetValue(x, y, radius);
	}
	SetValue(int x, int y, int radius) {
		this->x = x;
		this->y = y;
		this->radius = radius;
	}
	POINT GetPointAtDegree(int degree) {
		return (POINT){
			x + radius*cos( DegreeToRadian(degree) ),
			y + radius*sin( DegreeToRadian(degree) )
		};
	}
};

#endif
