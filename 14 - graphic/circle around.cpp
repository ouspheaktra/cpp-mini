#include"graphics.h"
main() {
	
	initwindow(640, 480);
	
	int midx = getmaxx()/2;
	int midy = getmaxy()/2;
	int angle = 0;
	int step = 5;
	while (angle <= 360) {
		setcolor(BLACK);
		arc(midx, midy, angle, angle+step, 150);
		
		arccoordstype a;
		getarccoords(&a);
		
		setcolor(YELLOW);
		circle(a.xend, a.yend, 50);
		delay(100);
		angle += step;
	}
	getch();
	closegraph();

}
