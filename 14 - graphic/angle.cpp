#include<graphics.h>
#include<math.h>
#include<iostream>
#include<windows.h>

int radtodeg(float rad) {
	return rad/M_PI*180;
}
int angle(int x1, int y1, int x2, int y2) {
	float r = atan2(y2-y1, x2-x1);
	int d = radtodeg(r);
	if (d < 0)	return -d;
	else		return 360-d;
}

void eye(int x, int y, int radius, int deg) {
	arccoordstype path;
	
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(x, y, radius, radius);
	
	arc(x, y, deg, deg, radius/2);
	getarccoords(&path);
	
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(path.xstart, path.ystart, radius/2, radius/2);
}

void m(int x, int y) {
	
	//cleardevice();
	
	static int radius = 50;
	for (int r = radius; r <= getmaxy()-radius; r += radius*2) {
		for (int c = radius; c <= getmaxx()-radius; c += radius*2) {
			eye(c, r, radius, angle(c, r, x, y));
		}
	}
	
}

main() {
	
	initwindow(640, 480);
	
	registermousehandler(WM_MOUSEMOVE, m);
	
	getch();
	closegraph();

}
