#ifndef DRAW_WINAPI_H
#define DRAW_WINAPI_H

#include <windows.h>

class Draw {
	HWND hwnd;
	HDC hdc;
	//PAINTSTRUCT ps;
	COLORREF color, backgroundColor;
	int width;
public:
	void SetWindow(HWND hwnd) {
		this->hwnd = hwnd;
		width = 1;
		color = RGB(0, 0, 0);
		backgroundColor = RGB(255, 255, 255);
		Prepare();
	}
	void SetColor(COLORREF color) {
		this->color = color;
		SelectObject(hdc, CreatePen(PS_SOLID, width, color));
	}
	void SetBackgroundColor(COLORREF color) {
		this->backgroundColor = color;
		SelectObject(hdc, CreateSolidBrush(color));
	}
	void SetWidth(int width) {
		this->width = width;
		SelectObject(hdc, CreatePen(PS_SOLID, width, color));
	}
	
	HDC GetHDC() {
		return hdc;
	}

	void Prepare() {
//		hdc = BeginPaint(hwnd, &ps);
		hdc = GetDC(hwnd);
		SetColor(color);
		SetBackgroundColor(backgroundColor);
	}
	void Finish() {
		//EndPaint(hwnd, &ps);
		ReleaseDC(hwnd, hdc);
	}
	
	POINT GetCenter() {
		RECT rect;
		GetClientRect(hwnd, &rect);
		return (POINT){rect.right/2, rect.bottom/2};
	}
	
	void Line(int x1, int y1, int x2, int y2) {
		Prepare();
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
		Finish();
	}
	void Circle(int x, int y, int radius) {
		Prepare();
		Ellipse(hdc, x-radius, y-radius, x+radius, y+radius);
		Finish();
	}
};

#endif
