#include "math.h"

double sec(double angle) {
	return 1 / cos(angle);
}

double versin(double angle) {
	return 1 - cos(angle);
}

double exsec(double angle) {
	return sec(angle) - 1;
}

double cosec(double angle) {
	return 1 / sin(angle);
}

double coversin(double angle) {
	return 1 - sin(angle);
}

double excsc(double angle) {
	return cosec(angle) - 1;
}

double crd(double angle) {
	return 2 * sin(angle / 2);
}

double haversin(double angle) {
	return versin(angle) / 2;
}
