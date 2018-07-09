#ifndef WINAPI_H
#define WINAPI_H

#include <windows.h>
#include "string.h"

class Draw {
	HDC hdc;
	COLORREF color, backgroundColor;
	int width;
public:
	Draw();
	void SetColor(COLORREF color);
	void SetBackgroundColor(COLORREF color);
	void SetWidth(int width);
	
	HDC GetHDC();

	void Begin(HWND hwnd);
	void Begin(HDC hdc);
	void End();
	
	POINT GetCenter();
	
	void Line(int x1, int y1, int x2, int y2);
	void Circle(int x, int y, int radius);
	void Circle(POINT point, int radius);
	void Image(int RESOURCE_ID, int x, int y);
	void Rectangle(POINT point, int width, int height);
	void Rectangle(int x, int y, int width, int height);
	void Rectangle(int x, int y, int width, int height, int angle);
	void Text(String s, int x, int y);
};

#endif
