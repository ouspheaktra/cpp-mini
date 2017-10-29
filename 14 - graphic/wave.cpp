#include <math.h>
#include <graphics.h>
#include <iostream>
#define radtodeg(rad) rad/M_PI*180
#define degtorad(deg) deg/180*M_PI
#define E 2.7182

int main() {
	
	initwindow(640, 360);

    double x, y;
 
	line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
	
	int prevy = NULL,
		prevx = NULL;
	
	/* generate a sine wave */
	for(x = 0; x < getmaxx(); x+=1) {
		
		/* calculate y value given x */
		y = sin(degtorad(x)*3);
		y = getmaxy()/2 - 75*y;
		
		if (prevy == NULL) {
			prevy = y;
			prevx = x;
		} else {
			/* draw line */
			line(prevx, prevy, x, y);
			prevy = y;
			prevx = x;
		}
		
		delay(10);
	}
	
	getch();
	
	/* deallocate memory allocated for graphics screen */
	closegraph();
	
	return 0;
}
