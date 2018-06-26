#ifndef WINAPI_H
#define WINAPI_H

#include <windef.h>

class Draw {
	HWND hwnd;
	HDC hdc;
	//PAINTSTRUCT ps;
	COLORREF color, backgroundColor;
	int width;
public:
	void SetWindow(HWND hwnd);
	void SetColor(COLORREF color);
	void SetBackgroundColor(COLORREF color);
	void SetWidth(int width);
	
	HDC GetHDC();

	void Prepare();
	void Finish();
	
	POINT GetCenter();
	
	void Line(int x1, int y1, int x2, int y2);
	void Circle(int x, int y, int radius);
};

#endif
