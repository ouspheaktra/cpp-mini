#ifndef MATH_H
#define MATH_H

#include <math.h>

#define PI 3.14159265358979323846
#define toRadian(degree) (double)(degree*PI / 180)
#define toDegree(radian) (double)(radian*180 / PI)

double sec(double angle);
double asec(double value);
double versin(double angle);
double aversin(double value);
double exsec(double angle);
double aexsec(double value);

double cosec(double angle);
double acosec(double value);
double coversin(double angle);
double acoversin(double value);
double excsc(double angle);
double aexcsc(double value);

double tan(double angle);
double cotan(double angle);
double acotan(double value);
double crd(double angle);
double acrd(double value);
double haversin(double angle);

#endif