#include "winapi.h"
#include <windows.h>


void Draw::SetWindow(HWND hwnd) {
	this->hwnd = hwnd;
	width = 1;
	color = RGB(0, 0, 0);
	backgroundColor = RGB(255, 255, 255);
	Prepare();
}
void Draw::SetColor(COLORREF color) {
	this->color = color;
	SelectObject(hdc, CreatePen(PS_SOLID, width, color));
}
void Draw::SetBackgroundColor(COLORREF color) {
	this->backgroundColor = color;
	SelectObject(hdc, CreateSolidBrush(color));
}
void Draw::SetWidth(int width) {
	this->width = width;
	SelectObject(hdc, CreatePen(PS_SOLID, width, color));
}

HDC Draw::GetHDC() {
	return hdc;
}

void Draw::Prepare() {
//		hdc = BeginPaint(hwnd, &ps);
	hdc = GetDC(hwnd);
	SetColor(color);
	SetBackgroundColor(backgroundColor);
}
void Draw::Finish() {
	//EndPaint(hwnd, &ps);
	ReleaseDC(hwnd, hdc);
}

POINT Draw::GetCenter() {
	RECT rect;
	GetClientRect(hwnd, &rect);
	return (POINT){rect.right/2, rect.bottom/2};
}

void Draw::Line(int x1, int y1, int x2, int y2) {
	Prepare();
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	Finish();
}
void Draw::Circle(int x, int y, int radius) {
	Prepare();
	Ellipse(hdc, x-radius, y-radius, x+radius, y+radius);
	Finish();
}
