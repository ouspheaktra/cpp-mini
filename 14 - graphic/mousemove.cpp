#include<graphics.h>

void m(int x, int y) {
	cleardevice();
	setcolor(YELLOW);
	circle(x, y, 50);
}

main() {
	
	initwindow(640, 480);
	
	registermousehandler(WM_MOUSEMOVE, m);
	
	getch();
	closegraph();

}
