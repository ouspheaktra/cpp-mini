#include<graphics.h>
main() {
	
	initwindow(640, 480);
	
	int midx = getmaxx()/2;
	int midy = getmaxy()/2;
	bool open = true;
	int maxangle = 45;
	int minangle = 0;
	int angle = 0;
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, YELLOW);
	while(1) {
		cleardevice();
		arc(midx, midy, angle, -angle, 150);
	
		arccoordstype a;
		getarccoords(&a);
		
		line(a.x, a.y, a.xstart, a.ystart);
		line(a.x, a.y, a.xend, a.yend);
		
		if (open)	angle+=4;
		else		angle-=4;
			
		if (angle >= maxangle)	open = false;
		if (angle <= minangle)	open = true;
		
		delay(50);
	}
	
	
	getch();
	closegraph();

}
