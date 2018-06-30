#include "winapi.h"
#include <windows.h>
Draw::Draw() {
	width = 1;
	color = RGB(0, 0, 0);
	backgroundColor = RGB(255, 255, 255);
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

void Draw::Begin(HWND hwnd) {
	return Begin(GetDC(hwnd));
}
void Draw::Begin(HDC hdc) {
	this->hdc = hdc;
	SetColor(color);
	SetBackgroundColor(backgroundColor);
}
void Draw::End() {
	ReleaseDC(WindowFromDC(hdc), hdc);
}

POINT Draw::GetCenter() {
	RECT rect;
	GetClientRect(WindowFromDC(hdc), &rect);
	POINT p;
	p.x = rect.right/2;
	p.y = rect.bottom/2;
	return p;
}

void Draw::Line(int x1, int y1, int x2, int y2) {
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}
void Draw::Circle(int x, int y, int radius) {
	Ellipse(hdc, x-radius, y-radius, x+radius, y+radius);
}
void Draw::Image(int RESOURCE_ID, int x, int y) {
	HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(RESOURCE_ID));
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(bitmap), &bitmap);

	HDC hdcBitmap = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmap, hBitmap);
	BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcBitmap, 0, 0, SRCCOPY);
	DeleteDC(hdcBitmap);
	DeleteObject(hBitmap);
}