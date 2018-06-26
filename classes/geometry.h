#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <windef.h>

class Circle {
	int x, y, radius;
public:
	Circle();
	Circle(int x, int y, int radius);
	void SetValue(int x, int y, int radius);
	POINT GetPointAtDegree(int degree);
};

#endif
