#include "math.h"

double sec(double angle) {
	if (angle == PI/2 || angle == -PI/2)
		return INFINITY;
	return 1 / cos(angle);
}

double asec(double value) {
	if (value == INFINITY)
		return PI / 2;
	if (value > -1 && value < 1)
		return NAN;
	return acos(1 / value);
}

double versin(double angle) {
	return 1 - cos(angle);
}

double aversin(double value) {
	if (value < 0 || value > 2)
		return NAN;
	return acos(1 - value);
}

double exsec(double angle) {
	return sec(angle) - 1;
}

double aexsec(double value) {
	return asec(value + 1);
}

double cosec(double angle) {
	if (angle == 0 || angle == PI)
		return INFINITY;
	return 1 / sin(angle);
}

double acosec(double value) {
	if (value == INFINITY)
		return 0;
	if (value > -1 && value < 1)
		return NAN;
	return asin(1 / value);
}

double coversin(double angle) {
	return 1 - sin(angle);
}

double acoversin(double value) {
	if (value < 0 || value > 2)
		return NAN;
	return asin(1 - value);
}

double excsc(double angle) {
	return cosec(angle) - 1;
}

double aexcsc(double value) {
	return acosec(value - 1);
}

double tan(double angle) {
	if (angle == PI / 2)
		return INFINITY;
	else if (angle == -PI / 2)
		return -INFINITY;
	return sin(angle) / cos(angle);
}

double cotan(double angle) {
	if (angle == 0)
		return INFINITY;
	else if (angle == PI)
		return -INFINITY;
	return 1 / tan(angle);
}

double acotan(double value) {
	if (value == INFINITY)
		return 0;
	else if (value == -INFINITY)
		return PI;
	return atan(1 / value);
}

double crd(double angle) {
	return 2 * sin(angle / 2);
}

double acrd(double value) {
	if (value < -2 || value > 2)
		return NAN;
	return 2 * asin(value / 2);
}

double haversin(double angle) {
	return versin(angle) / 2;
}
