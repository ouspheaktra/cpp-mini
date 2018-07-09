#include "winapi.h"
#include "string.h"
#include <windows.h>
#include <math.h>

#define PI	3.14
#define toRadian(x)	(x*PI/180)

BOOL (__stdcall *Rect)(HDC, int, int, int, int) = Rectangle;

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
void Draw::Circle(POINT point, int radius) {
	Circle(point.x, point.y, radius);
}
void Draw::Rectangle(POINT point, int width, int height) {
	Rectangle(point.x, point.y, width, height);
}
void Draw::Rectangle(int x, int y, int width, int height) {
	Rect(hdc, x, y, x+width, y+height);
}
void Draw::Rectangle(int x, int y, int width, int height, int angle) {
	double w = (width / 2) * cos(toRadian(angle)) - (height / 2) * sin(toRadian(angle));
	double h = (height / 2) * cos(toRadian(angle)) + (width / 2) * sin(toRadian(angle));
	POINT p[4];
	p[0].x = x + w;
	p[0].y = y + h;
	p[1].x = x - w;
	p[1].y = y + h;
	p[2].x = x - w;
	p[2].y = y - h;
	p[3].x = x + w;
	p[3].y = y - h;
	Polygon(hdc, p, 4);
}
void Draw::Text(String s, int x, int y) {
	TextOut(hdc, x, y, s, s.Length());
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